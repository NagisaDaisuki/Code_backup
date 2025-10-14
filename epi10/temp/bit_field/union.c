#include <stdio.h>

union {
  float f;
  int i;
} fi;

int main(void) {
  fi.f = 3.14159;
  fi.i = 3;
  printf("%d\n", fi.i);
  return 0;
}
