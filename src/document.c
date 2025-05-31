#include "document.h"
#define NUM_DATASETS 4

DatasetInfo database[NUM_DATASETS];

DatasetInfo *ds_chosen = NULL;

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
  printf("Initializing list with dataset %s\n", database[ds].path);
  ds_chosen = &database[ds];
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
      read_document(aux_document, file_path, i);
      append(documents, aux_document);
    }
  }

  free(aux_document);
  closedir(dr);

  return documents;
}

void get_links(Document *d) {
  int id = 0;
  int title_leangth = 100;
  char *title = malloc(title_leangth);
  for (int i = 0; i < (int)strlen(d->body); i++) {
    id = 0;

    if (d->body[i] == '[') {
      i++;

      int title_index = 0;
      while (d->body[i + 1] != '[' && d->body[i + 1] != ']' &&
             i < (int)strlen(d->body)) {
        title[title_index] = d->body[i];

        i++;
        title_index++;

        if (title_leangth <= title_index + 1) {

          title_leangth += 100;
          title = realloc(title, title_leangth);
        }
      }

      title[title_index] = d->body[i];
      title[title_index + 1] = '\0';

      if (d->body[i + 1] != ']' || i + 1 >= (int)strlen(d->body)) {
        continue;
      }

      if (d->body[i + 2] != '(') {
        continue;
      }

      i += 3;

      while (d->body[i] >= '0' && d->body[i] >= 0 && i < (int)strlen(d->body)) {
        id = id * 10 + (d->body[i] - '0');
        i++;
      }

      if (d->body[i] != ')')
        continue;

      DocumentLink *l = malloc(sizeof(DocumentLink));
      l->title = copy_str(title);
      l->documentID = id;

      if (!in_list(*d->links, l)) {
        append(d->links, l);
        printf("Found link with id %d, and title %s\n", id, title);
      }
      free(l);
    }
  }

  free(title);
}

void read_document(Document *d, char *filepath, int ID) {
  printf("\nReading document with ID %d\n", ID);
  d->filepath = copy_str(filepath);
  d->DocumentId = ID;

  FILE *f = fopen(d->filepath, "r");

  int initial_length = 100;
  char c;
  char *pointers[] = {
      NULL,                       // since the id is already made skip this part
      malloc(initial_length + 1), // for the title
      malloc(initial_length + 1)  // for the body
  };

  for (int p = 0; p < 3; p++) {
    int length = initial_length, i = 0;

    while ((c = fgetc(f)) != EOF) {
      // for the title and the index we pass when we find a single \n
      if (c == '\n' && p != 2) {
        break;
      }

      // for the first pointer we don't store nothing
      if (pointers[p] == NULL) {
        continue;
      }

      if (i >= length) {
        length += initial_length;
        pointers[p] = realloc(pointers[p], length + 1);
      }

      pointers[p][i] = c;
      i++;
    }

    if (pointers[p] != NULL)
      pointers[p][i] = '\0';
  }

  d->title = copy_str(pointers[1]);
  d->body = copy_str(pointers[2]);

  d->links = malloc(sizeof(LinkedList));
  initialize_list(d->links, DOCUMENT_LINK);

  get_links(d);

  fclose(f);

  free(pointers[1]);
  free(pointers[2]);
}

void print_document(Document *d) {
  printf("Document ID: %d\n", d->DocumentId);
  printf("Document Title: %s\n", d->title);
  printf("Document Body: \n%s\n", d->body);
}

void free_database() {
  for (int i = 0; i < NUM_DATASETS; i++) {
    free(database[i].path);
  }
}