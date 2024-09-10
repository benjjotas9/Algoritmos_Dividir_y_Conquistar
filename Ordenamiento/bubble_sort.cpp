// Optimized implementation of Bubble sort
#include <bits/stdc++.h>
#include <fstream>
#include <sys/resource.h>
#include <sys/time.h> 
using namespace std;

// Función para leer el archivo CSV y almacenar los datos en un array
void leerCSV(string filename, vector<int>& data) {
    ifstream file(filename);
    string line, cell;

    while (getline(file, line)) {
        stringstream lineStream(line);
        while (getline(lineStream, cell, ',')) {
            // Verificamos si el valor no está vacío y es numérico
            try {
                if (!cell.empty()) {
                    data.push_back(stoi(cell)); // Convertir a entero y agregar al vector
                }
            } catch (const invalid_argument& e) {
                // Manejar valores que no son números enteros válidos
                cerr << "Valor no numérico encontrado en el CSV y omitido: " << cell << endl;
            }
        }
    }
    file.close();
}

// An optimized version of Bubble Sort
void bubbleSort(int arr[], int n)
{
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // If no two elements were swapped
        // by inner loop, then break
        if (swapped == false)
            break;
    }
}

// Función para obtener el tiempo en segundos y microsegundos
double obtenerTiempo(struct timeval start, struct timeval end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
}

// Función para imprimir un array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    vector<int> data; // Vector para almacenar los datos del CSV

    // Leer el archivo CSV
    string inputCSV = "datos_aleatorios.csv"; 
    leerCSV(inputCSV, data);

    // Verificar que hay datos válidos
    if (data.empty()) {
        cerr << "Error: No se encontraron datos válidos en el archivo CSV." << endl;
        return 1;
    }

    // Convertir el vector a un array para el algoritmo de ordenamiento
    int N = data.size();
    int arr[N];
    for (int i = 0; i < N; i++) {
        arr[i] = data[i];
    }

    // Medir el uso de recursos antes de ejecutar el algoritmo
    struct rusage usage_start, usage_end;
    getrusage(RUSAGE_SELF, &usage_start);

    // Aplicar el Bubble Sort
    bubbleSort(arr, N);

    // Medir el uso de recursos después de ejecutar el algoritmo
    getrusage(RUSAGE_SELF, &usage_end);

    // Calcular el tiempo en segundos
    double user_time = obtenerTiempo(usage_start.ru_utime, usage_end.ru_utime);

    // Imprimir el array ordenado
    cout << "Sorted array: \n";
    printArray(arr, N);


    cout << "Tiempo de CPU en modo usuario: " << user_time << " segundos\n";
    return 0;
}
// This code is contributed by shivanisinghss2110
