#include "pagerank.hpp"
#include <cmath>
#include <numeric>

PageRankResult runPageRank(const CSRGraph& graph, const PageRankParams& params) {
    PageRankResult res;
    int N = graph.V;
    if (N == 0) return res;

    double d = params.damping;
    double tol = params.tolerance;
    int max_iter = params.max_iterations;

    // Precompute outdegrees from CSR
    std::vector<int> outdegree(N);
    for (int i = 0; i < N; ++i) {
        outdegree[i] = graph.row_ptr[i + 1] - graph.row_ptr[i];
    }

    // Initialize all ranks to 1 / N
    std::vector<double> pr(N, 1.0 / static_cast<double>(N));
    std::vector<double> next_pr(N, 0.0);

    double base_teleport = (1.0 - d) / static_cast<double>(N);

    for (int iter = 1; iter <= max_iter; ++iter) {
        res.iterations = iter;

        // Sum rank contributions of dangling nodes (outdegree == 0)
        double dangling_sum = 0.0;
        for (int u = 0; u < N; ++u) {
            if (outdegree[u] == 0) {
                dangling_sum += pr[u];
            }
        }

        // Each vertex receives teleport rank + evenly distributed dangling rank
        double base_contribution = base_teleport + (d * dangling_sum / static_cast<double>(N));
        for (int i = 0; i < N; ++i) {
            next_pr[i] = base_contribution;
        }

        // Distribute ranks along directed edges
        for (int u = 0; u < N; ++u) {
            if (outdegree[u] > 0) {
                double contrib = (d * pr[u]) / static_cast<double>(outdegree[u]);
                int start = graph.row_ptr[u];
                int end = graph.row_ptr[u + 1];
                for (int i = start; i < end; ++i) {
                    int v = graph.col_idx[i];
                    next_pr[v] += contrib;
                }
            }
        }

        // Convergence check via L1 norm (total absolute change)
        double diff = 0.0;
        for (int i = 0; i < N; ++i) {
            diff += std::fabs(next_pr[i] - pr[i]);
        }

        pr = next_pr;

        if (diff <= tol) {
            res.converged = true;
            break;
        }
    }

    res.ranks = pr;
    res.sum_ranks = 0.0;
    for (double r : pr) {
        res.sum_ranks += r;
    }

    return res;
}