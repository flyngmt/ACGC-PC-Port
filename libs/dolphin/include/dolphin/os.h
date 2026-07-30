#ifndef _DOLPHIN_OS
#define _DOLPHIN_OS

#include "types.h"
#include "dolphin/os/OSAlloc.h"
#include "dolphin/os/OSArena.h"
#include "dolphin/os/OSCache.h"
#include "dolphin/os/OSContext.h"
#include "dolphin/os/OSError.h"
#include "dolphin/os/OSInterrupt.h"
#include "dolphin/os/OSModule.h"
#include "dolphin/os/OSLink.h"
#include "dolphin/os/OSMemory.h"
#include "dolphin/os/OSMessage.h"
#include "libforest/osreport.h" /* OSReport funcs */
#include "dolphin/os/OSReset.h"
#include "dolphin/os/OSFont.h"
#include <dolphin/os/OSTime.h>
#include <dolphin/os/OSAlarm.h>
#include <dolphin/os/OSRtc.h>
#include <dolphin/hw_regs.h>
// #include "va_args.h"

#ifdef __cplusplus
extern "C" {
#endif

// __ppc_eabi_init
extern void __OSPSInit();
extern void __OSFPRInit();
extern void __OSCacheInit();

void OSPanic(const char* file, int line, const char* message, ...);
void OSVReport(const char* fmt, va_list list);
void OSReport(const char* fmt, ...);

extern void __OSPSInit();
extern void __OSCacheInit();

#define OSErrorLine(line, ...) OSPanic(__FILE__, line, __VA_ARGS__)

#ifdef DOLPHIN_DEBUG
#define DOLPHIN_ASSERTLINE(assertion, line) \
    (void)((assertion) || (OSErrorLine(line, "Failed assertion " #assertion), 0))
#define DOLPHIN_ASSERT(assertion) \
    (void)((assertion) || (OSPanic(__FILE__, __LINE__, "Failed assertion " #assertion), 0))
#else
#define DOLPHIN_ASSERTLINE(assertion, line)
#define DOLPHIN_ASSERT(assertion)
#endif

// void OSResetSystem(u32, u32, u32); // goes in reset, but eh
void OSInit(void);

#define OS_CONSOLE_RETAIL4 0x00000004
#define OS_CONSOLE_RETAIL3 0x00000003
#define OS_CONSOLE_RETAIL2 0x00000002
#define OS_CONSOLE_RETAIL1 0x00000001
#define OS_CONSOLE_RETAIL 0x00000000
#define OS_CONSOLE_DEVHW4 0x10000007
#define OS_CONSOLE_DEVHW3 0x10000006
#define OS_CONSOLE_DEVHW2 0x10000005
#define OS_CONSOLE_DEVHW1 0x10000004
#define OS_CONSOLE_MINNOW 0x10000003
#define OS_CONSOLE_ARTHUR 0x10000002
#define OS_CONSOLE_PC_EMULATOR 0x10000001
#define OS_CONSOLE_EMULATOR 0x10000000
#define OS_CONSOLE_DEVELOPMENT 0x10000000
#define OS_CONSOLE_DEVKIT 0x10000000
#define OS_CONSOLE_TDEVKIT 0x20000000

#define OS_CONSOLE_DEV_MASK 0x10000000

u32 OSGetConsoleType();
#define OS_CONSOLE_IS_DEV() ((OSGetConsoleType() & OS_CONSOLE_DEV_MASK) != 0)

#define OSHalt(msg) OSPanic(__FILE__, __LINE__, msg)

typedef void (*OSExceptionHandler)(u8, OSContext*);
OSExceptionHandler __OSSetExceptionHandler(u8, OSExceptionHandler);

#include <dolphin/dvd.h>

typedef struct OSBootInfo_s {
    // total size: 0x40
    DVDDiskID DVDDiskID; // offset 0x0, size 0x20
    unsigned long magic; // offset 0x20, size 0x4
    unsigned long version; // offset 0x24, size 0x4
    unsigned long memorySize; // offset 0x28, size 0x4
    unsigned long consoleType; // offset 0x2C, size 0x4
    void * arenaLo; // offset 0x30, size 0x4
    void * arenaHi; // offset 0x34, size 0x4
    void * FSTLocation; // offset 0x38, size 0x4
    unsigned long FSTMaxLength; // offset 0x3C, size 0x4
} OSBootInfo;

#define OS_CACHED_REGION_PREFIX 0x8000
#define OS_UNCACHED_REGION_PREFIX 0xC000
#define OS_PHYSICAL_MASK 0x3FFF

#define OS_BASE_CACHED (OS_CACHED_REGION_PREFIX << 16)
#define OS_BASE_UNCACHED (OS_UNCACHED_REGION_PREFIX << 16)

typedef struct BI2Debug {
	/* 0x00 */ s32 debugMonSize;
	/* 0x04 */ s32 simMemSize;
	/* 0x08 */ u32 argOffset;
	/* 0x0C */ u32 debugFlag;
	/* 0x10 */ int trackLocation;
	/* 0x14 */ int trackSize;
	/* 0x18 */ u32 countryCode;
	/* 0x1C */ u8 unk[8];
	/* 0x24 */ u32 padSpec;
} BI2Debug;

#ifdef TARGET_PC
/* PC port: these are regular variables defined in pc_misc.c / pc_os.c */
extern u32 __OSPhysicalMemSize;
extern volatile int __OSTVMode;
extern void *__gUnkThread1;
extern void *__gCurrentThread;
extern u32 __OSSimulatedMemSize;
extern u32 __OSBusClock;
extern u32 __OSCoreClock;
extern s32 __gUnknown800030C0[2];
extern u8 __gUnknown800030E3;
extern volatile u16 __OSDeviceCode;
#elif defined(__MWERKS__)
u32 __OSPhysicalMemSize   : (OS_BASE_CACHED | 0x0028);
volatile int __OSTVMode : (OS_BASE_CACHED | 0x00CC);
OSThread *__gUnkThread1 : (OS_BASE_CACHED | 0x00D8);
OSThreadQueue __OSActiveThreadQueue : (OS_BASE_CACHED | 0x00DC);
OSThread *__gCurrentThread : (OS_BASE_CACHED | 0x00E4);
u32 __OSSimulatedMemSize  : (OS_BASE_CACHED | 0x00F0);
u32 __OSBusClock  : (OS_BASE_CACHED | 0x00F8);
u32 __OSCoreClock : (OS_BASE_CACHED | 0x00FC);
s32 __gUnknown800030C0[2] : (OS_BASE_CACHED | 0x30C0);
u8 __gUnknown800030E3 : (OS_BASE_CACHED | 0x30E3);
vu16 __OSDeviceCode AT_ADDRESS(OS_BASE_CACHED | 0x30E6);
#else
#define __OSBusClock  (*(u32 *)(OS_BASE_CACHED | 0x00F8))
#define __OSCoreClock (*(u32 *)(OS_BASE_CACHED | 0x00FC))
#endif
#define OS_BUS_CLOCK   __OSBusClock
#define OS_CORE_CLOCK  __OSCoreClock
#define OS_TIMER_CLOCK (OS_BUS_CLOCK/4)

#define OSTicksToSeconds(ticks)      ((ticks)   / (OS_TIMER_CLOCK))
#define OSTicksToMilliseconds(ticks) ((ticks)   / (OS_TIMER_CLOCK/1000))
#define OSTicksToMicroseconds(ticks) ((ticks)*8 / (OS_TIMER_CLOCK/125000))
#define OSSecondsToTicks(sec) ((sec) * (OS_TIMER_CLOCK))
#define OSMillisecondsToTicks(msec) ((msec) * (OS_TIMER_CLOCK / 1000))
#define OSNanosecondsToTicks(nsec) (((nsec) * (OS_TIMER_CLOCK / 125000)) / 8000)
#define OSMicrosecondsToTicks(usec) (((usec) * (OS_TIMER_CLOCK / 125000)) / 8)

void *OSPhysicalToCached(u32 paddr);
void *OSPhysicalToUncached(u32 paddr);
u32 OSCachedToPhysical(void *caddr);
u32 OSUncachedToPhysical(void *ucaddr);
void *OSCachedToUncached(void *caddr);
void *OSUncachedToCached(void *ucaddr);
#ifdef TARGET_PC
/* On PC, address translation goes through functions in pc_os.c
 * that map physical addresses relative to our simulated 24MB arena. */
/* Do NOT define macros - let the function declarations above be used */
#elif !DEBUG
#define OSPhysicalToCached(paddr)    ((void*) ((u32)(OS_BASE_CACHED   + (u32)(paddr))))
#define OSPhysicalToUncached(paddr)  ((void*) ((u32)(OS_BASE_UNCACHED + (u32)(paddr))))
#define OSCachedToPhysical(caddr)    ((u32)   ((u32)(caddr)  - OS_BASE_CACHED))
#define OSUncachedToPhysical(ucaddr) ((u32)   ((u32)(ucaddr) - OS_BASE_UNCACHED))
#define OSCachedToUncached(caddr)    ((void*) ((u8*)(caddr)  + (OS_BASE_UNCACHED - OS_BASE_CACHED)))
#define OSUncachedToCached(ucaddr)   ((void*) ((u8*)(ucaddr) - (OS_BASE_UNCACHED - OS_BASE_CACHED)))
#endif

#define OFFSET(addr, align) (((u32)(addr) & ((align)-1)))

#ifdef __cplusplus
}
#endif
#endif
