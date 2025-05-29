#include "../src/sample_lib.h"
#include "utils.h"
#include "linked.h"
#include "search.h"
#include "document.h"
#include "hashmap.h"

void test_fact4() {
  runningtest("test_fact4");
  {
    int expectedResult = 24;
    int result = fact(4);

    assertEqualsInt(result, expectedResult);
  }
  successtest();
}

void test_fact3() {
  runningtest("test_fact3");
  {
    int expectedResult = 6;
    int result = fact(3);
    assertEqualsInt(result, expectedResult);
  }
  successtest();
}

void test_fact2() {
  runningtest("test_fact2");
  {
    int expectedResult = 2;
    int result = fact(2);

    // This line fails the test if result != expectedResult
    // Try changing expectedResult to 3 and run "make t" to see what happens
    assertEqualsInt(result, expectedResult);
  }
  successtest();
}

void sample_lib_test() {
  running("sample_lib_test");
  {
    // Call all tests you want to run here
    test_fact4();
    test_fact3();
    test_fact2();
    search_query_test();
  }
  success();
}


void search_query_test(){
  LinkedList doc_list = start_database();
  HashMap *index = create_hashmap_dataset(doc_list);
  int found1[2] = search_query(index,"circe");
  assertEqualsInt(found, )



  free_hashmap(index);
  free_list(&doc_list); 


}