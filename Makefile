# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Raylib paths (update these based on your setup)
RAYLIB_FLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Source files and build directory
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TARGET = $(BIN_DIR)/raylib_demo

# Collect all source files recursively and their corresponding object files
SRCS = $(wildcard $(SRC_DIR)/**/*.cpp $(SRC_DIR)/**/**/*.cpp $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Default target
all: $(TARGET)

# Create binary target
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(RAYLIB_FLAGS)

# Create object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D) # Ensure obj directories are created
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean the build
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Build, run, and clean
dev: $(TARGET)
	./$(TARGET)
	$(MAKE) clean

# Phony targets
.PHONY: all clean run dev
