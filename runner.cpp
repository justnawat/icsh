int command_run(string commandLine, int mode) {
    stringstream word(commandLine); // makes the line of the command a stream of strings
    word >> command; // puts the content of word into command
    if (command != "!!") { // if the command is not !!
        prevcmdw.open(".last_command.txt"); // writes to hidden file that saves prev commands
        prevcmdw << commandLine << endl; // writes the whole line of the command to the file
    } else { // the command is !!
        prevcmdr.open(".last_command.txt"); // read from the hidden file
    }

    /* MILESTONE 1 */

    // THE ECHO COMMAND
    if (command == "echo") {
        while (word >> command) { // as long as there are strings left
            if ((command.substr(0, 1) == "#") && (mode == 1)) break; // skip comments in script
            cout << command << " "; // prints it out on screen
            prevcmdw << command << " "; // put it in the hidden file
        }
        cout << endl;
        prevcmdw.close(); // close the file
    }

    // THE !! COMMAND
    else if (command == "!!") {
        if (getline(prevcmdr, oldLine)) { // prev command exists
            if (oldLine.length() == 0) cout << "icsh: !!: event not found" << endl; // no old command
            else {
                if (mode == 0) cout << oldLine << endl; // only tells which command it is if it's not in script mode
                while (getline(prevcmdr, oldLine)) { // gets a line from the hidden file
                    cout << oldLine << endl; // prints out the line
                }
            }
        } else {
            cout << "icsh: !!: event not found" << endl;
        }
        prevcmdr.close(); // closes the file
    }

    // THE EXIT COMMAND
    else if (command == "exit") {
        prevcmdw.close(); // closes the file
        if (word >> command) exit_code = stoi(command) & 0xff; // exit code specified
        else exit_code = 0;
        remove(".last_command.txt"); // delete the previous command file
        if (mode == 0) cout << "bye\n"; // only shows up in interactive mode
        exit(exit_code); // exits with the exit code
    }

    // EMPTY COMMAND
    else if ((command.substr(0, 1) == "\n") || (command.length() == 0)) {
        prevcmdw.close();
    }

    // BAD COMMAND
    else {
        prevcmdw << "BAD COMMAND"; // writes to the file that the last command is a bad one
        cout << "BAD COMMAND" << endl;
        prevcmdw.close(); // closes the file
    }

    return 0;
}

