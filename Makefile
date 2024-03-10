CXX := g++
CXXFLAGS := -std=c++23 -Wall -Werror -Wextra -pedantic -O3 -march=native

TARGET := main

SRC := src/main.cpp src/EmployeeManagementSystem.cpp
OBJ := $(SRC:.cpp=.o)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -f $(OBJ) $(TARGET)