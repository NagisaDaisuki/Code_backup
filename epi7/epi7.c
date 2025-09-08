#include "epi7.h"

/*
 *  函数定义
 *
 *  类型
 *  函数名( 形式参数 )
 *  代码块
 *
 *  functype
 *  functionname( vartype variable_name, ...)
 *  {
 *    statments;
 *  }
 *
 * */

// K&R C风格:
// A function definition without a prototype is deprecated in all versions of C
// and is not supported in C23
// 旧风格编译器只知道函数返回值类型不知道函数参数数量和类型
int *find_int(key, array, array_len)
int key;
int array[];
int array_len;
{
  return 0;
}

// 新声明风格
int *find_int_new(int key, int array[], int array_len) { return 0; }

// 一个没有参数的函数的原型应该写成下面这个样子：
int *func(void);

// 函数缺省认定无法见到函数原型的函数返回值为整型

// 对值进行偶校验
int even_parity(int value, int n_bits) {
  int parity = 0;

  // 计数值中值为1的位的个数
  while (n_bits > 0) {
    parity += value & 1;
    value >>= 1;
    n_bits -= 1;
  }
  // 如果计数器的最低位是0，返回TRUE
  // 举一反三：如果是1 则是奇校验
  return (parity % 2) == 0;
}

int main(void) { return 0; }
