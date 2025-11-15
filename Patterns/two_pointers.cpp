// Two Pointers Technique - Common Patterns and Problems
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 1. Two Sum (sorted array)
pair<int, int> twoSumSorted(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left < right) {
        int sum = arr[left] + arr[right];
        
        if (sum == target) {
            return {left, right};
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    
    return {-1, -1};
}

// 2. Remove duplicates from sorted array (in-place)
int removeDuplicates(vector<int>& arr) {
    if (arr.empty()) return 0;
    
    int i = 0;  // Slow pointer
    
    for (int j = 1; j < arr.size(); j++) {  // Fast pointer
        if (arr[j] != arr[i]) {
            i++;
            arr[i] = arr[j];
        }
    }
    
    return i + 1;
}

// 3. Container with most water
int maxArea(const vector<int>& height) {
    int left = 0;
    int right = height.size() - 1;
    int maxWater = 0;
    
    while (left < right) {
        int width = right - left;
        int h = min(height[left], height[right]);
        maxWater = max(maxWater, width * h);
        
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }
    
    return maxWater;
}

// 4. Three Sum (find triplets that sum to target)
vector<vector<int>> threeSum(vector<int>& arr, int target = 0) {
    vector<vector<int>> result;
    sort(arr.begin(), arr.end());
    
    for (int i = 0; i < arr.size() - 2; i++) {
        // Skip duplicates
        if (i > 0 && arr[i] == arr[i - 1]) continue;
        
        int left = i + 1;
        int right = arr.size() - 1;
        
        while (left < right) {
            int sum = arr[i] + arr[left] + arr[right];
            
            if (sum == target) {
                result.push_back({arr[i], arr[left], arr[right]});
                
                // Skip duplicates
                while (left < right && arr[left] == arr[left + 1]) left++;
                while (left < right && arr[right] == arr[right - 1]) right--;
                
                left++;
                right--;
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
    }
    
    return result;
}

// 5. Reverse string in-place
void reverseString(string& s) {
    int left = 0;
    int right = s.length() - 1;
    
    while (left < right) {
        swap(s[left], s[right]);
        left++;
        right--;
    }
}

// 6. Valid palindrome
bool isPalindrome(const string& s) {
    int left = 0;
    int right = s.length() - 1;
    
    while (left < right) {
        // Skip non-alphanumeric characters
        while (left < right && !isalnum(s[left])) left++;
        while (left < right && !isalnum(s[right])) right--;
        
        if (tolower(s[left]) != tolower(s[right])) {
            return false;
        }
        
        left++;
        right--;
    }
    
    return true;
}

// 7. Move zeros to end
void moveZeros(vector<int>& arr) {
    int nonZero = 0;  // Position to place next non-zero element
    
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] != 0) {
            swap(arr[nonZero], arr[i]);
            nonZero++;
        }
    }
}

// 8. Partition array (Dutch National Flag)
void partition(vector<int>& arr, int pivot) {
    int low = 0;
    int mid = 0;
    int high = arr.size() - 1;
    
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
}

// 9. Merge two sorted arrays
vector<int> mergeSorted(const vector<int>& arr1, const vector<int>& arr2) {
    vector<int> result;
    int i = 0, j = 0;
    
    while (i < arr1.size() && j < arr2.size()) {
        if (arr1[i] <= arr2[j]) {
            result.push_back(arr1[i]);
            i++;
        } else {
            result.push_back(arr2[j]);
            j++;
        }
    }
    
    while (i < arr1.size()) {
        result.push_back(arr1[i]);
        i++;
    }
    
    while (j < arr2.size()) {
        result.push_back(arr2[j]);
        j++;
    }
    
    return result;
}

// 10. Squares of sorted array
vector<int> sortedSquares(const vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n);
    int left = 0;
    int right = n - 1;
    int pos = n - 1;
    
    while (left <= right) {
        int leftSquare = arr[left] * arr[left];
        int rightSquare = arr[right] * arr[right];
        
        if (leftSquare > rightSquare) {
            result[pos] = leftSquare;
            left++;
        } else {
            result[pos] = rightSquare;
            right--;
        }
        pos--;
    }
    
    return result;
}

int main() {
    cout << "=== Two Pointers Technique ===" << endl;
    
    cout << "\n1. Two Sum (Sorted Array)" << endl;
    vector<int> arr1 = {2, 7, 11, 15};
    int target = 9;
    auto [idx1, idx2] = twoSumSorted(arr1, target);
    cout << "Array: ";
    for (int x : arr1) cout << x << " ";
    cout << "\nTarget: " << target << endl;
    cout << "Indices: " << idx1 << ", " << idx2 << endl;
    
    cout << "\n2. Remove Duplicates" << endl;
    vector<int> arr2 = {1, 1, 2, 2, 2, 3, 4, 4, 5};
    cout << "Original: ";
    for (int x : arr2) cout << x << " ";
    int newLen = removeDuplicates(arr2);
    cout << "\nAfter removing duplicates: ";
    for (int i = 0; i < newLen; i++) cout << arr2[i] << " ";
    cout << endl;
    
    cout << "\n3. Container With Most Water" << endl;
    vector<int> heights = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    cout << "Heights: ";
    for (int h : heights) cout << h << " ";
    cout << "\nMax water: " << maxArea(heights) << endl;
    
    cout << "\n4. Three Sum" << endl;
    vector<int> arr3 = {-1, 0, 1, 2, -1, -4};
    cout << "Array: ";
    for (int x : arr3) cout << x << " ";
    cout << "\nTriplets that sum to 0:" << endl;
    auto triplets = threeSum(arr3);
    for (const auto& t : triplets) {
        cout << "[" << t[0] << ", " << t[1] << ", " << t[2] << "]" << endl;
    }
    
    cout << "\n5. Reverse String" << endl;
    string s = "hello";
    cout << "Original: " << s << endl;
    reverseString(s);
    cout << "Reversed: " << s << endl;
    
    cout << "\n6. Valid Palindrome" << endl;
    string s1 = "A man, a plan, a canal: Panama";
    cout << "String: " << s1 << endl;
    cout << "Is palindrome: " << (isPalindrome(s1) ? "Yes" : "No") << endl;
    
    cout << "\n7. Move Zeros" << endl;
    vector<int> arr4 = {0, 1, 0, 3, 12};
    cout << "Original: ";
    for (int x : arr4) cout << x << " ";
    moveZeros(arr4);
    cout << "\nAfter moving zeros: ";
    for (int x : arr4) cout << x << " ";
    cout << endl;
    
    cout << "\n8. Partition Array (Dutch National Flag)" << endl;
    vector<int> arr5 = {3, 1, 2, 3, 2, 1, 3, 2, 1};
    cout << "Original: ";
    for (int x : arr5) cout << x << " ";
    partition(arr5, 2);
    cout << "\nAfter partitioning around 2: ";
    for (int x : arr5) cout << x << " ";
    cout << endl;
    
    cout << "\n9. Merge Sorted Arrays" << endl;
    vector<int> arr6 = {1, 3, 5, 7};
    vector<int> arr7 = {2, 4, 6, 8};
    cout << "Array 1: ";
    for (int x : arr6) cout << x << " ";
    cout << "\nArray 2: ";
    for (int x : arr7) cout << x << " ";
    vector<int> merged = mergeSorted(arr6, arr7);
    cout << "\nMerged: ";
    for (int x : merged) cout << x << " ";
    cout << endl;
    
    cout << "\n10. Squares of Sorted Array" << endl;
    vector<int> arr8 = {-4, -1, 0, 3, 10};
    cout << "Original: ";
    for (int x : arr8) cout << x << " ";
    vector<int> squares = sortedSquares(arr8);
    cout << "\nSquares: ";
    for (int x : squares) cout << x << " ";
    cout << endl;
    
    return 0;
}

/*
Time Complexity: O(n) for most problems
Space Complexity: O(1) - in-place operations

Two Pointers Pattern:
1. Opposite Direction: left and right pointers moving towards each other
2. Same Direction: slow and fast pointers (fast moves faster)
3. Multiple Arrays: pointers in different arrays

When to Use:
- Sorted arrays
- Finding pairs/triplets
- In-place modifications
- String manipulation
- Merging operations

Common Problems:
- Two Sum, Three Sum, Four Sum
- Container With Most Water
- Remove Duplicates
- Palindrome validation
- Dutch National Flag
- Merge Sorted Arrays
- Trapping Rain Water

Key Insights:
- Reduces O(n²) to O(n) for sorted arrays
- In-place operations save space
- Can handle multiple conditions
- Often combined with sorting

Advantages:
- Efficient: O(n) time
- Space efficient: O(1)
- Clean and readable code
- Avoids nested loops
*/
