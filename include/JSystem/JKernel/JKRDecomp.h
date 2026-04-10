#ifndef JKRDECOMP_H
#define JKRDECOMP_H

#include "types.h"
#include "dolphin/os/OSMessage.h"
#include "JSystem/JKernel/JKRDvdFile.h"
#include "JSystem/JKernel/JKRThread.h"
#include "JSystem/JKernel/JKRAram.h"
#include "JSystem/JKernel/JKREnum.h"

#ifdef __cplusplus
#define JKRDECOMP_MSG_BUF_COUNT 4
#define JKRDECOMP_STACK_SIZE 0x4000
#define JKRDECOMP_THREAD_MSG_BUF_COUNT 16

#define JKRDECOMP_READU32BE(ptr, offset) \
    (((u32)ptr[offset] << 24) | ((u32)ptr[offset + 1] << 16) | ((u32)ptr[offset + 2] << 8) | (u32)ptr[offset + 3])

#define SZ_MIN_BACKSIZE 3
#define SZ_DEFAULT_BACKSIZE 15 + SZ_MIN_BACKSIZE

#define SZP_GETBACKOFS(buf) (((*((u8*)buf) & 0xF) << 8) | (*(((u8*)buf) + 1)))
#define SZP_GETCOUNT(buf) (*((u16*)buf) >> 12)

#ifdef TARGET_PC
typedef void DecompCallback(uintptr_t);
#else
typedef void DecompCallback(u32);
#endif

class JKRDecompCommand {
  public:
    enum TransferType { MRAM = 0, ARAM = 1 };

    JKRDecompCommand();
    ~JKRDecompCommand();

    u8 _00[4];
    u8* mSrcBuffer;
    u8* mDstBuffer;
    u32 mSrcLength;
    u32 mSkipCount;
    DecompCallback* mCallback;
    JKRDecompCommand* mCmd;
    OSMessageQueue* pMesgQueue1C;
    TransferType transferType;
    JKRAMCommand* mAMCommand;
    OSMessageQueue mMesgQueue;
    OSMessage mMesgBuffer[1];
};

class JKRDecomp : public JKRThread {
  public:
    enum CompressionMode { NONE = 0, SZP = 1, SZS = 2 };

    JKRDecomp(s32 decompPriority);

    virtual ~JKRDecomp();

    virtual void* run();

    static JKRDecompCommand* prepareCommand(u8* srcBuffer, u8* dstBuffer, u32 srcLength, u32 skipCount,
                                            DecompCallback* callback);
    static CompressionMode checkCompressed(u8* buf);
    static JKRDecomp* create(s32 decompPriority);
    static void decode(u8* srcBuffer, u8* dstBuffer, u32 srcLength, u32 skipCount);
    static void decodeSZP(u8* srcBuffer, u8* dstBuffer, u32 srcLength, u32 skipCount);
    static void decodeSZS(u8* srcBuffer, u8* dstBuffer, u32 srcLength, u32 skipCount);
    static bool orderSync(u8* srcBuffer, u8* dstBuffer, u32 srcLength, u32 skipCount);
    static JKRDecompCommand* orderAsync(u8* srcBuffer, u8* dstBuffer, u32 srcLength, u32 skipCount,
                                        DecompCallback* callback);
    static bool sync(JKRDecompCommand* cmd, BOOL noBlock);
    static BOOL sendCommand(JKRDecompCommand* cmd);

    static OSMessageQueue sMessageQueue;
    static OSMessage sMessageBuffer[JKRDECOMP_MSG_BUF_COUNT];
    static JKRDecomp* sDecompObject;
};

inline JKRDecomp* JKRCreateDecompManager(s32 priority) {
    return JKRDecomp::create(priority);
}

inline int JKRCheckCompressed_noASR(u8* pBuf) {
    int compression = JKRDecomp::checkCompressed(pBuf);
    if (compression == JKRCOMPRESSION_ASR)
        compression = JKRCOMPRESSION_NONE;
    return compression;
}

inline JKRDecomp::CompressionMode JKRCheckCompressed(u8* buf) {
    return JKRDecomp::checkCompressed(buf);
}

inline u32 JKRDecompExpandSize(u8* buf) {
    return (buf[4] << 24) | (buf[5] << 16) | (buf[6] << 8) | buf[7];
}

inline void JKRDecompress(u8* src, u8* dst, u32 srcLength, u32 skipCount) {
    JKRDecomp::orderSync(src, dst, srcLength, skipCount);
}

int JKRDecompressFromDVD(JKRDvdFile* srcFile, void* buf, u32 size, u32 maxDest, u32 fileOffset, u32 srcOffset);
int JKRDecompressFromDVDToAram(JKRDvdFile* srcFile, u32 address, u32 fileSize, u32 maxDest, u32 fileOffset,
                               u32 srcOffset);
int JKRDecompressFromAramToMainRam(u32 srcAddress, void* dst, u32 fileSize, u32 maxDest, u32 fileOffset);

#endif
#endif
