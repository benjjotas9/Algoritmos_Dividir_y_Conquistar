# Define the C++ compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# List of source files
SOURCES = cubico_optimizado.cpp cubico.cpp strassen.cpp

# List of object files
OBJECTS = $(SOURCES:.cpp=.o)

# List of executables
EXECUTABLES = cubico_optimizado cubico strassen

# Default target to build all executables
all: $(EXECUTABLES)

# Rule for building each executable
cubico_optimizado: cubico_optimizado.o
	$(CXX) $(CXXFLAGS) -o $@ $^

cubico: cubico.o
	$(CXX) $(CXXFLAGS) -o $@ $^

strassen: strassen.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to build object files from source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Clean rule to remove all generated files
clean:
	rm -f $(OBJECTS) $(EXECUTABLES)
