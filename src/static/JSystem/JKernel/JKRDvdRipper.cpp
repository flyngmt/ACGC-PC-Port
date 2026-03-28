#include "_mem.h"
#include "types.h"
#include "dolphin/vi.h"
#include "JSystem/JSystem.h"
#include "JSystem/JKernel/JKRMacro.h"
#include "JSystem/JKernel/JKRDvdFile.h"
#include "JSystem/JKernel/JKRDecomp.h"

#include "JSystem/JKernel/JKRDvdRipper.h"

JSUList<JKRDMCommand> JKRDvdRipper::sDvdAsyncList;
bool JKRDvdRipper::errorRetry = true;

static int decompSZS_subroutine(u8* src, u8* dest);
static u8* firstSrcData();
static u8* nextSrcData(u8* nowData);

void* JKRDvdRipper::loadToMainRAM(const char* file, u8* buf, JKRExpandSwitch expandSwitch, u32 maxDest, JKRHeap* heap,
                                  EAllocDirection allocDir, u32 offset, int* compressMode) {
    JKRDvdFile dvdFile;

    if (!dvdFile.open(file)) {
        return nullptr;
    } else {
        return JKRDvdRipper::loadToMainRAM(&dvdFile, buf, expandSwitch, maxDest, heap, allocDir, offset, compressMode);
    }
}

void* JKRDvdRipper::loadToMainRAM(s32 entrynum, u8* buf, JKRExpandSwitch expandSwitch, u32 maxDest, JKRHeap* heap,
                                  EAllocDirection allocDir, u32 offset, int* compressMode) {
    JKRDvdFile dvdFile;

    if (!dvdFile.open(entrynum)) {
        return nullptr;
    } else {
        return JKRDvdRipper::loadToMainRAM(&dvdFile, buf, expandSwitch, maxDest, heap, allocDir, offset, compressMode);
    }
}

void* JKRDvdRipper::loadToMainRAM(JKRDvdFile* file, u8* buf, JKRExpandSwitch expandSwitch, u32 maxDest, JKRHeap* heap,
                                  EAllocDirection allocDir, u32 offset, int* compressMode) {
    u32 finalSize;

    bool allocated = false;
    JKRDecomp::CompressionMode fileCompressMode = JKRDecomp::NONE;
    u8* mem = nullptr;
    u32 fileSize = ALIGN_NEXT(file->getFileSize(), 32);

    if (expandSwitch == EXPAND_SWITCH_DECOMPRESS) {
        u8 buffer[64];
#ifdef TARGET_PC
        u8* aligned_buf = (u8*)ALIGN_NEXT((uintptr_t)buffer, 32);
#else
        u8* aligned_buf = (u8*)ALIGN_NEXT((u32)buffer, 32);
#endif
        while (true) {
            if (DVDReadPrio(file->getFileInfo(), aligned_buf, 32, 0, 2) >= 0) {
                break;
            }
            if (JKRDvdRipper::errorRetry == false) {
                return nullptr;
            }

            VIWaitForRetrace();
        }

        fileCompressMode = JKRCheckCompressed(aligned_buf);
        finalSize = JKRDecompExpandSize(aligned_buf);
    }

    if (compressMode != nullptr) {
        *compressMode = fileCompressMode;
    }

    if (expandSwitch == EXPAND_SWITCH_DECOMPRESS && fileCompressMode != JKRDecomp::NONE) {
        if (maxDest != 0 && finalSize > maxDest) {
            finalSize = maxDest;
        }

        if (buf == nullptr) {
            buf = (u8*)JKRAllocFromHeap(heap, finalSize, allocDir == ALLOC_DIR_TOP ? 32 : -32);
            allocated = true;
        }

        if (buf == nullptr) {
            return nullptr;
        }

        if (fileCompressMode == JKRDecomp::SZP) {
            mem = (u8*)JKRAllocFromHeap(heap, fileSize, 32);
            if (mem == nullptr && allocated == true) {
                JKRFree(buf);
                return nullptr;
            }
        }
    } else {
        if (buf == nullptr) {
            buf = (u8*)JKRAllocFromHeap(heap, fileSize - offset, allocDir == ALLOC_DIR_TOP ? 32 : -32);
            allocated = true;
        }

        if (buf == nullptr) {
            return nullptr;
        }
    }

    if (fileCompressMode == JKRDecomp::NONE) {
        JKRDecomp::CompressionMode subCompressMode = JKRDecomp::NONE;

        if (offset != 0) {
            u8 buffer[64];
#ifdef TARGET_PC
            u8* aligned_buf = (u8*)ALIGN_NEXT((uintptr_t)buffer, 32);
#else
            u8* aligned_buf = (u8*)ALIGN_NEXT((u32)buffer, 32);
#endif
            while (true) {
                if (DVDReadPrio(file->getFileInfo(), aligned_buf, 32, offset, 2) >= 0) {
                    break;
                }

                if (JKRDvdRipper::errorRetry == false) {
                    return nullptr;
                }

                VIWaitForRetrace();
            }

            subCompressMode = JKRCheckCompressed(aligned_buf);
        }

        if (subCompressMode == JKRDecomp::NONE || expandSwitch == EXPAND_SWITCH_NONE ||
            expandSwitch == EXPAND_SWITCH_DEFAULT) {
            s32 readSize = fileSize - offset;
            if (maxDest != 0 && maxDest < readSize) {
                readSize = maxDest;
            }

            while (true) {
                if (DVDReadPrio(file->getFileInfo(), buf, readSize, offset, 2) >= 0) {
                    break;
                }

                if (JKRDvdRipper::errorRetry == false) {
                    return nullptr;
                }

                VIWaitForRetrace();
            }
            return buf;
        }

        if (subCompressMode == JKRDecomp::SZS) {
            JKRDecompressFromDVD(file, buf, fileSize, maxDest, 0, offset);
        } else {
            JPANIC(297, "Sorry, not prepared for SZP resource\n");
        }
    }

    if (fileCompressMode == JKRDecomp::SZP) {
        if (offset != 0) {
            JPANIC(306, ":::Not support SZP with offset read");
        }

        /* Looks like a bug here */
#ifndef FIXES
        if (DVDReadPrio(file->getFileInfo(), mem, fileSize, 0, 2) < 0) {
            if (JKRDvdRipper::errorRetry == false) {
                VIWaitForRetrace();
            }

            JKRFree(mem);
            return nullptr;
        } else {
            JKRDecompress(mem, buf, finalSize, offset);
            JKRFree(mem);
            return buf;
        }
#else
        while (DVDReadPrio(file->getFileInfo(), mem, fileSize, 0, 2) < 0) {
            if (JKRDvdRipper::errorRetry == false) {
                if (allocated) {
                    JKRFree(buf);
                }

                JKRFree(mem);
                return nullptr;
            }

            VIWaitForRetrace();
        }

        JKRDecompress(mem, buf, finalSize, 0);
        JKRFree(mem);
#endif
    } else if (fileCompressMode == JKRDecomp::SZS) {
        JKRDecompressFromDVD(file, buf, fileSize, finalSize, offset, 0);
        return buf;
    } else {
        if (allocated) {
            JKRFree(buf);
        }
        return nullptr;
    }

    return buf;
}

static u8* szpBuf;
static u8* szpEnd;
static u8* refBuf;
static u8* refEnd;
static u8* refCurrent;

static u32 srcOffset;
static u32 transLeft;
static u8* srcLimit;
static JKRDvdFile* srcFile;
static u32 fileOffset;
static u32 readCount;
static u32 maxDest;

int JKRDecompressFromDVD(JKRDvdFile* _srcFile, void* buf, u32 size, u32 _maxDest, u32 _fileOffset, u32 _srcOffset) {
    int res = 0;

    szpBuf = (u8*)JKRAllocFromSysHeap(SZP_BUFFERSIZE, -32);
    szpEnd = szpBuf + SZP_BUFFERSIZE;

    if (_fileOffset != 0) {
        refBuf = (u8*)JKRAllocFromSysHeap(REF_BUFFERSIZE, -4);
        refEnd = refBuf + REF_BUFFERSIZE;
        refCurrent = refBuf;
    } else {
        refBuf = nullptr;
    }

    srcFile = _srcFile;
    srcOffset = _srcOffset;
    transLeft = size - _srcOffset;
    fileOffset = _fileOffset;
    readCount = 0;
    maxDest = _maxDest;

    u8* src = firstSrcData();
    if (src != nullptr) {
        res = decompSZS_subroutine(src, (u8*)buf);
    }

    JKRFree(szpBuf);

    if (refBuf != nullptr) {
        JKRFree(refBuf);
    }

    return res;
}

static int decompSZS_subroutine(u8* src, u8* dest) {
    u8* endPtr;
    s32 validBitCount = 0;
    s32 currCodeByte = 0;
    u32 ts = 0;

    if ((s32)src[0] != 'Y' || (s32)src[1] != 'a' || (s32)src[2] != 'z' || (s32)src[3] != '0') {
        return -1;
    }

    SZPHeader* header = (SZPHeader*)src;
    endPtr = dest + (header->decompSize - fileOffset);
    if (endPtr > dest + maxDest) {
        endPtr = dest + maxDest;
    }

    src += 0x10;
    do {
        if (validBitCount == 0) {
            if ((src > srcLimit) && transLeft) {
                src = nextSrcData(src);
                if (!src) {
                    return -1;
                }
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
                    ts++;
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
                ts++;
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
                        ts++;
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
                    ts++;
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
    u32 size = (szpEnd - szpBuf);
    u32 transSize = MIN(transLeft, size);

    while (true) {
        if (DVDReadPrio(srcFile->getFileInfo(), buf, transSize, srcOffset, 2) < 0) {
            if (JKRDvdRipper::errorRetry == false) {
                return nullptr;
            }
            VIWaitForRetrace();
        } else {
            srcOffset += transSize;
            transLeft -= transSize;
            return buf;
        }
    }
}

static u8* nextSrcData(u8* nowData) {
    u32 size = (szpEnd - nowData);
    u8* dst;
    if (JKR_ISNOTALIGNED32(size)) {
        dst = szpBuf + 32 - (size & 31);
    } else {
        dst = szpBuf;
    }

    memcpy(dst, nowData, size);

    u32 n_size = (szpEnd - (dst + size));
    if (n_size > transLeft) {
        n_size = transLeft;
    }

    while (true) {
        if (DVDReadPrio(srcFile->getFileInfo(), (dst + size), n_size, srcOffset, 2) >= 0) {
            break;
        }
        // Oopsies, forgot to call the function
#ifndef FIXES
        if (JKRDvdRipper::isErrorRetry == false) {
            return nullptr;
        }
#else
        if (JKRDvdRipper::isErrorRetry() == false) {
            return nullptr;
        }
#endif

        VIWaitForRetrace();
    }

    srcOffset += n_size;
    transLeft -= n_size;

    if (transLeft == 0) {
        srcLimit = (dst + size) + n_size;
    }

    return dst;
}
