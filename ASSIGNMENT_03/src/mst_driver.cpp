// #include "graph.h"
// #include "timer.hpp"
#include "../include/graph.h"
#include "../include/timer.hpp"
#include "kruskal.hpp"
#include "prim.hpp"
#include <iostream>
#include <iomanip>
#include <string>

void displayKruskalOutput(const KruskalResult& res, double runtime_ms) {
    std::cout << "Algorithm: Kruskal's MST\n";
    std::cout << "MST edges:\n";
    for (const auto& edge : res.edges) {
        std::cout << edge.u << " " << edge.v << " " << edge.weight << "\n";
    }
    std::cout << "Total MST weight: " << res.total_weight << "\n";
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Execution time: " << runtime_ms << " ms\n\n";
}

void displayPrimOutput(const PrimResult& res, double runtime_ms) {
    std::cout << "Algorithm: Prim's MST\n";
    std::cout << "MST edges:\n";
    for (const auto& edge : res.edges) {
        std::cout << edge.u << " " << edge.v << " " << edge.weight << "\n";
    }
    std::cout << "Total MST weight: " << res.total_weight << "\n";
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Execution time: " << runtime_ms << " ms\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <graph_input_path.txt> [kruskal|prim|both]\n";
        return 1;
    }

    std::string filepath = argv[1];
    std::string algorithm_choice = (argc >= 3) ? argv[2] : "both";

    try {
        // Preprocessing: Adjacency list reading and CSR conversion (UNTIMED)
        CSRGraph graph = loadCSRGraph(filepath);

        Timer timer;

        if (algorithm_choice == "kruskal" || algorithm_choice == "both") {
            timer.start();
            KruskalResult kruskal_res = runKruskalMST(graph);
            timer.stop();
            displayKruskalOutput(kruskal_res, timer.getElapsedMilliseconds());
        }

        if (algorithm_choice == "prim" || algorithm_choice == "both") {
            timer.start();
            PrimResult prim_res = runPrimMST(graph, 0);
            timer.stop();
            displayPrimOutput(prim_res, timer.getElapsedMilliseconds());
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}