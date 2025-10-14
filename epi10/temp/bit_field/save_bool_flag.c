#include <stdio.h>

enum DeviceMode { MODE_IDLE = 0, MODE_RUNNING = 1, MODE_ERROR = 2 };

// 传统方式：占用 4 * sizeof(int) = 16 字节
struct Status_Normal {
  int is_valid;
  int has_error;
  int is_locked;
  int has_changed;
};

// 位段方式：所有标志打包进一个 int/char/short (通常只占用1字节)
// 位段类型为 unsigned int 或 int
struct Status_BitField {
  unsigned int is_valid : 1;
  unsigned int has_error : 1;
  unsigned int is_locked : 1;
  unsigned int has_changed : 1;
  // 剩下的 4 位可以用于其他标志，或者浪费，但总共只占用 1 个字节(取决于对齐)。
  // 实际是int对齐，结构体占 4 字节大小
  unsigned int mod : 3; // 存储 0 - 8 的整数
};

int main(void) {
  printf("传统结构大小：%zu 字节\n", sizeof(struct Status_Normal));
  printf(
      "位段结构大小：%zu 字节\n",
      sizeof(
          struct Status_BitField)); // 通常是 4 字节(int对齐)或 1 字节(char对齐)

  struct Status_BitField status = {0, 0, 1, 1};

  if (status.is_locked)
    printf("系统已锁定。\n");
  status.mod = MODE_ERROR; // 位段存储enum枚举类型
  printf("设备模式(整数值): %u\n", status.mod);
  return 0;
}
