#include "icsh.h"
#include "command.cpp"

string trim(string st) {
	while (st.substr(0, 1) == " ") {
		st = st.substr(1, st.length() - 1);
	}

	return st;
}

int main(int argc, char * argv[]) {
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
