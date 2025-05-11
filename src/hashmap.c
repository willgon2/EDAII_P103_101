#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HashMap {
  int size;
  int capacity;
  int *keys;
  int *values;
} HashMap;

HashMap *create_hashmap(int capacity) {
  HashMap *map = malloc(sizeof(HashMap));
  map->size = 0;
  map->capacity = capacity;
  map->keys = malloc(capacity * sizeof(int));
  map->values = malloc(capacity * sizeof(int));
  return map;
}
