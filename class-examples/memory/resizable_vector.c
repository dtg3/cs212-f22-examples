/* 
    Simple resizable vector.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct vector {
    size_t size;
    int *items;
};

void push(struct vector* v, int i) {
    ++(v->size);
    
    v->items = realloc(v->items, sizeof(int)*v->size);
    assert(v->items != NULL);
    
    v->items[v->size - 1] = i;
}

int pop(struct vector* v) {
    assert(v->size > 0);

    int value = v->items[v->size - 1];
    --(v->size);
    v->items = realloc(v->items, sizeof(int)*v->size);

    return value;
}

struct vector init_vector() {
    struct vector v;
    v.items = NULL;
    v.size = 0;
    return v;
}

void free_vector(struct vector* v) {
    free(v->items);
    v->size = 0;
}

int main(int argc, char *argv[]) {

    struct vector my_vector = init_vector();
    push(&my_vector, 10);
    push(&my_vector, 40);
    push(&my_vector, 90);

    printf("%d\n", pop(&my_vector));

    free_vector(&my_vector);

    return 0;
}
