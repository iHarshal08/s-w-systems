/*
===========================================================================================================================
Name : 10.c
Author : Harshal Purohit
Description : Write a program to open a file with read write mode, write 10 bytes, move the file pointer by 10
bytes (use lseek) and write again 10 bytes.
    a. check the return value of lseek.
    b. open the file with od and check the empty spaces in between the data.
Date: 19th Aug, 2024.
===========================================================================================================================
*/


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include <sys/stat.h>
int main(){
    const char *file_lseek = "10.txt";
    int fd;
    ssize_t bytes_written;
    off_t offset;
    char buffer1[11]="HARSHAL056"; //10 bytes + '\0'
    char buffer2[11]="PUROHIT056";

    fd = open(file_lseek, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if(fd==-1){
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    offset = lseek(fd, 10, SEEK_CUR);

    if(offset==-1){
        perror("Failed to move file pointer ");
        close(fd);
        exit(EXIT_FAILURE);
    }

    bytes_written = write(fd, buffer2, 10);
    
    if(bytes_written != 10){
        perror("Failed to write 10 bytes ");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);

    printf("Task Done");
    return 0;
}