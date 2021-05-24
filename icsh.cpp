#include "icsh.h"
#include "command.cpp"

string trim(string st) {
	while (st.substr(0, 1) == " ") {
		st = st.substr(1, st.length() - 1);
	}

	return st;
}

int main(int argc, char * argv[]) {
	last_status = 0;

    // default handling just setting up
	default_action.sa_handler = SIG_IGN;
	sigemptyset(&default_action.sa_mask);
	default_action.sa_flags = 0;	

	// start by ignoring all signals
	sigaction(SIGTTOU, &default_action, NULL);
	sigaction(SIGINT, &default_action, NULL);
	sigaction(SIGTSTP, &default_action, NULL);

	// for SIGCHLD at the start
	chld_action.sa_handler = chld_handler;
	sigemptyset(&chld_action.sa_mask);
	chld_action.sa_flags = 0;
	sigaction(SIGCHLD, &chld_action, NULL);

	shell_id = getpid(); // get the pid of the shell
	setpgid(0, shell_id); // set the process group of the shell to its own pid

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
