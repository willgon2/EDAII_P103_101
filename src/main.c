#include "common.h"
#include "document.h"
#include "linked.h"
#include "sample_lib.h"
#include "search.h"

void createaleak() {
  char *foo = malloc(20 * sizeof(char));
  printf("Allocated leaking string: %s", foo);
}

int main() {
  printf("*****************\nWelcome to EDA 2!\n*****************\n");
  start_database();

  // how to import and call a function
  // printf("Factorial of 4 is %d\n", fact(4));

  // uncomment and run "make v" to see how valgrind detects memory leaks
  // createaleak();

  LinkedList *files = get_files(WIKIPEDIA540);
  show_list(*files);

  /*
  int test_id = 1;
  char *filepath = (char*)get_item(*files, test_id);

  Document d;
  d.DocumentId = test_id;

  get_document(&d, filepath);
  */

  printf("Pick a document [0-%d]: ", get_length(*files));
  int choice;
  scanf("%d", &choice);

  Document *document = get_item(*files, choice);
  printf("Document ID: %d\n", document->DocumentId);
  printf("Title: %s\n", document->title);
  printf("Body:\n %s\n", document->body);
  

  free(files);
  return 0;
}
