#include "dijkstras.h"

int main() {
    Graph G;

    file_to_graph("medium.txt", G);

    int source = 0;
    int max = G.numVertices - 1;

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);
    
    for (int i = 0; i <= max; ++i) {
        vector<int> path = extract_shortest_path(distances, previous, i);
        print_path(path, distances[i]);
    }

    return 0;
}