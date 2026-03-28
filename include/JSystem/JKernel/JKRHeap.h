#ifndef JKRHEAP_H
#define JKRHEAP_H

#include "dolphin/os/OSMutex.h"
#include "JSystem/JKernel/JKRDisposer.h"

#include "types.h"

#ifdef __cplusplus
typedef void JKRHeapErrorHandler(void*, u32, int);

class JKRHeap : public JKRDisposer {
  public:
    enum EAllocMode {
        HEAPALLOC_Unk1 = 1,
    };

    struct TState { // NB: this struct doesn't agree with TP's struct
        struct TLocation {
            TLocation() : _00(nullptr), _04(-1) {
            }

            void* _00; // _00
            int _04;   // _04
        };

        struct TArgument {
            TArgument(const JKRHeap* heap, u32 p2, bool p3)
                : mHeap((heap) ? heap : JKRHeap::sCurrentHeap), mId(p2), mIsCompareOnDestructed(p3) {
            }

            const JKRHeap* mHeap;        // _00
            u32 mId;                     // _04
            bool mIsCompareOnDestructed; // _08
        };

        TState(const JKRHeap* heap, u32 id, bool isCompareOnDestructed)
            : mUsedSize(0), mCheckCode(0), mArgument(heap, id, isCompareOnDestructed) {
            mArgument.mHeap->state_register(this, mArgument.mId);
        }

        TState(JKRHeap* heap) : mUsedSize(0), mCheckCode(0), mArgument(heap, 0xFFFFFFFF, true) {
        }

        ~TState();
        void dump() const {
            mArgument.mHeap->state_dump(*this);
        }
        bool isVerbose() {
            return bVerbose_;
        };
        bool isCompareOnDestructed() const {
            return mArgument.mIsCompareOnDestructed;
        };
        u32 getUsedSize() const {
            return mUsedSize;
        }
        u32 getCheckCode() const {
            return mCheckCode;
        }
        const JKRHeap* getHeap() const {
            return mArgument.mHeap;
        }
        u32 getId() const {
            return mArgument.mId;
        }

        // unused/inlined:
        TState(const JKRHeap::TState::TArgument& arg, const JKRHeap::TState::TLocation& location);
        TState(const JKRHeap::TState& other, bool p2);
        TState(const JKRHeap::TState& other, const JKRHeap::TState::TLocation& location, bool p3);

        static bool bVerbose_;

        u32 mUsedSize;       // _00
        u32 mCheckCode;      // _04, plausibly TLocation when combined with _00
        u32 mBuf;            // _08
        u8 _0C[0x4];         // _0C
        TArgument mArgument; // _10
        TLocation mLocation; // _1C
    };

  public:
    JKRHeap(void*, u32, JKRHeap*, bool);

    bool setErrorFlag(bool errorFlag);
    bool isSubHeap(JKRHeap* heap) const;

    virtual ~JKRHeap();
    virtual void callAllDisposer();
    virtual void* do_alloc(u32, int) = 0;
    virtual void do_free(void*) = 0;
    virtual void do_freeAll() = 0;
    virtual void do_freeTail() = 0;
    virtual s32 do_resize(void*, u32) = 0;
    virtual s32 do_getSize(void*) = 0;
    virtual s32 do_getFreeSize() = 0;
    virtual s32 do_getTotalFreeSize() = 0;
    virtual u32 getHeapType() = 0;
    virtual bool check() = 0;
    virtual bool dump_sort() {
        return true;
    }
    virtual bool dump() = 0;
    virtual s32 do_changeGroupID(u8 newGroupID) {
        return 0;
    }
    virtual u8 do_getCurrentGroupId() {
        return 0;
    }
    virtual void state_register(JKRHeap::TState*, u32) const;
    virtual bool state_compare(JKRHeap::TState const&, JKRHeap::TState const&) const;
    virtual void state_dump(JKRHeap::TState const&) const;

    JKRHeap* becomeSystemHeap();
    JKRHeap* becomeCurrentHeap();
    void destroy();
    void* alloc(u32, int);
    void free(void*);
    void freeAll();
    void freeTail();
    void fillFreeArea();
    s32 resize(void*, u32);
    static s32 getSize(void*, JKRHeap*);

    // ... more functions

    s32 getSize(void* ptr);
    s32 getFreeSize();
    void* getMaxFreeBlock();
    s32 getTotalFreeSize();
    u8 getCurrentGroupId();
    s32 changeGroupID(u8 newGroupId);
    u32 getMaxAllocatableSize(int alignment);
    JKRHeap* find(void*) const;        // 0x80084640
    JKRHeap* findAllHeap(void*) const; // 0x8008492c
#ifdef TARGET_PC
    void dispose_subroutine(uintptr_t begin, uintptr_t end);
#else
    void dispose_subroutine(u32 begin, u32 end);
#endif
    bool dispose(void*, u32);   // 0x80084b9c
    void dispose(void*, void*); // 0x80084c2c
    void dispose();             // 0x80084cb8

    void appendDisposer(JKRDisposer* disposer) {
        mDisposerList.append(&disposer->mPointerLinks);
    }

    void removeDisposer(JKRDisposer* disposer) {
        mDisposerList.remove(&disposer->mPointerLinks);
    }

    void setDebugFill(bool debugFill) {
        mDebugFill = debugFill;
    }
    bool getDebugFill() const {
        return mDebugFill;
    }
    void* getStartAddr() const {
        return (void*)mStart;
    }
    void* getEndAddr() const {
        return (void*)mEnd;
    }
    u32 getHeapSize() const {
        return mSize;
    }
    bool getErrorFlag() const {
        return mErrorFlag;
    }
    void callErrorHandler(JKRHeap* heap, u32 size, int alignment) {
        if (mErrorHandler) {
            (*mErrorHandler)(heap, size, alignment);
        }
    }

    // TState related
    static u32 getState_buf_(TState* state) {
        return state->mBuf;
    } // might instead be a pointer to a next state?
    static void setState_u32ID_(TState* state, u32 id) {
        state->mArgument.mId = id;
    }
    static void setState_uUsedSize_(TState* state, u32 usedSize) {
        state->mUsedSize = usedSize;
    }
    static void setState_u32CheckCode_(TState* state, u32 checkCode) {
        state->mCheckCode = checkCode;
    }

    void lock() const {
        OSLockMutex(const_cast<OSMutex*>(&mMutex));
    }
    void unlock() const {
        OSUnlockMutex(const_cast<OSMutex*>(&mMutex));
    }

    JKRHeap* getParent() {
        return mChildTree.getParent()->getObject();
    }

    const JSUTree<JKRHeap>& getHeapTree() {
        return mChildTree;
    }

    // Unused
    void checkMemoryFilled(u8*, u32 size, u8);

    static void destroy(JKRHeap* heap); // fabricated
    static bool initArena(char**, u32*, int);
    static void* alloc(u32, int, JKRHeap*);
    static void copyMemory(void*, void*, u32);
    static void free(void*, JKRHeap*);
    static void state_dumpDifference(const TState&, const TState&);
    static JKRHeap* findFromRoot(void*);
    static JKRHeapErrorHandler* setErrorHandler(JKRHeapErrorHandler*);

    static void* getCodeStart() {
        return mCodeStart;
    }

    static void* getCodeEnd() {
        return mCodeEnd;
    }

    static void* getUserRamStart() {
        return mUserRamStart;
    }

    static void* getUserRamEnd() {
        return mUserRamEnd;
    }

    static u32 getMemorySize() {
        return mMemorySize;
    }

    static JKRHeap* getCurrentHeap() {
        return sCurrentHeap;
    }

    static JKRHeap* getRootHeap() {
        return sRootHeap;
    }

    static JKRHeap* getSystemHeap() {
        return sSystemHeap;
    }

    static void* mCodeStart;
    static void* mCodeEnd;
    static void* mUserRamStart;
    static void* mUserRamEnd;
    static u32 mMemorySize;

    static JKRHeap* sSystemHeap;
    static JKRHeap* sCurrentHeap;
    static JKRHeap* sRootHeap;

    static bool sDefaultFillFlag;
    static bool sDefaultFillCheckFlag;

    static JKRHeapErrorHandler* mErrorHandler;

  protected:
    /* 0x00 */ // vtable
    /* 0x04 */ // JKRDisposer
    /* 0x18 */ OSMutex mMutex;
    /* 0x30 */ void* mStart;
    /* 0x34 */ void* mEnd;
    /* 0x38 */ u32 mSize;
    /* 0x3C */ bool mDebugFill;
    /* 0x3D */ bool mCheckMemoryFilled;
    /* 0x3E */ u8 mAllocationMode; // EAllocMode?
    /* 0x3F */ u8 mGroupId;
    /* 0x40 */ JSUTree<JKRHeap> mChildTree;
    /* 0x5C */ JSUList<JKRDisposer> mDisposerList;
    /* 0x68 */ bool mErrorFlag;
    /* 0x69 */ bool mInitFlag;
    /* 0x6A */ u8 padding_0x6a[2];
};

inline JKRHeap* JKRGetCurrentHeap() {
    return JKRHeap::getCurrentHeap();
}

inline JKRHeap* JKRGetSystemHeap() {
    return JKRHeap::getSystemHeap();
}

inline JKRHeap* JKRGetRootHeap() {
    return JKRHeap::getRootHeap();
}

inline void* JKRAllocFromSysHeap(u32 size, int alignment) {
    return JKRHeap::getSystemHeap()->alloc(size, alignment);
}

inline void* JKRAllocFromHeap(JKRHeap* heap, u32 size, int alignment) {
    return JKRHeap::alloc(size, alignment, heap);
}

inline void JKRFree(void* pBuf) {
    JKRHeap::free(pBuf, nullptr);
}

inline void JKRFreeToHeap(JKRHeap* heap, void* ptr) {
    JKRHeap::free(ptr, heap);
}

inline void JKRFreeToSysHeap(void* buf) {
    JKRHeap::getSystemHeap()->free(buf);
}

void JKRDefaultMemoryErrorRoutine(void*, u32, int);

void* operator new(size_t);
void* operator new(size_t, s32);
void* operator new(size_t, JKRHeap*, int);
inline void* operator new(size_t sz, void* buf) {
    return buf;
} // i believe this is actually part of MSL_C?

void* operator new[](size_t);
void* operator new[](size_t, s32);
void* operator new[](size_t, JKRHeap*, int);

void operator delete(void*);
void operator delete[](void*);

#endif
#endif // !JKRHEAP_H
