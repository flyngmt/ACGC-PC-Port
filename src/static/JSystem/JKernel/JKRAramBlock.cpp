#include "JSystem/JKernel/JKRAram.h"

JKRAramBlock::JKRAramBlock(u32 address, u32 size, u32 freeSize, u8 groupID, bool tempMemory)
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
    u32 address = this->mAddress + this->mSize;
    u32 freeSize = this->mFreeSize - size;

    JKRAramBlock* block = JKR_NEW_ARGS(heap->mHeap, 0) JKRAramBlock(address, size, freeSize, groupID, false);
    this->mFreeSize = 0;
    this->mLink.mPtrList->insert(this->mLink.mNext, &block->mLink);
    return block;
}

JKRAramBlock* JKRAramBlock::allocTail(u32 size, u8 groupID, JKRAramHeap* heap) {
    u32 address = this->mAddress + this->mSize + this->mFreeSize - size;

    JKRAramBlock* block = JKR_NEW_ARGS(heap->mHeap, 0) JKRAramBlock(address, size, 0, groupID, true);
    this->mFreeSize -= size;
    this->mLink.mPtrList->insert(this->mLink.mNext, &block->mLink);
    return block;
}
