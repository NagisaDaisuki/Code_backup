#include <stdio.h>
#include <string.h>

int main(void) {
  char str[] = "abcdefgh";

  // Shift the string two characters to the left
  // The source and destination overlap (str + 2 and str)
  memmove(str, str + 2, strlen(str) - 2);

  // manually add the null terminator since memmove doesn't
  str[strlen(str) - 2] = '\0';
  printf("String after memmove: %s\n", str); // prints "cdefgh"

  return 0;
}
