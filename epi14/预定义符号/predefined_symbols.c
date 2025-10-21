#include <stdio.h>

int main(void) {
  printf("This is file: %s\n", __FILE__);
  printf("This is line: %d\n", __LINE__);
  printf("This is compile date: %s\n", __DATE__);
  printf("This is compile time: %s\n", __TIME__);
  return 0;
}
