#ifndef QUERY_H
#define QUERY_H

#include "linked.h"
#include "hashmap.h"
#include "graph.h"
#include "document.h"
#include <stdbool.h>

typedef struct {
    int docID;
    int score;
} RankedResult;

void ranked_query(HashMap *index, LinkNode *graph, const char *input);
void separate_words(const char *input, LinkedList *words);
void find_documents(HashMap *index, LinkedList words, LinkedList *documents);
void score_documents(LinkNode *graph, LinkedList documents, RankedResult results[], int *count);
void sort_results(RankedResult results[], int count);

#endif 
