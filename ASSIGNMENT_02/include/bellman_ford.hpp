#ifndef BELLMAN_FORD_HPP
#define BELLMAN_FORD_HPP

#include "graph.h"
#include <vector>

struct BellmanFordResult {
    std::vector<double> distances;
    bool has_negative_cycle = false;
    int source = 0;


};

BellmanFordResult runBellmanFord(const CSRGraph& graph, int source);

#endif