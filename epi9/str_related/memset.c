#include <stdio.h>
#include <string.h>

int main(void) {
  char buffer[10];

  // Initialize all 10 bytes of the buffer to 'A'
  memset(buffer, 'A', sizeof(buffer));
  printf("Buffer after memset: %.10s\n", buffer);

  // Initialize the buffer to all zeros (a common and safe practice)
  memset(buffer, 0, sizeof(buffer));
  printf("Buffer after zeroing: %d\n", buffer[0]); // Prints 0

  return 0;
}
