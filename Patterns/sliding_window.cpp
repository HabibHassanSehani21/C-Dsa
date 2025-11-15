// Sliding Window Technique - Common Patterns and Problems
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <climits>
using namespace std;

// 1. Maximum sum subarray of size k (Fixed Window)
int maxSumFixedWindow(const vector<int>& arr, int k) {
    if (arr.size() < k) return -1;
    
    int windowSum = 0;
    
    // Calculate sum of first window
    for (int i = 0; i < k; i++) {
        windowSum += arr[i];
    }
    
    int maxSum = windowSum;
    
    // Slide the window
    for (int i = k; i < arr.size(); i++) {
        windowSum = windowSum - arr[i - k] + arr[i];
        maxSum = max(maxSum, windowSum);
    }
    
    return maxSum;
}

// 2. Longest substring without repeating characters (Variable Window)
int longestUniqueSubstring(const string& s) {
    unordered_map<char, int> charIndex;
    int maxLength = 0;
    int start = 0;
    
    for (int end = 0; end < s.length(); end++) {
        if (charIndex.find(s[end]) != charIndex.end()) {
            start = max(start, charIndex[s[end]] + 1);
        }
        
        charIndex[s[end]] = end;
        maxLength = max(maxLength, end - start + 1);
    }
    
    return maxLength;
}

// 3. Minimum window substring containing all characters
string minWindowSubstring(const string& s, const string& t) {
    if (s.empty() || t.empty()) return "";
    
    unordered_map<char, int> required;
    for (char c : t) {
        required[c]++;
    }
    
    int requiredChars = required.size();
    int formed = 0;
    unordered_map<char, int> windowCounts;
    
    int left = 0;
    int minLen = INT_MAX;
    int minLeft = 0;
    
    for (int right = 0; right < s.length(); right++) {
        char c = s[right];
        windowCounts[c]++;
        
        if (required.find(c) != required.end() && 
            windowCounts[c] == required[c]) {
            formed++;
        }
        
        // Contract window
        while (left <= right && formed == requiredChars) {
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
                minLeft = left;
            }
            
            char leftChar = s[left];
            windowCounts[leftChar]--;
            if (required.find(leftChar) != required.end() && 
                windowCounts[leftChar] < required[leftChar]) {
                formed--;
            }
            
            left++;
        }
    }
    
    return minLen == INT_MAX ? "" : s.substr(minLeft, minLen);
}

// 4. Maximum of all subarrays of size k
vector<int> maxSlidingWindow(const vector<int>& arr, int k) {
    vector<int> result;
    deque<int> dq;  // Store indices
    
    for (int i = 0; i < arr.size(); i++) {
        // Remove elements outside current window
        while (!dq.empty() && dq.front() < i - k + 1) {
            dq.pop_front();
        }
        
        // Remove smaller elements (they won't be max)
        while (!dq.empty() && arr[dq.back()] < arr[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
        
        // Add to result after first window
        if (i >= k - 1) {
            result.push_back(arr[dq.front()]);
        }
    }
    
    return result;
}

// 5. Count subarrays with sum equal to k
int countSubarraysWithSum(const vector<int>& arr, int k) {
    unordered_map<int, int> prefixSum;
    prefixSum[0] = 1;
    
    int sum = 0;
    int count = 0;
    
    for (int num : arr) {
        sum += num;
        
        if (prefixSum.find(sum - k) != prefixSum.end()) {
            count += prefixSum[sum - k];
        }
        
        prefixSum[sum]++;
    }
    
    return count;
}

// 6. Longest subarray with sum <= k
int longestSubarrayWithSum(const vector<int>& arr, int k) {
    int maxLength = 0;
    int sum = 0;
    int left = 0;
    
    for (int right = 0; right < arr.size(); right++) {
        sum += arr[right];
        
        while (sum > k && left <= right) {
            sum -= arr[left];
            left++;
        }
        
        maxLength = max(maxLength, right - left + 1);
    }
    
    return maxLength;
}

// 7. Fruits into baskets (at most 2 types)
int maxFruits(const vector<int>& fruits) {
    unordered_map<int, int> basket;
    int maxFruits = 0;
    int left = 0;
    
    for (int right = 0; right < fruits.size(); right++) {
        basket[fruits[right]]++;
        
        while (basket.size() > 2) {
            basket[fruits[left]]--;
            if (basket[fruits[left]] == 0) {
                basket.erase(fruits[left]);
            }
            left++;
        }
        
        maxFruits = max(maxFruits, right - left + 1);
    }
    
    return maxFruits;
}

// 8. Number of subarrays with product less than k
int numSubarraysWithProductLessThanK(const vector<int>& arr, int k) {
    if (k <= 1) return 0;
    
    int count = 0;
    int product = 1;
    int left = 0;
    
    for (int right = 0; right < arr.size(); right++) {
        product *= arr[right];
        
        while (product >= k) {
            product /= arr[left];
            left++;
        }
        
        count += right - left + 1;
    }
    
    return count;
}

// 9. Find all anagrams in string
vector<int> findAnagrams(const string& s, const string& p) {
    vector<int> result;
    if (s.length() < p.length()) return result;
    
    unordered_map<char, int> pCount;
    unordered_map<char, int> sCount;
    
    for (char c : p) {
        pCount[c]++;
    }
    
    int windowSize = p.length();
    
    // First window
    for (int i = 0; i < windowSize; i++) {
        sCount[s[i]]++;
    }
    
    if (sCount == pCount) {
        result.push_back(0);
    }
    
    // Slide window
    for (int i = windowSize; i < s.length(); i++) {
        sCount[s[i]]++;
        sCount[s[i - windowSize]]--;
        
        if (sCount[s[i - windowSize]] == 0) {
            sCount.erase(s[i - windowSize]);
        }
        
        if (sCount == pCount) {
            result.push_back(i - windowSize + 1);
        }
    }
    
    return result;
}

// 10. Minimum flips to make binary string alternating
int minFlips(const string& s) {
    int n = s.length();
    string target1 = "", target2 = "";
    
    // Create two possible alternating patterns
    for (int i = 0; i < n; i++) {
        target1 += (i % 2 == 0) ? '0' : '1';
        target2 += (i % 2 == 0) ? '1' : '0';
    }
    
    int flips1 = 0, flips2 = 0;
    
    for (int i = 0; i < n; i++) {
        if (s[i] != target1[i]) flips1++;
        if (s[i] != target2[i]) flips2++;
    }
    
    return min(flips1, flips2);
}

int main() {
    cout << "=== Sliding Window Technique ===" << endl;
    
    cout << "\n1. Maximum Sum Subarray (Fixed Window)" << endl;
    vector<int> arr1 = {2, 1, 5, 1, 3, 2};
    int k = 3;
    cout << "Array: ";
    for (int x : arr1) cout << x << " ";
    cout << "\nWindow size: " << k << endl;
    cout << "Maximum sum: " << maxSumFixedWindow(arr1, k) << endl;
    
    cout << "\n2. Longest Unique Substring" << endl;
    string s1 = "abcabcbb";
    cout << "String: " << s1 << endl;
    cout << "Length: " << longestUniqueSubstring(s1) << endl;
    
    cout << "\n3. Minimum Window Substring" << endl;
    string s2 = "ADOBECODEBANC";
    string t = "ABC";
    cout << "String: " << s2 << endl;
    cout << "Target: " << t << endl;
    cout << "Minimum window: " << minWindowSubstring(s2, t) << endl;
    
    cout << "\n4. Maximum of Sliding Window" << endl;
    vector<int> arr2 = {1, 3, -1, -3, 5, 3, 6, 7};
    k = 3;
    cout << "Array: ";
    for (int x : arr2) cout << x << " ";
    cout << "\nWindow size: " << k << endl;
    vector<int> maxValues = maxSlidingWindow(arr2, k);
    cout << "Maximums: ";
    for (int x : maxValues) cout << x << " ";
    cout << endl;
    
    cout << "\n5. Count Subarrays with Sum K" << endl;
    vector<int> arr3 = {1, 1, 1};
    int targetSum = 2;
    cout << "Array: ";
    for (int x : arr3) cout << x << " ";
    cout << "\nTarget sum: " << targetSum << endl;
    cout << "Count: " << countSubarraysWithSum(arr3, targetSum) << endl;
    
    cout << "\n6. Longest Subarray with Sum <= K" << endl;
    vector<int> arr4 = {1, 2, 3, 4, 5};
    int maxSum = 8;
    cout << "Array: ";
    for (int x : arr4) cout << x << " ";
    cout << "\nMax sum: " << maxSum << endl;
    cout << "Longest length: " << longestSubarrayWithSum(arr4, maxSum) << endl;
    
    cout << "\n7. Fruits into Baskets" << endl;
    vector<int> fruits = {1, 2, 1};
    cout << "Fruits: ";
    for (int x : fruits) cout << x << " ";
    cout << "\nMax fruits: " << maxFruits(fruits) << endl;
    
    cout << "\n8. Subarrays with Product < K" << endl;
    vector<int> arr5 = {10, 5, 2, 6};
    int k2 = 100;
    cout << "Array: ";
    for (int x : arr5) cout << x << " ";
    cout << "\nK: " << k2 << endl;
    cout << "Count: " << numSubarraysWithProductLessThanK(arr5, k2) << endl;
    
    return 0;
}

/*
Time Complexity: O(n) for most problems
Space Complexity: O(k) where k is window size or unique elements

Sliding Window Types:
1. Fixed Size: Window size is constant
2. Variable Size: Window expands/contracts based on condition

When to Use:
- Contiguous subarrays/substrings
- Finding max/min in subarrays
- Substring problems
- Running calculations

Common Patterns:
1. Fixed Window: Max/min sum of k elements
2. Variable Window: Longest/shortest substring with condition
3. With HashMap: Character frequency problems
4. Two Pointers + Window: Expand right, contract left

Key Insights:
- Avoid recalculating for overlapping elements
- Use deque for window maximum/minimum
- HashMap for frequency tracking
- Expand window (right++) when condition not met
- Contract window (left++) when condition violated

Applications:
- Time series analysis
- Network packet analysis
- Stock price analysis
- String matching
- Data stream processing
*/
