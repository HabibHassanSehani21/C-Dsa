// Linear Search - Simple sequential search algorithm
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Basic Linear Search
int linearSearch(const vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1; // Element not found
}

// Linear Search - Find all occurrences
vector<int> linearSearchAll(const vector<int>& arr, int target) {
    vector<int> indices;
    
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == target) {
            indices.push_back(i);
        }
    }
    
    return indices;
}

// Linear Search on strings
int linearSearch(const vector<string>& arr, const string& target) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

// Search with custom comparator
template<typename T, typename Compare>
int linearSearch(const vector<T>& arr, const T& target, Compare comp) {
    for (int i = 0; i < arr.size(); i++) {
        if (comp(arr[i], target)) {
            return i;
        }
    }
    return -1;
}

// Find maximum element
int findMax(const vector<int>& arr) {
    if (arr.empty()) {
        throw runtime_error("Array is empty");
    }
    
    int maxVal = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }
    
    return maxVal;
}

// Find minimum element
int findMin(const vector<int>& arr) {
    if (arr.empty()) {
        throw runtime_error("Array is empty");
    }
    
    int minVal = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] < minVal) {
            minVal = arr[i];
        }
    }
    
    return minVal;
}

// Find second largest element
int findSecondLargest(const vector<int>& arr) {
    if (arr.size() < 2) {
        throw runtime_error("Array must have at least 2 elements");
    }
    
    int largest = INT_MIN;
    int secondLargest = INT_MIN;
    
    for (int num : arr) {
        if (num > largest) {
            secondLargest = largest;
            largest = num;
        } else if (num > secondLargest && num != largest) {
            secondLargest = num;
        }
    }
    
    if (secondLargest == INT_MIN) {
        throw runtime_error("No second largest element found");
    }
    
    return secondLargest;
}

// Sentinel Linear Search (optimized - one comparison per iteration)
int sentinelLinearSearch(vector<int> arr, int target) {
    int n = arr.size();
    int last = arr[n - 1];
    
    arr[n - 1] = target;
    int i = 0;
    
    while (arr[i] != target) {
        i++;
    }
    
    arr[n - 1] = last;
    
    if (i < n - 1 || arr[n - 1] == target) {
        return i;
    }
    
    return -1;
}

// Count occurrences
int countOccurrences(const vector<int>& arr, int target) {
    int count = 0;
    
    for (int num : arr) {
        if (num == target) {
            count++;
        }
    }
    
    return count;
}

int main() {
    cout << "=== Basic Linear Search ===" << endl;
    
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90, 88};
    
    cout << "Array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    
    int target = 22;
    int result = linearSearch(arr, target);
    cout << "Search for " << target << ": " 
         << (result != -1 ? "Found at index " + to_string(result) : "Not found") << endl;
    
    target = 100;
    result = linearSearch(arr, target);
    cout << "Search for " << target << ": " 
         << (result != -1 ? "Found at index " + to_string(result) : "Not found") << endl;
    
    cout << "\n=== Find All Occurrences ===" << endl;
    
    vector<int> arr2 = {5, 2, 8, 2, 9, 1, 5, 5};
    
    cout << "Array: ";
    for (int num : arr2) {
        cout << num << " ";
    }
    cout << endl;
    
    target = 5;
    vector<int> indices = linearSearchAll(arr2, target);
    cout << "All occurrences of " << target << ": ";
    for (int idx : indices) {
        cout << idx << " ";
    }
    cout << endl;
    
    cout << "Count of " << target << ": " << countOccurrences(arr2, target) << endl;
    
    cout << "\n=== Search in String Array ===" << endl;
    
    vector<string> names = {"Alice", "Bob", "Charlie", "David", "Eve"};
    
    cout << "Names: ";
    for (const string& name : names) {
        cout << name << " ";
    }
    cout << endl;
    
    string searchName = "Charlie";
    int nameIdx = linearSearch(names, searchName);
    cout << "Search for " << searchName << ": " 
         << (nameIdx != -1 ? "Found at index " + to_string(nameIdx) : "Not found") << endl;
    
    cout << "\n=== Find Max and Min ===" << endl;
    
    cout << "Array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
    
    cout << "Maximum element: " << findMax(arr) << endl;
    cout << "Minimum element: " << findMin(arr) << endl;
    
    try {
        cout << "Second largest element: " << findSecondLargest(arr) << endl;
    } catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    cout << "\n=== Sentinel Linear Search ===" << endl;
    
    vector<int> arr3 = {10, 20, 30, 40, 50};
    
    cout << "Array: ";
    for (int num : arr3) {
        cout << num << " ";
    }
    cout << endl;
    
    target = 30;
    result = sentinelLinearSearch(arr3, target);
    cout << "Sentinel search for " << target << ": " 
         << (result != -1 ? "Found at index " + to_string(result) : "Not found") << endl;
    
    return 0;
}

/*
Time Complexity:
- Best Case: O(1) - element at first position
- Average Case: O(n)
- Worst Case: O(n) - element at last position or not found

Space Complexity: O(1)

When to use:
- Small datasets
- Unsorted arrays
- Searching once in an array
- When simplicity is more important than efficiency
- Linked lists (binary search not possible)

Advantages:
- Simple to implement
- Works on unsorted data
- No preprocessing required
- Works with any data type
- Suitable for linked lists

Disadvantages:
- Inefficient for large datasets
- Linear time complexity
- Not suitable for frequent searches

Optimizations:
- Sentinel search (reduces comparisons)
- Move-to-front (for repeated searches)
- Transposition (swap with previous element after each search)
*/
