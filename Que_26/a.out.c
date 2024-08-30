/*
===========================================================================================================================
Name : a.out.c
Author : Harshal Purohit
Description : Write a program to execute an executable program.
        a. use some executable program
        b. pass some input to an executable program. (for example execute an executable of $./a.out name)
Date: 23rd Aug, 2024.
===========================================================================================================================
*/


#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Hello, %s!\n", argv[1]);
    return 0;
}
