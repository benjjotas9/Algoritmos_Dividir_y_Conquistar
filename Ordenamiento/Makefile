# Define the C++ compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# List of source files
SOURCES = bubble_sort.cpp intro_sort.cpp merge_sort.cpp quick_sort.cpp

# List of object files
OBJECTS = $(SOURCES:.cpp=.o)

# List of executables
EXECUTABLES = bubble_sort intro_sort merge_sort quick_sort

# Default target to build all executables
all: $(EXECUTABLES)

# Rule for building each executable
bubble_sort: bubble_sort.o
	$(CXX) $(CXXFLAGS) -o $@ $^

intro_sort: intro_sort.o
	$(CXX) $(CXXFLAGS) -o $@ $^

merge_sort: merge_sort.o
	$(CXX) $(CXXFLAGS) -o $@ $^

quick_sort: quick_sort.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to build object files from source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Clean rule to remove all generated files
clean:
	rm -f $(OBJECTS) $(EXECUTABLES)
