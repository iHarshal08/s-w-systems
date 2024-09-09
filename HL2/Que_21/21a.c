/*
===========================================================================================================================
Name : 21a.c
Author : Harshal Purohit
Description : Write two programs so that both can communicate by FIFO -Use two way communications.
Date: 9th Sept, 2024.
===========================================================================================================================
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char msg[100];
    int fd1 = open("fifo_first", O_WRONLY);
    int fd2 = open("fifo_second", O_RDONLY);

    while (1) {
        printf("You: ");
        fgets(msg, 100, stdin);
        write(fd1, msg, 100);
        read(fd2, msg, 100);
        printf("Friend: %s", msg);
    }

    return 0;
}
