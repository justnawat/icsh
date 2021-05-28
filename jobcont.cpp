// checks if the command has to be run in the background or not
bool checkbg(string commandLine) {
    if (commandLine.substr(commandLine.length() - 2, 2) == " &") {
        return true;
    } else {
        return false;
    }
}

// adds a job
void pushjob(string in_cmd, pid_t in_jpid, bool in_bg) {
    job* temp = new job();
    temp->cmd = in_cmd;
    temp->stat = "running";
    temp->age = "+";
    temp->jpid = in_jpid;

    if (head == NULL) {
        temp->next = NULL; // no next node
        temp->jid = 1;

        // prints out the jid and pid
        if (in_bg) {
            cout << "[" << temp->jid << "]\t";
            cout << temp->jpid << endl;
        }

        head = temp;
    } else {
        int current_big;
        for (current = head; current != NULL; current = current->next) {
            current_big = current->jid;
            if (current->next == NULL) { // at the last node
                temp->next = NULL; // points the next pointer to nothing
                temp->jid = current_big + 1; // the job id is the higher than the current
                current->next = temp; // points the og last to the new last node

                if (in_bg) {
                    cout << "[" << temp->jid << "]\t";
                    cout << temp->jpid << endl;
                }
            }
        }
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
    if (head == NULL) {
        cout << "\033[1;31micsh:\033[0m there is no job\n";
        return ;
    }

    stringstream cmdstr(commandLine);
    cmdstr >> command;
    cmdstr >> command;

    // gets the jid
    int readjid;
    readjid = stoi(command.substr(1, command.length() - 1));

    for (current = head; current != NULL; current = current->next) {
        if (current->jid == readjid) {
            cout << "[" << current->jid << "]\t"; // job id
            cout << current->age << "\t"; // blank, -, or +
            current->stat = "running";
            cout << current->stat << "\t"; // status
            cout << current->cmd; // the command itself

            int status;
            tcsetpgrp(0, current->jpid); // gives terminal control
            waitpid(current->jpid, &status, WUNTRACED); // waits until it terminates
            return ;
        }
    }
    cout << "\033[1;31micsh:\033[0m job id cannot be found\n";
    return ;
}

void make_background(string commandLine) {
    stringstream cmdstr(commandLine);
    cmdstr >> command;
    cmdstr >> command;

    int readjid;
    readjid = stoi(command.substr(1, command.length() - 1));
}

void d_job() {
    if (head == NULL) {
        return; // does nothing
    }

    current = head;
    job* next;

    while (current != NULL) {
        next = current->next; // temp pointer to the next node
        free(current); // frees current
        current = next; // goes to the next node
    }
    return ;
}