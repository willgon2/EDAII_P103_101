#include "hashmap.h"

static int  next_pow2(int v);
void initialize_hashmap_cap(HashMap *h, int capacity);


/*void initialize_hashmap(HashMap *h) {
  h->size = 0;
  h->capacity = 4;
  int size_memory = h->capacity * sizeof(KeyValuePair);
  h->buckets = malloc(size_memory);
  memset(h->buckets, 0, size_memory);
} */

uint32_t djb2_hash(const char *key) {
  uint32_t hash = 5381;
  int c;

  while ((c = *key++)) {
    hash = ((hash << 5) + hash) + (uint8_t)c;
  }

  return hash;
}

int create_hash(HashMap h, char *word) {
  if (h.size >= h.capacity) {
    printf("The bucket is full!!!\n");
    exit(1);
  }

  int hash = djb2_hash(word) % h.capacity;
  KeyValuePair current = h.buckets[hash];

  while (current.key != NULL && strcmp(current.key, word) != 0) {
    hash = (hash + 1) % h.capacity;
    current = h.buckets[hash];
  }

  return hash;
}

void print_hashmap(HashMap h) {
  printf("\nTotal capacity of the hashmap: %d\n", h.capacity);
  printf("Size of hashmap: %d\n\n", h.size);
  for (int i = 0; i < h.capacity; i++) {
    if (h.buckets[i].key != 0) {
      printf("\"%s\" --> ", h.buckets[i].key);

      Node *n = h.buckets[i].documents.head;
      while (n != NULL) {
        printf("%d ", *((int *)n->value));
        n = n->next;
      }

      printf("\n");
    }
  }
}

void hashmap_add(HashMap *h, char *word, int documentID) {
  if ((float)h->size / (float)h->capacity >= 0.75) {
    rehash(h, h->capacity * 2);
  }

  int hash = create_hash(*h, word);

  KeyValuePair *pair = &h->buckets[hash];

  if (pair->key == NULL) {
    initialize_list(&pair->documents, INTEGER);
    append(&pair->documents, &documentID);

    pair->key = copy_str(word);
    h->size++;
  } else {
    append(&pair->documents, &documentID);
  }
}

void free_hashmap(HashMap *h) {
  for (int i = 0; i < h->capacity; i++) {
    if (h->buckets[i].key != 0) {
      free_list(&h->buckets[i].documents);
      free(h->buckets[i].key);
    }
  }
  free(h->buckets);
  free(h);
}

char *last_pointer = NULL; // static pointer
char *get_word(char *string) {

  if (string == NULL) {
    string = last_pointer;
  }

  if (string[0] == ' ' || string[0] == '\n') {
    string++;
  } else if (string[0] == '\0') {
    return NULL;
  }

  int size = 0;
  char c = string[0];
  while (c != ' ' && c != '\0') {
    size += 1;
    c = string[size];
  }

  char *new_string = malloc(size + 1);

  int i = 0, j = 0;
  c = string[0];
  while (c != '\n' && c != ' ' && c != '\0') {
    if (c >= 'a' && c <= 'z') {
      new_string[j] = c;
      j++;
    }

    else if (c >= 'A' && c <= 'Z') {
      new_string[j] = c - 'A' + 'a';
      j++;
    }

    i++;
    c = string[i];
  }
  new_string[j] = '\0';

  last_pointer = string + i;
  return new_string;
}

void rehash(HashMap *h, int capacity) {
  int old_capacity = h->capacity;

  if (capacity == 0) {
    capacity = h->capacity;
  } else {
    h->capacity = capacity;
  }

  KeyValuePair *new_bucket = malloc(capacity * sizeof(KeyValuePair));
  memset(new_bucket, 0, capacity * sizeof(KeyValuePair));
  KeyValuePair *old_bucket = h->buckets;

  h->buckets = new_bucket;

  int hash;

  for (int i = 0; i < old_capacity; i++) {
    if (old_bucket[i].key != 0) {
      hash = create_hash(*h, old_bucket[i].key);

      // remember there can't be the same key in a bucket
      new_bucket[hash].key = old_bucket[i].key;
      new_bucket[hash].documents = old_bucket[i].documents;
    }
  }

  free(old_bucket);
}

HashMap *create_hashmap_dataset(LinkedList documents) {
    HashMap *h = malloc(sizeof(HashMap));
    int cap_hint = next_pow2(ds_chosen->nr_documents * 32);
    initialize_hashmap_cap(h, cap_hint);

  Node *d_node = documents.head;

  while (d_node != NULL) {
    Document *d = (Document *)d_node->value;
    printf("Hashing document with id %d\n", d->DocumentId);
    printf("The capacity of the hash table is: %d and the size is: %d\n",
           h->capacity, h->size);

    char *word = get_word(d->title);

    while (word) {
      if (strlen(word) != 0)
        hashmap_add(h, word, d->DocumentId);
      free(word);
      word = get_word(NULL);
    }

    word = get_word(d->body);

    while (word) {

      if (strlen(word) != 0)
        hashmap_add(h, word, d->DocumentId);

      free(word);
      word = get_word(NULL);
    }

    free(word);

    d_node = d_node->next;
  }

  // print_hashmap(*h);
  return h;
}

/* helper ───────────────────────────────────────────────*/
static int next_pow2(int v) {          /* smallest  power-of-2 ≥ v */
    v--;  v |= v>>1; v |= v>>2; v |= v>>4; v |= v>>8; v |= v>>16;
    return v + 1;
}

/* existing initialise stays but calls the new one for default */
void initialize_hashmap(HashMap *h) { initialize_hashmap_cap(h, 4); }

/* NEW: one-shot allocate */
void initialize_hashmap_cap(HashMap *h, int capacity)
{
    capacity = next_pow2(capacity < 4 ? 4 : capacity);
    h->size = 0;
    h->capacity = capacity;
    h->buckets = calloc(capacity, sizeof(KeyValuePair));
}
