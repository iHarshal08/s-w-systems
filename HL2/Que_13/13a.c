/*
===========================================================================================================================
Name : 13a.c
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

void signal_handler(int sig) {
    if (sig == SIGSTOP) {
        printf("Received SIGSTOP signal\n");  // This line will never execute
    } else if (sig == SIGINT) {
        printf("Received SIGINT (Interrupt from keyboard)\n");
    } else if (sig == SIGCONT) {
        printf("Received SIGCONT (Continue after being stopped)\n");
    }
}

int main() {
    printf("Waiting for signals...\n");

    signal(SIGINT, signal_handler);   // Interrupt signal (Ctrl + C)
    signal(SIGCONT, signal_handler);  // Continue signal

    while (1) {
        pause(); 
    }

    return 0;
}
