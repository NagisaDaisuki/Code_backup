#include "struct_test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  Ex x = {10, "Hi", {5, {-1, 25}}, 0};
  Ex *px = &x;

  int *pi;
  // error: assignment to ‘int *’ from incompatible pointer type ‘Ex *’ {aka
  // ‘struct EX *’} [-Wincompatible-pointer-types]
  // pi = px;

  // 使用强制类型转换就能奏效
  pi = (int *)px;

  // 但是这种方法很危险，因为它避开了编译器的类型检查。
  // 正确的表达式更为简单
  pi = &px->a;
  // -> 操作符的优先级高于&操作符的优先级，所以这个表达式无需使用括号。

  char *pc;
  pc = px->b;     // ==&px->b[0]
                  // px->b作为数组不是一个合法的左值，作为右值指向数组第一个元素
  pc = &px->b[1]; // 指向数组第二个元素
  int num = px->c.a;
  short *num1 = px->c.b;
  int num2 = *px->c.b;

  Ex te;
  te = *px->d;
  x.d = &te; // 结构体传递，也就是一开始不能访问的px->d现在可以访问了

  return EXIT_SUCCESS;
}
