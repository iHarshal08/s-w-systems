#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

void print_file_type(mode_t mode) {
    if (S_ISREG(mode)) {
        printf("Regular file\n");
    } else if (S_ISDIR(mode)) {
        printf("Directory\n");
    } else if (S_ISLNK(mode)) {
        printf("Symbolic link\n");
    } else if (S_ISCHR(mode)) {
        printf("Character device\n");
    } else if (S_ISBLK(mode)) {
        printf("Block device\n");
    } else if (S_ISFIFO(mode)) {
        printf("FIFO (Named pipe)\n");
    } else {
        printf("Unknown file type\n");
    }
}

int main() {
    const char *file_path = "file_type.txt";  
    struct stat file_stat;

    if (stat(file_path, &file_stat) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    print_file_type(file_stat.st_mode);

    return 0;
}
