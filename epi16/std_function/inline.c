#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. 最小值和最大值函数(Min/Max)
#define MAX(a, b)                                                              \
  do {                                                                         \
    ((a) > (b)) ? (a) : (b))                                                   \
  } while (0)
// 上面的宏定义碰到 a++ ++b 这种后增前增就会出现错误

// inline 提供了可内联、类型安全且没有副作用的替代方案
inline int max(int a, int b) { return (a < b) ? a : b; }

// 2. 最小值函数(double)
#define MIN_DOUBLE(x, y) ((x) < (y) ? (x) : (y)

inline double min_double(double x, double y) { return (x < y) ? x : y; }

// 3. 定义 square
#define SQUARE(x) ((x) * (x))

inline long square(int x) { return x * x; }

// 4. 定义 cube
#define CUBE(x) ((x) * (x) * (x)

inline long cube(int x) { return x * x * x; }

// 5. 交换 swap
// 宏参数 a 和 b 都是变量名，用于交换它们的值
#define SWAP_INT(a, b)                                                         \
  do {                                                                         \
    int temp_var = (a);                                                        \
    (a) = (b);                                                                 \
    (b) = temp_var;                                                            \
  } while (0)

// 函数 需要传入变量地址
inline void swap_int(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

// 6. 检查某个位是否被设置
#define IS_BIT_SET(flags, bit) (((flags) & (1 << (bit))) != 0)
inline int is_bit_set(int flags, int bit) { return (flags & (1 << bit)) != 0; }

// 设置某个位
#define SET_BIT(flags, bit) ((flags) |= (1 << (bit)))
inline int set_bit(int flags, int bit) { return flags | (1 << bit); }

// 7. 简单的华氏度到开尔文温度转换
// 假设这里只做简单的加减法
#define CELSIUS_TO_KELVIN(c) ((c) + 273.15)

inline double celsius_to_kelvin(double c) { return c + 273.15; }

void bit_set_test(void) {
  int a = 0b111000;
  // printf("%d\n", a);

  IS_BIT_SET(a, 2) ? printf("二进制数 %d 位置 %d 已被设置。\n", a, 2)
                   : printf("二进制数 %d 位置 %d 未被设置。\n", a, 2);

  printf("设置 %d 位置为1（置1）。\n", 2);
  SET_BIT(a, 2);

  IS_BIT_SET(a, 2) ? printf("二进制数 %d 位置 %d 已被设置。\n", a, 2)
                   : printf("二进制数 %d 位置 %d 未被设置。\n", a, 2);
}

int main(void) {
  bit_set_test();
  return 0;
}
