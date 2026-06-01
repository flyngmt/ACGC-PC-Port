#include <MSL_C/ctype.h>
#include <string.h>

#include "JSystem/JKernel/JKRArchive.h"
#include "JSystem/JKernel/JKRFileLoader.h"
#include "types.h"

u32 JKRArchive::sCurrentDirID;

JKRArchive::JKRArchive() {
    mIsMounted = false;
    mMountDirection = MOUNT_DIRECTION_HEAD;
#ifdef TARGET_PC
    mFileEntryDataPtrs = nullptr;
#endif
}

JKRArchive::JKRArchive(s32 entryNum, JKRArchive::EMountMode mountMode) : JKRFileLoader() {
    mIsMounted = false;
    mMountMode = mountMode;
    mMountCount = 1;
    _54 = 1;
#ifdef TARGET_PC
    mFileEntryDataPtrs = nullptr;
#endif
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
        if (getFileEntryData(entry) == ptr) {
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
