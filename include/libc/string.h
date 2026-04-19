#ifndef _LIBC_STRING_H_
#define _LIBC_STRING_H_

#ifdef TARGET_PC
#include_next <string.h>
#else

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// void *memcpy(void *dest, const void *src, size_t num);
// void *memmove(void *dest, const void *src, size_t num);
// void *memset(void *dest, int ch, size_t count);
// int memcmp(const void *ptr1, const void *ptr2, size_t num);

size_t strlen(const char *s);
long strtol(const char *str, char **end, int base);
char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t num);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
char *strncat(char *dest, const char *src, size_t n);
char *strchr(const char *str, int c);
char* strrchr( char* str, int chr );
char* strstr(const char* str, const char* pat);
char* strcat(char* dst, const char* src);

#ifdef __cplusplus
}
#endif

#endif /* TARGET_PC */
#endif
