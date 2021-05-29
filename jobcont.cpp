#include "jobcont.h"

// adds a job
void pushjob(string in_cmd, pid_t in_jpid, bool in_bg) {
    // cout << "pushjob has been called\n";
    
    // creating the starting node for the linked list of jobs
    jobNode* temp = new jobNode();
    temp->cmd = in_cmd;
    temp->stat = "running";
    // temp->age = "+";
    temp->jpid = in_jpid;
    temp->next = NULL;

    if (head == NULL) { 
        cout << "head empty\n";
        temp->jid = 1;
        head = temp;
        tail = temp;
    } else {
        cout << "head emptyn't\n";
        // int current_big;
        // jobNode* current;
        temp->jid = tail->jid+1;
        tail->next = temp;
        tail = temp;
    }

    // prints out the jid and pid
    if (in_bg) {
        cout << "[" << temp->jid << "]\t";
        cout << temp->jpid << endl;
    }
}

// just prints out the current jobs
void myjob() {
    jobNode* current;
    if (head == NULL) { // no current job
        return;
    } else { // has jobs
        current = head; // start at the head
    }

    while (current != NULL) { // print each job
        cout << "[" << current->jid << "]\t"; // job id
        // cout << current->age << "\t"; // blank, -, or +
        cout << current->stat << "\t"; // status
        cout << current->cmd << endl; // the command itself
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

    jobNode* current;
    for (current = head; current != NULL; current = current->next) {
        if (current->jid == readjid) {
            int status;
            tcsetpgrp(0, current->jpid); // gives terminal control
            pause();
            // waitpid(current->jpid, &status, WUNTRACED); // waits until it terminates
            tcsetpgrp(0, getpid());
            // cout << current->age << "\t"; // blank, -, or +

            if (WIFEXITED(status)) {
                last_status = WEXITSTATUS(status);
                current->stat = "done";
            } else if (WIFSIGNALED(status)) {
                last_status = 130;
                cout << "termsig is " << WTERMSIG(status) << endl;
                current->stat = "signaled";
            } else if (WIFSTOPPED(status)) {
                last_status = 146;
                current->stat = "stopped";
            }

            cout << "[" << current->jid << "]\t"; // job id
            cout << current->stat << "\t"; // status
            cout << current->cmd << endl; // the command itself

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

    jobNode* current;
    for (current = head; current != NULL; current = current->next) {
        if (current->jid == readjid) {
            cout << "[" << current->jid << "]\t";
            current->stat = "running";
        }
    }
}

void d_job() {
    if (head == NULL) {
        return; // does nothing
    }

    jobNode* current;
    jobNode* next;
    current = head;

    while (current != NULL) {
        next = current->next; // temp pointer to the next node
        free(current); // frees current
        current = next; // goes to the next node
    }
    return ;
}