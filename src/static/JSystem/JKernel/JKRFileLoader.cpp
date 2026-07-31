#include <MSL_C/ctype.h>
#include <string.h>
#include "JSystem/JKernel/JKRFileLoader.h"
#include "JSystem/JKernel/JKRHeap.h"

JSUList<JKRFileLoader> JKRFileLoader::sVolumeList;
JKRFileLoader* JKRFileLoader::sCurrentVolume;

JKRFileLoader::JKRFileLoader() : JKRDisposer(), mFileLoaderLink(this) {
    mVolumeName = nullptr;
    mVolumeType = 0;
    mMountCount = 0;
}

JKRFileLoader::~JKRFileLoader() {
    if (sCurrentVolume == this)
        sCurrentVolume = nullptr;
}

void JKRFileLoader::unmount() {
    if (mMountCount != 0) {
        if (--mMountCount == 0)
            JKR_DELETE(this);
    }
}

void JKRFileLoader::changeDirectory(const char* dir) {
    JKRFileLoader* vol = findVolume(&dir);
    if (vol)
        vol->becomeCurrent(dir);
}

void* JKRFileLoader::getGlbResource(const char* path) {
    const char* components[2];
    components[0] = path;
    JKRFileLoader* loader = findVolume(components);
    return (loader == nullptr) ? nullptr : loader->getResource(components[0]);
}

void* JKRFileLoader::getGlbResource(const char* name, JKRFileLoader* fileLoader) {
    void* resource = nullptr;
    if (fileLoader) {
        return fileLoader->getResource(0, name);
    }

    JSUList<JKRFileLoader>& volumeList = getVolumeList();
    JSUListIterator<JKRFileLoader> iterator;
    for (iterator = volumeList.getFirst(); iterator != volumeList.getEnd(); ++iterator) {
        resource = iterator->getResource(0, name);
        if (resource)
            break;
    }
    return resource;
}

size_t JKRFileLoader::readGlbResource(void* resBuf, u32 bufSize, const char* volumeName, JKRExpandSwitch expandSwitch) {
    JKRFileLoader* vol = findVolume(&volumeName);

    return vol == nullptr ? 0 : vol->readResource(resBuf, bufSize, volumeName, expandSwitch);
}

bool JKRFileLoader::removeResource(void* resourceBuffer, JKRFileLoader* fileLoader) {
    if (fileLoader) {
        return fileLoader->removeResource(resourceBuffer);
    }

    JSUList<JKRFileLoader>& volumeList = getVolumeList();
    JSUListIterator<JKRFileLoader> iterator;
    for (iterator = volumeList.getFirst(); iterator != volumeList.getEnd(); ++iterator) {
        if (iterator->removeResource(resourceBuffer))
            return true;
    }

    return false;
}

bool JKRFileLoader::detachResource(void* resourceBuffer, JKRFileLoader* fileLoader) {
    if (fileLoader) {
        return fileLoader->detachResource(resourceBuffer);
    }

    JSUList<JKRFileLoader>& volumeList = getVolumeList();
    JSUListIterator<JKRFileLoader> iterator;
    for (iterator = volumeList.getFirst(); iterator != volumeList.getEnd(); ++iterator) {
        if (iterator->detachResource(resourceBuffer))
            return true;
    }

    return false;
}

JKRFileLoader* JKRFileLoader::findVolume(const char** volumeName) {
    if (*volumeName[0] != '/') {
        return sCurrentVolume;
    }

    char volumeNameBuffer[0x101];
    *volumeName = fetchVolumeName(volumeNameBuffer, ARRAY_COUNT(volumeNameBuffer), *volumeName);

    JSUList<JKRFileLoader>& volumeList = sVolumeList;
    JSUListIterator<JKRFileLoader> iterator;
    for (iterator = volumeList.getFirst(); iterator != volumeList.getEnd(); ++iterator) {
        if (strcmp(volumeNameBuffer, iterator->mVolumeName) == 0)
            return iterator.getObject();
    }
    return nullptr;
}

JKRFileFinder* JKRFileLoader::findFirstFile(const char* volumeName) {
    JKRFileFinder* ret = nullptr;

    JKRFileLoader* vol = findVolume(&volumeName);
    if (vol)
        ret = vol->getFirstFile(volumeName);

    return ret;
}

const char* JKRFileLoader::fetchVolumeName(char* buffer, long bufferSize, const char* path) {
    static char rootPath[] = "/";
    if (strcmp(path, "/") == 0) {
        strcpy(buffer, rootPath);
        return rootPath;
    } else {
        path++;
        while (*path != 0 && *path != '/') {
            if (1 < bufferSize) {
                *buffer = _tolower(*path);
                buffer++;
                bufferSize--;
            }
            path++;
        }
        buffer[0] = '\0';
        if (path[0] == '\0')
            path = rootPath;
    }

    return path;
}
