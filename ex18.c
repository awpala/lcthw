#include "ex18_utils.h"

int main(int argc, char *argv[]) {
  if (argc < 2) die("USAGE: ./ex18 4 3 1 5 6");

  int count = argc - 1;
  int i = 0;
  char **inputs = argv + 1;

  int *numbers = (int *)malloc(count * sizeof(int));
  if (!numbers) die("Memory error.");

  for (i = 0; i < count; i++) {
    numbers[i] = atoi(inputs[i]);
  }

  test_sorting(numbers, count, sorted_order);
  test_sorting(numbers, count, reverse_order);
  test_sorting(numbers, count, strange_order);

  free(numbers);

  return 0;
}
