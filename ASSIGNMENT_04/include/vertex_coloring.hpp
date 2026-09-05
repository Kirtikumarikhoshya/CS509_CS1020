#ifndef VERTEX_COLORING_HPP
#define VERTEX_COLORING_HPP

#include <vector>
#include "graph.h"

struct ColoringResult {
    std::vector<int> colors;
    int num_colors = 0;
    bool is_valid = false;
};

// Executes Welsh-Powell greedy heuristic coloring on undirected CSR graph
ColoringResult runVertexColoring(const CSRGraph& graph);

#endif // VERTEX_COLORING_HPP