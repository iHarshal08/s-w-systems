/*
===========================================================================================================================
Name : 6.c
Author : Harshal Purohit
Description : Write a program to take input from STDIN and display on STDOUT. Use only read/write system calls.
Date: 19th Aug, 2024.
===========================================================================================================================
*/


#include<unistd.h>
int main(){
    char buffer[1024];
    ssize_t bytesRead;
    bytesRead = read(0, buffer, sizeof(buffer)-1);
    if(bytesRead>0){
        buffer[bytesRead]='\0';
        write(1, buffer, bytesRead);
    }
    return 0;
}