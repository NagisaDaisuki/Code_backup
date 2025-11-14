#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LENGTH 20
#define ARRNUM_PRINT(ARR, SIZE)                                                \
  do {                                                                         \
    int __i;                                                                   \
    for (__i = 0; __i < (SIZE); __i++) {                                       \
      printf("%c", (ARR)[__i]);                                                \
    }                                                                          \
    printf("\n");                                                              \
  } while (0)

void atoi_test(void) {
  char num111str[LENGTH] = "111";
  char num123str[LENGTH] = "123";
  char num345str[LENGTH] = "345";

  ARRNUM_PRINT(num111str, strlen(num111str));
  size_t num111 = atoi(num111str);
  printf("%zu\n", num111);

  ARRNUM_PRINT(num123str, strlen(num123str));
  size_t num123 = atoi(num123str);
  printf("%zu\n", num123);

  ARRNUM_PRINT(num345str, strlen(num345str));
  size_t num345 = atoi(num345str);
  printf("%zu\n", num345);
}

void atol_test(void) {
  char num11111111111str[LENGTH] = "11111111111";
  char num12345678910str[LENGTH] = "12345678910";
  char num3456789101112str[LENGTH] = "3456789101112";

  ARRNUM_PRINT(num11111111111str, strlen(num11111111111str));
  long num11111111111 = atol(num11111111111str);
  printf("%ld\n", num11111111111);

  ARRNUM_PRINT(num12345678910str, strlen(num12345678910str));
  long num12345678910 = atol(num12345678910str);
  printf("%ld\n", num12345678910);

  ARRNUM_PRINT(num3456789101112str, strlen(num3456789101112str));
  long num3456789101112 = atol(num3456789101112str);
  printf("%ld\n", num3456789101112);
}

void strtol_test(void) {
  char num_with_char[LENGTH] = {'0', '1', '2', 'a', 'b', 'c'};
  ARRNUM_PRINT(num_with_char, strlen(num_with_char));
  long num_char = strtol(num_with_char, NULL, 0);
  printf("%ld\n", num_char);
}

void strtoul_test(void) {
  char unsigned_num_with_char[LENGTH] = {'3', '2', '7', '8', '6', '9', 'c'};
  ARRNUM_PRINT(unsigned_num_with_char, strlen(unsigned_num_with_char));
  unsigned long num327869c = strtoul(unsigned_num_with_char, NULL, 8);
  printf("%ld\n", num327869c);
}

int main(void) {
  atoi_test();
  atol_test();
  strtol_test();
  strtoul_test();
  return EXIT_SUCCESS;
}
