/*
===========================================================================================================================
Name : execl.c
Author : Harshal Purohit
Description : Write a program to execute ls -Rl by the following system calls
            a. execl
            b. execlp
            c. execled
            d. execv
            e. execvp
Date: 23rd Aug, 2024.
===========================================================================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("execl:\n");
    execl("/bin/ls", "ls", "-Rl", (char *)NULL);
    return 1;
}
