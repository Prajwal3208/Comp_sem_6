#include<iostream>
#include<omp.h>
#include<vector>

using namespace std;

void merge(int arr[], int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    vector<int> left(n1), right(n2);

    for (int i = 0; i < n1; i++) left[i] = arr[low + i];
    for (int j = 0; j < n2; j++) right[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = low;

    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) arr[k++] = left[i++];
        else arr[k++] = right[j++];
    }

    while (i < n1) arr[k++] = left[i++];
    while (j < n2) arr[k++] = right[j++];
}

void sequentialMergeSort(int arr[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        sequentialMergeSort(arr, low, mid);
        sequentialMergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

void parallelMergeSort(int arr[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(arr, low, mid);

            #pragma omp section
            parallelMergeSort(arr, mid + 1, high);
        }

        merge(arr, low, mid, high);
    }
}

void printArray(int arr[], int n) {
    cout << "[ ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << "]\n";
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    int* arr = new int[n];
    int* temp = new int[n];

    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        temp[i] = arr[i];  // copy for parallel
    }

    double start, end;

    // Sequential
    cout << "\n===== Sequential Merge Sort =====\n";
    start = omp_get_wtime();
    sequentialMergeSort(arr, 0, n - 1);
    end = omp_get_wtime();
    cout << "Sorted Array: ";
    printArray(arr, n);
    cout << "Time Taken: " << (end - start) * 1000 << " milliseconds\n";

    // Parallel
    cout << "\n===== Parallel Merge Sort =====\n";
    start = omp_get_wtime();
    parallelMergeSort(temp, 0, n - 1);
    end = omp_get_wtime();
    cout << "Sorted Array: ";
    printArray(temp, n);
    cout << "Time Taken: " << (end - start) * 1000 << " milliseconds\n";

    delete[] arr;
    delete[] temp;

    return 0;
}
