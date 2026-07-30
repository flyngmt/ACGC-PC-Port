#include <string.h>
#include <dolphin/os/OSCache.h>

#include "JSystem/JSystem.h"
#include "JSystem/JKernel/JKRArchive.h"
#include "JSystem/JKernel/JKRDecomp.h"
#include "JSystem/JKernel/JKRDvdRipper.h"
#include "JSystem/JUtility/JUTAssertion.h"

JKRMemArchive::JKRMemArchive() : JKRArchive() {
}

JKRMemArchive::JKRMemArchive(s32 entryNum, EMountDirection mountDirection) : JKRArchive(entryNum, MOUNT_MEM) {
    mIsMounted = false;
    mMountDirection = mountDirection;
    if (!open(entryNum, mMountDirection)) {
        return;
    } else {
        mVolumeType = 'RARC';
        mVolumeName = &mStrTable[mDirectories->mOffset];
        sVolumeList.prepend(&mFileLoaderLink);
        mIsMounted = true;
    }
}

JKRMemArchive::JKRMemArchive(void* mem, u32 size, JKRMemBreakFlag breakFlag) : JKRArchive((s32)(uintptr_t)mem, MOUNT_MEM) {
    mIsMounted = false;
    if (!open(mem, size, breakFlag)) {
        return;
    } else {
        mVolumeType = 'RARC';
        mVolumeName = &mStrTable[mDirectories->mOffset];
        sVolumeList.prepend(&mFileLoaderLink);
        mIsMounted = true;
    }
}

JKRMemArchive::~JKRMemArchive() {
    if (mIsMounted == true) {
#ifdef TARGET_PC
        if (mArcInfoBlock != nullptr) {
            JKRFreeToHeap(mHeap, mArcInfoBlock);
            mArcInfoBlock = nullptr;
        }
#endif
        if (mIsOpen && mArcHeader)
            JKRFreeToHeap(mHeap, mArcHeader);

        sVolumeList.remove(&mFileLoaderLink);
        mIsMounted = false;
    }
}

#if DEBUG // function is needed to generate certain strings first, however this is not what the original function looks
          // like
void JKRMemArchive::fixedInit(s32) {
    JUT_ASSERT(isMounted());
    JUT_PANIC("mMountCount == 1"); // some member is called mMountCount, if there's a game with this assert, fix
#ifdef TARGET_PC
    JUT_ASSERT(read_big_endian_u32(mArcHeader) == 'RARC');
#else
    JUT_ASSERT(mArcHeader->signature == 'RARC');
#endif
}
#endif

bool JKRMemArchive::open(s32 entryNum, JKRArchive::EMountDirection mountDirection) {
    mArcHeader = nullptr;
    mArcInfoBlock = nullptr;
    mArchiveData = nullptr;
    mDirectories = nullptr;
    mFileEntries = nullptr;
    mStrTable = nullptr;
    mIsOpen = false;
    mMountDirection = mountDirection;

    if (mMountDirection == JKRArchive::MOUNT_DIRECTION_HEAD) {
        u32 loadedSize;
        mArcHeader = (SArcHeader*)JKRDvdRipper::loadToMainRAM(entryNum, nullptr, EXPAND_SWITCH_DECOMPRESS, 0, mHeap,
                                                              JKRDvdRipper::ALLOC_DIR_TOP, 0, (int*)&mCompression);

    } else {
        u32 loadedSize;
        mArcHeader = (SArcHeader*)JKRDvdRipper::loadToMainRAM(entryNum, nullptr, EXPAND_SWITCH_DECOMPRESS, 0, mHeap,
                                                              JKRDvdRipper::ALLOC_DIR_BOTTOM, 0, (int*)&mCompression);
    }

    if (!mArcHeader) {
#ifdef TARGET_PC
        OSReport("[PC] Could not load entry %d into memory RARC (heap=%p)\n", entryNum, mHeap);
#endif
        mMountMode = UNKNOWN_MOUNT_MODE;
    } else {
#ifdef TARGET_PC
        SArcHeader header;
        if (!decodeBigEndianRarcHeader(mArcHeader, 32, &header)) {
            OSReport("[PC] Invalid memory RARC header\n");
            mMountMode = UNKNOWN_MOUNT_MODE;
        } else {
            const u8* rawInfo = (const u8*)mArcHeader + header.header_length;
            if (!convertBigEndianRarcMetadata(rawInfo, header.file_data_offset,
                                              header.file_data_length, nullptr, 0, nullptr,
                                              mMountDirection == MOUNT_DIRECTION_HEAD ? 32 : -32)) {
                OSReport("[PC] Invalid memory RARC metadata\n");
                mMountMode = UNKNOWN_MOUNT_MODE;
            } else {
                mArchiveData = (u8*)mArcHeader + header.header_length + header.file_data_offset;
                mIsOpen = true;
            }
        }

        if (mMountMode == UNKNOWN_MOUNT_MODE) {
            if (mArcInfoBlock != nullptr) {
                JKRFreeToHeap(mHeap, mArcInfoBlock);
                mArcInfoBlock = nullptr;
            }
            JKRFreeToHeap(mHeap, mArcHeader);
            mArcHeader = nullptr;
        }
#else
        JUT_ASSERT(mArcHeader->signature == 'RARC');
        mArcInfoBlock = (SArcDataInfo*)((u8*)mArcHeader + mArcHeader->header_length);
        mDirectories = (SDIDirEntry*)((u8*)&mArcInfoBlock->num_nodes + mArcInfoBlock->node_offset);
        mFileEntries = (SDIFileEntry*)((u8*)&mArcInfoBlock->num_nodes + mArcInfoBlock->file_entry_offset);
        mStrTable = (char*)((u8*)&mArcInfoBlock->num_nodes + mArcInfoBlock->string_table_offset);

        mArchiveData = (u8*)((uintptr_t)mArcHeader + mArcHeader->header_length + mArcHeader->file_data_offset);
        mIsOpen = true;
#endif
    }
#if DEBUG
    // OS Assert?
    if (mMountMode == UNKNOWN_MOUNT_MODE) {
        OSReport(":::Cannot alloc memory [%s][%d]\n", __FILE__, 460);
    }
#endif
    return (mMountMode == UNKNOWN_MOUNT_MODE) ? false : true;
}

bool JKRMemArchive::open(void* buffer, u32 bufferSize, JKRMemBreakFlag flag) {
    mArcHeader = (SArcHeader*)buffer;
#ifdef TARGET_PC
    SArcHeader header;
    mArcInfoBlock = nullptr;
    mDirectories = nullptr;
    mFileEntries = nullptr;
    mStrTable = nullptr;
    mHeap = JKRHeap::findFromRoot(buffer);
    if (mHeap == nullptr) {
        mHeap = JKRGetCurrentHeap();
    }
    if (!decodeBigEndianRarcHeader(buffer, bufferSize == 0xFFFF ? 32 : bufferSize, &header) ||
        (bufferSize != 0xFFFF && bufferSize < header.file_length) ||
        !convertBigEndianRarcMetadata((u8*)buffer + header.header_length,
                                      header.file_data_offset, header.file_data_length,
                                      nullptr, 0, nullptr, 32)) {
        OSReport("[PC] Invalid buffer-backed RARC\n");
        mMountMode = UNKNOWN_MOUNT_MODE;
        return false;
    }
    mArchiveData = (u8*)buffer + header.header_length + header.file_data_offset;
#else
    JUT_ASSERT(mArcHeader->signature == 'RARC');
    mArcInfoBlock = (SArcDataInfo*)((u8*)mArcHeader + mArcHeader->header_length);
    mDirectories = (SDIDirEntry*)((u8*)&mArcInfoBlock->num_nodes + mArcInfoBlock->node_offset);
    mFileEntries = (SDIFileEntry*)((u8*)&mArcInfoBlock->num_nodes + mArcInfoBlock->file_entry_offset);
    mStrTable = (char*)((u8*)&mArcInfoBlock->num_nodes + mArcInfoBlock->string_table_offset);
    mArchiveData = (u8*)(((uintptr_t)mArcHeader + mArcHeader->header_length) + mArcHeader->file_data_offset);
    mHeap = JKRHeap::findFromRoot(buffer);
#endif
    mIsOpen = (flag == MBF_1) ? true : false; // mIsOpen might be u8
    mCompression = JKRCOMPRESSION_NONE;
    return true;
}

void* JKRMemArchive::fetchResource(SDIFileEntry* fileEntry, u32* resourceSize) {
    JUT_ASSERT(isMounted())

    if (!fileEntry->mData)
        fileEntry->mData = mArchiveData + fileEntry->mDataOffset;

    if (resourceSize)
        *resourceSize = fileEntry->mSize;

    return fileEntry->mData;
}

void* JKRMemArchive::fetchResource(void* buffer, u32 bufferSize, SDIFileEntry* fileEntry, u32* resourceSize,
                                   JKRExpandSwitch expandSwitch) {
    JUT_ASSERT(isMounted())

    bufferSize = (bufferSize & -32);
    u32 srcLength = ALIGN_NEXT(fileEntry->mSize, 32);
    if (srcLength > bufferSize) {
        srcLength = bufferSize;
    }

    if (fileEntry->mData != nullptr) {
        JKRHeap::copyMemory(buffer, fileEntry->mData, srcLength);
    } else {
        int compression = JKRConvertAttrToCompressionType(fileEntry->getAttr());
        if (expandSwitch != EXPAND_SWITCH_DECOMPRESS)
            compression = JKRCOMPRESSION_NONE;

        void* data = mArchiveData + fileEntry->mDataOffset;
        srcLength = fetchResource_subroutine((u8*)data, srcLength, (u8*)buffer, bufferSize, compression);
    }

    if (resourceSize) {
        *resourceSize = srcLength;
    }

    return buffer;
}

void JKRMemArchive::removeResourceAll(void) {
    JUT_ASSERT(isMounted());

    if (mArcInfoBlock == nullptr)
        return;
    if (mMountMode == MOUNT_MEM)
        return;

    // !@bug: looping over file entries without incrementing the fileEntry pointer. Thus, only the
    // first fileEntry will clear/remove the resource data.
    SDIFileEntry* fileEntry = mFileEntries;
    for (int i = 0; i < mArcInfoBlock->num_file_entries; i++) {
        if (fileEntry->mData) {
            fileEntry->mData = nullptr;
        }
    }
}

bool JKRMemArchive::removeResource(void* resource) {
    JUT_ASSERT(isMounted());

    SDIFileEntry* fileEntry = findPtrResource(resource);
    if (!fileEntry)
        return false;

    fileEntry->mData = nullptr;
    return true;
}

u32 JKRMemArchive::fetchResource_subroutine(u8* src, u32 srcLength, u8* dst, u32 dstLength, int compression) {
    u32 alignedDst = dstLength & -32;
    u32 alignedSrc = ALIGN_NEXT(srcLength, 32);
    switch (compression) {
        case JKRCOMPRESSION_NONE:
            if (alignedSrc > alignedDst)
                alignedSrc = alignedDst;

            JKRHeap::copyMemory(dst, src, alignedSrc);
            return alignedSrc;

        case JKRCOMPRESSION_YAY0:
        case JKRCOMPRESSION_YAZ0: {
            u32 expandSize = JKRDecompExpandSize(src);

            if (expandSize > alignedDst) {
                expandSize = alignedDst;
            }

            JKRDecompress(src, dst, expandSize, 0);
            return expandSize;
        }
        default: {
            JPANIC(709, ":::??? bad sequence\n");
            return 0;
        }
    }

    return alignedSrc;
}
