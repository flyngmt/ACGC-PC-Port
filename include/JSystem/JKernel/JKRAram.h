#ifndef JKRARAM_H
#define JKRARAM_H

#include "types.h"
#include "dolphin/ar.h"
#include "dolphin/os/OSMessage.h"
#include "JSystem/JKernel/JKRDisposer.h"
#include "JSystem/JKernel/JKREnum.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JKernel/JKRThread.h"
#include "JSystem/JSupport/JSUList.h"
#include "JSystem/JSupport/JSUStream.h"

#ifdef __cplusplus
#define ARAM_GROUP_ID_ALL 0
#define ARAM_GROUP_ID_DEFAULT 0xFF

#define ARAM_MESGBUF_COUNT 4

#define ARAMPIECE_DONE_CALLBACK 0
#define ARAMPIECE_DONE_NONE 1
#define ARAMPIECE_DONE_DECOMPRESS 2

class JKRAramHeap;
class JKRDecompCommand;
class JKRAMCommand;

class JKRAramBlock {
  public:
    JKRAramBlock(u32 address, u32 size, u32 freeSize, u8 groupID, bool tempMemory);

    virtual ~JKRAramBlock();

    JKRAramBlock* allocHead(u32 size, u8 groupID, JKRAramHeap* heap);
    JKRAramBlock* allocTail(u32 size, u8 groupID, JKRAramHeap* heap);

    u32 getAddress() const {
        return this->mAddress;
    }
    u32 getSize() const {
        return this->mSize;
    }
    u32 getFreeSize() const {
        return this->mFreeSize;
    }
    bool isTempMemory() const {
        return this->mIsTempMemory;
    }
    void newGroupID(u8 groupID) {
        this->mGroupID = groupID;
    }

    JSULink<JKRAramBlock> mLink;
    u32 mAddress;
    u32 mSize;
    u32 mFreeSize;
    u8 mGroupID;
    bool mIsTempMemory;

    friend class JKRAramHeap;
};

class JKRAramHeap : public JKRDisposer {
  public:
    enum EAllocMode { Head = 0, Tail = 1 };

    JKRAramHeap(u32 baseAddress, u32 size);

    virtual ~JKRAramHeap();

    JKRAramBlock* alloc(u32 size, EAllocMode mode);
    void free(JKRAramBlock* block);
    JKRAramBlock* allocFromHead(u32 size);
    JKRAramBlock* allocFromTail(u32 size);
    u32 getFreeSize();
    u32 getTotalFreeSize();
    u32 getUsedSize(u8 groupID);
    void dump();

    u8 getCurrentGroupID() const {
        return this->mGroupID;
    }
    JKRHeap* getMgrHeap() const {
        return this->mHeap;
    }

    void lock() {
        OSLockMutex(&this->mMutex);
    }
    void unlock() {
        OSUnlockMutex(&this->mMutex);
    }

    static JSUList<JKRAramBlock> sAramList;

    OSMutex mMutex;
    JKRHeap* mHeap;
    u32 mHeadAddress;
    u32 mTailAddress;
    u32 mSize;
    u8 mGroupID;

    friend class JKRAramBlock;
};

class JKRAram : public JKRThread {
  public:
#ifdef TARGET_PC
    JKRAram(u32, u32, s32);
#else
    JKRAram(u32, u32, long);
#endif

    virtual ~JKRAram();  // _08
    virtual void* run(); // _0C

    static bool checkOkAddress(u8* addr, u32 size, JKRAramBlock* block, u32 param_4);
    static void changeGroupIdIfNeed(u8* data, int groupId);

#ifdef TARGET_PC
    static JKRAram* create(u32, u32, s32, s32, s32);
#else
    static JKRAram* create(u32, u32, long, long, long);
#endif
    static JKRAramBlock* mainRamToAram(u8*, u32, u32, JKRExpandSwitch, u32, JKRHeap*, int);
    static JKRAramBlock* mainRamToAram(u8*, JKRAramBlock* block, u32, JKRExpandSwitch, u32, JKRHeap*, int);
    static u8* aramToMainRam(u32, u8*, u32, JKRExpandSwitch, u32, JKRHeap*, int, u32*);
    static u8* aramToMainRam(JKRAramBlock*, u8*, u32, u32, JKRExpandSwitch, u32, JKRHeap*, int, u32*);

    void aramSync(JKRAMCommand*, int);

    u32 getAudioMemory() const {
        return mAudioMemoryPtr;
    }

    u32 getAudioMemSize() const {
        return mAudioMemorySize;
    }

    static u32 getSZSBufferSize() {
        return sSZSBufferSize;
    }

    static JKRAramHeap* getAramHeap() {
        return sAramObject->mAramHeap;
    }

    static JKRAram* getManager() {
        return sAramObject;
    }

    static u8 decideAramGroupId(int id) {
        if (id < 0)
            return getAramHeap()->getCurrentGroupID();
        else
            return id;
    }

    static u32 sSZSBufferSize;

    static JKRAram* sAramObject;
    static OSMessage sMessageBuffer[4];
    static OSMessageQueue sMessageQueue;
    static JSUList<JKRAMCommand> sAramCommandList;

    u32 mAudioMemoryPtr;    // _7C
    u32 mAudioMemorySize;   // _80
    u32 mGraphMemoryPtr;    // _84
    u32 mGraphMemorySize;   // _88
    u32 mUserMemoryPtr;     // _8C
    u32 mUserMemorySize;    // _90
    JKRAramHeap* mAramHeap; // _94
    u32 mStackArray[3];     // _98
};

class JKRAMCommand : public ARQRequest {
  public:
#ifdef TARGET_PC
    typedef void (*AMCommandCallback)(uintptr_t);
#else
    typedef void (*AMCommandCallback)(u32);
#endif

    JKRAMCommand();
    ~JKRAMCommand();

    JSULink<JKRAMCommand> mAramPieceCommandLink;
    JSULink<JKRAMCommand> mLink30;
    s32 mDirection;
    u32 mLength;
#ifdef TARGET_PC
    uintptr_t mSource;
    uintptr_t mDestination;
#else
    u32 mSource;
    u32 mDestination;
#endif
    JKRAramBlock* mAramBlock;
    u8 _54[4];
    AMCommandCallback mCallback;
    OSMessageQueue* mCompletedMesgQueue;
    s32 mCallbackType;
    JKRDecompCommand* mDecompCommand;
    OSMessageQueue mMesgQueue;
    OSMessage mMesgBuffer[1];
    void* _8C;
    void* _90;
    void* _94;
};

class JKRAramCommand {
  public:
    inline void setting(BOOL active, void* arg) {
        this->mActive = active;
        this->mArg = arg;
    }

    BOOL mActive;
    void* mArg;
};

class JKRAramPiece {
  public:
#ifdef TARGET_PC
    static JKRAMCommand* prepareCommand(int direction, uintptr_t source, uintptr_t destination, u32 length, JKRAramBlock* aramBlock,
                                        JKRAMCommand::AMCommandCallback callback);
    static void sendCommand(JKRAMCommand* cmd);
    static JKRAMCommand* orderAsync(int direction, uintptr_t source, uintptr_t destination, u32 length, JKRAramBlock* aramBlock,
                                    JKRAMCommand::AMCommandCallback callback);
    static bool sync(JKRAMCommand* cmd, BOOL noBlock);
    static bool orderSync(int direction, uintptr_t source, uintptr_t destination, u32 length, JKRAramBlock* aramBlock);
    static void startDMA(JKRAMCommand* cmd);
    static void doneDMA(uintptr_t arg);
#else
    static JKRAMCommand* prepareCommand(int direction, u32 source, u32 destination, u32 length, JKRAramBlock* aramBlock,
                                        JKRAMCommand::AMCommandCallback callback);
    static void sendCommand(JKRAMCommand* cmd);
    static JKRAMCommand* orderAsync(int direction, u32 source, u32 destination, u32 length, JKRAramBlock* aramBlock,
                                    JKRAMCommand::AMCommandCallback callback);
    static bool sync(JKRAMCommand* cmd, BOOL noBlock);
    static bool orderSync(int direction, u32 source, u32 destination, u32 length, JKRAramBlock* aramBlock);
    static void startDMA(JKRAMCommand* cmd);
    static void doneDMA(u32 arg);
#endif

    static OSMutex mMutex;
    static JSUList<JKRAMCommand> sAramPieceCommandList;

  private:
    static void lock() {
        OSLockMutex(&mMutex);
    }
    static void unlock() {
        OSUnlockMutex(&mMutex);
    }
};

class JKRAramStreamCommand {
  public:
    enum ECommandType {
        ECT_UNK = 0,
        ECT_READ = 1,
        ECT_WRITE = 2,
    };

    JKRAramStreamCommand();

    ECommandType type;             // _00
#ifdef TARGET_PC
    uintptr_t mAddress;            // _04
#else
    u32 mAddress;                  // _04
#endif
    u32 mSize;                     // _08
    u32 _0C;                       // _0C
    JSUFileInputStream* mStream;   // _10
    u32 mOffset;                   // _14
    u8* mTransferBuffer;           // _18
    u32 mTransferBufferSize;       // _1C
    JKRHeap* mHeap;                // _20
    bool mAllocatedTransferBuffer; // _24
    u32 _28;                       // _28
    OSMessageQueue mMessageQueue;  // _2C
    void* mMessage;                // _4C
    u32 _50;                       // _50
    u32 _54;                       // _54
};

class JKRAramStream : public JKRThread {
  public:
#ifdef TARGET_PC
    JKRAramStream(s32);
#else
    JKRAramStream(long);
#endif

    virtual ~JKRAramStream(); // _08
    virtual void* run();      // _0C

    static JKRAramStream* create(s32);

    static u32 readFromAram();
    static s32 writeToAram(JKRAramStreamCommand*);
    static JKRAramStreamCommand* write_StreamToAram_Async(JSUFileInputStream*, JKRAramBlock*, u32, u32);
    static JKRAramStreamCommand* write_StreamToAram_Async(JSUFileInputStream*, u32, u32, u32);
    static JKRAramStreamCommand* sync(JKRAramStreamCommand*, BOOL);
    static void setTransBuffer(u8*, u32, JKRHeap*);

    static JKRAramStream* sAramStreamObject;
    static OSMessage sMessageBuffer[4];
    static OSMessageQueue sMessageQueue;

    static u8* transBuffer;
    static JKRHeap* transHeap;
    static u32 transSize;

    // _00     = VTBL
    // _00-_7C = JKRThread
};

inline JKRAramBlock* JKRAllocFromAram(u32 size, JKRAramHeap::EAllocMode allocMode) {
    return JKRAram::getAramHeap()->alloc(size, allocMode);
}

inline void JKRFreeToAram(JKRAramBlock* block) {
    JKRAram::getAramHeap()->free(block);
}

inline u8* JKRAramToMainRam(u32 address, u8* buf, u32 bufSize, JKRExpandSwitch expandSwitch, u32 p5, JKRHeap* heap,
                            int id, u32* pSize) {
    return JKRAram::aramToMainRam(address, buf, bufSize, expandSwitch, p5, heap, id, pSize);
}

inline JKRAramBlock* JKRMainRamToAram(u8* buf, u32 bufSize, u32 alignedSize, JKRExpandSwitch expandSwitch, u32 fileSize,
                                      JKRHeap* heap, int id, u32) {
    return JKRAram::mainRamToAram(buf, bufSize, alignedSize, expandSwitch, fileSize, heap, id);
}

inline JKRAramStream* JKRCreateAramStreamManager(s32 priority) {
    return JKRAramStream::create(priority);
}

#ifdef TARGET_PC
inline bool JKRAramPcs(int direction, uintptr_t source, uintptr_t destination, u32 length, JKRAramBlock* block) {
    return JKRAramPiece::orderSync(direction, source, destination, length, block);
}
#else
inline bool JKRAramPcs(int direction, u32 source, u32 destination, u32 length, JKRAramBlock* block) {
    return JKRAramPiece::orderSync(direction, source, destination, length, block);
}
#endif

inline void JKRAramPcs_SendCommand(JKRAMCommand* cmd) {
    JKRAramPiece::sendCommand(cmd);
}

#endif
#endif
