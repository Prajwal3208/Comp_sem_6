#include <omp.h>
#include <iostream>
#include <chrono>
using namespace std::chrono;
using namespace std;

// Display Array
void displayArray(int nums[], int length)
{
    cout << "Nums: [";
    for (int i = 0; i < length; i++) {
        cout << nums[i];
        if (i != length - 1)
            cout << ", ";
    }
    cout << "]" << endl;
}

// Parallel Min Operation
void minOperation(int nums[], int length)
{
    int minValue = nums[0];
#pragma omp parallel for reduction(min : minValue)
    for (int i = 0; i < length; i++) {
        minValue = (nums[i] < minValue) ? nums[i] : minValue;
    }
    cout << "Min value: " << minValue << endl;
}

// Parallel Max Operation
void maxOperation(int nums[], int length)
{
    int maxValue = nums[0];
#pragma omp parallel for reduction(max : maxValue)
    for (int i = 0; i < length; i++) {
        maxValue = (nums[i] > maxValue) ? nums[i] : maxValue;
    }
    cout << "Max value: " << maxValue << endl;
}

// Parallel Sum Operation
void sumOperation(int nums[], int length)
{
    int sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < length; i++) {
        sum += nums[i];
    }
    cout << "Sum: " << sum << endl;
}

// Parallel Average Operation
void avgOperation(int nums[], int length)
{
    float sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < length; i++) {
        sum += nums[i];
    }
    cout << "Average: " << (sum / length) << endl;
}

// Main Function
int main()
{
    int nums[] = {4, 6, 3, 2, 6, 7, 9, 2, 1, 6, 5};
    int length = sizeof(nums) / sizeof(int);

    auto start = high_resolution_clock::now();

    displayArray(nums, length);
    minOperation(nums, length);
    maxOperation(nums, length);
    sumOperation(nums, length);
    avgOperation(nums, length);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nExecution time: " << duration.count() << " microseconds" << endl;

    return 0;
// }
// #include <iostream> 
// #include <vector> 
// #include <omp.h> 
// #include <climits> 
// using namespace std; 
// void min_reduction(vector<int>& arr) { 
// int min_value = INT_MAX; 
// #pragma omp parallel for reduction(min: min_value) 
// for (int i = 0; i < arr.size(); i++) { 
// if (arr[i] < min_value) { 
// min_value = arr[i]; 
// } 
// } 
// cout << "Minimum value: " << min_value << endl; 
// } 
// void max_reduction(vector<int>& arr) { 
// int max_value = INT_MIN; 
// #pragma omp parallel for reduction(max: max_value) 
// for (int i = 0; i < arr.size(); i++) { 
// if (arr[i] > max_value) { 
// max_value = arr[i]; 
// } 
// } 
// cout << "Maximum value: " << max_value << endl; 
// } 
// void sum_reduction(vector<int>& arr) { 
// int sum = 0; 
// #pragma omp parallel for reduction(+: sum) 
// for (int i = 0; i < arr.size(); i++) { 
// sum += arr[i]; 
// } 
// cout << "Sum: " << sum << endl; 
// } 
// void average_reduction(vector<int>& arr) { 
// int sum = 0; 
// #pragma omp parallel for reduction(+: sum) 
// for (int i = 0; i < arr.size(); i++) { 
// sum += arr[i]; 
// } 
// cout << "Average: " << (double)sum / arr.size() << endl; 
// } 
// int main() { 
// vector<int> arr = {5, 2, 9, 1, 7, 6, 8, 3, 4}; 
// min_reduction(arr); 
// max_reduction(arr); 
// sum_reduction(arr); 
// average_reduction(arr); 
// }