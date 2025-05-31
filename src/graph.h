#ifndef GRAPH_LIB_H
#define GRAPH_LIB_H

#include "common.h"
#include "document.h"
#include "linked.h"

typedef struct LinkNode {
  int DocumentId;
  LinkedList *adjacent_nodes;
  int relevance_score;
} LinkNode;

LinkNode *create_score_graph(LinkedList *d);
void show_graph(LinkNode *graph, bool show_items);
void free_graph(LinkNode *graph);

#endif
