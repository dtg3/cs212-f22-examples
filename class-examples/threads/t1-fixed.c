#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>

typedef struct {
    volatile int ready;
    pthread_mutex_t mtx;
    pthread_cond_t cond;
} control;

control ctrl;

void *my_thread_first(void *arg) {
    // A sleep to prove that it is working
    //  5 second delay
    sleep(5);

    // Since I know the program starts with ready set to 0
    //  I can safely print. If this were more complicated,
    //  I should grab the lock, check the value, and make
    //  sure I'm good to print.
    printf("%s\n", (char *) arg);
    
    // Grab the lock, set our variable to ready,
    //  and alert the thread(s) waiting on that condition
    //  they should wake back up and check again.
    pthread_mutex_lock(&ctrl.mtx);
    ctrl.ready = 1;
    pthread_cond_signal(&ctrl.cond);
    pthread_mutex_unlock(&ctrl.mtx);
    return NULL;
}


void *my_thread_second(void *arg) {
    // Secure a lock to check ready (avoid race condition)
    pthread_mutex_lock(&ctrl.mtx);
    
    // Why the while and not an if?
    //  It is possible that we encounter a spurious wakeup. Common reasons include:
    //     * The scheduler tries to run the thread
    //     * We have multiple threads and at some point in time were signaled, but
    //         couldn't respond, so the condition has since change back to not ready.
    //
    // THIS IS NOT BUSY WAITING!!!
    while(ctrl.ready == 0) {
        // Sleep until someone wakes me up via the condition variable
        pthread_cond_wait(&ctrl.cond, &ctrl.mtx);
    }
    // Remember that when wait returns the lock (mtx) is automatically acquired

    printf("%s\n", (char *) arg);
    
    pthread_mutex_unlock(&ctrl.mtx);
    return NULL;
}


int main(int argc, char *argv[]) {                    
    if (argc != 1) {
        fprintf(stderr, "usage: main\n");
        exit(1);
    }

    // Start my variable at 0 to indicate that
    //  the my_thread_second function is not ready to print.
    //  Note that this does not require any locking as I still
    //  currently only have one thread of execution.
    ctrl.ready = 0;
    pthread_mutex_init(&ctrl.mtx, NULL);
    pthread_cond_init(&ctrl.cond, NULL);
    

    pthread_t p1, p2;
    printf("main: begin\n");
    pthread_create(&p1, NULL, my_thread_second, "B"); 
    pthread_create(&p2, NULL, my_thread_first, "A");
    
    // join waits for the threads to finish
    pthread_join(p1, NULL); 
    pthread_join(p2, NULL); 
    printf("main: end\n");
    
    return 0;
}

