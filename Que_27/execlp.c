#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Using execlp:\n");
    execlp("ls", "ls", "-Rl", (char *)NULL);
    return 1;
}
