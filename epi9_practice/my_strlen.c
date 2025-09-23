#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t mystrlen(const char *string, size_t max_len) {
  if (string == NULL)
    return 0;

  size_t length = 0;
  // 在给定的最大长度范围内遍历字符串
  while (length < max_len && string[length] != '\0') {
    length++;
  }
  return length;
}

int main(void) {
  // 使用strncpy 创建一个未以NUL结尾的字符串
  char buffer[10] = {0};
  const char *source = "hello world";
  size_t max_copy = 5;

  // strncpy 拷贝5个字符，但不会自动添加\0
  strncpy(buffer, source, max_copy);

  // 此时buffer数组为 {'h','e','l','l','o','\0','\0'...}
  // 但是如果 source 的长度小于 max_copy,则剩余部分会用 '\0'填充
  // 如果 source 长度大于等于 max_copy，则不会自动添加 \0
  // 为了模拟题目的情况，我们假设它没有 \0 结尾
  buffer[9] = 'a';

  // 调用mystrlen 函数来计算长度
  // 传入最大值尽管只有5个字符
  size_t true_length = mystrlen(buffer, 10);

  printf("字符串：");
  for (int i = 0; i < 10; ++i)
    printf("%c", buffer[i]);
  printf("\n");

  printf("使用 mystrlen 函数计算的字符串长度是：%zu\n", true_length);
  printf("使用 strlen 函数计算的字符串长度是：%zu\n", strlen(buffer));
  return 0;
}
