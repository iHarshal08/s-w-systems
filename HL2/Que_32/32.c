/*
===========================================================================================================================
Name : 32.c
Author : Harshal Purohit
Description : Write a program to implement semaphore to protect any critical section.
            a. rewrite the ticket number creation program using semaphore
            b. protect shared memory from concurrent write access
            c. protect multiple pseudo resources ( may be two) using counting semaphore
            d. remove the created semaphore
Date: 18th Sept, 2024.
===========================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>   
#include <unistd.h>  
#include <sys/stat.h>

int tno = 0;
int rsrsc1 = 0, rsrc2 = 0;

sem_t *sem_binary, *sem_counting;

void create_ticket() {
    sem_wait(sem_binary); // Protect the critical section
    tno++;
    printf("Created Ticket Number: %d\n", tno);
    sem_post(sem_binary);
}

void access_shared_memory() {
    sem_wait(sem_binary); // Protect shared memory
    tno += 10; // Modification to shared memory
    printf("Updated Shared Memory: %d\n", tno);
    sem_post(sem_binary);
}

void useRsrc() {
    sem_wait(sem_counting); // Protect multiple resources
    if (rsrsc1 == 0) {
        rsrsc1 = 1;
        printf("Resource 1 in use.\n");
    } else if (rsrc2 == 0) {
        rsrc2 = 1;
        printf("Resource 2 in use.\n");
    }
    sleep(1); // Simulate resource usage
    if (rsrsc1 == 1) {
        rsrsc1 = 0;
        printf("Resource 1 released.\n");
    } else if (rsrc2 == 1) {
        rsrc2 = 0;
        printf("Resource 2 released.\n");
    }
    sem_post(sem_counting);
}

int main() {
    // Create and initialize semaphores
    sem_binary = sem_open("/binary_sem", O_CREAT, 0644, 1); 
    sem_counting = sem_open("/counting_sem", O_CREAT, 0644, 2); 

    if (sem_binary == SEM_FAILED || sem_counting == SEM_FAILED) {
        perror("sem_open failed");
        exit(EXIT_FAILURE);
    }

    create_ticket();
    access_shared_memory();
    useRsrc();
    useRsrc(); // Show counting semaphore in action

    sem_close(sem_binary);
    sem_close(sem_counting);
    sem_unlink("/binary_sem");
    sem_unlink("/counting_sem");

    return 0;
}
