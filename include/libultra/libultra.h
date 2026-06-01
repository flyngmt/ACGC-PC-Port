#ifndef LIBULTRA_H
#define LIBULTRA_H

#include "types.h"
#include "dolphin/os/OSTime.h"
#include "dolphin/os/OSCache.h"
#include "libultra/gu.h"
#include "libultra/osMesg.h"
#include "libultra/shutdown.h"
#include "libultra/os_timer.h"
#include "libultra/os_thread.h"
#include "libultra/os_pi.h"
#include "libultra/initialize.h"
#include "libc64/math64.h" /* TODO: sins and coss belong in libultra */

#define N64_SCREEN_HEIGHT 240
#define N64_SCREEN_WIDTH 320

#ifdef __cplusplus
extern "C" {
#endif

typedef u64 Z_OSTime;

#if defined(__APPLE__) || defined(__linux__)
/* macOS and Linux (glibc 2.41+ / GCC 15+) provide bcmp/bcopy/bzero — don't redeclare */
#include <strings.h>
#else
int bcmp(void* v1, void* v2, u32 size);
void bcopy(void* src, void* dst, size_t n);
void bzero(void* ptr, size_t size);
#endif
void osSyncPrintf(const char* fmt, ...);
void osWritebackDCache(void* vaddr, u32 nbytes);
u32 osGetCount(void);
OSTime osGetTime(void);

extern s32 osAppNMIBuffer[16];
extern int osShutdown;
extern u8 __osResetSwitchPressed;

#ifdef __cplusplus
}
#endif

#endif
