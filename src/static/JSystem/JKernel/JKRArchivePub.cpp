#include <dolphin/dvd.h>

#include "JSystem/JKernel/JKRAram.h"
#include "JSystem/JKernel/JKRArchive.h"
#include "JSystem/JKernel/JKRDisposer.h"
#include "JSystem/JKernel/JKRFileFinder.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JUtility/JUTAssertion.h"
#include "types.h"

// TODO: this file should emit a vtable but it doesn't, luckily JKRArchivePri
// does that and it doesn't cause any issues

JKRArchive* JKRArchive::check_mount_already(s32 entryNum, JKRHeap* pHeap) {
    // UNUSED FUNCTION
    JKRHeap* heap = pHeap;
    if (heap == nullptr) {
        heap = JKRGetCurrentHeap();
    }

    JSUListIterator<JKRFileLoader> iterator;
    for (iterator = sVolumeList.getFirst(); iterator != sVolumeList.getEnd(); ++iterator) {
        if (iterator->getVolumeType() == 'RARC') {
            JKRArchive* archive = (JKRArchive*)iterator.getObject(); // in TP debug it calls operator-> ?
            if (archive->mEntryNum == entryNum && archive->mHeap == heap) {
                archive->mMountCount++;
                return archive;
            }
        }
    }
    return nullptr;
}

JKRArchive* JKRArchive::check_mount_already(s32 entryNum) {
    for (JSUListIterator<JKRFileLoader> iterator = sVolumeList.getFirst(); iterator != sVolumeList.getEnd();
         ++iterator) {
        if (iterator->getVolumeType() == 'RARC') {
            JKRArchive* archive = (JKRArchive*)iterator.getObject(); // in TP debug it calls operator-> ?
            if (archive->mEntryNum == entryNum) {
                archive->mMountCount++;
                return archive;
            }
        }
    }
    return nullptr;
}

JKRArchive* JKRArchive::mount(const char* path, EMountMode mode, JKRHeap* heap, EMountDirection direction) {
    int entryNum = DVDConvertPathToEntrynum((char*)path);
    if (entryNum < 0)
        return nullptr;

    JKRArchive* mountedArchive = check_mount_already(entryNum);
    if (mountedArchive != nullptr) {
        return mountedArchive;
    }

    int alignment = (direction == MOUNT_DIRECTION_HEAD) ? 4 : -4;
    JKRArchive* archive;
    switch (mode) {
        case MOUNT_MEM:
            if (entryNum == -1)
                archive = nullptr;
            else
                archive = new (heap, alignment) JKRMemArchive(entryNum, direction);
            break;
        case MOUNT_ARAM:
            archive = new (heap, alignment) JKRAramArchive(entryNum, direction);
            break;
        case MOUNT_DVD:
            archive = new (heap, alignment) JKRDvdArchive(entryNum, direction);
            break;
        case MOUNT_COMP:
            archive = new (heap, alignment) JKRCompArchive(entryNum, direction);
            break;
    }
    if (archive != nullptr && archive->getMountMode() == UNKNOWN_MOUNT_MODE) {
        delete archive;
        archive = nullptr;
    }
    return archive;
}

JKRArchive* JKRArchive::mount(void* p1, JKRHeap* heap, EMountDirection mountDirection) {
    JKRArchive* archive = check_mount_already((s32)p1, heap);
    if (archive != nullptr) {
        return archive;
    }
    return new (heap, (mountDirection == MOUNT_DIRECTION_HEAD) ? 4 : -4) JKRMemArchive(p1, 0xFFFF, MBF_0);
}

JKRArchive* JKRArchive::mount(s32 entryNum, EMountMode mountMode, JKRHeap* heap, EMountDirection mountDirection) {
    JKRArchive* archive = check_mount_already(entryNum, heap);
    if (archive) {
        return archive;
    } else {
        int i = (mountDirection == MOUNT_DIRECTION_HEAD) ? 4 : -4;
        JKRArchive* archive;
        switch (mountMode) {
            case MOUNT_MEM:
                archive = new (heap, i) JKRMemArchive(entryNum, mountDirection);
                break;
            case MOUNT_ARAM:
                archive = new (heap, i) JKRAramArchive(entryNum, mountDirection);
                break;
            case MOUNT_DVD:
                archive = new (heap, i) JKRDvdArchive(entryNum, mountDirection);
                break;
            case MOUNT_COMP:
                archive = new (heap, i) JKRCompArchive(entryNum, mountDirection);
                break;
        }
        if (archive != nullptr && archive->getMountMode() == UNKNOWN_MOUNT_MODE) {
            delete archive;
            archive = nullptr;
        }
        return archive;
    }
}

bool JKRArchive::becomeCurrent(const char* path) {
    SDIDirEntry* entry;
    if (*path == '/') {
        const char* directoryName = path + 1;
        if (*directoryName == '\0') {
            directoryName = nullptr;
        }
        entry = findDirectory(directoryName, 0);
    } else {
        entry = findDirectory(path, sCurrentDirID);
    }
    bool result = (entry != nullptr);
    if (result) {
        sCurrentVolume = this;
        sCurrentDirID = (entry - mDirectories);
    }
    return result;
}

bool JKRArchive::getDirEntry(JKRArchive::SDirEntry* dirEntry, u32 p2) const {
    SDIFileEntry* fileEntry = findIdxResource(p2);
    if (!fileEntry) {
        return false;
    }

    dirEntry->mFlags = fileEntry->mFlag >> 0x18;
    dirEntry->mID = fileEntry->mFileID;
    dirEntry->mName = (char*)mStrTable + (fileEntry->mFlag & 0xFFFFFF);
    return true;
}

void* JKRArchive::getGlbResource(u32 type, const char* name, JKRArchive* archive) {
    void* resource = nullptr;
    if (archive) {
        return archive->getResource(type, name);
    }
    for (JSULink<JKRFileLoader>* link = sVolumeList.getFirst(); link != nullptr; link = link->getNext()) {
        if (link->getObject()->getVolumeType() == 'RARC' && (resource = link->getObject()->getResource(type, name))) {
            break;
        }
    }
    return resource;
}

void* JKRArchive::getResource(const char* path) {
    JUT_ASSERT(isMounted());
    SDIFileEntry* fileEntry;
    if (*path == '/') {
        fileEntry = findFsResource(path + 1, 0);
    } else {
        fileEntry = findFsResource(path, sCurrentDirID);
    }
    return (fileEntry != nullptr) ? (void*)fetchResource(fileEntry, nullptr) : nullptr;
}

void* JKRArchive::getResource(u32 type, const char* name) {
    JUT_ASSERT(isMounted());
    SDIFileEntry* fileEntry;
    if (type == 0 || type == '????') {
        fileEntry = findNameResource(name);
    } else {
        fileEntry = findTypeResource(type, name);
    }
    return (fileEntry != nullptr) ? (void*)fetchResource(fileEntry, nullptr) : nullptr;
}

void* JKRArchive::getIdxResource(u32 index) {
    SDIFileEntry* fileEntry = findIdxResource(index);
    return (fileEntry != nullptr) ? (void*)fetchResource(fileEntry, nullptr) : nullptr;
}

size_t JKRArchive::readResource(void* resourceBuffer, u32 bufferSize, u32 type, const char* name) {
    JUT_ASSERT(isMounted());
    SDIFileEntry* fileEntry;
    if (type == 0 || type == '????') {
        fileEntry = findNameResource(name);
    } else {
        fileEntry = findTypeResource(type, name);
    }
    if (fileEntry) {
        u32 resourceSize;
        fetchResource(resourceBuffer, bufferSize, fileEntry, &resourceSize, EXPAND_SWITCH_DECOMPRESS);
        return resourceSize;
    }
    return 0;
}

// Returns the size of the resource at the given path, or 0 if not found.
size_t JKRArchive::readResource(void* resourceBuffer, u32 bufferSize, const char* path, JKRExpandSwitch expandSwitch) {
    JUT_ASSERT(isMounted());
    SDIFileEntry* fileEntry;
    if (*path == '/') {
        fileEntry = findFsResource(path + 1, 0);
    } else {
        fileEntry = findFsResource(path, sCurrentDirID);
    }
    if (fileEntry) {
        u32 resourceSize;
        fetchResource(resourceBuffer, bufferSize, fileEntry, &resourceSize, expandSwitch);
        return resourceSize;
    }
    return 0;
}

// Returns the size of the resource with the given ID, or 0 if not found.
size_t JKRArchive::readResource(void* resourceBuffer, u32 bufferSize, u16 id) {
    JUT_ASSERT(isMounted());
    SDIFileEntry* fileEntry = findIdResource(id);
    if (fileEntry) {
        u32 resSize;
        fetchResource(resourceBuffer, bufferSize, fileEntry, &resSize, EXPAND_SWITCH_DEFAULT);
        return resSize;
    }
    return 0;
}

// This function is currently full off bugs, it doesn't increase the pointer to
// the file entries, and sets the pointer of mData to null before it's sent to
// free
void JKRArchive::removeResourceAll() {
    if (mArcInfoBlock && mMountMode != MOUNT_MEM) {
        SDIFileEntry* entry = mFileEntries;
        for (int i = 0; i < mArcInfoBlock->num_file_entries; i++) {
            if (getFileEntryData(entry)) {
                setFileEntryData(entry, nullptr);
                JKRFreeToHeap(mHeap, getFileEntryData(entry));
            }
        }
    }
}

bool JKRArchive::removeResource(void* resource) {
    JUT_ASSERT(resource != 0);
    SDIFileEntry* entry = findPtrResource(resource);
    if (entry == nullptr) {
        return false;
    }
    setFileEntryData(entry, nullptr);
    JKRHeap::free(resource, mHeap);
    return true;
}

bool JKRArchive::detachResource(void* resource) {
    JUT_ASSERT(resource != 0);
    SDIFileEntry* entry = findPtrResource(resource);
    if (entry == nullptr) {
        return false;
    }
    setFileEntryData(entry, nullptr);
    return true;
}

s32 JKRArchive::getResSize(const void* resource) const {
    JUT_ASSERT(resource != 0);
    SDIFileEntry* entry = findPtrResource(resource);
    return (entry == nullptr) ? -1 : entry->getSize();
}

u32 JKRArchive::countFile(const char* path) const {
    SDIDirEntry* dirEntry;
    if (*path == '/') {
        const char* pathPtr = path + 1;
        if (*pathPtr == '\0') {
            pathPtr = nullptr;
        }
        dirEntry = findDirectory(pathPtr, 0);
    } else {
        dirEntry = findDirectory(path, sCurrentDirID);
    }
    return (dirEntry) ? dirEntry->mNum : 0;
}

JKRFileFinder* JKRArchive::getFirstFile(const char* path) const {
    SDIDirEntry* dirEntry;
    if (*path == '/') {
        const char* pathPtr = path + 1;
        if (*pathPtr == '\0') {
            pathPtr = nullptr;
        }
        dirEntry = findDirectory(pathPtr, 0);
    } else {
        dirEntry = findDirectory(path, sCurrentDirID);
    }
    if (dirEntry) {
        return new (JKRGetSystemHeap(), 0)
            JKRArcFinder(const_cast<JKRArchive*>(this), dirEntry->mFirstIdx, dirEntry->mNum);
    }
    return nullptr;
}
