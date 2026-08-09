#include "floyd_warshall.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
using namespace std;

FloydWarshallInput loadFloydWarshallMatrix(const string& filename){
    ifstream infile(filename);
    FloydWarshallInput input;

    if(!infile.is_open()){
        cerr << "error can't open file" << filename << endl;
        return input;
    }

    string line;
    int V = 0;

    while( getline(infile , line)){
        if(line.empty() || line[0] == '#') continue;
        stringstream ss(line);
        if (ss >> V){
            break;
        }
    }
    if (V <= 0){
        infile.close();
        return input;
    }

    input.num_vertices = V;
    const double INF = numeric_limits<double>::infinity();
    input.matrix.assign(V, vector<double>(V, INF));

    int row = 0;
    while(row < V && getline(infile,line)){
        if(line.empty() || line[0] == '#') continue;

        stringstream ss(line);
        string token;
        int col =0;

        while(col < V && ss >> token){
            if(token == "INF" || token == "inf" || token == "Inf"){
                input.matrix[row][col] = INF;
            }else{
                input.matrix[row][col] = stod(token);
            }
            col++;
        }
        row++;
    }
    infile.close();
    return input;
}

FloydWarshallResult runFloydWarshall(const FloydWarshallInput& input){
    FloydWarshallResult result;
    int V  = input.num_vertices;

    if(V <= 0){
        return result;
    }

    const double INF = numeric_limits<double>::infinity();
    result.dist = input.matrix;

    for(int k =0; k< V; ++k){
        for( int i =0; i <V; ++i){
            for (int j =0; j < V ; ++j){
                if(result.dist[i][k] != INF && result.dist[k][j] !=INF){
                    if(result.dist[i][k] + result.dist[k][j] < result.dist[i][j]){
                        result.dist[i][j] = result.dist[i][k] + result.dist[k][j];
                    }
                }
            }
        }
    }

    for(int i =0; i< V ; ++i){
        if(result.dist[i][i] < 0.0){
            result.has_negative_cycle = true;
        }
    }

    return result;
}