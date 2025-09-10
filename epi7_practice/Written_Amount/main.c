#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *digits[] = {"",         "ONE ",       "TWO ",      "THREE ",
                         "FOUR ",    "FIVE ",      "SIX ",      "SEVEN ",
                         "EIGHT ",   "NINE ",      "TEN ",      "ELEVEN ",
                         "TWELVE ",  "THIRTEEN ",  "FOURTEEN ", "FIFTEEN ",
                         "SIXTEEN ", "SEVENTEEN ", "EIGHTEEN ", "NINETEEN "};

static char *tens[] = {"",       "",       "TWENTY ",  "THIRTY ", "FORTY ",
                       "FIFTY ", "SIXTY ", "SEVENTY ", "EIGHTY ", "NINETY "};

static char *magnitudes[] = {"", "THOUSAND ", "MILLION ", "BILLION "};

static void do_one_group(unsigned int amount, char *buffer, char **magnitude) {
  int value;
  value = amount / 1000;
  if (value > 0)
    do_one_group(value, buffer, magnitude + 1);

  amount %= 1000;
  value = amount / 100;
  if (value > 0) {
    strcat(buffer, digits[value]);
    strcat(buffer, "HUNDRED ");
  }

  value = amount % 100;
  if (value >= 20) {
    strcat(buffer, tens[value / 10]);
    value %= 10;
  }
  if (value > 0)
    strcat(buffer, digits[value]);
  if (amount > 0)
    strcat(buffer, *magnitude);
}
void written_amount(unsigned int amount, char *buffer) {
  if (amount == 0)
    // special case for Zero
    strcpy(buffer, "ZERO ");
  else {
    // Store an Empty string in the buffer, then begin
    *buffer = '\0';
    do_one_group(amount, buffer, magnitudes);
  }
}

int main(void) {
  char str[20] = {};
  int i = 10022;
  written_amount(i, str);
  printf("输入的数为: %d.\n", i);
  printf("输出的字符串为: %s.\n", str);

  return 0;
}
