// Tree Diameter - Longest path between any two nodes
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Diameter of binary tree (number of edges)
class DiameterCalculator {
private:
    int diameter;
    
    int height(TreeNode* root) {
        if (root == nullptr) return 0;
        
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        
        // Update diameter if path through current node is longer
        diameter = max(diameter, leftHeight + rightHeight);
        
        return 1 + max(leftHeight, rightHeight);
    }
    
public:
    int calculateDiameter(TreeNode* root) {
        diameter = 0;
        height(root);
        return diameter;
    }
};

// Diameter with path
class DiameterWithPath {
private:
    int diameter;
    vector<int> longestPath;
    
    pair<int, vector<int>> heightWithPath(TreeNode* root) {
        if (root == nullptr) return {0, {}};
        
        auto [leftHeight, leftPath] = heightWithPath(root->left);
        auto [rightHeight, rightPath] = heightWithPath(root->right);
        
        // Check if path through current node is longest
        if (leftHeight + rightHeight > diameter) {
            diameter = leftHeight + rightHeight;
            
            // Construct the path
            longestPath.clear();
            for (auto it = leftPath.rbegin(); it != leftPath.rend(); ++it) {
                longestPath.push_back(*it);
            }
            longestPath.push_back(root->val);
            for (int node : rightPath) {
                longestPath.push_back(node);
            }
        }
        
        // Return height and path from current node
        if (leftHeight > rightHeight) {
            vector<int> path = leftPath;
            path.push_back(root->val);
            return {1 + leftHeight, path};
        } else {
            vector<int> path = rightPath;
            path.push_back(root->val);
            return {1 + rightHeight, path};
        }
    }
    
public:
    pair<int, vector<int>> calculateDiameterWithPath(TreeNode* root) {
        diameter = 0;
        longestPath.clear();
        heightWithPath(root);
        return {diameter, longestPath};
    }
};

// Diameter of general tree (represented as adjacency list)
class TreeDiameter {
private:
    vector<vector<int>> adj;
    int n;
    
    // BFS to find farthest node and its distance
    pair<int, int> bfs(int start) {
        vector<int> dist(n, -1);
        queue<int> q;
        
        dist[start] = 0;
        q.push(start);
        
        int farthest = start;
        int maxDist = 0;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                    
                    if (dist[v] > maxDist) {
                        maxDist = dist[v];
                        farthest = v;
                    }
                }
            }
        }
        
        return {farthest, maxDist};
    }
    
public:
    TreeDiameter(int nodes) : n(nodes) {
        adj.resize(n);
    }
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // Two BFS approach to find diameter
    int findDiameter() {
        // First BFS from any node to find one end of diameter
        auto [farthest, dist1] = bfs(0);
        
        // Second BFS from farthest node to find diameter
        auto [otherEnd, diameter] = bfs(farthest);
        
        return diameter;
    }
    
    // Find diameter with path
    pair<int, vector<int>> findDiameterWithPath() {
        auto [farthest, dist1] = bfs(0);
        
        // BFS with parent tracking
        vector<int> parent(n, -1);
        vector<int> dist(n, -1);
        queue<int> q;
        
        dist[farthest] = 0;
        q.push(farthest);
        
        int otherEnd = farthest;
        int maxDist = 0;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    parent[v] = u;
                    q.push(v);
                    
                    if (dist[v] > maxDist) {
                        maxDist = dist[v];
                        otherEnd = v;
                    }
                }
            }
        }
        
        // Reconstruct path
        vector<int> path;
        int current = otherEnd;
        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }
        
        return {maxDist, path};
    }
};

// Helper function to create sample tree
TreeNode* createSampleTree() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    
    return root;
}

void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    cout << "=== Binary Tree Diameter ===" << endl;
    
    TreeNode* root = createSampleTree();
    
    cout << "Tree structure:" << endl;
    cout << "     1" << endl;
    cout << "    / \\" << endl;
    cout << "   2   3" << endl;
    cout << "  / \\" << endl;
    cout << " 4   5" << endl;
    
    DiameterCalculator dc;
    int diameter = dc.calculateDiameter(root);
    cout << "\nDiameter (number of edges): " << diameter << endl;
    
    cout << "\n=== Binary Tree Diameter with Path ===" << endl;
    
    DiameterWithPath dwp;
    auto [diam, path] = dwp.calculateDiameterWithPath(root);
    
    cout << "Diameter: " << diam << endl;
    cout << "Path: ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << endl;
    
    cout << "\n=== General Tree Diameter ===" << endl;
    
    TreeDiameter td(6);
    td.addEdge(0, 1);
    td.addEdge(0, 2);
    td.addEdge(1, 3);
    td.addEdge(1, 4);
    td.addEdge(2, 5);
    
    cout << "Tree edges: 0-1, 0-2, 1-3, 1-4, 2-5" << endl;
    
    int treeDiameter = td.findDiameter();
    cout << "Diameter: " << treeDiameter << endl;
    
    auto [treeDiam, treePath] = td.findDiameterWithPath();
    cout << "Path: ";
    for (int i = 0; i < treePath.size(); i++) {
        cout << treePath[i];
        if (i < treePath.size() - 1) cout << " -> ";
    }
    cout << endl;
    
    deleteTree(root);
    
    return 0;
}

/*
Time Complexity:
- Binary tree: O(n)
- General tree (two BFS): O(n)

Space Complexity: O(h) for recursion stack in binary tree

Approaches:
1. Binary Tree: DFS calculating height at each node
2. General Tree: Two BFS approach
   - First BFS finds one end of diameter
   - Second BFS from that end finds diameter

Key Insights:
- Diameter passes through some node as root
- At each node, diameter = left_height + right_height
- For general tree, farthest node from any node is one end of diameter
- Two BFS gives correct diameter

Applications:
- Network analysis
- Finding bottlenecks
- Tree visualization
- Hierarchical clustering
- Biological phylogeny

Related Problems:
- Tree height/depth
- Longest path in tree
- Tree center
- Tree radius
*/
