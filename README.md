 CS509 - INDIVIDUAL ASSIGNMENT 1

Name: Kirti Kumari

Entry No: 2026CSM1020

Repository:CS509_CS1020

Language:C++

Environment: Windows (PowerShell) / GCC 9+ (g++) with -O2 optimization


Directory Structure:

```text
CS509_CS1020/
├── ASSIGNMENT_01/
│   ├── include/          # Headers (csr_graph.hpp, gemm.hpp, matrix_io.hpp, timer.hpp)
│   ├── src/              # Source & executables (driver.cpp, driver.exe, csr_runner.cpp, csr_runner.exe)
│   ├── gemm/             # Input matrix test files
│   ├── csr_test/         # Input graph test files
│   └── outputs/          # Benchmark outputs
├── wrapper.cpp           # Interactive CLI menu source
├── wrapper.exe           # Interactive CLI menu executable
└── README.md             # Project documentation
```




Compilation:

Build all targets using `g++` (C++17, `-O2`) from the root directory:

```powershell
g++ -std=c++17 -O2 -I ASSIGNMENT_01/include ASSIGNMENT_01/src/driver.cpp ASSIGNMENT_01/src/gemm_simple.cpp ASSIGNMENT_01/src/gemm_blocking.cpp -o ASSIGNMENT_01/src/driver.exe
g++ -std=c++17 -O2 -I ASSIGNMENT_01/include ASSIGNMENT_01/src/csr_runner.cpp -o ASSIGNMENT_01/src/csr_runner.exe
g++ -std=c++17 -O2 wrapper.cpp -o wrapper.exe
```


Execution:

Running interactive launcher:
```powershell
.\wrapper.exe
```

Input Paths:
- **GEMM Test:** `ASSIGNMENT_01/gemm/gemm_test_01.txt`
- **CSR Test:** `ASSIGNMENT_01/csr_test/csr_test_01.txt`

Output Piping:
```powershell
.\ASSIGNMENT_01\src\driver.exe ASSIGNMENT_01/gemm/gemm_test_01.txt > ASSIGNMENT_01/outputs/gemm_test_01_output.txt
.\ASSIGNMENT_01\src\csr_runner.exe ASSIGNMENT_01/csr_test/csr_test_01.txt > ASSIGNMENT_01/outputs/csr_test_01_output.txt
```

---

Experimental Results:

GEMM Performance (Block Size B = 64)

| Test File | Size (N x N) | Simple GEMM | Blocking GEMM | Speedup | Correctness |
| :--- | :---: | :---: | :---: | :---: | :---: |
| `gemm_test_01.txt` | 10 x 10 | 0.012 ms | 0.015 ms | 0.80x | Matched |
| `gemm_test_02.txt` | 50 x 50 | 0.420 ms | 0.280 ms | 1.50x | Matched |
| `gemm_test_03.txt` | 100 x 100 | 3.150 ms | 1.820 ms | 1.73x | Matched |
| `gemm_test_04_100.txt` | 100 x 100 | 3.120 ms | 1.810 ms | 1.72x | Matched |
| `gemm_test_05_1000.txt` | 1000 x 1000 | 2850.000 ms | 890.000 ms | 3.20x | Matched |

CSR Graph Conversion:

| Test File | Vertices (V) | Edges (E) | Conversion Time | Output File |
| :--- | :---: | :---: | :---: | :--- |
| `csr_test_01.txt` | 6 | 7 | 0.045 ms | `outputs/csr_test_01_output.txt` |
| `csr_test_02.txt` | 5 | 7 | 0.052 ms | `outputs/csr_test_02_output.txt` |