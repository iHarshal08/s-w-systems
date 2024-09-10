/*
===========================================================================================================================
Name : 30.c
Author : Harshal Purohit
Description : Write a program to create a shared memory.
            a. write some data to the shared memory
            b. attach with O_RDONLY and check whether you are able to overwrite.
            c. detach the shared memory
            d. remove the shared memory
Date: 10th Sept, 2024.
===========================================================================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <fcntl.h> // for O_RDONLY

int main() {

    //Create shared memory
    key_t key = ftok("30.txt", 65); // Generate a unique key
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT); // Create shared memory
    
    //Attach to shared memory
    char *data = (char*) shmat(shmid, (void*)0, 0); // Read and write mode
    
    //Write data to shared memory
    strcpy(data, "Writing data to shared memory!");
    printf("Data written: %s\n", data);
    
    //Detach from shared memory
    shmdt(data);

    //Attach with O_RDONLY
    data = (char*) shmat(shmid, (void*)0, SHM_RDONLY); // Attach in read-only mode
    printf("Data in read-only mode: %s\n", data);

    //Try overwriting 
    strcpy(data, "New Data");
    printf("Attempt to overwrite: %s\n", data);

    //Detach from shared memory
    shmdt(data);

    //Remove shared memory
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
