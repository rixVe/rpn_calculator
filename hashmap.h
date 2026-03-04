#ifndef HASHMAP_H
#define HASHMAP_H
#include <stddef.h>
typedef struct {
  void* key;
  size_t key_size;
  void* value;
} Entry;

typedef struct {
  Entry* array;
  size_t used;
  size_t capacity;
} Map;

void map_initialize(Map* map);
void* map_get(Map* map, void* key, size_t key_size);
void map_insert(Map* map, void* key, size_t key_size, void* value);
void map_delete(Map* map, void* key, size_t key_size);
Entry* map_iter(Map* map, int index);
void map_free(Map* map);


#endif
