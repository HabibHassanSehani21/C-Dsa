// Tree Serialization and Deserialization
#include <iostream>
#include <sstream>
#include <queue>
#include <string>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Serialization and Deserialization using Preorder
class PreorderCodec {
public:
    // Serialize tree to string
    string serialize(TreeNode* root) {
        if (root == nullptr) {
            return "null,";
        }
        
        string result = to_string(root->val) + ",";
        result += serialize(root->left);
        result += serialize(root->right);
        
        return result;
    }
    
    // Deserialize string to tree
    TreeNode* deserialize(string data) {
        queue<string> nodes;
        stringstream ss(data);
        string item;
        
        while (getline(ss, item, ',')) {
            if (!item.empty()) {
                nodes.push(item);
            }
        }
        
        return deserializeHelper(nodes);
    }
    
private:
    TreeNode* deserializeHelper(queue<string>& nodes) {
        if (nodes.empty()) return nullptr;
        
        string val = nodes.front();
        nodes.pop();
        
        if (val == "null") {
            return nullptr;
        }
        
        TreeNode* root = new TreeNode(stoi(val));
        root->left = deserializeHelper(nodes);
        root->right = deserializeHelper(nodes);
        
        return root;
    }
};

// Serialization using Level Order (BFS)
class LevelOrderCodec {
public:
    string serialize(TreeNode* root) {
        if (root == nullptr) return "";
        
        string result = "";
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            
            if (node == nullptr) {
                result += "null,";
            } else {
                result += to_string(node->val) + ",";
                q.push(node->left);
                q.push(node->right);
            }
        }
        
        return result;
    }
    
    TreeNode* deserialize(string data) {
        if (data.empty()) return nullptr;
        
        stringstream ss(data);
        string item;
        getline(ss, item, ',');
        
        TreeNode* root = new TreeNode(stoi(item));
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            
            // Left child
            if (getline(ss, item, ',')) {
                if (item != "null") {
                    node->left = new TreeNode(stoi(item));
                    q.push(node->left);
                }
            }
            
            // Right child
            if (getline(ss, item, ',')) {
                if (item != "null") {
                    node->right = new TreeNode(stoi(item));
                    q.push(node->right);
                }
            }
        }
        
        return root;
    }
};

// Serialization using Parenthesis representation
class ParenthesisCodec {
public:
    string serialize(TreeNode* root) {
        if (root == nullptr) return "";
        
        string result = to_string(root->val);
        
        if (root->left != nullptr || root->right != nullptr) {
            result += "(" + serialize(root->left) + ")";
            
            if (root->right != nullptr) {
                result += "(" + serialize(root->right) + ")";
            }
        }
        
        return result;
    }
    
    TreeNode* deserialize(string data) {
        if (data.empty()) return nullptr;
        
        int index = 0;
        return deserializeHelper(data, index);
    }
    
private:
    TreeNode* deserializeHelper(const string& data, int& index) {
        if (index >= data.length()) return nullptr;
        
        // Parse number
        int num = 0;
        bool negative = false;
        
        if (data[index] == '-') {
            negative = true;
            index++;
        }
        
        while (index < data.length() && isdigit(data[index])) {
            num = num * 10 + (data[index] - '0');
            index++;
        }
        
        if (negative) num = -num;
        
        TreeNode* root = new TreeNode(num);
        
        // Left child
        if (index < data.length() && data[index] == '(') {
            index++; // skip '('
            root->left = deserializeHelper(data, index);
            index++; // skip ')'
        }
        
        // Right child
        if (index < data.length() && data[index] == '(') {
            index++; // skip '('
            root->right = deserializeHelper(data, index);
            index++; // skip ')'
        }
        
        return root;
    }
};

// Helper functions
TreeNode* createSampleTree() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);
    
    return root;
}

void printInorder(TreeNode* root) {
    if (root == nullptr) return;
    
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    cout << "=== Tree Serialization and Deserialization ===" << endl;
    
    TreeNode* originalTree = createSampleTree();
    
    cout << "Original tree (Inorder): ";
    printInorder(originalTree);
    cout << endl;
    
    cout << "\n=== Preorder Serialization ===" << endl;
    
    PreorderCodec preorderCodec;
    string serialized = preorderCodec.serialize(originalTree);
    cout << "Serialized: " << serialized << endl;
    
    TreeNode* deserializedTree = preorderCodec.deserialize(serialized);
    cout << "Deserialized tree (Inorder): ";
    printInorder(deserializedTree);
    cout << endl;
    
    cout << "\n=== Level Order Serialization ===" << endl;
    
    LevelOrderCodec levelOrderCodec;
    string serialized2 = levelOrderCodec.serialize(originalTree);
    cout << "Serialized: " << serialized2 << endl;
    
    TreeNode* deserializedTree2 = levelOrderCodec.deserialize(serialized2);
    cout << "Deserialized tree (Inorder): ";
    printInorder(deserializedTree2);
    cout << endl;
    
    cout << "\n=== Parenthesis Serialization ===" << endl;
    
    ParenthesisCodec parenthesisCodec;
    string serialized3 = parenthesisCodec.serialize(originalTree);
    cout << "Serialized: " << serialized3 << endl;
    
    TreeNode* deserializedTree3 = parenthesisCodec.deserialize(serialized3);
    cout << "Deserialized tree (Inorder): ";
    printInorder(deserializedTree3);
    cout << endl;
    
    // Clean up
    deleteTree(originalTree);
    deleteTree(deserializedTree);
    deleteTree(deserializedTree2);
    deleteTree(deserializedTree3);
    
    return 0;
}

/*
Time Complexity: O(n) for both serialization and deserialization
Space Complexity: O(n) for storing the serialized string

Serialization Methods:
1. Preorder: Root, Left, Right with null markers
2. Level Order (BFS): Breadth-first with null markers
3. Parenthesis: Compact representation with brackets
4. Inorder + Preorder/Postorder: Can reconstruct unique tree

Applications:
- Saving tree to file/database
- Network transmission
- Caching tree structures
- Debugging and testing
- Tree comparison

Key Insights:
- Need to encode null nodes to preserve structure
- Preorder/Postorder needs null markers
- Level order naturally represents tree structure
- Can use delimiters to separate values
- Parenthesis representation is compact

Related Problems:
- Serialize N-ary tree
- Serialize BST (can optimize by not storing nulls)
- Construct tree from traversals
- Tree isomorphism
*/
