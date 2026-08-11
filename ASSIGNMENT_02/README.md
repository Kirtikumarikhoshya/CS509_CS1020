# CS509: PG Software Lab — Assignment 02

## Student Information
* **Repository**: [CS509_CS1020]
* **Student Name**: Kirti Kumari
* **Entry No**: 2026csm1020

---

## 1. Overview & Project Structure

This repository contains the C++17 implementations, driver programs, and performance benchmarking for the individual algorithms assigned in **Assignment 02**:
1. **Bellman-Ford Algorithm** (O(V · E) Single-Source Shortest Paths with negative weight edge handling and negative cycle detection)
2. **Floyd-Warshall Algorithm** (O(V³) All-Pairs Shortest Paths operating on dense adjacency matrices with negative cycle detection)

### Directory Layout

```text
ASSIGNMENT_02/
├── bin/                        # Compiled executable binaries
│   ├── bf_driver.exe
│   └── fw_driver.exe
├── include/                    # Header declarations
│   ├── bellman_ford.hpp
│   ├── floyd_warshall.hpp
│   ├── graph.h
│   └── timer.hpp
├── src/                        # Core algorithm implementations & drivers
│   ├── bellman_ford.cpp
│   ├── bf_driver.cpp
│   ├── csr.cpp
│   ├── floyd_warshall.cpp
│   └── fw_driver.cpp
├── tests/                      # Input test graphs and dense matrix files
│   ├── bf_10.txt
│   ├── bf_100.txt
│   ├── bf_1000.txt
│   ├── bf_10000.txt
│   ├── bf_50000.txt
│   ├── bf_100000.txt
│   ├── fw_10.txt
│   ├── fw_100.txt
│   ├── fw_500.txt
│   ├── fw_1000.txt
│   └── fw_neg_cycle.txt
├── outputs/                    # Output benchmark logs
├── Makefile                    # Target build script
└── README.md                   # Benchmark report and documentation
```

---

## 2. Compilation and Execution Commands

All components are compiled using `g++` with standard C++17 flags and `-O2` optimizations.

```powershell
# Compile Bellman-Ford Binary
g++ -std=c++17 -O2 -Wall -Wextra -Iinclude src/csr.cpp src/bellman_ford.cpp src/bf_driver.cpp -o bin/bf_driver.exe

# Compile Floyd-Warshall Binary
g++ -std=c++17 -O2 -Wall -Wextra -Iinclude src/floyd_warshall.cpp src/fw_driver.cpp -o bin/fw_driver.exe
```

### Execution Commands

```powershell
# Run Bellman-Ford
.\bin\bf_driver.exe tests\bf_10.txt

# Run Floyd-Warshall
.\bin\fw_driver.exe tests\fw_10.txt
```

---

## 3. Algorithm Implementation & Timing Rules

1. **Timer Placement Guardrail**: Precision timing (`std::chrono::high_resolution_clock`) strictly measures algorithm execution. File I/O, parsing, dynamic allocation, and CSR array conversions are executed outside the timed block as preprocessing steps.
2. **Clock Granularity Averaging**: Execution runtimes under 5.0 ms are automatically executed across a 100-iteration loop and averaged to prevent system clock precision noise.
3. **Graph Structures**: Adjacency list input files are preprocessed into Compressed Sparse Row (CSR) format (`row_ptr`, `col_ind`, `weights`). Floyd-Warshall reads dense V x V matrices directly.

---

## 4. Benchmark Performance Results

### Bellman-Ford Algorithm

| Graph Name | Vertices (V) | Edges (E) | Execution Time | Output / Status |
| :--- | :--- | :--- | :--- | :--- |
| `bf_10.txt` | 10 | 20 | 0 ms | Valid |
| `bf_100.txt` | 100 | 200 | 0 ms | Valid |
| `bf_1000.txt` | 1000 | 2000 | 0 ms | Valid |
| `bf_10000.txt` | 10000 | 20000 | 0 ms | Valid |
| `bf_50000.txt` | 50000 | 100000 | 0 ms | Valid |
| `bf_100000.txt` | 100000 | 200000 | 3.5790 ms | Valid |

---

### Floyd-Warshall Algorithm

| Matrix Name | Vertices (V) | Execution Time | Output / Status |
| :--- | :--- | :--- | :--- |
| `fw_10.txt` | 10 | 0 ms | Valid |
| `fw_100.txt` | 100 | 0 ms | Valid |
| `fw_500.txt` | 500 | 2792.7 ms | Valid |
| `fw_1000.txt` | 1000 | 59581.034 ms | Valid |
