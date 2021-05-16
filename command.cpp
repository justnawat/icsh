void run(string commandLine, int mode) {
	stringstream word(commandLine);
	word >> command;
	if (command == "!!") prevcmdr.open(".pcmd.txt");
	else if (command == "exit"); // doesn't open previous command file becuase it's exiting
	else {
		prevcmdw.open(".pcmd.txt");
		if (mode == 0) prevcmdw << commandLine << endl;
	}

	/* MILESTONE 1 */
	if (command == "echo") {
		while (word >> command) {
			cout << command << " ";
			prevcmdw << command << " ";
		}

		prevcmdw.close();
		cout << endl;
		if (mode == 0) cout << "icsh $ ";
	}

	else if (command == "!!") {
		if (prevcmdr.is_open()) {
			while (getline(prevcmdr, oldLine)) 
				cout << oldLine << endl;
		}
		else {
			if (mode == 0) cout << "icsh: command not found\n";
		}

		prevcmdr.close();
		if (mode == 0) cout << "icsh $ ";
	}

	else if (command == "exit") {
		if (word >> command) exit_code = stoi(command) & 0xff;
		else exit_code = 0;
		remove(".pcmd.txt");
		if (mode == 0) cout << "Bye! See you later!\n";
		exit(exit_code);
	}

	else {
		if (mode == 0) { // only indicates that there is a bad command only if it's in interactive mode (or I'd go crazy otherwise)
			prevcmdw << "icsh: bad command\n";
			cout << "icsh: bad command\n";
			cout << "icsh $ ";
		}

		prevcmdw.close();
	}
}
