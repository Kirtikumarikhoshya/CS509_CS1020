# CS509: PG Software Lab — Assignment 03

## Student Information
* **Repository**: [CS509_CS1020](https://github.com/Kirtikumarikhoshya/CS509_CS1020.git)
* **Student Name**: KIRTI KUMARI
* **Entry No**: 2026CSM1020

---

## 1. Overview & Project Structure

This repository contains the C++17 implementations, driver programs, and performance benchmarking for **Assignment 03** (Minimum Spanning Tree):
1. **Kruskal's Algorithm**: Extracts unique undirected edges ($u < v$), sorts them in non-decreasing order of weight, and applies Disjoint Set Union (DSU) with path compression and union by rank.
2. **Prim's Algorithm**: Greedily grows a minimum spanning tree from source vertex 0 using a min-priority queue (min-heap) until all reachable vertices are spanned.

Both algorithms operate on weighted, undirected graphs converted from adjacency lists into Compressed Sparse Row (CSR) format (`row_ptr`, `col_idx`, `values`).

### Directory Layout

```text
ASSIGNMENT_03/
├── bin/                             # Output compiled binary executables
│   └── mst_driver.exe
├── include/                         # Header declarations
│   ├── graph.h                      # CSRGraph data structure & loader
│   ├── kruskal.hpp                  # Kruskal's MST declarations
│   ├── prim.hpp                     # Prim's MST declarations
│   └── timer.hpp                    # High-precision execution timer
├── outputs/                         # Benchmark result logs
│   ├── mst_10_output.txt
│   ├── mst_100_output.txt
│   ├── mst_10000_output.txt
│   ├── mst_50000_output.txt
│   ├── mst_100000_output.txt
│   ├── mst_edge_neg_zero_output.txt
│   └── mst_edge_ties_output.txt
├── src/                             # C++ Source implementations
│   ├── csr.cpp                      # Adjacency-list to CSR converter
│   ├── kruskal.cpp                  # Kruskal's algorithm implementation
│   ├── mst_driver.cpp               # MST benchmark runner & driver
│   └── prim.cpp                     # Prim's algorithm implementation
├── tests/                           # Input test graphs
│   ├── mst_10.txt
│   ├── mst_100.txt
│   ├── mst_10000.txt
│   ├── mst_50000.txt
│   ├── mst_100000.txt
│   ├── mst_edge_neg_zero.txt
│   └── mst_edge_ties.txt
├── Makefile                         # Build automation script
├── wrapper.cpp                      # Multi-assignment interactive wrapper
└── README.md                        # Assignment report and documentation
```


2. Compilation and Execution Commands
All source files are compiled using g++ with standard C++17 flags and -O2 optimizations.

PowerShell
# Compile MST Driver Binary
g++ -std=c++17 -O2 -Wall -Wextra -Iinclude src/csr.cpp src/kruskal.cpp src/prim.cpp src/mst_driver.cpp -o bin/mst_driver.exe

# Compile Root Interactive Wrapper
g++ -std=c++17 -O2 wrapper.cpp -o wrapper.exe
Execution Commands
PowerShell
# Run both Kruskal and Prim on a test graph
.\bin\mst_driver.exe tests\mst_10.txt both

# Run only Kruskal's MST
.\bin\mst_driver.exe tests\mst_10.txt kruskal

# Run only Prim's MST
.\bin\mst_driver.exe tests\mst_10.txt prim

# Launch interactive CLI wrapper
.\wrapper.exe


### 9. Required Report File with Result Tables

#### 9.1 MST Results Table

| File | V | E | Exp. Wt. | Kruskal Wt. | Prim Wt. | Kruskal Time | Prim Time | Equal? | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| `mst_10.txt` | 10 | 15 | 31 | 31 | 31 | 1.0360 ms | 0.0000 ms | Yes | Pass |
| `mst_100.txt` | 100 | 200 | 1473 | 1473 | 1473 | 0.0000 ms | 0.0000 ms | Yes | Pass |
| `mst_10000.txt` | 10000 | 20000 | 283812 | 283812 | 283812 | 2.1210 ms | 3.0000 ms | Yes | Pass |
| `mst_50000.txt` | 50000 | 100000 | 1419060 | 1419060 | 1419060 | 14.5210 ms | 18.2340 ms | Yes | Pass |
| `mst_100000.txt` | 100000 | 200000 | 2838120 | 2838120 | 2838120 | 31.8420 ms | 39.1120 ms | Yes | Pass |

---

### 5. Edge Cases Tested

| Test Case File | V | E | Edge Condition Tested | Expected Wt. | Kruskal Wt. | Prim Wt. | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| `mst_edge_neg_zero.txt` | 4 | 5 | Negative and zero weight edges | -11 | -11 | -11 | Pass |
| `mst_edge_ties.txt` | 4 | 4 | Duplicate identical edge weights (Ties) | 15 | 15 | 15 | Pass |