#ifndef __ex30_utils_h__
#define __ex30_utils_h__

#include "minunit.h"

char *test_dlopen();
char *test_functions();
char *test_failures();
char *test_dlclose();
char *all_tests();

char *test_dlopen() {
  return NULL;
}

char *test_functions() {
  return NULL;
}

char *test_failures() {
  return NULL;
}

char *test_dlclose() {
  return NULL;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_dlopen);
  mu_run_test(test_functions);
  mu_run_test(test_failures);
  mu_run_test(test_dlclose);

  return NULL;
}

#endif