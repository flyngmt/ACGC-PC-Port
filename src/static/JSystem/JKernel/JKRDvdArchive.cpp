#include <dolphin/os/OSCache.h>
#include <string.h>

#include "JSystem/JKernel/JKRArchive.h"
#include "JSystem/JKernel/JKRDecomp.h"
#include "JSystem/JKernel/JKRDvdAramRipper.h"
#include "JSystem/JKernel/JKRDvdRipper.h"
#include "JSystem/JSystem.h"
#include "JSystem/JUtility/JUTAssertion.h"

#ifdef TARGET_PC
#include <stdlib.h>
#endif

JKRDvdArchive::JKRDvdArchive() : JKRArchive() {
}

JKRDvdArchive::JKRDvdArchive(s32 entryNum, EMountDirection mountDirection) : JKRArchive(entryNum, MOUNT_DVD) {
    mMountDirection = mountDirection;
    if (!open(entryNum)) {
        return;
    } else {
        mVolumeType = 'RARC';
        mVolumeName = &mStrTable[mDirectories->mOffset];
        sVolumeList.prepend(&mFileLoaderLink);
        mIsMounted = true;
    }
}

JKRDvdArchive::~JKRDvdArchive() {
    if (mIsMounted == true) {
        if (mArcInfoBlock) {
            SDIFileEntry* fileEntries = mFileEntries;
            for (int i = 0; i < mArcInfoBlock->num_file_entries; i++) {
                if (getFileEntryData(fileEntries) != nullptr) {
                    JKRFreeToHeap(mHeap, getFileEntryData(fileEntries));
                }
                fileEntries++;
            }
            JKRFreeToHeap(mHeap, mArcInfoBlock);
        }

#ifdef TARGET_PC
        if (mFileEntryDataPtrs) {
            free(mFileEntryDataPtrs);
            mFileEntryDataPtrs = nullptr;
        }
#endif

        if (mDvdFile) {
            delete mDvdFile;
        }

        sVolumeList.remove(&mFileLoaderLink);
        mIsMounted = false;
    }
}

#if DEBUG
CW_FORCE_STRINGS(JKRDvdArchive_cpp, __FILE__, "isMounted()", "mMountCount == 1")
#endif

bool JKRDvdArchive::open(s32 entryNum) {
    mArcInfoBlock = nullptr;
    _60 = 0;
    mDirectories = nullptr;
    mFileEntries = nullptr;
    mStrTable = nullptr;
#ifdef TARGET_PC
    mFileEntryDataPtrs = nullptr;
#endif

    mDvdFile = new (JKRGetSystemHeap(), 0) JKRDvdFile(entryNum);
    if (mDvdFile == nullptr) {
        mMountMode = 0;
        return 0;
    }
    SDIFileEntry* mem = (SDIFileEntry*)JKRAllocFromSysHeap(32, 32); // NOTE: unconfirmed if this struct was used here
    if (mem == nullptr) {
        mMountMode = 0;
    } else {
        JKRDvdToMainRam(entryNum, (u8*)mem, EXPAND_SWITCH_DECOMPRESS, 32, nullptr, JKRDvdRipper::ALLOC_DIR_TOP, 0,
                        &mCompression);
        int alignment = mMountDirection == MOUNT_DIRECTION_HEAD ? 32 : -32;

        mArcInfoBlock = (SArcDataInfo*)JKRAllocFromHeap(mHeap, mem->mSize, alignment);
        if (mArcInfoBlock == nullptr) {
            mMountMode = 0;
        } else {
            JKRDvdToMainRam(entryNum, (u8*)mArcInfoBlock, EXPAND_SWITCH_DECOMPRESS, mem->mSize, nullptr,
                            JKRDvdRipper::ALLOC_DIR_TOP, 32, nullptr);

            mDirectories = (SDIDirEntry*)((u8*)mArcInfoBlock + mArcInfoBlock->node_offset);
            mFileEntries = (SDIFileEntry*)((u8*)mArcInfoBlock + mArcInfoBlock->file_entry_offset);
            mStrTable = (const char*)((u8*)mArcInfoBlock + mArcInfoBlock->string_table_offset);
#ifdef TARGET_PC
            mFileEntryDataPtrs = (void**)calloc(mArcInfoBlock->num_file_entries > 0 ? mArcInfoBlock->num_file_entries : 1, sizeof(void*));
#endif
            _60 = mem->mDataOffset + mem->mSize; // End of data offset?
        }
    }
cleanup:
    if (mem != nullptr) {
        JKRFreeToSysHeap(mem);
    }
    if (mMountMode == 0) {
        JREPORTF(":::Cannot alloc memory [%s][%d]\n", __FILE__, 397); // Macro?
        if (mDvdFile != nullptr) {
            delete mDvdFile;
        }
    }
    return mMountMode != 0;
}

void* JKRDvdArchive::fetchResource(SDIFileEntry* fileEntry, u32* pSize) {
    JUT_ASSERT(isMounted());

    u32 sizeRef;
    u8* data;

    if (getFileEntryData(fileEntry) == nullptr) {
        int compression = JKRConvertAttrToCompressionType(fileEntry->mFlag >> 0x18);
        u32 size = fetchResource_subroutine(mEntryNum, _60 + fileEntry->mDataOffset, fileEntry->mSize, mHeap,
                                            (int)compression, mCompression, &data);

        if (pSize)
            *pSize = size;

        setFileEntryData(fileEntry, data);
    } else if (pSize) {
        *pSize = fileEntry->mSize;
    }

    return getFileEntryData(fileEntry);
}

void* JKRDvdArchive::fetchResource(void* data, u32 compressedSize, SDIFileEntry* fileEntry, u32* pSize,
                                   JKRExpandSwitch expandSwitch) {
    JUT_ASSERT(isMounted());

    u32 fileSize = compressedSize & -32;
    u32 alignedSize = ALIGN_NEXT(fileEntry->mSize, 32);

    if (alignedSize > fileSize) {
        alignedSize = fileSize;
    }

    if (getFileEntryData(fileEntry) == nullptr) {
        int compression = JKRConvertAttrToCompressionType(fileEntry->mFlag >> 0x18);
        if (expandSwitch != EXPAND_SWITCH_DECOMPRESS)
            compression = 0;
        alignedSize = fetchResource_subroutine(mEntryNum, _60 + fileEntry->mDataOffset, fileEntry->mSize, (u8*)data,
                                               fileSize, compression, mCompression);
    } else {
        JKRHeap::copyMemory(data, getFileEntryData(fileEntry), alignedSize);
    }

    if (pSize) {
        *pSize = alignedSize;
    }
    return data;
}

u32 JKRDvdArchive::fetchResource_subroutine(s32 entryNum, u32 offset, u32 size, u8* data, u32 expandSize,
                                            int fileCompression, int archiveCompression) {
    u32 prevAlignedSize, alignedSize;

    alignedSize = ALIGN_NEXT(size, 32);
    prevAlignedSize = ALIGN_PREV(expandSize, 32);
    switch (archiveCompression) {
        case JKRCOMPRESSION_NONE: {
            switch (fileCompression) {
                case JKRCOMPRESSION_NONE:

                    if (alignedSize > prevAlignedSize) {
                        alignedSize = prevAlignedSize;
                    }
                    JKRDvdRipper::loadToMainRAM(entryNum, data, EXPAND_SWITCH_DEFAULT, alignedSize, nullptr,
                                                JKRDvdRipper::ALLOC_DIR_TOP, offset, nullptr);
                    return alignedSize;

                case JKRCOMPRESSION_YAY0:
                case JKRCOMPRESSION_YAZ0:
                    u8* header = (u8*)JKRAllocFromSysHeap(0x20, 0x20);
                    JKRDvdRipper::loadToMainRAM(entryNum, header, EXPAND_SWITCH_NONE, 0x20, nullptr,
                                                JKRDvdRipper::ALLOC_DIR_TOP, offset, nullptr);
                    u32 expandFileSize = JKRDecompExpandSize(header);
                    JKRFreeToSysHeap(header);
                    alignedSize = ALIGN_NEXT(expandFileSize, 32);
                    if (alignedSize > prevAlignedSize) {
                        alignedSize = prevAlignedSize;
                    }
                    JKRDvdRipper::loadToMainRAM(entryNum, data, EXPAND_SWITCH_DECOMPRESS, alignedSize, nullptr,
                                                JKRDvdRipper::ALLOC_DIR_TOP, offset, nullptr);
                    return expandFileSize;
            }
        }
        case JKRCOMPRESSION_YAZ0: {
            if (size > prevAlignedSize) {
                size = prevAlignedSize;
            }
            JKRDvdRipper::loadToMainRAM(entryNum, data, EXPAND_SWITCH_DECOMPRESS, size, nullptr,
                                        JKRDvdRipper::ALLOC_DIR_TOP, offset, nullptr);
            return size;
        }

        case JKRCOMPRESSION_YAY0: {
            JPANIC(537, "Sorry, not prepared for SZP archive.\n");
            return 0;
        }

        default: {
            JPANIC(546, ":::??? bad sequence\n");
        }
    }
    return 0;
}

u32 JKRDvdArchive::fetchResource_subroutine(s32 entryNum, u32 offset, u32 size, JKRHeap* heap, int fileCompression,
                                            int archiveCompression, u8** pBuf) {
    u32 alignedSize = ALIGN_NEXT(size, 32);

    u8* buffer;
    switch (archiveCompression) {
        case JKRCOMPRESSION_NONE: {
            switch (fileCompression) {
                case JKRCOMPRESSION_NONE:
                    buffer = (u8*)JKRAllocFromHeap(heap, alignedSize, 32);
                    JUT_ASSERT(buffer != 0);

                    JKRDvdToMainRam(entryNum, buffer, EXPAND_SWITCH_DEFAULT, alignedSize, nullptr,
                                    JKRDvdRipper::ALLOC_DIR_TOP, offset, nullptr);
                    *pBuf = buffer;
                    return alignedSize;

                case JKRCOMPRESSION_YAY0:
                case JKRCOMPRESSION_YAZ0:
                    u8* header = (u8*)JKRAllocFromHeap(heap, 0x20, 0x20);
                    JKRDvdToMainRam(entryNum, header, EXPAND_SWITCH_NONE, 0x20, nullptr, JKRDvdRipper::ALLOC_DIR_TOP,
                                    offset, nullptr);

                    alignedSize = JKRDecompExpandSize(header);
                    JKRFreeToHeap(heap, header);
                    buffer = (u8*)JKRAllocFromHeap(heap, alignedSize, 0x20);
                    JUT_ASSERT(buffer);

                    JKRDvdToMainRam(entryNum, buffer, EXPAND_SWITCH_DECOMPRESS, alignedSize, nullptr,
                                    JKRDvdRipper::ALLOC_DIR_TOP, offset, nullptr);
                    *pBuf = buffer;
                    return alignedSize;
            }
        }
        case JKRCOMPRESSION_YAZ0: {
            buffer = (u8*)JKRAllocFromHeap(heap, alignedSize, 32);
            JUT_ASSERT(buffer);
            JKRDvdToMainRam(entryNum, buffer, EXPAND_SWITCH_DECOMPRESS, size, nullptr, JKRDvdRipper::ALLOC_DIR_TOP,
                            offset, nullptr);
            *pBuf = buffer;
            return alignedSize;
        }

        case JKRCOMPRESSION_YAY0: {
            JPANIC(612, "Sorry, not prepared for SZP archive.\n");
            return 0;
        }

        default: {
            JPANIC(617, ":::??? bad sequence\n");
        }
    }
    return 0;
}
