#include "JSystem/JKernel/JKRDvdFile.h"

JSUList<JKRDvdFile> JKRDvdFile::sDvdList;

JKRDvdFile::JKRDvdFile() : JKRFile(), mLink(this) {
    this->initiate();
}

/* This method is confirmed to exist, but goes unused in AC. Retrieved from TP debug. */
JKRDvdFile::JKRDvdFile(const char* filename) : JKRFile(), mLink(this) {
    this->initiate();
    this->mFileOpen = this->open(filename);

    if (this->isAvailable()) {
        return;
    }
}

JKRDvdFile::JKRDvdFile(s32 entrynum) : JKRFile(), mLink(this) {
    this->initiate();
    this->mFileOpen = this->open(entrynum);

    if (this->isAvailable()) {
        return;
    }
}

JKRDvdFile::~JKRDvdFile() {
    this->close();
}

void JKRDvdFile::initiate() {
    /* Reference to self. Used to retrieve reference in the DVDReadAsync
     * DVDCallback func. */
    this->mDvdFileInfo.mFile = this;
    OSInitMutex(&this->mDvdMutex);
    OSInitMutex(&this->mAramMutex);
    OSInitMessageQueue(&this->mDvdMessageQueue, &this->mDvdMessage, 1);
    OSInitMessageQueue(&this->mAramMessageQueue, &this->mAramMessage, 1);
    this->mDvdThread = nullptr;
    this->mAramThread = nullptr;
    this->_58 = 0;
}

/* This method is confirmed to exist, but goes unused in AC. Retrieved from TP debug. */
bool JKRDvdFile::open(const char* filename) {
    if (this->mFileOpen == false) {
        this->mFileOpen = DVDOpen((char*)filename, &this->mDvdFileInfo);
        if (this->mFileOpen) {
            sDvdList.append(&this->mLink);
            DVDGetFileInfoStatus(&this->mDvdFileInfo);
        }
    }

    return this->mFileOpen;
}

bool JKRDvdFile::open(s32 entrynum) {
    if (this->mFileOpen == false) {
        this->mFileOpen = DVDFastOpen(entrynum, &this->mDvdFileInfo);
        if (this->mFileOpen) {
            sDvdList.append(&this->mLink);
            DVDGetFileInfoStatus(&this->mDvdFileInfo);
        }
    }

    return this->mFileOpen;
}

bool JKRDvdFile::close() {
    if (this->mFileOpen) {
        if (DVDClose(&this->mDvdFileInfo)) {
            this->mFileOpen = false;
            return sDvdList.remove(&this->mLink);
        } else {
            OSErrorLine(212, "cannot close DVD file\n"); /* JKRDvdFile.cpp line 212 */
        }
    }
    return false;
}

int JKRDvdFile::readData(void* data, s32 length, s32 ofs) {
    OSLockMutex(&this->mDvdMutex);
    s32 retAddr;

    if (this->mDvdThread != nullptr) {
        OSUnlockMutex(&this->mDvdMutex);
        return -1;
    } else {
        this->mDvdThread = OSGetCurrentThread();
        retAddr = -1;
        if (DVDReadAsync(&this->mDvdFileInfo, data, length, ofs, JKRDvdFile::doneProcess)) {
            retAddr = this->sync();
        }

        this->mDvdThread = nullptr;
        OSUnlockMutex(&this->mDvdMutex);
    }

    return retAddr;
}

int JKRDvdFile::writeData(const void* data, s32 length, s32 ofs) {
    return -1;
}

s32 JKRDvdFile::sync() {
    OSMessage m;

    OSLockMutex(&this->mDvdMutex);
    OSReceiveMessage(&this->mDvdMessageQueue, &m, OS_MESSAGE_BLOCK);
    this->mDvdThread = nullptr;
    OSUnlockMutex(&this->mDvdMutex);
    return (s32)(intptr_t)m;
}

void JKRDvdFile::doneProcess(s32 result, DVDFileInfo* info) {
    OSSendMessage(&static_cast<JKRDvdFileInfo*>(info)->mFile->mDvdMessageQueue, (OSMessage)(intptr_t)result,
                  OS_MESSAGE_NOBLOCK);
}
