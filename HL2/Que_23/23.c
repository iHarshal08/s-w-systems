/*
===========================================================================================================================
Name : 23.c
Author : Harshal Purohit
Description : Write a program to print the maximum number of files can be opened within a process and
size of a pipe (circular buffer).
Date: 10th Sept, 2024.
===========================================================================================================================
*/

#include <stdio.h>
#include <unistd.h>

int main() {

    printf("Max number of open files: %ld\n", sysconf(_SC_OPEN_MAX));
    printf("Pipe size: %ld bytes\n", fpathconf(STDIN_FILENO, _PC_PIPE_BUF));

    return 0;
}
