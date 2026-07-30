#ifndef JKREXPHEAP_H
#define JKREXPHEAP_H

#include "JSystem/JKernel/JKRHeap.h"
#include "types.h"

#ifdef __cplusplus
class JKRExpHeap : public JKRHeap {
  public:
    class CMemBlock {
      public:
        CMemBlock* allocBack(u32, u8, u8, u8, u8);
        CMemBlock* allocFore(u32, u8, u8, u8, u8);
        void* free(JKRExpHeap*);
        static CMemBlock* getHeapBlock(void*);
        void initiate(CMemBlock*, CMemBlock*, u32, u8, u8);

        void newGroupId(u8 groupId) {
            mGroupID = groupId;
        }
        bool isValid() const {
            return mUsageHeader == 'HM';
        }
        bool _isTempMemBlock() const {
            return (mFlags & 0x80) ? true : false;
        }
        int getAlignment() const {
            return mFlags & 0x7f;
        }
        void* getContent() const {
            return (void*)(this + 1);
        }
        CMemBlock* getPrevBlock() const {
            return mPrev;
        }
        CMemBlock* getNextBlock() const {
            return mNext;
        }
        u32 getSize() const {
            return mAllocatedSpace;
        }
        u8 getGroupId() const {
            return mGroupID;
        }
        static CMemBlock* getBlock(void* data) {
            return ((CMemBlock*)data) - 1;
        }

        u16 mUsageHeader;    // _00
        u8 mFlags;           // _02, a|bbbbbbb = a=temp, b=aln
        u8 mGroupID;         // _03
        int mAllocatedSpace; // _04
        CMemBlock* mPrev;    // _08
        CMemBlock* mNext;    // _0C
    };

    JKRExpHeap(void*, u32, JKRHeap*, bool);

    virtual ~JKRExpHeap();                                          // _08
    virtual void* do_alloc(u32, int);                               // _10
    virtual void do_free(void*);                                    // _14
    virtual void do_freeTail();                                     // _18
    virtual void do_freeAll();                                      // _1C
    virtual s32 do_resize(void*, u32);                              // _20
    virtual s32 do_getSize(void*);                                  // _24
    virtual s32 do_getFreeSize();                                   // _28
    virtual s32 do_getTotalFreeSize();                              // _2C
    virtual bool check();                                           // _34
    virtual bool dump_sort();                                       // _38
    virtual bool dump();                                            // _3C
    virtual s32 do_changeGroupID(u8);                               // _40
    virtual void state_register(TState*, u32) const;                // _48
    virtual bool state_compare(const TState&, const TState&) const; // _4C

    virtual u8 do_getCurrentGroupId() {
        return mCurrentGroupID;
    } // _44 (weak)
    virtual u32 getHeapType() {
        return 'EXPH';
    } // _30 (weak)

    void* allocFromHead(u32, int);
    void* allocFromHead(u32);
    void* allocFromTail(u32, int);
    void* allocFromTail(u32);
    void appendUsedList(CMemBlock*);
    static JKRExpHeap* create(u32, JKRHeap*, bool);
    static JKRExpHeap* create(void*, u32, JKRHeap*, bool);
    static JKRExpHeap* createRoot(int, bool);
    int freeGroup(u8 groupID);
    void joinTwoBlocks(CMemBlock*);
    void recycleFreeBlock(CMemBlock*);
    void removeFreeBlock(CMemBlock*);
    void setFreeBlock(CMemBlock*, CMemBlock*, CMemBlock*);

    // unused/inlined:
    void removeUsedBlock(CMemBlock*);
    bool isEmpty();
    s32 getUsedSize(u8 groupId) const;

    CMemBlock* getHeadUsedList() const {
        return mHeadUsedList;
    }
    void setAllocationMode(EAllocMode mode) {
        mCurrentAllocMode = mode;
    }

    static s32 getUsedSize_(JKRExpHeap* expHeap) {
        // s32 totalFreeSize = expHeap->getTotalFreeSize();
        return expHeap->mSize - expHeap->getTotalFreeSize();
    }
    static u32 getState_(TState* state) {
        return getState_buf_(state);
    } // might instead be a pointer to a next state?

  private:
    // _00     = VTBL
    // _00-_6C = JKRHeap
    u8 mCurrentAllocMode;     // _6C
    u8 mCurrentGroupID;       // _6D
    u8 _6E;                   // _6E
    void* _70;                // _70
    u32 _74;                  // _74
    CMemBlock* mHead;         // _78, free list
    CMemBlock* mTail;         // _7C, free list
    CMemBlock* mHeadUsedList; // _80
    CMemBlock* mTailUsedList; // _84
};

inline JKRExpHeap* JKRCreateExpHeap(u32 size, JKRHeap* parent, bool errorFlag) {
    return JKRExpHeap::create(size, parent, errorFlag);
}
#endif

#endif /* JKREXPHEAP_H */
