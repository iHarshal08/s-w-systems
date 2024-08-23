#include <stdio.h>
#include <unistd.h>  //fork() and sleep()
#include <sys/types.h>

int main() {
    pid_t pid;
    pid = fork();
    if (pid == 0) {
        printf("Child process: PID = %d\n", getpid());
        _exit(0);
    } 
    else {
        printf("Parent process: PID = %d\n", getpid());
        printf("Parent sleeps for 30 seconds...\n");
        // parent sleep for 30 sec making child zombie
        sleep(30);
    }
    return 0;
}
