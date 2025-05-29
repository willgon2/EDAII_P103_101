#ifndef HASHMAP_LIB_H
#define HASHMAP_LIB_H

#include "common.h"
#include "document.h"
#include "linked.h"

typedef struct KeyValuePair {
  char *key;
  LinkedList documents;
} KeyValuePair;

typedef struct HashMap {
  int size;
  int capacity;
  KeyValuePair *buckets;
} HashMap;

uint32_t djb2_hash(const char *key);
int create_hash(HashMap h, char *word);
void initialize_hashmap(HashMap *h);
void free_hashmap(HashMap *h);
void print_hashmap(HashMap h);
void hashmap_add(HashMap *h, char *word, int documentID);
HashMap *create_hashmap_dataset(LinkedList documents);
LinkedList split(char *string);
void rehash(HashMap *h, int capacity);

#endif