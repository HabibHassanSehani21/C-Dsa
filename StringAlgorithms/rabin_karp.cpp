// Rabin-Karp Algorithm - Pattern Matching using Rolling Hash
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class RabinKarp {
private:
    const int d = 256;      // Number of characters in input alphabet
    const int q = 101;      // A prime number for modulo
    
public:
    // Basic Rabin-Karp search
    vector<int> search(const string& text, const string& pattern) {
        int n = text.length();
        int m = pattern.length();
        vector<int> result;
        
        if (m > n) return result;
        
        int h = 1;
        int patternHash = 0;
        int textHash = 0;
        
        // Calculate h = d^(m-1) % q
        for (int i = 0; i < m - 1; i++) {
            h = (h * d) % q;
        }
        
        // Calculate initial hash values
        for (int i = 0; i < m; i++) {
            patternHash = (d * patternHash + pattern[i]) % q;
            textHash = (d * textHash + text[i]) % q;
        }
        
        // Slide the pattern over text
        for (int i = 0; i <= n - m; i++) {
            // Check if hash values match
            if (patternHash == textHash) {
                // Verify character by character
                bool match = true;
                for (int j = 0; j < m; j++) {
                    if (text[i + j] != pattern[j]) {
                        match = false;
                        break;
                    }
                }
                
                if (match) {
                    result.push_back(i);
                }
            }
            
            // Calculate hash for next window
            if (i < n - m) {
                textHash = (d * (textHash - text[i] * h) + text[i + m]) % q;
                
                // Convert negative to positive
                if (textHash < 0) {
                    textHash = textHash + q;
                }
            }
        }
        
        return result;
    }
    
    // Search for multiple patterns
    vector<pair<string, vector<int>>> searchMultiple(const string& text, 
                                                      const vector<string>& patterns) {
        vector<pair<string, vector<int>>> results;
        
        for (const string& pattern : patterns) {
            vector<int> positions = search(text, pattern);
            results.push_back({pattern, positions});
        }
        
        return results;
    }
    
    // Check if two strings are anagrams using hash
    bool areAnagrams(const string& s1, const string& s2) {
        if (s1.length() != s2.length()) return false;
        
        int hash1 = 0, hash2 = 0;
        
        for (int i = 0; i < s1.length(); i++) {
            hash1 = (hash1 + s1[i]) % q;
            hash2 = (hash2 + s2[i]) % q;
        }
        
        return hash1 == hash2;
    }
};

// Advanced: Find all anagram occurrences of pattern in text
vector<int> findAnagrams(const string& text, const string& pattern) {
    vector<int> result;
    int n = text.length();
    int m = pattern.length();
    
    if (m > n) return result;
    
    // Frequency arrays
    vector<int> patternFreq(256, 0);
    vector<int> windowFreq(256, 0);
    
    // Count frequency of characters in pattern
    for (char c : pattern) {
        patternFreq[c]++;
    }
    
    // First window
    for (int i = 0; i < m; i++) {
        windowFreq[text[i]]++;
    }
    
    // Check first window
    if (patternFreq == windowFreq) {
        result.push_back(0);
    }
    
    // Slide window
    for (int i = m; i < n; i++) {
        windowFreq[text[i]]++;
        windowFreq[text[i - m]]--;
        
        if (patternFreq == windowFreq) {
            result.push_back(i - m + 1);
        }
    }
    
    return result;
}

// Check for duplicate substrings of given length
bool hasDuplicateSubstring(const string& s, int len) {
    if (len > s.length()) return false;
    
    const int d = 256;
    const int q = 1000000007;
    
    int h = 1;
    for (int i = 0; i < len - 1; i++) {
        h = (1LL * h * d) % q;
    }
    
    vector<long long> hashes;
    long long hash = 0;
    
    // Calculate hash for first window
    for (int i = 0; i < len; i++) {
        hash = (1LL * d * hash + s[i]) % q;
    }
    hashes.push_back(hash);
    
    // Slide window
    for (int i = len; i < s.length(); i++) {
        hash = (1LL * d * (hash - 1LL * s[i - len] * h) + s[i]) % q;
        if (hash < 0) hash += q;
        
        // Check if hash already exists
        for (long long h : hashes) {
            if (h == hash) return true;
        }
        hashes.push_back(hash);
    }
    
    return false;
}

int main() {
    cout << "=== Rabin-Karp Pattern Matching ===" << endl;
    
    RabinKarp rk;
    
    string text = "GEEKS FOR GEEKS";
    string pattern = "GEEK";
    
    cout << "Text: " << text << endl;
    cout << "Pattern: " << pattern << endl;
    
    vector<int> positions = rk.search(text, pattern);
    
    cout << "Occurrences at positions: ";
    if (positions.empty()) {
        cout << "None";
    } else {
        for (int pos : positions) {
            cout << pos << " ";
        }
    }
    cout << endl;
    
    cout << "\n=== Multiple Pattern Search ===" << endl;
    
    string text2 = "AABAACAADAABAABA";
    vector<string> patterns = {"AABA", "AA", "BA"};
    
    cout << "Text: " << text2 << endl;
    cout << "Patterns: ";
    for (const string& p : patterns) {
        cout << p << " ";
    }
    cout << endl;
    
    auto results = rk.searchMultiple(text2, patterns);
    
    cout << "\nResults:" << endl;
    for (const auto& [pattern, positions] : results) {
        cout << "Pattern '" << pattern << "' found at: ";
        for (int pos : positions) {
            cout << pos << " ";
        }
        cout << endl;
    }
    
    cout << "\n=== Anagram Search ===" << endl;
    
    string text3 = "cbaebabacd";
    string pattern3 = "abc";
    
    cout << "Text: " << text3 << endl;
    cout << "Pattern: " << pattern3 << endl;
    
    vector<int> anagrams = findAnagrams(text3, pattern3);
    
    cout << "Anagram occurrences at: ";
    for (int pos : anagrams) {
        cout << pos << " ";
    }
    cout << endl;
    
    cout << "\n=== Duplicate Substring Detection ===" << endl;
    
    string s = "abcabcabc";
    int len = 3;
    
    cout << "String: " << s << endl;
    cout << "Length: " << len << endl;
    cout << "Has duplicate substring: " 
         << (hasDuplicateSubstring(s, len) ? "Yes" : "No") << endl;
    
    return 0;
}

/*
Time Complexity:
- Average case: O(n + m)
- Worst case: O(n * m) when many hash collisions
- Expected: O(n + m) with good hash function

Space Complexity: O(1)

Algorithm:
1. Compute hash of pattern
2. Compute hash of first window in text
3. Slide window, update hash using rolling hash formula
4. When hash matches, verify character by character

Rolling Hash:
- Remove leftmost character's contribution
- Add rightmost character's contribution
- hash = (d * (hash - text[i] * h) + text[i + m]) % q

Advantages:
- Simple to implement
- Works well in average case
- Can search multiple patterns simultaneously
- Uses rolling hash for efficiency

Disadvantages:
- Worst case O(n*m) with hash collisions
- Spurious hits require character verification
- Performance depends on hash function quality

Applications:
- Plagiarism detection
- Multiple pattern matching
- Substring search
- DNA sequence analysis
- Network intrusion detection

Comparison:
- Rabin-Karp: O(n+m) average, good for multiple patterns
- KMP: O(n+m) worst case, single pattern
- Boyer-Moore: Best in practice for long patterns

Related Techniques:
- Rolling hash
- Polynomial hash
- Modular arithmetic
- Multiple pattern matching
*/
