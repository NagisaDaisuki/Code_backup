#include <stdio.h>
#include <string.h>

int main(void) {
  // This array contains a null byte in the middle.
  char data[] = {'h', 'e', 'l', 'l', 'o', '\0', 'w', 'o', 'r', 'l', 'd'};
  char *result;

  // Search for the character 'o' within the first 11 bytes of the array.
  // A string search function like strchr would stop at the '\0'
  result = memchr(data, 'o', sizeof(data));
  if (result != NULL) {
    printf("Found 'o' at memory address: %p\n", result);
    printf("Character found: '%c'\n", *result);

    // Calculate the index of the found character
    size_t index = (size_t)(result - data);
    printf("It is located at index: %zu\n", index);
  } else {
    printf("The character was not found.\n");
  }
  return 0;
}
