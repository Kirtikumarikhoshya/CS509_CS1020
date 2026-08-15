#include "prim.hpp"
#include <queue>
#include <vector>

namespace {
struct PrimHeapElement {
    int weight;
    int node;
    int parent;

    bool operator>(const PrimHeapElement& other) const {
        if (weight != other.weight) return weight > other.weight;
        if (parent != other.parent) return parent > other.parent;
        return node > other.node;
    }
};
} // namespace

PrimResult runPrimMST(const CSRGraph& graph, int start_node) {
    PrimResult result;
    result.total_weight = 0;

    int num_vertices = graph.V;
    if (num_vertices <= 1) {
        return result;
    }

    if (start_node < 0 || start_node >= num_vertices) {
        start_node = 0;
    }

    std::vector<bool> visited(num_vertices, false);
    std::priority_queue<PrimHeapElement, std::vector<PrimHeapElement>, std::greater<PrimHeapElement>> min_heap;

    // Start with root node
    min_heap.push({0, start_node, -1});

    int vertices_included = 0;

    while (!min_heap.empty() && vertices_included < num_vertices) {
        PrimHeapElement current = min_heap.top();
        min_heap.pop();

        int u = current.node;
        int p = current.parent;
        int w = current.weight;

        if (visited[u]) {
            continue;
        }

        visited[u] = true;
        vertices_included++;

        if (p != -1) {
            result.edges.push_back({p, u, w});
            result.total_weight += w;
        }

        // Expand CSR neighbors
        int start_idx = graph.row_ptr[u];
        int end_idx = graph.row_ptr[u + 1];

        for (int idx = start_idx; idx < end_idx; ++idx) {
            int v = graph.col_idx[idx];
            int edge_wt = graph.values[idx];

            if (!visited[v]) {
                min_heap.push({edge_wt, v, u});
            }
        }
    }

    return result;
}