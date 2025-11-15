// Quick Sort - Efficient divide and conquer sorting algorithm
#include <iostream>
#include <vector>
using namespace std;

// Partition function (Lomuto partition scheme)
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Choose last element as pivot
    int i = low - 1;       // Index of smaller element
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quick Sort function
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        // Partitioning index
        int pi = partition(arr, low, high);
        
        // Recursively sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Wrapper function
void quickSort(vector<int>& arr) {
    quickSort(arr, 0, arr.size() - 1);
}

// Hoare partition scheme (alternative partitioning)
int hoarePartition(vector<int>& arr, int low, int high) {
    int pivot = arr[low];
    int i = low - 1;
    int j = high + 1;
    
    while (true) {
        do {
            i++;
        } while (arr[i] < pivot);
        
        do {
            j--;
        } while (arr[j] > pivot);
        
        if (i >= j) {
            return j;
        }
        
        swap(arr[i], arr[j]);
    }
}

// Quick Sort with Hoare partition
void quickSortHoare(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = hoarePartition(arr, low, high);
        
        quickSortHoare(arr, low, pi);
        quickSortHoare(arr, pi + 1, high);
    }
}

void quickSortHoare(vector<int>& arr) {
    quickSortHoare(arr, 0, arr.size() - 1);
}

// Three-way partition (for arrays with many duplicates)
void threeWayPartition(vector<int>& arr, int low, int high, int& lt, int& gt) {
    if (high - low <= 1) {
        if (arr[high] < arr[low]) {
            swap(arr[high], arr[low]);
        }
        lt = low;
        gt = high;
        return;
    }
    
    int mid = low;
    int pivot = arr[high];
    
    while (mid <= high) {
        if (arr[mid] < pivot) {
            swap(arr[low], arr[mid]);
            low++;
            mid++;
        } else if (arr[mid] > pivot) {
            swap(arr[mid], arr[high]);
            high--;
        } else {
            mid++;
        }
    }
    
    lt = low - 1;
    gt = high + 1;
}

// Quick Sort with three-way partition
void quickSort3Way(vector<int>& arr, int low, int high) {
    if (low >= high) return;
    
    int lt, gt;
    threeWayPartition(arr, low, high, lt, gt);
    
    quickSort3Way(arr, low, lt);
    quickSort3Way(arr, gt, high);
}

void quickSort3Way(vector<int>& arr) {
    quickSort3Way(arr, 0, arr.size() - 1);
}

// Display array
void displayArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    cout << "=== Quick Sort (Lomuto Partition) ===" << endl;
    
    vector<int> arr1 = {64, 34, 25, 12, 22, 11, 90, 88, 45, 50};
    
    cout << "Original array: ";
    displayArray(arr1);
    
    quickSort(arr1);
    
    cout << "Sorted array: ";
    displayArray(arr1);
    
    cout << "\n=== Quick Sort (Hoare Partition) ===" << endl;
    
    vector<int> arr2 = {38, 27, 43, 3, 9, 82, 10};
    
    cout << "Original array: ";
    displayArray(arr2);
    
    quickSortHoare(arr2);
    
    cout << "Sorted array: ";
    displayArray(arr2);
    
    cout << "\n=== Quick Sort with Many Duplicates ===" << endl;
    
    vector<int> arr3 = {4, 9, 4, 4, 1, 9, 4, 4, 9, 4, 4, 1, 4};
    
    cout << "Original array: ";
    displayArray(arr3);
    
    quickSort3Way(arr3);
    
    cout << "Sorted array (3-way partition): ";
    displayArray(arr3);
    
    // Test with negative numbers
    cout << "\n=== Sorting with Negative Numbers ===" << endl;
    vector<int> arr4 = {-5, 10, -3, 0, 8, -9, 1};
    
    cout << "Original array: ";
    displayArray(arr4);
    
    quickSort(arr4);
    
    cout << "Sorted array: ";
    displayArray(arr4);
    
    return 0;
}

/*
Time Complexity:
- Best Case: O(n log n) - when partition divides array evenly
- Average Case: O(n log n)
- Worst Case: O(n²) - when array is already sorted or reverse sorted

Space Complexity: 
- O(log n) - recursion stack space (best case)
- O(n) - recursion stack space (worst case)

Stability: Not stable (relative order of equal elements may change)

When to use:
- General purpose sorting
- Large datasets
- When average-case performance is important
- In-place sorting is required

Advantages:
- Fast in practice (often faster than merge sort)
- In-place sorting (low memory overhead)
- Cache-friendly
- Good average-case performance

Disadvantages:
- Unstable
- Worst-case O(n²) performance
- Not suitable for linked lists

Optimizations:
1. Choose pivot randomly or use median-of-three
2. Switch to insertion sort for small subarrays
3. Three-way partitioning for arrays with many duplicates
*/
