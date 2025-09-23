#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_chars(char const *str, char const *chars);

int main(void) {
  char buffer[20] = "Hello World!";
  char *string = "elo";

  printf("String \"%s\" have %d characters in \"%s\"\n", buffer,
         count_chars(buffer, string), string);
  return 0;
}

int count_chars(char const *str, char const *chars) {
  int count = 0;

  while ((str = strpbrk(str, chars)) != NULL) {
    count += 1;
    str++;
  }

  return count;
}
