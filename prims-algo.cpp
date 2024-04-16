#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>

using namespace std;

typedef pair<int, int> pii;

class Graph {
private:
    int V;
    vector<vector<pii>> adj;

public:
    Graph(int vertices) : V(vertices), adj(vertices) {}

    void addEdge(int u, int v, int weight) {
        adj[u].push_back(make_pair(v, weight));
        adj[v].push_back(make_pair(u, weight)); // Undirected graph
    }

    vector<pii> primMST() {
        // Priority queue to store vertices with their minimum edge weights
        priority_queue<pii, vector<pii>, greater<pii>> pq;

        vector<int> key(V, INT_MAX); // Key values used to pick minimum weight edge
        vector<pii> parent(V, make_pair(-1, -1)); // Store MST edges

        vector<bool> inMST(V, false); // Track if vertex is included in MST

        // Start with vertex 0
        pq.push(make_pair(0, 0));
        key[0] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            // Include vertex u in MST
            inMST[u] = true;

            // Iterate through all adjacent vertices of u
            for (const auto& neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                // If v is not yet in MST and the weight of (u, v) is smaller than current key of v
                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = make_pair(u, weight);
                    pq.push(make_pair(key[v], v));
                }
            }
        }

        // Construct MST edges from parent array
        vector<pii> result;
        for (int i = 1; i < V; ++i) {
            result.push_back(parent[i]);
        }

        return result;
    }
};

int main() {
    int V = 5; // Number of vertices
    Graph g(V);

    // Add edges and their weights
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

    vector<pii> mst = g.primMST();

    cout << "Edges in the Minimum Spanning Tree (MST):\n";
    for (const auto& edge : mst) {
        cout << edge.first << " - " << edge.second << endl;
    }

    return 0;
}

