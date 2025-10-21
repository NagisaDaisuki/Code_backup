#include <stdio.h>

void print_compiler_info() {
#ifdef __GUNC__
  printf("Compiler: GCC %d.%d.%d\n", __GUNC__, __GUNC_MINOR__,
         __GUNC_PATCHLEVEL__);
#else
  printf("Compiler is not GCC.\n");
#endif

#if defined(__OPTIMIZE__)
  printf("Optimization is enabled.\n");
#else
  printf("Optimization is disabled.\n");
#endif
}

int main(void) {
  print_compiler_info();
  return 0;
}
