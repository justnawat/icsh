// THE BASIC STUFF
#include <cstdio>
#include <cstdlib>
#include <iostream>

// DEALING WITH FILES
#include <fstream>

// DEALING WITH STRINGS
#include <string.h>
#include <string>
#include <sstream>

// DEALING WITH SYSTEM CALLS
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cerrno>

// DEALING WITH SIGNALS
#include <signal.h>

using namespace std;

// MILESTONE 1
string commandLine; // the whole line of the command
string command; // just the first word of the command
string oldLine;
ofstream prevcmdw;
ifstream prevcmdr;

// MILESTONE 2
ifstream script;

// MILESTONE 3
string prompt = "icsh $ ";

// MILESTONE 4
struct sigaction default_action;
struct sigaction chld_action;
// struct sigaction ignore;
// struct sigaction sigint_action;
// struct sigaction sigstop_action;

int last_status;
pid_t shell_id;
