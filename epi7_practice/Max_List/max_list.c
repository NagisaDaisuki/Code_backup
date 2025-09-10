#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
// 也可以使用<ctype.h>头文件内的isdigit()函数判断字符是否为数字
// if (!isdigit(str[i]))
//  return 0;
int ascii_to_integer(char *str) {
  int res = 0;

  for (int i = 0; str[i] != '\n'; ++i) {
    if (str[i] < '0' && str[i] > '9')
      return -1;
    res = res * 10 + (str[i] - '0');
  }
  return res;
}

int max_list(int first_arg, ...) {
  va_list var_arg;
  int max = 0;

  // get the first arg if there is one and save it as the max
  if (first_arg >= 0) {
    int this_arg;
    max = first_arg;

    // get the remaining arguments and save each one
    // if it is greater than the current max.
    va_start(var_arg, first_arg);
    while ((this_arg = va_arg(var_arg, int)) >= 0) // 无法传递负数且存在安全问题
      if (this_arg > max)
        max = this_arg;
    va_end(var_arg);
  } // 最好的方法是传入参数个数或在最后传入一个终止符NULL 或 0
  return max;
}

int max_list_safe(int n_values, ...) { // 确定传入参数个数更加安全
  if (n_values <= 0)                   // 如果没有参数，直接返回
  {
    return -1; // 返回错误码 -1
  }

  va_list var_arg;
  int max;
  int count;
  int this_arg;

  // 将 va_list 初始化到 n_values 之后
  va_start(var_arg, n_values);
  // 取出第一个参数作为 max 的初始值
  max = va_arg(var_arg, int); // 不初始化为0防止传入参数全为负数的风险

  // 从第二个参数开始循环
  for (count = 1; count < n_values; count += 1)
    if ((this_arg = va_arg(var_arg, int)) > max)
      max = this_arg;

  // 清理 va_list
  va_end(var_arg);
  return max;
}

int main(void) {

  unsigned int n_values = 6;
  int max_value;
  int max_value1;
  // char str_val[20] = {};

  max_value = max_list(1, 2, 3, 4, 5, 6);
  max_value1 = max_list_safe(n_values, 1, 2, 3, 4, 5, 6);
  fputs("#====================================================================="
        "=====\n",
        stdout);
  printf("max_list的输入为:%d\n", max_value);
  fputs("#====================================================================="
        "=====\n",
        stdout);
  printf("\n");
  fputs("#====================================================================="
        "=====\n",
        stdout);
  printf("max_list_safe的输入为:%d\n", max_value1);
  fputs("#====================================================================="
        "=====\n",
        stdout);

  // fputs("#================================================================",
  //       stdout);
  // fputs("请输入你想要输入到max_list中的数的个数：(2^32 - 1)", stdout);
  // fputs("#================================================================",
  //       stdout);
  //
  // fputs("#================================================================",
  //       stdout);
  // printf("请输入%d位数字:\n", n_values);
  // fgets(str_val, sizeof(str_val), stdin);
  // fputs("#================================================================",
  //       stdout);
  //
  // fputs("#================================================================",
  //       stdout);
  // printf("调用ASCII_TO_INTEGER()函数......\n");
  // fputs("#================================================================",
  //       stdout);
  //
  //  ascii_to_integer(str_val);

  return EXIT_SUCCESS;
}
