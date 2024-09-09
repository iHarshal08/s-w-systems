/*
===========================================================================================================================
Name : 21b.c
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
    int fd1 = open("fifo_first", O_RDONLY);
    int fd2 = open("fifo_second", O_WRONLY);

    while (1) {
        read(fd1, msg, 100);
        printf("Friend: %s", msg);
        printf("You: ");
        fgets(msg, 100, stdin);
        write(fd2, msg, 100);
    }

    return 0;
}
