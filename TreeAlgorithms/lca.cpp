// Lowest Common Ancestor (LCA) in Binary Tree
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// LCA using recursion
TreeNode* findLCA(TreeNode* root, int n1, int n2) {
    if (root == nullptr) return nullptr;
    
    if (root->val == n1 || root->val == n2) {
        return root;
    }
    
    TreeNode* leftLCA = findLCA(root->left, n1, n2);
    TreeNode* rightLCA = findLCA(root->right, n1, n2);
    
    if (leftLCA && rightLCA) {
        return root;
    }
    
    return (leftLCA != nullptr) ? leftLCA : rightLCA;
}

// LCA in Binary Search Tree (optimized)
TreeNode* findLCABST(TreeNode* root, int n1, int n2) {
    if (root == nullptr) return nullptr;
    
    if (root->val > n1 && root->val > n2) {
        return findLCABST(root->left, n1, n2);
    }
    
    if (root->val < n1 && root->val < n2) {
        return findLCABST(root->right, n1, n2);
    }
    
    return root;
}

// LCA using parent pointers
struct TreeNodeWithParent {
    int val;
    TreeNodeWithParent* left;
    TreeNodeWithParent* right;
    TreeNodeWithParent* parent;
    
    TreeNodeWithParent(int x) : val(x), left(nullptr), right(nullptr), parent(nullptr) {}
};

int getDepth(TreeNodeWithParent* node) {
    int depth = 0;
    while (node != nullptr) {
        depth++;
        node = node->parent;
    }
    return depth;
}

TreeNodeWithParent* findLCAWithParent(TreeNodeWithParent* n1, TreeNodeWithParent* n2) {
    int d1 = getDepth(n1);
    int d2 = getDepth(n2);
    
    // Bring both nodes to same level
    while (d1 > d2) {
        n1 = n1->parent;
        d1--;
    }
    
    while (d2 > d1) {
        n2 = n2->parent;
        d2--;
    }
    
    // Move both up until they meet
    while (n1 != n2) {
        n1 = n1->parent;
        n2 = n2->parent;
    }
    
    return n1;
}

// LCA using Binary Lifting (for multiple queries)
class BinaryLifting {
private:
    vector<vector<int>> parent;
    vector<int> depth;
    int maxLog;
    
    void dfs(int node, int par, int d, const vector<vector<int>>& tree) {
        parent[node][0] = par;
        depth[node] = d;
        
        for (int i = 1; i < maxLog; i++) {
            if (parent[node][i-1] != -1) {
                parent[node][i] = parent[parent[node][i-1]][i-1];
            }
        }
        
        for (int child : tree[node]) {
            if (child != par) {
                dfs(child, node, d + 1, tree);
            }
        }
    }
    
public:
    BinaryLifting(int n, const vector<vector<int>>& tree, int root = 0) {
        maxLog = ceil(log2(n)) + 1;
        parent.assign(n, vector<int>(maxLog, -1));
        depth.assign(n, 0);
        
        dfs(root, -1, 0, tree);
    }
    
    int findLCA(int u, int v) {
        if (depth[u] < depth[v]) {
            swap(u, v);
        }
        
        int diff = depth[u] - depth[v];
        
        // Bring u to same level as v
        for (int i = 0; i < maxLog; i++) {
            if ((diff >> i) & 1) {
                u = parent[u][i];
            }
        }
        
        if (u == v) return u;
        
        // Binary search for LCA
        for (int i = maxLog - 1; i >= 0; i--) {
            if (parent[u][i] != parent[v][i]) {
                u = parent[u][i];
                v = parent[v][i];
            }
        }
        
        return parent[u][0];
    }
    
    int getDistance(int u, int v) {
        int lca = findLCA(u, v);
        return depth[u] + depth[v] - 2 * depth[lca];
    }
};

// Helper function to create a sample tree
TreeNode* createSampleTree() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);
    
    return root;
}

// Helper function to delete tree
void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    cout << "=== Lowest Common Ancestor (LCA) ===" << endl;
    
    TreeNode* root = createSampleTree();
    
    cout << "Tree structure:" << endl;
    cout << "       1" << endl;
    cout << "      / \\" << endl;
    cout << "     2   3" << endl;
    cout << "    / \\ / \\" << endl;
    cout << "   4  5 6  7" << endl;
    
    int n1 = 4, n2 = 5;
    TreeNode* lca = findLCA(root, n1, n2);
    cout << "\nLCA of " << n1 << " and " << n2 << ": " << lca->val << endl;
    
    n1 = 4; n2 = 6;
    lca = findLCA(root, n1, n2);
    cout << "LCA of " << n1 << " and " << n2 << ": " << lca->val << endl;
    
    n1 = 3; n2 = 4;
    lca = findLCA(root, n1, n2);
    cout << "LCA of " << n1 << " and " << n2 << ": " << lca->val << endl;
    
    cout << "\n=== LCA in Binary Search Tree ===" << endl;
    
    TreeNode* bstRoot = new TreeNode(20);
    bstRoot->left = new TreeNode(8);
    bstRoot->right = new TreeNode(22);
    bstRoot->left->left = new TreeNode(4);
    bstRoot->left->right = new TreeNode(12);
    bstRoot->left->right->left = new TreeNode(10);
    bstRoot->left->right->right = new TreeNode(14);
    
    cout << "BST structure:" << endl;
    cout << "       20" << endl;
    cout << "      /  \\" << endl;
    cout << "     8   22" << endl;
    cout << "    / \\" << endl;
    cout << "   4  12" << endl;
    cout << "      / \\" << endl;
    cout << "    10  14" << endl;
    
    n1 = 10; n2 = 14;
    lca = findLCABST(bstRoot, n1, n2);
    cout << "\nLCA of " << n1 << " and " << n2 << ": " << lca->val << endl;
    
    n1 = 8; n2 = 14;
    lca = findLCABST(bstRoot, n1, n2);
    cout << "LCA of " << n1 << " and " << n2 << ": " << lca->val << endl;
    
    cout << "\n=== Binary Lifting for Multiple Queries ===" << endl;
    
    vector<vector<int>> tree(8);
    tree[1] = {2, 3};
    tree[2] = {1, 4, 5};
    tree[3] = {1, 6, 7};
    tree[4] = {2};
    tree[5] = {2};
    tree[6] = {3};
    tree[7] = {3};
    
    BinaryLifting bl(8, tree, 1);
    
    cout << "LCA of 4 and 5: " << bl.findLCA(4, 5) << endl;
    cout << "LCA of 4 and 6: " << bl.findLCA(4, 6) << endl;
    cout << "LCA of 5 and 7: " << bl.findLCA(5, 7) << endl;
    
    cout << "\n=== Distance Between Nodes ===" << endl;
    cout << "Distance between 4 and 5: " << bl.getDistance(4, 5) << endl;
    cout << "Distance between 4 and 7: " << bl.getDistance(4, 7) << endl;
    
    deleteTree(root);
    deleteTree(bstRoot);
    
    return 0;
}

/*
Time Complexity:
- Basic recursion: O(n) per query
- Binary Lifting: O(n log n) preprocessing, O(log n) per query
- With parent pointers: O(h) where h is height

Space Complexity:
- Basic: O(h) recursion stack
- Binary Lifting: O(n log n)

Approaches:
1. Recursive: Simple but O(n) per query
2. Binary Lifting: Fast queries but requires preprocessing
3. Tarjan's Offline: All queries together
4. Euler Tour + RMQ: O(n) preprocessing, O(1) per query

Applications:
- Finding distance between nodes
- Path queries in trees
- Hierarchical data structures
- Phylogenetic trees
- Version control systems

Key Insights:
- LCA is the deepest node that is ancestor of both nodes
- In BST, can use value comparison
- Binary lifting uses 2^i ancestors for fast lookup
- Can be extended to find kth ancestor
*/
