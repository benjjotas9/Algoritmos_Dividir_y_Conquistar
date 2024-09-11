#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <sys/resource.h>
#include <sys/time.h> 

using namespace std;

// Función para medir el tiempo de ejecución usando getrusage
double obtenerTiempo(struct timeval start, struct timeval end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
}

// Función para leer una matriz desde un archivo
vector<vector<int>> leerMatrizDesdeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    vector<vector<int>> matriz;
    string linea;

    while (getline(archivo, linea)) {
        vector<int> fila;
        stringstream ss(linea);
        int valor;

        while (ss >> valor) {
            fila.push_back(valor);
        }

        matriz.push_back(fila);
    }

    return matriz;
}

// Funciones auxiliares para las operaciones de Strassen
vector<vector<int>> sumarMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] + B[i][j];

    return C;
}

vector<vector<int>> restarMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] - B[i][j];

    return C;
}

vector<vector<int>> strassenMultiplicacion(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();

    if (n == 1) {
        vector<vector<int>> C(1, vector<int>(1));
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int newSize = n / 2;
    vector<vector<int>> A11(newSize, vector<int>(newSize));
    vector<vector<int>> A12(newSize, vector<int>(newSize));
    vector<vector<int>> A21(newSize, vector<int>(newSize));
    vector<vector<int>> A22(newSize, vector<int>(newSize));
    vector<vector<int>> B11(newSize, vector<int>(newSize));
    vector<vector<int>> B12(newSize, vector<int>(newSize));
    vector<vector<int>> B21(newSize, vector<int>(newSize));
    vector<vector<int>> B22(newSize, vector<int>(newSize));

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

    vector<vector<int>> M1 = strassenMultiplicacion(sumarMatrices(A11, A22), sumarMatrices(B11, B22));
    vector<vector<int>> M2 = strassenMultiplicacion(sumarMatrices(A21, A22), B11);
    vector<vector<int>> M3 = strassenMultiplicacion(A11, restarMatrices(B12, B22));
    vector<vector<int>> M4 = strassenMultiplicacion(A22, restarMatrices(B21, B11));
    vector<vector<int>> M5 = strassenMultiplicacion(sumarMatrices(A11, A12), B22);
    vector<vector<int>> M6 = strassenMultiplicacion(restarMatrices(A21, A11), sumarMatrices(B11, B12));
    vector<vector<int>> M7 = strassenMultiplicacion(restarMatrices(A12, A22), sumarMatrices(B21, B22));

    vector<vector<int>> C11 = sumarMatrices(restarMatrices(sumarMatrices(M1, M4), M5), M7);
    vector<vector<int>> C12 = sumarMatrices(M3, M5);
    vector<vector<int>> C21 = sumarMatrices(M2, M4);
    vector<vector<int>> C22 = sumarMatrices(restarMatrices(sumarMatrices(M1, M3), M2), M6);

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

// Función para imprimir la matriz
void imprimirMatriz(const vector<vector<int>>& matriz) {
    for (const auto& fila : matriz) {
        for (int valor : fila) {
            cout << valor << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<int>> A = leerMatrizDesdeArchivo("matrix_A.txt");
    vector<vector<int>> B = leerMatrizDesdeArchivo("matrix_B.txt");

    if (A.size() != B.size() || A[0].size() != B[0].size()) {
        cout << "Las matrices deben ser cuadradas y del mismo tamaño." << endl;
        return 1;
    }

    // Medir el tiempo de ejecución usando getrusage
    struct rusage usage_start, usage_end;
    getrusage(RUSAGE_SELF, &usage_start);

    vector<vector<int>> C = strassenMultiplicacion(A, B);

    // Obtener el tiempo después de la multiplicación
    getrusage(RUSAGE_SELF, &usage_end);
    double user_time = obtenerTiempo(usage_start.ru_utime, usage_end.ru_utime);

    cout << "Resultado de la multiplicación de matrices usando Strassen:" << endl;
    imprimirMatriz(C);

    cout << "Tiempo de CPU en modo usuario: " << user_time << " segundos\n";

    return 0;
}
