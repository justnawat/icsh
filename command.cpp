void echo(string commandLine) {
    stringstream word(commandLine);
    word >> command;
    while (word >> command) {
        if (command == "$?") { // supporting echo $? to get last exit status
            cout << last_status;
            break;
        }
        cout << command << " ";
        prevcmdw << command << " ";
    }   
    prevcmdw.close();
    last_status = 0;
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

void f_ex(string commandLine) {
    pid_t pid = fork();
    if (pid < 0) {
        cout << "icsh: forking failed\n";
    } else if (pid == 0) {
        pid = getpid();
        setpgid(pid, pid); // put child process in its own process group
        tcsetpgrp(0, pid); // make child process the foreground process

        // for executing external commands in c++
        stringstream word(commandLine);
        int my_argc = 0;
    
        // counts the number of arguments 
        for (unsigned int i = 0; i <= commandLine.length(); i++) {
            if (commandLine[i] == ' ' || commandLine[i] == '\0')
                my_argc++;
        }

        // makes an array of C++ strings
        string sarr[my_argc+1];
        for (int i = 0; i < my_argc; i++)
            word >> sarr[i];

        // makes an array of C strings
        char * c_sarr[my_argc+1];
        for (int i = 0; i < my_argc; i++)
            c_sarr[i] = const_cast <char *> (sarr[i].c_str());
        c_sarr[my_argc] = NULL;

        // turn on signals
        sigaction(SIGTSTP, &default_action, NULL);
        sigaction(SIGINT, &default_action, NULL);

        execvp(c_sarr[0], c_sarr);

        // only if the exec command doesn't work
        cout << "icsh: command not found\n";
        exit(127); // according to bash, this is the exit code when a command is not found
    } else {
        setpgid(pid, pid); // make sure the child process gets to control the terminal
        tcsetpgrp(0, pid);

        int status;
        waitpid(pid, &status, WUNTRACED);
        tcsetpgrp(0, getpid());
        if (WIFEXITED(status))
            last_status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            last_status = 130;
        else if (WIFSTOPPED(status))
            last_status = 146;

        // back to ignoring signals again
        sigaction(SIGTSTP, &ignore, NULL);
        sigaction(SIGINT, &ignore, NULL);
    }
}

void dbrun(string commandLine, int mode) {
	stringstream word(commandLine);
	word >> command;
	if (command == "echo") echo(commandLine);
	else if (command == "exit") my_exit(commandLine, mode);
	else f_ex(commandLine); // will run external commands
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
    else f_ex(commandLine); // for external commands
    if (mode == 0) cout << prompt;
}
