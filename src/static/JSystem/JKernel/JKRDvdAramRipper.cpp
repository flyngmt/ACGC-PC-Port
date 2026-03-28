#include "JSystem/JKernel/JKRDvdAramRipper.h"

#include <_mem.h>
#include <string.h>
#include <dolphin/vi.h>

#include "JSystem/JKernel/JKRDecomp.h"
#include "JSystem/JKernel/JKRDvdFile.h"
#include "JSystem/JKernel/JKRDvdRipper.h"
#include "JSystem/JUtility/JUTAssertion.h"

JSUList<JKRADCommand> JKRDvdAramRipper::sDvdAramAsyncList;

bool JKRDvdAramRipper::errorRetry = true;
int JKRDvdAramRipper::sSZSBufferSize = 0x400;

JKRAramBlock* JKRDvdAramRipper::loadToAram(s32 entrynum, u32 p2, JKRExpandSwitch expSwitch, u32 p6, u32 p7) {
    JKRDvdFile dvdFile;
    if (!dvdFile.open(entrynum))
        return nullptr;
    else
        return loadToAram(&dvdFile, p2, expSwitch, p6, p7);
}

JKRAramBlock* JKRDvdAramRipper::loadToAram(JKRDvdFile* dvdFile, u32 p1, JKRExpandSwitch p2, u32 p3, u32 p4) {
    JKRADCommand* command = loadToAram_Async(dvdFile, p1, p2, nullptr, p3, p4);
    syncAram(command, 0);

    if (p1) {
        delete command;
        return (JKRAramBlock*)-1;
    }

    JKRAramBlock* result = command->mBlock;
    delete command;
    return result;
}

JKRADCommand* JKRDvdAramRipper::loadToAram_Async(JKRDvdFile* dvdFile, u32 p1, JKRExpandSwitch expSwitch,
                                                 JKRADCommand::LoadCallback cb, u32 p4, u32 p5) {
    JKRADCommand* command = new (JKRGetSystemHeap(), -4) JKRADCommand();
    command->mDvdFile = dvdFile;
    command->_1C = p1;
    command->mBlock = nullptr;
    command->mExpandSwitch = expSwitch;
    command->mCallBack = cb;

    command->_14 = p4;
    command->_18 = p5;

    if (!callCommand_Async(command)) {
        delete command;
        return nullptr;
    }

    return command;
}

JKRADCommand* JKRDvdAramRipper::callCommand_Async(JKRADCommand* command) {
    bool isCmdTrdNull = true;
    JKRDvdFile* dvdFile = command->mDvdFile;
    int compression = JKRCOMPRESSION_NONE;
    OSLockMutex(&dvdFile->mAramMutex);

    s32 uncompressedSize;

    if (dvdFile->mAramThread) {
        isCmdTrdNull = false;
    } else {
        dvdFile->mAramThread = OSGetCurrentThread();
        JSUFileInputStream* stream = new (JKRGetSystemHeap(), -4) JSUFileInputStream(dvdFile);
        dvdFile->mInputStream = stream;
        u32 fileSize = dvdFile->getFileSize();
        if (command->_18 && fileSize > command->_18) {
            fileSize = command->_18;
        }
        fileSize = ALIGN_NEXT(fileSize, 0x20);
        if (command->mExpandSwitch == EXPAND_SWITCH_DECOMPRESS) {
            u8 buffer[0x40];
#ifdef TARGET_PC
            u8* bufPtr = (u8*)ALIGN_NEXT((uintptr_t)buffer, 0x20);
#else
            u8* bufPtr = (u8*)ALIGN_NEXT((u32)buffer, 0x20);
#endif
            while (true) {
                if (DVDReadPrio(dvdFile->getFileInfo(), bufPtr, 0x20, 0, 2) >= 0) {
                    break;
                }

                if (errorRetry == false) {
                    delete stream;
                    return nullptr;
                }

                VIWaitForRetrace();
            }

            compression = JKRCheckCompressed(bufPtr);
            u32 expSize = JKRDecompExpandSize(bufPtr);
            uncompressedSize = expSize;

            if ((command->_18 != 0) && expSize > command->_18) {
                uncompressedSize = command->_18;
            }
        }

        if (compression == JKRCOMPRESSION_NONE) {
            command->mExpandSwitch = EXPAND_SWITCH_DEFAULT;
        }

        if (command->mExpandSwitch == EXPAND_SWITCH_DECOMPRESS) {
            if (command->_1C == 0 && command->mBlock == nullptr) {
                command->mBlock = JKRAram::getAramHeap()->alloc(uncompressedSize, JKRAramHeap::Head);
                if (command->mBlock) {
                    command->_1C = command->mBlock->mAddress;
                }
                dvdFile->mAramBlock = command->mBlock;
            }

            if (command->mBlock) {
                command->_1C = command->mBlock->mAddress;
            }

            if (command->_1C == 0) {
                dvdFile->mAramThread = nullptr;
                return nullptr;
            }
        } else {
            if (command->_1C == 0 && !command->mBlock) {
                command->mBlock = JKRAram::getAramHeap()->alloc(fileSize, JKRAramHeap::Head);
            }

            if (command->mBlock) {
                command->_1C = command->mBlock->mAddress;
            }

            if (command->_1C == 0) {
                dvdFile->mAramThread = nullptr;
                return nullptr;
            }
        }


        if (compression == 0) {
            command->mStreamCommand =
                JKRAramStream::write_StreamToAram_Async(stream, command->_1C, fileSize - command->_14, command->_14);
        } else if (compression == JKRCOMPRESSION_YAY0) {
            command->mStreamCommand =
                JKRAramStream::write_StreamToAram_Async(stream, command->_1C, fileSize - command->_14, command->_14);
        } else if (compression == JKRCOMPRESSION_YAZ0) {
            command->mStreamCommand = nullptr;
            JKRDecompressFromDVDToAram(command->mDvdFile, command->_1C, fileSize, uncompressedSize, command->_14, 0);
        }

        if (!command->mCallBack) {
            sDvdAramAsyncList.append(&command->mLink);
        } else {
#ifdef TARGET_PC
            command->mCallBack((uintptr_t)command);
#else
            command->mCallBack((u32)command);
#endif
        }
    }

    OSUnlockMutex(&dvdFile->mAramMutex);
    return isCmdTrdNull == true ? command : nullptr;
}

bool JKRDvdAramRipper::syncAram(JKRADCommand* command, int p1) {
    JKRDvdFile* dvdFile = command->mDvdFile;
    OSLockMutex(&dvdFile->mAramMutex);

    if (command->mStreamCommand) {
        JKRAramStreamCommand* var1 = JKRAramStream::sync(command->mStreamCommand, p1);

        if (p1 != 0 && var1 == nullptr) {
            OSUnlockMutex(&dvdFile->mAramMutex);
            return false;
        }
    }

    sDvdAramAsyncList.remove(&command->mLink);
    if (command->mStreamCommand) {
        delete command->mStreamCommand;
    }

    delete dvdFile->mInputStream;
    dvdFile->mAramThread = nullptr;
    OSUnlockMutex(&dvdFile->mAramMutex);
    return true;
}

JKRADCommand::JKRADCommand() : mLink(this) {
    _44 = 0;
}

JKRADCommand::~JKRADCommand() {
    if (_44 == 1)
        delete mDvdFile;
}

static OSMutex decompMutex;
static u8* szpBuf;
static u8* szpEnd;
static u8* refBuf;
static u8* refEnd;
static u8* refCurrent;
static u8* dmaBuf;
static u8* dmaEnd;
static u8* dmaCurrent;
static u32 srcOffset;
static u32 transLeft;
static u8* srcLimit;
static JKRDvdFile* srcFile;
static u32 fileOffset;
static int readCount;
static u32 maxDest;
static bool isInitMutex;
static u32* tsPtr;
static u32 tsArea;

static int decompSZS_subroutine(u8*, u32);
static u8* firstSrcData();
static u8* nextSrcData(u8*);
static u32 dmaBufferFlush(u32);

int JKRDecompressFromDVDToAram(JKRDvdFile* dvdFile, u32 address, u32 fileSize, u32 _maxDest, u32 _fileOffset,
                               u32 _srcOffset) {
    int result = 0;
    szpBuf = (u8*)JKRAllocFromSysHeap(SZP_BUFFERSIZE, 32);
    JUT_ASSERT(szpBuf != 0);
    szpEnd = szpBuf + SZP_BUFFERSIZE;

    refBuf = (u8*)JKRAllocFromSysHeap(REF_BUFFERSIZE, 0);
    JUT_ASSERT(refBuf != 0);
    refEnd = refBuf + REF_BUFFERSIZE;
    refCurrent = refBuf;

    dmaBuf = (u8*)JKRAllocFromSysHeap(DMA_BUFFERSIZE, 32);
    JUT_ASSERT(dmaBuf != 0);
    dmaEnd = dmaBuf + DMA_BUFFERSIZE;
    dmaCurrent = dmaBuf;

    srcFile = dvdFile;
    srcOffset = _srcOffset;
    transLeft = fileSize - _srcOffset;
    fileOffset = _fileOffset;
    readCount = 0;
    maxDest = _maxDest;

    u8* first = firstSrcData();
    if (first)
        result = decompSZS_subroutine(first, address);

    JKRFree(szpBuf);
    JKRFree(refBuf);
    JKRFree(dmaBuf);

    return result;
}

int decompSZS_subroutine(u8* src, u32 dmaAddr) {
    u32 endPtr;
    u8* copySource;
    s32 validBitCount = 0;
    s32 currCodeByte = 0;
    s32 numBytes;

    u32 dmaStart = dmaAddr;

    if (src[0] != 'Y' || src[1] != 'a' || src[2] != 'z' || src[3] != '0')
        return -1;

    SYaz0Header* header = (SYaz0Header*)src;
    endPtr = dmaAddr + (header->length - fileOffset);
    if (endPtr > dmaAddr + maxDest)
        endPtr = dmaAddr + maxDest;

    src += 0x10;

    do {
        if (validBitCount == 0) {
            if ((src > srcLimit) && transLeft)
                src = nextSrcData(src);

            currCodeByte = *src++;
            validBitCount = 8;
        }
        if (currCodeByte & 0x80) {
            if (readCount >= fileOffset) {
                dmaAddr++;
                *dmaCurrent++ = *src;
                if (dmaCurrent == dmaEnd)
                    dmaStart += dmaBufferFlush(dmaStart);

                if (dmaAddr == endPtr)
                    break;
            }
            *(refCurrent++) = *src;
            if (refCurrent == refEnd)
                refCurrent = refBuf;

            src++;

            readCount++;
        } else {
            int t0 = src[0];
            int t1 = src[1];
            copySource = refCurrent - (t1 | (t0 & 0x0f) << 8) - 1;
            numBytes = t0 >> 4;
            src += 2;
            if (copySource < refBuf)
                copySource = copySource + (refEnd - refBuf);

            if (numBytes == 0)
                numBytes = *src++ + 0x12;
            else
                numBytes += 2;

            do {
                if (readCount >= fileOffset) {
                    dmaAddr++;
                    *(dmaCurrent++) = *copySource;
                    if (dmaCurrent == dmaEnd)
                        dmaStart += dmaBufferFlush(dmaStart);

                    if (dmaAddr == endPtr)
                        break;
                }
                *(refCurrent++) = *copySource;
                if (refCurrent == refEnd)
                    refCurrent = refBuf;

                copySource++;

                if (copySource == refEnd)
                    copySource = refBuf;

                readCount++;
                numBytes--;
            } while (numBytes != 0);
        }
        currCodeByte <<= 1;
        validBitCount--;
    } while (dmaAddr < endPtr);

    dmaBufferFlush(dmaStart);

    return 0;
}

u8* firstSrcData() {
    srcLimit = szpEnd - 0x19;
    u8* buf = szpBuf;
    u32 max = (szpEnd - szpBuf);
    u32 transSize = MIN(transLeft, max);

    while (true) {
        if (0 <= DVDReadPrio(srcFile->getFileInfo(), buf, transSize, 0, 2))
            break;
        if (!JKRDvdAramRipper::isErrorRetry())
            return nullptr;
        VIWaitForRetrace();
    }
    srcOffset += transSize;
    transLeft -= transSize;
    return buf;
}

u8* nextSrcData(u8* src) {
    u32 limit = szpEnd - src;
    u8* buf;
    if (IS_NOT_ALIGNED(limit, 0x20))
        buf = szpBuf + 0x20 - (limit & (0x20 - 1));
    else
        buf = szpBuf;

    memcpy(buf, src, limit);
#ifdef TARGET_PC
    uintptr_t transSize = (uintptr_t)(szpEnd - (buf + limit));
#else
    u32 transSize = (u32)(szpEnd - (buf + limit));
#endif
    if (transSize > transLeft)
        transSize = transLeft;

    JUT_ASSERT(transSize > 0);
    while (true) {
        int result = DVDReadPrio(srcFile->getFileInfo(), (buf + limit), transSize, srcOffset, 2);
        if (result >= 0)
            break;

        if (!JKRDvdAramRipper::isErrorRetry())
            return nullptr;

        VIWaitForRetrace();
    }

    srcOffset += transSize;
    transLeft -= transSize;
    if (transLeft == 0)
        srcLimit = transSize + (buf + limit);

    return buf;
}

u32 dmaBufferFlush(u32 src) {
    if (dmaCurrent == dmaBuf) {
        return 0;
    } else {
#ifdef TARGET_PC
        u32 length = ALIGN_NEXT((uintptr_t)(dmaCurrent - dmaBuf), 32);
        JKRAramPiece::orderSync(0, (uintptr_t)dmaBuf, src, length, nullptr);
#else
        u32 length = ALIGN_NEXT((u32)(dmaCurrent - dmaBuf), 32);
        JKRAramPiece::orderSync(0, (u32)dmaBuf, src, length, nullptr);
#endif
        dmaCurrent = dmaBuf;
        return length;
    }
}
