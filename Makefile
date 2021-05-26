CXX = g++
CXXFLAGS = -g -Wall -O

all: icsh.h icsh.cpp command.cpp redirect.cpp
	$(CXX) $(CXXFLAGS) icsh.cpp -o icsh
