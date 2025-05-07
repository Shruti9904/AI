#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, weight;
};

// Compare edges by weight
bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}

// Find parent of node
int findParent(int node, vector<int>& parent) {
    if (parent[node] == node)
        return node;
    return findParent(parent[node], parent);  // No path compression
}

// Union of two sets
void unionSets(int u, int v, vector<int>& parent) {
    int parentU = findParent(u, parent);
    int parentV = findParent(v, parent);
    parent[parentV] = parentU;
}

int main() {
    int V = 4; 
    vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    // Sort edges by weight (greedy)
    sort(edges.begin(), edges.end(), compare);

    vector<int> parent(V);
    for (int i = 0; i < V; i++) parent[i] = i;

    vector<Edge> mst;
    int totalCost = 0;

    for (Edge e : edges) {
        int u = e.u;
        int v = e.v;

        // If adding this edge won't form a cycle
        if (findParent(u, parent) != findParent(v, parent)) {
            mst.push_back(e);
            totalCost += e.weight;
            unionSets(u, v, parent);
        }
    }

    cout << "Edges in MST:\n";
    for (Edge e : mst) {
        cout << e.u << " - " << e.v << " : " << e.weight << "\n";
    }
    cout << "Total cost: " << totalCost << endl;

    return 0;
}