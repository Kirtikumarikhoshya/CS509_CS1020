CXX := g++
CXXFLAGS := -std=c++17 -02 -Wall -Wextra -Iinclude

SRC := src/driver.cpp src/gemm_simple.cpp
BIN:= driver

.PHONY: all clean run

all: $(BIN)

$(BIN): $(SRC) include/matrix_io.hpp include/gemm.hpp include/timer.hpp $(CXX) $(CXXFLAGS) $(SRC) -O $(BIN)

run: $(BIN)
     ./$(BIN) tests/gemm/gemm_test_01.txt

clean:
rm -f $(BIN)

