# Compiler g++.

CXX = g++

# Flags for the C++ compiler.

CXXFLAGS = -Wall -std=c++11

# Object files - created from *.cpp files.

OBJECTS = tests.o

# Header files - included in *.cpp files.

HFILES = skiplist.h

# Final executable file.

TARGET = skiplist.out

# Definition of the default pattern rule.

# $< represents the name of the first prerequisite.

# $@ represents the name of the target file.

# All object files depend on all header files.

# Indentations are done with TAB.

%.o : %.cpp $(HFILES) Makefile

	$(CXX) $(CXXFLAGS) -c $< -o $@ 

$(TARGET) : $(OBJECTS)

	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)
	
	./$(TARGET)

# Define phony targets.

.PHONY : clean

clean :

	$(RM) $(TARGET) *.o* core
