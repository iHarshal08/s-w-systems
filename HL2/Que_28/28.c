/*
===========================================================================================================================
Name : 28.c
Author : Harshal Purohit
Description : Write a program to change the exiting message queue permission. (use msqid_ds structure)
Date: 10th Sept, 2024.
===========================================================================================================================
*/


#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t key = ftok("28.txt", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    struct msqid_ds info;
    msgctl(msgid, IPC_STAT, &info);

    info.msg_perm.mode = 0644;  // Change permissions to -rw-r--r--

    msgctl(msgid, IPC_SET, &info);  // Apply the changes

    printf("Permissions changed to 0644\n");
    return 0;
}
