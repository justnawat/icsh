#include "redirect.cpp"
// #include "jobcont.cpp"

void chld_handler(int signum) {
	waitpid(-1, NULL, WNOHANG);
}

void echo(string commandLine) {
    stringstream word(commandLine);
    word >> command;
    while (word >> command) {
        if (command == "$?") { // supporting echo $? to get last exit status
            cout << last_status;
            break;
        }
        cout << command << " ";
        // prevcmdw << command << " ";
    }   
    // prevcmdw.close();
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
    if (mode == 0) cout << "\033[1;36mBye! See you later!\033[0m\n";
    // free(prevcmd);
    exit(exit_code);
}

void f_ex(string commandLine) {
    pid_t pid = fork();
    if (pid < 0) {
        cout << "\033[1;31micsh:\033[0m forking failed\n";
    } else if (pid == 0) {
        pid = getpid();
        setpgid(pid, pid); // put child process in its own process group
        tcsetpgrp(0, pid); // make child process the foreground process

        // for executing external commands in c++
        int my_argc = 0;
    
        // counts the number of arguments 
        for (unsigned int i = 0; i <= commandLine.length(); i++) {
            if (commandLine[i] == ' ' || commandLine[i] == '\0')
                my_argc++;
        }

        // makes an array of C++ strings
        stringstream word(commandLine);
        string sarr[my_argc+1];
        for (int i = 0; i < my_argc; i++)
            word >> sarr[i];

        // makes an array of C strings
        char * c_sarr[my_argc+1];
        for (int i = 0; i < my_argc; i++)
            c_sarr[i] = const_cast <char *> (sarr[i].c_str());
        c_sarr[my_argc] = NULL;

        // turn on signals
        default_action.sa_handler = SIG_DFL;
        sigaction(SIGTSTP, &default_action, NULL);
        sigaction(SIGINT, &default_action, NULL);

        // disables my SIGCHLD handler
        chld_action.sa_handler = SIG_IGN;
        sigaction(SIGCHLD, &chld_action, NULL); // reinstalls child handler

        execvp(c_sarr[0], c_sarr);

        cout << "\033[1;31micsh:\033[0m command not found\n";
        exit(127); // according to bash, this is the exit code when a command is not found
    } else {
        setpgid(pid, pid); // make sure the child process gets to control the terminal
        tcsetpgrp(0, pid);

        int status;
        waitpid(pid, &status, WUNTRACED);
        // cout << "wait successfully\n";
        tcsetpgrp(0, shell_id);

        // back to ignoring signals again
        default_action.sa_handler = SIG_IGN;
        sigaction(SIGTSTP, &default_action, NULL);
        sigaction(SIGINT, &default_action, NULL);
        
        // puts the chld_handler back in place
        chld_action.sa_handler = chld_handler;
        sigaction(SIGCHLD, &chld_action, NULL);

        if (WIFEXITED(status))
            last_status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            last_status = 130;
        else if (WIFSTOPPED(status))
            last_status = 146;
    }
}

void dbrun(string commandLine, int mode) {
	stringstream word(commandLine);
	word >> command;
	if (command == "echo") echo(commandLine);
	else if (command == "exit") my_exit(commandLine, mode);

    // else if (command == "jobs") myjob();
    // else if (command == "fg") make_foreground(commandLine);
    // else if (command == "bg") make_background(commandLine);

	else f_ex(commandLine); // will run external commands
}	

void doubleBang(int mode) {
    if (oldcommand.length() != 0) {
        if (mode == 0) cout << oldcommand << endl;
        dbrun(oldcommand, mode);
    } else {
        if (mode == 0) cout << "\033[1;31micsh:\033[1;31m command not found\n";
    }
}

void run(string commandLine, int mode) {

    // int fin_fd, fout_fd, saved_stdin, saved_stdout;
    // string fin_name, fout_name;

	stringstream word(commandLine);
	word >> command;
    if (!(command == "!!" || command == "exit")) oldcommand = commandLine;

	// if (command == "!!") prevcmdr.open(".pcmd.txt");
	// else if (command == "exit"); // doesn't open previous command file becuase it's exiting
	// else {
	// 	prevcmdw.open(".pcmd.txt");
	// 	prevcmdw << commandLine << endl;
	//     prevcmdw.close();
    // }

	if (command == "echo") echo(commandLine);
	else if (command == "!!") doubleBang(mode);
	else if (command == "exit") my_exit(commandLine, mode);

    // else if (command == "jobs") myjob();
    // else if (command == "fg") make_foreground(commandLine);
    // else if (command == "bg") make_background(commandLine);

    else f_ex(commandLine); // for external commands
}
