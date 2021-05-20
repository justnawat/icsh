CXX = g++
CXXFLAGS = -g -Wall

all: icsh.h icsh.cpp command.cpp
	$(CXX) $(CXXFLAGS) icsh.cpp -o icsh

