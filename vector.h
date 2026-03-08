#ifndef VECTOR_H
#define VECTOR_H
#include <stddef.h>

typedef struct {
    size_t item_size;
    int size;
    int used;
    void *array;
} Vector;

void vector_initialize(Vector *v, size_t it_size);

void vector_push(Vector *v, void *src);

void vector_get(Vector *v, int index, void *dst);

int vector_get_size(Vector *v);

void vector_free(Vector *v);

#endif
