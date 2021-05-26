int reout_pos(string commmandLine) {
	int pos = -1;
	for (unsigned int i = 0; i < commandLine.length(); i++) {
		if (commandLine[i] == '>') {
			pos = i;
			// cout << "pos: " << pos << endl;
			break;
		}
	}

	return pos;
}

int rein_pos(string commandLine) {
	int pos = -1;
	for (unsigned int i = 0; i < commandLine.length(); i++) {
		if (commandLine[i] == '<') {
			pos = i;
			// cout << "pos: " << pos << endl;
			break;
		}
	}
	
	return pos;
}

int redirc(string commandLine) {
	string red_command;
	int red_argc = 0;
	int reinc = 0;
	int reoutc = 0;

	// counts the number of arguments and the number of redirection arguments
	for (unsigned int i = 0; i < commandLine.length(); i++) {
		if (commandLine[i] == ' ' || commandLine[i] == '\n') {
			red_argc++;
		} else if (commandLine[i] == '<') {
			reinc++;
		} else if (commandLine[i] == '>') {
			reoutc++;
		}
		if (reinc > 1 || reoutc > 1) return -1;
	}
	// red_argc = red_argc + 1;

	// flip the bits for the redirection indicators
	int ret = 0;
	if (reinc) ret = ret | 0b01;
	if (reoutc) ret = ret | 0b10;

	// if any of the redirection is the last argument, it fails
	if (reinc) {
		if ((unsigned int) rein_pos(commandLine) >= commandLine.length()) {
			// cout << "redirection last arg\n";
			return -1;
		}
	}
	
	if (reoutc) {
		if ((unsigned int) reout_pos(commandLine) >= commandLine.length()) {
			// cout << "redirection last arg\n";
			return -1;
		}
	}

	// creates an array of strings
	stringstream word(commandLine);
	string all_arg[red_argc];
	for (int i = 0; i < red_argc; i++) {
		word >> red_command;
		all_arg[i] = red_command;
		// cout << all_arg[i] << " ";
	}
	// cout << endl;

	// checks for < > next to each other
	for (int i = 0; i < red_argc; i++) {
		if (((all_arg[i] == "<") || (all_arg[i] == ">")) && (i+1 < red_argc)) {
			if (all_arg[i+1] == "<" || all_arg[i+1] == ">") {
				// cout << "err bc < bad argument\n";
				return -1;
			}
		}
	}

	if (ret == 0b11) { // if commandLine has both redirections
		if (rein_pos(commandLine) > reout_pos(commandLine)) { // < comes after > which is illegale
			// cout << "< after >\n";
			return -1;
		} else if (rein_pos(commandLine) == reout_pos(commandLine)+1 || reout_pos(commandLine) == rein_pos(commandLine)+1) {
			return -1;
		} else {
			return ret;
		}
	} else return ret;
}

string find_rein(string commandLine) {
	string ret;
	string find_command;
	stringstream word(commandLine);

	while (word >> find_command) {
		if (find_command == "<") {
			word >> find_command;
			ret = find_command;
			return ret;
		}
	}

	return ret;
}

string find_reout(string commandLine) {
	string ret;
	string find_command;
	stringstream word(commandLine);

	while (word >> find_command) {
		if (find_command == ">") {
			word >> find_command;
			ret = find_command;
			return ret;
		}
	}

	return ret;
}

