#include "dijkstras.h"
#include <algorithm>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int numVertices = G.size();
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);
    distances[source] = 0;
    previous.assign(numVertices, -1);
    
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> minHeap;
    minHeap.push({source, 0});
    while (!minHeap.empty()) {
        int u = minHeap.top().first;
        minHeap.pop();

        if (visited[u]) {
            continue;
        }

        visited[u] = true;

        for (Edge e : G[u]) {
            int v = e.dst;
            int weight = e.weight;

            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({v, distances[v]});
            }
        }
    }

    return distances;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {
    std::vector<int> shortest_path;

    if (previous[destination] == -1 && destination != 0) {
        return shortest_path;
    }

    for (int v = destination; v != -1; v = previous[v]) {
        shortest_path.push_back(v);
    }

    std::reverse(shortest_path.begin(), shortest_path.end());

    return shortest_path;
}

void print_path(const vector<int>& v, int total) {
    for (int i : v) {
        std::cout << i << " ";
    }
    std::cout << endl;

    std::cout << "Total cost is " << total << endl;
}