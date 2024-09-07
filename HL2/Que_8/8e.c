/*
===========================================================================================================================
Name : 8e.c
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
#include <sys/time.h>
#include <unistd.h>

void sigALRM(int sig) {
    printf("Caught SIGALRM\n");
}

int main() {
    struct itimerval timer;
    signal(SIGALRM, sigALRM);

    // Set timer for 3 seconds, no repeating
    timer.it_value.tv_sec = 3;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL, &timer, NULL);

    printf("Waiting for alarm...\n");
    pause();
    return 0;
}


