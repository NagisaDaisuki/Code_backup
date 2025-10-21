#include <stdio.h>

int main(void) {
#ifdef __STDC__
  printf("Compiler conforms to the ISO C standard.\n");
  printf("__STDC__ = %d\n", __STDC__);
#else
  printf("Compiler does not conform to the ISO C standard.\n");
#endif

#if defined(__STDC_VERION__)
  printf("C standard version: %ld\n", __STDC_VERION__);
#else
  printf("C standard version is not available.\n");
#endif

  return 0;
}
