// Graph Data Structure - Adjacency List and Adjacency Matrix
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

// Graph using Adjacency List
class Graph {
private:
    int vertices;
    vector<vector<int>> adjList;
    
    void DFSHelper(int vertex, vector<bool>& visited) {
        visited[vertex] = true;
        cout << vertex << " ";
        
        for (int neighbor : adjList[vertex]) {
            if (!visited[neighbor]) {
                DFSHelper(neighbor, visited);
            }
        }
    }
    
public:
    Graph(int v) : vertices(v) {
        adjList.resize(v);
    }
    
    // Add edge for undirected graph
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
    
    // Add directed edge
    void addDirectedEdge(int u, int v) {
        adjList[u].push_back(v);
    }
    
    // Breadth First Search (BFS)
    void BFS(int start) {
        vector<bool> visited(vertices, false);
        queue<int> q;
        
        visited[start] = true;
        q.push(start);
        
        cout << "BFS starting from vertex " << start << ": ";
        
        while (!q.empty()) {
            int vertex = q.front();
            q.pop();
            cout << vertex << " ";
            
            for (int neighbor : adjList[vertex]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }
    
    // Depth First Search (DFS) - Recursive
    void DFS(int start) {
        vector<bool> visited(vertices, false);
        cout << "DFS starting from vertex " << start << ": ";
        DFSHelper(start, visited);
        cout << endl;
    }
    
    // DFS - Iterative
    void DFSIterative(int start) {
        vector<bool> visited(vertices, false);
        stack<int> st;
        
        st.push(start);
        
        cout << "DFS (Iterative) starting from vertex " << start << ": ";
        
        while (!st.empty()) {
            int vertex = st.top();
            st.pop();
            
            if (!visited[vertex]) {
                visited[vertex] = true;
                cout << vertex << " ";
                
                // Push neighbors in reverse order for consistent traversal
                for (auto it = adjList[vertex].rbegin(); it != adjList[vertex].rend(); ++it) {
                    if (!visited[*it]) {
                        st.push(*it);
                    }
                }
            }
        }
        cout << endl;
    }
    
    // Check if graph is connected (for undirected graph)
    bool isConnected() {
        vector<bool> visited(vertices, false);
        
        // Find a vertex with non-zero degree
        int start = 0;
        for (int i = 0; i < vertices; i++) {
            if (!adjList[i].empty()) {
                start = i;
                break;
            }
        }
        
        DFSHelper(start, visited);
        
        // Check if all vertices with edges are visited
        for (int i = 0; i < vertices; i++) {
            if (!adjList[i].empty() && !visited[i]) {
                return false;
            }
        }
        
        return true;
    }
    
    // Detect cycle in undirected graph
    bool hasCycleHelper(int vertex, int parent, vector<bool>& visited) {
        visited[vertex] = true;
        
        for (int neighbor : adjList[vertex]) {
            if (!visited[neighbor]) {
                if (hasCycleHelper(neighbor, vertex, visited)) {
                    return true;
                }
            } else if (neighbor != parent) {
                return true;
            }
        }
        
        return false;
    }
    
    bool hasCycle() {
        vector<bool> visited(vertices, false);
        
        for (int i = 0; i < vertices; i++) {
            if (!visited[i] && !adjList[i].empty()) {
                if (hasCycleHelper(i, -1, visited)) {
                    return true;
                }
            }
        }
        
        return false;
    }
    
    // Display adjacency list
    void display() {
        cout << "Adjacency List:" << endl;
        for (int i = 0; i < vertices; i++) {
            cout << i << ": ";
            for (int neighbor : adjList[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
};

// Weighted Graph using Adjacency List
class WeightedGraph {
private:
    int vertices;
    vector<vector<pair<int, int>>> adjList; // pair<neighbor, weight>
    
public:
    WeightedGraph(int v) : vertices(v) {
        adjList.resize(v);
    }
    
    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight});
    }
    
    void addDirectedEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
    }
    
    void display() {
        cout << "Weighted Adjacency List:" << endl;
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
    cout << "=== Unweighted Graph ===" << endl;
    Graph g(6);
    
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);
    
    g.display();
    
    g.BFS(0);
    g.DFS(0);
    g.DFSIterative(0);
    
    cout << "Is connected: " << (g.isConnected() ? "Yes" : "No") << endl;
    cout << "Has cycle: " << (g.hasCycle() ? "Yes" : "No") << endl;
    
    cout << "\n=== Weighted Graph ===" << endl;
    WeightedGraph wg(4);
    
    wg.addEdge(0, 1, 10);
    wg.addEdge(0, 2, 6);
    wg.addEdge(0, 3, 5);
    wg.addEdge(1, 3, 15);
    wg.addEdge(2, 3, 4);
    
    wg.display();
    
    return 0;
}

/*
Time Complexity:
- Add Edge: O(1)
- BFS/DFS: O(V + E) where V = vertices, E = edges
- Cycle Detection: O(V + E)

Space Complexity:
- Adjacency List: O(V + E)
- Adjacency Matrix: O(V^2)
*/
