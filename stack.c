#include <stddef.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "stack.h"


void initialize_stack(Stack* s, size_t it_size) {
  s->size = 8;
  s->item_size = it_size;
  s->top = -1;
  s->array = malloc(s->item_size*s->size);
}

void push_stack(Stack* s, void* element) {
  if(s->top >= s->size - 1) {
    s->array = realloc(s->array, s->item_size*(s->size * 2 + 1));
    s->size = s->size * 2 + 1;
  }
  s->top += 1;
  void* dst = s->array + s->top*s->item_size;
  memcpy(dst, element, s->item_size);
}

void pop_stack(Stack* s, void* dst) {
  if(s->top < 0) {
    return;
  }
  void* src = s->array + s->item_size*s->top;
  s->top -=1;
  memcpy(dst,src, s->item_size);
}

void peep_stack(Stack* s, void* dst) {
  if (s->top < 0) {
    return;
  }
  void* src = s->array + s->top*s->item_size;
  memcpy(dst, src, s->item_size);
}

bool is_empty_stack(Stack*s) {
  return s->top < 0;  
}

void free_stack(Stack* s) {
  free(s->array);
  s->size = 0;
  s->top = -1;
}
