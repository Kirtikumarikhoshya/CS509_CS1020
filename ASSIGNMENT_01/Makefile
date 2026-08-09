CXX := g++
CXXFLAGS := -std=c++17 -02 -Wall -Wextra -Iinclude

GEMM_SRC := src/driver.cpp src/gemm_simple.cpp
GEMM_BIN:= driver

CSR_SRC := src/csr_runner.cpp
CSR_BIN := csr_runner

.PHONY: all clean run

all: $(GEMM_BIN) $(CSR_BIN)

$(GEMM_BIN): $(GEMM_SRC) include/matrix_io.hpp include/gemm.hpp include/timer.hpp include/csr_graph.hpp $(CXX) $(CXXFLAGS) $(GEMM_SRC) -o $(GEMM_BIN)

$(CSR_BIN): $(CSR_SRC) include/csr_graph.hpp include/timer.hpp $(CXX) $(CXXFLAGS) $(CSR_SRC) -o $ (CSR_BIN)
run: $(BIN)
     ./$(BIN) tests/gemm/gemm_test_01.txt

clean:
rm -f $(GEMM_BIN) $(CSR_BIN) *.o

