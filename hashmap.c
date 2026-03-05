#include <stdatomic.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hashmap.h"

uint64_t FNV_offset_basis = 0xcbf29ce484222325;
uint64_t FNV_prime = 0x100000001b3;


uint64_t hash(char* data, size_t data_capacity) {
  uint64_t ret = FNV_offset_basis;
  for(size_t i = 0; i < data_capacity; ++i) {
    ret ^= data[i];
    ret *= FNV_prime;
  }
  return ret;
}

void map_initialize(Map* map, size_t key_size, size_t value_size) {
  map->used = 0;
  map->capacity = 8;
  map->key_size = key_size;
  map->value_size = value_size;
  
  map->buckets = malloc(8*sizeof(Entry));
  for(size_t i = 0; i < 8; ++i) {
    map->buckets[i].key = NULL;
    map->buckets[i].value = NULL;
  }

  map->data = malloc(8*(key_size+value_size));
  map->data_capacity = 8;
  map->data_used = 0;
}

void* map_get_value(Map* map, void* key) {
  size_t index = hash(key, map->key_size)%map->capacity;
  if(map->buckets[index].key == NULL) {
    return NULL;
  }
  for(size_t i = 0; i < map->capacity; i++) {

    if(memcmp(map->buckets[(index+i)%map->capacity].key, key, map->key_size) == 0) {
      return map->buckets[(index+i)%map->capacity].value;
    }
  }
  return NULL;
}
bool map_contains_key(Map* map, void* key) {
  return map_get_value(map, key) != NULL;
}

void map_check_resize(Map* m) {
  if(5*m->used < 3*m->capacity) {
    return;
  }
  Entry* new_buckets = malloc(2*m->capacity * sizeof(Entry) + sizeof(Entry));
  for(size_t i = 0; i < 2*m->capacity+1; ++i) {
    new_buckets[i].key = NULL;
    new_buckets[i].value = NULL;
  }
  for(size_t i = 0; i < m->capacity; ++i) {
    if(m->buckets[i].key == NULL) {
      continue;
    }
    size_t j = hash(m->buckets[i].key, m->key_size)%(2*m->capacity +1);
    while(new_buckets[j].key != NULL) {
      j+=1;
      j%=2*m->capacity+1;
    }
    new_buckets[j] = m->buckets[i];
  }
  free(m->buckets);
  m->buckets = new_buckets;
  m->capacity = m->capacity*2+1;
}

void map_set(Map* map, void* key, void* value) {
  map_check_resize(map);
  if(map_contains_key(map, key)) {
    void* ptr = map_get_value(map, key);
    memcpy(ptr, value, map->value_size);
    return;
  }
  size_t index = hash(key, map->key_size)%map->capacity;
  size_t i = 0;
  for(i = 0; i < map->capacity; i++) {
    if(map->buckets[(index+i)%map->capacity].key == NULL) {
      break;
    }
  }
  if(map->data_used >= map->data_capacity) {
    void* new_data = malloc((map->key_size + map->value_size)*(map->data_capacity*2+1));
    for(size_t k = 0; k < map->capacity; k++) {
      if(map->buckets[k].key != NULL) {
        map->buckets[k].key += (new_data-map->data);
        map->buckets[k].value += (new_data-map->data);
      }
    }
    memcpy(new_data, map->data, map->data_capacity*(map->key_size + map->value_size));
    free(map->data);
    map->data = new_data;
    map->data_capacity = map->data_capacity*2+1;
  }
  memcpy((map->data + map->data_used*(map->key_size + map->value_size)), key, map->key_size);
  memcpy((map->data + map->data_used*(map->key_size + map->value_size) + map->key_size), value, map->value_size);

  map->buckets[(index+i)%map->capacity].key = map->data + (map->data_used*(map->key_size + map->value_size));
  map->buckets[(index+i)%map->capacity].value = map->data + map->data_used*(map->key_size + map->value_size) + map->key_size;
  map->used+=1;
  map->data_used+=1;
 }

Entry map_iter(Map* map, int index) {
  if(index >= map->used) {
    exit(1);
  }
  int counter = 0;
  int i;
  for(i = 0; i < map->capacity; ++i) {
    if(map->buckets[i].key != NULL) {
      counter+=1;
    }
    if(counter == index+1) {
      break;
    }
    
  }

  return map->buckets[i];
}


void map_free(Map* map) {
  map->used = 0;
  map->capacity = 0;
  map->data_capacity = 0;
  map->data_used = 0;
  free(map->buckets);
  free(map->data);
}

int main() {
  Map m;
  map_initialize(&m, sizeof(char), sizeof(int));
  int number = 128;
  for(int i = 0; i < number; i++) {
    int f = i+17;
    map_set(&m,&i,&f);
  }
  for(int i = 0; i < number; i++) {
    Entry e = map_iter(&m, i);
    printf("%d ", *(int*)e.value);
  }
  map_free(&m);
  return 0;
}
