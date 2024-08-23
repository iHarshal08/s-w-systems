#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define RECORD_SIZE 100  // Size of each record in bytes
#define NUM_RECORDS 3    // Number of records in the file

// Function to lock a record
int lock_record(int fd, off_t offset, int length, int lock_type) {
    struct flock fl;
    fl.l_type = lock_type;   // F_RDLCK for read lock, F_WRLCK for write lock
    fl.l_whence = SEEK_SET;
    fl.l_start = offset;
    fl.l_len = length;
    return fcntl(fd, F_SETLK, &fl);
}

void access_record(int fd, int record_num, int lock_type, const char *data) {
    off_t offset = record_num * RECORD_SIZE;
    
    if (lock_record(fd, offset, RECORD_SIZE, lock_type) == -1) {
        perror("Lock failed");
        exit(EXIT_FAILURE);
    }

    if (lock_type == F_WRLCK) {
        // Write record
        lseek(fd, offset, SEEK_SET);
        write(fd, data, RECORD_SIZE);
    } else {
        // Read record
        char buffer[RECORD_SIZE + 1];
        lseek(fd, offset, SEEK_SET);
        read(fd, buffer, RECORD_SIZE);
        buffer[RECORD_SIZE] = '\0';  // Null-terminate the string
        printf("Record %d: %s\n", record_num, buffer);
    }

    // Unlock the record
    lock_record(fd, offset, RECORD_SIZE, F_UNLCK);
}

int main() {
    const char *filename = "records.dat";
    int fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    // Initialize file with records if empty
    char initial_records[NUM_RECORDS][RECORD_SIZE] = {
        "Record 1: Initial Data",
        "Record 2: Initial Data",
        "Record 3: Initial Data"
    };
    
    for (int i = 0; i < NUM_RECORDS; ++i) {
        lseek(fd, i * RECORD_SIZE, SEEK_SET);
        write(fd, initial_records[i], RECORD_SIZE);
    }

    // Perform operations with locking
    access_record(fd, 0, F_RDLCK, NULL);       // Read lock record 0
    access_record(fd, 1, F_WRLCK, "Updated Record 2"); // Write lock record 1
    access_record(fd, 2, F_RDLCK, NULL);       // Read lock record 2

    close(fd);
    return EXIT_SUCCESS;
}
