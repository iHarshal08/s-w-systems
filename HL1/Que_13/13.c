/*
===========================================================================================================================
Name : 13.c
Author : Harshal Purohit
Description : Write a program to wait for a STDIN for 10 seconds using select. Write a proper print statement to
        verify whether the data is available within 10 seconds or not (check in $man 2 select).
Date: 22nd Aug, 2024.
===========================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>

int main() {
    fd_set readfds;
    struct timeval timeout;
    int retval;
    char buffer[100];
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    printf("Waiting for input for 10 seconds...\n");

    retval = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);

    if (retval == -1) {
        perror("select()");
        exit(EXIT_FAILURE);
    } else if (retval) {
        printf("Data is available. Enter your input: ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            printf("Input received: %s", buffer);
        }
    } else {
        printf("No input received within the timeout period.\n");
    }

    return 0;
}