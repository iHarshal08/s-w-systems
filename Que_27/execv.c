#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Using execv:\n");
    char *argv[] = {"ls", "-Rl", NULL};
    execv("/bin/ls", argv);
    return 1;
}
