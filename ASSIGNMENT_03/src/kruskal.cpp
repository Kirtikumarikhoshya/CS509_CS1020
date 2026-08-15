#include "kruskal.hpp"
#include <algorithm>
#include <numeric>

namespace {
// Disjoint Set Union structure
struct DisjointSetUnion {
    std::vector<int> parent;
    std::vector<int> rank;

    explicit DisjointSetUnion(int n) {
        parent.resize(n);
        std::iota(parent.begin(), parent.end(), 0);
        rank.assign(n, 0);
    }

    int find(int node) {
        if (parent[node] != node) {
            parent[node] = find(parent[node]); // Path compression
        }
        return parent[node];
    }

    bool unite(int a, int b) {
        int root_a = find(a);
        int root_b = find(b);

        if (root_a == root_b) {
            return false; // Cycle detected
        }

        if (rank[root_a] < rank[root_b]) {
            parent[root_a] = root_b;
        } else if (rank[root_a] > rank[root_b]) {
            parent[root_b] = root_a;
        } else {
            parent[root_b] = root_a;
            rank[root_a]++;
        }
        return true;
    }
};
} // namespace

KruskalResult runKruskalMST(const CSRGraph& graph) {
    KruskalResult result;
    result.total_weight = 0;

    int num_vertices = graph.V;
    if (num_vertices <= 1) {
        return result;
    }

    // Step 1: Extract unique undirected edges (u < v) from CSR
    std::vector<MSTEdge> edge_list;
    edge_list.reserve(graph.E > 0 ? graph.E : num_vertices * 2);

    for (int u = 0; u < num_vertices; ++u) {
        int start_idx = graph.row_ptr[u];
        int end_idx = graph.row_ptr[u + 1];

        for (int idx = start_idx; idx < end_idx; ++idx) {
            int v = graph.col_idx[idx];
            int w = graph.values[idx];
            if (u < v) {
                edge_list.push_back({u, v, w});
            }
        }
    }

    // Step 2: Sort edges in non-decreasing order of weight
    std::sort(edge_list.begin(), edge_list.end(), [](const MSTEdge& a, const MSTEdge& b) {
        if (a.weight != b.weight) {
            return a.weight < b.weight;
        }
        if (a.u != b.u) {
            return a.u < b.u;
        }
        return a.v < b.v;
    });

    // Step 3: Kruskal greedy selection with DSU
    DisjointSetUnion dsu(num_vertices);
    int edges_selected = 0;

    for (const auto& edge : edge_list) {
        if (dsu.unite(edge.u, edge.v)) {
            result.edges.push_back(edge);
            result.total_weight += edge.weight;
            edges_selected++;

            if (edges_selected == num_vertices - 1) {
                break;
            }
        }
    }

    return result;
}