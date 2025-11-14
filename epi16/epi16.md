# 🤤 标准函数库

## 16.1 整型函数

- 这组函数返回整型值。这些函数分为三类：**算术**、**随机数**和**字符串转换**。

### 16.1.1 算数<stdlib.h>

标准库函数包含了4个整型算数函数。

~~~C
int abs(int value);
long int labs(long int value);
div_t div(int numerator, int denominator);
ldiv_t ldiv(long int numer, long int denom);
~~~

`abs`函数返回它的参数的绝对值。如果其结果不能用一个整数表示，这个行为是未定义的。
`labs`用于执行相同的任务，但它作用的对象是长整数。

`div`函数把它的第二个参数(分母)除以第一个参数(分子)，产生商和余数，用一个`div_t`结构返回。这个结构包含下面两个字段。

~~~C
int quot; // 商
int rem; // 余数 
~~~

> 这两个字段并不一定以这个顺序出现。

### 16.2.1 随机数<stdlib.h>

两个函数可以产生**伪随机数(pseudo-random number)**。

~~~C
int rand(void);
void srand(unsigned int seed);
~~~

`rand` 返回一个 范围在 0 和 RAND_MAX(至少为32767)之间的伪随机数。
使用`srand` 获取随机数数列。

常见用法

~~~C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 

int main(void)
{
  int i, n;
  time_t t; // <time.h>
  
  n = 5;
  
  // 初始化随机数发生器 
  srand((unsigned) time(&t));

  // 输出 0 到 49 之间的 5 个随机数
  for (i = 0; i < n; i++)
  {
    printf("%d\n", rand() % 50);
  }

  return 0;
}
~~~

~~~C
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TRUE 1
#define FALSE 1

#define PRINT_ARR(ARR, SIZE)                                                   \
  do {                                                                         \
    int __i;                                                                   \
    for (__i = 0; __i < (SIZE); __i++) {                                       \
      printf("%-4d", (ARR)[__i]);                                              \
    }                                                                          \
    printf("\n");                                                              \
  } while (0)

void shuffle(int *deck, int n_cards);

int main(void) {

  int cards[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  fputs("Before shuffle: ", stdout);
  PRINT_ARR(cards, sizeof(cards) / sizeof(cards[0]));

  shuffle(cards, 10);

  fputs("After shuffle: ", stdout);
  PRINT_ARR(cards, sizeof(cards) / sizeof(cards[0]));
  return 0;
}

void shuffle(int *deck, int n_cards) {
  int i;
  static int first_time = TRUE;

  // 如果尚未初始化，用当天的当前时间作为随机数发生器
  if (first_time) {
    first_time = FALSE;
    srand((unsigned int)time(NULL));
  }

  // 通过交换随机对的牌进行 "洗牌"
  for (i = n_cards - 1; i > 0; i -= 1) {
    int where;
    int temp;

    where = rand() % i;
    temp = deck[where];
    deck[where] = deck[i];
    deck[i] = temp;
  }
}
~~~

### 16.1.3 字符串转换 <stdlib.h>

字符串转换函数把字符串转换为数值。其中最简单的函数`atoi`和`atol`。

~~~C
int atoi(char const *string);
long int atol(char const *string);
long int strtol(char const *string, char **unused, int base);
unsigned long int strtoul(char const *string, char **unused, int base);
~~~

> 对于上面四个函数第一个参数来说，如果包含了前导空白字符将被跳过；函数把剩余的合法字符转换为指定类型的值。在尾部存在非法缀尾字符也将被忽略。

> `atoi`和`atol`分别把字符转换为整数和长整数值。`strtol`和`atol`一样把参数字符串转换为long。但是`strtol`保存一个指向转换值后面第一个字符的指针。如果函数的第二个参数并非NULL，这个指针便保存在第二个参数所指向的位置。`strtoul`和`strtol`的执行方式相同，但它产生一个无符号长整数。

> 后两个函数的第三个参数是转换所指向的基数(即进制数)。如果基数为0，任何在程序中用于书写整数字面值的形式都将被接收如`0x2af4`和`0377`。

~~~C
x = strtol("    590bear", next, 12);
~~~

上面的表达式x的值为9947，并把一个指向字母e的指针保存在next所指向的变量中。

#### strtol 和 strtoul 返回的错误值

|函数|返回值|
|:---:|:---:|
|strtol|如果值太大且为负数，返回LONG_MIN。如果值太大且为正数，返回LONG_MAX|
|strtoul|如果值太大返回ULONG_MAX|

## 16.2 浮点型函数

- 头文件`math.h`包含了函数库中剩余的数学函数的声明。这些函数的返回值以及绝大多数参数都是double类型。

几种错误

~~~C
1. 未包含头文件math.h

double x;
x = sqrt(5.5);

// 编译器在此之前未曾见到过sqrt函数的原型。

2. 定义域错误(domain error)

sqrt(-5.0);

3. 范围错误(range error)
exp(DBL_MAX);
// 因为结果值太大，这种情况函数会返回HUGE_VAL
~~~

### 16.2.1 三角函数<math.h>

标准函数库提供了常见的三角函数。

~~~C
double sin(double angle);
double cos(double angle);
double tan(double angle);
double asin(double value);
double acos(double value);
double atan(double value);
double atan2(double x, double y);
~~~

`sin`,`cos`和`tan`函数的参数是一个用弧度表示的角度，这些函数分别返回这个角度的正弦、余弦和正切值。

`asin`,`acos`和`atan`函数分别返回它们参数的反正弦、反余弦和反正切值。也会出现定义域错误(比如`asin`和`acos`的参数并不位于-1和1之间，就会出现一个定义域错误)。

### 16.2.2 双曲函数<math.h>

~~~C
double sinh(double angle);
double cosh(double angle);
double tanh(double angle);
~~~

这些函数分别返回它们的参数的双曲正弦、双曲余弦和双曲正切值。

### 16.2.3 对数和指数函数<math.h>

~~~C
double exp(double x);
double log(double x);
double log10(double x);
~~~

`exp`函数返回e值的x次幂，也就是$e^x$  
`log`函数返回x以e为底的对数，也就是自然对数${\ln x}$；`log10`函数返回x以10为底的对数，也就是${\lg x}$
> 任何一个以`b`为底的对数可以通过下面的公式转换

$log_b x = \frac{\ln x} {\ln b}$

$log_b x = \frac{\log_e x} {\log_e b}$
> 如果它们的参数为负数，两个对数函数都将出现定义域错误。

### 16.2.4 浮点表示形式<math.h>

~~~C
double frexp(double value, int *exponent);
double ldexp(double fraction, int exponent);
double modf(double value, double *ipart);
~~~

`frexp`函数计算一个**指数(exponent)**和**小数(fraction)**，这样$\text{fraction} \times 2^
\text{exponent} = \text{value}$，其中 $0.5 <= fraction < 1$，`exponent`是一个整数。exponent存储于第二个参数所指向的内存的位置。函数返回fraction的值。与它相关的函数`ldexp`的返回值是$\text{fraction} \times 2^\text{exponent}$也就是它原先的值。当需要在那些浮点格式不兼容的机器之间传递浮点数时，这些函数非常有用。

`modf`函数把一个浮点值分成整数和小数两个部分，每个部分都具有和原值一样的符号。整数部分以double类型存储于第二个参数错指向的内存位置，小数部分作为函数的返回值返回。
> frexp 和 ldexp 函数通常用于浮点数的内部处理，例如实现快速幂或进行高精度计算。
>
### 16.2.5 幂<math.h>

~~~C
double pow(double x, double y);
double sqrt(double x);
~~~

`pow`函数会返回$\text{x}^\text{y}$的值。由于在计算这个值时可能要用到对数，如果x是一个负数且y不是一个整数会出现一个定义域错误。

`sqrt`函数返回其参数的平方根。如果参数为负，就会出现一个定义域错误。

### 16.2.6 底数、顶数、绝对值和余数<math.h>

~~~C
double floor(double x);
double ceil(double x);
double fabs(double x);
double fmod(double x, double y);
~~~

这些函数都是用来处理浮点数的函数，分别用于取整和求模运算。

`floor`函数为传入的double值向下取整，`ceil`向上取整，`fmod`返回x除以y所产生的余数，
`fabs`返回双精度浮点数绝对值。

### 16.2.7 字符串转换 <stdlib.h>

~~~C
double atof(char const *string);
double strtod(char const *string, char **unused);
~~~

和`strtol`,`atol`类似，任一函数参数包含了前导空白字符，这些字符将被忽略。函数随后将合法的字符转换为一个double值并忽略任何缀尾的非法字符。

`strtod`函数把参数字符串转换为一个double值，其方法和`atof`类似，但保存一个指向字符串中被转换的值后面的第一个字符的指针。

> 值太大会返回 HUGE_VAL，值太小会返回0

## 16.3 日期和时间函数

函数库提供了一组非常丰富的函数，用于简化日期和时间的处理。它们的原型位于`time.h`。

### 16.3.1 处理器时间 <time.h>
