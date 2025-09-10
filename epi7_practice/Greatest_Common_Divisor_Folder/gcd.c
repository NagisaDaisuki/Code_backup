#include "gcd.h"
#include <setjmp.h>
#include <stdio.h>

long gcd(int m, int n) {

  int r;
  if (m <= 0 || n <= 0)
    return 0;
  // else if (m % n == 0)
  //   return n;
  // else if (m % n > 0)
  //   return gcd(n, (m % n));

  // 可以使用三目运算符
  r = m % n;
  return r > 0 ? gcd(n, r) : n;
}
//
// 欧几里得算法的迭代过程
// 用较大的数除以较小的数，得到余数。
//
// 将较小的数作为新的“较大的数”，将余数作为新的“较小的数”。
//
// 重复这个过程，直到余数变为 0。
//
// 当余数为 0 时，此时的“较大的数”（即上一步的余数）就是这两个数的最大公因数。

// 欧几里得算法迭代实现
// int gcd (int a, int b)
// {
//   int temp;
//
//   // 欧几里得算法的迭代实现
//   while (b != 0){
//    temp = a % b;
//    a = b;
//    b = temp;
//   }
//   return a;
// }
long gcd_iterative(int m, int n) {
  int r;

  if (m <= 0 || n <= 0)
    return 0;
  do {
    r = m % n;
    m = n;
    n = r;
  } while (r > 0);
  return m;
}
