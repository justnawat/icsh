#include "icsh.h"
#include "runner.cpp"

string trim(string st) { // makes sure there are no leading spaces
    while (st.substr(0, 1) == " ") {
        st = st.substr(1, st.length() - 1);
    }

    return st;
}

int main(int argc, char * argv[]) {
    if (argc == 1) { // no command line argument
        cout << "Initializing IC Shell..." << endl;
        cout << "icsh $ "; // prompts for command

        while (1) {
            runMode = 0;
            getline(cin, commandLine); // gets the whole line of the command as string
            if (commandLine.substr(0, 1) == " ") commandLine = trim(commandLine);
            command_run(commandLine, 0);
            cout << "icsh $ ";
        }

    } else {
        runMode = 1;
        script.open(argv[1]); // opens the script file

        if (!script.is_open()) { // script file doesn't exist
            cout << "icsh: script not found.\n";
            exit(127); // according to bash
        }

        while (getline(script, commandLine)) {
            if (commandLine.substr(0, 1) == " ") commandLine = trim(commandLine); // has leading spaces
            if (commandLine.length() == 0) { // empty line
                ; // does nothing
            } else if (commandLine.substr(0, 1) == "#") { // starts with # so skip because it's a comment
                ; // also does nothing ;)
            } else command_run(commandLine, 1);
        };
        exit(0);
    }

    return 0;
}

