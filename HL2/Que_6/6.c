/*
===========================================================================================================================
Name : 6.c
Author : Harshal Purohit
Description : Write a simple program to create three threads.
Date: 7th Sept, 2024.
===========================================================================================================================
*/

#include <stdio.h>
#include <pthread.h>

void* thread_function(void* arg) {
    int th_count = *(int*)arg;
    printf("Thread %d \n", th_count);
    return NULL;
}

int main() {
    pthread_t threads[3];
    int th_counts[3] = {1, 2, 3};

    for(int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, thread_function, &th_counts[i]);
    }

    for(int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
