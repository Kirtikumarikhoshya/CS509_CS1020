#ifndef PRIM_HPP
#define PRIM_HPP

#include "graph.h"
#include "kruskal.hpp"
#include <vector>

struct PrimResult {
    std::vector<MSTEdge> edges;
    long long total_weight = 0;
};

// Starts from vertex 0 for reproducible tree generation
PrimResult runPrimMST(const CSRGraph& graph, int start_node = 0);

#endif // PRIM_HPP