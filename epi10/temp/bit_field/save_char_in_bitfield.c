#include <stdio.h>

struct CharStorage {
  // 8位存储 ASCII码 (0-127)和 扩展 ASCII码 (0-255)
  unsigned int character_code : 8;
};

int main(void) {
  struct CharStorage data;

  // 存储字符 'A' 的 ASCII码 (65)
  data.character_code = 'A';

  printf("存储的整数值为: %u\n", data.character_code);

  // 取出整数值并强制转换为 char ，得到原始字符
  printf("还原的字符: %c\n", (char)data.character_code);
  return 0;
}
