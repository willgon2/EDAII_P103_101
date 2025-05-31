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
  int i = 0;
  for (Node *node = l.head; node != NULL; node = node->next) {
      i++;
  }
  return i;
}


Node *create_node(void *value, DataType dt) {
  Node *n = malloc(sizeof(Node));
  n->next = NULL;
  n->prev = NULL;

  switch (dt) {
    case INTEGER: {
      int *p_value = malloc(sizeof(int));
      *p_value = *(int *)value;
      n->value = p_value;
      break;
    }

    case STRING: {
      char *text = copy_str((char *)value);
      n->value = text;
      break;
    }

    case DOCUMENT_STR: {
      Document *p_document = malloc(sizeof(Document));
      *p_document = *(Document *)value;
      n->value = p_document;
      break;
    }

    case DOCUMENT_LINK: {
      DocumentLink *l = malloc(sizeof(DocumentLink));
      *l = *(DocumentLink *)value;
      n->value = l;
      break;
    }

    default: {
      printf("The datatype introduced is not available\n");
      exit(1);
    }
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
      printf("Links: ");
      show_list(*((Document *)node->value)->links);
      printf("\n");
      break;
    case DOCUMENT_LINK:
      printf("%d ", ((DocumentLink *)node->value)->documentID);
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
    free_list(((Document *)node->value)->links);
    free(((Document *)node->value)->links);
  } else if (l->type_of_variable == DOCUMENT_LINK) {
    free(((DocumentLink *)node->value)->title);
  }

  // for debugging 

  if (l->type_of_variable == STRING) {
    printf("Deliting the string %s\n", (char *)node->value);
  }

  free(node->value);
  free(node);
}

bool in_list(LinkedList l, void *value) {
  Node *n = l.head;
  while (n != NULL) {
    if (l.type_of_variable == INTEGER) {
      int *node_value = (int *)n->value, *value_int = (int *)value;
      if (*node_value == *value_int) {
        return true;
      }
    } else if (l.type_of_variable == STRING) {
      if (strcmp((char *)n->value, (char *)value) == 0) {
        return true;
      }
    } else if (l.type_of_variable == DOCUMENT_STR) {
      Document *d = (Document *)n->value, *value_d = (Document *)value;
      if (d->DocumentId == value_d->DocumentId &&
          strcmp(d->filepath, value_d->filepath) == 0) {
        return true;
      }
    } else if (l.type_of_variable == DOCUMENT_LINK) {
      DocumentLink *l = (DocumentLink *)n->value,
                   *l_value = (DocumentLink *)value;
      if (l->documentID == l_value->documentID) {
        return true;
      }
    } else {
      printf("The type of variable was not found!\n");
      exit(0);
    }
    n = n->next;
  }

  return false;
}

void free_list(LinkedList *l) {
  while (!l->is_empty) {
    delete (l, 0);
  }
}