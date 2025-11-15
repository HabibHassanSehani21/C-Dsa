// Prim's Algorithm - Minimum Spanning Tree using Priority Queue
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef pair<int, int> pii; // pair<weight, vertex>

struct Edge {
    int src, dest, weight;
    
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
};

class Graph {
private:
    int vertices;
    vector<vector<pii>> adjList; // pair<neighbor, weight>
    
public:
    Graph(int v) : vertices(v) {
        adjList.resize(v);
    }
    
    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight});
    }
    
    // Prim's algorithm using priority queue
    pair<vector<Edge>, int> primMST(int start = 0) {
        vector<bool> inMST(vertices, false);
        vector<int> parent(vertices, -1);
        vector<int> key(vertices, INT_MAX);
        
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        
        key[start] = 0;
        pq.push({0, start});
        
        vector<Edge> mst;
        int totalWeight = 0;
        
        while (!pq.empty()) {
            int u = pq.top().second;
            int weight = pq.top().first;
            pq.pop();
            
            if (inMST[u]) continue;
            
            inMST[u] = true;
            
            // Add edge to MST (except for start vertex)
            if (parent[u] != -1) {
                mst.push_back(Edge(parent[u], u, weight));
                totalWeight += weight;
            }
            
            // Update keys of adjacent vertices
            for (auto& [v, w] : adjList[u]) {
                if (!inMST[v] && w < key[v]) {
                    key[v] = w;
                    parent[v] = u;
                    pq.push({w, v});
                }
            }
        }
        
        return {mst, totalWeight};
    }
    
    // Prim's algorithm using simple array (better for dense graphs)
    pair<vector<Edge>, int> primMSTSimple(int start = 0) {
        vector<bool> inMST(vertices, false);
        vector<int> parent(vertices, -1);
        vector<int> key(vertices, INT_MAX);
        
        key[start] = 0;
        
        vector<Edge> mst;
        int totalWeight = 0;
        
        for (int count = 0; count < vertices; count++) {
            // Find vertex with minimum key value
            int minKey = INT_MAX;
            int u = -1;
            
            for (int v = 0; v < vertices; v++) {
                if (!inMST[v] && key[v] < minKey) {
                    minKey = key[v];
                    u = v;
                }
            }
            
            if (u == -1) break; // Graph is disconnected
            
            inMST[u] = true;
            
            // Add edge to MST (except for start vertex)
            if (parent[u] != -1) {
                mst.push_back(Edge(parent[u], u, key[u]));
                totalWeight += key[u];
            }
            
            // Update keys of adjacent vertices
            for (auto& [v, weight] : adjList[u]) {
                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                }
            }
        }
        
        return {mst, totalWeight};
    }
    
    void display() {
        cout << "Graph adjacency list:" << endl;
        for (int i = 0; i < vertices; i++) {
            cout << i << ": ";
            for (auto& [v, w] : adjList[i]) {
                cout << "(" << v << ", " << w << ") ";
            }
            cout << endl;
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
    cout << "=== Prim's Algorithm - Example 1 ===" << endl;
    
    Graph g1(4);
    g1.addEdge(0, 1, 10);
    g1.addEdge(0, 2, 6);
    g1.addEdge(0, 3, 5);
    g1.addEdge(1, 3, 15);
    g1.addEdge(2, 3, 4);
    
    g1.display();
    
    auto [mst1, weight1] = g1.primMST(0);
    
    cout << endl;
    g1.displayMST(mst1, weight1);
    
    cout << "\n=== Prim's Algorithm - Example 2 ===" << endl;
    
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
    
    auto [mst2, weight2] = g2.primMST(0);
    
    cout << endl;
    g2.displayMST(mst2, weight2);
    
    cout << "\n=== Comparing Priority Queue vs Simple Array ===" << endl;
    
    Graph g3(5);
    g3.addEdge(0, 1, 2);
    g3.addEdge(0, 3, 6);
    g3.addEdge(1, 2, 3);
    g3.addEdge(1, 3, 8);
    g3.addEdge(1, 4, 5);
    g3.addEdge(2, 4, 7);
    g3.addEdge(3, 4, 9);
    
    auto [mst3a, weight3a] = g3.primMST(0);
    auto [mst3b, weight3b] = g3.primMSTSimple(0);
    
    cout << "Priority Queue Implementation:" << endl;
    g3.displayMST(mst3a, weight3a);
    
    cout << "\nSimple Array Implementation:" << endl;
    g3.displayMST(mst3b, weight3b);
    
    return 0;
}

/*
Time Complexity:
- Priority Queue: O((V + E) log V)
- Simple Array: O(V²)

Space Complexity: O(V + E)

Algorithm:
1. Start with arbitrary vertex
2. Maintain set of vertices in MST
3. At each step, add minimum weight edge connecting MST to non-MST vertex
4. Repeat until all vertices are in MST

Properties:
- Greedy algorithm
- Vertex-based approach
- Grows tree one vertex at a time
- Always finds optimal MST

When to use:
- Dense graphs (more edges)
- Need to grow tree from specific vertex
- Vertex-based problems

Advantages:
- Better for dense graphs
- Natural vertex-based approach
- Can start from any vertex
- Easy to implement with priority queue

Disadvantages:
- Requires priority queue for efficiency
- More complex than Kruskal for beginners
- Need adjacency list representation

Comparison with Kruskal:
- Prim: Better for dense graphs, O((V+E)logV)
- Kruskal: Better for sparse graphs, O(E log E)
- Both give same MST weight

Optimization:
- Priority Queue: Better for sparse graphs
- Simple Array: Better for dense graphs (V² < E log V)
- Fibonacci Heap: O(E + V log V) theoretical best

Applications:
- Network design (telecommunication, water pipes)
- Clustering algorithms
- Approximation algorithms for TSP
- Image segmentation
- Circuit design
- Laying cables or pipelines
*/
