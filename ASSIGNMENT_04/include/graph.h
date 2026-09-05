#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

// Unweighted Compressed Sparse Row (CSR) Graph Representation
struct CSRGraph {
    int V = 0;
    int E = 0;
    std::vector<int> row_ptr; // Size V + 1
    std::vector<int> col_idx; // Size E
};

// PageRank specific hyperparameter container
struct PageRankParams {
    double damping = 0.85;
    double tolerance = 1e-4;
    int max_iterations = 100;
};

// Adjacency-list loaders (Preprocessing)
CSRGraph loadColoringGraph(const std::string& filepath);
CSRGraph loadPageRankGraph(const std::string& filepath, PageRankParams& params);

#endif // GRAPH_H