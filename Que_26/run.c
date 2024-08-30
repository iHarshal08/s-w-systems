/*
===========================================================================================================================
Name : run.c
Author : Harshal Purohit
Description : Write a program to execute an executable program.
        a. use some executable program
        b. pass some input to an executable program. (for example execute an executable of $./a.out name)
Date: 23rd Aug, 2024.
===========================================================================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>

int main() {
    char *command = "./a.out";
    char *name = "Harshal (MT2024056)";
    char *args[] = {command, name, NULL};

    execvp(command, args);
    return 1;
}
