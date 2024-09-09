/*
===========================================================================================================================
Name : 14.c
Author : Harshal Purohit
Description : Write a simple program to create a pipe, write to the pipe, read from pipe and display on
the monitor.
Date: 8th Sept, 2024.
===========================================================================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2];
    char writeMsg[] = "Hello, This pipe is created by Harshal(MT2024056)!!!";
    char readMsg[100];

    pipe(pipefd);
    write(pipefd[1], writeMsg, strlen(writeMsg) + 1);
    read(pipefd[0], readMsg, sizeof(readMsg));
    printf("Read from pipe: %s\n", readMsg);

    return 0;
}
