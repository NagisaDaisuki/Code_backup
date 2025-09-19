#include <stdio.h>
#include <string.h>

int main(void) {
  int source_array[] = {1, 2, 3, 4, 5};
  int destination_array[5];

  memcpy(destination_array, source_array, sizeof(source_array));

  printf("destination_array: ");
  for (int i = 0; i < 5; i++)
    printf("%d ", destination_array[i]);
  printf("\n");

  return 0;
}
