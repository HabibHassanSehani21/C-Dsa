// Dijkstra's Algorithm - Shortest Path in Weighted Graph
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

typedef pair<int, int> pii; // pair<distance, vertex>

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
        adjList[v].push_back({u, weight}); // For undirected graph
    }
    
    void addDirectedEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
    }
    
    // Dijkstra's algorithm using priority queue (min-heap)
    vector<int> dijkstra(int source) {
        vector<int> dist(vertices, INT_MAX);
        vector<bool> visited(vertices, false);
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        
        dist[source] = 0;
        pq.push({0, source});
        
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            
            if (visited[u]) continue;
            visited[u] = true;
            
            for (auto& edge : adjList[u]) {
                int v = edge.first;
                int weight = edge.second;
                
                if (!visited[v] && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }
        
        return dist;
    }
    
    // Dijkstra with path reconstruction
    pair<vector<int>, vector<int>> dijkstraWithPath(int source) {
        vector<int> dist(vertices, INT_MAX);
        vector<int> parent(vertices, -1);
        vector<bool> visited(vertices, false);
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        
        dist[source] = 0;
        pq.push({0, source});
        
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            
            if (visited[u]) continue;
            visited[u] = true;
            
            for (auto& edge : adjList[u]) {
                int v = edge.first;
                int weight = edge.second;
                
                if (!visited[v] && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
        
        return {dist, parent};
    }
    
    // Get shortest path from source to destination
    vector<int> getPath(int source, int dest) {
        auto [dist, parent] = dijkstraWithPath(source);
        
        if (dist[dest] == INT_MAX) {
            return {}; // No path exists
        }
        
        vector<int> path;
        int current = dest;
        
        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }
        
        reverse(path.begin(), path.end());
        return path;
    }
    
    void display() {
        cout << "Graph adjacency list:" << endl;
        for (int i = 0; i < vertices; i++) {
            cout << i << ": ";
            for (auto& edge : adjList[i]) {
                cout << "(" << edge.first << ", " << edge.second << ") ";
            }
            cout << endl;
        }
    }
};

int main() {
    cout << "=== Dijkstra's Algorithm ===" << endl;
    
    Graph g(6);
    
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 2);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 8);
    g.addEdge(2, 4, 10);
    g.addEdge(3, 4, 2);
    g.addEdge(3, 5, 6);
    g.addEdge(4, 5, 3);
    
    g.display();
    
    int source = 0;
    cout << "\nShortest distances from vertex " << source << ":" << endl;
    
    vector<int> distances = g.dijkstra(source);
    
    for (int i = 0; i < distances.size(); i++) {
        cout << "Vertex " << i << ": ";
        if (distances[i] == INT_MAX) {
            cout << "INF" << endl;
        } else {
            cout << distances[i] << endl;
        }
    }
    
    cout << "\n=== Shortest Path Reconstruction ===" << endl;
    
    for (int dest = 1; dest < 6; dest++) {
        vector<int> path = g.getPath(source, dest);
        
        cout << "Path from " << source << " to " << dest << ": ";
        if (path.empty()) {
            cout << "No path exists";
        } else {
            for (int i = 0; i < path.size(); i++) {
                cout << path[i];
                if (i < path.size() - 1) cout << " -> ";
            }
            cout << " (Distance: " << distances[dest] << ")";
        }
        cout << endl;
    }
    
    cout << "\n=== Another Example ===" << endl;
    
    Graph g2(5);
    g2.addEdge(0, 1, 10);
    g2.addEdge(0, 4, 5);
    g2.addEdge(1, 2, 1);
    g2.addEdge(1, 4, 2);
    g2.addEdge(2, 3, 4);
    g2.addEdge(3, 0, 7);
    g2.addEdge(3, 2, 6);
    g2.addEdge(4, 1, 3);
    g2.addEdge(4, 2, 9);
    g2.addEdge(4, 3, 2);
    
    source = 0;
    distances = g2.dijkstra(source);
    
    cout << "Shortest distances from vertex " << source << ":" << endl;
    for (int i = 0; i < distances.size(); i++) {
        cout << "Vertex " << i << ": " << distances[i] << endl;
    }
    
    return 0;
}

/*
Time Complexity: O((V + E) log V) using priority queue
- V: number of vertices
- E: number of edges

Space Complexity: O(V + E)

Algorithm:
1. Initialize distances to infinity, except source (0)
2. Use min-heap to extract vertex with minimum distance
3. Update distances of neighbors if shorter path found
4. Repeat until all vertices processed

Properties:
- Works only with non-negative edge weights
- Greedy algorithm
- Finds shortest path from source to all vertices
- Can reconstruct the actual path

Applications:
- GPS navigation systems
- Network routing protocols
- Social network analysis
- Game pathfinding
- Flight routing systems

Limitations:
- Doesn't work with negative edge weights
- Use Bellman-Ford for negative weights
*/
