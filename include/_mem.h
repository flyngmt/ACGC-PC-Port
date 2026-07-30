#ifndef _MEM_H
#define _MEM_H

#ifdef TARGET_PC
#include <string.h>
#else
#include "stddef.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma section code_type ".init"

#ifndef TARGET_PC
void * memcpy(void * dst, const void * src, size_t n);
void * memset(void * dst, int val, size_t n);
int memcmp(const void* src1, const void* src2, size_t n);
#endif
void __fill_mem(void * dst, int val, unsigned long n);

#pragma section code_type

#ifdef __cplusplus
};
#endif
#endif
