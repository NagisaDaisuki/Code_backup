#include <stdio.h>
#include <string.h>

void strspn_test() {
  const char *sentence = "Hello, world!";
  const char *charset_vowels = "aeiou";
  const char *charset_alpha = "abcdefghijklmnopqrstuvwxyz";

  size_t length1 = strspn(sentence, "Heo");
  printf("The length of the initial part of \"%s\"consisting of 'H','e','o' "
         "is: %zu\n",
         sentence, length1);
  // 输出：2 (因为 'l' 不在 "Heo" 中)
  size_t length2 = strspn(sentence, charset_alpha);
  printf("The length of the initial part of \"%s \" consisting of letters is: "
         "%zu\n",
         sentence, length2);
  // 输出：5 (因为 ' ' 不在字母表中)
}

void strcspn_test() {
  const char *filename = "test.txt";
  const char *delimiters = "./";

  // 计算到第一个分隔符 '.' 或 '/' 之前有多少个字符
  size_t length = strcspn(filename, delimiters);
  printf("The length of the prefix before the first delimiter is: %zu\n",
         length);
  // 输出：4 ()

  // 提取文件名
  char name[10];
  strncpy(name, filename, length);
  name[length] = '\0';
  printf("The filename is: %s\n", name);
  // 输出: test
}

int main(void) {
  strspn_test();
  strcspn_test();
  return 0;
}
