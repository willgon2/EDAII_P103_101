#ifndef LINKED_LIB_H
#define LINKED_LIB_H

#include "linked.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define Query LinkedList
#define Stack LinkedList

typedef struct Node {
  int value;
  struct Node *next;
  struct Node *prev;
} Node;

typedef struct {
  Node *head;
  Node *tail;
  bool is_empty;
} LinkedList;

Node *create_node(int value);
void insert(LinkedList *l, int value);
void show_list(LinkedList l);
void initialize_list(LinkedList *l);

#endif