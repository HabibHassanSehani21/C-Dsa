// Set - Container with Unique Elements in C++
#include <iostream>
#include <set>
#include <unordered_set>
using namespace std;

void demonstrateSet() {
    cout << "=== Set Operations (Ordered, Unique) ===" << endl;
    
    // Declaration
    set<int> s;
    
    // Insert elements
    s.insert(30);
    s.insert(10);
    s.insert(50);
    s.insert(20);
    s.insert(40);
    s.insert(20); // Duplicate - won't be inserted
    
    cout << "Size: " << s.size() << endl;
    
    // Display elements (automatically sorted)
    cout << "Set elements: ";
    for (auto x : s) {
        cout << x << " ";
    }
    cout << endl;
    
    // Check if element exists
    if (s.find(30) != s.end()) {
        cout << "30 exists in set" << endl;
    }
    
    if (s.count(100) == 0) {
        cout << "100 does not exist in set" << endl;
    }
    
    // Lower bound and upper bound
    auto lb = s.lower_bound(25); // First element >= 25
    cout << "Lower bound of 25: " << *lb << endl;
    
    auto ub = s.upper_bound(30); // First element > 30
    cout << "Upper bound of 30: " << *ub << endl;
    
    // Erase element
    s.erase(20);
    cout << "Size after erasing 20: " << s.size() << endl;
    
    // Erase by iterator
    s.erase(s.begin());
    cout << "After erasing first element: ";
    for (auto x : s) {
        cout << x << " ";
    }
    cout << endl;
    
    // Clear all elements
    s.clear();
    cout << "Size after clear: " << s.size() << endl;
}

void demonstrateUnorderedSet() {
    cout << "\n=== Unordered Set Operations (Hash Table) ===" << endl;
    
    unordered_set<int> us;
    
    // Insert elements
    us.insert(30);
    us.insert(10);
    us.insert(50);
    us.insert(20);
    us.insert(40);
    
    cout << "Unordered Set elements: ";
    for (auto x : us) {
        cout << x << " ";
    }
    cout << endl;
    
    // Find element
    if (us.find(30) != us.end()) {
        cout << "30 found in unordered set" << endl;
    }
}

void demonstrateMultiset() {
    cout << "\n=== Multiset Operations (Allows Duplicates) ===" << endl;
    
    multiset<int> ms;
    
    // Insert elements (including duplicates)
    ms.insert(30);
    ms.insert(10);
    ms.insert(30);
    ms.insert(20);
    ms.insert(30);
    ms.insert(10);
    
    cout << "Multiset elements: ";
    for (auto x : ms) {
        cout << x << " ";
    }
    cout << endl;
    
    // Count occurrences
    cout << "Count of 30: " << ms.count(30) << endl;
    cout << "Count of 10: " << ms.count(10) << endl;
    
    // Erase one occurrence
    ms.erase(ms.find(30)); // Erase one occurrence of 30
    cout << "After erasing one 30: ";
    for (auto x : ms) {
        cout << x << " ";
    }
    cout << endl;
    
    // Erase all occurrences
    ms.erase(10); // Erase all occurrences of 10
    cout << "After erasing all 10s: ";
    for (auto x : ms) {
        cout << x << " ";
    }
    cout << endl;
}

// Example: Finding unique elements in an array
vector<int> findUniqueElements(vector<int>& arr) {
    set<int> s(arr.begin(), arr.end());
    return vector<int>(s.begin(), s.end());
}

int main() {
    demonstrateSet();
    demonstrateUnorderedSet();
    demonstrateMultiset();
    
    cout << "\n=== Example: Finding Unique Elements ===" << endl;
    vector<int> arr = {1, 2, 3, 2, 4, 1, 5, 3, 6};
    cout << "Original array: ";
    for (auto x : arr) {
        cout << x << " ";
    }
    cout << endl;
    
    vector<int> unique = findUniqueElements(arr);
    cout << "Unique elements: ";
    for (auto x : unique) {
        cout << x << " ";
    }
    cout << endl;
    
    return 0;
}

/*
Time Complexity:
Set (Balanced BST):
- Insert: O(log n)
- Delete: O(log n)
- Search: O(log n)

Unordered Set (Hash Table):
- Insert: O(1) average, O(n) worst
- Delete: O(1) average, O(n) worst
- Search: O(1) average, O(n) worst

Space Complexity: O(n)
*/
