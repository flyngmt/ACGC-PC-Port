#include <MSL_C/ctype.h>
#include <string.h>

#include "JSystem/JKernel/JKRArchive.h"
#include "JSystem/JKernel/JKRFileLoader.h"
#include "types.h"

u32 JKRArchive::sCurrentDirID;

JKRArchive::JKRArchive() {
    mIsMounted = false;
    mMountDirection = MOUNT_DIRECTION_HEAD;
}

JKRArchive::JKRArchive(s32 entryNum, JKRArchive::EMountMode mountMode) : JKRFileLoader() {
    mIsMounted = false;
    mMountMode = mountMode;
    mMountCount = 1;
    _54 = 1;
    mHeap = JKRHeap::findFromRoot(this);
    if (!mHeap) {
        mHeap = JKRHeap::sCurrentHeap;
    }
    mEntryNum = entryNum;
    if (sCurrentVolume == nullptr) {
        sCurrentDirID = 0;
        sCurrentVolume = this;
    }
}

JKRArchive::~JKRArchive() {
}

#ifdef TARGET_PC
bool JKRArchive::decodeBigEndianRarcHeader(const void* rawHeader, u32 rawSize, SArcHeader* header) {
    if (rawHeader == nullptr || header == nullptr || rawSize < 0x20) {
        return false;
    }

    const u8* raw = (const u8*)rawHeader;
    header->signature = read_big_endian_u32(raw + 0x00);
    header->file_length = read_big_endian_u32(raw + 0x04);
    header->header_length = read_big_endian_u32(raw + 0x08);
    header->file_data_offset = read_big_endian_u32(raw + 0x0C);
    header->file_data_length = read_big_endian_u32(raw + 0x10);
    header->_14 = read_big_endian_u32(raw + 0x14);
    header->_18 = read_big_endian_u32(raw + 0x18);
    header->_1C = read_big_endian_u32(raw + 0x1C);

    return header->signature == 'RARC' && header->header_length >= 0x20 &&
           header->file_length >= header->header_length &&
           header->file_data_offset <= header->file_length - header->header_length &&
           header->file_data_length <= header->file_length - header->header_length - header->file_data_offset;
}

bool JKRArchive::convertBigEndianRarcMetadata(const void* rawInfoPtr, u32 rawInfoSize, u32 fileDataSize,
                                              const void* memoryPart, u32 memoryPartSize,
                                              JKRArchiveDataAddress* nativeMemoryPart, int alignment) {
    if (nativeMemoryPart != nullptr) {
        *nativeMemoryPart = 0;
    }
    if (rawInfoPtr == nullptr || rawInfoSize < sizeof(SArcDataInfo) ||
        (memoryPartSize != 0 && memoryPart == nullptr)) {
        return false;
    }

    const u8* rawInfo = (const u8*)rawInfoPtr;
    const u32 numNodes = read_big_endian_u32(rawInfo + 0x00);
    const u32 rawNodeOffset = read_big_endian_u32(rawInfo + 0x04);
    const u32 numFiles = read_big_endian_u32(rawInfo + 0x08);
    const u32 rawFileOffset = read_big_endian_u32(rawInfo + 0x0C);
    const u32 stringLength = read_big_endian_u32(rawInfo + 0x10);
    const u32 rawStringOffset = read_big_endian_u32(rawInfo + 0x14);

    if (rawNodeOffset > rawInfoSize || numNodes > (rawInfoSize - rawNodeOffset) / 16 ||
        rawFileOffset > rawInfoSize || numFiles > (rawInfoSize - rawFileOffset) / 20 ||
        rawStringOffset > rawInfoSize || stringLength > rawInfoSize - rawStringOffset) {
        return false;
    }

    const size_t nativeNodeOffset = (sizeof(SArcDataInfo) + 7u) & ~size_t(7u);
    const size_t nativeFileOffset =
        (nativeNodeOffset + (size_t)numNodes * sizeof(SDIDirEntry) + 7u) & ~size_t(7u);
    const size_t nativeStringOffset = nativeFileOffset + (size_t)numFiles * sizeof(SDIFileEntry);
    const size_t nativeMemoryOffset = (nativeStringOffset + stringLength + 31u) & ~size_t(31u);
    const size_t nativeTotalSize = (nativeMemoryOffset + memoryPartSize + 31u) & ~size_t(31u);
    if (nativeNodeOffset > 0xffffffffu || nativeFileOffset > 0xffffffffu ||
        nativeStringOffset > 0xffffffffu || nativeTotalSize > 0xffffffffu) {
        return false;
    }

    SArcDataInfo* nativeInfo =
        (SArcDataInfo*)JKRAllocFromHeap(mHeap, (u32)nativeTotalSize, alignment);
    if (nativeInfo == nullptr) {
        return false;
    }
    memset(nativeInfo, 0, nativeTotalSize);

    nativeInfo->num_nodes = numNodes;
    nativeInfo->node_offset = (u32)nativeNodeOffset;
    nativeInfo->num_file_entries = numFiles;
    nativeInfo->file_entry_offset = (u32)nativeFileOffset;
    nativeInfo->string_table_length = stringLength;
    nativeInfo->string_table_offset = (u32)nativeStringOffset;
    nativeInfo->nextFreeFileID = read_big_endian_u16(rawInfo + 0x18);
    nativeInfo->isSyncIDs = rawInfo[0x1A];

    SDIDirEntry* directories = (SDIDirEntry*)((u8*)nativeInfo + nativeNodeOffset);
    SDIFileEntry* files = (SDIFileEntry*)((u8*)nativeInfo + nativeFileOffset);
    char* strings = (char*)((u8*)nativeInfo + nativeStringOffset);
    memcpy(strings, rawInfo + rawStringOffset, stringLength);

    bool valid = numNodes != 0 && stringLength != 0;
    for (u32 i = 0; valid && i < numNodes; i++) {
        const u8* raw = rawInfo + rawNodeOffset + i * 16;
        directories[i].mType = read_big_endian_u32(raw + 0x00);
        directories[i].mOffset = read_big_endian_u32(raw + 0x04);
        directories[i]._08 = read_big_endian_u16(raw + 0x08);
        directories[i].mNum = read_big_endian_u16(raw + 0x0A);
        directories[i].mFirstIdx = read_big_endian_u32(raw + 0x0C);
        valid = directories[i].mOffset < stringLength &&
                memchr(strings + directories[i].mOffset, '\0', stringLength - directories[i].mOffset) != nullptr &&
                directories[i].mFirstIdx <= numFiles &&
                directories[i].mNum <= numFiles - directories[i].mFirstIdx;
        if (!valid) {
            OSReport("[PC] Invalid RARC node %u: name=%u first=%u count=%u strings=%u files=%u\n",
                     i, directories[i].mOffset, directories[i].mFirstIdx,
                     directories[i].mNum, stringLength, numFiles);
        }
    }

    for (u32 i = 0; valid && i < numFiles; i++) {
        const u8* raw = rawInfo + rawFileOffset + i * 20;
        files[i].mFileID = read_big_endian_u16(raw + 0x00);
        files[i].mHash = read_big_endian_u16(raw + 0x02);
        files[i].mFlag = read_big_endian_u32(raw + 0x04);
        files[i].mDataOffset = read_big_endian_u32(raw + 0x08);
        files[i].mSize = read_big_endian_u32(raw + 0x0C);
        files[i].mData = nullptr;

        const u32 nameOffset = files[i].mFlag & 0x00ffffff;
        const bool isDirectory = ((files[i].mFlag >> 24) & 0x02) != 0;
        valid = nameOffset < stringLength &&
                memchr(strings + nameOffset, '\0', stringLength - nameOffset) != nullptr;
        if (valid && isDirectory) {
            valid = files[i].mDataOffset < numNodes ||
                    (files[i].mDataOffset == 0xffffffffu && strcmp(strings + nameOffset, "..") == 0);
        } else if (valid && fileDataSize != 0) {
            valid = files[i].mDataOffset <= fileDataSize &&
                    files[i].mSize <= fileDataSize - files[i].mDataOffset;
        }
        if (!valid) {
            OSReport("[PC] Invalid RARC file %u: flags=%08x name=%u data=%u size=%u strings=%u nodes=%u dataSize=%u\n",
                     i, files[i].mFlag, nameOffset, files[i].mDataOffset, files[i].mSize,
                     stringLength, numNodes, fileDataSize);
        }
    }

    if (!valid) {
        JKRFreeToHeap(mHeap, nativeInfo);
        return false;
    }

    if (memoryPartSize != 0) {
        void* nativeMemory = (u8*)nativeInfo + nativeMemoryOffset;
        memcpy(nativeMemory, memoryPart, memoryPartSize);
        if (nativeMemoryPart != nullptr) {
            *nativeMemoryPart = (JKRArchiveDataAddress)(uintptr_t)nativeMemory;
        }
    }

    mArcInfoBlock = nativeInfo;
    mDirectories = directories;
    mFileEntries = files;
    mStrTable = strings;
    OSReport("[PC] RARC info: mode=%u nodes=%u files=%u\n", mMountMode, numNodes, numFiles);
    return true;
}
#endif

bool JKRArchive::isSameName(JKRArchive::CArcName& archiveName, u32 nameTableOffset, u16 hash) const {
    u16 arcHash = archiveName.getHash();
    if (arcHash != hash)
        return false;

    return strcmp(&mStrTable[nameTableOffset], archiveName.getString()) == 0;
}

JKRArchive::SDIDirEntry* JKRArchive::findResType(u32 type) const {
    SDIDirEntry* dirEntry = mDirectories;
    for (u32 i = 0; i < mArcInfoBlock->num_nodes; i++, dirEntry++) {
        if (dirEntry->mType == type) {
            return dirEntry;
        }
    }
    return nullptr;
}

JKRArchive::SDIDirEntry* JKRArchive::findDirectory(const char* path, u32 index) const {
    if (path == nullptr) {
        return &mDirectories[index];
    }

    CArcName arcName(&path, '/');
    SDIDirEntry* dirEntry = &mDirectories[index];
    SDIFileEntry* entry = &mFileEntries[dirEntry->mFirstIdx];

    for (int i = 0; i < dirEntry->mNum; entry++, i++) {
        if (isSameName(arcName, entry->mFlag & 0xFFFFFF, entry->mHash)) {
            if ((entry->mFlag >> 24) & 0x02) {
                return findDirectory(path, entry->mDataOffset);
            }
            break;
        }
    }

    return nullptr;
}

JKRArchive::SDIFileEntry* JKRArchive::findTypeResource(u32 type, const char* name) const {
    if (type != 0) {
        CArcName arcName;
        arcName.store(name);
        SDIDirEntry* dirEntry = findResType(type);
        if (dirEntry != nullptr) {
            SDIFileEntry* fileEntry = mFileEntries + dirEntry->mFirstIdx;
            for (int i = 0; i < dirEntry->mNum; fileEntry++, i++) {
                if (isSameName(arcName, fileEntry->mFlag & 0xFFFFFF, fileEntry->mHash)) {
                    return fileEntry;
                }
            }
        }
    }
    return nullptr;
}

JKRArchive::SDIFileEntry* JKRArchive::findFsResource(const char* path, u32 index) const {
    if (path) {
        CArcName arcName(&path, '/');
        SDIDirEntry* dirEntry = &mDirectories[index];
        SDIFileEntry* entry = &mFileEntries[dirEntry->mFirstIdx];
        for (int i = 0; i < dirEntry->mNum; entry++, i++) {
            if (isSameName(arcName, entry->mFlag & 0xFFFFFF, entry->mHash)) {
                if (((entry->mFlag >> 0x18) & 2)) {
                    return findFsResource(path, entry->mDataOffset);
                }
                if (path == 0) {
                    return entry;
                }
                return nullptr;
            }
        }
    }
    return nullptr;
}

JKRArchive::SDIFileEntry* JKRArchive::findIdxResource(u32 idx) const {
    if (idx < mArcInfoBlock->num_file_entries) {
        return mFileEntries + idx;
    }
    return nullptr;
}

JKRArchive::SDIFileEntry* JKRArchive::findNameResource(const char* name) const {
    SDIFileEntry* fileEntry = mFileEntries;

    CArcName arcName(name);
    for (int i = 0; i < mArcInfoBlock->num_file_entries; fileEntry++, i++) {
        if (isSameName(arcName, fileEntry->mFlag & 0xFFFFFF, fileEntry->mHash)) {
            return fileEntry;
        }
    }

    return nullptr;
}

JKRArchive::SDIFileEntry* JKRArchive::findPtrResource(const void* ptr) const {
    SDIFileEntry* entry = mFileEntries;
    for (u32 i = 0; i < mArcInfoBlock->num_file_entries; entry++, i++) {
        if (entry->mData == ptr) {
            return entry;
        }
    }
    return nullptr;
}

JKRArchive::SDIFileEntry* JKRArchive::findIdResource(u16 id) const {
    SDIFileEntry* entry;
    if (id != 0xFFFF) {
        entry = &mFileEntries[id];
        if (entry->mFileID == id && (entry->getFlag01())) {
            return entry;
        }

        entry = mFileEntries;
        for (int i = 0; i < mArcInfoBlock->num_file_entries; entry++, i++) {
            if (entry->mFileID == id && (entry->getFlag01())) {
                return entry;
            }
        }
    }
    return nullptr;
}

void JKRArchive::CArcName::store(const char* name) {
    mHash = 0;
    int count = 0;
    while (*name) {
        int lower = tolower(*name);
        mHash = lower + mHash * 3;
        if (count < 0x100) {
            mString[count++] = lower;
        }
        name++;
    }
    _02 = count;
    mString[count] = '\0';
}

const char* JKRArchive::CArcName::store(const char* name, char endChar) {
    mHash = 0;
    int count = 0;
    for (; *name && *name != endChar; name++) {
        int lower = tolower(*name);
        mHash = lower + mHash * 3;
        if (count < 0x100) {
            mString[count++] = lower;
        }
    }
    _02 = count;
    mString[count] = '\0';

    if (*name == 0)
        return nullptr;
    return name + 1;
}
