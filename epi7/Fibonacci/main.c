#include "fibonacci.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  int test_num;
  long result1, result2;

  test_num = 0;
  result1 = result2 = 0;

  printf("Please Enter a integer num:\n");
  scanf("%d", &test_num);
  clear_input_buffer();

  result1 = fibonacci_recursion(test_num);
  printf("fibonacci numbers using recursion.\n");
  printf("Fibonacci(%d) = %ld\n", test_num, result1);

  test_num = 0;
  printf("Please Enter another integer num:\n");
  scanf("%d", &test_num);
  clear_input_buffer();

  result2 = fibonacci_iteration(test_num);

  printf("fibonacci numbers using iteration.\n");
  printf("Fibonacci(%d) = %ld\n", test_num, result2);

  sleep(1);

  testlist();
  return EXIT_SUCCESS;
}
