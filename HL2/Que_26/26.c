/*
===========================================================================================================================
Name : 26.c
Author : Harshal Purohit
Description : Write a program to send messages to the message queue. Check $ipcs -q
Date: 10th Sept, 2024.
===========================================================================================================================
*/


#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key = ftok("progfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    struct msg_buffer message;
    message.msg_type = 1;  // Set message type
    strcpy(message.msg_text, "Hello, World!");

    msgsnd(msgid, &message, sizeof(message.msg_text), 0);

    printf("Message sent: %s\n", message.msg_text);

    return 0;
}
