#include <dolphin/dvd.h>
#include "JSystem/JKernel/JKRFileFinder.h"
#include "JSystem/JKernel/JKRArchive.h"

JKRArcFinder::JKRArcFinder(JKRArchive* archive, long startindex, long entries) : JKRFileFinder() {
    mArchive = archive;

    mIsAvailable = entries > 0;
    mStartIndex = (u32)startindex;
    mEndIndex = (u32)(startindex + entries - 1);
    mNextIndex = mStartIndex;

    findNextFile();
}

bool JKRArcFinder::findNextFile() {
    if (mIsAvailable) {
        mIsAvailable = (mNextIndex <= mEndIndex);
        if (mIsAvailable) {
            JKRArchive::SDirEntry dirEntry;
            mIsAvailable = mArchive->getDirEntry(&dirEntry, mNextIndex);
            mBase.mFileName = dirEntry.mName;
            mBase.mFileIndex = mNextIndex;
            mBase.mFileID = dirEntry.mID;
            mBase.mFileTypeFlags = dirEntry.mFlags;
            mIsDir = FLAG_OFF(mBase.mFileTypeFlags, 2);
            mNextIndex++;
        }
    }
    return mIsAvailable;
}

// UNUSED
JKRDvdFinder::JKRDvdFinder(const char* path) : JKRFileFinder() {
    mIsDvdOpen = DVDOpenDir(const_cast<char*>(path), &mDir);
    mIsAvailable = mIsDvdOpen;
    findNextFile();
}

// UNUSED, not sure if it matches
bool JKRDvdFinder::findNextFile() {
    if (mIsAvailable) {
        DVDDirEntry entry;
        mIsAvailable = DVDReadDir(&mDir, &entry);
        if (mIsAvailable) {
            mIsDir = (bool)entry.isDir;
            mBase.mFileName = entry.name;
            mBase.mFileIndex = entry.entryNum;
            mBase.mFileID = 0;

            mBase.mFileTypeFlags = mIsDir ? 2 : 1;
        }
    }
    return mIsAvailable;
}
