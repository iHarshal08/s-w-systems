/*
===========================================================================================================================
Name : 3.c
Author : Harshal Purohit
Description : Write a program to set (any one) system resource limit. Use setrlimit system call.
Date: 4th Sept, 2024.
===========================================================================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

int main() {
    struct rlimit rl;

    rl.rlim_cur = 1; // Soft limit
    rl.rlim_max = 2; // Hard limit

    setrlimit(RLIMIT_CPU, &rl);

    printf("CPU time limit set to 1 second.\n");

    while (1);

    return EXIT_SUCCESS;
}
