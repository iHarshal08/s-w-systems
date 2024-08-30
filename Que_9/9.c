/*
===========================================================================================================================
Name : 9.c
Author : Harshal Purohit

Description : Write a program to print the following information about a given file.
a. inode
b. number of hard links
c. uid
d. gid
e. size
f. block size
g. number of blocks
h. time of last access
i. time of last modification
j. time of last change

Date: 19th Aug, 2024.
===========================================================================================================================
*/


#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<time.h>

void print_file_info(const char *infoFile){
    struct stat file_stat; 
    printf("\nFile: %s\n", infoFile);
    printf("Inode: %ld\n",(long)file_stat.st_ino);
    printf("No. of hard links: %ld\n", (long)file_stat.st_nlink);
    printf("UID: %d\n", file_stat.st_uid);
    printf("GID: %d\n", file_stat.st_gid);
    printf("Size: %ld bytes\n", (long)file_stat.st_size);
    printf("Block Size: %ld bytes\n", (long)file_stat.st_blksize);
    printf("No. of Blocks: %ld\n",(long) file_stat.st_blocks);
    printf("Last access time: %s", ctime(&file_stat.st_atime));
    printf("Last modification time: %s", ctime(&file_stat.st_mtime));
    printf("Last status change time: %s\n", ctime(&file_stat.st_ctime));
}

int main(){
    const char *infoFile = "9.txt";
    print_file_info(infoFile);
    return 0;
}