#ifndef __ex16stackEC_utils_h__
#define __ex16stackEC_utils_h__

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN_NAME_BUFFER 20

typedef struct {
  char name[MAX_LEN_NAME_BUFFER];
  int age;
  int height;
  int weight;
} Person;

Person Person_create(char[], int, int, int);
void Person_print(Person);

Person Person_create(
  char name[],
  int age,
  int height,
  int weight
) {
  Person who;

  strcpy(who.name, name);
  who.age = age;
  who.height = height;
  who.weight = weight;
  
  return who;
}

void Person_print(Person who) {
  printf("Name: %s\n", who.name);
  printf("\tAge: %d\n", who.age);
  printf("\tHeight: %d\n", who.height);
  printf("\tWeight: %d\n", who.weight);
  printf("\n");
}

#endif
