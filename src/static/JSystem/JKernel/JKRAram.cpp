#include <dolphin/ar.h>
#include <string.h>

#include "JSystem/JKernel/JKRDecomp.h"
#include "JSystem/JKernel/JKRDvdRipper.h"
#include "JSystem/JKernel/JKRExpHeap.h"
#include "JSystem/JSystem.h"
#include "_mem.h"

JSUList<JKRAMCommand> JKRAram::sAramCommandList;
JKRAram* JKRAram::sAramObject;
u32 JKRAram::sSZSBufferSize = 0x400;

JKRAram* JKRAram::create(u32 aram_audio_buffer_size, u32 aram_audio_graph_size, s32 streamPriority, s32 decomp_priority,
                         s32 piece_priority) {
    if (!sAramObject) {
        sAramObject =
            new (JKRGetSystemHeap(), 0) JKRAram(aram_audio_buffer_size, aram_audio_graph_size, piece_priority);
    }

    JKRCreateAramStreamManager(streamPriority);
    JKRCreateDecompManager(decomp_priority);
    sAramObject->resume();
    return sAramObject;
}

OSMessage JKRAram::sMessageBuffer[4] = {
    nullptr,
    nullptr,
    nullptr,
    nullptr,
};

OSMessageQueue JKRAram::sMessageQueue = { 0 };

JKRAram::JKRAram(u32 bufSize, u32 graphSize, s32 priority) : JKRThread(0x4000, 0x10, priority) {
    u32 aramBase = ARInit(mStackArray, ARRAY_COUNT(mStackArray));
    ARQInit();

    u32 aramSize = ARGetSize();
    mAudioMemorySize = bufSize;
    if (graphSize == 0xffffffff) {
        mGraphMemorySize = aramSize - bufSize - aramBase;
        mUserMemorySize = 0;
    } else {
        mGraphMemorySize = graphSize;
        mUserMemorySize = (aramSize - (bufSize + graphSize) - aramBase);
    }

    mAudioMemoryPtr = ARAlloc(mAudioMemorySize);
    mGraphMemoryPtr = ARAlloc(mGraphMemorySize);

    if (mUserMemorySize != 0) { // ternary?
        mUserMemoryPtr = ARAlloc(mUserMemorySize);
    } else {
        mUserMemoryPtr = (u32)0;
    }

    mAramHeap = new (JKRHeap::getSystemHeap(), 0) JKRAramHeap(mGraphMemoryPtr, mGraphMemorySize);
}

JKRAram::~JKRAram() {
    sAramObject = nullptr;
    if (mAramHeap)
        delete mAramHeap;
}

void* JKRAram::run() {
    int result;
    JKRAMCommand* command;
    JKRAramCommand* message;
    OSInitMessageQueue(&sMessageQueue, sMessageBuffer, 4);
    do {
        OSReceiveMessage(&sMessageQueue, (OSMessage*)&message, OS_MESSAGE_BLOCK);
        result = message->mActive;
        command = (JKRAMCommand*)message->mArg;
        delete message;

        switch (result) {
            case 1:
                JKRAramPiece::startDMA(command);
                break;
        }
    } while (true);
}

bool JKRAram::checkOkAddress(u8* addr, u32 size, JKRAramBlock* block, u32 blockSize) {
#ifdef TARGET_PC
    if (!IS_ALIGNED((uintptr_t)addr, 0x20) && !IS_ALIGNED(size, 0x20)) {
#else
    if (!IS_ALIGNED((u32)addr, 0x20) && !IS_ALIGNED(size, 0x20)) {
#endif
        JPANIC(225, ":::address not 32Byte aligned.");
        return false;
    }

    if (block) {
        if (!IS_ALIGNED(block->getAddress() + blockSize, 0x20)) {
            JPANIC(234, ":::address not 32Byte aligned.");
            return false;
        }
    }
    return true;
}

void JKRAram::changeGroupIdIfNeed(u8* data, int groupId) {
    JKRHeap* currentHeap = JKRGetCurrentHeap();
    if (currentHeap->getHeapType() == 'EXPH' && groupId >= 0) {
        JKRExpHeap::CMemBlock* block = (JKRExpHeap::CMemBlock*)(data + -0x10);
        block->newGroupId(groupId);
    }
}

JKRAramBlock* JKRAram::mainRamToAram(u8* buf, u32 address, u32 alignedSize, JKRExpandSwitch expandSwitch, u32 fileSize,
                                     JKRHeap* heap, int id) {
    JKRAramBlock* block = nullptr;
    checkOkAddress(buf, address, nullptr, 0);
    if (expandSwitch == EXPAND_SWITCH_DECOMPRESS) {
        expandSwitch =
            (JKRCheckCompressed(buf) == JKRCOMPRESSION_NONE) ? EXPAND_SWITCH_DEFAULT : EXPAND_SWITCH_DECOMPRESS;
    }
    if (expandSwitch == EXPAND_SWITCH_DECOMPRESS) {
        u32 expandSize = JKRCheckCompressed(buf) != JKRCOMPRESSION_NONE ? JKRDecompExpandSize(buf) : 0;
        if (fileSize == 0 || fileSize > expandSize) {
            fileSize = expandSize;
        }
        if (address == 0) {
            block = JKRAllocFromAram(fileSize, JKRAramHeap::Head);
            if (block == nullptr)
                return nullptr;

            block->newGroupID(decideAramGroupId(id));
            address = block->getAddress();
        }
        if (alignedSize == 0 || alignedSize > expandSize)
            alignedSize = expandSize;

        if (fileSize > alignedSize)
            fileSize = alignedSize;

        void* allocatedMem = JKRAllocFromHeap(heap, fileSize, -32);
        if (allocatedMem == nullptr) {
            if (block != nullptr) {
                delete block;
            }
            block = nullptr;
        } else {
            JKRDecompress(buf, (u8*)allocatedMem, fileSize, 0);
#ifdef TARGET_PC
            JKRAramPcs(0, (uintptr_t)allocatedMem, address, alignedSize, block);
#else
            JKRAramPcs(0, (u32)allocatedMem, address, alignedSize, block);
#endif
            JKRFreeToHeap(heap, allocatedMem);
            block = block == nullptr ? (JKRAramBlock*)-1 : block;
        }
    } else {
        if (address == 0) {
            block = JKRAllocFromAram(alignedSize, JKRAramHeap::Head);
            block->newGroupID(decideAramGroupId(id));
            if (block == nullptr)
                return nullptr;

            address = block->getAddress();
        }

#ifdef TARGET_PC
        JKRAramPcs(0, (uintptr_t)buf, address, alignedSize, block);
#else
        JKRAramPcs(0, (u32)buf, address, alignedSize, block);
#endif
        block = block == nullptr ? (JKRAramBlock*)-1 : block;
    }
    return block;
}

JKRAramBlock* JKRAram::mainRamToAram(u8* buf, JKRAramBlock* block, u32 alignedSize, JKRExpandSwitch expandSwitch,
                                     u32 fileSize, JKRHeap* heap, int id) {
    checkOkAddress(buf, 0, block, 0);

    if (block == nullptr) {
        return mainRamToAram(buf, (u32)0, alignedSize, expandSwitch, fileSize, heap, id);
    }

    u32 blockSize = block->getSize();

    if (expandSwitch == EXPAND_SWITCH_DECOMPRESS) {
        fileSize = fileSize >= blockSize ? blockSize : fileSize;
    }

    alignedSize = alignedSize > blockSize ? blockSize : alignedSize;

    return mainRamToAram(buf, block->getAddress(), alignedSize, expandSwitch, fileSize, heap, id);
}

// TODO: figure out name of parameter 5
u8* JKRAram::aramToMainRam(u32 address, u8* buf, u32 srcSize, JKRExpandSwitch expandSwitch, u32 p5, JKRHeap* heap,
                           int id, u32* pSize) {
    int compression = JKRCOMPRESSION_NONE;
    if (pSize)
        *pSize = 0;

    checkOkAddress(buf, address, nullptr, 0);

    u32 expandSize;
    if (expandSwitch == EXPAND_SWITCH_DECOMPRESS) {
        u8 buffer[64];
#ifdef TARGET_PC
        u8* bufPtr = (u8*)ALIGN_NEXT((uintptr_t)buffer, 32);
        JKRAramPcs(1, address, (uintptr_t)bufPtr, sizeof(buffer) / 2,
                   nullptr); // probably change sizeof(buffer) / 2 to 32
#else
        u8* bufPtr = (u8*)ALIGN_NEXT((u32)buffer, 32);
        JKRAramPcs(1, address, (u32)bufPtr, sizeof(buffer) / 2,
                   nullptr); // probably change sizeof(buffer) / 2 to 32
#endif
        compression = JKRCheckCompressed(bufPtr);
        expandSize = JKRDecompExpandSize(bufPtr);
    }

    if (compression == JKRCOMPRESSION_YAZ0) // SZS
    {
        if (p5 != 0 && p5 < expandSize)
            expandSize = p5;

        if (buf == nullptr)
            buf = (u8*)JKRAllocFromHeap(heap, expandSize, 32);
        if (buf == nullptr)
            return nullptr;
        else {
            changeGroupIdIfNeed(buf, id);
            JKRDecompressFromAramToMainRam(address, buf, srcSize, expandSize, 0);
            if (pSize) {
                *pSize = expandSize;
            }
            return buf;
        }
    } else if (compression == JKRCOMPRESSION_YAY0) // SZP
    {
        u8* szpSpace = (u8*)JKRAllocFromHeap(heap, srcSize, -32);
        if (szpSpace == nullptr) {
            return nullptr;
        } else {
#ifdef TARGET_PC
            JKRAramPcs(1, address, (uintptr_t)szpSpace, srcSize, nullptr);
#else
            JKRAramPcs(1, address, (u32)szpSpace, srcSize, nullptr);
#endif
            if (p5 != 0 && p5 < expandSize)
                expandSize = p5;

            u8* szpBuffer = buf == nullptr ? (u8*)JKRAllocFromHeap(heap, expandSize, 32) : buf;

            if (szpBuffer == nullptr) {
                JKRFree(szpSpace);
                return nullptr;
            } else {
                changeGroupIdIfNeed(szpBuffer, id);
                JKRDecompress(szpSpace, szpBuffer, expandSize, 0);
                JKRFreeToHeap(heap, szpSpace);
                if (pSize) {
                    *pSize = expandSize;
                }
                return szpBuffer;
            }
        }
    } else // Not compressed or ASR
    {
        if (buf == nullptr)
            buf = (u8*)JKRAllocFromHeap(heap, srcSize, 32);
        if (buf == nullptr) {
            return nullptr;
        } else {
            changeGroupIdIfNeed(buf, id);
#ifdef TARGET_PC
            JKRAramPcs(1, address, (uintptr_t)buf, srcSize, nullptr);
#else
            JKRAramPcs(1, address, (u32)buf, srcSize, nullptr);
#endif
            if (pSize != nullptr) {
                *pSize = srcSize;
            }
            return buf;
        }
    }
}

// TODO: figure out what p6 does
u8* JKRAram::aramToMainRam(JKRAramBlock* block, u8* buf, u32 bufSize, u32 alignedBlockSize,
                           JKRExpandSwitch expandSwitch, u32 p6, JKRHeap* heap, int id, u32* pSize) {
    int compression = JKRCOMPRESSION_NONE;
    if (pSize)
        *pSize = 0;

    checkOkAddress(buf, 0, block, alignedBlockSize);

    if (block == nullptr) {
        JPANIC(667, ":::Bad Aram Block specified.\n");
    }

    u32 freeSize = block->getSize();

    if (alignedBlockSize >= freeSize)
        return nullptr;

    bufSize = bufSize == 0 ? freeSize : bufSize;

    if (alignedBlockSize + bufSize > freeSize) {
        bufSize = freeSize - alignedBlockSize;
    }

    return aramToMainRam(alignedBlockSize + block->getAddress(), buf, bufSize, expandSwitch, p6, heap, id, pSize);
}

static OSMutex decompMutex;

static u8* szpBuf;
static u8* szpEnd;
static u8* refBuf;
static u8* refEnd;
static u8* refCurrent;
static u32 srcOffset;
static u32 transLeft;
static u8* srcLimit;
static u32 srcAddress;
static u32 fileOffset;
static u32 readCount;
static u32 maxDest;
static bool isInitMutex;
static u32* tsPtr;
static u32 tsArea;

static u8* firstSrcData();
static u8* nextSrcData(u8* current);
static int decompSZS_subroutine(u8* src, u8* dest);

void JKRAram::aramSync(JKRAMCommand*, int) {
    // JUT_REPORT_MSG("bad aramSync\n");
}

int JKRDecompressFromAramToMainRam(u32 src, void* dst, u32 srcLength, u32 dstLength, u32 offset) {
    szpBuf = (u8*)JKRAllocFromSysHeap(SZP_BUFFERSIZE, 32);

    JUT_ASSERT(szpBuf != 0);

    szpEnd = szpBuf + SZP_BUFFERSIZE;
    if (offset != 0) {
        refBuf = (u8*)JKRAllocFromSysHeap(0x1120, 0);
        JUT_ASSERT(refBuf != 0);
        refEnd = refBuf + 0x1120;
        refCurrent = refBuf;
    } else {
        refBuf = nullptr;
    }

    srcAddress = src;
    srcOffset = 0;
    transLeft = (srcLength != 0) ? srcLength : -1;
    fileOffset = offset;
    readCount = 0;
    maxDest = dstLength;

    decompSZS_subroutine(firstSrcData(), (u8*)dst);
    JKRFree(szpBuf);

    if (refBuf) {
        JKRFree(refBuf);
    }

    return 0;
}

int decompSZS_subroutine(u8* src, u8* dest) {
    u8* endPtr;
    s32 validBitCount = 0;
    s32 currCodeByte = 0;

    if (src[0] != 'Y' || src[1] != 'a' || src[2] != 'z' || src[3] != '0') {
        return -1;
    }

    SYaz0Header* header = (SYaz0Header*)src;
    endPtr = dest + (header->length - fileOffset);
    if (endPtr > dest + maxDest) {
        endPtr = dest + maxDest;
    }

    src += 0x10;
    do {
        if (validBitCount == 0) {
            if ((src > srcLimit) && transLeft) {
                src = nextSrcData(src);
            }
            currCodeByte = *src;
            validBitCount = 8;
            src++;
        }
        if (currCodeByte & 0x80) {
            if (fileOffset != 0) {
                if (readCount >= fileOffset) {
                    *dest = *src;
                    dest++;
                    if (dest == endPtr) {
                        break;
                    }
                }
                *(refCurrent++) = *src;
                if (refCurrent == refEnd) {
                    refCurrent = refBuf;
                }
                src++;
            } else {
                *dest = *src;
                dest++;
                src++;
                if (dest == endPtr) {
                    break;
                }
            }
            readCount++;
        } else {
            u32 dist = src[1] | (src[0] & 0x0f) << 8;
            s32 numBytes = src[0] >> 4;
            src += 2;
            u8* copySource;
            if (fileOffset != 0) {
                copySource = refCurrent - dist - 1;
                if (copySource < refBuf) {
                    copySource += refEnd - refBuf;
                }
            } else {
                copySource = dest - dist - 1;
            }
            if (numBytes == 0) {
                numBytes = *src + 0x12;
                src += 1;
            } else {
                numBytes += 2;
            }
            if (fileOffset != 0) {
                do {
                    if (readCount >= fileOffset) {
                        *dest = *copySource;
                        dest++;
                        if (dest == endPtr) {
                            break;
                        }
                    }
                    *(refCurrent++) = *copySource;
                    if (refCurrent == refEnd) {
                        refCurrent = refBuf;
                    }
                    copySource++;
                    if (copySource == refEnd) {
                        copySource = refBuf;
                    }
                    readCount++;
                    numBytes--;
                } while (numBytes != 0);
            } else {
                do {
                    *dest = *copySource;
                    dest++;
                    if (dest == endPtr) {
                        break;
                    }
                    readCount++;
                    numBytes--;
                    copySource++;
                } while (numBytes != 0);
            }
        }
        currCodeByte <<= 1;
        validBitCount--;
    } while (dest < endPtr);
    return 0;
}

static u8* firstSrcData() {
    srcLimit = szpEnd - 0x19;
    u8* buf = szpBuf;
    u32 maxSize = (szpEnd - szpBuf);
    u32 transSize = MIN(transLeft, maxSize);

#ifdef TARGET_PC
    JKRAramPcs(1, srcAddress + srcOffset, (uintptr_t)buf, ALIGN_NEXT(transSize, 32), nullptr);
#else
    JKRAramPcs(1, srcAddress + srcOffset, (u32)buf, ALIGN_NEXT(transSize, 32), nullptr);
#endif

    srcOffset += transSize;
    transLeft -= transSize;

    return buf;
}

u8* nextSrcData(u8* current) {
    u8* dest;
#ifdef TARGET_PC
    u32 left = (uintptr_t)(szpEnd - current);
#else
    u32 left = (u32)(szpEnd - current);
#endif
    if (IS_NOT_ALIGNED(left, 0x20))
        dest = szpBuf + 0x20 - (left & (0x20 - 1));
    else
        dest = szpBuf;

    memcpy(dest, current, left);
#ifdef TARGET_PC
    u32 transSize = (uintptr_t)(szpEnd - (dest + left));
#else
    u32 transSize = (u32)(szpEnd - (dest + left));
#endif
    if (transSize > transLeft)
        transSize = transLeft;
    JUT_ASSERT(transSize > 0);

#ifdef TARGET_PC
    JKRAramPcs(1, (uintptr_t)(srcAddress + srcOffset), ((uintptr_t)dest + left), ALIGN_NEXT(transSize, 0x20), nullptr);
#else
    JKRAramPcs(1, (u32)(srcAddress + srcOffset), ((u32)dest + left), ALIGN_NEXT(transSize, 0x20), nullptr);
#endif
    srcOffset += transSize;
    transLeft -= transSize;

    if (transLeft == 0)
        srcLimit = (dest + left) + transSize;

    return dest;
}
