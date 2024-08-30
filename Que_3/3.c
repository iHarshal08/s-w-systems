/*
===========================================================================================================================
Name : 3.c
Author : Harshal Purohit
Description : Write a program to create a file and print the file descriptor value. Use creat ( ) system call.
Date: 18th Aug, 2024.
===========================================================================================================================
*/

#include <stdio.h>
#include <fcntl.h>  
#include <unistd.h> 
#include <sys/stat.h>

int main() {
    const char *file_path = "3.txt";
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; // Read/write for owner, read for group and others
    int fd = creat(file_path, mode);
    printf("File descriptor: %d\n", fd);
    return 0;
}
