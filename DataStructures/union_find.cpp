// Union-Find (Disjoint Set Union) Data Structure
#include <iostream>
#include <vector>
using namespace std;

class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;
    int numSets;
    
public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        numSets = n;
        
        // Initialize each element as its own parent
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    // Find operation with path compression
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }
    
    // Union operation with union by rank
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX == rootY) {
            return false; // Already in same set
        }
        
        // Union by rank
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        
        numSets--;
        return true;
    }
    
    // Check if two elements are in the same set
    bool isConnected(int x, int y) {
        return find(x) == find(y);
    }
    
    // Get number of disjoint sets
    int getNumSets() {
        return numSets;
    }
    
    // Get size of set containing x
    int getSetSize(int x) {
        int root = find(x);
        int size = 0;
        
        for (int i = 0; i < parent.size(); i++) {
            if (find(i) == root) {
                size++;
            }
        }
        
        return size;
    }
    
    // Display all sets
    void displaySets() {
        cout << "Current sets:" << endl;
        vector<vector<int>> sets(parent.size());
        
        for (int i = 0; i < parent.size(); i++) {
            sets[find(i)].push_back(i);
        }
        
        int setNum = 1;
        for (int i = 0; i < sets.size(); i++) {
            if (!sets[i].empty()) {
                cout << "Set " << setNum++ << ": ";
                for (int elem : sets[i]) {
                    cout << elem << " ";
                }
                cout << endl;
            }
        }
    }
};

// Example: Detect cycle in undirected graph using Union-Find
class GraphCycleDetector {
private:
    int vertices;
    vector<pair<int, int>> edges;
    
public:
    GraphCycleDetector(int v) : vertices(v) {}
    
    void addEdge(int u, int v) {
        edges.push_back({u, v});
    }
    
    bool hasCycle() {
        UnionFind uf(vertices);
        
        for (auto& edge : edges) {
            int u = edge.first;
            int v = edge.second;
            
            // If both vertices are already in same set, adding this edge creates a cycle
            if (uf.isConnected(u, v)) {
                return true;
            }
            
            uf.unite(u, v);
        }
        
        return false;
    }
};

// Example: Count connected components in graph
int countConnectedComponents(int n, vector<pair<int, int>>& edges) {
    UnionFind uf(n);
    
    for (auto& edge : edges) {
        uf.unite(edge.first, edge.second);
    }
    
    return uf.getNumSets();
}

int main() {
    cout << "=== Union-Find Operations ===" << endl;
    
    UnionFind uf(10);
    
    cout << "Initial number of sets: " << uf.getNumSets() << endl;
    
    // Perform union operations
    uf.unite(0, 1);
    uf.unite(2, 3);
    uf.unite(4, 5);
    uf.unite(6, 7);
    uf.unite(1, 3); // This will merge sets {0,1} and {2,3}
    uf.unite(5, 7); // This will merge sets {4,5} and {6,7}
    
    cout << "Number of sets after unions: " << uf.getNumSets() << endl;
    
    uf.displaySets();
    
    // Check connectivity
    cout << "\n=== Connectivity Checks ===" << endl;
    cout << "Are 0 and 3 connected? " << (uf.isConnected(0, 3) ? "Yes" : "No") << endl;
    cout << "Are 0 and 5 connected? " << (uf.isConnected(0, 5) ? "Yes" : "No") << endl;
    cout << "Are 4 and 7 connected? " << (uf.isConnected(4, 7) ? "Yes" : "No") << endl;
    cout << "Are 8 and 9 connected? " << (uf.isConnected(8, 9) ? "Yes" : "No") << endl;
    
    // Get set sizes
    cout << "\n=== Set Sizes ===" << endl;
    cout << "Size of set containing 0: " << uf.getSetSize(0) << endl;
    cout << "Size of set containing 5: " << uf.getSetSize(5) << endl;
    cout << "Size of set containing 8: " << uf.getSetSize(8) << endl;
    
    // Example: Cycle detection in graph
    cout << "\n=== Cycle Detection in Graph ===" << endl;
    GraphCycleDetector graph1(4);
    graph1.addEdge(0, 1);
    graph1.addEdge(1, 2);
    graph1.addEdge(2, 3);
    cout << "Graph 1 has cycle: " << (graph1.hasCycle() ? "Yes" : "No") << endl;
    
    GraphCycleDetector graph2(4);
    graph2.addEdge(0, 1);
    graph2.addEdge(1, 2);
    graph2.addEdge(2, 3);
    graph2.addEdge(3, 0); // This creates a cycle
    cout << "Graph 2 has cycle: " << (graph2.hasCycle() ? "Yes" : "No") << endl;
    
    // Example: Count connected components
    cout << "\n=== Connected Components ===" << endl;
    vector<pair<int, int>> edges = {{0, 1}, {1, 2}, {3, 4}};
    int components = countConnectedComponents(5, edges);
    cout << "Number of connected components: " << components << endl;
    
    return 0;
}

/*
Time Complexity:
- Find: O(α(n)) ≈ O(1) amortized (with path compression)
- Union: O(α(n)) ≈ O(1) amortized (with union by rank)
where α is the inverse Ackermann function (grows extremely slowly)

Space Complexity: O(n)

Applications:
- Cycle detection in undirected graphs
- Kruskal's algorithm for MST
- Connected components in graphs
- Network connectivity problems
*/
