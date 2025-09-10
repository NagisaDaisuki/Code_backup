#include "gcd.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {

  int a = 0;
  int b = 0;

  printf("#==============================\n");
  printf("求两个数的最大公约数:\n");
  printf("#==============================\n");

  printf("\n\n");

  printf("#==============================\n");
  printf("请输入两个数,例如(12,23):\n");
  printf("#==============================\n");

  printf("\n\n");

  scanf("%d,%d", &a, &b);

  printf("#==============================\n");
  printf("(%d,%d)的最大公约数是%ld\n", a, b, gcd(a, b));
  printf("#==============================\n");

  printf("\n\n");

  printf("#==============================\n");
  printf("(%d,%d)的最大公约数(iterative)是%ld\n", a, b, gcd_iterative(a, b));
  printf("#==============================\n");

  return EXIT_SUCCESS;
}
