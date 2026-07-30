#ifndef JKRMACRO_H
#define JKRMACRO_H

#ifdef __cplusplus
#define JKR_ISALIGNED(addr, alignment) ((((uintptr_t)addr) & (((uintptr_t)alignment) - 1)) == 0)
#define JKR_ISALIGNED32(addr) (JKR_ISALIGNED(addr, 32))

#define JKR_ISNOTALIGNED(addr, alignment) ((((uintptr_t)addr) & (((uintptr_t)alignment) - 1)) != 0)
#define JKR_ISNOTALIGNED32(addr) (JKR_ISNOTALIGNED(addr, 32))

#define JKR_ALIGN(addr, alignment) (((uintptr_t)addr) & (~(((uintptr_t)alignment) - 1)))
#define JKR_ALIGN32(addr) (JKR_ALIGN(addr, 32))
#endif

#endif
