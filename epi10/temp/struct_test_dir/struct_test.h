#ifndef STRUCT_TEST
#define STRUCT_TEST

typedef struct {
  int a;
  short b[2];
} Ex2;

typedef struct EX {
  int a;
  char b[3];
  Ex2 c;
  struct EX *d;
} Ex;

#endif
