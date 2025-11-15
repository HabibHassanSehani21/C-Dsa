// Bubble Sort - Simple comparison-based sorting algorithm
#include <iostream>
#include <vector>
using namespace std;

// Basic Bubble Sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Optimized Bubble Sort (stops early if array is already sorted)
void bubbleSortOptimized(vector<int>& arr) {
    int n = arr.size();
    bool swapped;
    
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        
        // If no swaps were made, array is already sorted
        if (!swapped) {
            break;
        }
    }
}

// Display array
void displayArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    cout << "=== Bubble Sort ===" << endl;
    
    vector<int> arr1 = {64, 34, 25, 12, 22, 11, 90};
    
    cout << "Original array: ";
    displayArray(arr1);
    
    bubbleSort(arr1);
    
    cout << "Sorted array: ";
    displayArray(arr1);
    
    cout << "\n=== Optimized Bubble Sort ===" << endl;
    
    vector<int> arr2 = {5, 1, 4, 2, 8};
    cout << "Original array: ";
    displayArray(arr2);
    
    bubbleSortOptimized(arr2);
    
    cout << "Sorted array: ";
    displayArray(arr2);
    
    // Test with already sorted array
    vector<int> arr3 = {1, 2, 3, 4, 5};
    cout << "\nAlready sorted array: ";
    displayArray(arr3);
    
    bubbleSortOptimized(arr3);
    
    cout << "After bubble sort: ";
    displayArray(arr3);
    
    return 0;
}

/*
Time Complexity:
- Best Case: O(n) - when array is already sorted (optimized version)
- Average Case: O(n²)
- Worst Case: O(n²) - when array is reverse sorted

Space Complexity: O(1) - in-place sorting

Stability: Stable (maintains relative order of equal elements)

When to use:
- Small datasets
- Nearly sorted data (with optimization)
- Educational purposes
- When simplicity is more important than efficiency
*/
