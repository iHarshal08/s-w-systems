/*
===========================================================================================================================
Name : 15.c
Author : Harshal Purohit
Description : Write a program to display the environmental variable of the user (use environ).
Date: 22nd Aug, 2024.
===========================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main() {
    char **env = environ;

    while (*env) {
        printf("%s\n", *env);
        env++;
    }

    return 0;
}