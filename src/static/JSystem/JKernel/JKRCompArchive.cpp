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

JKRCompArchive::JKRCompArchive(s32 entryNum, EMountDirection mountDirection) : JKRArchive(entryNum, MOUNT_COMP) {
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

#if DEBUG
void stringGen() {
    JUT_PANIC("isMounted()");
    JUT_PANIC("mMountCount == 1");
}
#endif

JKRCompArchive::~JKRCompArchive() {
    if (mArcInfoBlock) {
        SDIFileEntry* fileEntries = mFileEntries;
        for (int i = 0; i < mArcInfoBlock->num_file_entries; i++) {
            u32 flag = (fileEntries->mFlag >> 24);
            if ((flag & 16) == 0 && getFileEntryData(fileEntries)) {
                JKRFreeToHeap(mHeap, getFileEntryData(fileEntries));
            }
            fileEntries++;
        }
        JKRFreeToHeap(mHeap, mArcInfoBlock);
        mArcInfoBlock = nullptr;
    }

#ifdef TARGET_PC
    if (mFileEntryDataPtrs) {
        free(mFileEntryDataPtrs);
        mFileEntryDataPtrs = nullptr;
    }
#endif

    if (mAramPart) {
        delete mAramPart;
    }
    if (mDvdFile) {
        delete mDvdFile;
    }

    sVolumeList.remove(&mFileLoaderLink);
    mIsMounted = false;
}

bool JKRCompArchive::open(s32 entryNum) {
    mArcInfoBlock = nullptr;
    _60 = 0;
    mAramPart = nullptr;
    _68 = 0;
    mSizeOfMemPart = 0;
    mSizeOfAramPart = 0;
    _78 = 0;
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
    SArcHeader* arcHeader =
        (SArcHeader*)JKRAllocFromSysHeap(sizeof(SArcHeader), -32); // NOTE: unconfirmed if this struct is used
    if (arcHeader == nullptr) {
        mMountMode = 0;
    } else {
        int alignment;

        JKRDvdToMainRam(entryNum, (u8*)arcHeader, EXPAND_SWITCH_DECOMPRESS, 32, nullptr, JKRDvdRipper::ALLOC_DIR_TOP, 0,
                        &mCompression);

        mSizeOfMemPart = arcHeader->_14;
        mSizeOfAramPart = arcHeader->_18;
        JUT_ASSERT((mSizeOfMemPart & 0x1f) == 0);
        JUT_ASSERT((mSizeOfAramPart & 0x1f) == 0);

        switch (mCompression) {
            case JKRCOMPRESSION_NONE:
            case JKRCOMPRESSION_YAZ0:
                alignment = mMountDirection == 1 ? 32 : -32;
                mArcInfoBlock =
                    (SArcDataInfo*)JKRAllocFromHeap(mHeap, arcHeader->file_data_offset + mSizeOfMemPart, alignment);
                if (mArcInfoBlock == nullptr) {
                    mMountMode = 0;
                } else {
                    JKRDvdToMainRam(entryNum, (u8*)mArcInfoBlock, EXPAND_SWITCH_DECOMPRESS,
                                    (u32)arcHeader->file_data_offset + mSizeOfMemPart, nullptr,
                                    JKRDvdRipper::ALLOC_DIR_TOP, 0x20, nullptr);
#ifdef TARGET_PC
                    _60 = (uintptr_t)mArcInfoBlock + arcHeader->file_data_offset;
#else
                    _60 = (u32)mArcInfoBlock + arcHeader->file_data_offset;
#endif

                    if (mSizeOfAramPart != 0) {
                        mAramPart = JKRAllocFromAram(mSizeOfAramPart, JKRAramHeap::Head);
                        if (mAramPart == nullptr) {
                            mMountMode = 0;
                            break;
                        }

                        JKRDvdToAram(entryNum, mAramPart->getAddress(), EXPAND_SWITCH_DECOMPRESS,
                                     arcHeader->header_length + arcHeader->file_data_offset + mSizeOfMemPart, 0);
                    }

#ifdef TARGET_PC
                    mDirectories = (SDIDirEntry*)((uintptr_t)mArcInfoBlock + mArcInfoBlock->node_offset);
                    mFileEntries = (SDIFileEntry*)((uintptr_t)mArcInfoBlock + mArcInfoBlock->file_entry_offset);
                    mStrTable = (const char*)((uintptr_t)mArcInfoBlock + mArcInfoBlock->string_table_offset);
                    mFileEntryDataPtrs = (void**)calloc(mArcInfoBlock->num_file_entries > 0 ? mArcInfoBlock->num_file_entries : 1, sizeof(void*));
#else
                    mDirectories = (SDIDirEntry*)((u32)mArcInfoBlock + mArcInfoBlock->node_offset);
                    mFileEntries = (SDIFileEntry*)((u32)mArcInfoBlock + mArcInfoBlock->file_entry_offset);
                    mStrTable = (const char*)((u32)mArcInfoBlock + mArcInfoBlock->string_table_offset);
#endif
                    _68 = arcHeader->header_length + arcHeader->file_data_offset;
                }
                break;

            case JKRCOMPRESSION_YAY0:
                u32 alignedSize = ALIGN_NEXT(mDvdFile->getFileSize(), 32);
                alignment = ((mMountDirection == 1) ? 32 : -32);
                u8* buf = (u8*)JKRAllocFromSysHeap(alignedSize, -alignment);

                if (buf == nullptr) {
                    mMountMode = 0;
                } else {
                    JKRDvdToMainRam(entryNum, buf, EXPAND_SWITCH_NONE, alignedSize, nullptr,
                                    JKRDvdRipper::ALLOC_DIR_TOP, 0, nullptr);
                    u32 expandSize = ALIGN_NEXT(JKRDecompExpandSize(buf), 32);
                    u8* mem = (u8*)JKRAllocFromHeap(mHeap, expandSize, -alignment);

                    if (mem == nullptr) {
                        mMountMode = 0;
                    } else {
                        arcHeader = (SArcHeader*)mem;
                        JKRDecompress((u8*)buf, (u8*)mem, expandSize, 0);
                        JKRFreeToSysHeap(buf);

                        mArcInfoBlock = (SArcDataInfo*)JKRAllocFromHeap(
                            mHeap, arcHeader->file_data_offset + mSizeOfMemPart, alignment);
                        if (mArcInfoBlock == nullptr) {
                            mMountMode = 0;
                        } else {
                            // arcHeader + 1 should lead to 0x20, which is the data after the
                            // header
                            JKRHeap::copyMemory((u8*)mArcInfoBlock, arcHeader + 1,
                                                (arcHeader->file_data_offset + mSizeOfMemPart));
#ifdef TARGET_PC
                            _60 = (uintptr_t)mArcInfoBlock + arcHeader->file_data_offset;
#else
                            _60 = (u32)mArcInfoBlock + arcHeader->file_data_offset;
#endif
                            if (mSizeOfAramPart != 0) {
                                mAramPart = JKRAllocFromAram(mSizeOfAramPart, JKRAramHeap::Head);
                                if (mAramPart == nullptr) {
                                    mMountMode = 0;
                                } else {
                                    JKRMainRamToAram((u8*)mem + arcHeader->header_length + arcHeader->file_data_offset +
                                                         mSizeOfMemPart,
                                                     mAramPart->getAddress(), mSizeOfAramPart, EXPAND_SWITCH_DEFAULT, 0,
                                                     nullptr, -1, (u32)0);
                                }
                            }
                        }
                    }
                }
#ifdef TARGET_PC
                mDirectories = (SDIDirEntry*)((uintptr_t)mArcInfoBlock + mArcInfoBlock->node_offset);
                mFileEntries = (SDIFileEntry*)((uintptr_t)mArcInfoBlock + mArcInfoBlock->file_entry_offset);
                mStrTable = (const char*)((uintptr_t)mArcInfoBlock + mArcInfoBlock->string_table_offset);
                mFileEntryDataPtrs = (void**)calloc(mArcInfoBlock->num_file_entries > 0 ? mArcInfoBlock->num_file_entries : 1, sizeof(void*));
#else
                mDirectories = (SDIDirEntry*)((u32)mArcInfoBlock + mArcInfoBlock->node_offset);
                mFileEntries = (SDIFileEntry*)((u32)mArcInfoBlock + mArcInfoBlock->file_entry_offset);
                mStrTable = (const char*)((u32)mArcInfoBlock + mArcInfoBlock->string_table_offset);
#endif
                _68 = arcHeader->header_length + arcHeader->file_data_offset;
                break;
        }
    }

    if (arcHeader) {
        JKRFreeToHeap(mHeap, arcHeader);
    }
    if (mMountMode == 0) {
        JREPORTF(0, ":::[%s: %d] Cannot alloc memory in mounting CompArchive\n", __FILE__, 567); // Macro?
        if (mDvdFile) {
            delete mDvdFile;
            mDvdFile = nullptr;
        }
    }
    return mMountMode != 0;
}

void* JKRCompArchive::fetchResource(SDIFileEntry* fileEntry, u32* pSize) {
    JUT_ASSERT(isMounted());

    u32 ptrSize;

    if (getFileEntryData(fileEntry) == nullptr) {
        u32 flag = fileEntry->mFlag >> 0x18;
        if (flag & 0x10) {
            setFileEntryData(fileEntry, (void*)(_60 + fileEntry->mDataOffset));
            if (pSize)
                *pSize = fileEntry->mSize;
        } else if (flag & 0x20) {
            u32 address = mAramPart->getAddress();
            int compression = JKRConvertAttrToCompressionType(fileEntry->mFlag >> 0x18);

            u8* data;
            u32 size = JKRAramArchive::fetchResource_subroutine(fileEntry->mDataOffset + address - mSizeOfMemPart,
                                                                fileEntry->mSize, mHeap, compression, &data);

            if (pSize)
                *pSize = size;

            setFileEntryData(fileEntry, data);

        } else if (flag & 0x40) {
            int compression = JKRConvertAttrToCompressionType(fileEntry->mFlag >> 0x18);

            u8* data;
            u32 size = JKRDvdArchive::fetchResource_subroutine(
                mEntryNum, _68 + fileEntry->mDataOffset, fileEntry->mSize, mHeap, compression, mCompression, &data);

            if (pSize)
                *pSize = size;

            setFileEntryData(fileEntry, data);
        }
    } else if (pSize) {
        *pSize = fileEntry->mSize;
    }
    return getFileEntryData(fileEntry);
}

void* JKRCompArchive::fetchResource(void* data, u32 compressedSize, SDIFileEntry* fileEntry, u32* pSize,
                                    JKRExpandSwitch expandSwitch) {
    // u32 size = 0;
    JUT_ASSERT(isMounted());

    u32 size = ALIGN_NEXT(fileEntry->mSize, 32);
    u32 expandSize = 0;

    if (size == 0)
        JPANIC(651, ":::bad resource size. size = 0\n");

    if (getFileEntryData(fileEntry)) {
        if (size > (compressedSize & ~31)) {
            size = (compressedSize & ~31);
        }

        JKRHeap::copyMemory(data, getFileEntryData(fileEntry), size);
        expandSize = size;
    } else {
        u32 fileFlag = fileEntry->mFlag >> 0x18;
        int compression = JKRConvertAttrToCompressionType(fileFlag);
        if (expandSwitch != EXPAND_SWITCH_DECOMPRESS)
            compression = 0;

        if (fileFlag & 0x10) {
            if (size > (compressedSize & ~31)) {
                size = (compressedSize & ~31);
            }

            if (FLAG_ON(fileFlag, 4)) {
                JKRHeap::copyMemory(data, (void*)(_60 + fileEntry->mDataOffset), size);
            } else {
                u8* header = (u8*)(_60 + fileEntry->mDataOffset);
                expandSize = JKRDecompExpandSize(header);
                expandSize = (expandSize > compressedSize) ? compressedSize : expandSize;
                JKRDecompress(header, (u8*)data, expandSize, 0);
            }

            expandSize = JKRMemArchive::fetchResource_subroutine((u8*)(_60 + fileEntry->mDataOffset), size, (u8*)data,
                                                                 compressedSize, compression);
        } else if (fileFlag & 0x20) {
            expandSize = JKRAramArchive::fetchResource_subroutine(fileEntry->mDataOffset + mAramPart->getAddress() -
                                                                      mSizeOfMemPart,
                                                                  size, (u8*)data, compressedSize, compression);
        } else if (fileFlag & 0x40) {
            expandSize = JKRDvdArchive::fetchResource_subroutine(mEntryNum, _68 + fileEntry->mDataOffset, size,
                                                                 (u8*)data, compressedSize, compression, mCompression);
        } else {
            JPANIC(731, ":::CompArchive: bad mode.");
        }
    }

    if (pSize) {
        *pSize = expandSize;
    }
    return data;
}

void JKRCompArchive::removeResourceAll() {
    if (mArcInfoBlock && mMountMode != MOUNT_MEM) {
        SDIFileEntry* fileEntry = mFileEntries;
        for (int i = 0; i < mArcInfoBlock->num_file_entries; i++) {
            u32 flag = fileEntry->mFlag >> 0x18;
            if (getFileEntryData(fileEntry)) {
                if ((flag & 0x10) == 0) {
                    JKRFreeToHeap(mHeap, getFileEntryData(fileEntry));
                }

                setFileEntryData(fileEntry, nullptr);
            }
        }
    }
}

bool JKRCompArchive::removeResource(void* resource) {
    SDIFileEntry* fileEntry = findPtrResource(resource);
    if (!fileEntry)
        return false;

    if (((fileEntry->mFlag >> 0x18) & 0x10) == 0) {
        JKRFreeToHeap(mHeap, resource);
    }

    setFileEntryData(fileEntry, nullptr);
    return true;
}
