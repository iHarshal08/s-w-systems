/*
===========================================================================================================================
Name : 8a.c
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
#include <stdlib.h>

void segmentation_fault(int sig) {
    printf("Segmentation Fault\n");
    exit(1);
}

int main() {
    signal(SIGSEGV, segmentation_fault);

    int *p = NULL;
    *p = 10;

    return 0;
}