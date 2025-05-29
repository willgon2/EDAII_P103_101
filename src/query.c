
//search function using the reverse index to pull up the first 5 documents containing the keyword
void search_query(HashMap *h, const char *query) {
    //start by normalizing the query,converting upper to lower case and ignoring caractesrs that are not letters
    char normalized[256]; //max length for a word is set to 255 characters
    int j = 0;
    for (int i = 0; query[i] != '\0' && j < 255; i++) {
        char c = query[i];
        if (c >= 'A' && c <= 'Z') {
            normalized[j++] = c - 'A' + 'a';
        } else if (c >= 'a' && c <= 'z') {
            normalized[j++] = c;
        }
        //dont add any other symbols to the normalized word, i.e skip them
    }
    normalized[j] = '\0';

    //hash
    int hash = djb2_hash(normalized) % h->capacity;

    
   
   
   
    //linear probing implementation
    for (int i = 0; i < h->capacity; i++) {
        int idx = (hash + i) % h->capacity;
        KeyValuePair pair = h->buckets[idx];

        if (pair.key == NULL) {
            // word not found, break out early
           printf("No documents found for \"%s\".\n", normalized); //word not found
            break;
        }

        if (strcmp(pair.key, normalized) == 0) {
            printf("Documents containing \"%s\": ", normalized); // word found 

            Node *n = pair.documents.head;
            int count = 0;
            while (n != NULL && count < 5) {
                printf("%d ", *((int *)n->value));
                n = n->next;
                count++;
            }

            printf("\n");
            return;
        }
    }

    //if the loop ever ends the word was not found 
    printf("No documents found for \"%s\".\n", normalized);
}
