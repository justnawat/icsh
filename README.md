In this README file, I'd like to share the references that I used for completing this project.

I'll go through this Milestone by Milestone.

-- MILESTONE 1&2 --
- getting blank lines (for empty commands): https://www.geeksforgeeks.org/how-to-use-getline-in-c-when-there-are-black-lines-in-input/
- splitting strings (for how I implemented my echo): https://www.geeksforgeeks.org/how-to-split-a-string-in-cc-python-and-java/

-- MILESTONE 3 --
- converting a C++ string into a C string (char *): https://stackoverflow.com/questions/11821491/converting-string-to-cstring-in-c 
- turning a string into char ** (for execvp because I used strings): https://stackoverflow.com/questions/28712552/c-using-execvp-with-string-array/28713130

-- MILESTONE 4 -- 
- sending signals to the child process from a signal handler: https://stackoverflow.com/questions/13351851/killing-a-child-process-from-a-signal-handler
- talking with Justin where he shared his conversation with Aj.Sunsern
- talking with Aj.Sunsern

-- MILESTONE 5 --
- The program is designed to have a delay when redirecting.
- returning to using stdin and stdout after using dup2(): https://stackoverflow.com/questions/11042218/c-restore-stdout-to-terminal

-- MILESTONE 6 -- 
- External commands CAN and WILL run in the background. However, it causes the prompt to be printed repeatedly after terminating/finishing.
- jobs now works.
- fg doesn't work.
- bg also doesn't work.

-- MILESTONE 7 -- 
- changing color of the terminal to look nicer: https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
- getting the username of a user: https://gist.github.com/krishna0512/5e5f8761a24ea850f0bd
