/*
===========================================================================================================================
Name : 25.c
Author : Harshal Purohit
Description : Write a program to create three child processes. The parent should wait for a particular child    
        (use waitpid system call).
Date: 23rd Aug, 2024.
===========================================================================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2, pid3;
    int status;

    // 1st child process
    if ((pid1 = fork()) == 0) {
        printf("Child 1 => PID: %d\n", getpid());
        exit(0);
    } 
    // 2nd child process
    if ((pid2 = fork()) == 0) {
        printf("Child 2 => PID: %d\n", getpid());
        exit(0);
    } 

    // 3rd child process
    if ((pid3 = fork()) == 0) {
        // Inside the third child process
        printf("Child 3 (PID: %d)\n", getpid());
        exit(0);
    } 

    // Parent process waits for the 1st child process
    if (waitpid(pid1, &status, 0) == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }

    printf("Parent process (PID: %d) exiting\n", getpid());
    return 0;
}
