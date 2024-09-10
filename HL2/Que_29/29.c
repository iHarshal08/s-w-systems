/*
===========================================================================================================================
Name : 29.c
Author : Harshal Purohit
Description : Write a program to remove the message queue.
Date: 10th Sept, 2024.
===========================================================================================================================
*/


#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t key = ftok("29.txt", 65);

    // Create the message queue if it doesn't exist (IPC_CREAT ensures creation)
    int msgid = msgget(key, 0666 | IPC_CREAT);

    if (msgid == -1) {
        printf("Failed to create or access the message queue.\n");
        return 1;
    } else
        printf("Message queue created with ID: %d\n", msgid);

    // Now remove the message queue
    msgctl(msgid, IPC_RMID, NULL);
    printf("Message queue removed.\n");

    return 0;
}
