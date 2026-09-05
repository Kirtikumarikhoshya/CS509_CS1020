#include "../include/graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

CSRGraph loadColoringGraph(const std::string& filepath) {
    std::ifstream infile(filepath);
    if (!infile.is_open()) {
        throw std::runtime_error("Could not open input file: " + filepath);
    }

    CSRGraph graph;
    std::string line;

    // Header: V and E
    while (std::getline(infile, line)) {
        if (line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos) continue;
        std::stringstream ss(line);
        if (ss >> graph.V >> graph.E) break;
    }

    if (graph.V <= 0) {
        throw std::runtime_error("Invalid vertex count V <= 0 in: " + filepath);
    }

    std::vector<std::vector<int>> adj(graph.V);

    while (std::getline(infile, line)) {
        if (line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos) continue;
        std::stringstream ss(line);
        int u, degree;
        if (!(ss >> u >> degree)) continue;

        if (u < 0 || u >= graph.V) {
            throw std::runtime_error("Vertex ID out of bounds: " + std::to_string(u));
        }

        int count = 0;
        int v;
        while (ss >> v) {
            if (v < 0 || v >= graph.V) {
                throw std::runtime_error("Neighbor vertex ID out of range: " + std::to_string(v));
            }
            if (u == v) {
                throw std::runtime_error("Self-loop detected at vertex: " + std::to_string(u));
            }
            adj[u].push_back(v);
            count++;
        }

        if (count != degree) {
            throw std::runtime_error("Mismatched degree/neighbor count for vertex " + std::to_string(u));
        }
    }
    infile.close();

    // Flatten to CSR
    graph.row_ptr.assign(graph.V + 1, 0);
    for (int i = 0; i < graph.V; ++i) {
        graph.row_ptr[i + 1] = graph.row_ptr[i] + static_cast<int>(adj[i].size());
    }

    int total_edges = graph.row_ptr[graph.V];
    graph.col_idx.reserve(total_edges);
    for (int i = 0; i < graph.V; ++i) {
        for (int v : adj[i]) {
            graph.col_idx.push_back(v);
        }
    }

    return graph;
}

CSRGraph loadPageRankGraph(const std::string& filepath, PageRankParams& params) {
    std::ifstream infile(filepath);
    if (!infile.is_open()) {
        throw std::runtime_error("Could not open input file: " + filepath);
    }

    CSRGraph graph;
    std::string line;

    // Header: V and E
    while (std::getline(infile, line)) {
        if (line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos) continue;
        std::stringstream ss(line);
        if (ss >> graph.V >> graph.E) break;
    }

    if (graph.V <= 0) {
        throw std::runtime_error("Invalid vertex count in: " + filepath);
    }

    std::vector<std::vector<int>> adj(graph.V);

    while (std::getline(infile, line)) {
        if (line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos) continue;
        std::stringstream ss(line);
        std::string token;
        if (!(ss >> token)) continue;

        if (token == "DAMPING") {
            ss >> params.damping;
            if (params.damping <= 0.0 || params.damping >= 1.0) {
                throw std::runtime_error("Invalid damping factor: must be in (0, 1)");
            }
        } else if (token == "TOLERANCE") {
            ss >> params.tolerance;
            if (params.tolerance <= 0.0) {
                throw std::runtime_error("Invalid tolerance: must be > 0");
            }
        } else if (token == "MAX_ITERATIONS") {
            ss >> params.max_iterations;
            if (params.max_iterations <= 0) {
                throw std::runtime_error("Invalid MAX_ITERATIONS: must be > 0");
            }
        } else {
            int u = std::stoi(token);
            int degree = 0;
            if (!(ss >> degree)) continue;

            if (u < 0 || u >= graph.V) {
                throw std::runtime_error("Vertex ID out of bounds: " + std::to_string(u));
            }

            for (int i = 0; i < degree; ++i) {
                int v;
                if (ss >> v) {
                    if (v >= 0 && v < graph.V) {
                        adj[u].push_back(v);
                    }
                }
            }
        }
    }
    infile.close();

    // Flatten to CSR
    graph.row_ptr.assign(graph.V + 1, 0);
    for (int i = 0; i < graph.V; ++i) {
        graph.row_ptr[i + 1] = graph.row_ptr[i] + static_cast<int>(adj[i].size());
    }

    int total_edges = graph.row_ptr[graph.V];
    graph.col_idx.reserve(total_edges);
    for (int i = 0; i < graph.V; ++i) {
        for (int v : adj[i]) {
            graph.col_idx.push_back(v);
        }
    }

    return graph;
}