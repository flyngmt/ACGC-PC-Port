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

#include <string.h>

static inline unsigned short pc_load_be16(const void* src) {
    unsigned short value;
    memcpy(&value, src, sizeof(value));
    return pc_bswap16(value);
}

static inline unsigned int pc_load_be32(const void* src) {
    unsigned int value;
    memcpy(&value, src, sizeof(value));
    return pc_bswap32(value);
}

static inline void pc_store_be16(void* dst, unsigned short value) {
    value = pc_bswap16(value);
    memcpy(dst, &value, sizeof(value));
}

static inline void pc_store_be32(void* dst, unsigned int value) {
    value = pc_bswap32(value);
    memcpy(dst, &value, sizeof(value));
}

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
