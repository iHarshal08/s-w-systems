#include <stdio.h>
#include <unistd.h> //fork()
#include <fcntl.h>  // For open()
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    pid_t pid;
    int fd;
    fd = open("fork_file.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    // Create a new process
    pid = fork();

    if (pid == 0) {
        //executed by the child process
        const char *child_message = "File written by child process.\n";
        close(fd);
        printf("Child wrote to file.\n");
    } 
    else {
        //executed by the parent process
        const char *parent_message = "File written by parent process.\n";
        close(fd);
        printf("Parent wrote to file.\n");
    }
    close(fd);
    return 0;
}
