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

void delete(LinkedList *l, int item_index) {
  int i = 0;
  Node *node = l->head;

  while (i != item_index && node != NULL) {
    node = node->next;
    i += 1;
  }

  if (node == NULL) {
    printf("List index out of range!!\n");
    return;
  }

  Node *prev = node->prev, *next = node->next;

  if (prev == NULL && next == NULL) {
    initialize_list(l);
  }

  if (prev != NULL) {
    prev->next = next;
    if (node == l->tail) {
      l->tail = prev;
    }
  }

  if (next != NULL) {
    next->prev = prev;
    if (node == l->head) {
      l->head = next;
    }
  }

  free(node);
}