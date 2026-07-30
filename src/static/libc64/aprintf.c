#include "libc64/aprintf.h"

#ifdef TARGET_PC
#include <stdio.h>
#include <stdlib.h>
#else
#include "libultra/xprintf.h" /* _Printf */
#endif

extern int vaprintf(aprout_func_t* func, const char* fmt, va_list ap) {
#ifdef TARGET_PC
  va_list count_args;
  va_copy(count_args, ap);
  int length = vsnprintf(NULL, 0, fmt, count_args);
  va_end(count_args);
  if (length < 0) {
    return length;
  }

  char* buffer = malloc((size_t)length + 1);
  if (buffer == NULL) {
    return -1;
  }

  va_list format_args;
  va_copy(format_args, ap);
  int written = vsnprintf(buffer, (size_t)length + 1, fmt, format_args);
  va_end(format_args);
  if (written >= 0 && func->prout_func(func, buffer, written) == NULL) {
    written = -1;
  }
  free(buffer);
  return written;
#else
  return _Printf(func->prout_func, func, fmt, ap);
#endif
}
