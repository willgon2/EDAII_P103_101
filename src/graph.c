#include "graph.h"

LinkNode *create_score_graph(LinkedList *d) {
    int memory_graph = sizeof(LinkNode) * (ds_chosen->nr_documents + 1);
    LinkNode *graph = malloc(memory_graph);
    memset(graph, 0, memory_graph);

    for (int i = 0; i < ds_chosen->nr_documents + 1; i ++) {
        graph[i].DocumentId = i;
        graph[i].adjacent_nodes = malloc(sizeof(LinkedList));
        initialize_list(graph[i].adjacent_nodes, INTEGER);
        graph[i].relevance_score = 0;
    }

    Node *d_node = d->head;
    Document *document = NULL; 
    
    while (d_node) {
        document = (Document *)d_node->value;
        
        Node *l_node = document->links->head;
        DocumentLink *dl = NULL;

        while (l_node) {
            dl = (DocumentLink *)l_node->value;
            append(graph[dl->documentID].adjacent_nodes, &(document->DocumentId));
            graph[dl->documentID].relevance_score++;
            l_node = l_node->next;
        }

        d_node = d_node->next;
    }

    bool show_items = true;
    show_graph(graph, show_items);

    // sort by relevance score
    for (int i = 1; i < ds_chosen->nr_documents + 1; i++) {
        for (int j = ds_chosen->nr_documents; j >= i; j--) {
            if (graph[j].relevance_score > graph[j - 1].relevance_score) {
                LinkNode aux = graph[j];
                graph[j] = graph[j - 1];
                graph[j - 1] = aux;
            }
        }
    }

    show_graph(graph, show_items);

    return graph;
}

void show_graph(LinkNode *graph, bool show_items) {
    for (int i = 0; i < ds_chosen->nr_documents + 1; i ++) {
        printf("Document with id %d has relevance score of %d\n", graph[i].DocumentId, graph[i].relevance_score);
        if (show_items) show_list(*graph[i].adjacent_nodes);
    }
}

void free_graph(LinkNode *graph) {
    for (int i = 0; i < ds_chosen->nr_documents + 1; i++) {
        free_list(graph[i].adjacent_nodes);
        free(graph[i].adjacent_nodes);
    }
    free(graph);
}