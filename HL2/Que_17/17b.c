/*
===========================================================================================================================
Name : 17b.c
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
    
    if (fork() == 0) { // Child process
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to the write end of the pipe
        close(pipefd[0]);
        close(pipefd[1]); // Close duplicate file descriptor
        execlp("ls", "ls", "-l", NULL); // Execute "ls -l"
    } else { 
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to the read end of the pipe
        close(pipefd[1]);
        close(pipefd[0]); // Close duplicate file descriptor
        execlp("wc", "wc", NULL); // Execute "wc"
    }
    
    return 0;
}
