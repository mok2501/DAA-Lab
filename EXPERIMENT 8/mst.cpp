#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct Edge {
    int u, v, weight;
};

int findParent(vector<int>& parent, int x) {
    if (parent[x] == x)
        return x;

    return parent[x] = findParent(parent, parent[x]);
}

void unionSets(vector<int>& parent, vector<int>& rank, int u, int v) {
    u = findParent(parent, u);
    v = findParent(parent, v);

    if (u == v)
        return;

    if (rank[u] < rank[v])
        parent[u] = v;
    else if (rank[u] > rank[v])
        parent[v] = u;
    else {
        parent[v] = u;
        rank[u]++;
    }
}

void kruskal(int V, vector<Edge> edges) {

    sort(edges.begin(), edges.end(),
         [](Edge a, Edge b) {
             return a.weight < b.weight;
         });

    vector<int> parent(V);
    vector<int> rank(V, 0);

    for (int i = 0; i < V; i++)
        parent[i] = i;

    int totalWeight = 0;

    cout << "\nKruskal's MST:\n";

    int count = 0;

    for (Edge e : edges) {

        if (findParent(parent, e.u) != findParent(parent, e.v)) {

            cout << e.u << " - " << e.v
                 << " : " << e.weight << endl;

            totalWeight += e.weight;

            unionSets(parent, rank, e.u, e.v);

            count++;

            if (count == V - 1)
                break;
        }
    }

    cout << "Total weight = " << totalWeight << endl;
}


void prim(vector<vector<int>>& graph, int V) {

    vector<int> key(V, INT_MAX);
    vector<bool> inMST(V, false);
    vector<int> parent(V, -1);

    key[0] = 0;

    for (int count = 0; count < V; count++) {

        int u = -1;

        for (int i = 0; i < V; i++) {
            if (!inMST[i] &&
                (u == -1 || key[i] < key[u])) {
                u = i;
            }
        }

        inMST[u] = true;

        for (int v = 0; v < V; v++) {

            if (graph[u][v] != 0 &&
                !inMST[v] &&
                graph[u][v] < key[v]) {

                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    int totalWeight = 0;

    cout << "\nPrim's MST:\n";

    for (int i = 1; i < V; i++) {

        cout << parent[i] << " - "
             << i << " : "
             << graph[i][parent[i]] << endl;

        totalWeight += graph[i][parent[i]];
    }

    cout << "Total weight = " << totalWeight << endl;
}


int main() {

    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    cout << "Enter number of edges: ";
    cin >> E;

    vector<vector<int>> graph(V, vector<int>(V, 0));
    vector<Edge> edges;

    cout << "Enter edges (source destination weight):\n";

    for (int i = 0; i < E; i++) {

        int u, v, w;
        cin >> u >> v >> w;

        graph[u][v] = w;
        graph[v][u] = w;

        edges.push_back({u, v, w});
    }

    prim(graph, V);

    kruskal(V, edges);

    return 0;
}