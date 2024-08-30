/*
===========================================================================================================================
Name : 4.c
Author : Harshal Purohit
Description : Write a program to open an existing file with read write mode.
Date: 18th Aug, 2024.
===========================================================================================================================
*/

#include <stdio.h>
#include <fcntl.h>  
#include <unistd.h> 

int main() {
    const char *file_path = "4.txt";  
    int fd = open(file_path, O_RDWR);
    printf("File Descriptor Value: %d\n", fd);
    return 0;
}
