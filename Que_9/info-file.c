#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<time.h>

void print_file_info(const char *infoFile){
    struct stat file_stat; 
    
    //get file stats
    if(stat(infoFile, &file_stat)==-1){
        perror("Failed to get file stats");
        exit(EXIT_FAILURE);
    }

    //Print file info.
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
    const char *infoFile = "info-file.txt";
    print_file_info(infoFile);
    return 0;
}