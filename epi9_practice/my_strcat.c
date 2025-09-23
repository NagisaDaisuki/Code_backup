#include <stdio.h>
#include <string.h>

char *my_strcat(char *dest, const char *src, int n) {
  char *original_dest = dest;

  // 1. 找到 dest 的末尾
  while (*dest != '\0')
    dest++;

  // 2. 从 src 复制 n 个字符到 dest 的末尾
  // 这里的循环条件非常重要
  while (n-- > 0 && *src != '\0') {
    *dest++ = *src++;
  }

  // 3. 在新末尾添加空字符
  *dest = '\0';

  return original_dest;
}

int main(void) {
  // char buffer[40] = {0};
  char string[100] = "I'm caught inside of the fire again.";
  char *string1 = "I'm the wizard of death, I come to visit you next.";
  char *final_string = my_strcat(string, string1, 50);

  char ch;
  int i;
  for (i = 0; ((ch = final_string[i]) != '\0'); i++) {
    printf("%c", ch);
  }
  printf("\n");

  return 0;
}
