#include "fibonacci.h"
#include <stdio.h>

long fibonacci_recursion(int n) {
  if (n <= 2)
    return 1;

  return fibonacci_recursion(n - 1) + fibonacci_recursion(n - 2);
}

long fibonacci_iteration(int n) {
  long result, previous_result, next_older_result;

  previous_result = result = 1;

  while (n > 2) {
    n -= 1;

    next_older_result = previous_result;
    previous_result = result;
    result = previous_result + next_older_result;
  }
  return result;
}

void clear_input_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}
