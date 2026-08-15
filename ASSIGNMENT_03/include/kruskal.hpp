#ifndef KRUSKAL_HPP
#define KRUSKAL_HPP

#include "graph.h"
#include <vector>

struct MSTEdge {
    int u;
    int v;
    int weight;
};

struct KruskalResult {
    std::vector<MSTEdge> edges;
    long long total_weight = 0;
};

KruskalResult runKruskalMST(const CSRGraph& graph);

#endif // KRUSKAL_HPP