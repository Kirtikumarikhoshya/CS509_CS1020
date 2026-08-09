#include "graph.h"
#include "bellman_ford.hpp"
#include "timer.hpp"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

int main(int argc, char* argv[]){
    if(argc < 2){
        cerr << "usuage: " << argv[0] << "input _file_path\n";
        return 1;
    }

    string filename = argv[1];
    CSRGraph graph = loadCSRGraph(filename);
    if(graph.num_vertices == 0){
        cerr << "error failed to load \n";
        return 1;
    }

    int source = (graph.source_vertex != -1) ? graph.source_vertex : 0;

    Timer timer;
    timer.start();
    BellmanFordResult res = runBellmanFord(graph,source);
    timer.stop();

    double elapsed_ms = timer.elapsedMs();


    cout << "Algorithm : Bellman_ford\n";
    cout << "source: " << res.source << "\n";


    if (res.has_negative_cycle){
        cout << "Negative cycle: true\n";
    }
    else{
        cout << "vertex distance\n";
        for (int i =0; i <graph.num_vertices; ++i){
            cout << i << " ";
            if (res.distances[i] == numeric_limits<double>:: infinity()){
                cout << "INF\n";
    
            }
            else{
                cout << static_cast<long long>(res.distances[i] ) << "\n";
            }
        }
         cout << "Negative cycle: none \n";
    }
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Execution time: " << elapsed_ms << " ms\n";

    return 0;
}
