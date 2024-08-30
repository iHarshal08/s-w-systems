/*
===========================================================================================================================
Name : 24.c
Author : Harshal Purohit
Description : Write a program to create an orphan process.
Date: 23rd Aug, 2024.
===========================================================================================================================
*/


#include <stdio.h>
#include <unistd.h>  //fork() and sleep()
#include <sys/types.h>

int main() {
    pid_t pid;
    pid = fork();
    if (pid == 0) {
        printf("Child process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        sleep(30);
        printf("Child process (after sleep): PID = %d, Parent PID = %d\n", getpid(), getppid());
    } else {
        printf("Parent process: PID = %d\n", getpid());
        printf("Parent process is terminating...\n");
        // Parent process exits, making the child an orphan
        _exit(0);
    }

    return 0;
}
