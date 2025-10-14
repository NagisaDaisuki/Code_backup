#include <float.h>
#include <limits.h>
#include <stdio.h>

void print_type_size(const char *type_name, size_t size) {
  // 使用 %zu 格式化输出 size_t 类型的大小
  printf("%-20s: %2zu 字节 (%-10s)\n", type_name, size,
         size == 4 ? "32 位" : (size == 8 ? "64 位" : ""));
}

int main() {
  printf("--- C 语言基本数据类型大小 (bytes) ---\n");

  // 1. 整数类型
  printf("\n[ 整数类型 ]\n");
  print_type_size("char", sizeof(char));
  print_type_size("signed char", sizeof(signed char));
  print_type_size("unsigned char", sizeof(unsigned char));

  print_type_size("short", sizeof(short));
  print_type_size("unsigned short", sizeof(unsigned short));

  // int 在大多数 64 位系统上是 4 字节
  print_type_size("int", sizeof(int));
  print_type_size("unsigned int", sizeof(unsigned int));

  // long 在 64 位系统上通常是 8 字节
  print_type_size("long", sizeof(long));
  print_type_size("unsigned long", sizeof(unsigned long));

  // long long 保证是 8 字节
  print_type_size("long long", sizeof(long long));
  print_type_size("unsigned long long", sizeof(unsigned long long));

  // 2. 浮点数类型
  printf("\n[ 浮点数类型 ]\n");
  print_type_size("float", sizeof(float));
  print_type_size("double", sizeof(double));
  print_type_size("long double", sizeof(long double)); // 大小取决于编译器和平台

  // 3. 其他类型
  printf("\n[ 其他和派生类型 ]\n");
  print_type_size("bool (_Bool)", sizeof(_Bool));

  // 指针类型在 64 位系统上通常是 8 字节
  print_type_size("void * (指针)", sizeof(void *));

  printf("\n--- 结果取决于编译器和平台 (ABI) ---\n");

  return 0;
}
