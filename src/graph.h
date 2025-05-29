#ifndef GRAPH_LIB_H
#define GRAPH_LIB_H

#include "document.h"
#include "linked.h"

typedef struct {
  int num_nodes;        
  LinkedList **edges;   
} DocumentGraph;

DocumentGraph *create_document_graph(LinkedList *documents);
void free_document_graph(DocumentGraph *graph);

#endif