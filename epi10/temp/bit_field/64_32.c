#include <stdio.h>

int main() {
  int x = 10;
  int *ptr = &x;

  // sizeof(int) 通常输出 4
  printf("int 的大小: %zu 字节\n", sizeof(int));

  // sizeof(int*) 或任何指针类型，在 64 位系统上通常输出 8
  printf("int* (指针) 的大小: %zu 字节\n", sizeof(ptr));

  // sizeof(long) 也常用于检查长整数大小
  printf("long 的大小: %zu 字节\n", sizeof(long));

  return 0;
}
