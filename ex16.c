#include "ex16_utils.h"

int main(int argc, char *argv[]) {
  // make two people structures
  Person *joe = Person_create("Joe Alex", 32, 64, 140);
  Person *frank = Person_create("Frank Blank", 20, 72, 180);

  // print them out and where they are in memory
  printf("Joe is at memory location %p:\n", joe);
  Person_print(joe);

  printf("Frank is at memory location %p:\n", frank);
  Person_print(frank);

  // make everyone age 20 years and print them again
  printf("After aging:\n");

  joe -> age += 20;
  joe->height -= 2;
  joe->weight += 40;
  Person_print(joe);

  frank->age += 20;
  frank->weight += 20;
  Person_print(frank);

  // destroy them both so we clean up
  Person_destroy(joe);
  Person_destroy(frank);

  joe = frank = NULL;

  printf("Memory freed.\n");

  return 0;
}
