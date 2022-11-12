#ifndef __counting_scaling_h__
#define __counting_scaling_h__

#include "common-threads.h"

#define NUMCPUS 5

typedef struct __scounter_t {
    int global; // global count
    pthread_mutex_t glock; // global lock
    int local[NUMCPUS]; // per-CPU count
    pthread_mutex_t llock[NUMCPUS]; // ... and locks
    int threshold; // update frequency
} scounter_t;

// init: record threshold, init locks, init values
// of all local counts and global count
void scounter_init(scounter_t *c, int threshold);

// update: usually, just grab local lock and update
// local amount; once local count has risen ’threshold’,
// grab global lock and transfer local values to it
void scounter_update(scounter_t *c, int threadID, int amt);

// get: just return global amount (approximate)
int scounter_get(scounter_t *c);

#endif