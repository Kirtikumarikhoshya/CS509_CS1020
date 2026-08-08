#include "bellman_ford.hpp"
#include <limits>
using namespace std;

BellmanFordResult runBellmanFord(const CSRGraph graph,int source){
    BellmanFordResult result;
    result.source = source;
    int V = graph.num_vertices;

    if (V <=0 || source <0 || source >= V){
        return result;
    }

    const double INF = numeric_limits<double>::infinity();
    result.distance.assign(V, INF);
    result.distance[source] = 0.0;


    //relaxing all E edges v-1 times

    for(int iter = 0; iter <V-1; ++iter){
        bool updated = false;

        for(int u = 0; u < V ; ++u){
            if(result.distances[u] == INF) continue;

            int start_idx = graph.row_ptr[u];
            int end_idx = graph.row_ptr[u+1];

            for(int idx = start_idx; idx< end_idx; ++idx){
                int v = graph.col_ind[idx];
                double weight = graph.weights[idx];

                if(result.distance[u] + weight < result.distances[v]){
                    result.distances[v] = result.distances[u] + weight;
                    updated = true;
                }
            }
        }
        if(!updated) break;
    }


    for(int u =0; u < V;  ++u){
        if(result.distances[u]== INF) continue;

        int start_idx = graph.row_ptr[u];
        int end_idx = graph.row_ptr[u+1];

        for(int idx = start_idx; idx < end_idx; ++idx){
            int v = graph.col_ind[idx];
            double weight = graph.weights[idx];

            if(result.distances[u] + weight < result.distances[v]){
                result.has_negtive_cycle = true;
                return result;// detection of negative cycle
            }

        }
    }
    return result;
}