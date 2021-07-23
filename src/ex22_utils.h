#ifndef __ex22_utils_h__
#define __ex22_utils_h__

#include <stdio.h>
#include "dbg.h"

// makes THE_SIZE available to other .c files
extern int THE_SIZE;

static int THE_AGE = 37;

// gets and sets an internal static variable
int get_age();
void set_age(int);

// updates a static variable that's inside `update_ratio`
double update_ratio(double);

// general functions
void print_size();
void scope_demo(int);

int get_age() {
  return THE_AGE;
}

void set_age(int age) {
  THE_AGE = age;
}

double update_ratio(double new_ratio) {
  static double ratio = 1.0;

  double old_ratio = ratio;
  ratio = new_ratio;

  return old_ratio;
}

void print_size() {
  log_info("I think size is: %d", THE_SIZE);
}

void scope_demo(int count) {
  log_info("count is: %d", count);

  if (count > 10) {
    int count = 100; // BAD! BUGS! -- `count` scoped locally to `if` block here

    log_info("count in this scope is %d", count);
  }

  log_info("count is at exit: %d", count);

  count = 3000;

  log_info("count after assign: %d", count);
}

#endif