#include<iostream>
#include<omp.h>
using namespace std;

void sBubble(int array[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                swap(array[j], array[j + 1]);
            }
        }
    }
}

void pBubble(int array[], int n) {
    for (int i = 0; i < n; i++) {
        #pragma omp parallel for
        for (int j = 1; j < n; j += 2) {
            if (array[j] < array[j - 1]) {
                swap(array[j], array[j - 1]);
            }
        }

        #pragma omp parallel for
        for (int j = 2; j < n; j += 2) {
            if (array[j] < array[j - 1]) {
                swap(array[j], array[j - 1]);
            }
        }
    }
}

void printArray(int arr[], int n) {
    cout << "[ ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "]\n";
}

int main() {
    int n;

    cout << "Enter the number of elements: ";
    cin >> n;

    int arr[n], brr[n];
    cout << "Enter the elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        brr[i] = arr[i]; // duplicate for parallel version
    }

    double start_time, end_time;

    // Sequential
    start_time = omp_get_wtime();
    sBubble(arr, n);
    end_time = omp_get_wtime();
    cout << "\n===== Sequential Bubble Sort =====\n";
    cout << "Sorted Array: ";
    printArray(arr, n);
    cout << "Time Taken: " << (end_time - start_time) * 1000 << " milliseconds\n";

    // Parallel
    start_time = omp_get_wtime();
    pBubble(brr, n);
    end_time = omp_get_wtime();
    cout << "\n===== Parallel Bubble Sort =====\n";
    cout << "Sorted Array: ";
    printArray(brr, n);
    cout << "Time Taken: " << (end_time - start_time) * 1000 << " milliseconds\n";

    return 0;
}
