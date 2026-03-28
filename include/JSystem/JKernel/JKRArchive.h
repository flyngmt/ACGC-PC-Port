#ifndef JKRARCHIVE_H_
#define JKRARCHIVE_H_

#include "JSystem/JKernel/JKRDvdFile.h"
#include "JSystem/JKernel/JKRFileLoader.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "types.h"

#ifdef __cplusplus
// NOTE: Vtable offsets are off

#define JKRARCHIVE_ATTR_COMPRESSION 0x04
#define JKRARCHIVE_ATTR_YAY0 0x80

inline u32 read_big_endian_u32(void* ptr) {
    u8* uptr = (u8*)ptr;
    return ((u32)uptr[0] << 0x18) | ((u32)uptr[1] << 0x10) | ((u32)uptr[2] << 8) | (u32)uptr[3];
}

class JKRArchive : public JKRFileLoader {
  public:
    enum EMountMode {
        UNKNOWN_MOUNT_MODE = 0,
        MOUNT_MEM = 1,
        MOUNT_ARAM = 2,
        MOUNT_DVD = 3,
        MOUNT_COMP = 4,
    };

    enum EMountDirection {
        UNKNOWN_MOUNT_DIRECTION = 0,
        MOUNT_DIRECTION_HEAD = 1,
        MOUNT_DIRECTION_TAIL = 2,
    };

    class CArcName {
      public:
        CArcName(const char** p1, char p2) {
            p1[0] = store(p1[0], p2);
        }

        const char* getString() const {
            return mString;
        }
        u16 getHash() const {
            return mHash;
        }
        void store(const char*);
        const char* store(const char*, char);

        // Unused/inlined:
        CArcName() {
        }
        CArcName(const char* data) {
            store(data);
        }

        u16 mHash;         // _00
        u16 _02;           // _02
        char mString[256]; // _04
        u8 _104[4];        // _104, unknown, used to fix stack size
    };

    struct SDIFileEntry {
        u16 getNameHash() const {
            return mHash;
        }
        u32 getNameOffset() const {
            return mFlag & 0xFFFFFF;
        }
        u32 getFlags() const {
            return mFlag >> 24;
        }
        u32 getAttr() const {
            return getFlags();
        }
        u32 getSize() {
            return mSize;
        }
        u16 getFileID() const {
            return mFileID;
        }
        bool isDirectory() const {
            return (getFlags() & 0x02) != 0;
        }
        bool isCompressed() const {
            return (getFlags() & 0x04) != 0;
        }
        u8 getCompressFlag() const {
            return (getFlags() & 0x04);
        } // apparently both necessary?
        bool isYAZ0Compressed() const {
            return (getFlags() & 0x80) != 0;
        }

        bool getFlag01() const {
            return (getFlags() & 0x01) != 0;
        }
        bool getFlag04() {
            return mFlag >> 0x18 & 0x04;
        }
        bool getFlag10() {
            return mFlag >> 0x18 & 0x10;
        }
        bool getFlag80() {
            return mFlag >> 0x18 & 0x80;
        }

        u16 mFileID;     // _00
        u16 mHash;       // _02
        u32 mFlag;       // _04
        u32 mDataOffset; // _08
        u32 mSize;       // _0C
#ifdef TARGET_PC
        /* On 64-bit, void* is 8 bytes which breaks the 0x14-byte RARC
         * binary layout. Keep a u32 placeholder here to preserve stride.
         * Actual mData pointers are stored in a parallel array via
         * the accessor macros below. */
        u32 mData_pad;   // _10 (placeholder, not used directly)
#else
        void* mData;     // _10
#endif
    };

#ifdef TARGET_PC
    /* On 64-bit, SDIFileEntry.mData is a u32 placeholder (not a real pointer)
     * to keep the struct at 0x14 bytes matching the RARC binary layout.
     * Store actual mData pointers in a parallel heap-allocated array. */
    void** mFileEntryDataPtrs;       // allocated alongside mFileEntries

    void* getFileEntryData(SDIFileEntry* entry) const {
        if (!mFileEntryDataPtrs || !mArcInfoBlock) return nullptr;
        int idx = (int)(entry - mFileEntries);
        if (idx >= 0 && (u32)idx < mArcInfoBlock->num_file_entries) return mFileEntryDataPtrs[idx];
        return nullptr;
    }
    void setFileEntryData(SDIFileEntry* entry, void* data) {
        if (!mFileEntryDataPtrs || !mArcInfoBlock) return;
        int idx = (int)(entry - mFileEntries);
        if (idx >= 0 && (u32)idx < mArcInfoBlock->num_file_entries) mFileEntryDataPtrs[idx] = data;
    }
#else
    void* getFileEntryData(SDIFileEntry* entry) const { return entry->mData; }
    void setFileEntryData(SDIFileEntry* entry, void* data) { entry->mData = data; }
#endif

    struct SDirEntry {
        u8 mFlags;   // _00
        u8 _01;      // _01
        u16 mID;     // _02
        char* mName; // _04
    };

    struct SDIDirEntry {
        u32 mType;     // _00
        u32 mOffset;   // _04
        u16 _08;       // _08
        u16 mNum;      // _0A
        u32 mFirstIdx; // _0C
    };

    // NB: Fabricated name
    struct SArcDataInfo {
        u32 num_nodes;           // _00
        u32 node_offset;         // _04
        u32 num_file_entries;    // _08
        u32 file_entry_offset;   // _0C
        u32 string_table_length; // _10
        u32 string_table_offset; // _14
        u16 nextFreeFileID;      // _18
        bool isSyncIDs;          // _1A
        u8 _1B[5];               // _1B, unknown
    };

    // NB: Fabricated name - need to check size
    struct SArcHeader {
        u32 signature;        // _00
        u32 file_length;      // _04
        u32 header_length;    // _08
        u32 file_data_offset; // _0C
        u32 file_data_length; // _10
        u32 _14;              // _14
        u32 _18;              // _18
        u32 _1C;              // _1C
    };

  public:
    virtual bool becomeCurrent(const char*);               // _10
    virtual void* getResource(const char* path);           // _14
    virtual void* getResource(u32 type, const char* name); // _18
    virtual size_t readResource(void* resourceBuffer, u32 bufferSize, const char* path,
                                JKRExpandSwitch expandSwitch);                                     // _1C
    virtual size_t readResource(void* resourceBuffer, u32 bufferSize, u32 type, const char* name); // _20
    virtual void removeResourceAll();                                                              // _24
    virtual bool removeResource(void*);                                                            // _28
    virtual bool detachResource(void*);                                                            // _2C
    virtual s32 getResSize(const void*) const;                                                     // _30
    virtual u32 countFile(const char*) const;                                                      // _34
    virtual JKRFileFinder* getFirstFile(const char*) const;                                        // _38
    virtual void* fetchResource(SDIFileEntry* entry, u32* outSize) = 0;                            // _40
    virtual void* fetchResource(void* resourceBuffer, u32 bufferSize, SDIFileEntry* entry, u32* resSize,
                                JKRExpandSwitch expandSwitch) = 0; // _44

    JKRArchive(s32, EMountMode);
    JKRArchive();
    JKRArchive(const char* p1, EMountMode mountMode);
    ~JKRArchive();

    SDIDirEntry* findDirectory(const char*, u32) const;
    SDIFileEntry* findFsResource(const char*, u32) const;
    SDIFileEntry* findIdResource(u16) const;
    SDIFileEntry* findIdxResource(u32) const;
    SDIFileEntry* findNameResource(const char*) const;
    SDIFileEntry* findPtrResource(const void*) const;
    SDIFileEntry* findTypeResource(u32, const char*) const;
    bool isSameName(CArcName&, u32, u16) const;

    bool getDirEntry(SDirEntry*, u32) const;
    void* getIdxResource(u32 index);
    size_t readResource(void* resourceBuffer, u32 bufferSize, u16 id);

    static JKRArchive* mount(char const*, EMountMode, JKRHeap*, EMountDirection);
    static JKRArchive* mount(void*, JKRHeap*, EMountDirection);
    static JKRArchive* mount(s32, EMountMode, JKRHeap*, EMountDirection);
    static void* getGlbResource(u32 type, const char* name, JKRArchive* archive);
    static JKRArchive* check_mount_already(s32);
    static JKRArchive* check_mount_already(s32, JKRHeap*);

    SDIDirEntry* findResType(u32) const;
    SDIFileEntry* findTypeResource(u32, u32) const;

    static int convertAttrToCompressionType(int attr) {
        int compression;
        if (FLAG_ON(attr, JKRARCHIVE_ATTR_COMPRESSION))
            compression = JKRCOMPRESSION_NONE;
        else if (!FLAG_ON(attr, JKRARCHIVE_ATTR_YAY0))
            compression = JKRCOMPRESSION_YAZ0;
        else
            compression = JKRCOMPRESSION_YAY0;

        return compression;
    }

    u32 getMountMode() const {
        return mMountMode;
    }
    u32 countFile() const {
        return mArcInfoBlock->num_file_entries;
    }
    int countDirectory() const {
        return mArcInfoBlock->num_nodes;
    }
    static u32 getCurrentDirID() {
        return sCurrentDirID;
    }
    static void setCurrentDirID(u32 dirID) {
        sCurrentDirID = dirID;
    }

    static u32 sCurrentDirID;

  protected:
    // _00     = VTBL
    // _00-_38 = JKRFileLoader
    JKRHeap* mHeap;                  // _38
    u8 mMountMode;                   // _3C
    s32 mEntryNum;                   // _40
    SArcDataInfo* mArcInfoBlock;     // _44
    SDIDirEntry* mDirectories;       // _48
    SDIFileEntry* mFileEntries;      // _4C
    const char* mStrTable;           // _50
    int _54;                         // _54
    int mCompression;                // _58
    EMountDirection mMountDirection; // _5C
};

enum JKRMemBreakFlag { MBF_0 = 0, MBF_1 = 1 };

class JKRAramArchive : public JKRArchive {
  public:
    JKRAramArchive();
    JKRAramArchive(s32, EMountDirection);

    virtual ~JKRAramArchive();                                                                  // _08
    virtual void* fetchResource(SDIFileEntry*, u32*);                                           // _40
    virtual void* fetchResource(void*, u32, SDIFileEntry*, u32*, JKRExpandSwitch expandSwitch); // _44

    bool open(s32);
    u32 getAramAddress_Entry(SDIFileEntry* fileEntry);
    u32 getAramAddress(u32, const char* file);
    static u32 fetchResource_subroutine(u32, u32, u8*, u32, int);
    static u32 fetchResource_subroutine(u32, u32, JKRHeap*, int, u8**);

    void fixedInit(s32 entryNum, EMountDirection direction);
    bool mountFixed(s32 entryNum, EMountDirection direction);
    bool mountFixed(const char* path, EMountDirection direction);
    void unmountFixed();

    // _00     = VTBL
    // _00-_60 = JKRArchive
    JKRAramBlock* mBlock; // _60
    JKRFile* mDvdFile;    // _64
};

struct JKRCompArchive : public JKRArchive {
    JKRCompArchive(s32, EMountDirection);

    virtual ~JKRCompArchive();                                      // _08
    virtual void removeResourceAll();                               // _24
    virtual bool removeResource(void*);                             // _28
    virtual void* fetchResource(SDIFileEntry* entry, u32* outSize); // _40
    virtual void* fetchResource(void* resourceBuffer, u32 bufferSize, SDIFileEntry* entry, u32* resSize,
                                JKRExpandSwitch expandSwitch); // _44

    bool open(s32);

    // Unused/inlined:
    void fixedInit(s32);
    void mountFixed(s32);
    void mountFixed(const char*);
    void unmountFixed();

    // _00     = VTBL
    // _00-_5C = JKRArchive
#ifdef TARGET_PC
    uintptr_t _60;           // _60
#else
    u32 _60;                 // _60
#endif
    JKRAramBlock* mAramPart; // _64
    u32 _68;                 // _68
    JKRFile* mDvdFile;       // _6C
    u32 mSizeOfMemPart;      // _70
    u32 mSizeOfAramPart;     // _74
    u32 _78;                 // _78
};

struct JKRDvdArchive : public JKRArchive {
    JKRDvdArchive();
    JKRDvdArchive(s32, JKRArchive::EMountDirection);

    virtual ~JKRDvdArchive();                                       // _00
    virtual void* fetchResource(SDIFileEntry* entry, u32* outSize); // _38
    virtual void* fetchResource(void* resourceBuffer, u32 bufferSize, SDIFileEntry* entry, u32* resSize,
                                JKRExpandSwitch expandSwitch); // _3C

    bool open(s32);
    static u32 fetchResource_subroutine(s32, u32, u32, u8*, u32, int, int);
    static u32 fetchResource_subroutine(s32, u32, u32, JKRHeap*, int, int, u8**);

    // Unused/inlined:
    unknown fixedInit(s32, EMountDirection);
    unknown mountFixed(s32, EMountDirection);
    unknown mountFixed(const char*, EMountDirection);
    unknown unmountFixed();

    // _00     = VTBL
    // _00-_5C = JKRArchive
    int _60;           // _60
    JKRFile* mDvdFile; // _64
};

struct JKRMemArchive : public JKRArchive {
    JKRMemArchive(); // unused/inlined
    JKRMemArchive(s32, EMountDirection);
    JKRMemArchive(void*, u32, JKRMemBreakFlag);
    JKRMemArchive(const char*, EMountDirection); // unused/inlined

    virtual ~JKRMemArchive();                                       // _08
    virtual void removeResourceAll();                               // _24
    virtual bool removeResource(void*);                             // _28
    virtual void* fetchResource(SDIFileEntry* entry, u32* outSize); // _40
    virtual void* fetchResource(void* resourceBuffer, u32 bufferSize, SDIFileEntry* entry, u32* resSize,
                                JKRExpandSwitch expandSwitch); // _44

    bool open(s32, EMountDirection);
    bool open(void*, u32, JKRMemBreakFlag);
    static u32 fetchResource_subroutine(u8*, u32, u8*, u32, int);

    // Unused/inlined:
    void fixedInit(s32);
    void mountFixed(s32, EMountDirection);
    void mountFixed(const char*, EMountDirection);
    void mountFixed(void*, JKRMemBreakFlag);
    void unmountFixed();
    void open(const char*, EMountDirection);

    // _00     = VTBL
    // _00-_60 = JKRArchive
    SArcHeader* mArcHeader; // _60
    u8* mArchiveData;       // _64
    bool mIsOpen;           // _68
};

inline int JKRConvertAttrToCompressionType(int attr) {
    return JKRArchive::convertAttrToCompressionType(attr);
}

inline JKRArchive* JKRMountArchive(const char* path, JKRArchive::EMountMode mountMode, JKRHeap* heap,
                                   JKRArchive::EMountDirection mountDirection) {
    return JKRArchive::mount(path, mountMode, heap, mountDirection);
}

inline JKRArchive* JKRMountArchive(void* inBuf, JKRHeap* heap, JKRArchive::EMountDirection mountDirection) {
    return JKRArchive::mount(inBuf, heap, mountDirection);
}

#endif
#endif
