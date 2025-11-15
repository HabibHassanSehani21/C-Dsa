// Map - Associative Container (Key-Value pairs) in C++
#include <iostream>
#include <map>
#include <unordered_map>
using namespace std;

void demonstrateMap() {
    cout << "=== Map Operations (Ordered) ===" << endl;
    
    // Declaration
    map<string, int> mp;
    
    // Insert elements
    mp["apple"] = 5;
    mp["banana"] = 3;
    mp["orange"] = 7;
    mp.insert({"grape", 4});
    mp.insert(make_pair("mango", 6));
    
    // Access elements
    cout << "apple count: " << mp["apple"] << endl;
    cout << "banana count: " << mp.at("banana") << endl;
    
    // Check if key exists
    if (mp.find("grape") != mp.end()) {
        cout << "grape exists with count: " << mp["grape"] << endl;
    }
    
    if (mp.count("watermelon") == 0) {
        cout << "watermelon does not exist" << endl;
    }
    
    // Size
    cout << "Size: " << mp.size() << endl;
    
    // Iterate through map
    cout << "Map elements (key-value pairs):" << endl;
    for (auto pair : mp) {
        cout << pair.first << ": " << pair.second << endl;
    }
    
    // Iterate using iterator
    cout << "Using iterator:" << endl;
    for (auto it = mp.begin(); it != mp.end(); it++) {
        cout << it->first << ": " << it->second << endl;
    }
    
    // Update value
    mp["apple"] = 10;
    cout << "Updated apple count: " << mp["apple"] << endl;
    
    // Erase element
    mp.erase("banana");
    cout << "Size after erasing banana: " << mp.size() << endl;
    
    // Clear all elements
    mp.clear();
    cout << "Size after clear: " << mp.size() << endl;
}

void demonstrateUnorderedMap() {
    cout << "\n=== Unordered Map Operations (Hash Table) ===" << endl;
    
    unordered_map<string, int> ump;
    
    // Insert elements
    ump["red"] = 1;
    ump["green"] = 2;
    ump["blue"] = 3;
    ump["yellow"] = 4;
    
    cout << "Unordered Map elements:" << endl;
    for (auto pair : ump) {
        cout << pair.first << ": " << pair.second << endl;
    }
    
    // Finding element
    auto it = ump.find("green");
    if (it != ump.end()) {
        cout << "Found green with value: " << it->second << endl;
    }
}

void demonstrateMultimap() {
    cout << "\n=== Multimap Operations (Multiple values per key) ===" << endl;
    
    multimap<string, int> mmp;
    
    // Insert multiple values for same key
    mmp.insert({"apple", 1});
    mmp.insert({"apple", 2});
    mmp.insert({"apple", 3});
    mmp.insert({"banana", 4});
    mmp.insert({"banana", 5});
    
    cout << "Multimap elements:" << endl;
    for (auto pair : mmp) {
        cout << pair.first << ": " << pair.second << endl;
    }
    
    // Find all values for a key
    cout << "All values for 'apple':" << endl;
    auto range = mmp.equal_range("apple");
    for (auto it = range.first; it != range.second; it++) {
        cout << it->second << " ";
    }
    cout << endl;
}

int main() {
    demonstrateMap();
    demonstrateUnorderedMap();
    demonstrateMultimap();
    
    return 0;
}

/*
Time Complexity:
Map (Balanced BST):
- Insert: O(log n)
- Delete: O(log n)
- Search: O(log n)

Unordered Map (Hash Table):
- Insert: O(1) average, O(n) worst
- Delete: O(1) average, O(n) worst
- Search: O(1) average, O(n) worst

Space Complexity: O(n)
*/
