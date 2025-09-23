#include <stdio.h>
#define BSIZE 100

char *my_strcpy(char *dest, const char *src, size_t n) {
  size_t i;

  // 复制 src 的前 n 个字符到 dest
  for (i = 0; i < n && src[i] != '\0'; i++)
    dest[i] = src[i];

  // 如果 src 长度小于 n, 用 \0 填充 dest 的剩余部分

  for (; i < n; i++)
    dest[i] = '\0';

  dest[BSIZE - 1] = '\0';
  return dest;
}

int main(void) {
  char buffer[BSIZE] = {0};
  char *test = "Everything I found great was sunfaded.";
  my_strcpy(buffer, test, BSIZE);

  char ch;
  int i;

  for (i = 0; ((ch = buffer[i]) != '\0'); i++) {
    printf("%c", ch);
  }
  printf("\n");

  return 0;
}
