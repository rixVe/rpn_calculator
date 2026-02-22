#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include <stdbool.h>

typedef struct {
  int size;
  int top;
  size_t item_size;
  void* array;
} Stack;

void initialize_stack(Stack* s, size_t it_size);

void push_stack(Stack* s, void* element);

void pop_stack(Stack* s, void* dst);

void peep_stack(Stack* s, void* dst);

bool is_empty_stack(Stack*s);

void free_stack(Stack* s);
#endif
