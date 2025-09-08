#include <assert.h> /* 提供assert()宏用于程序调试 */
#include <ctype.h> /*Character type,用于判断字符的类型(是字母、数字还是标点等),以及进行大小写转换 */
#include <float.h> /* 与limits.h 类似，定义了浮点数类型的最大值最小值和精度 */
#include <limits.h>  /* 极限值，这个头文件不包含函数，定义了一系列宏 */
#include <math.h>    /* 数学函数，提供了各种复杂的数学运算函数 */
#include <stdbool.h> /* C99 提供了标准的布尔类型bool和布尔值true false*/
#include <stdint.h>  /* C99 定义了具有确定位宽的整数类型如int32_t和uint64_t */
#include <stdio.h> /* 标准输入输出,提供了所有与标准输入/输出流和文件操作相关的功能 */
#include <stdlib.h> /* 标准库,包含通用的工具函数，如内存管理，随机数生成，字符串和数字转换等 */
#include <string.h> /* 字符串处理，专门用于处理C风格字符串(以空字符\0结尾的字符数组) */
#include <time.h> /* 获取和操作时间相关函数 */
/*
 ============================================================================
                  C语言常用头文件简介及函数原型
 ============================================================================

  本文档总结了C语言中一些最常用和最重要的头文件，
  并列出了其核心函数的原型以供快速参考。

 ----------------------------------------------------------------------------
                             核心头文件
 ----------------------------------------------------------------------------

 1. #include <stdio.h>  (Standard Input/Output - 标准输入输出)
    - 作用:   处理标准输入/输出流（键盘、屏幕）和文件操作。
              (类型 FILE* 在此头文件中定义)
    - 常用函数原型:
        - printf()  : int printf(const char *format, ...);
        - scanf()   : int scanf(const char *format, ...);
        - fopen()   : FILE *fopen(const char *filename, const char *mode);
        - fclose()  : int fclose(FILE *stream);
        - fprintf() : int fprintf(FILE *stream, const char *format, ...);
        - fscanf()  : int fscanf(FILE *stream, const char *format, ...);
        - getchar() : int getchar(void);
        - putchar() : int putchar(int character);

 2. #include <stdlib.h> (Standard Library - 标准库)
    - 作用:   提供内存管理、随机数、字符串转换、进程控制等通用工具。
              (类型 size_t 在此头文件中定义)
    - 常用函数原型:
        - malloc()  : void *malloc(size_t size);
        - free()    : void free(void *ptr);
        - rand()    : int rand(void);
        - srand()   : void srand(unsigned int seed);
        - atoi()    : int atoi(const char *str);
        - atof()    : double atof(const char *str);
        - exit()    : void exit(int status);
        - system()  : int system(const char *command);
        - qsort()   : void qsort(void *base, size_t num, size_t size, int
 (*compar)(const void *, const void *));

 3. #include <string.h> (String - 字符串处理)
    - 作用:   提供一系列操作C风格字符串的函数。
    - 常用函数原型:
        - strcpy()  : char *strcpy(char *dest, const char *src);
        - strcat()  : char *strcat(char *dest, const char *src);
        - strlen()  : size_t strlen(const char *str);
        - strcmp()  : int strcmp(const char *str1, const char *str2);
        - strstr()  : char *strstr(const char *haystack, const char *needle);
        - memset()  : void *memset(void *str, int c, size_t n);

 4. #include <math.h> (Mathematics - 数学函数)
    - 作用:   提供常见的数学计算函数。
    - 常用函数原型:
        - sqrt()    : double sqrt(double x);
        - pow()     : double pow(double base, double exponent);
        - sin()     : double sin(double x);
        - cos()     : double cos(double x);
        - tan()     : double tan(double x);
        - log()     : double log(double x);
        - log10()   : double log10(double x);
        - ceil()    : double ceil(double x);
        - floor()   : double floor(double x);
        - fabs()    : double fabs(double x);

 5. #include <limits.h> (Limits - 整型极限值)
    - 作用:   定义了各种整型数据类型的最大值和最小值。(不含函数)
    - 常用宏:   INT_MAX, INT_MIN, CHAR_BIT, LONG_MAX

 ----------------------------------------------------------------------------
                             其他重要头文件
 ----------------------------------------------------------------------------

 6. #include <ctype.h> (Character Type - 字符类型)
    - 作用:   用于字符分类（字母、数字等）和大小写转换。
    - 常用函数原型:
        - isalpha() : int isalpha(int c);
        - isdigit() : int isdigit(int c);
        - isspace() : int isspace(int c);
        - toupper() : int toupper(int c);
        - tolower() : int tolower(int c);

 7. #include <time.h> (Time - 时间)
    - 作用:   提供处理日期和时间的函数。
              (类型 time_t, size_t, struct tm 在此头文件中定义)
    - 常用函数原型:
        - time()     : time_t time(time_t *timer);
        - strftime() : size_t strftime(char *str, size_t maxsize, const char
 *format, const struct tm *timeptr);

 8. #include <stdbool.h> (Boolean - 布尔类型, C99标准)
    - 作用:   定义了布尔类型 bool 和布尔常量 true, false。(不含函数)

 9. #include <stdint.h> (Standard Integers - 标准整型, C99标准)
    - 作用:   定义了固定宽度的整数类型，提高代码可移植性。(不含函数)
    - 示例类型: int8_t, uint32_t, int64_t。

 10. #include <assert.h> (Assertion - 断言)
     - 作用:   提供 assert() 宏，用于程序调试。如果断言条件为假，程序将终止。
     - 宏原型:   void assert(int expression);

 11. #include <float.h> (Floating-Point - 浮点数)
     - 作用:   定义了浮点数类型的属性，如最大值、最小值和精度。(不含函数)
     - 常用宏:   FLT_MAX, DBL_MAX, DBL_DIG。

 ============================================================================
*/
