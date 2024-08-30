/*
===========================================================================================================================
Name : 29.c
Author : Harshal Purohit
Description : Write a program to get scheduling policy and modify the scheduling policy (SCHED_FIFO,
SCHED_RR).
Date: 24th Aug, 2024.
===========================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>

void print_policy(int policy) {
    switch (policy) {
        case SCHED_FIFO:
            printf("Curre. policy: SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("Curr. policy: SCHED_RR\n");
            break;
        case SCHED_OTHER:
            printf("Curr. policy: SCHED_OTHER\n");
            break;
        default:
            printf("Curr. policy: Unknown\n");
            break;
    }
}

int main() {
    int policy;
    struct sched_param param;

    // Get current scheduling policy
    policy = sched_getscheduler(getpid());
    print_policy(policy);

    // Set the scheduling policy to SCHED_FIFO
    param.sched_priority = 10; 
    if (sched_setscheduler(getpid(), SCHED_FIFO, &param) == -1) {
        perror("sched_setscheduler SCHED_FIFO");
        exit(EXIT_FAILURE);
    }

    printf("Changed scheduling policy to SCHED_FIFO\n");

    policy = sched_getscheduler(getpid());
    print_policy(policy);

    // Set the scheduling policy back to SCHED_RR
    param.sched_priority = 10; 
    if (sched_setscheduler(getpid(), SCHED_RR, &param) == -1) {
        perror("sched_setscheduler SCHED_RR");
        exit(EXIT_FAILURE);
    }
    printf("Changed scheduling policy to SCHED_RR\n");
    policy = sched_getscheduler(getpid());
    print_policy(policy);
    return 0;
}
