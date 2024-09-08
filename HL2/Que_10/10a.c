
/*
===========================================================================================================================
Name : 10a.c
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

void handle_sigsegv(int sig) {
    exit(1);
}

int main() {
    struct sigaction sa = { .sa_handler = handle_sigsegv };
    sigaction(SIGSEGV, &sa, NULL);

    int *ptr = NULL;
    *ptr = 42;  // Segmentation fault but will not produce error due to "handle_sigsegv"

    return 0;
}
