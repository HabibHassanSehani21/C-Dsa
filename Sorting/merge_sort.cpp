// Merge Sort - Divide and Conquer sorting algorithm
#include <iostream>
#include <vector>
using namespace std;

// Merge two sorted subarrays
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Create temporary arrays
    vector<int> L(n1);
    vector<int> R(n2);
    
    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }
    
    // Merge the temporary arrays back
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // Copy remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // Copy remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge Sort function
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        
        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Wrapper function
void mergeSort(vector<int>& arr) {
    mergeSort(arr, 0, arr.size() - 1);
}

// Display array
void displayArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

// Iterative Merge Sort
void mergeSortIterative(vector<int>& arr) {
    int n = arr.size();
    
    // Start with merge subarrays of size 1, then 2, 4, 8, ...
    for (int currSize = 1; currSize < n; currSize *= 2) {
        // Pick starting index of left sub array to be merged
        for (int leftStart = 0; leftStart < n - 1; leftStart += 2 * currSize) {
            // Find ending point of left subarray
            int mid = min(leftStart + currSize - 1, n - 1);
            
            // Find ending point of right subarray
            int rightEnd = min(leftStart + 2 * currSize - 1, n - 1);
            
            // Merge subarrays
            merge(arr, leftStart, mid, rightEnd);
        }
    }
}

int main() {
    cout << "=== Merge Sort (Recursive) ===" << endl;
    
    vector<int> arr1 = {64, 34, 25, 12, 22, 11, 90, 88, 45, 50};
    
    cout << "Original array: ";
    displayArray(arr1);
    
    mergeSort(arr1);
    
    cout << "Sorted array: ";
    displayArray(arr1);
    
    cout << "\n=== Merge Sort (Iterative) ===" << endl;
    
    vector<int> arr2 = {38, 27, 43, 3, 9, 82, 10};
    
    cout << "Original array: ";
    displayArray(arr2);
    
    mergeSortIterative(arr2);
    
    cout << "Sorted array: ";
    displayArray(arr2);
    
    // Test with negative numbers
    cout << "\n=== Sorting with Negative Numbers ===" << endl;
    vector<int> arr3 = {-5, 10, -3, 0, 8, -9, 1};
    
    cout << "Original array: ";
    displayArray(arr3);
    
    mergeSort(arr3);
    
    cout << "Sorted array: ";
    displayArray(arr3);
    
    return 0;
}

/*
Time Complexity:
- Best Case: O(n log n)
- Average Case: O(n log n)
- Worst Case: O(n log n)

Space Complexity: O(n) - requires additional space for merging

Stability: Stable (maintains relative order of equal elements)

When to use:
- Large datasets
- When stable sorting is required
- When guaranteed O(n log n) performance is needed
- External sorting (sorting data that doesn't fit in memory)
- Linked lists (no random access penalty)

Advantages:
- Consistent O(n log n) performance
- Stable sorting algorithm
- Works well with linked lists
- Good for external sorting

Disadvantages:
- Requires O(n) extra space
- Slower than quicksort in practice for arrays
*/
