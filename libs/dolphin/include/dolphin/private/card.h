#ifndef CARD_H
#define CARD_H

#include "types.h"
#include "dolphin/card.h"
#include "dolphin/dvd.h"
#include "dolphin/os/OSAlarm.h"
#include "dolphin/os/OSThread.h"
#include "dolphin/dsp.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CARDDir {
    // total size: 0x40
    u8 gameName[4];                 // offset 0x0, size 0x4
    u8 company[2];                  // offset 0x4, size 0x2
    u8 _padding0;                   // offset 0x6, size 0x1
    u8 bannerFormat;                // offset 0x7, size 0x1
    u8 fileName[CARD_FILENAME_MAX]; // offset 0x8, size 0x20
    u32 time;                       // offset 0x28, size 0x4
    u32 iconAddr;                   // offset 0x2C, size 0x4
    u16 iconFormat;                 // offset 0x30, size 0x2
    u16 iconSpeed;                  // offset 0x32, size 0x2
    u8 permission;                  // offset 0x34, size 0x1
    u8 copyTimes;                   // offset 0x35, size 0x1
    u16 startBlock;                 // offset 0x36, size 0x2
    u16 length;                     // offset 0x38, size 0x2
    u8 _padding1[2];                // offset 0x3A, size 0x2
    u32 commentAddr;                // offset 0x3C, size 0x4
} CARDDir;

s32 __CARDGetStatusEx(s32 chan, s32 fileNo, CARDDir* dirent);
s32 __CARDSetStatusExAsync(s32 chan, s32 fileNo, CARDDir* dirent, CARDCallback callback);
s32 __CARDSetStatusEx(s32 chan, s32 fileNo, CARDDir* dirent);

#ifdef __cplusplus
}
#endif

#endif
