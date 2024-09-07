/*
===========================================================================================================================
Name : 9.c
Author : Harshal Purohit
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT
signal - Use signal system call.
Date: 7th Sept, 2024.
===========================================================================================================================
*/


#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void ignore_sigint(int sig) {}

int main() {
    
    signal(SIGINT, ignore_sigint);

    printf("SIGINT is now being ignored. Press Ctrl+C to test.\n");
    sleep(10); 
    
    signal(SIGINT, SIG_DFL);

    printf("\nSIGINT action has been reset to default. Press Ctrl+C to test.\n");
    sleep(10);

    return 0;
}
