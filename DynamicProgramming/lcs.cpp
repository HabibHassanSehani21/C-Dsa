// Longest Common Subsequence (LCS) - Dynamic Programming
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Basic LCS - Return length
int lcsLength(const string& s1, const string& s2) {
    int m = s1.length();
    int n = s2.length();
    
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    
    return dp[m][n];
}

// LCS with subsequence reconstruction
pair<int, string> lcsWithString(const string& s1, const string& s2) {
    int m = s1.length();
    int n = s2.length();
    
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    // Fill DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    
    // Reconstruct LCS
    string lcs = "";
    int i = m, j = n;
    
    while (i > 0 && j > 0) {
        if (s1[i-1] == s2[j-1]) {
            lcs = s1[i-1] + lcs;
            i--;
            j--;
        } else if (dp[i-1][j] > dp[i][j-1]) {
            i--;
        } else {
            j--;
        }
    }
    
    return {dp[m][n], lcs};
}

// Space-optimized LCS (only length)
int lcsOptimized(const string& s1, const string& s2) {
    int m = s1.length();
    int n = s2.length();
    
    vector<int> prev(n + 1, 0);
    vector<int> curr(n + 1, 0);
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1]) {
                curr[j] = prev[j-1] + 1;
            } else {
                curr[j] = max(prev[j], curr[j-1]);
            }
        }
        prev = curr;
    }
    
    return prev[n];
}

// Longest Common Substring (continuous)
pair<int, string> longestCommonSubstring(const string& s1, const string& s2) {
    int m = s1.length();
    int n = s2.length();
    
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    int maxLength = 0;
    int endIndex = 0;
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endIndex = i;
                }
            }
        }
    }
    
    string substring = s1.substr(endIndex - maxLength, maxLength);
    return {maxLength, substring};
}

// Print all LCS (there can be multiple)
void printAllLCS(const string& s1, const string& s2, int i, int j, 
                 const vector<vector<int>>& dp, string current, 
                 vector<string>& allLCS) {
    if (i == 0 || j == 0) {
        reverse(current.begin(), current.end());
        allLCS.push_back(current);
        return;
    }
    
    if (s1[i-1] == s2[j-1]) {
        printAllLCS(s1, s2, i-1, j-1, dp, current + s1[i-1], allLCS);
    } else {
        if (dp[i-1][j] >= dp[i][j-1]) {
            printAllLCS(s1, s2, i-1, j, dp, current, allLCS);
        }
        if (dp[i][j-1] >= dp[i-1][j]) {
            printAllLCS(s1, s2, i, j-1, dp, current, allLCS);
        }
    }
}

vector<string> getAllLCS(const string& s1, const string& s2) {
    int m = s1.length();
    int n = s2.length();
    
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    
    vector<string> allLCS;
    printAllLCS(s1, s2, m, n, dp, "", allLCS);
    
    // Remove duplicates
    sort(allLCS.begin(), allLCS.end());
    allLCS.erase(unique(allLCS.begin(), allLCS.end()), allLCS.end());
    
    return allLCS;
}

// Shortest Common Supersequence length
int scsLength(const string& s1, const string& s2) {
    int lcs = lcsLength(s1, s2);
    return s1.length() + s2.length() - lcs;
}

int main() {
    cout << "=== Longest Common Subsequence (LCS) ===" << endl;
    
    string s1 = "AGGTAB";
    string s2 = "GXTXAYB";
    
    cout << "String 1: " << s1 << endl;
    cout << "String 2: " << s2 << endl;
    
    int length = lcsLength(s1, s2);
    cout << "\nLCS Length: " << length << endl;
    
    auto [len, lcs] = lcsWithString(s1, s2);
    cout << "LCS: " << lcs << endl;
    
    cout << "\n=== Another Example ===" << endl;
    
    string s3 = "ABCDGH";
    string s4 = "AEDFHR";
    
    cout << "String 1: " << s3 << endl;
    cout << "String 2: " << s4 << endl;
    
    auto [len2, lcs2] = lcsWithString(s3, s4);
    cout << "LCS Length: " << len2 << endl;
    cout << "LCS: " << lcs2 << endl;
    
    cout << "\n=== Longest Common Substring ===" << endl;
    
    string s5 = "OldSite:GeeksforGeeks.org";
    string s6 = "NewSite:GeeksQuiz.com";
    
    cout << "String 1: " << s5 << endl;
    cout << "String 2: " << s6 << endl;
    
    auto [subLen, substring] = longestCommonSubstring(s5, s6);
    cout << "Longest Common Substring Length: " << subLen << endl;
    cout << "Substring: " << substring << endl;
    
    cout << "\n=== All Possible LCS ===" << endl;
    
    string s7 = "AGTGATG";
    string s8 = "GTTAG";
    
    cout << "String 1: " << s7 << endl;
    cout << "String 2: " << s8 << endl;
    
    vector<string> allLCS = getAllLCS(s7, s8);
    cout << "All LCS (" << allLCS.size() << " total):" << endl;
    for (const string& seq : allLCS) {
        cout << "  " << seq << endl;
    }
    
    cout << "\n=== Shortest Common Supersequence ===" << endl;
    
    cout << "String 1: " << s1 << endl;
    cout << "String 2: " << s2 << endl;
    
    int scs = scsLength(s1, s2);
    cout << "Shortest Common Supersequence Length: " << scs << endl;
    
    cout << "\n=== Space-Optimized LCS ===" << endl;
    
    int lenOpt = lcsOptimized(s1, s2);
    cout << "LCS Length (optimized): " << lenOpt << endl;
    
    return 0;
}

/*
Time Complexity: O(m * n)
Space Complexity: 
- Basic: O(m * n)
- Optimized: O(min(m, n))

Problem Variants:
1. LCS - Longest Common Subsequence (not continuous)
2. LCS - Longest Common Substring (continuous)
3. SCS - Shortest Common Supersequence
4. Edit Distance (Levenshtein Distance)

Applications:
- DNA sequence alignment
- Diff utilities (version control)
- Plagiarism detection
- File comparison
- Data compression
- Bioinformatics

Related Problems:
- Edit Distance: minimum operations to convert s1 to s2
- Longest Palindromic Subsequence: LCS(s, reverse(s))
- Shortest Common Supersequence: len(s1) + len(s2) - LCS

Key Insights:
- If chars match: dp[i][j] = dp[i-1][j-1] + 1
- If chars don't match: dp[i][j] = max(dp[i-1][j], dp[i][j-1])
- Can optimize space to O(n) by keeping only two rows
- Backtracking reconstructs the actual sequence
*/
