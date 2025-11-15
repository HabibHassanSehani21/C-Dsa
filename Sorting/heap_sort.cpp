// Heap Sort - Comparison-based sorting using binary heap
#include <iostream>
#include <vector>
using namespace std;

// Heapify a subtree rooted at index i
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;       // Initialize largest as root
    int left = 2 * i + 1;  // Left child
    int right = 2 * i + 2; // Right child
    
    // If left child is larger than root
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    
    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    
    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);
        
        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Main function to perform heap sort
void heapSort(vector<int>& arr) {
    int n = arr.size();
    
    // Build max heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    
    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(arr[0], arr[i]);
        
        // Call heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

// Min Heap Sort (sorts in descending order)
void minHeapify(vector<int>& arr, int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && arr[left] < arr[smallest]) {
        smallest = left;
    }
    
    if (right < n && arr[right] < arr[smallest]) {
        smallest = right;
    }
    
    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        minHeapify(arr, n, smallest);
    }
}

void heapSortDescending(vector<int>& arr) {
    int n = arr.size();
    
    // Build min heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        minHeapify(arr, n, i);
    }
    
    // Extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        minHeapify(arr, i, 0);
    }
}

// Display array
void displayArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

// Visualize heap structure
void displayHeap(const vector<int>& arr) {
    int n = arr.size();
    int height = 0;
    int level = 1;
    
    cout << "Heap structure:" << endl;
    
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
        
        if (i == level - 1 && i < n - 1) {
            cout << endl;
            level = level * 2 + 1;
        }
    }
    cout << endl;
}

// Build max heap and display
void buildMaxHeap(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

int main() {
    cout << "=== Heap Sort (Ascending Order) ===" << endl;
    
    vector<int> arr1 = {64, 34, 25, 12, 22, 11, 90, 88, 45, 50};
    
    cout << "Original array: ";
    displayArray(arr1);
    
    heapSort(arr1);
    
    cout << "Sorted array: ";
    displayArray(arr1);
    
    cout << "\n=== Heap Sort (Descending Order) ===" << endl;
    
    vector<int> arr2 = {38, 27, 43, 3, 9, 82, 10};
    
    cout << "Original array: ";
    displayArray(arr2);
    
    heapSortDescending(arr2);
    
    cout << "Sorted array (descending): ";
    displayArray(arr2);
    
    cout << "\n=== Building Max Heap ===" << endl;
    
    vector<int> arr3 = {4, 10, 3, 5, 1};
    
    cout << "Original array: ";
    displayArray(arr3);
    
    buildMaxHeap(arr3);
    
    cout << "Max heap: ";
    displayArray(arr3);
    displayHeap(arr3);
    
    // Test with negative numbers
    cout << "\n=== Sorting with Negative Numbers ===" << endl;
    vector<int> arr4 = {-5, 10, -3, 0, 8, -9, 1};
    
    cout << "Original array: ";
    displayArray(arr4);
    
    heapSort(arr4);
    
    cout << "Sorted array: ";
    displayArray(arr4);
    
    // Test with duplicates
    cout << "\n=== Sorting with Duplicates ===" << endl;
    vector<int> arr5 = {5, 2, 8, 2, 9, 1, 5, 5};
    
    cout << "Original array: ";
    displayArray(arr5);
    
    heapSort(arr5);
    
    cout << "Sorted array: ";
    displayArray(arr5);
    
    return 0;
}

/*
Time Complexity:
- Best Case: O(n log n)
- Average Case: O(n log n)
- Worst Case: O(n log n)

Space Complexity: O(1) - in-place sorting (O(log n) if counting recursion stack)

Stability: Not stable (relative order of equal elements may change)

When to use:
- When consistent O(n log n) performance is required
- When memory is limited (in-place sorting)
- When worst-case performance matters
- Priority queue implementation

Advantages:
- Guaranteed O(n log n) performance
- In-place sorting (no extra space needed)
- Better worst-case performance than quicksort
- No recursion stack overflow risk

Disadvantages:
- Not stable
- Not cache-friendly (random memory access)
- Slower than quicksort in practice
- More complex implementation

Heap Properties:
- Max Heap: Parent >= Children
- Min Heap: Parent <= Children
- Complete binary tree
- Height: O(log n)

Applications:
- Priority queues
- Heap data structure
- Finding k largest/smallest elements
- External sorting
*/
