CXX = g++
CXXFLAGS = -g -Wall

all: icsh.h icsh.cpp
	$(CXX) $(CXXFLAGS) icsh.cpp -o icsh

