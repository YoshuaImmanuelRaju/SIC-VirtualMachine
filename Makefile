# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

# Directories
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

# Source files
SRCS = $(SRC_DIR)/debugger.cpp \
       $(SRC_DIR)/execution.cpp \
       $(SRC_DIR)/memory.cpp \
       $(SRC_DIR)/disassembler.cpp \
       $(SRC_DIR)/symbols.cpp \
       $(SRC_DIR)/utils.cpp

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Executable name
EXEC = sic-debugger

# Default target
all: $(EXEC)

# Link object files to create the executable
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC)

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Clean up object files and the executable
clean:
	rm -f $(OBJ_DIR)/*.o $(EXEC)

# Run the debugger
run: $(EXEC)
	./$(EXEC)

# Rebuild everything
rebuild: clean all
