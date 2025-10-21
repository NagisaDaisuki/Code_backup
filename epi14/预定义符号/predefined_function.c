#include <stdio.h>

void my_function() { printf("This function is called: %s\n", __func__); }

int main(void) {
  printf("Inside function: %s\n", __func__);
  my_function();
  return 0;
}
