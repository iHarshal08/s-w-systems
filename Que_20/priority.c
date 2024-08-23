#include <stdio.h>
#include <unistd.h> // For sleep()

int main() {
    // Run indefinitely
    while (1) {
        sleep(10); 
    }
    return 0;
}
