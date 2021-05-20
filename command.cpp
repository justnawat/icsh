void exe(string commandLine) {
    stringstream word(commandLine);
    int my_argc = 0;
    
    // counts the number of arguments 
    for (unsigned int i = 0; i <= commandLine.length(); i++) {
        if (commandLine[i] == ' ' || commandLine[i] == '\0')
            my_argc++;
    }
    
    // makes an array of C++ strings
   string arr[my_argc+1];
    for (int i = 0; i < my_argc; i++)
        word >> arr[i];

    // makes an array of C strings
    char * argv[my_argc+1];
    for (int i = 0; i < my_argc; i++)
        argv[i] = const_cast <char *> (arr[i].c_str());
    argv[my_argc] = NULL;
    execvp(argv[0], argv);
}

void echo(string commandLine) {
    stringstream word(commandLine);
    word >> command;
    while (word >> command) {
        cout << command << " ";
        prevcmdw << command << " ";
        }   
    prevcmdw.close();
    cout << endl;
}

 
void my_exit(string commandLine, int mode) {
    int exit_code;
    stringstream word(commandLine);
    word >> command;
    if (word >> command) exit_code = stoi(command) & 0xff;
    else exit_code = 0;
    remove(".pcmd.txt");
    if (mode == 0) cout << "Bye! See you later!\n";
    exit(exit_code);
}

void dbrun(string commandLine, int mode) {
	stringstream word(commandLine);
	word >> command;
	if (command == "echo") echo(commandLine);
	else if (command == "exit") my_exit(commandLine, mode);
	else { // will run external commands
		pid_t pid = fork();

		if (pid < 0) { // fork failed
			cout << "icsh: forking failed\n";
		} 
		else if (pid == 0) { // child process
			exe(commandLine);

            // only for if the exec command fails
			cout << "icsh: command not found\n";
			exit(127);
		}
		else { // parent process
			waitpid(pid, NULL, 0);
		}
    }	
}

void doubleBang(int mode) {
    if (prevcmdr.is_open()) {
        getline(prevcmdr, oldLine);
        if (mode == 0) cout << oldLine << endl;
        dbrun(oldLine, mode);
    } else {
        if (mode == 0) cout << "icsh: command not found\n";
    }
    prevcmdr.close();
}

void run(string commandLine, int mode) {
	stringstream word(commandLine);
	word >> command;
	if (command == "!!") prevcmdr.open(".pcmd.txt");
	else if (command == "exit"); // doesn't open previous command file becuase it's exiting
	else {
		prevcmdw.open(".pcmd.txt");
		prevcmdw << commandLine << endl;
	    prevcmdw.close();
    }

	if (command == "echo") echo(commandLine);
	else if (command == "!!") doubleBang(mode);
	else if (command == "exit") my_exit(commandLine, mode);
	else { // will run external commands
		pid_t pid = fork();

		if (pid < 0) { // fork failed
			cout << "icsh: forking failed\n";
		} 
		else if (pid == 0) { // child process
			exe(commandLine);

            // only for if the exec command fails
			cout << "icsh: command not found\n";
			exit(127);
		}
		else { // parent process
            int status;
			waitpid(pid, &status, 0);
		}
	}
    if (mode == 0) cout << prompt;
}
