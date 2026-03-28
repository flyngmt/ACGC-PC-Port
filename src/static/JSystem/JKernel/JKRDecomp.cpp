#include "JSystem/JKernel/JKRDecomp.h"

#include "JSystem/JKernel/JKRAram.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JSystem.h"
#include "dolphin/os/OSMessage.h"
#include "types.h"

OSMessage JKRDecomp::sMessageBuffer[JKRDECOMP_MSG_BUF_COUNT] = { 0 };
OSMessageQueue JKRDecomp::sMessageQueue = { 0 };
JKRDecomp* JKRDecomp::sDecompObject;

JKRDecomp* JKRDecomp::create(s32 decompPriority) {
    if (JKRDecomp::sDecompObject == nullptr) {
        JKRDecomp::sDecompObject = new (JKRGetSystemHeap(), 0) JKRDecomp(decompPriority);
    }

    return JKRDecomp::sDecompObject;
}

JKRDecomp::JKRDecomp(s32 priority) : JKRThread(JKRDECOMP_STACK_SIZE, JKRDECOMP_THREAD_MSG_BUF_COUNT, priority) {
    OSResumeThread(this->mThreadRecord);
}

JKRDecomp::~JKRDecomp() {
}

void* JKRDecomp::run() {
    OSMessage recMesg;
    JKRDecompCommand* cmd;
    OSInitMessageQueue(&JKRDecomp::sMessageQueue, JKRDecomp::sMessageBuffer, JKRDECOMP_MSG_BUF_COUNT);

    while (true) {
        while (true) {
            while (true) {
                OSReceiveMessage(&JKRDecomp::sMessageQueue, &recMesg, OS_MESSAGE_BLOCK);
                cmd = static_cast<JKRDecompCommand*>(recMesg);
                JKRDecomp::decode(cmd->mSrcBuffer, cmd->mDstBuffer, cmd->mSrcLength, cmd->mSkipCount);

                if (cmd->transferType == JKRDecompCommand::MRAM) {
                    break;
                }

                if (cmd->transferType == JKRDecompCommand::ARAM) {
                    JKRAramPcs_SendCommand(cmd->mAMCommand);
                }
            }

            if (cmd->mCallback == nullptr) {
                break;
            }

#ifdef TARGET_PC
            cmd->mCallback((uintptr_t)cmd);
#else
            cmd->mCallback((u32)cmd);
#endif
        }

        if (cmd->pMesgQueue1C != nullptr) {
            OSSendMessage(cmd->pMesgQueue1C, (OSMessage)1, OS_MESSAGE_NOBLOCK);
        } else {
            OSSendMessage(&cmd->mMesgQueue, (OSMessage)1, OS_MESSAGE_NOBLOCK);
        }
    }
}

JKRDecompCommand* JKRDecomp::prepareCommand(u8* srcBuffer, u8* dstBuffer, u32 srcLength, u32 skipCount,
                                            DecompCallback* callback) {
    JKRDecompCommand* cmd = new (JKRGetSystemHeap(), -4) JKRDecompCommand();

    cmd->mSrcBuffer = srcBuffer;
    cmd->mDstBuffer = dstBuffer;
    cmd->mSrcLength = srcLength;
    cmd->mSkipCount = skipCount;
    cmd->mCallback = callback;

    return cmd;
}

BOOL JKRDecomp::sendCommand(JKRDecompCommand* cmd) {
    BOOL res = OSSendMessage(&JKRDecomp::sMessageQueue, (OSMessage)cmd, OS_MESSAGE_BLOCK);

#ifdef JSYSTEM_DEBUG
    if (res == FALSE) {
        JPANIC(142, "Decomp MesgBuf FULL!");
    }
#endif

    return res;
}

JKRDecompCommand* JKRDecomp::orderAsync(u8* srcBuffer, u8* dstBuffer, u32 srcLength, u32 skipCount,
                                        DecompCallback* callback) {
    JKRDecompCommand* cmd = JKRDecomp::prepareCommand(srcBuffer, dstBuffer, srcLength, skipCount, callback);
#ifdef TARGET_PC
    /* Execute decompression synchronously on PC (no worker thread) */
    JKRDecomp::decode(cmd->mSrcBuffer, cmd->mDstBuffer, cmd->mSrcLength, cmd->mSkipCount);
#else
    JKRDecomp::sendCommand(cmd);
#endif
    return cmd;
}

bool JKRDecomp::sync(JKRDecompCommand* cmd, BOOL noBlock) {
#ifdef TARGET_PC
    /* On PC, decompression already happened synchronously */
    return true;
#else
    OSMessage msg;

    if (!noBlock) {
        OSReceiveMessage(&cmd->mMesgQueue, &msg, OS_MESSAGE_BLOCK);
        return true;
    } else {
        return OSReceiveMessage(&cmd->mMesgQueue, &msg, OS_MESSAGE_NOBLOCK) != FALSE;
    }
#endif
}

bool JKRDecomp::orderSync(u8* srcBuffer, u8* dstBuffer, u32 srcLength, u32 skipCount) {
    JKRDecompCommand* cmd = JKRDecomp::orderAsync(srcBuffer, dstBuffer, srcLength, skipCount, nullptr);
    bool res = JKRDecomp::sync(cmd, FALSE);
    delete cmd;
    return res;
}

void JKRDecomp::decode(u8* srcBuffer, u8* dstBuffer, u32 srcLength, u32 skipCount) {
    CompressionMode mode = JKRDecomp::checkCompressed(srcBuffer);
    if (mode == SZP) {
        JKRDecomp::decodeSZP(srcBuffer, dstBuffer, srcLength, skipCount);
    } else if (mode == SZS) {
        JKRDecomp::decodeSZS(srcBuffer, dstBuffer, srcLength, skipCount);
    }
}

void JKRDecomp::decodeSZP(u8* src, u8* dst, u32 srcLength, u32 skipCount) {
    int srcChunkOffset;
    int count;
    int dstOffset;
    u32 length;
    int linkInfo;
    int offset;
    int i;

    int decodedSize = JKRDECOMP_READU32BE(src, 4);
    int linkTableOffset = JKRDECOMP_READU32BE(src, 8);
    int srcDataOffset = JKRDECOMP_READU32BE(src, 12);

    dstOffset = 0;
    u32 counter = 0; // curently counter gets assembled before the READ_U32 operations
    srcChunkOffset = 16;

    u32 chunkBits;
    if (srcLength == 0)
        return;
    if (skipCount > decodedSize)
        return;

    length = srcLength;
    do {
        if (counter == 0) {
            chunkBits = JKRDECOMP_READU32BE(src, srcChunkOffset);
            srcChunkOffset += sizeof(u32);
            counter = sizeof(u32) * 8;
        }

        if (chunkBits & 0x80000000) {
            if (skipCount == 0) {
                dst[dstOffset] = src[srcDataOffset];
                length--;
                if (length == 0)
                    return;
            } else {
                skipCount--;
            }
            dstOffset++;
            srcDataOffset++;
        } else {
            linkInfo = src[linkTableOffset] << 8 | src[linkTableOffset + 1];
            linkTableOffset += sizeof(u16);

            offset = dstOffset - (linkInfo & 0xFFF);
            count = (linkInfo >> 12);
            if (count == 0) {
                count = (u32)src[srcDataOffset++] + 0x12;
            } else
                count += 2;

            if ((int)count > decodedSize - dstOffset)
                count = decodedSize - dstOffset;

            for (i = 0; i < (int)count; i++, dstOffset++, offset++) {
                if (skipCount == 0) {
                    dst[dstOffset] = dst[offset - 1];
                    length--;
                    if (length == 0)
                        return;
                } else
                    skipCount--;
            }
        }

        chunkBits <<= 1;
        counter--;
    } while (dstOffset < decodedSize);
}

void JKRDecomp::decodeSZS(u8* src_buffer, u8* dst_buffer, u32 srcSize, u32 skipCount) {
    u8* decompEnd = dst_buffer + *(u32*)(src_buffer + 4) - skipCount;
    u8* copyStart;
    s32 copyByteCount;
    s32 chunkBitsLeft = 0;
    s32 chunkBits;

    if (srcSize == 0)
        return;
    if (skipCount > *(u32*)src_buffer)
        return;

    u8* curSrcPos = src_buffer + 0x10;
    do {
        if (chunkBitsLeft == 0) {
            chunkBits = *curSrcPos++;
            chunkBitsLeft = 8;
        }
        if ((chunkBits & 0x80) != 0) {
            if (skipCount == 0) {
                *dst_buffer = *curSrcPos;
                srcSize--;
                dst_buffer++;
                if (srcSize == 0)
                    return;
            } else {
                skipCount--;
            }
            curSrcPos++;
        } else {
            u8 curVal = *curSrcPos;
            copyStart = dst_buffer - (curSrcPos[1] | (curVal & 0xF) << 8);
            curSrcPos += 2;
            if (curVal >> 4 == 0) {
                copyByteCount = *curSrcPos + 0x12;
                curSrcPos++;
            } else {
                copyByteCount = (curVal >> 4) + 2;
            }
            do {
                if (skipCount == 0) {
                    *dst_buffer = *(copyStart - 1);
                    srcSize--;
                    dst_buffer++;
                    if (srcSize == 0)
                        return;
                } else {
                    skipCount--;
                }
                copyByteCount--;
                copyStart++;
            } while (copyByteCount != 0);
        }
        chunkBits <<= 1;
        chunkBitsLeft--;
    } while (dst_buffer != decompEnd);
}

JKRDecomp::CompressionMode JKRDecomp::checkCompressed(u8* buf) {
    if (buf[0] == 'Y' && buf[1] == 'a' && buf[3] == '0') {
        if (buf[2] == 'y') {
            return SZP;
        }

        if (buf[2] == 'z') {
            return SZS;
        }
    }

    return NONE;
}

JKRDecompCommand::JKRDecompCommand() {
    OSInitMessageQueue(&this->mMesgQueue, this->mMesgBuffer, 1);
    this->mCallback = nullptr;
    this->pMesgQueue1C = nullptr;
    this->mCmd = this;
    this->transferType = MRAM;
}

JKRDecompCommand::~JKRDecompCommand() {
}
