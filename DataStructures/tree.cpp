// Binary Tree and Binary Search Tree in C++
#include <iostream>
#include <queue>
#include <climits>
using namespace std;

// Node structure for Binary Tree
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    TreeNode* root;
    
    // Helper function for insertion
    TreeNode* insertHelper(TreeNode* node, int val) {
        if (node == nullptr) {
            return new TreeNode(val);
        }
        
        if (val < node->data) {
            node->left = insertHelper(node->left, val);
        } else if (val > node->data) {
            node->right = insertHelper(node->right, val);
        }
        
        return node;
    }
    
    // Helper function for searching
    bool searchHelper(TreeNode* node, int val) {
        if (node == nullptr) return false;
        
        if (node->data == val) return true;
        
        if (val < node->data) {
            return searchHelper(node->left, val);
        } else {
            return searchHelper(node->right, val);
        }
    }
    
    // Helper function to find minimum value node
    TreeNode* findMin(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    
    // Helper function for deletion
    TreeNode* deleteHelper(TreeNode* node, int val) {
        if (node == nullptr) return nullptr;
        
        if (val < node->data) {
            node->left = deleteHelper(node->left, val);
        } else if (val > node->data) {
            node->right = deleteHelper(node->right, val);
        } else {
            // Node to be deleted found
            
            // Case 1: No child or one child
            if (node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }
            
            // Case 2: Two children
            TreeNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteHelper(node->right, temp->data);
        }
        
        return node;
    }
    
    // Inorder Traversal (Left -> Root -> Right)
    void inorderHelper(TreeNode* node) {
        if (node == nullptr) return;
        
        inorderHelper(node->left);
        cout << node->data << " ";
        inorderHelper(node->right);
    }
    
    // Preorder Traversal (Root -> Left -> Right)
    void preorderHelper(TreeNode* node) {
        if (node == nullptr) return;
        
        cout << node->data << " ";
        preorderHelper(node->left);
        preorderHelper(node->right);
    }
    
    // Postorder Traversal (Left -> Right -> Root)
    void postorderHelper(TreeNode* node) {
        if (node == nullptr) return;
        
        postorderHelper(node->left);
        postorderHelper(node->right);
        cout << node->data << " ";
    }
    
    // Helper function to calculate height
    int heightHelper(TreeNode* node) {
        if (node == nullptr) return -1;
        
        int leftHeight = heightHelper(node->left);
        int rightHeight = heightHelper(node->right);
        
        return 1 + max(leftHeight, rightHeight);
    }
    
    // Helper function to delete tree
    void deleteTree(TreeNode* node) {
        if (node == nullptr) return;
        
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
    
public:
    BinarySearchTree() : root(nullptr) {}
    
    void insert(int val) {
        root = insertHelper(root, val);
    }
    
    bool search(int val) {
        return searchHelper(root, val);
    }
    
    void remove(int val) {
        root = deleteHelper(root, val);
    }
    
    void inorder() {
        cout << "Inorder: ";
        inorderHelper(root);
        cout << endl;
    }
    
    void preorder() {
        cout << "Preorder: ";
        preorderHelper(root);
        cout << endl;
    }
    
    void postorder() {
        cout << "Postorder: ";
        postorderHelper(root);
        cout << endl;
    }
    
    // Level Order Traversal (BFS)
    void levelOrder() {
        if (root == nullptr) return;
        
        cout << "Level Order: ";
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();
            
            cout << current->data << " ";
            
            if (current->left != nullptr) q.push(current->left);
            if (current->right != nullptr) q.push(current->right);
        }
        cout << endl;
    }
    
    int height() {
        return heightHelper(root);
    }
    
    // Check if tree is valid BST
    bool isValidBST() {
        return isValidBSTHelper(root, LONG_MIN, LONG_MAX);
    }
    
    bool isValidBSTHelper(TreeNode* node, long minVal, long maxVal) {
        if (node == nullptr) return true;
        
        if (node->data <= minVal || node->data >= maxVal) return false;
        
        return isValidBSTHelper(node->left, minVal, node->data) &&
               isValidBSTHelper(node->right, node->data, maxVal);
    }
    
    ~BinarySearchTree() {
        deleteTree(root);
    }
};

int main() {
    cout << "=== Binary Search Tree Operations ===" << endl;
    
    BinarySearchTree bst;
    
    // Insert elements
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);
    
    // Traversals
    bst.inorder();
    bst.preorder();
    bst.postorder();
    bst.levelOrder();
    
    // Height
    cout << "Height of tree: " << bst.height() << endl;
    
    // Search
    cout << "Search 40: " << (bst.search(40) ? "Found" : "Not Found") << endl;
    cout << "Search 100: " << (bst.search(100) ? "Found" : "Not Found") << endl;
    
    // Validate BST
    cout << "Is valid BST: " << (bst.isValidBST() ? "Yes" : "No") << endl;
    
    // Delete
    cout << "\nDeleting 20..." << endl;
    bst.remove(20);
    bst.inorder();
    
    cout << "Deleting 30..." << endl;
    bst.remove(30);
    bst.inorder();
    
    cout << "Deleting 50..." << endl;
    bst.remove(50);
    bst.inorder();
    
    return 0;
}

/*
Time Complexity:
- Insert: O(log n) average, O(n) worst
- Delete: O(log n) average, O(n) worst
- Search: O(log n) average, O(n) worst
- Traversal: O(n)

Space Complexity: O(n)
Recursion stack space: O(h) where h is height
*/
