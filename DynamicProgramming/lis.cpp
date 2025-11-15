// Longest Increasing Subsequence (LIS) - Dynamic Programming
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// LIS using DP - O(n²)
int lisDP(const vector<int>& arr) {
    int n = arr.size();
    vector<int> dp(n, 1);
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    
    return *max_element(dp.begin(), dp.end());
}

// LIS with subsequence reconstruction
pair<int, vector<int>> lisDPWithSequence(const vector<int>& arr) {
    int n = arr.size();
    vector<int> dp(n, 1);
    vector<int> parent(n, -1);
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
    }
    
    // Find index with maximum LIS length
    int maxLength = 0;
    int maxIndex = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i] > maxLength) {
            maxLength = dp[i];
            maxIndex = i;
        }
    }
    
    // Reconstruct LIS
    vector<int> lis;
    int current = maxIndex;
    while (current != -1) {
        lis.push_back(arr[current]);
        current = parent[current];
    }
    
    reverse(lis.begin(), lis.end());
    
    return {maxLength, lis};
}

// LIS using Binary Search - O(n log n)
int lisBinarySearch(const vector<int>& arr) {
    vector<int> tails;
    
    for (int num : arr) {
        auto it = lower_bound(tails.begin(), tails.end(), num);
        
        if (it == tails.end()) {
            tails.push_back(num);
        } else {
            *it = num;
        }
    }
    
    return tails.size();
}

// LIS using Binary Search with sequence
pair<int, vector<int>> lisBinarySearchWithSequence(const vector<int>& arr) {
    int n = arr.size();
    vector<int> tails;
    vector<int> parent(n, -1);
    vector<int> indices;
    
    for (int i = 0; i < n; i++) {
        auto it = lower_bound(tails.begin(), tails.end(), arr[i]);
        int pos = it - tails.begin();
        
        if (it == tails.end()) {
            tails.push_back(arr[i]);
            if (pos > 0) {
                parent[i] = indices[pos - 1];
            }
            indices.push_back(i);
        } else {
            *it = arr[i];
            if (pos > 0) {
                parent[i] = indices[pos - 1];
            }
            indices[pos] = i;
        }
    }
    
    // Reconstruct LIS
    vector<int> lis;
    int current = indices.back();
    while (current != -1) {
        lis.push_back(arr[current]);
        current = parent[current];
    }
    
    reverse(lis.begin(), lis.end());
    
    return {tails.size(), lis};
}

// Longest Decreasing Subsequence
int lds(const vector<int>& arr) {
    int n = arr.size();
    vector<int> dp(n, 1);
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    
    return *max_element(dp.begin(), dp.end());
}

// Longest Bitonic Subsequence (increasing then decreasing)
int longestBitonicSubsequence(const vector<int>& arr) {
    int n = arr.size();
    
    // LIS ending at each index
    vector<int> lis(n, 1);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                lis[i] = max(lis[i], lis[j] + 1);
            }
        }
    }
    
    // LDS starting from each index
    vector<int> lds(n, 1);
    for (int i = n - 2; i >= 0; i--) {
        for (int j = n - 1; j > i; j--) {
            if (arr[j] < arr[i]) {
                lds[i] = max(lds[i], lds[j] + 1);
            }
        }
    }
    
    // Maximum bitonic length
    int maxLength = 0;
    for (int i = 0; i < n; i++) {
        maxLength = max(maxLength, lis[i] + lds[i] - 1);
    }
    
    return maxLength;
}

// Number of LIS
int numberOfLIS(const vector<int>& arr) {
    int n = arr.size();
    vector<int> length(n, 1);
    vector<int> count(n, 1);
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                if (length[j] + 1 > length[i]) {
                    length[i] = length[j] + 1;
                    count[i] = count[j];
                } else if (length[j] + 1 == length[i]) {
                    count[i] += count[j];
                }
            }
        }
    }
    
    int maxLength = *max_element(length.begin(), length.end());
    int result = 0;
    
    for (int i = 0; i < n; i++) {
        if (length[i] == maxLength) {
            result += count[i];
        }
    }
    
    return result;
}

int main() {
    cout << "=== Longest Increasing Subsequence (LIS) ===" << endl;
    
    vector<int> arr1 = {10, 9, 2, 5, 3, 7, 101, 18};
    
    cout << "Array: ";
    for (int num : arr1) {
        cout << num << " ";
    }
    cout << endl;
    
    int length = lisDP(arr1);
    cout << "LIS Length (DP): " << length << endl;
    
    auto [len, lis] = lisDPWithSequence(arr1);
    cout << "LIS: ";
    for (int num : lis) {
        cout << num << " ";
    }
    cout << endl;
    
    cout << "\n=== LIS using Binary Search (Faster) ===" << endl;
    
    int lengthBS = lisBinarySearch(arr1);
    cout << "LIS Length (Binary Search): " << lengthBS << endl;
    
    auto [lenBS, lisBS] = lisBinarySearchWithSequence(arr1);
    cout << "LIS: ";
    for (int num : lisBS) {
        cout << num << " ";
    }
    cout << endl;
    
    cout << "\n=== Another Example ===" << endl;
    
    vector<int> arr2 = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
    
    cout << "Array: ";
    for (int num : arr2) {
        cout << num << " ";
    }
    cout << endl;
    
    auto [len2, lis2] = lisBinarySearchWithSequence(arr2);
    cout << "LIS Length: " << len2 << endl;
    cout << "LIS: ";
    for (int num : lis2) {
        cout << num << " ";
    }
    cout << endl;
    
    cout << "\n=== Longest Decreasing Subsequence ===" << endl;
    
    vector<int> arr3 = {10, 9, 2, 5, 3, 7, 101, 18};
    
    cout << "Array: ";
    for (int num : arr3) {
        cout << num << " ";
    }
    cout << endl;
    
    int ldsLen = lds(arr3);
    cout << "LDS Length: " << ldsLen << endl;
    
    cout << "\n=== Longest Bitonic Subsequence ===" << endl;
    
    vector<int> arr4 = {1, 11, 2, 10, 4, 5, 2, 1};
    
    cout << "Array: ";
    for (int num : arr4) {
        cout << num << " ";
    }
    cout << endl;
    
    int lbsLen = longestBitonicSubsequence(arr4);
    cout << "Longest Bitonic Subsequence Length: " << lbsLen << endl;
    
    cout << "\n=== Number of LIS ===" << endl;
    
    vector<int> arr5 = {1, 3, 5, 4, 7};
    
    cout << "Array: ";
    for (int num : arr5) {
        cout << num << " ";
    }
    cout << endl;
    
    int numLIS = numberOfLIS(arr5);
    cout << "Number of LIS: " << numLIS << endl;
    
    return 0;
}

/*
Time Complexity:
- DP approach: O(n²)
- Binary Search approach: O(n log n)

Space Complexity: O(n)

Approaches:
1. DP: Check all previous elements for each element
2. Binary Search: Maintain array of smallest tail elements

Problem Variants:
1. LIS - Longest Increasing Subsequence
2. LDS - Longest Decreasing Subsequence
3. LBS - Longest Bitonic Subsequence
4. Number of LIS
5. Russian Doll Envelopes (2D LIS)

Applications:
- Patience sorting
- Box stacking problems
- Building bridges
- Maximum length chain
- Activity selection variants

Key Insights:
- DP: dp[i] = max length ending at i
- Binary Search: tails[i] = smallest tail of length i+1
- For non-decreasing: use lower_bound
- For strictly increasing: use upper_bound

Related Problems:
- Maximum Sum Increasing Subsequence
- Longest Alternating Subsequence
- Box Stacking Problem
- Russian Doll Envelopes
*/
