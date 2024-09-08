/*
===========================================================================================================================
Name : 10b.c
Author : Harshal Purohit
Description : Write a separate program using sigaction system call to catch the following signals.
            a. SIGSEGV
            b. SIGINT
            c. SIGFPE
Date: 8th Sept, 2024.
===========================================================================================================================
*/

#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void handle_sigint(int sig) {}

int main() {
    struct sigaction sa = { .sa_handler = handle_sigint };
    sigaction(SIGINT, &sa, NULL);

    while (1) 
        sleep(1);  
}
