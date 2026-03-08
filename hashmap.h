#ifndef HASHMAP_H
#define HASHMAP_H
#include <stddef.h>
#include <stdbool.h>

typedef struct {
    void *key;
    void *value;
} Entry;

typedef struct {
    int used;
    size_t capacity;
    size_t key_size;
    size_t value_size;
    Entry *buckets;
    void *data;
    int data_capacity;
    int data_used;
} Map;

void map_initialize(Map *map, size_t key_size, size_t value_size);

void *map_get_value(Map *map, void *key);

bool map_contains_key(Map *map, void *key);

void map_set(Map *map, void *key, void *value);

Entry map_iter(Map *map, int index);

void map_free(Map *map);


#endif
