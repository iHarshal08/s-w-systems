#include <stdio.h>
#include <fcntl.h>  // For creat() and O_RDWR
#include <unistd.h> // For close()
#include <sys/stat.h>

int main() {
    const char *file_path = "FileDescriptorValue.txt";
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; // Read/write for owner, read for group and others
    int fd = creat(file_path, mode);
    
    if (fd == -1) {
        perror("created");
        return 1;
    }

    printf("File descriptor: %d\n", fd);

    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}
