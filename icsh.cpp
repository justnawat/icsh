#include "icsh.h"

// void save_cmd(string command) { // saves the last command in a file
//     ofstream prevcmdw(".last_command.txt"); // opens a file to write previous command to it
//     prevcmdw << command << endl; // writes the line of command
//     prevcmdw.close(); // closes the file
// }

int main() {
    cout << "Initializing IC Shell..." << endl;
    cout << "icsh $ ";

    while (1) {
        getline(cin, commandLine); // gets the whole line of the command as string
        
        stringstream word(commandLine); // makes the line of the command a stream of strings
        word >> command; // puts the content of word into command
        if (command != "!!") { // if the command is not !!
            prevcmdw.open(".last_command.txt"); // writes to hidden file that saves prev commands
            prevcmdw << commandLine << endl; // writes the whole line of the command to the file
        } else { // the command is !!
            prevcmdr.open(".last_command.txt"); // read from the hidden file
        }

        // THE ECHO COMMAND
        if (command == "echo") {
            while (word >> command) { // as long as there are strings left
                cout << command << " "; // prints it out on screen
                prevcmdw << command << " "; // put it in the hidden file
            }
            prevcmdw.close(); // close the file
            cout << endl << "icsh $ "; // prompts user for the next command
        }

        // THE !! COMMAND
        else if (command == "!!") {
            if (getline(prevcmdr, oldLine)) { // prev command exists
                if (oldLine.length() == 0) cout << "icsh: !!: event not found" << endl;
                else {
                    cout << oldLine << endl;
                    while (getline(prevcmdr, oldLine)) { // gets a line from the hidden file
                        cout << oldLine << endl; // prints out the line
                    }
                }
            } else {
                cout << "icsh: !!: event not found" << endl;
            }
            prevcmdr.close(); // closes the file
            cout << "icsh $ "; // prompts for next command
        }

        // THE EXIT COMMAND
        else if (command == "exit") {
            prevcmdw.close(); // closes the file
            if (word >> command) exit_code = stoi(command) & 0xff; // exit code specified
            else exit_code = 0;
            remove(".last_command.txt"); // delete the previous command file
            cout << "exit\n";
            exit(exit_code); // exits with the exit code
        }

        // EMPTY COMMAND
        else if (command.length() == 0) {
            prevcmdw.close();
            cout << "icsh $ ";
        }

        // BAD COMMAND
        else {
            prevcmdw << "BAD COMMAND"; // writes to the file that the last command is a bad one
            cout << "BAD COMMAND" << endl << "icsh $ ";
            prevcmdw.close(); // closes the file
        }
    }

    return 0;
}

