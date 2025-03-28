#include "dijkstras.h"
#include <queue>
#include <algorithm>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int numVertices = G.numVertices;

    std::vector<int> distances(numVertices, INF);
    previous.assign(numVertices, -1);
    std::vector<bool> visited(numVertices, false);
    distances[source] = 0;
    
    // pair<weight, vertex>
    std::priority_queue<pair<int, int>, std::vector<pair<int, int>>, std::greater<pair<int, int>>> minHeap;
    minHeap.push({0, source});

    while (!minHeap.empty()) {
        int u = minHeap.top().second;
        minHeap.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (Edge neighbor : G[u]) {
            int v = neighbor.dst;
            int weight = neighbor.weight;
            if (!visited[v] && (distances[u] + weight) < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({distances[v], v});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    std::vector<int> res;
    for (int i=destination; i > -1; i = previous[i])
        res.push_back(i);

    std::reverse(res.begin(), res.end());
    return res;
}

void print_path(const vector<int>& v, int total) {
    for (int node : v) 
        std::cout << node << ' ';
    std::cout << std::endl;
    std::cout << "Total cost is " << total << std::endl;
}