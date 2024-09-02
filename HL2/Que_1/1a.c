/*
===========================================================================================================================
Name : 1a.c
Author : Harshal Purohit
Description : Write a separate program (for each time domain) to set a interval timer in 10sec and
    10micro second.
        a. ITIMER_REAL
        b. ITIMER_VIRTUAL
        c. ITIMER_PROF
Date: 1st Sept, 2024.
===========================================================================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>

void handle_t(int signum) {
    printf("Timer expired! (ITIMER_REAL)\n");
}

int main() {
    struct itimerval timer;
    signal(SIGALRM, handle_t);
    
    // Configure the timer to expire after 10 seconds and 10 microseconds
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;

    // Configure the timer to reset to the same interval
    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    setitimer(ITIMER_REAL, &timer, NULL);
    while (1);

    return 0;
}
