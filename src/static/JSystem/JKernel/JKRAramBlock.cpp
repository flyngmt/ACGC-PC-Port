#include "JSystem/JKernel/JKRAram.h"

#ifdef TARGET_PC
JKRAramBlock::JKRAramBlock(uintptr_t address, u32 size, u32 freeSize, u8 groupID, bool tempMemory)
#else
JKRAramBlock::JKRAramBlock(u32 address, u32 size, u32 freeSize, u8 groupID, bool tempMemory)
#endif
    : mLink(this), mAddress(address), mSize(size), mFreeSize(freeSize), mGroupID(groupID), mIsTempMemory(tempMemory) {
}

JKRAramBlock::~JKRAramBlock() {
    JSULink<JKRAramBlock>* prev = this->mLink.getPrev();
    JSUList<JKRAramBlock>* list = this->mLink.getList();

    if (prev) {
        prev->getObject()->mFreeSize += this->mSize + this->mFreeSize;
        list->remove(&this->mLink);
    } else {
        this->mFreeSize += this->mSize;
        this->mSize = 0;
    }
}

JKRAramBlock* JKRAramBlock::allocHead(u32 size, u8 groupID, JKRAramHeap* heap) {
#ifdef TARGET_PC
    uintptr_t address = this->mAddress + this->mSize;
#else
    u32 address = this->mAddress + this->mSize;
#endif
    u32 freeSize = this->mFreeSize - size;

    JKRAramBlock* block = new (heap->mHeap, 0) JKRAramBlock(address, size, freeSize, groupID, false);
    this->mFreeSize = 0;
    this->mLink.mPtrList->insert(this->mLink.mNext, &block->mLink);
    return block;
}

JKRAramBlock* JKRAramBlock::allocTail(u32 size, u8 groupID, JKRAramHeap* heap) {
#ifdef TARGET_PC
    uintptr_t address = this->mAddress + this->mSize + this->mFreeSize - size;
#else
    u32 address = this->mAddress + this->mSize + this->mFreeSize - size;
#endif

    JKRAramBlock* block = new (heap->mHeap, 0) JKRAramBlock(address, size, 0, groupID, true);
    this->mFreeSize -= size;
    this->mLink.mPtrList->insert(this->mLink.mNext, &block->mLink);
    return block;
}
