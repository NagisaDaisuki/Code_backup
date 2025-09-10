#include "Hermite_Polynomials.h"
#include <stdio.h>

int main(void) {
  int input1 = 4;
  double input2 = 3;
  printf("the result of hermite(%d,%f) euqals (%f)\n", input1, input2,
         hermite(input1, input2));

  printf("the result of hermite_iterative(%d,%f) euqals (%f)\n", input1, input2,
         hermite_iterative(input1, input2));
  outputCountNum();
  return 0;
}
