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
#include <fcntl.h>

// DEALING WITH SIGNALS
#include <signal.h>

using namespace std;

// MILESTONE 1
string commandLine; // the whole line of the command
string command; // just the first word of the command
string oldLine; // old line

// new way to run old commands
string oldcommand;

// ofstream prevcmdw; // file of previous command but write only
// ifstream prevcmdr; // file of prev command but read only

// MILESTONE 2
ifstream script; // read only for script file

// MILESTONE 3
string prompt; // changing to a variable prompt for consistency

// MILESTONE 4
struct sigaction default_action; // sig handler for default stuff
struct sigaction chld_action; // sig handler for children
// struct sigaction ignore;
// struct sigaction sigint_action;
// struct sigaction sigstop_action;
int last_status; // for echo $?
pid_t shell_id;

// MILESTONE 5
int redir_flag; // checks if there is need to redirect

// MILESTONE 6
bool background;
class job {
public:
    int jid;
    string cmd;
    string stat;
    // string age;
    int jpid;
    job* next;
};

// MILESTONE 7
string username; // get username of user