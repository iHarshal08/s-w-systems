#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Using execle:\n");
    execle("/bin/ls", "ls", "-Rl", (char *)NULL, NULL);
    return 1;
}
