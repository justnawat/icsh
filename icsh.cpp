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
        getline(cin, command); // gets the whole line of the command as string
        // ofstream prevcmdw(".last_command.txt"); // opens the file to write the command

        ccmd = command.c_str(); // converts the command C++ string into a C-style string
        word = strtok((char *) ccmd, " "); // get a word from the command line

        // THE ECHO COMMAND
        if (strcmp(word, "echo") == 0) { // if the first word of the line is echo
            word = strtok(NULL, " "); // skips the first word (yes, i know)
            while (word != NULL) {
                cout << word << " ";
                word = strtok(NULL, " ");
            }
            cout << endl << "icsh $ "; // ends command and prompts for a new one
        } 

        // THE !! COMMAND
        else if (strcmp(word, "!!") == 0) {
            cout << prevcmd << endl << "icsh $ ";
        }

        // THE EXIT COMMAND
        else if (strcmp(word, "exit") == 0) {
            word = strtok(NULL, " ");
            cout << "[Sarcastic voice] Bye bye, I hope we meet again!\n";
            exit_code = atoi(word) & 0xff;
            cout << "Exit code: " << exit_code << endl;
            return exit_code;
        }

        // BAD COMMAND
        else cout << "BAD COMMAND" << endl << "icsh $ ";
    }

    return 0;
}

/* REFERENCES
- https://www.geeksforgeeks.org/how-to-split-a-string-in-cc-python-and-java/
- https://www.tutorialspoint.com/c-program-to-check-if-two-strings-are-same-or-not
- https://www.tutorialspoint.com/cplusplus/cpp_strings.htm
- https://stackoverflow.com/questions/11821491/converting-string-to-cstring-in-c
- https://blog.udemy.com/c-string-to-int/
*/