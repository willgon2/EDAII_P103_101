#include "query.h"




int indegree(LinkNode *graph, int docID) {
    return graph[docID].relevance_score;
}


void separate_words(const char *input, LinkedList *words) {
    char word[256];
    int j = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];

        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a';
            if (j < 255) word[j++] = c;
        } else {
            if (j > 0) {
                word[j] = '\0';
                append(words, copy_str(word));
                j = 0;
            }
        }
    }

    if (j > 0) {
        word[j] = '\0';
        append(words, copy_str(word));
    }
}



void find_documents(HashMap *index, LinkedList words, LinkedList *documents) {
    Node *w = words.head;

    while (w != NULL) {
        char *word = (char *)w->value;
        int hash = djb2_hash(word) % index->capacity;

        for (int i = 0; i < index->capacity; i++) {
            int idx = (hash + i) % index->capacity;
            KeyValuePair pair = index->buckets[idx];

            if (pair.key == NULL) break;

            if (strcmp(pair.key, word) == 0) {
                Node *n = pair.documents.head;
                while (n != NULL) {
                    int *docID = (int *)n->value;
                    if (!in_list(*documents, docID)) {
                        int *copy = malloc(sizeof(int));
                        *copy = *docID;
                        append(documents, copy);
                    }
                    n = n->next;
                }
                break;
            }
        }

        w = w->next;
    }
}

void score_documents(LinkNode *graph, LinkedList documents, RankedResult results[], int *count) {
    Node *n = documents.head;
    int i = 0;

    while (n != NULL) {
        int docID = *((int *)n->value);
        results[i].docID = docID;
        results[i].score = graph[docID].relevance_score;
        i++;
        n = n->next;
    }

    *count = i;
}


void sort_results(RankedResult results[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (results[j].score > results[i].score) {
                RankedResult tmp = results[i];
                results[i] = results[j];
                results[j] = tmp;
            }
        }
    }
}

void ranked_query(HashMap *index, LinkNode *graph, const char *input) {            
    LinkedList words, documents;
    initialize_list(&words, STRING);
    initialize_list(&documents, INTEGER);

    separate_words(input, &words);
    find_documents(index, words, &documents);

    int len = get_length(documents);

    if (len == 0) {
    printf("No matching documents found.\n");
    return;
    }

    RankedResult results[len];
    int count = 0;
    score_documents(graph, documents, results, &count);

    score_documents(graph, documents, results, &count);
    sort_results(results, count);

    printf("Top relevant documents:\n");
    for (int i = 0; i < count && i < 5; i++) {
        printf("Document ID: %d (Relevance Score: %d)\n", results[i].docID, results[i].score);
    }

    free_list(&words);
    free_list(&documents);
}
