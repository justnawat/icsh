CC = g++
CFLAGS = -g -Wall

all: icsh.cpp icsh.h
	$(CC) $(CFLAGS) icsh.cpp -o icsh