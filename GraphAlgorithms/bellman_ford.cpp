// Bellman-Ford Algorithm - Shortest Path with Negative Weights
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Edge {
    int src, dest, weight;
    
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
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
    
    void addUndirectedEdge(int u, int v, int weight) {
        edges.push_back(Edge(u, v, weight));
        edges.push_back(Edge(v, u, weight));
    }
    
    // Bellman-Ford algorithm
    pair<vector<int>, bool> bellmanFord(int source) {
        vector<int> dist(vertices, INT_MAX);
        dist[source] = 0;
        
        // Relax all edges V-1 times
        for (int i = 0; i < vertices - 1; i++) {
            for (const Edge& edge : edges) {
                if (dist[edge.src] != INT_MAX && 
                    dist[edge.src] + edge.weight < dist[edge.dest]) {
                    dist[edge.dest] = dist[edge.src] + edge.weight;
                }
            }
        }
        
        // Check for negative weight cycles
        for (const Edge& edge : edges) {
            if (dist[edge.src] != INT_MAX && 
                dist[edge.src] + edge.weight < dist[edge.dest]) {
                return {dist, true}; // Negative cycle detected
            }
        }
        
        return {dist, false}; // No negative cycle
    }
    
    // Bellman-Ford with path reconstruction
    pair<vector<int>, vector<int>> bellmanFordWithPath(int source) {
        vector<int> dist(vertices, INT_MAX);
        vector<int> parent(vertices, -1);
        dist[source] = 0;
        
        // Relax all edges V-1 times
        for (int i = 0; i < vertices - 1; i++) {
            for (const Edge& edge : edges) {
                if (dist[edge.src] != INT_MAX && 
                    dist[edge.src] + edge.weight < dist[edge.dest]) {
                    dist[edge.dest] = dist[edge.src] + edge.weight;
                    parent[edge.dest] = edge.src;
                }
            }
        }
        
        return {dist, parent};
    }
    
    // Detect negative cycle and return the cycle
    vector<int> detectNegativeCycle() {
        vector<int> dist(vertices, 0);
        vector<int> parent(vertices, -1);
        int cycleVertex = -1;
        
        // Relax all edges V times
        for (int i = 0; i < vertices; i++) {
            cycleVertex = -1;
            for (const Edge& edge : edges) {
                if (dist[edge.src] + edge.weight < dist[edge.dest]) {
                    dist[edge.dest] = dist[edge.src] + edge.weight;
                    parent[edge.dest] = edge.src;
                    cycleVertex = edge.dest;
                }
            }
        }
        
        if (cycleVertex == -1) {
            return {}; // No negative cycle
        }
        
        // Trace back to find the cycle
        for (int i = 0; i < vertices; i++) {
            cycleVertex = parent[cycleVertex];
        }
        
        vector<int> cycle;
        int current = cycleVertex;
        
        do {
            cycle.push_back(current);
            current = parent[current];
        } while (current != cycleVertex);
        
        cycle.push_back(cycleVertex);
        reverse(cycle.begin(), cycle.end());
        
        return cycle;
    }
    
    void display() {
        cout << "Graph edges:" << endl;
        for (const Edge& edge : edges) {
            cout << edge.src << " -> " << edge.dest 
                 << " (weight: " << edge.weight << ")" << endl;
        }
    }
};

int main() {
    cout << "=== Bellman-Ford Algorithm (No Negative Cycle) ===" << endl;
    
    Graph g1(5);
    g1.addEdge(0, 1, 6);
    g1.addEdge(0, 2, 7);
    g1.addEdge(1, 2, 8);
    g1.addEdge(1, 3, 5);
    g1.addEdge(1, 4, -4);
    g1.addEdge(2, 3, -3);
    g1.addEdge(2, 4, 9);
    g1.addEdge(3, 1, -2);
    g1.addEdge(4, 0, 2);
    g1.addEdge(4, 3, 7);
    
    g1.display();
    
    int source = 0;
    auto [distances, hasNegCycle] = g1.bellmanFord(source);
    
    if (hasNegCycle) {
        cout << "\nNegative weight cycle detected!" << endl;
    } else {
        cout << "\nShortest distances from vertex " << source << ":" << endl;
        for (int i = 0; i < distances.size(); i++) {
            cout << "Vertex " << i << ": ";
            if (distances[i] == INT_MAX) {
                cout << "INF";
            } else {
                cout << distances[i];
            }
            cout << endl;
        }
    }
    
    cout << "\n=== Bellman-Ford with Negative Cycle ===" << endl;
    
    Graph g2(4);
    g2.addEdge(0, 1, 1);
    g2.addEdge(1, 2, -1);
    g2.addEdge(2, 3, -1);
    g2.addEdge(3, 1, -1); // Creates negative cycle: 1 -> 2 -> 3 -> 1
    
    g2.display();
    
    source = 0;
    auto [distances2, hasNegCycle2] = g2.bellmanFord(source);
    
    if (hasNegCycle2) {
        cout << "\nNegative weight cycle detected!" << endl;
        
        vector<int> cycle = g2.detectNegativeCycle();
        if (!cycle.empty()) {
            cout << "Negative cycle: ";
            for (int i = 0; i < cycle.size(); i++) {
                cout << cycle[i];
                if (i < cycle.size() - 1) cout << " -> ";
            }
            cout << endl;
        }
    }
    
    cout << "\n=== Comparing with Dijkstra's Use Case ===" << endl;
    
    Graph g3(5);
    g3.addEdge(0, 1, 4);
    g3.addEdge(0, 2, 2);
    g3.addEdge(1, 2, 1);
    g3.addEdge(1, 3, 5);
    g3.addEdge(2, 3, 8);
    g3.addEdge(2, 4, 10);
    g3.addEdge(3, 4, 2);
    
    source = 0;
    auto [distances3, hasNegCycle3] = g3.bellmanFord(source);
    
    cout << "Shortest distances from vertex " << source << ":" << endl;
    for (int i = 0; i < distances3.size(); i++) {
        cout << "Vertex " << i << ": " << distances3[i] << endl;
    }
    
    return 0;
}

/*
Time Complexity: O(V * E)
- V: number of vertices
- E: number of edges

Space Complexity: O(V)

Algorithm:
1. Initialize distances to infinity, except source (0)
2. Relax all edges V-1 times
3. Check once more for negative cycles

Properties:
- Works with negative edge weights
- Can detect negative weight cycles
- Slower than Dijkstra's algorithm
- Dynamic programming approach

When to use:
- Graph has negative edge weights
- Need to detect negative cycles
- Distributed systems (easier to implement in parallel)

Advantages:
- Handles negative weights
- Detects negative cycles
- Simpler implementation than Dijkstra
- Works well in distributed systems

Disadvantages:
- Slower than Dijkstra (O(VE) vs O((V+E)logV))
- Not suitable for large graphs
- Requires all edges to be relaxed multiple times

Comparison with Dijkstra:
- Dijkstra: Faster but only non-negative weights
- Bellman-Ford: Slower but handles negative weights

Applications:
- Currency arbitrage detection
- Network routing with varying costs
- Distance vector routing protocols
- Detecting arbitrage opportunities in financial markets
*/
