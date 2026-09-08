CXX      = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -Iinclude
SRC_DIR  = src
BIN_DIR  = bin

# Target executables
TARGETS = $(BIN_DIR)/color_driver.exe $(BIN_DIR)/pagerank_driver.exe

all: $(TARGETS)

# Vertex Coloring Build
$(BIN_DIR)/color_driver.exe: $(SRC_DIR)/color_driver.cpp $(SRC_DIR)/vertex_coloring.cpp $(SRC_DIR)/csr.cpp
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# PageRank Build
$(BIN_DIR)/pagerank_driver.exe: $(SRC_DIR)/pagerank_driver.cpp $(SRC_DIR)/pagerank.cpp $(SRC_DIR)/csr.cpp
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -rf $(BIN_DIR)/*.exe

.PHONY: all clean