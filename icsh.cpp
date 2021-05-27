#include "icsh.h"
#include "command.cpp"

string trim(string st) {
	while (st.substr(0, 1) == " ") {
		st = st.substr(1, st.length() - 1);
	}
	// cout << st;
	return st;
}

int main(int argc, char * argv[]) {
	// prevcmd = new oldcmd();
	last_status = 0;
	username = getenv("USER");
	prompt = "\033[1;36m" + username + "@icsh> \033[0m";

    // default handling just setting up
	default_action.sa_handler = SIG_IGN;
	sigemptyset(&default_action.sa_mask);
	default_action.sa_flags = 0;	

	// start by ignoring all signals
	sigaction(SIGTTOU, &default_action, NULL);
	sigaction(SIGINT, &default_action, NULL);
	sigaction(SIGTSTP, &default_action, NULL);

	// for SIGCHLD at the start
	chld_action.sa_handler = chld_handler;
	sigemptyset(&chld_action.sa_mask);
	chld_action.sa_flags = 0;
	sigaction(SIGCHLD, &chld_action, NULL);

	shell_id = getpid(); // get the pid of the shell
	setpgid(0, shell_id); // set the process group of the shell to its own pid

	if (argc == 1) { // runs in interactive mode
		cout << "\033[1;36mInitiliazing IC Shell...\033[0m";
		cout << endl << prompt;

		while (1) {
			getline(cin, commandLine); // get a line from the command line
			
			if (commandLine[0] == ' ') commandLine = trim(commandLine); // trim leading spaces
			if (commandLine.length() == 0) { // empty commmand
				cout << prompt;
				continue;
			}

			// not empty command
			int fin_fd, fout_fd, saved_stdin, saved_stdout;
			string fin_name, fout_name;
			
			redir_flag = redirc(commandLine); // sees if there is any redirection
			// cout << "case is : " << redir_flag << endl;
			switch(redir_flag) {
				case 0:
					// cout << "case 0\n";
					run(commandLine, 0);
					break;

				case 0b01: // only stdin redirection
					// cout << "case 0b01\n";
					fin_name = find_rein(commandLine); // find file name
					fin_fd = open(fin_name.c_str(), O_RDONLY); // open in read-only
					
					if (fin_fd < 0) { // can't open file
						cout << "\033[1;31micsh:\033[0m cannot find input file\n";
						continue;
					}

					// duplicate, run, and close
					saved_stdin = dup(STDIN_FILENO); // saves the original stdin
					dup2(fin_fd, STDIN_FILENO);
					commandLine = commandLine.substr(0, rein_pos(commandLine)-1);
					run(commandLine, 0);

					close(fin_fd);
					fflush(stdin);
					sleep(1); // gives time to flush everything in stdin
					dup2(saved_stdin, STDIN_FILENO);
					close(saved_stdin);
					break;

				case 0b10:
					// cout << "case 0b10\n";
					fout_name = find_reout(commandLine); // find output name
					fout_fd = open(fout_name.c_str(), O_TRUNC | O_WRONLY | O_CREAT, 0644); 
				
					if (fout_fd < 0) {
						cout << "\033[1;31micsh:\033[0m cannot find/create output file\n";
						continue;
					}

					saved_stdout = dup(STDOUT_FILENO);
					dup2(fout_fd, 1);
					commandLine = commandLine.substr(0, reout_pos(commandLine)-1);
					run(commandLine, 0);

					close(fout_fd);
					fflush(stdout);
					sleep(1);
					dup2(saved_stdout, STDOUT_FILENO);
					close(saved_stdout);
					break;

				case 0b11:
					// cout << "case 0b11\n";
					fin_name = find_rein(commandLine);
					fout_name = find_reout(commandLine);
					fin_fd = open(fin_name.c_str(), O_RDONLY);
					fout_fd = open(fout_name.c_str(), O_CREAT | O_WRONLY, 0644);

					if (fin_fd < 0 || fout_fd < 0) {
						cout << "\033[1;31micsh:\033[0m cannot find/create output file\n";
						continue;
					}

					saved_stdin = dup(STDIN_FILENO);
					saved_stdout = dup(STDOUT_FILENO);
					dup2(fin_fd, STDIN_FILENO);
					dup2(fout_fd, STDOUT_FILENO);
					commandLine = commandLine.substr(0, rein_pos(commandLine)-1);
					run(commandLine, 0);

					close(fin_fd);
					close(fout_fd);
					fflush(stdin);
					fflush(stdout);
					sleep(1);
					dup2(saved_stdin, STDIN_FILENO);
					dup2(saved_stdout, STDOUT_FILENO);
					close(saved_stdin);
					close(saved_stdout);
					break;

				default:
					cout << "\033[1;31micsh:\033[0m redirection failed\n";
			}
			cout << prompt;
		}
	} else { // runs in script mode
		script.open(argv[1]);
		if (!script.is_open()) {
			cout << "\033[1;31micsh:\033[0m script not found\n";
			exit(127);
		} else {
			while (getline(script, commandLine)) {
				if (commandLine.substr(0, 1) == " ") commandLine = trim(commandLine);
				if (commandLine.length() == 0) continue;
				if (commandLine.substr(0, 1) == "#") continue; // skips comments

				int fin_fd, fout_fd, saved_stdin, saved_stdout;
				string fin_name, fout_name;

				redir_flag = redirc(commandLine);

				switch(redir_flag) {
					case 0:
						// cout << "case 0\n";
						run(commandLine, 0);
						break;

					case 0b01: // only stdin redirection
						// cout << "case 0b01\n";
						fin_name = find_rein(commandLine); // find file name
						fin_fd = open(fin_name.c_str(), O_RDONLY); // open in read-only
						
						if (fin_fd < 0) { // can't open file
							cout << "\033[1;31micsh:\033[0m cannot find input file\n";
							continue;
						}

						// duplicate, run, and close
						saved_stdin = dup(STDIN_FILENO); // saves the original stdin
						dup2(fin_fd, STDIN_FILENO);
						commandLine = commandLine.substr(0, rein_pos(commandLine)-1);
						run(commandLine, 0);

						close(fin_fd);
						fflush(stdin);
						sleep(1);
						dup2(saved_stdin, STDIN_FILENO);
						close(saved_stdin);
						break;

					case 0b10:
						// cout << "case 0b10\n";
						fout_name = find_reout(commandLine); // find output name
						fout_fd = open(fout_name.c_str(), O_TRUNC | O_WRONLY | O_CREAT, 0644); 
					
						if (fout_fd < 0) {
							cout << "\033[1;31micsh:\033[0m cannot find/create output file\n";
							continue;
						}

						saved_stdout = dup(STDOUT_FILENO);
						dup2(fout_fd, 1);
						commandLine = commandLine.substr(0, reout_pos(commandLine)-1);
						run(commandLine, 0);

						close(fout_fd);
						fflush(stdout);
						sleep(1);
						dup2(saved_stdout, STDOUT_FILENO);
						close(saved_stdout);
						break;

					case 0b11:
						// cout << "case 0b11\n";
						fin_name = find_rein(commandLine);
						fout_name = find_reout(commandLine);
						fin_fd = open(fin_name.c_str(), O_RDONLY);
						fout_fd = open(fout_name.c_str(), O_CREAT | O_WRONLY, 0644);

						if (fin_fd < 0 || fout_fd < 0) {
							cout << "\033[1;31micsh:\033[0m cannot find/create output file\n";
							continue;
						}

						saved_stdin = dup(STDIN_FILENO);
						saved_stdout = dup(STDOUT_FILENO);
						dup2(fin_fd, STDIN_FILENO);
						dup2(fout_fd, STDOUT_FILENO);
						commandLine = commandLine.substr(0, rein_pos(commandLine)-1);
						run(commandLine, 0);

						close(fin_fd);
						close(fout_fd);
						fflush(stdin);
						fflush(stdout);
						sleep(1);
						dup2(saved_stdin, STDIN_FILENO);
						dup2(saved_stdout, STDOUT_FILENO);
						close(saved_stdin);
						close(saved_stdout);
						break;

					default:
						cout << "\033[1;31micsh:\033[0m redirection failed\n";
				}
			}
			
			// deleting the previous command file
			// just in case that there's no exit call in the script
            // prevcmdr.open(".pcmd.txt");
			// if (prevcmdr.is_open()) {
			// 	prevcmdr.close();
			// 	remove(".pcmd.txt");
			// }

			exit(0);
		}
	}

	return 0;
}
