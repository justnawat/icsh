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
string command; // the whole line of the input command
const char * ccmd; // the whole line of the input command but in C-style string form
char * word; // for each word of command line
ofstream prevcmd; // saves the previous command
int exit_code; // saves the exit code
char * lastout;