#include "document.h"
#include "linked.h"
#include "search.h"
#include "sample_lib.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

void createaleak() {
  char *foo = malloc(20 * sizeof(char));
  printf("Allocated leaking string: %s", foo);
}

int main() {
  printf("*****************\nWelcome to EDA 2!\n*****************\n");

  // how to import and call a function
  // printf("Factorial of 4 is %d\n", fact(4));

  // uncomment and run "make v" to see how valgrind detects memory leaks
  // createaleak();

  // get_files("datasets/wikipedia12");
  
  LinkedList example1;
  int leangth_text = 20;
  char *a = malloc((leangth_text+1) * sizeof(char));
  initialize_list(&example1, STRING);

  a = "Hello world";
  append(&example1, a);
  a = "Hello world2";
  append(&example1, a);
  a = "Hello world3";
  insert(&example1, a);

  delete(&example1, 1);
  delete(&example1, 1);


  show_list(example1);

  return 0;
}
