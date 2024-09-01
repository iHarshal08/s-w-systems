/*
===========================================================================================================================
Name : 2.c
Author : Harshal Purohit
Description : Write a simple program to execute in an infinite loop at the background. Go to /proc directory and
identify all the process related information in the corresponding proc directory.
Date: 18th Aug, 2024.
===========================================================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main() {
    while (1) {
        FILE *logfile = fopen("2.txt", "a");
        if (logfile) {
            fprintf(logfile, "Timestamp: %s", ctime(&(time_t){time(NULL)}));
            system("ls /proc >> 2.txt");
            fprintf(logfile, "-----\n");
            fclose(logfile);
        }
        sleep(10);
    }
    return 0;
}
