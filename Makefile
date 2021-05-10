CXX = g++
CXXFLAGS = -g -Wall

all: icsh.cpp icsh.h
	$(CXX) $(CXXFLAGS) icsh.cpp -o icsh