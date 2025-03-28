/*
===========================================================================================================================
Name : 21.c
Author : Harshal Purohit
Description : Write a program, call fork and print the parent and child process id.
Date: 23rd Aug, 2024.
===========================================================================================================================
*/


#include <stdio.h>
#include <unistd.h> // For fork()
#include <sys/types.h>

int main() {
    pid_t pid;
    pid = fork(); // will create a new process
    if (pid == 0)
        printf("Child process: PID = %d, Parent PID = %d\n", getpid(), getppid());// executed by child process
    else 
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);//executed by parent process
    return 0;
}
