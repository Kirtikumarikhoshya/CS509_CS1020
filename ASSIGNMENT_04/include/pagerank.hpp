#ifndef PAGERANK_HPP
#define PAGERANK_HPP

#include <vector>
#include "graph.h"

struct PageRankResult {
    std::vector<double> ranks;
    double sum_ranks = 0.0;
    int iterations = 0;
    bool converged = false;
};

// Executes PageRank iterative updates on directed CSR graph
PageRankResult runPageRank(const CSRGraph& graph, const PageRankParams& params);

#endif // PAGERANK_HPP