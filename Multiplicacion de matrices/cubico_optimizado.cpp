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

// Función para leer una matriz desde un archivo .txt
vector<vector<int>> leer_matriz(const string& filename) {
    ifstream archivo(filename);
    vector<vector<int>> matriz;
    string linea;

    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo " << filename << endl;
        return matriz;
    }

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
void print_matrix(const vector<vector<int>>& matrix, const string& nombre) {
    cout << "\n" << nombre << ":" << endl;
    for (const auto& fila : matrix) {
        for (const auto& elem : fila) {
            cout << setw(5) << elem;
        }
        cout << endl;
    }
}

// Función para transponer una matriz
vector<vector<int>> transponer_matriz(const vector<vector<int>>& matriz) {
    int filas = matriz.size();
    int columnas = matriz[0].size();
    vector<vector<int>> matriz_transpuesta(columnas, vector<int>(filas));

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            matriz_transpuesta[j][i] = matriz[i][j];
        }
    }

    return matriz_transpuesta;
}

// Función de multiplicación cúbica optimizada para matrices cuadradas o no cuadradas
vector<vector<int>> multiplicar_matrices_optimizado(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int filas_A = A.size();
    int columnas_A = A[0].size();
    int filas_B = B.size();
    int columnas_B = B[0].size();

    // Verificar si la multiplicación es posible
    if (columnas_A != filas_B) {
        cerr << "Error: El número de columnas de la matriz A debe ser igual al número de filas de la matriz B." << endl;
        return {};
    }

    // Transponer la matriz B para mejorar la localización en caché
    vector<vector<int>> B_transpuesta = transponer_matriz(B);

    // Crear la matriz resultante inicializada en 0
    vector<vector<int>> C(filas_A, vector<int>(columnas_B, 0));

    // Multiplicación optimizada con la matriz B transpuesta
    for (int i = 0; i < filas_A; i++) {
        for (int j = 0; j < columnas_B; j++) {
            for (int k = 0; k < columnas_A; k++) {
                C[i][j] += A[i][k] * B_transpuesta[j][k];
            }
        }
    }

    return C;
}

int main() {
    vector<vector<int>> A = leer_matriz("matrix_A.txt");
    vector<vector<int>> B = leer_matriz("matrix_B.txt");

    if (A.empty() || B.empty()) {
        cerr << "Error: No se pudo leer una o ambas matrices." << endl;
        return 1;
    }

    // Medir el tiempo de ejecución usando getrusage
    struct rusage usage_start, usage_end;
    getrusage(RUSAGE_SELF, &usage_start);

    // Multiplicar las matrices
    vector<vector<int>> C = multiplicar_matrices_optimizado(A, B);

    // Obtener el tiempo después de la multiplicación
    getrusage(RUSAGE_SELF, &usage_end);
    double user_time = obtenerTiempo(usage_start.ru_utime, usage_end.ru_utime);

    // Imprimir el resultado si la multiplicación fue exitosa
    if (!C.empty()) {
        print_matrix(C, "Matriz Resultante");
    }

    cout << "Tiempo de CPU en modo usuario: " << user_time << " segundos\n";

    return 0;
}
