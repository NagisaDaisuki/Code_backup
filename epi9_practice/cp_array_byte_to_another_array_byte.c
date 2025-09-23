#include <stdio.h>
#include <string.h>

int main(void) {
  char x[100];
  char y[100];

  // 假设x数组已经被初始化，例如：
  memset(x, 'A', 50);

  // 使用memcpy 将x的前50个字节复制到y
  memcpy(y, x, 50);

  // 验证复制是否成功
  printf("y 的前50个字节：\n");
  for (int i = 0; i < 50; i++) {
    printf("%c", y[i]);
  }
  printf("\n");
  return 0;
}
