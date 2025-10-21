#include <stdio.h>

int a = 1;

#define DEBUG 0
#undef DEBUG
// gcc -std=c11 -g -Wall -DDEBUG=0 line.c
// gcc -std=c11 -g -Wall -DDEBUG=1 line.c
// 使用-DNAME 控制定义名的值
#if DEBUG
#line 100 "generated_code.c"
#endif
void func() {
  int b = 2;       // 编译器现在认为这是 generated_code.c 的 101 行
  int c = "error"; // 故意制造一个错误
}

// 恢复到当前文件的实际行号
#line __LINE__

int main(void) {
  func();
  return 0;
}
