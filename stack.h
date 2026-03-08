#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    int size;
    int top;
    size_t item_size;
    void *array;
} Stack;

void stack_initialize(Stack *s, size_t it_size);

void stack_push(Stack *s, void *element);

void stack_pop(Stack *s, void *dst);

void stack_peep(Stack *s, void *dst);

bool stack_is_empty(Stack *s);

void stack_free(Stack *s);
#endif
