CXX = g++
CXXFLAGS = -std=c++17 -Wall

SRC = src/main.cpp src/sic_vm.cpp src/debugger.cpp
OBJ = $(SRC:.cpp=.o)

TARGET = sic_debugger

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

clean:
	rm -f $(OBJ) $(TARGET)
