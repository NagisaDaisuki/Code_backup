// 使用字符常量而不是整型常量可以提高程序的可移植性

#include <stdio.h>
#include <stdlib.h>

void binary_to_ascii(unsigned int value) {
  unsigned int quotient;
  quotient = value / 10;
  if (quotient != 0)
    binary_to_ascii(quotient);
  putchar(value % 10 + '0');
}

int main(void) {
  int output_num = 10001;
  binary_to_ascii(output_num);

  return EXIT_SUCCESS;
}
