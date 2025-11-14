#include <math.h>
#include <stdio.h>

int main(void) {
  double x = 8.0;
  double y = 2.0;
  double integer_part;
  double fractional_part;
  int exponent;

  printf("--- 示例输入 ---\n");
  printf("x = %.1f, y = %.1f\n\n", x, y);

  // 1. frexp
  printf("1. frexp(x, &exponent):\n");
  double fraction =
      frexp(x, &exponent); // 函数返回小数值，传入指数变量的地址接收指数
  printf("  fraction = %.1f, exponent = %d\n", fraction, exponent);
  printf("  (%.1f * 2^%d = %.1f)\n\n", fraction, exponent, x);

  // 2. ldexp
  printf("2. ldexp(fraction, exponent):\n");
  double value_ldexp = ldexp(fraction, exponent);
  printf("  value = %.1f\n\n", value_ldexp);

  // 3. modf
  printf("3. modf(3.14,&integer_part):\n");
  fractional_part =
      modf(3.14, &integer_part); // 函数返回小数值，传入整数变量地址接收整数
  printf("  整数部分 = %.0f，小数部分 = %.2f\n\n", integer_part,
         fractional_part);

  // 4. exp
  printf("4. exp(y): e ^ y\n");
  printf("  e^%.1f = %.4f\n\n", y, exp(y));

  // 5. log
  printf("5. log(x) : ln(x) (自然对数)\n");
  printf("  ln(%.1f) = %.4f\n\n", x, log(x));

  // 6. log10
  printf("6. log10(x): log10(x) (常用对数)\n");
  printf("  log10(%.1f) = %.4f\n\n", x, log10(x));
}
