#include "linked.h"

Node *create_node(int value) {
  Node *n = malloc(sizeof(Node));
  n->value = value;
  n->next = NULL;
  n->prev = NULL;

  return n;
}

void initialize_list(LinkedList *l) {
  l->head = NULL;
  l->tail = NULL;
  l->is_empty = true;
}

void insert(LinkedList *l, int value) {
  Node *new_node = create_node(value);

  if (l->is_empty) {
    l->head = new_node;
    l->tail = new_node;
    l->is_empty = false;
  } else {
    new_node->next = l->head;
    (l->head)->prev = new_node;
    l->head = new_node;
  }
}

void show_list(LinkedList l) {
  Node *node = l.head;

  do {
    printf("Found node with value %d\n", node->value);
    node = node->next;
  } while (node != NULL);
}