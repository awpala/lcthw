#ifndef __darray_h__
#define __darray_h__

#include "utils_dbg.h"
#include <stdlib.h>
#include <assert.h>

typedef struct {
  int end;
  int max;
  size_t element_size;
  size_t expand_rate;
  void **contents;
} DArray;

#define DArray_last(A)  ((A)->contents[(A)->end - 1])
#define DArray_first(A) ((A)->contents[0])
#define DArray_end(A)   ((A)->end)
#define DArray_count(A) DArray_end(A)
#define DArray_max(A)   ((A)->max)
#define DArray_free(E)  free((E))

#define DEFAULT_EXPAND_RATE 300

static void DArray_set(DArray *, int, void *);
static void *DArray_get(DArray *, int);
static void *DArray_remove(DArray *, int);
static void *DArray_new(DArray *);
static int DArray_resize(DArray *, size_t);

DArray *DArray_create(size_t, size_t);
void DArray_clear(DArray *);
int DArray_expand(DArray *);
int DArray_contract(DArray *);
void DArray_destroy(DArray *);
void DArray_clear_destroy(DArray *);
int DArray_push(DArray *, void *);
void *DArray_pop(DArray *);

static void DArray_set(DArray *array, int i, void *el) {
  check(i < array->max, "darray attempt to set past max.");
  if (i > array->end) {
    array->end = i;
  }
  array->contents[i] = el;

error:
  return;
}

static void *DArray_get(DArray *array, int i) {
  check(i < array->max, "darray attempt to get past max.");
  return array->contents[i];

error:
  return NULL;
}

static void *DArray_remove(DArray *array, int i) {
  void *el = array->contents[i];

  array->contents[i] = NULL;

  return el;
}

static void *DArray_new(DArray *array) {
  check(array->element_size > 0, "Can't use DArray_new on 0 size darrays.");
  return (void *)calloc(1, array->element_size);

error:
  return NULL;
}

static int DArray_resize(DArray *array, size_t new_size) {
  array->max = new_size;
  check(array->max > 0, "The new size must be > 0.");

  void *contents = (void *)realloc(array->contents, array->max * sizeof(void *));

  // check contents and assume realloc doesn't harm the original on error
  check_mem(contents);
  array->contents = contents;

  return 0;

error:
  return -1;
}

DArray *DArray_create(size_t element_size, size_t initial_max) {
  DArray *array = (DArray *)malloc(sizeof(DArray));
  check_mem(array);

  array->max = initial_max;
  check(array->max > 0, "You must set an intial_max > 0.");

  array->contents = (void *)calloc(initial_max, sizeof(void *));
  check_mem(array->contents);

  array->end = 0;
  array->element_size = element_size;
  array->expand_rate = DEFAULT_EXPAND_RATE;

  return array;

error:
  if (array) free(array);
  return NULL;
}

void DArray_clear(DArray *array) {
  int i = 0;
  if (array->element_size > 0) {
    for (i = 0; i < array->max; i++) {
      if (array->contents[i] != NULL) {
        free(array->contents[i]);
      }
    }
  }
}

int DArray_expand(DArray *array) {
  size_t old_max = array->max;
  check(
    DArray_resize(array, array->max + array->expand_rate) == 0,
    "Failed to expand array to new size: %d",
    array->max + (int)array->expand_rate
  );

  memset(array->contents + old_max, 0, array->expand_rate + 1);
  return 0;

error:
  return -1;
}

int DArray_contract(DArray *array) {
  int new_size = array->end < (int)array->expand_rate
    ? (int)array->expand_rate
    : array->end;
  
  return DArray_resize(array, new_size + 1);
}

void DArray_destroy(DArray *array) {
  if (array) {
    if (array->contents) free(array->contents);
    free(array);
  }
}

void DArray_clear_destroy(DArray *array) {
  DArray_clear(array);
  DArray_destroy(array);
}

int DArray_push(DArray *array, void *el) {
  array->contents[array->end] = el;
  array->end++;

  if (DArray_end(array) >= DArray_max(array)) {
    return DArray_expand(array);
  } else {
    return 0;
  }
}

void *DArray_pop(DArray *array) {
  check(array->end - 1 >= 0, "Attempt to pop from empty array.");

  void *el = DArray_remove(array, array->end - 1);
  array->end--;

  if (
    (DArray_end(array) > (int)array->expand_rate)
    && (DArray_end(array) % array->expand_rate)
  ) {
    DArray_contract(array);
  }

  return el;

error:
  return NULL;
}

#endif
