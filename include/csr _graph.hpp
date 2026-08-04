#ifndef CSR_GRAPH_HPP
#define CSR_GRAPH_HPP

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
using namespace std;


//GRAPH CSR STRUCTURE
struct CSRGraph{
    int num_vertices =0;
    int num_edges =0;
    int source_vertex =0;

    vector<int> row_ptr;
    vector<int> col_idx;
    vector<int> values;
};
 // INTERNAL REP. FOR PARSING 
struct AdjListGraph{
    int V = 0;
    int E = 0;
    int source = 0;
    vector<vector<pair<int,int>>> adj;
};

// CONVERT ADJ LIST TO CSR

inline CSRGraph convertToCSR(const AdjListGraph& adjList){
    CSRGraph csr;
    csr.num_vertices= adjList.V;
    csr.num_edges = adjList.E;
    csr.source_vertex = adjList.source;

    csr.row_ptr.reserve(adjList.V +1);
    csr.row_ptr.push_back(0);

    for(int i =0; i < adjList.V ; ++i){
        for(const auto& edge : adjList.adj[i]){
            csr.col_idx.push_back(edge.first);
            csr.values.push_back(edge.second);
        }
        csr.row_ptr.push_back(static_cast<int>(csr.col_idx.size()));
    }
    return csr;
}

// READER FOR UNWEIGHTED GRAPHS

inline CSRGraph readUnweightedGraphToCSR(const string& filepath){
    ifstream infile(filepath);
    if(!infile.is_open()){
        throw runtime_error("could not open file:" + filepath);
    }

    AdjListGraph adjList;
    if(!(infile >> adjList.V >> adjList.E)){
        throw runtime_error("Invalid file format");
    }

    adjList.adj.resize(adjList.V);
    for(int i = 0; i < adjList.V; ++i ){
        int u, degree;
        if(!(infile >> u >> degree)) break;
        for(int d=0; d< degree; ++d){
            int v;
            infile >> v;
            adjList.adj[u].push_back({v,1});
        }
    }
  
    string tag;
    while(infile >> tag){
        if (tag == "SOURCE"){
            infile >> adjList.source;
            break;
        }
    }
    return convertToCSR(adjList);
}
  //READER FOR WEIGHTED GRAPH
inline CSRGraph readWeightedGraphToCSR(string& filepath){
    ifstream infile(filepath);
    if(!infile.is_open()){
        throw runtime_error("could not open file");
    }

    AdjListGraph adjList;
    if(!(infile >> adjList.V >> adjList.E)){
       throw runtime_error("Invalid file format");
    }

    adjList.adj.resize(adjList.V);
    for(int i= 0; i < adjList.V; ++i){
        int u, degree;
        if(!(infile >> u >> degree)) break;
        for(int d = 0; d < degree; d++){
            int v,w;
            infile >> v >> w;
            adjList.adj[u].push_back({v,w});
        }
    }
    string tag;
    while (infile >> tag) {
        if (tag == "SOURCE"){
            infile >> adjList.source;
            break;
        }
    }
    return convertToCSR(adjList);
}


# endif


