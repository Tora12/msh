// Jenner Higgins
// CS 240
// 03-19-2019
// Assignment #3
// msh2.c

#include "linkedlist.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int make_args_pipe(char *s, char **strpipe);
int make_args_semi(char *s, char **strsemi);
int process_input(int counter, char *s, char **argv, char **argvpipe);
void color(void);
void exec(char **argv);
void exec_pipe(char **argv, char **argvpipe);
void exec_semi(char **argv, char **argvpipe);
void make_args_space(char *s, char **argv);
void parse_alias(char * buff, char **stralias);

int parse_file(char * s, char **argv, char **argv2);


int main()
{
    char *argv[20], input[50], *argv2[20];
    int counter = 0, file;
    
    while(1)
    {
        printf(">: ");                            // Print shell line
        scanf("%[^\n]%*c", input);                // Read user input line
        
        file = parse_file(input, argv, argv2);
        
        if(strlen(input) != 0)
        {
            add_history(++counter, input);
        }
        else
        {
            printf("No input recorded");
            exit(-1);
        }
        
        if(file)
            process_input(counter, input, argv, argv2);
    }
    
    return 0;
}

int make_args_pipe(char *s, char **strpipe)
{
    int i;
    
    for(i = 0; i < 2; i++)
    {
        strpipe[i] = strsep(&s, "|");                   // Search for pipe in user input, if found split into 2 parts and store in array
        if (strpipe[i] == NULL)
            break;
    }
    if(strpipe[1] == NULL)
        return 0;                                       // Returns zero if no pipe is found
    else
    {
        return 1;                                       // Returna one if pipe is found
    }
}

int make_args_semi(char *s, char **strsemi)
{
    int i;
    
    for(i = 0; i < 2; i++)
    {
        strsemi[i] = strsep(&s, ";");                   // Search for semicolon in user input, if found split into 2 parts and store in array
        if (strsemi[i] == NULL)
            break;
    }
    
    if(strsemi[1] == NULL)
        return 0;                                       // Returns zero if no semicolon is found
    else
    {
        return 1;                                       // Returna one if semicolon is found
    }
}

int process_input(int counter, char *s, char **argv, char **argv2)
{
    char *strpipe[2], *strsemi[2], *stralias[2], *p = NULL, currarg[50], buff[50];
    int pipe = 0, semi = 0;
    
    strcpy(buff,s);                             // Copy full user input into variable buff before modifiction to s
    
    pipe = make_args_pipe(s, strpipe);
    semi = make_args_semi(s, strsemi);
    
    if (pipe)                                   // NOT SURE HOW PIPE WORKS
    {
        make_args_space(strpipe[0], argv);
        make_args_space(strpipe[1], argv2);
        exec_pipe(argv, argv2);
        return 0;
    }
    else if(semi)
    {
        make_args_space(strsemi[0], argv);
        make_args_space(strsemi[1], argv2);
        
        exec_semi(argv, argv2);                   // WEIRD BUG WHEN ADDING SPACES IN BETWEEN COMMANDS AND SEMI-COLON...
        return 0;
    }
    else
    {
        s = check_alias(s);                       // Check for aliase
        make_args_space(s, argv);                 // Parse user input line
        strcpy(currarg, *argv);
        if(strcmp(argv[0], "exit") == 0)          // Check for exit command before execution
            exit(0);
        
        if(strcmp(argv[0], "history") == 0)       // Check for history built in commands
        {
            show_history();
            return 0;
        }
        else if(strcmp(argv[0], "!!") == 0)
        {
            s = exec_last();
            if(s != 0)
                add_history(counter, s);
                process_input(counter, s, argv, argv2);
            return 0;
        }
        else if(currarg[0] == '!' && currarg[1] > '0' && currarg[1] <= '9')
        {
            int hnum;
            char * p = currarg;
            p++;                                  // Increment pointer to point to number value instead of !
            sscanf(p, "%d", &hnum);               // Convert char * p number to int cnum number
            s = exec_past_command(hnum);
            if(s != 0)
                add_history(counter, s);
                process_input(counter, s, argv, argv2);
            return 0;
        }
        
        if((strcmp(argv[0], "alias") == 0) && argv[1] != NULL)      // Check for alias built in commands
        {
            for(int i = 0; i < strlen(buff); i++)       // Deletes "alias " from buff
                buff[i] = buff[i+6];
            parse_alias(buff, stralias);
            p = stralias[1];                            // Deletes single quotes from stralias[1];
            p++;
            p[strlen(p)-1] = 0;
            stralias[1] = p;
            add_alias(stralias[0], stralias[1]);
            return 0;
        }
        else if((strcmp(argv[0], "alias") == 0))
        {
            print_list();
            return 0;
        }
        else if((strcmp(argv[0], "unalias") == 0))
        {
            for(int i = 0; i < strlen(buff); i++)       // Deletes "unalias " from buff
                buff[i] = buff[i+8];
            _unalias(buff);
            return 0;
        }
        
        if((strcmp(argv[0], "color") == 0))
        {
            color();
            return 0;
        }
        
        exec(argv);                               // Exexcute non-piped/non-semi/non-built-in input line
        
        return 0;
    }
}

void color(void)
{
    printf("\033[%d;%dm",1,36);
    printf("\033[1,36m");
}


void exec(char **argv)
{
    int status;
    pid_t childpid;
    
    if((childpid = fork()) == -1)               // Fork a process
    {
        perror("Error in the fork\n");
        exit(-1);
    }
    else if(childpid == 0)
    {
        if(execvp(*argv, argv) < 0)             // Execute the command
        {
            perror("Error in the exec\n");
            exit(-1);
        }
    }
    else
    {
        while(childpid != wait(&status));       // Parent wait for child completion
    }
}

void exec_pipe(char **argv, char **argv2)
{
    int fd[2];
    int wait, status, pid;
    pipe(fd);
    
    if((pid = fork()) == -1)               // Fork a process
    {
        perror("Error in the fork\n");
        exit(-1);
    }
    else if(pid == 0)
    {
        dup2(fd[1], 1);
        close(fd[1]);
        close(fd[0]);
        char * arg[] = {"sh", "-c", *argv, NULL};
        execvp(arg[0], arg);
        perror("Failed to execute /bin/ls\n");
        exit(1);
    }
    
    close(fd[1]);
    
    if((pid = fork()) == -1)               // Fork a process
    {
        perror("Error in the fork\n");
        exit(-1);
    }
    else if(pid == 0)
    {
        dup2(fd[0],0);
        close(fd[0]);
        char * arg[] = {"sh", "-c", *argv2, NULL};
        execvp(arg[0], arg);
        perror("Failed to execute /bin/ls\n");
        exit(1);
    }
    close(fd[0]);
    
    while((wait = waitpid(-1, &status, 0)) > 0);        // Parent wait for child completion
}

void exec_semi(char **argv, char **argvpipe)
{
    int status;
    pid_t p1, p2;
    
    if((p1 = fork()) < 0)                                 // Fork process 1
    {
        perror("Error in the fork\n");
        exit(-1);
    }
    else if(p1 == 0)
    {
        if(execvp(*argv, argv) < 0)                      // Execute command 1
        {
            perror("Error in the exec\n");
            exit(-1);
        }
    }
    else
    {
        while(p1 != wait(&status));                     // Parents wait for child completion
    }
    
    if((p2 = fork()) == -1)                             // Fork process 2
    {
        perror("Error in the fork\n");
        exit(-1);
    }
    else if(p2 == 0)
    {
        if(execvp(*argvpipe, argvpipe) < 0)             // Execute command 2
        {
            perror("Error in the exec\n");
            exit(-1);
        }
    }
    else
    {
        while(p2 != wait(&status));
    }    
}

void make_args_space(char *s, char **argv)
{
    while(*s != '\0')
    {
        while(*s == ' ')                        // Replace ' ' with '\0'
            *s++ = '\0';
        
        *argv++ = s;                            // Split up each argument
        
        while(*s != ' ' && *s != '\0')          // Check spot for ' ' or '\0'
            s++;
    }
    *argv = NULL;                               // Place '\0' at end of argument list
}

void parse_alias(char * buff, char ** stralias)
{
    int i;
    
    for(i = 0; i < 2; i++)
    {
        stralias[i] = strsep(&buff, "=");        // Search for assignment operator in user input, if found split into 2 parts and store in array
    }
}

int parse_file(char * s, char ** argv, char ** argv2)
{
    char * line = NULL, file[] = "mshrc.txt";
    FILE * fp = NULL;
    size_t len = 0;
    
    if(strcmp((s), file) == 0)
    {
        fp = fopen(file, "r");
        
        while ((getline(&line, &len, fp)) != -1)
        {
            make_args_space(line, argv);
            strtok(*argv, "\n");
            exec(argv);
        }
        fclose(fp);
        return 0;
    }
    else
        return 1;
}


