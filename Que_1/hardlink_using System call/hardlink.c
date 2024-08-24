#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    const char *target = "file_hardlink.txt";
    const char *linkpath = "hard_link.txt";
    
    if (access(linkpath, F_OK) != -1) {
        if (unlink(linkpath) == -1) {
            perror("unlink");
            exit(EXIT_FAILURE);
        }
    }
    // Create a hard link
    if (link(target, linkpath) == -1) {
        perror("link");
        exit(EXIT_FAILURE);
    }
    
    printf("Hard link created: %s -> %s\n", linkpath, target);
    
    return 0;
}
