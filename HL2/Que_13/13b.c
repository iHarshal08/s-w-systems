/*
===========================================================================================================================
Name : 13b.c
Author : Harshal Purohit
Description : Write two programs: first program is waiting to catch SIGSTOP signal, the second program
will send the signal (using kill system call). Find out whether the first program is able to catch
the signal or not.
Date: 8th Sept, 2024.
===========================================================================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    pid_t pid;

    printf("Enter the PID of the first program: ");
    scanf("%d", &pid);

    kill(pid, SIGSTOP);
    printf("Sent SIGSTOP to process %d\n", pid);

    // After a pause, send SIGCONT to resume the process
    sleep(2); 
    kill(pid, SIGCONT);
    printf("Sent SIGCONT to process %d\n", pid);

    return 0;
}
