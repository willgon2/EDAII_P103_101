#ifndef QUERY_H
#define QUERY_H

#include "document.h"
#include "graph.h"
#include "hashmap.h"
#include "linked.h"
#include <stdbool.h>

typedef struct {
  int docID;
  int queryScore;
  int relevanceScore;
} RankedResult;

void ranked_query(HashMap *index, LinkNode *graph, const char *input);
void separate_words(const char *input, LinkedList *words);
void find_documents(HashMap *index, LinkedList words, LinkedList *documents);
void score_documents(LinkNode *graph, LinkedList documents,
                     LinkedList documentSet, RankedResult results[],
                     int *count);
void sort_results(RankedResult results[], int count);

#endif
