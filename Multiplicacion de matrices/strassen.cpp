#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <sys/resource.h>
#include <sys/time.h> 
using namespace std;

// Función para medir el tiempo de ejecución usando getrusage
double obtenerTiempo(struct timeval start, struct timeval end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
}

// Función para leer una matriz desde un archivo TXT
vector<vector<int>> leer_matriz(string filename) {
    ifstream archivo(filename);
    vector<vector<int>> matriz;
    string linea;

    while (getline(archivo, linea)) {
        vector<int> fila;
        stringstream ss(linea);
        int numero;
        while (ss >> numero) {
            fila.push_back(numero);
        }
        matriz.push_back(fila);
    }

    archivo.close();
    return matriz;
}

// Función para imprimir una matriz
void print(string display, vector<vector<int>> matrix) {
    cout << endl << display << " =>" << endl;
    for (auto& fila : matrix) {
        for (auto& elem : fila) {
            cout << setw(10) << elem;
        }
        cout << endl;
    }
    cout << endl;
}

// Función para sumar dos matrices
vector<vector<int>> sum_matrix(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

// Función para restar dos matrices
vector<vector<int>> subtract_matrix(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

// Función para multiplicar matrices con el algoritmo de Strassen
vector<vector<int>> strassen_multiply(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();

    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    int newSize = n / 2;
    vector<int> inner(newSize);
    vector<vector<int>> 
        A11(newSize, inner), A12(newSize, inner), A21(newSize, inner), A22(newSize, inner),
        B11(newSize, inner), B12(newSize, inner), B21(newSize, inner), B22(newSize, inner),
        C11(newSize, inner), C12(newSize, inner), C21(newSize, inner), C22(newSize, inner),
        P1(newSize, inner), P2(newSize, inner), P3(newSize, inner), P4(newSize, inner),
        P5(newSize, inner), P6(newSize, inner), P7(newSize, inner);

    // Dividir las matrices A y B en 4 submatrices
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Calcular los 7 productos de Strassen
    P1 = strassen_multiply(A11, subtract_matrix(B12, B22));
    P2 = strassen_multiply(sum_matrix(A11, A12), B22);
    P3 = strassen_multiply(sum_matrix(A21, A22), B11);
    P4 = strassen_multiply(A22, subtract_matrix(B21, B11));
    P5 = strassen_multiply(sum_matrix(A11, A22), sum_matrix(B11, B22));
    P6 = strassen_multiply(subtract_matrix(A12, A22), sum_matrix(B21, B22));
    P7 = strassen_multiply(subtract_matrix(A11, A21), sum_matrix(B11, B12));

    // Calcular los elementos de la matriz resultante C
    C11 = sum_matrix(subtract_matrix(sum_matrix(P5, P4), P2), P6);
    C12 = sum_matrix(P1, P2);
    C21 = sum_matrix(P3, P4);
    C22 = subtract_matrix(subtract_matrix(sum_matrix(P5, P1), P3), P7);

    // Combinar las submatrices en la matriz resultante
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    return C;
}

int main() {
    // Leer las matrices desde archivos TXT
    vector<vector<int>> matrix_A = leer_matriz("matrix_A.txt");
    vector<vector<int>> matrix_B = leer_matriz("matrix_B.txt");

    // Verificar si las matrices son cuadradas y de tamaño potencia de 2
    if (matrix_A.size() != matrix_A[0].size() || matrix_B.size() != matrix_B[0].size() || matrix_A.size() != matrix_B.size()) {
        cout << "Error: Las matrices deben ser cuadradas y del mismo tamaño para Strassen.\n";
        return 1;
    }

    // Medir el tiempo de ejecución usando getrusage
    struct rusage usage_start, usage_end;
    getrusage(RUSAGE_SELF, &usage_start);

    // Multiplicar matrices con el algoritmo de Strassen
    vector<vector<int>> result_matrix = strassen_multiply(matrix_A, matrix_B);


    // Obtener el tiempo después de la multiplicación
    getrusage(RUSAGE_SELF, &usage_end);
    double user_time = obtenerTiempo(usage_start.ru_utime, usage_end.ru_utime);
    // Imprimir resultado
    print("Resultado de la multiplicación (Strassen)", result_matrix);
    

        // Imprimir el tiempo de ejecución
    cout << "Tiempo de CPU en modo usuario: " << user_time << " segundos\n";

    return 0;
}
