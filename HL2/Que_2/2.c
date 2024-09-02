/*
===========================================================================================================================
Name : 1a.c
Author : Harshal Purohit
Description : Write a program to print the system resource limits. Use getrlimit system call.
Date: 2nd Sept, 2024.
===========================================================================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

void rsrc_lmt(int resource, const char *resource_name) {
    struct rlimit limit;

    if (getrlimit(resource, &limit) == 0) {
        printf("%s:\n", resource_name);
        printf("  Soft limit: %ld\n", limit.rlim_cur);
        printf("  Hard limit: %ld\n\n", limit.rlim_max);
    } else {
        perror("getrlimit failed");
        exit(EXIT_FAILURE);
    }
}

int main() {
    rsrc_lmt(RLIMIT_CPU, "CPU time limit");
    rsrc_lmt(RLIMIT_FSIZE, "File size limit");
    rsrc_lmt(RLIMIT_STACK, "Stack size limit");
    rsrc_lmt(RLIMIT_NOFILE, "Number of open files limit");
    rsrc_lmt(RLIMIT_NPROC, "Number of processes limit");

    return 0;
}
