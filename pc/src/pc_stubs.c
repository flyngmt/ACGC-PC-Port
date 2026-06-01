/* pc_stubs.c - stub definitions for symbols the decomp declares but we don't need */
#include <stdarg.h>
#include <stddef.h>  /* size_t */
#include "types.h"

typedef s32 OSPriority;

/* data symbols */
unsigned char cKF_Animation_R_getDataTable[4] = {0};
unsigned char cKF_Animation_R_getFixedTable[4] = {0};
unsigned char cKF_Animation_R_getFlagTable[4] = {0};
unsigned char cKF_Animation_R_getKeyTable[4] = {0};

char _e_data = 0;
char _f_rodata = 0;

/* my_malloc_current and save_game_image now provided by famicom.cpp */

/* DVD */
BOOL DVDCheckDisk(void) { return 0; }
BOOL DVDOpenDir(char* dirName, void* dir) { (void)dirName; (void)dir; return 0; }
BOOL DVDReadDir(void* dir, void* dirEntry) { (void)dir; (void)dirEntry; return 0; }
BOOL DVDCloseDir(void* dir) { (void)dir; return 0; }

/* GBA link */
void GBAInit(void) {}
s32 GBAGetStatus(s32 chan, u8* status) { (void)chan; (void)status; return -1; }
s32 GBAGetProcessStatus(s32 chan, u8* percentp) { (void)chan; (void)percentp; return -1; }
s32 GBARead(s32 chan, u8* dst, u8* status) { (void)chan; (void)dst; (void)status; return -1; }
s32 GBAWrite(s32 chan, u8* src, u8* status) { (void)chan; (void)src; (void)status; return -1; }
s32 GBAReset(s32 chan, u8* status) { (void)chan; (void)status; return -1; }
s32 GBAJoyBootAsync(s32 chan, s32 palette_color, s32 palette_speed, u8* programp,
                    s32 length, u8* status, void* callback) {
    (void)chan; (void)palette_color; (void)palette_speed; (void)programp;
    (void)length; (void)status; (void)callback; return -1;
}

/* OS threads */
BOOL OSCreateThread(void* thread, void* (*func)(void*), void* param,
                    void* stack, u32 stackSize, OSPriority priority, u16 attr) {
    (void)thread; (void)func; (void)param; (void)stack;
    (void)stackSize; (void)priority; (void)attr; return 0;
}
void OSCancelThread(void* thread) { (void)thread; }
void OSDetachThread(void* thread) { (void)thread; }
s32 OSResumeThread(void* thread) { (void)thread; return 0; }
s32 OSSuspendThread(void* thread) { (void)thread; return 0; }
BOOL OSIsThreadTerminated(void* thread) { (void)thread; return 1; }
BOOL OSJoinThread(void* thread, void** val) { (void)thread; (void)val; return 1; }
s32 OSEnableScheduler(void) { return 0; }
void OSYieldThread(void) {}
long OSCheckActiveThreads(void) { return 0; }
void OSFillFPUContext(void* context) { (void)context; }

/* OS misc */
u16 OSGetFontEncode(void) { return 0; }
u32 OSGetProgressiveMode(void) { return 0; }
void OSSetProgressiveMode(u32 on) { (void)on; }
u32 OSGetSoundMode(void) { return 0; }
void OSSetSoundMode(u32 mode) { (void)mode; }
void OSProtectRange(u32 chan, void* addr, u32 nBytes, u32 control) {
    (void)chan; (void)addr; (void)nBytes; (void)control;
}
void* OSSetErrorHandler(u16 error, void* handler) { (void)error; (void)handler; return NULL; }
void OSReportEnable(void) {}

/* VI */
void VIConfigurePan(u16 x_origin, u16 y_origin, u16 width, u16 height) {
    (void)x_origin; (void)y_origin; (void)width; (void)height;
}

int __abs(int x) { return x < 0 ? -x : x; }
void _strip(float x) { (void)x; }

/* famicom (NES emulator) — real implementation in famicom.cpp, stubs for linker */
void ksNesEmuFrame(void* wp, void* sp, u32 flags) { (void)wp; (void)sp; (void)flags; }

/* famicom.cpp dependencies: CARD functions, nesinfo, misc */
int CARDGetAttributes(int chan, int fileNo, u8* attr) { (void)chan; (void)fileNo; (void)attr; return -1; }
int CARDSetAttributes(int chan, int fileNo, u8 attr) { (void)chan; (void)fileNo; (void)attr; return -1; }
int CARDFastOpen(int chan, int fileNo, void* fileInfo) { (void)chan; (void)fileNo; (void)fileInfo; return -1; }
int bcmp(const void* a, const void* b, size_t n) { return memcmp(a, b, n); }

/* nesinfo — now provided by famicom_nesinfo.cpp */

/* libultra */
void osContGetQuery(void* status) { (void)status; }
void osContGetReadData(void* pad) { (void)pad; }
s32 osContInit(void* mq, u8* pattern_p, void* status) { (void)mq; (void)pattern_p; (void)status; return 0; }
s32 osContSetCh(u8 num_controllers) { (void)num_controllers; return 0; }
s32 osContStartQuery(void* mq) { (void)mq; return 0; }
s32 osContStartReadData(void* mq) { (void)mq; return 0; }
void osDestroyThread(void* t) { (void)t; }
s32 osGetThreadId(void* thread) { (void)thread; return 0; }
int osSetTimer(void* t, s64 countdown, s64 interval, void* mq, void* msg) {
    (void)t; (void)countdown; (void)interval; (void)mq; (void)msg; return 0;
}
void osSyncPrintf(const char* fmt, ...) { (void)fmt; }
void osWritebackDCache(void* vaddr, u32 nbytes) { (void)vaddr; (void)nbytes; }

int vaprintf(void* func, const char* fmt, va_list ap) { (void)func; (void)fmt; (void)ap; return 0; }
