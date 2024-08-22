#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

#define FILENAME "duplicate.txt"
#define BUFFER1 "This is written using original fd.\n"
#define BUFFER2 "This is written using dup fd.\n"
#define BUFFER3 "This is written using dup2 fd.\n"
#define BUFFER4 "This is written using fcntl fd.\n"

void check_file_update(){
    FILE *file = fopen(FILENAME,"r");
    if(!file){
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    char ch;
    while ((ch = fgetc(file)) != EOF){
        putchar(ch);
    }
    fclose(file);
}

int main(){
    int fd = open(FILENAME, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if(fd<0){
        perror("open");
        exit(EXIT_FAILURE);
    }
    //using org. fd
    if(write(fd, BUFFER1, sizeof(BUFFER1)-1)<0){
        perror("write");
        exit(EXIT_FAILURE);
    }
    
    /************************** */

    //Duplicate fd using dup
    int fd_dup = dup(fd);
    if(fd_dup < 0){
        perror("dup");
        exit(EXIT_FAILURE);
    }
    //write using the duplicated fd
    if(write(fd_dup, BUFFER2, sizeof(BUFFER2)-1)<0){
        perror("write");
        exit(EXIT_FAILURE);
    }

    /*************************** */

    //Duplicate the fd using dup2
    int fd_dup2 = dup2(fd, 10);
    if(fd_dup2 < 0){
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    //duplicated fd from dup2
    if(write(fd_dup2, BUFFER3, sizeof(BUFFER3)-1)<0){
        perror("write");
        exit(EXIT_FAILURE);
    }

    /*************************** */

    //Duplicate the fd using fcntl
    int fd_fcntl = fcntl(fd, F_DUPFD, 0);
    if(fd_fcntl < 0){
        perror("fcntl");
        exit(EXIT_FAILURE);
    }
    //duplicated fd from fcntl
    if(write(fd_fcntl, BUFFER4, sizeof(BUFFER4)-1)<0){
        perror("write");
        exit(EXIT_FAILURE);
    }

    close(fd);
    close(fd_dup);
    close(fd_dup2);
    close(fd_fcntl);

    //checking file
    printf("File Contents '%s':\n",FILENAME);
    check_file_update();
    return 0;

}