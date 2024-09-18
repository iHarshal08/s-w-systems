/*
===========================================================================================================================
Name : 31a.c
Author : Harshal Purohit
Description : Write a program to create a semaphore and initialize value to the semaphore.
            a. create a binary semaphore
            b. create a counting semaphore
Date: 18th Sept, 2024.
===========================================================================================================================
*/

#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h> // For mode constants

int main() {
    sem_t *binary_semaphore;

    // Create and initialize the binary semaphore with initial value 1
    binary_semaphore = sem_open("/binary_sem", O_CREAT, 0644, 1);

    if (binary_semaphore == SEM_FAILED) {
        perror("sem_open failed");
        return 1;
    }

    printf("Binary semaphore created and initialized to 1.\n");

    sem_close(binary_semaphore);
    sem_unlink("/binary_sem");

    return 0;
}
