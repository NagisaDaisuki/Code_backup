#include <stdio.h>
#include <string.h>

int main(void) {
  char str[] = "apple,banana-orange";
  const char *delimiters = ",-";
  char *token;

  // 第一次调用， 传入字符串
  token = strtok(str, delimiters);
  printf("First token: %s\n", token);
  // 输出 apple

  // 后续调用，传入NULL
  while (token != NULL) {
    token = strtok(NULL, delimiters);
    if (token != NULL) {
      printf("Next token: %s\n", token);
      // 输出 banana orange
    }
  }
  return 0;
}
