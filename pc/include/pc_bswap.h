/* pc_bswap.h - Byte-swap helpers for BE data from ARAM/ROM/GCI */
#ifndef PC_BSWAP_H
#define PC_BSWAP_H

#if defined(_MSC_VER)
#include <stdlib.h>
#define pc_bswap16(x) _byteswap_ushort(x)
#define pc_bswap32(x) _byteswap_ulong(x)
#define pc_bswap64(x) _byteswap_uint64(x)
#else
#define pc_bswap16(x) __builtin_bswap16(x)
#define pc_bswap32(x) __builtin_bswap32(x)
#define pc_bswap64(x) __builtin_bswap64(x)
#endif

static inline void pc_bswap16_array(void* ptr, int count) {
    unsigned short* arr = (unsigned short*)ptr;
    int i;
    for (i = 0; i < count; i++) {
        arr[i] = pc_bswap16(arr[i]);
    }
}

static inline void pc_bswap32_array(void* ptr, int count) {
    unsigned int* arr = (unsigned int*)ptr;
    int i;
    for (i = 0; i < count; i++) {
        arr[i] = pc_bswap32(arr[i]);
    }
}

#endif /* PC_BSWAP_H */
