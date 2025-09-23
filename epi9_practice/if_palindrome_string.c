#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int palindrome(char *string);
int palindrome_advanced(char *string);

int main(void) {
  char *string = "sawaS";
  printf("Is \"%s\" a palindrome? %s.\n", string,
         palindrome(string) ? "true" : "false");
  printf("Is \"%s\" a palindrome? %s.\n", string,
         palindrome_advanced(string) ? "true" : "false");
  return EXIT_SUCCESS;
}

int palindrome(char *string) {
  char *p_front = string;
  char *p_rear; // string + strlen(s) - 1;
  char *p_test;

  for (p_test = string; (unsigned char)*p_test != '\0'; p_test++)
    ;

  p_rear = p_test - 1;

  while (p_front < p_rear) {
    if (*p_front++ != *p_rear--)
      break;
  }

  if (p_front < p_rear)
    return 0;

  return 1;
}

int palindrome_advanced(char *string) {
  if (string == NULL)
    return 0;

  // 初始化左右指针
  const char *left = string;
  const char *right = string + strlen(string) - 1;

  // 只要左右指针没有相遇，就继续循环
  while (left < right) {
    // 移动左指针，直到找到一个字母
    while (left < right && !isalpha((unsigned char)*left))
      left++;

    // 移动右指针，直到找到一个字母
    while (left < right && !isalpha((unsigned char)*right))
      right--;

    // 如果指针相遇，则已经检查完毕
    if (left >= right)
      break;

    // 将两个字母都转为小写后进行比较
    if (tolower((unsigned char)*left) != tolower((unsigned char)*right))
      // 如果不匹配，则不是回文
      return 0;

    // 如果匹配则继续向中间移动
    left++;
    right--;
  }

  // 所有有效字符都匹配，是回文
  return 1;
}
