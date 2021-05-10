CXX = g++
CXXFLAGS = -g -Wall

all: icsh.cpp icsh.h
	$(CC) $(CFLAGS) icsh.cpp -o icsh