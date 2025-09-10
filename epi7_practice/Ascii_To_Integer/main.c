#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_all_digits = 1;
// 只要有非数字字符就返回0
int ascii_to_integer(char *str) {
  int res = 0;

  for (int i = 0; str[i] != '\n'; ++i) { // fgets会包含换行符\n在字符串中
    if (str[i] < '0' || str[i] > '9') {
      is_all_digits = 0;
      return 0;
    }
    res = res * 10 + (str[i] - '0');
  }
  return res;
}

int main(void) {
  char string_var[20] = {};
  int result = 0;
  printf("#=========================================================#\n");
  printf("请输入一串以纯数字组成的字符串: \n");
  printf("#=========================================================#\n");

  // scanf("%s", string_var);
  //  使用char *fgets(char *str, int size, FILE *stream)更安全

  fgets(string_var, sizeof(string_var), stdin);

  // 使用fgets获取的字符串自带\n换行符
  printf("\n#=========================================================#\n");
  printf("你输入的字符串为:%s", string_var);
  printf("#=========================================================#\n");

  result = ascii_to_integer(string_var);

  if (is_all_digits == 0) {
    printf("错误输入");
    return -1;
  }

  printf("\n#=========================================================#\n");
  printf("转换的结果为:%d\n", result);
  printf("#=========================================================#\n");
  return 0;
}
