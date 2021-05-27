// checks if the command has to be run in the background or not
bool checkbg(string commandLine) {
    if (commandLine[commandLine.length() - 1] == '&') {
        return true;
    } else {
        return false;
    }
}

// just prints out the current jobs
void myjob() {
    if (head == NULL) { // no current job
        return;
    } else { // has jobs
        current = head; // start at the head
    }

    while (current != NULL) { // print each job
        cout << "[" << current->jid << "]\t"; // job id
        cout << current->age << "\t"; // blank, -, or +
        cout << current->stat << "\t"; // status
        cout << current->cmd; // the command itself
        current = current->next; // goes to the next node
    }
    return;
}

void make_foreground(string commandLine) {
    stringstream cmdstr(commandLine);
    word >> command;
    word >> command;

    int readjid;
    readjid = stoi(command.substr(1, command.length() - 1));


}

void make_background(string commandLine) {
    stringstream cmdstr(commandLine);
    word >> command;
    word >> command;

    int readjid;
    readjid = stoi(command.substr(1, command.length() - 1));
}