#include "common.h"
#include "document.h"
#include "graph.h"
#include "hashmap.h"
#include "linked.h"
#include "query.h"
#include "sample_lib.h"
#include "search.h"

void createaleak() {
  char *foo = malloc(20 * sizeof(char));
  printf("Allocated leaking string: %s", foo);
}

int main(void)
{
    start_database();

    LinkedList *files   = get_files(WIKIPEDIA540);     // all docs
    HashMap    *index   = create_hashmap_dataset(*files);
    LinkNode   *graph   = create_score_graph(files);

    char input[256];

    while (1) {
        printf("\nSearch (or 'exit'): ");
        if (!fgets(input, sizeof input, stdin)) break;
        if (strncmp(input, "exit", 4) == 0) break;

        /* strip trailing newline */
        input[strcspn(input, "\n")] = '\0';

        int count = 0;
        int *top  = ranked_query(index, graph, input, &count);

        if (count == 0) { free(top); continue; }

        /* show titles */
        printf("\n=== Top results ===\n");
        for (int i = 0; i < count; ++i) {
            Document *d = find_document_by_id(*files, top[i]);
            if (d) printf("[%d] %s\n", d->DocumentId, d->title);
        }

        /* choose one */
        printf("\nEnter an ID to open (or just press Enter to skip): ");
        char buf[32];
        fgets(buf, sizeof buf, stdin);
        if (buf[0] != '\n') {
            int id = atoi(buf);
            Document *d = find_document_by_id(*files, id);
            if (d) {
                printf("\n---- %s (ID %d) ----\n", d->title, d->DocumentId);
                puts(d->body);            /* full body; or print first N lines */
                printf("---------------------------\n");
            } else {
                printf("No document with ID %d\n", id);
            }
        }

        free(top);
    }

    /* tidy up … */
    free_list(files); free(files);
    free_hashmap(index);
    free_graph(graph);
    free_database();
    return 0;
}
