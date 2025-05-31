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
      if (c >= 'A' && c <= 'Z')
        c = c - 'A' + 'a';
      if (j < 255)
        word[j++] = c;
    } else {
      if (j > 0) {
        word[j] = '\0';
        append(words, word);
        j = 0;
      }
    }
  }

  if (j > 0) {
    word[j] = '\0';
    append(words, word);
  }
}

void find_documents(HashMap *index, LinkedList words, LinkedList *documents) {
  Node *w = words.head;

  while (w != NULL) {
    char *word = (char *)w->value;
    printf("Word %s is in the following documents: ", word);
    int hash = djb2_hash(word) % index->capacity;

    for (int i = 0; i < index->capacity; i++) {
      int idx = (hash + i) % index->capacity;
      KeyValuePair pair = index->buckets[idx];

      if (pair.key == NULL)
        break;

      if (strcmp(pair.key, word) == 0) {
        Node *n = pair.documents.head;
        while (n != NULL) {
          int *docID = (int *)n->value;
          printf("%d ", *docID);
          append(documents, docID);
          n = n->next;
        }

        break;
      }
    }
    printf("\n");
    w = w->next;
  }
}

void score_documents(LinkNode *graph, LinkedList documents,
                     LinkedList documentSet, RankedResult results[],
                     int *count) {
  Node *n = documentSet.head;
  int i = 0;

  while (n != NULL) {
    int docID = *((int *)n->value);
    results[i].docID = docID;
    results[i].relevanceScore = graph[docID].relevance_score;
    results[i].queryScore = 0;

    Node *n_documents = documents.head;
    while (n_documents) {
      if (*(int *)n_documents->value == *(int *)n->value) {
        results[i].queryScore++;
      }
      n_documents = n_documents->next;
    }

    i++;
    n = n->next;
  }

  printf("Pointer to count is %p\n", count);
  printf("i = %d, &i = %p\n", i, &i);

  *count = i;
  printf("Pointer to count is %p\n", count);
}

void sort_results(RankedResult results[], int count) {
  for (int i = 0; i < count - 1; i++) {
    for (int j = i + 1; j < count; j++) {
      bool change = false;
      if (results[j].queryScore > results[i].queryScore) {
        change = true;
      } else if (results[j].queryScore == results[i].queryScore &&
                 results[j].relevanceScore > results[i].relevanceScore) {
        change = true;
      }

      if (change) {
        RankedResult tmp = results[i];
        results[i] = results[j];
        results[j] = tmp;
      }
    }
  }
}

int *ranked_query(HashMap *index, LinkNode *graph, const char *input,
                  int *count) {
  LinkedList words, documents, documentSet;

  initialize_list(&words, STRING);
  initialize_list(&documentSet, INTEGER);
  initialize_list(&documents, INTEGER);

  separate_words(input, &words);
  show_list(words);
  find_documents(index, words, &documents);

  Node *n = documents.head;
  while (n) {
    if (!in_list(documentSet, n->value))
      append(&documentSet, n->value);
    n = n->next;
  }

  int len = get_length(documentSet);

  int *top5 = NULL;
  if (len != 0) {
    top5 = malloc(5 * sizeof(int));
    memset(top5, 0, 5 * sizeof(int));

    RankedResult results[len];
    memset(results, 0, len * sizeof(RankedResult));

    printf("Count is %d with pointer %p\n", *count, count);
    score_documents(graph, documents, documentSet, results, count);
    printf("Pointer to count is %p\n", count);
    printf("Count is %d with pointer %p\n", *count, count);
    sort_results(results, *count);

    printf("Top relevant documents:\n");

    if (*count >= 5)
      *count = 5;

    for (int i = 0; i < *count; i++) {
      printf("Document ID: %d (Relevance Score: %d; Query score: %d)\n",
             results[i].docID, results[i].relevanceScore,
             results[i].queryScore);

      top5[i] = results[i].docID;
    }
  } else {
    printf("No matching documents found!\n");
  }

  free_list(&words);
  free_list(&documents);
  free_list(&documentSet);

  return top5;
}