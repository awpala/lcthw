#ifndef __ex16_utils_h__
#define __ex16_utils_h__

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *name;
  int age;
  int height;
  int weight;
} Person;

Person *Person_create(const char *, int, int, int);
void Person_destroy(Person *);
void Person_print(Person *);

Person *Person_create(
  const char *name,
  int age,
  int height,
  int weight
) {
  Person *who = (Person *)malloc(sizeof(Person));
  assert(who != NULL);

  who->name = strdup(name);
  who->age = age;
  who->height = height;
  who->weight = weight;

  return who;
}

void Person_destroy(Person *who) {
  assert(who != NULL);
  free(who->name);
  who->name = NULL;
  free(who);
}

void Person_print(Person *who) {
  printf("Name: %s\n", who->name);
  printf("\tAge: %d\n", who->age);
  printf("\tHeight: %d\n", who->height);
  printf("\tWeight: %d\n", who->weight);
  printf("\n");
}

#endif
