#include "vector.h"
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

void initialize_vector(Vector* v, size_t it_size){
  v->item_size = it_size;
  v->size = 8;
  v->used = 0;
  v->array = malloc(v->item_size*(v->size));
}

void push_vector(Vector* v, void* src) {
  if(v->used >= v->size) {
    v->size = 2*v->size + 1;
    v->array = realloc(v->array, v->item_size*v->size);
  }
  void* dst = v->array + v->used * v->item_size;
  v->used += 1;
  memcpy(dst, src, v->item_size);
}
void get_vector(Vector* v,int index,  void* dst) {
  if(index >= v->used) {
    return;
  }
  void* src = v->array + v->item_size*index;
  memcpy(dst,src, v->item_size);
}
int get_size_vector(Vector* v) {
  return v->used;
}
void free_vector(Vector* v) {
  v->size = 0;
  v->used = 0;
  free(v->array);
}
