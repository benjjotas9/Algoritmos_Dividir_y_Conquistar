#include <bits/stdc++.h>
#include <fstream>
#include <sys/resource.h>
#include <sys/time.h> 
using namespace std;

int partition(vector<int>& arr, int low, int high) {
  
    // Choose the pivot
    int pivot = arr[high];
  
    // Index of smaller element and indicates 
    // the right position of pivot found so far
    int i = low - 1;

    // Traverse arr[;ow..high] and move all smaller
    // elements on left side. Elements from low to 
    // i are smaller after every iteration
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    // Move pivot after smaller elements and
    // return its position
    swap(arr[i + 1], arr[high]);  
    return i + 1;
}

// The QuickSort function implementation
void quickSort(vector<int>& arr, int low, int high) {
  
    if (low < high) {
      
        // pi is the partition return index of pivot
        int pi = partition(arr, low, high);

        // Recursion calls for smaller elements
        // and greater or equals elements
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
// Función para medir el tiempo de ejecución usando getrusage
double obtenerTiempo(struct timeval start, struct timeval end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
}


int main() {
    vector<int> arr;  // Vector para almacenar los números

    // Leer el archivo CSV
    ifstream file("datos_aleatorios.csv");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string value;
        while (getline(ss, value, ',')) {
            arr.push_back(stoi(value));  // Convertimos cada valor a entero y lo agregamos al vector
        }
    }
    file.close();  


    // Medir el uso de recursos antes de ejecutar el algoritmo
    struct rusage usage_start, usage_end;
    getrusage(RUSAGE_SELF, &usage_start);

    int n = arr.size();
    quickSort(arr, 0, n - 1);  // Llamamos a QuickSort para ordenar el vector

    // Medir el uso de recursos después de ejecutar el algoritmo
    getrusage(RUSAGE_SELF, &usage_end);

    // Calcular el tiempo en segundos
    double user_time = obtenerTiempo(usage_start.ru_utime, usage_end.ru_utime);

    // Imprimir el resultado ordenado
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ",";  // Añadir una coma entre los elementos, excepto el último
    }
    cout << endl;  // Imprimir nueva línea al final

    cout << "Tiempo de CPU en modo usuario: " << user_time << " segundos\n";
    return 0;
}
