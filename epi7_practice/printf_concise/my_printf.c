#include "my_printf.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
void printf_concise(char *format, ...) {
  va_list arg;
  char ch;
  char *str;

  va_start(arg, format);

  /*
    Get the format characters one by one.
  */
  while ((ch = *format++) != '\0') {
    if (ch != '%') {
      // Not a format code -- print the character verbatim.
      putchar(ch);
      continue;
    }
    /*
     *  We got a % -- now get the format code and use it to format
     *  the next argument.
     * */
    switch (*format != '\0' ? *format++ : '\0') {
    case 'd':
      printf_integer(va_arg(arg, int));
      break;
    case 'f':
      printf_float(va_arg(arg, double));
      break;
    case 'c':
      putchar(va_arg(arg, int));
      break;
    case 's':
      str = va_arg(arg, char *);
      while (*str != '\0')
        putchar(*str++);
      break;
    }
  }
  va_end(arg);
}

void printf_integer(int format) { printf("%d", format); }

void printf_float(float format) { printf("%f", format); }
