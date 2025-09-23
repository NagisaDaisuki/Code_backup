#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void before_optimization(int *message) {
  int *p_str;
  for (p_str = message; *p_str != '\0'; p_str++)
    if (islower(*p_str)) // unnecessary, because tpupper can also test whether
                         // alphabet is upper or lower
      *p_str = toupper(*p_str);
}

void after_optimization(int *message) {
  register int ch;
  int *pstring;
  for (pstring = message; (ch = *pstring) != '\0';) {
    *pstring++ = toupper(ch);
  }
}

int main(void) { return 0; }
