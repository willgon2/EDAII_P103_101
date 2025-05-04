#ifndef LINKED_LIB_H
#define LINKED_LIB_H

#include "linked.h"
#include "common.h"

#define Query LinkedList
#define Stack LinkedList

typedef enum {
  INTEGER,
  STRING
} DataType;

typedef struct _Node {
  void* value;
  struct _Node *next;
  struct _Node *prev;
} Node;

typedef struct {
  Node *head;
  Node *tail;
  bool is_empty;
  DataType type_of_variable;
} LinkedList;

Node *create_node(void *value, DataType dt);
void insert(LinkedList *l, void* value);
void append(LinkedList *l, void* value);
void show_list(LinkedList l);
void initialize_list(LinkedList *l, DataType dt);

Node *get_node(LinkedList l, int index);
void * get_item(LinkedList l, int index);
void delete(LinkedList *l, int index);

#endif