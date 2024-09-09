/*
===========================================================================================================================
Name : 17a.c
Author : Harshal Purohit
Description : Write a program to execute ls -l | wc.
            a. use dup
            b. use dup2
            c. use fcntl
Date: 8th Sept, 2024.
===========================================================================================================================
*/

#include <stdio.h>
#include <unistd.h>

int main() {
    int pipefd[2];
    pipe(pipefd);
    
    if (fork() == 0) { 
        dup(pipefd[1]); // Duplicate write end of the pipe to stdout
        close(pipefd[0]); // Close unused read end
        execlp("ls", "ls", "-l", NULL); // Execute "ls -l"
    } else { 
        dup(pipefd[0]); // Duplicate read end of the pipe to stdin
        close(pipefd[1]); // Close unused write end
        execlp("wc", "wc", NULL); // Execute "wc"
    }
    
    return 0;
}

