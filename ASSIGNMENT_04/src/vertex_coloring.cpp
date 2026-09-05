#include "vertex_coloring.hpp"
#include <algorithm>
#include <numeric>

ColoringResult runVertexColoring(const CSRGraph& graph) {
    ColoringResult result;
    int V = graph.V;
    result.colors.assign(V, -1);

    if (V == 0) {
        result.num_colors = 0;
        result.is_valid = true;
        return result;
    }

    // 1. Calculate degrees directly from CSR in O(1) per vertex
    std::vector<int> degrees(V);
    for (int i = 0; i < V; ++i) {
        degrees[i] = graph.row_ptr[i + 1] - graph.row_ptr[i];
    }

    // 2. Welsh-Powell ordering: sort vertices by degree descending
    std::vector<int> order(V);
    std::iota(order.begin(), order.end(), 0);
    std::stable_sort(order.begin(), order.end(), [&](int a, int b) {
        return degrees[a] > degrees[b];
    });

    // 3. Greedy coloring using an iteration-stamp array
    std::vector<int> last_seen(V, -1);
    int max_color_assigned = -1;

    for (int idx = 0; idx < V; ++idx) {
        int u = order[idx];

        // Mark colors taken by colored neighbors
        int start = graph.row_ptr[u];
        int end = graph.row_ptr[u + 1];
        for (int i = start; i < end; ++i) {
            int v = graph.col_idx[i];
            int c = result.colors[v];
            if (c != -1) {
                last_seen[c] = u;
            }
        }

        // Find the smallest available color
        int assigned = 0;
        while (assigned < V && last_seen[assigned] == u) {
            assigned++;
        }

        result.colors[u] = assigned;
        if (assigned > max_color_assigned) {
            max_color_assigned = assigned;
        }
    }

    result.num_colors = max_color_assigned + 1;

    // 4. Correctness validation: ensure no two adjacent vertices share a color
    result.is_valid = true;
    for (int u = 0; u < V; ++u) {
        int start = graph.row_ptr[u];
        int end = graph.row_ptr[u + 1];
        for (int i = start; i < end; ++i) {
            int v = graph.col_idx[i];
            if (result.colors[u] == result.colors[v]) {
                result.is_valid = false;
                break;
            }
        }
        if (!result.is_valid) break;
    }

    return result;
}