#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>

int main() {
    // Define the command and arguments to pass to the executable
    char *command = "./a.out";
    char *name = "Harshal (MT2024056)";
    char *args[] = {command, name, NULL};

    execvp(command, args);
    return 1;
}
