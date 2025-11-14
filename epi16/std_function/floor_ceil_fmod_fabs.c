#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void floor_test(void) {
  double a = 3.14;
  double b = 3.99;
  double c = -3.14;

  printf("floor(%.2f) = %.0f\n", a, floor(a));
  printf("floor(%.2f) = %.0f\n", b, floor(b));
  printf("floor(%.2f) = %.0f\n", c, floor(c));
}

void ceil_test(void) {
  double a = 3.14;
  double b = 3.99;
  double c = -3.14;

  printf("ceil(%.2f) = %.0f\n", a, ceil(a)); // 输出：4
  printf("ceil(%.2f) = %.0f\n", b, ceil(b)); // 输出：4
  printf("ceil(%.2f) = %.0f\n", c, ceil(c)); // 输出：-3 (向正无穷大取整)
}

void fmod_test(void) {
  double x1 = 10.5;
  double y1 = 3.0;
  double x2 = -10.5;
  double y2 = 4.0;

  // 10.5 = 3 * 3.0 + 1.5
  printf("fmod(%.1f, %.1f) = %.1f\n", x1, y1, fmod(x1, y1));

  // -10.5 = -2 * 4.0 + (-2.5)
  printf("fmod(%.1f, %.1f) = %.1f\n", x2, y2, fmod(x2, y2));
}
int main(int argc, char *argv[]) {
  floor_test();
  ceil_test();
  fmod_test();
  return EXIT_SUCCESS;
}
