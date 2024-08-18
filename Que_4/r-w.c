#include <stdio.h>
#include <fcntl.h>  
#include <unistd.h> 

int main() {
    const char *file_path = "r-w.txt";  
    int fd = open(file_path, O_RDWR);
    
    if (fd == -1) {
        perror("created");
        return 1;
    }

    printf("File Descriptor Value: %d\n", fd);
    if (close(fd) == -1) {
        perror("created");
        return 1;
    }

    return 0;
}
