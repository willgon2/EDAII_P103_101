#include "linked.h"
#include "document.h"

char *copy_str(char *old_str) {
  int length = (int)strlen(old_str) + 1;
  char *new_str = malloc(length);
  memset(new_str, 0, length);

  for (int i = 0; i < length - 1; i++) {
    new_str[i] = old_str[i];
  }

  new_str[length - 1] = '\0';

  return new_str;
}

int get_length(LinkedList l) {
  if (l.is_empty == true) {
    return 0;
  }

  int i = 0;
  Node *node = l.head;

  while (node != l.tail) {
    i++;
    node = node->next;
  }

  return i;
}

Node *create_node(void *value, DataType dt) {
  Node *n = malloc(sizeof(Node));
  n->next = NULL;
  n->prev = NULL;

  switch (dt) {
  case INTEGER:
    int *p_value = malloc(sizeof(int));
    *p_value = *(int *)value;

    n->value = p_value;
    break;

  case STRING:
    char *text = copy_str((char *)value);

    n->value = text;
    break;

  case DOCUMENT_STR:
    Document *p_document = malloc(sizeof(Document));
    *p_document = *(Document *)value;

    n->value = p_document;
    break;

  default:
    printf("The datatype introduced is not available\n");
    exit(1);
    break;
  }
  return n;
}

void initialize_list(LinkedList *l, DataType dt) {
  l->head = NULL;
  l->tail = NULL;
  l->is_empty = true;
  l->type_of_variable = dt;
}

void push(LinkedList *l, void *value) {
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
  } else {
    new_node->prev = l->tail;
    (l->tail)->next = new_node;
    l->tail = new_node;
  }
}

void show_list(LinkedList l) {
  Node *node = l.head;

  while (node != NULL) {
    switch (l.type_of_variable) {
    case INTEGER:
      printf("Found node with value %d\n", *(int *)node->value);
      break;
    case STRING:
      printf("Found node with value %s\n", (char *)node->value);
      break;
    case DOCUMENT_STR:
      printf("Found document with filepath %s\n",
             ((Document *)node->value)->filepath);
      break;
    default:
      printf("Error: Data type not found!!\n");
      exit(1);
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

void *get_item(LinkedList l, int index) {
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

  if (l->type_of_variable == DOCUMENT_STR) {
    free(((Document *)node->value)->filepath);
    free(((Document *)node->value)->body);
    free(((Document *)node->value)->title);
  }

  free(node->value);
  free(node);
}

void free_list(LinkedList *l) {
  while (!l->is_empty) {
    delete (l, 0);
  }

  free(l);
}