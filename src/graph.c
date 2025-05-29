#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

DocumentGraph *create_document_graph(LinkedList *documents) {
  int n = get_length(*documents);
  DocumentGraph *graph = malloc(sizeof(DocumentGraph));
  graph->num_nodes = n;
  graph->edges = malloc(n * sizeof(LinkedList *));

  for (int i = 0; i < n; i++) {
    graph->edges[i] = malloc(sizeof(LinkedList));
    initialize_list(graph->edges[i], INTEGER);
  }

  regex_t regex;
  regcomp(&regex, "\\[\\[([0-9]+)\\]\\]", REG_EXTENDED);

  for (int i = 0; i < n; i++) {
    Document *doc = (Document *)get_item(*documents, i);
    char *body = doc->body;

    regmatch_t matches[2];
    char *cursor = body;

    while (regexec(&regex, cursor, 2, matches, 0) == 0) {
      int start = matches[1].rm_so;
      int end = matches[1].rm_eo;

      char number_str[10];
      int len = end - start;
      strncpy(number_str, cursor + start, len);
      number_str[len] = '\0';

      int referenced_id = atoi(number_str);
      append(graph->edges[doc->DocumentId], &referenced_id);

      cursor += matches[0].rm_eo;
    }
  }

  regfree(&regex);
  return graph;
}

void free_document_graph(DocumentGraph *graph) {
  for (int i = 0; i < graph->num_nodes; i++) {
    free_list(graph->edges[i]);
  }
  free(graph->edges);
  free(graph);
}