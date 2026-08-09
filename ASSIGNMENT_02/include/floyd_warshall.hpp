#ifndef FLOYD_WARSHALL_HPP
#define FLOYD_WARSHALL_HPP

#include <vector>
#include <string>
#include <limits>


struct FloydWarshallInput{
    int num_vertices = 0;
    std::vector<std::vector<double>>matrix;
};

struct FloydWarshallResult{
    std::vector<std::vector<double>>dist;
    bool has_negative_cycle = false;
};

FloydWarshallInput loadFloydWarshallMatrix(const std::string& filename);
FloydWarshallResult runFloydWarshall(const FloydWarshallInput& input);

#endif