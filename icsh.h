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
string commandLine; // the whole line of the command
string command; // just the first word of the command
int exit_code;
string oldLine;
ofstream prevcmdw;
ifstream prevcmdr;

// MILESTONE 2
ifstream script;
int i;
