#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    const char *target = "file_symlink.txt";
    const char *linkpath = "symlink.txt";

    if (access(linkpath, F_OK) != -1) {
        if (unlink(linkpath) == -1) {
            perror("unlink");
            exit(EXIT_FAILURE);
        }
    }
    
    if (symlink(target, linkpath) == -1) {
        perror("symlink");
        exit(EXIT_FAILURE);
    }
    
    printf("Symlink: %s -> %s\n", linkpath, target);
    
    return 0;
}
