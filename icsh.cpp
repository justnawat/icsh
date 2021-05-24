#include "icsh.h"
#include "command.cpp"

string trim(string st) {
	while (st.substr(0, 1) == " ") {
		st = st.substr(1, st.length() - 1);
	}

	return st;
}

// void int_handler(int signum) {
// 	cout << "icsh: please exit shell properly and use the exit command.\n";
// }

// void stop_handler(int signum) {
// 	cout << "icsh: shell cannot be suspended\n";
// }

void chld_handler(int signum) {
	waitpid(-1, NULL, WUNTRACED);
}

int main(int argc, char * argv[]) {
	last_status = 0;

    // default handling just setting up
	default_action.sa_handler = SIG_IGN;
	// sigemptyset(&default_action.sa_mask);
	// default_action.sa_flags = 0;	

	// // for ignore
	// ignore.sa_handler = SIG_IGN;
	// sigemptyset(&ignore.sa_mask);
	// ignore.sa_flags = SA_NOCLDWAIT;
	// sigaction(SIGTTOU, &ignore, NULL);

	// start by ignoring all signals
	sigaction(SIGTTOU, &default_action, NULL);
	sigaction(SIGINT, &default_action, NULL);
	sigaction(SIGTSTP, &default_action, NULL);

	// for SIGCHLD
	chld_action.sa_handler = chld_handler;
	sigaction(SIGCHLD, &chld_action, NULL);

    // // for SIGINT
    // sigint_action.sa_handler = int_handler;
    // sigemptyset(&sigint_action.sa_mask);
    // sigint_action.sa_flags = 0;
	// sigaction(SIGINT, &sigint_action, NULL);
    
	// // for SIGTSTP
	// sigstop_action.sa_handler = stop_handler;
	// sigemptyset(&sigstop_action.sa_mask);
	// sigstop_action.sa_flags = 0;
	// sigaction(SIGTSTP, &sigstop_action, NULL);

	if (argc == 1) { // runs in interactive mode
		cout << "Initiliazing IC Shell...";
		cout << endl << prompt;

		while (1) {
			getline(cin, commandLine); // get a line from the command line
			if (commandLine.length() == 0) {
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
