// KMP (Knuth-Morris-Pratt) Algorithm - Pattern Matching
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Compute LPS (Longest Proper Prefix which is also Suffix) array
vector<int> computeLPS(const string& pattern) {
    int m = pattern.length();
    vector<int> lps(m, 0);
    int len = 0;  // Length of previous longest prefix suffix
    int i = 1;
    
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    
    return lps;
}

// KMP search algorithm
vector<int> KMPSearch(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();
    
    vector<int> occurrences;
    
    if (m == 0 || m > n) return occurrences;
    
    // Compute LPS array
    vector<int> lps = computeLPS(pattern);
    
    int i = 0;  // Index for text
    int j = 0;  // Index for pattern
    
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        
        if (j == m) {
            occurrences.push_back(i - j);
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    
    return occurrences;
}

// Count occurrences of pattern in text
int countOccurrences(const string& text, const string& pattern) {
    vector<int> occurrences = KMPSearch(text, pattern);
    return occurrences.size();
}

// Check if pattern exists in text
bool contains(const string& text, const string& pattern) {
    vector<int> occurrences = KMPSearch(text, pattern);
    return !occurrences.empty();
}

// Find first occurrence
int findFirst(const string& text, const string& pattern) {
    vector<int> occurrences = KMPSearch(text, pattern);
    return occurrences.empty() ? -1 : occurrences[0];
}

// Replace all occurrences of pattern with replacement
string replaceAll(const string& text, const string& pattern, const string& replacement) {
    vector<int> occurrences = KMPSearch(text, pattern);
    
    if (occurrences.empty()) return text;
    
    string result = "";
    int lastPos = 0;
    
    for (int pos : occurrences) {
        result += text.substr(lastPos, pos - lastPos);
        result += replacement;
        lastPos = pos + pattern.length();
    }
    
    result += text.substr(lastPos);
    
    return result;
}

// Check if string is a rotation of another
bool isRotation(const string& s1, const string& s2) {
    if (s1.length() != s2.length()) return false;
    
    string temp = s1 + s1;
    return contains(temp, s2);
}

// Find shortest period of repeating pattern
int shortestPeriod(const string& s) {
    vector<int> lps = computeLPS(s);
    int n = s.length();
    int len = lps[n - 1];
    
    // If LPS is not zero and string length is divisible by (n - LPS)
    if (len > 0 && n % (n - len) == 0) {
        return n - len;
    }
    
    return n;
}

int main() {
    cout << "=== KMP Pattern Matching Algorithm ===" << endl;
    
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";
    
    cout << "Text: " << text << endl;
    cout << "Pattern: " << pattern << endl;
    
    vector<int> occurrences = KMPSearch(text, pattern);
    
    cout << "\nOccurrences found at positions: ";
    if (occurrences.empty()) {
        cout << "None";
    } else {
        for (int pos : occurrences) {
            cout << pos << " ";
        }
    }
    cout << endl;
    
    cout << "Total occurrences: " << countOccurrences(text, pattern) << endl;
    
    cout << "\n=== LPS Array ===" << endl;
    
    cout << "Pattern: " << pattern << endl;
    vector<int> lps = computeLPS(pattern);
    
    cout << "LPS array: ";
    for (int val : lps) {
        cout << val << " ";
    }
    cout << endl;
    
    cout << "\n=== Another Example ===" << endl;
    
    string text2 = "AABAACAADAABAABA";
    string pattern2 = "AABA";
    
    cout << "Text: " << text2 << endl;
    cout << "Pattern: " << pattern2 << endl;
    
    occurrences = KMPSearch(text2, pattern2);
    
    cout << "Occurrences at: ";
    for (int pos : occurrences) {
        cout << pos << " ";
    }
    cout << endl;
    
    cout << "\n=== Pattern Replacement ===" << endl;
    
    string text3 = "the cat in the hat sat on the mat";
    string pattern3 = "the";
    string replacement = "a";
    
    cout << "Original: " << text3 << endl;
    cout << "Replace '" << pattern3 << "' with '" << replacement << "'" << endl;
    
    string result = replaceAll(text3, pattern3, replacement);
    cout << "Result: " << result << endl;
    
    cout << "\n=== String Rotation Check ===" << endl;
    
    string s1 = "waterbottle";
    string s2 = "erbottlewat";
    
    cout << "String 1: " << s1 << endl;
    cout << "String 2: " << s2 << endl;
    cout << "Is rotation: " << (isRotation(s1, s2) ? "Yes" : "No") << endl;
    
    string s3 = "abcde";
    string s4 = "cdeab";
    
    cout << "\nString 1: " << s3 << endl;
    cout << "String 2: " << s4 << endl;
    cout << "Is rotation: " << (isRotation(s3, s4) ? "Yes" : "No") << endl;
    
    cout << "\n=== Shortest Period ===" << endl;
    
    string repeating = "abcabcabc";
    cout << "String: " << repeating << endl;
    cout << "Shortest period: " << shortestPeriod(repeating) << endl;
    
    return 0;
}

/*
Time Complexity: O(n + m)
- Preprocessing (LPS): O(m)
- Searching: O(n)
- Total: O(n + m)

Space Complexity: O(m) for LPS array

Algorithm Steps:
1. Compute LPS array for pattern
2. Use LPS to skip unnecessary comparisons
3. When mismatch occurs, use LPS to determine next position

LPS Array:
- LPS[i] = length of longest proper prefix which is also suffix
- Helps in skipping already matched characters
- Key to KMP's efficiency

Advantages:
- Never re-examines text characters
- Linear time complexity
- Efficient for repeated searches
- No backtracking in text

Applications:
- Text editors (find/replace)
- DNA sequence matching
- Network packet inspection
- Plagiarism detection
- Data compression

Comparison with Naive:
- Naive: O(n * m)
- KMP: O(n + m)
- KMP is faster for large texts

Related Algorithms:
- Boyer-Moore (faster in practice)
- Rabin-Karp (rolling hash)
- Aho-Corasick (multiple patterns)
- Z-algorithm (similar efficiency)
*/
