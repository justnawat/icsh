#include "icsh.h"
#include "command.cpp"

string trim(string st) {
	while (st.substr(0, 1) == " ") {
		st = st.substr(1, st.length() - 1);
	}

	return st;
}


void int_handler(int signum) {
}

void stop_handler(int signum) {
}

void chld_handler(int signum) {
}

int main(int argc, char * argv[]) {
    // signal handling
    struct sigaction old_action;

    // for SIGINT
    struct sigaction sigint_action;
    sigint_action.sa_handler = int_handler;
    sigemptyset(&sigint_action.sa_mask);
    sigint_action.sa_flags = 0;
    sigaction(SIGINT, NULL, &old_action);
    if (old_action.sa_handler != SIG_IGN) sigaction(SIGINT, &sigint_action, NULL);
    
    // for SIGSTOP
    struct sigaction sigstop_action;
    sigstop_action.sa_handler = stop_handler;
    sigemptyset(&sigstop_action.sa_mask);
    sigstop_action.sa_flags = 0; 
    sigaction(SIGSTOP, NULL, &old_action);
    if (old_action.sa_handler != SIG_IGN) sigaction(SIGSTOP, &sigstop_action, NULL);
    
    // for SIGCHLD
    struct sigaction sigchld_action;
    sigchld_action.sa_handler = chld_handler;
    sigemptyset(&sigchld_action.sa_mask);
    sigchld_action.sa_flags = 0;
    sigaction(SIGCHLD, NULL, &old_action);
    if (old_action.sa_handler != SIG_IGN) sigaction(SIGCHLD, &sigchld_action, NULL);

	if (argc == 1) { // runs in interactive mode
		cout << "Initiliazing IC Shell...\n";
		cout << prompt;

		while (1) {
			getline(cin, commandLine); // get a line from the command line
			if(commandLine.length() == 0) {
				cout << prompt;
				continue;
			}

			if (commandLine.substr(0, 1) == " ") commandLine = trim(commandLine); // trim leading spaces

			else { // not empty command
				run(commandLine, 0);
			}
		}
	} else { // runs in script mode
		script.open(argv[1]);
		if (!script.is_open()) {
			cout << "icsh: script not found\n";
			exit(127);
		} else {
			while (getline(script, commandLine)) {
				if (commandLine.length() == 0) continue;
				if (commandLine.substr(0, 1) == " ") commandLine = trim(commandLine);
				if (commandLine.substr(0, 1) == "#") continue; // skips comments
				run(commandLine, 1);
			}
			
			// deleting the previous command file
			// just in case that there's no exit call in the script
            prevcmdr.open(".pcmd.txt");
			if (prevcmdr.is_open()) {
				prevcmdr.close();
				remove(".pcmd.txt");
			}

			exit(0);
		}
	}

	return 0;
}
