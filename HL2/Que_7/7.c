/*
===========================================================================================================================
Name : 7.c
Author : Harshal Purohit
Description : Write a simple program to print the created thread ids.
Date: 7th Sept, 2024.
===========================================================================================================================
*/


#include <stdio.h>
#include <pthread.h>

void* thread(void* arg) {
    pthread_t thread_id = pthread_self();
    printf("Thread ID: %lu\n", thread_id);
    return NULL;
}

int main() {
    pthread_t threads[3];

    for(int i = 0; i < 3; i++) 
        pthread_create(&threads[i], NULL, thread, NULL);
    
    for(int i = 0; i < 3; i++) 
        pthread_join(threads[i], NULL);

    return 0;
}
