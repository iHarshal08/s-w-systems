/*
===========================================================================================================================
Name : 12.c
Author : Harshal Purohit
Description : Write a program to find out the opening mode of a file. Use fcntl.
Date: 22nd Aug, 2024.
===========================================================================================================================
*/



#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

void file_mode(int flags) {

    printf("File mode:\n");

    if (flags & O_RDONLY) printf("Opened in Read-only\n");
    if (flags & O_WRONLY) printf("Opened in Write-only\n");
    if (flags & O_RDWR)   printf("Opened in Read and Write\n");
    
}

int main() {
    const char *file = "12.txt";  
    int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    int flags = fcntl(fd, F_GETFL);
    if (flags == -1) {
        perror("fcntl");
        close(fd);
        return 1;
    }

    file_mode(flags);

    close(fd);
    return 0;
}
