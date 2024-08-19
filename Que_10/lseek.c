#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include <sys/stat.h>
int main(){
    const char *file_lseek = "file-lseek.txt";
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