/*
===========================================================================================================================
Name : 8b.c
Author : Harshal Purohit
Description : Write a separate program using signal system call to catch the following signals.
            a. SIGSEGV
            b. SIGINT
            c. SIGFPE
            d. SIGALRM (use alarm system call)
            e. SIGALRM (use setitimer system call)
            f. SIGVTALRM (use setitimer system call)
            g. SIGPROF (use setitimer system call)
Date: 7th Sept, 2024.
===========================================================================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void sigINT(int sig) {
    printf("Caught SIGINT\n");
    exit(0);
}

int main() {
    signal(SIGINT, sigINT);

    while (1) {
        printf("Process running... \n Press Ctrl+C to stop\n");
        sleep(1);
    }

    return 0;
}



