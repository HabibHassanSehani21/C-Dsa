// Kruskal's Algorithm - Minimum Spanning Tree using Union-Find
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int src, dest, weight;
    
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
    
    // For sorting edges by weight
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Union-Find (Disjoint Set Union) for cycle detection
class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;
    
public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX == rootY) {
            return false; // Already in same set (would create cycle)
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
        
        return true;
    }
};

class Graph {
private:
    int vertices;
    vector<Edge> edges;
    
public:
    Graph(int v) : vertices(v) {}
    
    void addEdge(int u, int v, int weight) {
        edges.push_back(Edge(u, v, weight));
    }
    
    // Kruskal's algorithm to find MST
    pair<vector<Edge>, int> kruskalMST() {
        // Sort edges by weight
        sort(edges.begin(), edges.end());
        
        UnionFind uf(vertices);
        vector<Edge> mst;
        int totalWeight = 0;
        
        for (const Edge& edge : edges) {
            // If including this edge doesn't create a cycle
            if (uf.unite(edge.src, edge.dest)) {
                mst.push_back(edge);
                totalWeight += edge.weight;
                
                // MST should have V-1 edges
                if (mst.size() == vertices - 1) {
                    break;
                }
            }
        }
        
        return {mst, totalWeight};
    }
    
    void display() {
        cout << "Graph edges:" << endl;
        for (const Edge& edge : edges) {
            cout << edge.src << " - " << edge.dest 
                 << " (weight: " << edge.weight << ")" << endl;
        }
    }
    
    void displayMST(const vector<Edge>& mst, int totalWeight) {
        cout << "Minimum Spanning Tree edges:" << endl;
        for (const Edge& edge : mst) {
            cout << edge.src << " - " << edge.dest 
                 << " (weight: " << edge.weight << ")" << endl;
        }
        cout << "Total MST weight: " << totalWeight << endl;
    }
};

int main() {
    cout << "=== Kruskal's Algorithm - Example 1 ===" << endl;
    
    Graph g1(4);
    g1.addEdge(0, 1, 10);
    g1.addEdge(0, 2, 6);
    g1.addEdge(0, 3, 5);
    g1.addEdge(1, 3, 15);
    g1.addEdge(2, 3, 4);
    
    g1.display();
    
    auto [mst1, weight1] = g1.kruskalMST();
    
    cout << endl;
    g1.displayMST(mst1, weight1);
    
    cout << "\n=== Kruskal's Algorithm - Example 2 ===" << endl;
    
    Graph g2(6);
    g2.addEdge(0, 1, 4);
    g2.addEdge(0, 2, 4);
    g2.addEdge(1, 2, 2);
    g2.addEdge(1, 3, 5);
    g2.addEdge(2, 3, 8);
    g2.addEdge(2, 4, 10);
    g2.addEdge(3, 4, 2);
    g2.addEdge(3, 5, 6);
    g2.addEdge(4, 5, 3);
    
    g2.display();
    
    auto [mst2, weight2] = g2.kruskalMST();
    
    cout << endl;
    g2.displayMST(mst2, weight2);
    
    cout << "\n=== Kruskal's Algorithm - Example 3 (Dense Graph) ===" << endl;
    
    Graph g3(5);
    g3.addEdge(0, 1, 2);
    g3.addEdge(0, 3, 6);
    g3.addEdge(1, 2, 3);
    g3.addEdge(1, 3, 8);
    g3.addEdge(1, 4, 5);
    g3.addEdge(2, 4, 7);
    g3.addEdge(3, 4, 9);
    
    g3.display();
    
    auto [mst3, weight3] = g3.kruskalMST();
    
    cout << endl;
    g3.displayMST(mst3, weight3);
    
    return 0;
}

/*
Time Complexity: O(E log E) or O(E log V)
- Sorting edges: O(E log E)
- Union-Find operations: O(E α(V)) ≈ O(E)
- Total: O(E log E)

Space Complexity: O(V + E)

Algorithm:
1. Sort all edges by weight in ascending order
2. Initialize Union-Find for cycle detection
3. For each edge in sorted order:
   - If including edge doesn't create cycle, add to MST
   - Use Union-Find to detect cycles
4. Continue until MST has V-1 edges

Properties:
- Greedy algorithm
- Edge-based approach
- Uses Union-Find for cycle detection
- Always finds optimal MST

Minimum Spanning Tree (MST):
- Connects all vertices
- No cycles
- Minimum total edge weight
- Has exactly V-1 edges

When to use:
- Sparse graphs (fewer edges)
- Need to process edges in sorted order
- Edge-based problems

Advantages:
- Simple to implement
- Good for sparse graphs
- Natural edge-based approach
- Easy to understand

Disadvantages:
- Requires sorting edges O(E log E)
- Not efficient for dense graphs
- Additional space for sorted edges

Comparison with Prim's:
- Kruskal: Better for sparse graphs
- Prim: Better for dense graphs
- Both give same MST weight

Applications:
- Network design (minimum cable length)
- Clustering algorithms
- Approximation algorithms
- Image segmentation
- Circuit design
*/
