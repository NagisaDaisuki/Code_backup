#include "fibonacci.h"
#include <stdio.h>

int call_num_re = 0;
int call_num_iter = 0;

long fibonacci_recursion(int n) {
  call_num_re += 1;
  if (n <= 2)
    return 1;

  return fibonacci_recursion(n - 1) + fibonacci_recursion(n - 2);
}

long fibonacci_iteration(int n) {
  call_num_iter += 1;
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

void testlist() {
  printf("递归调用了%d次函数。\n", call_num_re);
  printf("迭代调用了%d次函数。\n", call_num_iter);
}

void clear_input_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}
