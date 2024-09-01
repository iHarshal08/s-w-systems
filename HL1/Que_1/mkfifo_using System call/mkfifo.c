#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    const char *fifo_path = "my_fifo";
    
    // Create a FIFO
    if (mkfifo(fifo_path, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }
    
    printf("FIFO created: %s\n", fifo_path);
    
    return 0;
}
