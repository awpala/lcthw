#ifndef __ex18_utils_h__
#define __ex18_utils_h__

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// A typedef to alias the function pointer `compare_cb`
typedef int (*compare_cb)(int, int);

void die(const char *);
int *bubble_sort(int *, int, compare_cb);
int sorted_order(int, int);
int reverse_order(int, int);
int strange_order(int, int);
void test_sorting(int *, int, compare_cb);

/** N.B. Recall `die()` from ex17. */
void die(const char *message) {
  if (errno) {
    perror(message);
  } else {
    printf("ERROR: %s\n", message);
  }

  exit(1);
}

/**
 * A classic bubble sort function that uses the
 * function pointer `compare_cb` to do the sorting.
*/
int *bubble_sort(int *numbers, int count, compare_cb cmp) {
  int temp, i, j;
  temp = i = j = 0;

  int *target = (int *)malloc(count * sizeof(int));

  if (!target)
    die("Memory error.");

  memcpy(target, numbers, count * sizeof(int));

  for (i = 0; i < count; i++) {
    for (j = 0; j < count - 1; j++) {
      if (cmp(target[j], target[j + 1]) > 0) {
        temp = target[j + 1];
        target[j + 1] = target[j];
        target[j] = temp;
      }
    }
  }

  return target;
}

int sorted_order(int a, int b) {
  return (a > b) - (a < b);
}

int reverse_order(int a, int b) {
  return (a < b) - (a > b);
}

int strange_order(int a, int b) {
  if (a == 0 || b == 0) {
    return 0;
  } else {
    return a % b;
  }
}

/**
 * Used to test that we are sorting things correctly
 * by performing the sort and printing it out.
*/
void test_sorting(int *numbers, int count, compare_cb cmp) {
  int i = 0;
  int *sorted = bubble_sort(numbers, count, cmp);

  if (!sorted)
    die("Failed to sort as requested");
  
  for (i = 0; i < count; i++) {
    printf("%d ", sorted[i]);
  }
  printf("\n");

  free(sorted);
}

#endif
