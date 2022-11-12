#include <stdio.h>
#include "common-threads.h"
#include "counting-scaling.h"

// Shared global struct for this example
scounter_t scount;

// Function to have the threads perform
void* scaling_threads(void* args) {
    int* t_id = (int*) args;
    for(int i = 0; i < 20; ++i) {
        scounter_update(&scount, *t_id, 1);
    }
    return NULL;
}

void scaling_counter_experiment() {    
    scounter_init(&scount, 10);
    pthread_t threads[NUMCPUS];
    
    for (int i = 0; i < NUMCPUS; ++i) {
        // Create multiple threads
        Pthread_create(&threads[i], NULL, scaling_threads, &i);
    }

    // Intermediate value (NOT FINAL)
    printf("RUNNING SAMPLE: %d\n", scounter_get(&scount));

    // Wait for all the threads to finish
    for (int i = 0; i < NUMCPUS; ++i) {
        Pthread_join(threads[i], NULL);
    }

    // Final Value
    printf("COMPLETE RESULT: %d\n", scounter_get(&scount));
}


int main(int argc, char* argv[]) {
    scaling_counter_experiment();   
    return 0;
}