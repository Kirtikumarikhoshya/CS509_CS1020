// #include "graph.h"
#include "../include/graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
using namespace std;

CSRGraph loadCSRGraph(const string& filepath) {
    ifstream infile(filepath);
    if (!infile.is_open()) {
        throw std::runtime_error("Unable to open graph file: " + filepath);
    }

    CSRGraph graph;
    string line;

    // Step 1: Parse the header (V and E)
    while (getline(infile, line)) {
        if (line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos) {
            continue;
        }
        stringstream ss(line);
        if (ss >> graph.V >> graph.E) {
            break;
        }
    }

    if (graph.V <= 0) {
        throw std::runtime_error("Invalid or missing vertex count in file: " + filepath);
    }

    // Temporary adjacency list for construction
    std::vector<std::vector<std::pair<int, int>>> adj(graph.V);

    // Step 2: Read each vertex line
    while (std::getline(infile, line)) {
        if (line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos) {
            continue;
        }

        std::stringstream ss(line);
        int u, degree;
        if (!(ss >> u >> degree)) {
            continue;
        }

        if (u < 0 || u >= graph.V) {
            throw std::runtime_error("Vertex ID out of bounds: " + std::to_string(u));
        }

        for (int i = 0; i < degree; ++i) {
            int v, w;
            if (ss >> v >> w) {
                if (v >= 0 && v < graph.V) {
                    adj[u].push_back({v, w});
                }
            }
        }
    }
    infile.close();

    // Step 3: Populate CSR arrays (row_ptr, col_idx, values)
    graph.row_ptr.assign(graph.V + 1, 0);
    for (int i = 0; i < graph.V; ++i) {
        graph.row_ptr[i + 1] = graph.row_ptr[i] + static_cast<int>(adj[i].size());
    }

    int total_elements = graph.row_ptr[graph.V];
    graph.col_idx.reserve(total_elements);
    graph.values.reserve(total_elements);

    for (int u = 0; u < graph.V; ++u) {
        for (const auto& neighbor : adj[u]) {
            graph.col_idx.push_back(neighbor.first);
            graph.values.push_back(neighbor.second);
        }
    }

    return graph;
}