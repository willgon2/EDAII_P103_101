#ifndef DOCUMENT_LIB_H
#define DOCUMENT_LIB_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include "linked.h"

typedef struct {
    char *title;
    int DocumentId;
    char *body;
} Document;

void get_files(char *directory);

#endif