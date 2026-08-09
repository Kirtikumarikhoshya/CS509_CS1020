CXX      := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Iinclude

# Directory paths
SRC_DIR  := src
INC_DIR  := include
BIN_DIR  := bin
TEST_DIR := tests

# Target Executables
BF_BIN   := $(BIN_DIR)/bf_driver
FW_BIN   := $(BIN_DIR)/fw_driver

.PHONY: all clean directories run_bf run_fw

# Default target builds all binaries
all: directories $(BF_BIN)

directories:
	@mkdir -p $(BIN_DIR)

# ---------------------------------------------------------------------
# Individual Algorithms Compilations
# ---------------------------------------------------------------------

# Bellman-Ford Driver (Individual Task)
$(BF_BIN): $(SRC_DIR)/csr.cpp $(SRC_DIR)/bellman_ford.cpp $(SRC_DIR)/bf_driver.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

# Floyd-Warshall Driver (Individual Task)
$(FW_BIN): $(SRC_DIR)/floyd_warshall.cpp $(SRC_DIR)/fw_driver.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

	# Run Bellman-Ford with test input
run_bf: $(BF_BIN)
	./$(BF_BIN) $(TEST_DIR)/bf_10.txt

# Run Floyd-Warshall with test input
run_fw: $(FW_BIN)
	./$(FW_BIN) $(TEST_DIR)/fw_10.txt

clean:
	rm -rf $(BIN_DIR) *.o