#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Using execvp:\n");
    char *argv[] = {"ls", "-Rl", NULL};
    execvp("ls", argv);
    return 1;
}
