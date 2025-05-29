#include "search.h"

Document *linear_search_title(LinkedList documents, char *title) {
  Node *d_node = documents.head;
  Document *d = (Document *)d_node->value;  

  while (d_node != NULL && strcmp(title, d->title)) {
    d_node = d_node->next;
    if (d_node != NULL)
      d = (Document *)d_node->value;
  }

  if (d_node == NULL) {
    printf("\nThe document with the name %s could not be found\n", title);
    exit(1);
  }

  return d;
}