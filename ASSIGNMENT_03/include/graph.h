#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

// Compressed Sparse Row representation for weighted undirected graphs
struct CSRGraph {
    int V = 0;                      // Total number of vertices
    int E = 0;                      // Total number of undirected edges
    std::vector<int> row_ptr;       // Row offsets (size V + 1)
    std::vector<int> col_idx;       // Flattened column/neighbor indices
    std::vector<int> values;        // Flattened edge weights
};

// Function declaration to read adjacency list file and construct CSR
CSRGraph loadCSRGraph(const std::string& filepath);

#endif // GRAPH_H