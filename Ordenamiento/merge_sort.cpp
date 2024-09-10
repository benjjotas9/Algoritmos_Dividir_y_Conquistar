#include <bits/stdc++.h>
#include <sys/resource.h>  
#include <sys/time.h> 
using namespace std;

// Merges two subarrays of arr[].
// First subarray is arr[left..mid]
// Second subarray is arr[mid+1..right]
void merge(vector<int>& arr, int left, 
                     int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp vectors
    vector<int> L(n1), R(n2);

    // Copy data to temp vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Merge the temp vectors back 
    // into arr[left..right]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], 
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], 
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// begin is for left index and end is right index
// of the sub-array of arr to be sorted
void mergeSort(vector<int>& arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Function to print a vector
void printVector(vector<int>& arr)
{
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    cout << endl;
}


// Function to read CSV file and return a vector of integers
vector<int> readCSV(const string& filename)
{
    vector<int> data;
    ifstream file(filename);
    string line;


    while (getline(file, line)) {
        stringstream ss(line);
        string value;


        while (getline(ss, value, ',')) {
            data.push_back(stoi(value));  
        }
    }

    file.close();
    return data;
}


// Función para medir el tiempo de ejecución usando getrusage
double obtenerTiempo(struct timeval start, struct timeval end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
}

// Driver code
int main()
{

    string filename = "datos_aleatorios.csv"; 
    vector<int> arr = readCSV(filename);


    struct rusage usage_start, usage_end;
    getrusage(RUSAGE_SELF, &usage_start);


    // Aplicar Merge Sort
    mergeSort(arr, 0, arr.size() - 1);


    // Obtener el tiempo después de ejecutar Merge Sort
    getrusage(RUSAGE_SELF, &usage_end);
    double user_time = obtenerTiempo(usage_start.ru_utime, usage_end.ru_utime);
    
    cout << "\nSorted vector is:\n";
    printVector(arr);

    cout << "Tiempo de CPU en modo usuario: " << user_time << " segundos\n";

    return 0;
}
