#ifndef JKRDVDRIPPER_H
#define JKRDVDRIPPER_H

#include "types.h"
#include "JSystem/JKernel/JKREnum.h"
#include "JSystem/JKernel/JKRDvdFile.h"

#ifdef __cplusplus

#define SZP_BUFFERSIZE 1024
#define REF_BUFFERSIZE 0x1120
#define DMA_BUFFERSIZE 0x100

struct SZPHeader {
    u32 magic;
    u32 decompSize;
};

struct SYaz0Header {
    u32 signature;
    u32 length;
};

class JKRDMCommand {
    JKRDMCommand();
    ~JKRDMCommand();
};

class JKRDvdRipper {
  public:
    enum EAllocDirection { ALLOC_DIR_DEFAULT = 0, ALLOC_DIR_TOP = 1, ALLOC_DIR_BOTTOM = 2 };

    static void* loadToMainRAM(const char* file, u8* buf, JKRExpandSwitch expandSwitch, u32 maxDest, JKRHeap* heap,
                               EAllocDirection allocDir, u32 offset, int* compressMode);
    static void* loadToMainRAM(s32 entrynum, u8* buf, JKRExpandSwitch expandSwitch, u32 maxDest, JKRHeap* heap,
                               EAllocDirection allocDir, u32 offset, int* compressMode);
    static void* loadToMainRAM(JKRDvdFile* file, u8* buf, JKRExpandSwitch expandSwitch, u32 maxDest, JKRHeap* heap,
                               EAllocDirection allocDir, u32 offset, int* compressMode);

    static inline bool isErrorRetry() {
        return JKRDvdRipper::errorRetry;
    }

    static JSUList<JKRDMCommand> sDvdAsyncList;

    static bool errorRetry;
};

inline void* JKRDvdToMainRam(long entryNum, u8* dst, JKRExpandSwitch expandSwitch, u32 fileSize, JKRHeap* heap,
                             JKRDvdRipper::EAllocDirection allocDirection, u32 startOffset, int* pCompression) {
    return JKRDvdRipper::loadToMainRAM((s32)entryNum, dst, expandSwitch, fileSize, heap, allocDirection, startOffset,
                                       pCompression);
}

inline void* JKRDvdToMainRam(const char* path, u8* dst, JKRExpandSwitch expandSwitch, u32 fileSize, JKRHeap* heap,
                             JKRDvdRipper::EAllocDirection allocDirection, u32 startOffset, int* pCompression) {
    return JKRDvdRipper::loadToMainRAM(path, dst, expandSwitch, fileSize, heap, allocDirection, startOffset,
                                       pCompression);
}

#endif
#endif
