#include <stdio.h>
#include <string.h>

char *my_strnchr(char const *str, int ch, int which) {
  const char *p_str;
  const char *slow_str;
  int count;
  count = 0;

  for (p_str = str, slow_str = str; *p_str != '\0' && count < which; p_str++) {
    if (*p_str == ch) {
      count += 1;
      slow_str = p_str;
    }

    if (count == which)
      break;
  }

  if (count < which)
    return (char *)slow_str;

  return (char *)p_str;
}

int main(void) {
  char buffer[200] = "Let us commerate this occasion by partaking in a "
                     "delightful tea gathering between the two of us shall we?";
  char ch = 'c';
  int which = 2;
  char *p_buffer = my_strnchr(buffer, ch, which);
  printf("found the \'%c\' character occurs with 3 times on buffers %d "
         "location.\n",
         *p_buffer, (int)(p_buffer - buffer));

  return 0;
}
