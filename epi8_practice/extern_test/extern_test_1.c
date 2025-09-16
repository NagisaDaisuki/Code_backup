#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int x, y;
  extern int *a;
  extern int b[];
  x = a[3];
  y = b[3];
  printf("output: %d,%d\n", x, y);
  return EXIT_SUCCESS;
}
