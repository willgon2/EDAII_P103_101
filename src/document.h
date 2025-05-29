#ifndef DOCUMENT_LIB_H
#define DOCUMENT_LIB_H

#include "common.h"
#include "linked.h"

typedef struct DocumentLink {
  int documentID;
  char *title;
} DocumentLink;

typedef struct Document {
  char *filepath;
  char *title;
  int DocumentId;
  char *body;
  LinkedList *links;
} Document;

typedef enum {
  WIKIPEDIA12 = 0,
  WIKIPEDIA270,
  WIKIPEDIA540,
  WIKIPEDIA5400
} Dataset;

typedef struct DatasetInfo {
  Dataset ds;
  char *path;
  int nr_documents;
} DatasetInfo;

extern DatasetInfo * ds_chosen;

void start_database();
void add_dataset(Dataset ds, char *path, int nr_documents);
LinkedList *get_files(Dataset ds);

void read_document(Document *d, char *filepath, int ID);
void print_document(Document *d);
void free_database();
void get_links(Document *d);

#endif