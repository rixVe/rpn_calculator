#ifndef VECTOR_H
#define VECTOR_H
#include <stddef.h>

typedef struct {
  size_t item_size;
  int size;
  int used;
  void* array;
} Vector;

void initialize_vector(Vector* v, size_t it_size);
void push_vector(Vector* v, void* src);
void get_vector(Vector* v,int index,  void* dst);
int get_size_vector(Vector* v);
void free_vector(Vector* v);

#endif
