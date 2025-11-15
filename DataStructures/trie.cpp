// Trie (Prefix Tree) - Efficient string storage and retrieval
#include <iostream>
#include <unordered_map>
using namespace std;

// Trie Node structure
struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;
    
    TrieNode() : isEndOfWord(false) {}
};

class Trie {
private:
    TrieNode* root;
    
    // Helper function to delete trie
    void deleteTrie(TrieNode* node) {
        if (node == nullptr) return;
        
        for (auto& pair : node->children) {
            deleteTrie(pair.second);
        }
        
        delete node;
    }
    
    // Helper function for autocomplete
    void findAllWordsHelper(TrieNode* node, string prefix, vector<string>& results) {
        if (node == nullptr) return;
        
        if (node->isEndOfWord) {
            results.push_back(prefix);
        }
        
        for (auto& pair : node->children) {
            findAllWordsHelper(pair.second, prefix + pair.first, results);
        }
    }
    
public:
    Trie() {
        root = new TrieNode();
    }
    
    // Insert a word into the trie
    void insert(string word) {
        TrieNode* current = root;
        
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
        
        current->isEndOfWord = true;
    }
    
    // Search for a word in the trie
    bool search(string word) {
        TrieNode* current = root;
        
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end()) {
                return false;
            }
            current = current->children[ch];
        }
        
        return current->isEndOfWord;
    }
    
    // Check if any word starts with given prefix
    bool startsWith(string prefix) {
        TrieNode* current = root;
        
        for (char ch : prefix) {
            if (current->children.find(ch) == current->children.end()) {
                return false;
            }
            current = current->children[ch];
        }
        
        return true;
    }
    
    // Delete a word from the trie
    bool deleteWord(string word) {
        return deleteWordHelper(root, word, 0);
    }
    
    bool deleteWordHelper(TrieNode* node, string& word, int index) {
        if (node == nullptr) return false;
        
        // Base case: reached end of word
        if (index == word.length()) {
            if (!node->isEndOfWord) return false;
            
            node->isEndOfWord = false;
            
            // If node has no children, it can be deleted
            return node->children.empty();
        }
        
        char ch = word[index];
        if (node->children.find(ch) == node->children.end()) {
            return false;
        }
        
        TrieNode* childNode = node->children[ch];
        bool shouldDeleteChild = deleteWordHelper(childNode, word, index + 1);
        
        if (shouldDeleteChild) {
            delete childNode;
            node->children.erase(ch);
            
            // Return true if node has no children and is not end of another word
            return node->children.empty() && !node->isEndOfWord;
        }
        
        return false;
    }
    
    // Get all words with given prefix (autocomplete)
    vector<string> autocomplete(string prefix) {
        vector<string> results;
        TrieNode* current = root;
        
        // Navigate to the prefix
        for (char ch : prefix) {
            if (current->children.find(ch) == current->children.end()) {
                return results; // No words with this prefix
            }
            current = current->children[ch];
        }
        
        // Find all words starting from this node
        findAllWordsHelper(current, prefix, results);
        
        return results;
    }
    
    // Count total words in trie
    int countWords() {
        return countWordsHelper(root);
    }
    
    int countWordsHelper(TrieNode* node) {
        if (node == nullptr) return 0;
        
        int count = node->isEndOfWord ? 1 : 0;
        
        for (auto& pair : node->children) {
            count += countWordsHelper(pair.second);
        }
        
        return count;
    }
    
    // Check if trie is empty
    bool isEmpty() {
        return root->children.empty();
    }
    
    ~Trie() {
        deleteTrie(root);
    }
};

int main() {
    cout << "=== Trie Operations ===" << endl;
    
    Trie trie;
    
    // Insert words
    trie.insert("apple");
    trie.insert("app");
    trie.insert("application");
    trie.insert("apply");
    trie.insert("banana");
    trie.insert("band");
    trie.insert("bandana");
    
    cout << "Total words in trie: " << trie.countWords() << endl;
    
    // Search for words
    cout << "\n=== Search Operations ===" << endl;
    cout << "Search 'apple': " << (trie.search("apple") ? "Found" : "Not Found") << endl;
    cout << "Search 'app': " << (trie.search("app") ? "Found" : "Not Found") << endl;
    cout << "Search 'appl': " << (trie.search("appl") ? "Found" : "Not Found") << endl;
    cout << "Search 'orange': " << (trie.search("orange") ? "Found" : "Not Found") << endl;
    
    // Check prefix
    cout << "\n=== Prefix Operations ===" << endl;
    cout << "Starts with 'app': " << (trie.startsWith("app") ? "Yes" : "No") << endl;
    cout << "Starts with 'ban': " << (trie.startsWith("ban") ? "Yes" : "No") << endl;
    cout << "Starts with 'ora': " << (trie.startsWith("ora") ? "Yes" : "No") << endl;
    
    // Autocomplete
    cout << "\n=== Autocomplete ===" << endl;
    vector<string> suggestions = trie.autocomplete("app");
    cout << "Words starting with 'app': ";
    for (string word : suggestions) {
        cout << word << " ";
    }
    cout << endl;
    
    suggestions = trie.autocomplete("ban");
    cout << "Words starting with 'ban': ";
    for (string word : suggestions) {
        cout << word << " ";
    }
    cout << endl;
    
    // Delete word
    cout << "\n=== Delete Operations ===" << endl;
    cout << "Deleting 'app'..." << endl;
    trie.deleteWord("app");
    cout << "Search 'app' after deletion: " << (trie.search("app") ? "Found" : "Not Found") << endl;
    cout << "Search 'apple' after deletion: " << (trie.search("apple") ? "Found" : "Not Found") << endl;
    
    cout << "Total words after deletion: " << trie.countWords() << endl;
    
    return 0;
}

/*
Time Complexity:
- Insert: O(m) where m is length of word
- Search: O(m)
- StartsWith: O(m)
- Delete: O(m)
- Autocomplete: O(n) where n is total characters in all matching words

Space Complexity: O(ALPHABET_SIZE * m * n)
where m is average length and n is number of words
*/
