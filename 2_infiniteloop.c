#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main() {
    while (1) {
        FILE *logfile = fopen("2_logfile.txt", "a");
        if (logfile) {
            fprintf(logfile, "Timestamp: %s", ctime(&(time_t){time(NULL)}));
            system("ls /proc >> 2_logfile.txt");
            fprintf(logfile, "-----\n");
            fclose(logfile);
        }
        sleep(10);
    }
    return 0;
}
