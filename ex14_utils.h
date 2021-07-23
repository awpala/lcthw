#ifndef __ex14_utils_h__
#define __ex14_utils_h__

#include <stdio.h>
#include <ctype.h>

// forward declarations
void print_arguments(int, char**);
int can_print_it(char);
void print_letters(char[]);

// function definitions
void print_arguments(int argc, char *argv[]) {
  int i = 0;

  for (i = 0; i < argc; i++) {
    print_letters(argv[i]);
  }
}

void print_letters(char arg[]) {
  int i = 0;

  for (i = 0; arg[i] != '\0'; i++) {
    char ch = arg[i];

    if (can_print_it(ch)) {
      printf("'%c' == %d ", ch, ch);
    }
  }

  printf("\n");
}

int can_print_it(char ch) {
  return isalpha((int)ch) || isblank((int)ch);
}

#endif
