#include "floyd_warshall.hpp"
#include "timer.hpp"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

int main(int argc, char*argv[]){
    if (argc <2){
        cerr << "usage : " << argv[0] << "<input_file_path\n";
        return 1;
    }

    string filename = argv[1];

    FloydWarshallInput input = loadFloydWarshallMatrix(filename);
    if(input.num_vertices == 0){
        cerr << "error failed to load.\n";
        return 1;
    }

    Timer timer;
    timer.start();
    FloydWarshallResult res = runFloydWarshall(input);
    timer.stop();

    cout << "Algorithm : Floyd Warshall\n";

    if(res.has_negative_cycle){
        cout << "Negative cycle: true\n";

    }else{
        cout << "distance matrix: \n";

        for(int i =0 ; i< input.num_vertices; ++i){
            for(int j =0; j< input.num_vertices; ++j){
                if(res.dist[i][j] == numeric_limits<double>::infinity()){
                    cout << "INF";

                }else{
                    cout << static_cast<long long>(res.dist[i][j]);
                }
                if (j+1 < input.num_vertices) cout << " ";
            }
            cout << "\n";
        }
        cout << "negative cycle : none\n";
    }

    cout << std::fixed << std::setprecision(4);
    cout << "execution time: " << timer.elapsedMs() << "ms\n";

    return 0;
}