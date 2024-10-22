/*
===========================================================================================================================
Name : 8g.c
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
#include <unistd.h>
#include <sys/time.h>

void handle_sigprof(int sig) {
    printf("Caught SIGPROF: Profiling timer expired\n");
}

int main() {
    struct itimerval timer;
    signal(SIGPROF, handle_sigprof);

    // Set profiling timer for 3 seconds
    timer.it_value.tv_sec = 3;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_PROF, &timer, NULL);

    printf("Waiting for profiling timer alarm...\n");
    for (long long i = 0; i < 1e10; ++i);
    pause();  // Wait for signal

    return 0;
}
