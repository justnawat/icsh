#include "icsh.h"

string trim(string st) {
	while (st.substr(0, 1) == " ") {
		st = st.substr(1, st.length() - 1);
	}

	return st;
}

int main() {
	cout << "Initiliazing IC Shell...\n";
	cout << "icsh $ ";

	while (1) {
		getline(cin, commandLine); // get a line from the command line
		if (commandLine.substr(0, 1) == " ") commandLine = trim(commandLine); // trim leading spaces
		if (commandLine.length() == 0) { // empty command
			cout << "icsh $ ";
		} 

		else { // not empty command
			stringstream word(commandLine); // make the command line into a stream of strings
			word >> command;

			if (command == "echo") { // echo command
				prevcmdw.open(".pcmd.txt");
				prevcmdw << commandLine << endl;

				while (word >> command) {
					cout << command << " ";
					prevcmdw << command << " ";
				}

				prevcmdw.close();
				cout << endl  << "icsh $ ";
			} 

			else if (command == "!!") { // repeat command
				prevcmdr.open(".pcmd.txt");
				if (prevcmdr.is_open()) {
					while (getline(prevcmdr, oldLine)) {
						cout << oldLine << endl;
					}
				} else {
					cout << "icsh: command not found\n";
				}
				
				prevcmdr.close();
				cout << "icsh $ ";
			} 

			else if (command == "exit") { // exit command
				if (word >> command) exit_code = stoi(command) & 0xff;
				else exit_code = 0;
				remove(".pcmd.txt");
				exit(exit_code);
			}

			else {
				prevcmdw.open(".pcmd.txt");
				prevcmdw << commandLine << endl << "icsh: bad command\n";
				prevcmdw.close();
				cout << "icsh: bad command\n";
				cout << "icsh $ ";
			}
		}
	}

	return 0;
}
