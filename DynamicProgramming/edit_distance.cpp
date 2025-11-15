// Edit Distance (Levenshtein Distance) - Dynamic Programming
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Basic Edit Distance
int editDistance(const string& s1, const string& s2) {
    int m = s1.length();
    int n = s2.length();
    
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    
    // Initialize base cases
    for (int i = 0; i <= m; i++) {
        dp[i][0] = i; // Delete all characters from s1
    }
    
    for (int j = 0; j <= n; j++) {
        dp[0][j] = j; // Insert all characters of s2
    }
    
    // Fill the DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1]; // No operation needed
            } else {
                dp[i][j] = 1 + min({
                    dp[i-1][j],      // Delete
                    dp[i][j-1],      // Insert
                    dp[i-1][j-1]     // Replace
                });
            }
        }
    }
    
    return dp[m][n];
}

// Edit Distance with operation tracking
pair<int, vector<string>> editDistanceWithOperations(const string& s1, const string& s2) {
    int m = s1.length();
    int n = s2.length();
    
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    
    for (int i = 0; i <= m; i++) {
        dp[i][0] = i;
    }
    
    for (int j = 0; j <= n; j++) {
        dp[0][j] = j;
    }
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            } else {
                dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
            }
        }
    }
    
    // Backtrack to find operations
    vector<string> operations;
    int i = m, j = n;
    
    while (i > 0 || j > 0) {
        if (i == 0) {
            operations.push_back("Insert '" + string(1, s2[j-1]) + "' at position " + to_string(i));
            j--;
        } else if (j == 0) {
            operations.push_back("Delete '" + string(1, s1[i-1]) + "' at position " + to_string(i-1));
            i--;
        } else if (s1[i-1] == s2[j-1]) {
            i--;
            j--;
        } else {
            int minOp = min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
            
            if (minOp == dp[i-1][j-1]) {
                operations.push_back("Replace '" + string(1, s1[i-1]) + "' with '" + 
                                   string(1, s2[j-1]) + "' at position " + to_string(i-1));
                i--;
                j--;
            } else if (minOp == dp[i-1][j]) {
                operations.push_back("Delete '" + string(1, s1[i-1]) + "' at position " + to_string(i-1));
                i--;
            } else {
                operations.push_back("Insert '" + string(1, s2[j-1]) + "' at position " + to_string(i));
                j--;
            }
        }
    }
    
    reverse(operations.begin(), operations.end());
    
    return {dp[m][n], operations};
}

// Space-optimized Edit Distance
int editDistanceOptimized(const string& s1, const string& s2) {
    int m = s1.length();
    int n = s2.length();
    
    vector<int> prev(n + 1);
    vector<int> curr(n + 1);
    
    for (int j = 0; j <= n; j++) {
        prev[j] = j;
    }
    
    for (int i = 1; i <= m; i++) {
        curr[0] = i;
        
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1]) {
                curr[j] = prev[j-1];
            } else {
                curr[j] = 1 + min({prev[j], curr[j-1], prev[j-1]});
            }
        }
        
        prev = curr;
    }
    
    return prev[n];
}

// Edit Distance with custom costs
int editDistanceCustom(const string& s1, const string& s2, 
                       int insertCost, int deleteCost, int replaceCost) {
    int m = s1.length();
    int n = s2.length();
    
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    
    for (int i = 0; i <= m; i++) {
        dp[i][0] = i * deleteCost;
    }
    
    for (int j = 0; j <= n; j++) {
        dp[0][j] = j * insertCost;
    }
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1];
            } else {
                dp[i][j] = min({
                    dp[i-1][j] + deleteCost,
                    dp[i][j-1] + insertCost,
                    dp[i-1][j-1] + replaceCost
                });
            }
        }
    }
    
    return dp[m][n];
}

// One Edit Distance (check if exactly one edit away)
bool isOneEditDistance(const string& s1, const string& s2) {
    int m = s1.length();
    int n = s2.length();
    
    if (abs(m - n) > 1) return false;
    
    int i = 0, j = 0;
    int diffCount = 0;
    
    while (i < m && j < n) {
        if (s1[i] != s2[j]) {
            diffCount++;
            if (diffCount > 1) return false;
            
            if (m > n) {
                i++;
            } else if (n > m) {
                j++;
            } else {
                i++;
                j++;
            }
        } else {
            i++;
            j++;
        }
    }
    
    if (i < m || j < n) diffCount++;
    
    return diffCount == 1;
}

int main() {
    cout << "=== Edit Distance (Levenshtein Distance) ===" << endl;
    
    string s1 = "saturday";
    string s2 = "sunday";
    
    cout << "String 1: " << s1 << endl;
    cout << "String 2: " << s2 << endl;
    
    int distance = editDistance(s1, s2);
    cout << "Edit Distance: " << distance << endl;
    
    cout << "\n=== Edit Distance with Operations ===" << endl;
    
    auto [dist, operations] = editDistanceWithOperations(s1, s2);
    
    cout << "Edit Distance: " << dist << endl;
    cout << "Operations:" << endl;
    for (const string& op : operations) {
        cout << "  " << op << endl;
    }
    
    cout << "\n=== Another Example ===" << endl;
    
    string s3 = "intention";
    string s4 = "execution";
    
    cout << "String 1: " << s3 << endl;
    cout << "String 2: " << s4 << endl;
    
    auto [dist2, ops2] = editDistanceWithOperations(s3, s4);
    
    cout << "Edit Distance: " << dist2 << endl;
    cout << "Operations:" << endl;
    for (const string& op : ops2) {
        cout << "  " << op << endl;
    }
    
    cout << "\n=== Space-Optimized Edit Distance ===" << endl;
    
    int distOpt = editDistanceOptimized(s1, s2);
    cout << "Edit Distance (optimized): " << distOpt << endl;
    
    cout << "\n=== Edit Distance with Custom Costs ===" << endl;
    
    int customDist = editDistanceCustom(s1, s2, 1, 2, 3);
    cout << "Edit Distance (insert=1, delete=2, replace=3): " << customDist << endl;
    
    cout << "\n=== One Edit Distance ===" << endl;
    
    string s5 = "abc";
    string s6 = "abcd";
    
    cout << "String 1: " << s5 << endl;
    cout << "String 2: " << s6 << endl;
    cout << "Is one edit away: " << (isOneEditDistance(s5, s6) ? "Yes" : "No") << endl;
    
    string s7 = "abc";
    string s8 = "adc";
    
    cout << "\nString 1: " << s7 << endl;
    cout << "String 2: " << s8 << endl;
    cout << "Is one edit away: " << (isOneEditDistance(s7, s8) ? "Yes" : "No") << endl;
    
    return 0;
}

/*
Time Complexity: O(m * n)
Space Complexity: 
- Basic: O(m * n)
- Optimized: O(min(m, n))

Operations:
1. Insert: Add a character
2. Delete: Remove a character
3. Replace: Change a character

Applications:
- Spell checkers
- DNA sequence alignment
- Plagiarism detection
- Natural language processing
- Auto-correction
- Fuzzy string matching

Problem Variants:
1. Edit Distance (all operations cost 1)
2. Weighted Edit Distance (custom costs)
3. One Edit Distance
4. Edit Distance with backtrace
5. Hamming Distance (only substitution)

Key Insights:
- If chars match: dp[i][j] = dp[i-1][j-1]
- If chars differ: 1 + min(insert, delete, replace)
- Base cases: empty string conversions
- Can optimize space to O(n)

Related Problems:
- Longest Common Subsequence
- Minimum ASCII Delete Sum
- Delete Operation for Two Strings
- One Edit Distance
- String Similarity
*/
