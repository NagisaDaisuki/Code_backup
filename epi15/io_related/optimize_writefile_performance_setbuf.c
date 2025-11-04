#include <stdio.h>
#include <stdlib.h>

int main(void) {
  // 1. 使用 setbuf 将标准输出(stdout) 设置为无缓冲
  // 传入 NULL, 表示禁用缓冲(_IONBF)
  setbuf(stdout, NULL);

  printf("1. 这行会立刻显示。");
  // 注意：没有使用 '\n'

  // 如果没有 setbuf(stdout, NULL)，上面这行文字可能会停留在缓冲区，
  // 直到遇到换行符或程序结束。

  // 2. 写入更多内容，确保即使没有换行符也立即输出
  printf("2. 这行也会立即显示。\n");

  // 3. 设置标准 错误流 stderr为无缓冲(通常 stderr 默认就是无缓冲)
  setbuf(stderr, NULL);
  fprintf(stderr, "这是紧错误信息，保证实时输出。\n");

  return 0;
}
