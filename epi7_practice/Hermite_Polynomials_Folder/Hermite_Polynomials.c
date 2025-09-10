#include "Hermite_Polynomials.h"
#include <stdio.h>
int count1 = 0;
int count2 = 0;

// 函数原型: int hermite(int n, int x)
double hermite(int n, double x) {
  count1 += 1;
  if (n <= 0)
    return 1.0;

  if (n == 1)
    return 2.0 * x;

  return 2.0 * x * hermite(n - 1, x) - 2.0 * (n - 1) * hermite(n - 2, x);
}

double hermite_iterative(int n, double x) {
  count2 += 1;
  if (n == 0)
    return 1.0;
  if (n == 1)
    return 2.0 * x;

  double h_n_minus_1 = 1.0; // H_0(x)
  double h_n = 2.0 * x;     // H_1(x)

  for (int i = 1; i < n; ++i) {
    double h_n_plus_1 = 2.0 * x * h_n - 2.0 * i * h_n_minus_1;
    h_n_minus_1 = h_n;
    h_n = h_n_plus_1;
  }
  return h_n;
}

void outputCountNum() {
  printf("Iterative function count: %d\n", count2);
  printf("Recursion function count: %d\n", count1);
}
