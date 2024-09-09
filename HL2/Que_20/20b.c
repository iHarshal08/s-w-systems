/*
===========================================================================================================================
Name : 20b.c
Author : Harshal Purohit
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 8th Sept, 2024.
===========================================================================================================================
*/


                                                    /* Reader */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char msg[100];
    int fd = open("one_way_fifo", O_RDONLY);

    while (1) {
        read(fd, msg, sizeof(msg));
        printf("%s", msg);
    }

    return 0;
}


