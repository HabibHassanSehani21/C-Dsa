// Vector - Dynamic Array Implementation and Usage in C++
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void demonstrateVector() {
    // Declaration and Initialization
    vector<int> vec;                    // Empty vector
    vector<int> vec2(5);                // Vector with 5 elements (default 0)
    vector<int> vec3(5, 10);            // Vector with 5 elements, all 10
    vector<int> vec4 = {1, 2, 3, 4, 5}; // Initialize with values
    
    cout << "=== Vector Operations ===" << endl;
    
    // Adding elements
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);
    vec.push_back(50);
    
    // Accessing elements
    cout << "Element at index 2: " << vec[2] << endl;
    cout << "Element at index 2 (at): " << vec.at(2) << endl;
    cout << "First element: " << vec.front() << endl;
    cout << "Last element: " << vec.back() << endl;
    
    // Size and Capacity
    cout << "Size: " << vec.size() << endl;
    cout << "Capacity: " << vec.capacity() << endl;
    cout << "Is empty: " << vec.empty() << endl;
    
    // Iterating through vector
    cout << "Elements: ";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
    
    // Using iterator
    cout << "Elements (iterator): ";
    for (auto it = vec.begin(); it != vec.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
    
    // Range-based for loop
    cout << "Elements (range-based): ";
    for (auto x : vec) {
        cout << x << " ";
    }
    cout << endl;
    
    // Modifying elements
    vec[0] = 100;
    vec.at(1) = 200;
    
    // Inserting elements
    vec.insert(vec.begin() + 2, 150); // Insert 150 at index 2
    
    // Removing elements
    vec.pop_back();              // Remove last element
    vec.erase(vec.begin() + 1);  // Remove element at index 1
    
    // Sorting
    sort(vec.begin(), vec.end());
    cout << "Sorted: ";
    for (auto x : vec) {
        cout << x << " ";
    }
    cout << endl;
    
    // Reversing
    reverse(vec.begin(), vec.end());
    cout << "Reversed: ";
    for (auto x : vec) {
        cout << x << " ";
    }
    cout << endl;
    
    // Clear all elements
    vec.clear();
    cout << "Size after clear: " << vec.size() << endl;
}

int main() {
    demonstrateVector();
    return 0;
}

/*
Time Complexity:
- Access: O(1)
- Insert/Delete at end: O(1) amortized
- Insert/Delete at arbitrary position: O(n)
- Search: O(n)

Space Complexity: O(n)
*/
