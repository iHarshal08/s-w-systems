/*
===========================================================================================================================
Name : 31b.c
Author : Harshal Purohit
Description : Write a program to create a semaphore and initialize value to the semaphore.
            a. create a binary semaphore
            b. create a counting semaphore
Date: 18th Sept, 2024.
===========================================================================================================================
*/

#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h> // For O_CREAT
#include <sys/stat.h> // For mode constants

int main() {
    sem_t *counting_semaphore;

    // Create and initialize the counting semaphore with initial value 3
    counting_semaphore = sem_open("/counting_sem", O_CREAT, 0644, 3);

    if (counting_semaphore == SEM_FAILED) {
        perror("sem_open failed");
        return 1;
    }

    printf("Counting semaphore created and initialized to 3.\n");

    sem_close(counting_semaphore);
    sem_unlink("/counting_sem");

    return 0;
}
