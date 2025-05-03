#include "linked.h"

Node *create_node(void* value, DataType dt) {
  Node *n = malloc(sizeof(Node));
  n->next = NULL;
  n->prev = NULL;

  if (dt == INTEGER) {

    int *p_value = malloc(sizeof(int));
    *p_value = *(int*)value;
    
    n->value = p_value;

  } else if (dt == STRING) {
    int leangth_text = (int)strlen((char*)value);
    char *text = malloc((leangth_text+1) * sizeof(char));

    for (int i = 0; i < leangth_text; i++) {
      text[i] = ((char*)value)[i];
    }

    n->value = text;

  } else {
    printf("The datatype introduced is not available\n");
    exit(1);
  }

  return n;
}

void initialize_list(LinkedList *l, DataType dt) {
  l->head = NULL;
  l->tail = NULL;
  l->is_empty = true;
  l->type_of_variable = dt;
}

void insert(LinkedList *l, void *value) {
  Node *new_node = create_node(value, l->type_of_variable);

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

void append(LinkedList *l, void *value) {
  Node *new_node = create_node(value, l->type_of_variable);

  if (l->is_empty) {
    l->head = new_node;
    l->tail = new_node;
    l->is_empty = false;
  } else{
    new_node->prev = l->tail;
    (l->tail)->next = new_node;
    l->tail = new_node;
  }
}

void show_list(LinkedList l) {
  Node *node = l.head;

  while (node != NULL) {
    if (l.type_of_variable == INTEGER) {
      printf("Found node with value %d\n", *(int*)node->value);
    } else if (l.type_of_variable == STRING) {
      printf("Found node with value %s\n", (char*)node->value);
    }
    node = node->next;
  };
}

Node *get_node(LinkedList l, int index) {
  int i = 0;
  Node *node = l.head;

  while (i != index && node != NULL) {
    node = node->next;
    i += 1;
  }

  if (node == NULL) {
    return NULL;
  } else {
    return node;
  }
}

void * get_item(LinkedList l, int index) {
  Node *node = get_node(l, index);

  if (node != NULL) {
    return node->value;
  } else {
    printf("List index out of range!!");
    exit(1);
  }
}

void delete(LinkedList *l, int item_index) {
  Node *node = get_node(*l, item_index);

  if (node == NULL) {
    printf("List index out of range!!\n");
    exit(1);
  }

  Node *prev = node->prev, *next = node->next;

  if (prev == NULL && next == NULL) {
    initialize_list(l, l->type_of_variable);
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