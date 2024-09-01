#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>

void timer_handler(int signum) {
    printf("Timer expired! (ITIMER_VIRTUAL)\n");
}

int main() {
    struct itimerval timer;
    signal(SIGVTALRM, timer_handler);
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;

    // Configure the timer to reset to the same interval
    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;
    
    setitimer(ITIMER_VIRTUAL, &timer, NULL);
    while (1);
    return 0;
}
