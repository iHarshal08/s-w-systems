/*
===========================================================================================================================
Name : 15.c
Author : Harshal Purohit
Description : Write a simple program to send some data from parent to the child process.
Date: 8th Sept, 2024.
===========================================================================================================================
*/

#include <stdio.h>
#include <unistd.h>

int main() {
    int pipefd[2];
    char msg[] = "Hello, This is child!";
    char buf[20];

    pipe(pipefd);
    if (fork() == 0) {  
        read(pipefd[0], buf, sizeof(buf));
        printf("Child received: %s\n", buf);
    } else {  // Parent process
        write(pipefd[1], msg, sizeof(msg));
    }
    return 0;
}
