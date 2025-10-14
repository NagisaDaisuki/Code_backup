/*
 *  用动态分配内存制作一个字符串的一份拷贝。注意：
 *  调用程序应该负责检查这块内存是否成功分配。
 *  这样做允许调用程序以任何它所希望的方式对错误做出反应。
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strdup(char const *string) {
  char *new_string;

  // 请求足够长度的内存，用于存储字符串和它的结尾NUL字节
  new_string = malloc(strlen(string) + 1);

  // 如果我们得到内存就复制字符串
  if (new_string != NULL)
    strcpy(new_string, string);
  return new_string;
}
