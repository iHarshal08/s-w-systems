/*
===========================================================================================================================
Name : 30.c
Author : Harshal Purohit
Description : Write a program to run a script at a specific time using a Daemon process.
Date: 30th Aug, 2024.
===========================================================================================================================
*/

#include<unistd.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
    if(!fork()){
        setsid();
        chdir("/");
        umask(0);
            while(1){
                sleep(4);
                printf("Child pid: %d\n",getpid());
                printf("Daemon Process is running.....\n");
            }
    }
    else    
        exit(0);
}
