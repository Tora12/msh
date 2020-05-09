README

  msh ("my shell") is a shell written in C that allows the user to run any Linux command line commands (bash-syntax compatible). To run msh.c first compile by using: "gcc -c msh2.c -o msh2.o", "gcc -c alias.c -o alias.o", "gcc -c history.c -o history.o", and "gcc msh2.o alias.o history.o" commands and then ./a.out to run.

1. To run multiple commands using only one user input line the user must enter both commands separated by ";" with no space in between. EXAMPLE: "ls;ps" will execute "ls" first followed by "ps". (Note: There is a bug when including spaces between the commands and semicolon which results in failing to execute the first command)

2. To read in input from file mshrc.txt, first write all commands you wish to run into the file called mshrc.txt and separate each command with a newline, then in order to run those commands from the file simply type "mshrc.txt" into the shell buffer. EXAMPLE: The mshrc.txt file provided after typing "mshrc.txt" into the shell buffer will run pwd followed by ps.

3. In order to use aliases, use unix syntax for aliases. For example, to define an alias use "alias greet='echo Hello User'", to undefine an alias use "undefine greet", to show all aliases type "alias".

4. The feature to expand the PATH variable is currently unavailable/unsupported and therefore the code for expanding the PATH variable was left out in order to allow user to compile and run the program. 

5. To use history commands, use bash syntax. For example, "history" will display all of the last 20 lines of commands (both successful and unsuccessful), "!!" will re-execute the last command, "!413" will attempt to re-execute command line 413 if command line 413 exists.

6. To use pipes, type the two commands you wish to use and separate them by using "|" (NOTE: The command before the "|" operator will feed info/output into the command that follows the "|" operator). EXAMPLE: "ls -al | more" will pipe the output of ls to more.

7. To change color of the current font, simply type "color" into the shell buffer and the shell font will have changed color to blue.

8. Some other commands include but are not limited to: pwd, ps, top, date, cal, who, mkdir, rmdir, more, ls, ls -l, ls -a, ls -ls, vim, ping, man, etc...

WARNING: The msh2.c program is still a work in progress and there are still plenty bugs to fix and edge cases to implement. 
 
