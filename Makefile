CXX = g++
CXXFLAGS = -g -Wall

all: icsh.h icsh.cpp runner.cpp
	$(CXX) $(CXXFLAGS) icsh.cpp -o icsh