#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    while (1) {
        for (int i = 1; i <= 5; ++i) { 
            char filename[10];
            snprintf(filename, sizeof(filename), "file%d", i);
            int fd = open(filename, O_CREAT | O_WRONLY, 0644);
            if (fd < 0) {
                perror("open");
                return 1;
            }
            sleep(5);
            close(fd);
        }
    }
    return 0;
}
