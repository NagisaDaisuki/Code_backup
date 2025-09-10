#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "my_printf.h"

int main(void) {
  char *str1 = "Carl Lee";
  int PIN = 12345;
  char ch = 'H';
  double num = 3.1415926;
  printf_concise("Hello,%s! Nice to meet you, PIN: %d\n", str1, PIN);

  printf_concise("Output float num: %f, Output char: %c\n", num, ch);
  return EXIT_SUCCESS;
}
