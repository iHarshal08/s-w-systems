/*
===========================================================================================================================
Name : 20a.c
Author : Harshal Purohit
Description : Write two programs so that both can communicate by FIFO -Use one way communication.
Date: 8th Sept, 2024.
===========================================================================================================================
*/

                                        /* Writer */
#include <fcntl.h>
#include <unistd.h>

int main() {
    char msg[100];
    int fd = open("one_way_fifo", O_WRONLY);

    while (1) {
        write(fd, "\nHello from Writer Program!!!\n", 29);
        sleep(1);
    }

    return 0;
}






