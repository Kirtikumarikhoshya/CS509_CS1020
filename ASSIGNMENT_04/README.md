CS509: PG Software Lab — Assignment 04 Report: CS509_CS1020
Student Name: Kirti Kumari
Entry Number: 2026CSM1020 
1. Overview & Project StructureThis project implements, validates, and evaluates two core graph algorithms on large-scale sparse networks using the Compressed Sparse Row (CSR) storage format:Greedy Vertex Coloring: Orders graph vertices using the Welsh-Powell heuristic (sorting by out-degree in descending order) and greedily assigns the minimum available integer color index ($0, 1, 2, \dots$) such that no adjacent vertices share the same color.PageRank: Computes importance scores across directed graphs using iterative power updates with damping factor $d = 0.85$. It tracks residual probability from dangling vertices (out-degree = 0) and distributes it uniformly, terminating when the change in $L_1$ norm drops below the convergence tolerance ($10^{-4}$) or maximum iterations ($100$) are reached.PlaintextASSIGNMENT_04/
├── bin/                             # Compiled binaries
│   ├── color_driver.exe             # Vertex Coloring driver
│   └── pagerank_driver.exe          # PageRank driver
├── include/                         # Header declarations
│   ├── graph.h                      # CSR graph representation and loader
│   ├── pagerank.hpp                 # PageRank prototypes and structures
│   ├── timer.hpp                    # High-precision execution timer
│   └── vertex_coloring.hpp          # Vertex coloring declarations
├── outputs/                         # Benchmark logs
│   ├── color_10_output.txt
│   ├── color_100_output.txt
│   ├── color_10000_output.txt
│   ├── color_50000_output.txt
│   ├── color_100000_output.txt
│   ├── pagerank_10_output.txt
│   ├── pagerank_100_output.txt
│   ├── pagerank_1000_output.txt
│   ├── pagerank_10000_output.txt
│   └── pagerank_50000_output.txt
├── src/                             # Source implementations
│   ├── color_driver.cpp             # Driver for vertex coloring
│   ├── csr.cpp                      # Adjacency list to CSR conversion
│   ├── pagerank.cpp                 # PageRank power iteration
│   ├── pagerank_driver.cpp          # Driver for PageRank
│   └── vertex_coloring.cpp          # Welsh-Powell coloring implementation
├── tests/                           # Input dataset files
│   ├── coloring/                    # Undirected graph inputs
│   └── pagerank/                    # Directed graph inputs
├── Makefile                         # Build automation script
└── README.md                        # Documentation and result logs
2. Compilation and ExecutionAll programs are written in C++17 and compiled with -O2 optimization using g++.CompilationPowerShell# Build both binaries using the Makefile
make

# Manual compilation with g++
g++ -std=c++17 -O2 -Wall -Wextra -Iinclude src/csr.cpp src/vertex_coloring.cpp src/color_driver.cpp -o bin/color_driver.exe
g++ -std=c++17 -O2 -Wall -Wextra -Iinclude src/csr.cpp src/pagerank.cpp src/pagerank_driver.cpp -o bin/pagerank_driver.exe
Execution CommandsPowerShell# Vertex Coloring runs
.\bin\color_driver.exe tests\coloring\color_10.txt
.\bin\color_driver.exe tests\coloring\color_100.txt
.\bin\color_driver.exe tests\coloring\color_10000.txt
.\bin\color_driver.exe tests\coloring\color_50000.txt
.\bin\color_driver.exe tests\coloring\color_100000.txt

# PageRank runs
.\bin\pagerank_driver.exe tests\pagerank\pagerank_10.txt
.\bin\pagerank_driver.exe tests\pagerank\pagerank_100.txt
.\bin\pagerank_driver.exe tests\pagerank\pagerank_1000.txt
.\bin\pagerank_driver.exe tests\pagerank\pagerank_10000.txt
.\bin\pagerank_driver.exe tests\pagerank\pagerank_50000.txt

## 3. Benchmark Result Specifications

### 3.1 Greedy Vertex Coloring Results

| Input File | Output File | Vertices (V) | Edges (E) | Colors Used | Valid Coloring? | Execution Time | Status |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: | :---: |
| `color_10.txt` | `color_10_output.txt` | 10 | 15 | 3 | Yes | 0.0000 ms | Pass |
| `color_100.txt` | `color_100_output.txt` | 100 | 200 | 4 | Yes | 0.0000 ms | Pass |
| `color_10000.txt` | `color_10000_output.txt` | 10,000 | 20,000 | 4 | Yes | 1.0080 ms | Pass |
| `color_50000.txt` | `color_50000_output.txt` | 50,000 | 100,000 | 5 | Yes | 1.0040 ms | Pass |
| `color_100000.txt` | `color_100000_output.txt` | 100,000 | 200,000 | 4 | Yes | 3.0060 ms | Pass |

---

### 3.2 PageRank Results

| Input File | Output File | Vertices (V) | Edges (E) | Damping (d) | Top Vertex | Sum of Ranks | Iterations | Execution Time | Status |
| :--- | :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| `pagerank_10.txt` | `pagerank_10_output.txt` | 10 | 18 | 0.85 | 0 | 1.000000 | 18 | 0.0000 ms | Pass |
| `pagerank_100.txt` | `pagerank_100_output.txt` | 100 | 200 | 0.85 | 0 | 1.000000 | 1 | 0.0000 ms | Pass |
| `pagerank_1000.txt` | `pagerank_1000_output.txt` | 1,000 | 2,000 | 0.85 | 0 | 1.000000 | 1 | 0.0000 ms | Pass |
| `pagerank_10000.txt` | `pagerank_10000_output.txt` | 10,000 | 20,000 | 0.85 | 0 | 1.000000 | 1 | 0.0000 ms | Pass |
| `pagerank_50000.txt` | `pagerank_50000_output.txt` | 50,000 | 100,000 | 0.85 | 0 | 1.000000 | 1 | 0.0000 ms | Pass |