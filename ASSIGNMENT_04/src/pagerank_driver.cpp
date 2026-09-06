#include <iostream>
#include <iomanip>
#include "../include/graph.h"
#include "pagerank.hpp"
#include "timer.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file_path>\n";
        return 1;
    }

    std::string filepath = argv[1];
    PageRankParams params;
    CSRGraph graph;

    try {
        // Preprocessing: Untimed
        graph = loadPageRankGraph(filepath, params);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    // Timed Section: Algorithm Execution Only
    Timer timer;
    timer.start();
    PageRankResult result = runPageRank(graph, params);
    timer.stop();

    // Output formatting according to Section 6.3
    std::cout << "Algorithm: PageRank\n";
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Damping: " << std::setprecision(2) << params.damping << "\n";
    std::cout << "Vertex ranks:\n";
    for (int i = 0; i < graph.V; ++i) {
        std::cout << i << " " << std::fixed << std::setprecision(6) << result.ranks[i] << "\n";
    }
    std::cout << "Sum of ranks: " << std::fixed << std::setprecision(6) << result.sum_ranks << "\n";
    std::cout << "Iterations: " << result.iterations << "\n";
    std::cout << "Converged: " << (result.converged ? "true" : "false") << "\n";
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Execution time: " << timer.elapsedMs() << " ms\n";

    return 0;
}