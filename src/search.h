#ifndef SEARCH_LIB_H
#define SEARCH_LIB_H

#include "document.h"
#include "linked.h"
#include <stdbool.h>
#include <string.h>

Document *linear_search_title(LinkedList documents, char *title);

#endif