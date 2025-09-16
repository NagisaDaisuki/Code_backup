#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// income 为应征收税的个人收入，函数返回值为income应该征收的税额
float single_tax(float income) {
  if (income <= 23350.0f) {
    return income * 0.15f;
  } else if (income <= 56550.0f) {
    return 3502.50f + (income - 23350.0f) * 0.28f;
  } else if (income <= 117950.0f) {
    return 12798.50f + (income - 56550.0f) * 0.31f;
  } else if (income <= 256500.0f) {
    return 31832.50f + (income - 117950.0f) * 0.36f;
  } else {
    return 81710.50f + (income - 256500.0f) * 0.396f;
  }
}

// 结构体数组(查表法)
// 将税率表格的数据和代码逻辑分离。更具可扩展性和可维护性，如果税率表格发生变化，只需要修改数组数据而不需要动函数主体。
typedef struct {
  float upper_limit;   // 范围上限
  float base_tax;      // 基础税额
  float marginal_rate; // 边际税率
  float excess_base;   // 超过这个数额的部分
} TaxBracket;

float single_tax_advanced(float income) {
  // 声明并初始化税率表数组
  // 注意：这里的顺序很重要，必须是从低到高
  static const TaxBracket brackets[] = {
      {23350.0f, 0.0f, 0.15f, 0.0f},
      {56550.0f, 3502.50f, 0.28f, 23350.0f},
      {117950.0f, 12798.50f, 0.31f, 56550.0f},
      {256500.0f, 31832.50f, 0.36f, 117950.0f},
      {__FLT_MAX__, 81710.50f, 0.396f, 256500.0f},
  };

  int num_brackets = sizeof(brackets) / sizeof(brackets[0]);

  for (int i = 0; i < num_brackets; ++i) {
    if (income <= brackets[i].upper_limit) {
      float taxable_excess = income - brackets[i].excess_base;
      return brackets[i].base_tax + taxable_excess * brackets[i].marginal_rate;
    }
  }

  return 0.0f; // 理论上不会执行到这里，除非输入负数。
}

int main(int argc, char *argv[]) {

  float income = 0.0;
  float tax = 0.0;
  float tax_advanced = 0.0;

  printf("Please input your income (including tax) this year:\n");
  scanf("%f", &income);
  tax = single_tax(income);
  tax_advanced = single_tax_advanced(income);
  printf("\naccording to your salary that you should afford %.2f taxs in a "
         "year.\n",
         tax);
  printf("\naccording to your salary that you should afford %.2f taxs in a "
         "year.(Use advanced function)\n",
         tax_advanced);

  return EXIT_SUCCESS;
}
