/*
===========================================================================================================================
Name : 22.c
Author : Harshal Purohit
Description : Write a program, open a file, call fork, and then write to the file by both the child as well as the
            parent processes. Check output of the file.
Date: 23rd Aug, 2024.
===========================================================================================================================
*/


#include <stdio.h>
#include <unistd.h> //fork()
#include <fcntl.h>  
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    pid_t pid;
    int fd;
    fd = open("22.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    pid = fork();

    if (pid == 0) {
        //executed by the child process
        const char *child_message = "File written by child process.\n";
        close(fd);
        printf("Child wrote to file.\n");
    } 
    else {
        //executed by the parent process
        const char *parent_message = "File written by parent process.\n";
        close(fd);
        printf("Parent wrote to file.\n");
    }
    close(fd);
    return 0;
}
