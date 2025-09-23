#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int n_cntrl;
  int n_space;
  int n_digit;
  int n_lower;
  int n_upper;
  int n_punct;
  int n_nprint;
  int total;

} Counter_struct;

void clear_input_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
    // do nothing, just consume the characters
  }
}

void count_symbol_num(const char *string, Counter_struct *counter) {
  const char *p_str;

  // 先将计数器清零
  counter->n_cntrl = 0;
  counter->n_space = 0;
  counter->n_digit = 0;
  counter->n_lower = 0;
  counter->n_upper = 0;
  counter->n_punct = 0;
  counter->n_nprint = 0;
  counter->total = 0;

  for (p_str = string; *p_str != '\0'; p_str++) {
    unsigned char ch = (unsigned char)*p_str; // 安全转换

    // 使用 if-else if结构来确保每个字符只能被统计一次
    if (iscntrl(ch)) {
      counter->n_cntrl++;
    } else if (isspace(ch)) {
      counter->n_space++;
    } else if (isdigit(ch)) {
      counter->n_digit++;
    } else if (islower(ch)) {
      counter->n_lower++;
    } else if (isupper(ch)) {
      counter->n_upper++;
    } else if (ispunct(ch)) {
      counter->n_punct++;
    } else if (!isprint(ch)) {
      // 如果既不是控制字符，也不是可打印字符，那么就是不可打印字符
      // is_cntrl 已经排除了大部分，这里主要处理一些特殊情况
      counter->n_nprint++;
    }
    counter->total++;
  }
}

void print_count(const char *string, Counter_struct counter) {
  printf("#=======================================================#\n");
  printf("字符串：\"%s\"\n", string);
  printf("控制字符: %d\n", counter.n_cntrl);
  printf("空白字符: %d\n", counter.n_space);
  printf("数字: %d\n", counter.n_digit);
  printf("小写字母: %d\n", counter.n_lower);
  printf("大写字母: %d\n", counter.n_upper);
  printf("标点符号: %d\n", counter.n_punct);
  printf("不可打印: %d\n", counter.n_nprint);
  printf("总字符数: %d\n", counter.total);
  printf("#=======================================================#\n");
}

void percent_count(const char *string, Counter_struct counter) {
  if (counter.total == 0)
    printf("No characters in the input!\n");
  else {
    printf("#=======================================================#\n");
    printf("%3.0f%%   control characters\n",
           (double)counter.n_cntrl * 100 / counter.total);
    printf("%3.0f%%   whitespace characters\n",
           (double)counter.n_space * 100 / counter.total);
    printf("%3.0f%%   digit characters\n",
           (double)counter.n_digit * 100 / counter.total);
    printf("%3.0f%%   lower case characters\n",
           (double)counter.n_lower * 100 / counter.total);
    printf("%3.0f%%   upper casecharacters\n",
           (double)counter.n_upper * 100 / counter.total);
    printf("%3.0f%%   control characters\n",
           (double)counter.n_punct * 100 / counter.total);
    printf("%3.0f%%   control characters\n",
           (double)counter.n_nprint * 100 / counter.total);
    printf("#=======================================================#\n");
  }
}
int main(void) {
  char string[100] = "";
  Counter_struct counter = {0, 0, 0, 0, 0, 0, 0, 0};

  printf("Please enter some characters below the line:\n");

  fgets(string, sizeof(string), stdin);

  if (string[strlen(string) - 1] != '\n') {
    clear_input_buffer();
  }
  string[strcspn(string, "\n")] = '\0';
  // 将fgets获取到的\n 删去

  count_symbol_num(string, &counter);
  print_count(string, counter);
  printf("\n");
  percent_count(string, counter);
  return EXIT_SUCCESS;
}
