/*
===========================================================================================================================
Name : 5.c
Author : Harshal Purohit
Description : Write a program to print the system limitation of
            a. maximum length of the arguments to the exec family of functions.
            b. maximum number of simultaneous process per user id.
            c. number of clock ticks (jiffy) per second.
            d. maximum number of open files
            e. size of a page
            f. total number of pages in the physical memory
            g. number of currently available pages in the physical memory.
Date: 7th Sept, 2024.
===========================================================================================================================
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/sysinfo.h>

int main() {

    printf("Maximum length of the arguments to exec: %ld\n", sysconf(_SC_ARG_MAX));
    printf("Maximum number of simultaneous processes per user id: %ld\n", sysconf(_SC_CHILD_MAX));
    printf("Number of clock ticks per second: %ld\n", sysconf(_SC_CLK_TCK));
    printf("Maximum number of open files: %ld\n", sysconf(_SC_OPEN_MAX));
    printf("Size of a page: %ld bytes\n", sysconf(_SC_PAGESIZE));
    printf("Total number of pages in physical memory: %ld\n", get_phys_pages());
    printf("Number of available pages in physical memory: %ld\n", get_avphys_pages());

    return 0;
}
