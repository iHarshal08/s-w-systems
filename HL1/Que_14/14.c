/*
===========================================================================================================================
Name : 14.c
Author : Harshal Purohit
Description : Write a program to find the type of a file.
            a. Input should be taken from command line.
            b. program should be able to identify any type of a file.
Date: 22nd Aug, 2024.
===========================================================================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

void print_file_type(mode_t mode) {
    if (S_ISREG(mode)) {
        printf("Regular file\n");
    } else if (S_ISDIR(mode)) {
        printf("Directory\n");
    } else if (S_ISLNK(mode)) {
        printf("Symbolic link\n");
    } else if (S_ISCHR(mode)) {
        printf("Character device\n");
    } else if (S_ISBLK(mode)) {
        printf("Block device\n");
    } else if (S_ISFIFO(mode)) {
        printf("FIFO (Named pipe)\n");
    } else {
        printf("Unknown file type\n");
    }
}

int main() {
    const char *file_path = "14.txt";  
    struct stat file_stat;

    stat(file_path, &file_stat);

    print_file_type(file_stat.st_mode);

    return 0;
}
