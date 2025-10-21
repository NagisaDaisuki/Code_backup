#include <stdio.h>

// 检查 C 标准版本
#if __STDC_VERSION__ < 199901L
// 如果编译器版本低于 C99，则停止编译并报错
#error "本项目要求 C99 或更高版本的编译器!"
#endif

#ifdef WINDOWS_ENV
// ... 针对 Windows 的代码 ...
#elif defined(LINUX_ENV)
// ... 针对 Linux 的代码 ...
#else
// 如果没有定义任何操作系统环境，则报错
#error "必须定义 WINDOWS_ENV 或 LINUX_ENV 宏以指定编译环境！"
#endif

int main() {
  printf("编译成功，版本符合要求。\n");
  return 0;
}
