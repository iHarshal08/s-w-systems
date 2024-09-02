/*
===========================================================================================================================
Name : 1b.c
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
    printf("Timer expired! (ITIMER_VIRTUAL)\n");
}

int main() {
    struct itimerval timer;
    signal(SIGVTALRM, handle_t);
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;

    // Configure the timer to reset to the same interval
    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;
    
    setitimer(ITIMER_VIRTUAL, &timer, NULL);
    while (1);
    return 0;
}
