#include "document.h"

DatasetInfo database[4];

void start_database() {
  add_dataset(WIKIPEDIA12, "datasets/wikipedia12", 12);
  add_dataset(WIKIPEDIA270, "datasets/wikipedia270", 270);
  add_dataset(WIKIPEDIA540, "datasets/wikipedia540", 540);
  add_dataset(WIKIPEDIA5400, "datasets/wikipedia5400", 5400);
}

void add_dataset(Dataset ds, char *path, int nr_documents) {
  database[ds].ds = ds;
  database[ds].path = malloc(strlen(path) + 1);
  strcpy(database[ds].path, path);
  database[ds].nr_documents = nr_documents;
}

LinkedList *get_files(Dataset ds) {
  DatasetInfo *ds_chosen = &database[ds];
  DIR *dr = opendir(ds_chosen->path);

  if (dr == NULL) {
    printf("The directory %s could not be oppened!\n", ds_chosen->path);
    exit(1);
  }

  LinkedList *documents = malloc(sizeof(LinkedList));
  initialize_list(documents, DOCUMENT_STR);

  char file_path[100];
  Document *aux_document = malloc(sizeof(Document));
  for (int i = 0; i <= ds_chosen->nr_documents; i++) {
    snprintf(file_path, sizeof(file_path), "%s/%d.txt", ds_chosen->path, i);

    if (access(file_path, F_OK) == 0) {
      get_document(aux_document, file_path, i);
      append(documents, aux_document);
    }
  }

  closedir(dr);

  return documents;
}

void get_document(Document *d, char *filepath, int ID) {
  d->filepath = copy_str(filepath);
  d->DocumentId = ID;

  FILE *f = fopen(d->filepath, "r");

  // skip the DocumentID since we already know it
  char c;
  while ((c = fgetc(f)) != EOF && c != '\n') {
    continue;
  }

  int length = 100, i = 0;
  char *aux_string = malloc(length);
  memset(aux_string, 0, length);

  while ((c = fgetc(f)) != EOF && c != '\n') {
    if ((int)strlen(aux_string) >= length - 1) {
      length += 100;
      aux_string = realloc(aux_string, length * sizeof(char));
    }

    aux_string[i] = c;
    i++;
  }

  aux_string[length - 1] = '\0';

  d->title = copy_str(aux_string);

  length = 100;
  i = 0;
  aux_string = realloc(aux_string, length * sizeof(char));
  memset(aux_string, 0, length);

  while ((c = fgetc(f)) != EOF) {
    if ((int)strlen(aux_string) >= length - 1) {
      length += 100;
      aux_string = realloc(aux_string, length * sizeof(char));
    }

    aux_string[i] = c;
    i++;
  }

  d->body = copy_str(aux_string);

  free(aux_string);

  printf("Starting document with id %d \n", ID);
}
