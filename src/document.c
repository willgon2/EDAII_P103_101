#include "document.h"

DatasetInfo database[4];

void start_database() {
    add_dataset(WIKIPEDIA12, "datasets/wikipedia12", 12);
    add_dataset(WIKIPEDIA270, "datasets/wikipedia270", 270);
    add_dataset(WIKIPEDIA540, "datasets/wikipedia540", 540);
    add_dataset(WIKIPEDIA5400, "datasets/wikipedia5400", 5400);
}

void add_dataset(Dataset ds, char *path, int nr_documents){
    database[ds].ds = ds;
    database[ds].path = malloc(strlen(path) + 1);
    strcpy(database[ds].path, path);
    database[ds].nr_documents = nr_documents;
}

void get_files(Dataset ds) {
    struct dirent *de;
    DatasetInfo *ds_chosen = &database[ds];

    DIR *dr = opendir(ds_chosen->path);

    if (dr == NULL) {
        printf("The directory %s could not be oppened!\n", ds_chosen->path);
        exit(1);
    }
    while ((de = readdir(dr)) != NULL) 
            printf("%s\n", de->d_name); 
  
    closedir(dr);
}
