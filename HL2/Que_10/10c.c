/*
===========================================================================================================================
Name : 10c.c
Author : Harshal Purohit
Description : Write a separate program using sigaction system call to catch the following signals.
            a. SIGSEGV
            b. SIGINT
            c. SIGFPE
Date: 8th Sept, 2024.
===========================================================================================================================
*/

#include <signal.h>
#include <stdlib.h>

void handle_sigfpe(int sig) {
    exit(1);
}

int main() {
    struct sigaction sa = { .sa_handler = handle_sigfpe };
    sigaction(SIGFPE, &sa, NULL);

    int a = 1, b = 0;
    a = a / b;  // Division by zero

    return 0;
}
