// Binary Search - Efficient search algorithm for sorted arrays
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Iterative Binary Search
int binarySearch(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        }
        
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1; // Element not found
}

// Recursive Binary Search
int binarySearchRecursive(const vector<int>& arr, int target, int left, int right) {
    if (left > right) {
        return -1;
    }
    
    int mid = left + (right - left) / 2;
    
    if (arr[mid] == target) {
        return mid;
    }
    
    if (arr[mid] < target) {
        return binarySearchRecursive(arr, target, mid + 1, right);
    } else {
        return binarySearchRecursive(arr, target, left, mid - 1);
    }
}

int binarySearchRecursive(const vector<int>& arr, int target) {
    return binarySearchRecursive(arr, target, 0, arr.size() - 1);
}

// Find first occurrence of target
int findFirstOccurrence(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            right = mid - 1; // Continue searching in left half
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

// Find last occurrence of target
int findLastOccurrence(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            left = mid + 1; // Continue searching in right half
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

// Count occurrences of target
int countOccurrences(const vector<int>& arr, int target) {
    int first = findFirstOccurrence(arr, target);
    
    if (first == -1) {
        return 0;
    }
    
    int last = findLastOccurrence(arr, target);
    return last - first + 1;
}

// Lower bound - find first element >= target
int lowerBound(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size();
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return left;
}

// Upper bound - find first element > target
int upperBound(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size();
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] <= target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return left;
}

// Search in rotated sorted array
int searchRotated(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        }
        
        // Check which half is sorted
        if (arr[left] <= arr[mid]) {
            // Left half is sorted
            if (target >= arr[left] && target < arr[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else {
            // Right half is sorted
            if (target > arr[mid] && target <= arr[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    
    return -1;
}

// Find peak element (element greater than its neighbors)
int findPeakElement(const vector<int>& arr) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] < arr[mid + 1]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return left;
}

int main() {
    cout << "=== Basic Binary Search ===" << endl;
    
    vector<int> arr = {2, 5, 8, 12, 16, 23, 38, 45, 56, 67, 78};
    
    cout << "Array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    
    int target = 23;
    int result = binarySearch(arr, target);
    cout << "Search for " << target << ": " 
         << (result != -1 ? "Found at index " + to_string(result) : "Not found") << endl;
    
    target = 100;
    result = binarySearchRecursive(arr, target);
    cout << "Search for " << target << ": " 
         << (result != -1 ? "Found at index " + to_string(result) : "Not found") << endl;
    
    cout << "\n=== Finding Occurrences ===" << endl;
    
    vector<int> arr2 = {1, 2, 2, 2, 3, 4, 5, 5, 5, 5, 6};
    
    cout << "Array: ";
    for (int num : arr2) {
        cout << num << " ";
    }
    cout << endl;
    
    target = 5;
    int first = findFirstOccurrence(arr2, target);
    int last = findLastOccurrence(arr2, target);
    int count = countOccurrences(arr2, target);
    
    cout << "First occurrence of " << target << ": " << first << endl;
    cout << "Last occurrence of " << target << ": " << last << endl;
    cout << "Total occurrences: " << count << endl;
    
    cout << "\n=== Lower and Upper Bound ===" << endl;
    
    target = 5;
    int lb = lowerBound(arr2, target);
    int ub = upperBound(arr2, target);
    
    cout << "Lower bound of " << target << ": " << lb << endl;
    cout << "Upper bound of " << target << ": " << ub << endl;
    
    cout << "\n=== Search in Rotated Sorted Array ===" << endl;
    
    vector<int> rotated = {6, 7, 8, 9, 1, 2, 3, 4, 5};
    
    cout << "Rotated array: ";
    for (int num : rotated) {
        cout << num << " ";
    }
    cout << endl;
    
    target = 3;
    result = searchRotated(rotated, target);
    cout << "Search for " << target << ": " 
         << (result != -1 ? "Found at index " + to_string(result) : "Not found") << endl;
    
    cout << "\n=== Find Peak Element ===" << endl;
    
    vector<int> peakArr = {1, 3, 20, 4, 1, 0};
    
    cout << "Array: ";
    for (int num : peakArr) {
        cout << num << " ";
    }
    cout << endl;
    
    int peak = findPeakElement(peakArr);
    cout << "Peak element at index " << peak << " with value " << peakArr[peak] << endl;
    
    return 0;
}

/*
Time Complexity:
- Best Case: O(1) - element found at middle
- Average Case: O(log n)
- Worst Case: O(log n)

Space Complexity: 
- Iterative: O(1)
- Recursive: O(log n) - recursion stack

When to use:
- Searching in sorted arrays
- Finding boundaries (lower/upper bound)
- Optimization problems
- Searching in rotated arrays

Prerequisites:
- Array must be sorted (or have some order property)

Advantages:
- Very efficient for large datasets
- Simple to implement
- Logarithmic time complexity
- Works well with divide and conquer

Applications:
- Database indexing
- Dictionary lookups
- Finding insertion position
- Range queries
- Finding extrema in unimodal functions
*/
