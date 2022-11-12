#include "common-threads.h"
#include "counting-scaling.h"

#define NUMCPUS 5

// init: record threshold, init locks, init values
// of all local counts and global count
void scounter_init(scounter_t *c, int threshold) {
    c->threshold = threshold;
    c->global = 0;
    Mutex_init(&c->glock);
    int i;
    for (i = 0; i < NUMCPUS; i++) {
        c->local[i] = 0;
        Mutex_init(&c->llock[i]);
    }
}

// update: usually, just grab local lock and update
// local amount; once local count has risen ’threshold’,
// grab global lock and transfer local values to it
void scounter_update(scounter_t *c, int threadID, int amt) {
    int cpu = threadID % NUMCPUS;
    Mutex_lock(&c->llock[cpu]);
    c->local[cpu] += amt;
    if (c->local[cpu] >= c->threshold) {
        // transfer to global (assumes amt>0)
        Mutex_lock(&c->glock);
        c->global += c->local[cpu];
        Mutex_unlock(&c->glock);
        c->local[cpu] = 0;
    }
    Mutex_unlock(&c->llock[cpu]);
}

// get: just return global amount (approximate)
int scounter_get(scounter_t *c) {
    Mutex_lock(&c->glock);
    int val = c->global;
    Mutex_unlock(&c->glock);
    return val; // only approximate!
}