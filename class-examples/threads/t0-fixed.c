#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

typedef struct {
    int max;
    volatile int value;
    pthread_mutex_t mtx;
} counter;

counter count; // shared global variable

void *mythread(void *arg) {
    char *letter = arg;
    int i; // stack (private per thread) 
    
    pthread_mutex_lock(&(count.mtx));
    printf("%s: begin [addr of i: %p]\n", letter, &i);
    for (i = 0; i < count.max; i++) {
        // Lock before race condition
	    ++count.value;
    }
    printf("%s: done\n", letter);
    // Release lock when we are done
    pthread_mutex_unlock(&count.mtx);

    return NULL;
}
                                                                             
int main(int argc, char *argv[]) {                    
    if (argc != 2) {
        fprintf(stderr, "usage: main-first <loopcount>\n");
        exit(1);
    }
    
    count.max = atoi(argv[1]);
    pthread_mutex_init(&count.mtx, NULL);
    count.value = 0;

    pthread_t p1, p2;
    printf("main: begin [counter = %d] [%lx]\n", count.value, (uintptr_t) &count.value);
    pthread_create(&p1, NULL, mythread, "A"); 
    pthread_create(&p2, NULL, mythread, "B");

    // join waits for the threads to finish
    pthread_join(p1, NULL); 
    pthread_join(p2, NULL); 
    printf("main: done\n [counter: %d]\n [should: %d]\n", count.value, count.max*2);
    
    return 0;

}

