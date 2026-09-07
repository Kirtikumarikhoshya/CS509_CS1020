CXX      := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Iinclude
BIN_DIR  := bin
SRC_DIR  := src

# Target executable (Windows: .exe extension)
TARGET   := $(BIN_DIR)/mst_driver.exe

# Source files matching your ASSIGNMENT_03/src layout
SRCS     := $(SRC_DIR)/csr.cpp \
            $(SRC_DIR)/kruskal.cpp \
            $(SRC_DIR)/prim.cpp \
            $(SRC_DIR)/mst_driver.cpp

# Default rule
all: $(TARGET)

# Link & compile the executable
$(TARGET): $(SRCS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Clean compiled binaries and intermediate files
clean:
	rm -rf $(BIN_DIR)/*.exe *.o

.PHONY: all clean