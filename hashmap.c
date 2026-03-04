#include "hashmap.h"
#include <stdint.h>
#include <stdlib.h>

uint64_t FNV_offset_basis = 0xcbf29ce484222325;
uint64_t FNV_prime = 0x100000001b3;

uint64_t hash(char* data, size_t data_len) {
  uint64_t ret = FNV_offset_basis;
  for(size_t i = 0; i < data_len; ++i) {
    ret ^= data[i];
    ret *= FNV_prime;
  }
  return ret;
}

void map_initialize(Map* map) {
  map->used = 0;
  map->capacity = 8;
  map->array = malloc(8*sizeof(Entry));
  for(size_t i = 0; i < map->capacity; ++i) {
    map->array[i].key = NULL;
    map->array[i].value = NULL;
  }
}


void map_free(Map* map) {
  map->used = 0;
  map->capacity = 0;
  free(map->array);
}

