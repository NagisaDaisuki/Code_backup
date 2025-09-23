#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BSIZE 50
#define ALPHABET_SIZE 256

char *my_strrstr(char const *s1, char const *s2);
void build_bad_char_table(int bad_char_table[], const char *needle,
                          int needle_len);
const char *my_strstr(const char *haystack, const char *needle);
char *my_strstr_bruteforce(const char *haystack, const char *needle);
int my_strstr_count(const char *s1, const char *s2);

int main(void) {
  char buffer[BSIZE] = "Will they one day reach their destination?";
  char string[BSIZE] = "Will";
  char buffer_fgets[BSIZE] = {};
  // int i;

  fgets(buffer_fgets, BSIZE, stdin);

  buffer_fgets[strcspn(buffer, "\n")] = '\0';

  printf("string \"%s\" was occurred %d times in string \"%s\".\n", string,
         my_strstr_count(buffer_fgets, string), buffer_fgets);

  const char *haystack = "HERE IS A SIMPLE EXAMPL";
  const char *needle = "EXAMPLE";

  const char *result = my_strstr(haystack, needle);

  if (result)
    printf("找到子串 \"%s\" 在主串 \"%s\" 中，位置是 %ld。\n", needle, haystack,
           result - haystack);
  else
    printf("未找到子串 \"%s\"。\n", needle);

  return EXIT_SUCCESS;
}

void build_bad_char_table(int bad_char_table[], const char *needle,
                          int needle_len) {
  int i;

  // 初始化所有字符的最后出现位置为 -1
  for (i = 0; i < ALPHABET_SIZE; i++)
    bad_char_table[i] = -1;

  // 遍历子串，记录每个字符的最后出现位置
  for (i = 0; i < needle_len; i++)
    bad_char_table[(unsigned char)needle[i]] = i;
}

// my_strstr函数，基于Boyer-Moore算法
const char *my_strstr(const char *haystack, const char *needle) {
  // 检查空指针或空字符串的边缘情况
  if (!haystack || !needle)
    return NULL;
  if (*needle == '\0')
    return haystack;

  int haystack_len = strlen(haystack);
  int needle_len = strlen(needle);

  // 如果主串比子串短，不可能匹配
  if (needle_len > haystack_len)
    return NULL;

  // 构建坏字符表
  int bad_char_table[ALPHABET_SIZE];
  build_bad_char_table(bad_char_table, needle, needle_len);

  // 主串当前位置
  int i = 0;

  // 主循环
  while (i <= (haystack_len - needle_len)) {
    int j = needle_len - 1; // 子串的当前位置(从末尾开始)

    // 从子串末尾向前比较
    while (j >= 0 && haystack[i + j] == needle[j])
      j--;

    // 如果 j < 0，说明找到了完全匹配
    if (j < 0)
      return (haystack + i);
    else {
      // 不匹配，根据坏字符规则计算跳跃的距离
      // bad_char_table[haystack[i+j]] 找到坏字符在子串中的最后位置
      // j - bad_char_table[...] 是子串向右移动的距离
      int bad_char_shift = j - bad_char_table[(unsigned char)haystack[i + j]];

      // 确保至少移动一位
      i += (bad_char_shift > 0) ? bad_char_shift : 1;
    }
  }

  return NULL;
}

// 朴素算法
char *my_strstr_bruteforce(const char *haystack, const char *needle) {
  // 处理空指针和空字符串的边界情况
  if (!haystack || !needle)
    return NULL;
  if (*needle == '\0')
    return (char *)haystack;

  int i = 0; // 主字符串的当前位置
  int j = 0; // 子字符串的当前位置

  // 主循环：遍历主字符串
  while (haystack[i] != '\0') {
    // 内层循环：比较子字符串
    if (haystack[i] == needle[i]) {
      // 如果字符匹配，两个指针都向后移动
      i++;
      j++;
    } else {
      // 如果不匹配，回退主字符串指针，重新开始比较
      // 这里是算法的关键：i 需要回到上一次匹配的起点之后
      // j 回到子字符串的开头
      i = i - j + 1;
      j = 0;
    }

    // 如果子字符串的指针已经到了末尾，说明找到了匹配
    if (needle[j] == '\0') {
      // 返回匹配的起始位置
      return (char *)&haystack[i - j];
    }
  }

  // 遍历完主字符串后，没有找到匹配
  return NULL;
}

int my_strstr_count(const char *s1, const char *s2) {
  if (s1 == NULL || s2 == NULL || *s2 == '\0')
    return 0;

  const char *p_str = s1;
  int count = 0;

  while ((p_str = strstr(p_str, s2)) != NULL) {
    // 找到一个匹配，计数器加1
    count++;

    // 将搜索位置移动到匹配后的字符，防止重复计数或陷入无限循环
    // 例如: 在 "ababab"中 查找 "aba"， 如果只移动一个字符，会重复计数
    p_str += strlen(s2);
  }

  return count;
}

char *my_strrstr(char const *s1, char const *s2) {
  register char *last;
  register char *current;

  // 把指针初始化为我们已经找到的前一次匹配
  last = NULL;

  // 只在第二个字符不为空的时候进行查找，如果s2为空返回NULL
  if (*s2 != '\0') {
    // 查找 s2 在 s1 中第一次出现的位置
    current = strstr(s1, s2);
    while (current != NULL) {
      last = current;
      current = strstr(last + 1, s2);
    }
  }
  return last;
}
