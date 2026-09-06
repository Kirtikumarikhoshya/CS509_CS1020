#include <iostream>
#include <iomanip>
#include "../include/graph.h"
#include "vertex_coloring.hpp"
#include "timer.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file_path>\n";
        return 1;
    }

    std::string filepath = argv[1];
    CSRGraph graph;

    try {
        // Preprocessing: Untimed
        graph = loadColoringGraph(filepath);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    // Timed Section: Algorithm Execution Only
    Timer timer;
    timer.start();
    ColoringResult result = runVertexColoring(graph);
    timer.stop();

    // Output formatting according to Section 5.3
    std::cout << "Algorithm: Greedy Vertex Coloring\n";
    std::cout << "Vertex colors:\n";
    for (int i = 0; i < graph.V; ++i) {
        std::cout << i << " " << result.colors[i] << "\n";
    }
    std::cout << "Colors used: " << result.num_colors << "\n";
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Execution time: " << timer.elapsedMs() << " ms\n";

    return 0;
}