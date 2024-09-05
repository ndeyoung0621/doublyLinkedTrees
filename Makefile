# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++14

# Target executable
TARGET = my_program

# Test executable
TEST_TARGET = test_program

# Source files
SRCS = main.cpp linkedList.cpp

# Test source files 
TEST_SRCS = unitTests.cpp linkedList.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Test object files
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Default target to build the executable
all: $(TARGET)

# Rule to link object files and create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to build and run tests
tests: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)

# Rule to compile C++ source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Run the tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)