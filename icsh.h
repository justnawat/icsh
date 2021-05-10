// THE BASIC STUFF
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// DEALING WITH FILES
#include <fstream>

// DEALING WITH STRINGS
#include <string.h>
#include <string>
#include <sstream>
using namespace std;

// MILESTONE 1
string commandLine; // the whole line of the input command
string command;
int exit_code;
string oldLine;
ofstream prevcmdw;
ifstream prevcmdr;

/* REFERENCES
- https://www.geeksforgeeks.org/how-to-split-a-string-in-cc-python-and-java/
- https://www.geeksforgeeks.org/comparing-two-strings-cpp/
- https://www.tutorialspoint.com/cplusplus/cpp_strings.htm
- https://stackoverflow.com/questions/11821491/converting-string-to-cstring-in-c
- https://www.bitdegree.org/learn/string-to-int-c-plus-plus
*/