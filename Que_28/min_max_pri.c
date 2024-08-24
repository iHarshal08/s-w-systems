#include <stdio.h>
#include <stdlib.h>
#include <sched.h>

int main() {
    int max, min;
    max = sched_get_priority_max(SCHED_FIFO);
    min = sched_get_priority_min(SCHED_FIFO);
    printf("Real-time priority range for SCHED_FIFO:\n");
    printf("Maximum priority: %d\n", max);
    printf("Minimum priority: %d\n", min);
    return 0;
}
