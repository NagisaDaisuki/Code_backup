#include <stdio.h>
#include <string.h>

char *my_strrchr(char const *str, int ch) {
  char *p_str;
  for (p_str = str; *p_str != '\0'; p_str++)
    ;
  for (; *p_str != ch && p_str != str; p_str--)
    ;
  return p_str;
}

int main(void) {
  char string[20] = "Hello world!";
  char ch = 'd';
  char *p_string = my_strrchr(string, ch);
  printf("found character in string pointer: %c", *p_string);
  return 0;
}
