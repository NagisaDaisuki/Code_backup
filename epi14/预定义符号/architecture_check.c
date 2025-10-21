#include <stdio.h>

int main(void) {
  printf("Target architecture: ");
#if defined(__x86_64__) || defined(_M_X64)
  printf("x86-64\n");
#elif defined(__i386) || defined(_M_IX86)
  printf("x86 (32-bit)\n");
#elif defined(__aarch64__)
  printf("ARM64 (AArch64)\n");
#elif defined(__arm__)
  printf("ARM\n");
#elif defined(__powerpc64__)
  printf("PowerPC (64-bit)\n");
#elif defined(__powerpc__)
  printf("PowerPC (32-bit)\n");
#else
  printf("Unknown\n");
#endif

  return 0;
}
