
/*
===========================================================================================================================
Name : 11.c
Author : Harshal Purohit
Description : Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal -
            use sigaction system call.
Date: 8th Sept, 2024.
===========================================================================================================================
*/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    struct sigaction sa;

    sa.sa_handler = SIG_IGN;  
    sigaction(SIGINT, &sa, NULL);
    printf("SIGINT ignored. Sleep for 5 sec.....\n");
    sleep(5);

    sa.sa_handler = SIG_DFL; 
    sigaction(SIGINT, &sa, NULL);
    printf("\nSIGINT reset. Sleep again for 5 sec.....\n");
    sleep(5);

    return 0;
}
