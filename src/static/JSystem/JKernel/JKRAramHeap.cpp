#include "JSystem/JKernel/JKRAram.h"
#include "JSystem/JSystem.h"
#include "dolphin/os.h" /* TODO: OSReport is actually in libforest */

JSUList<JKRAramBlock> JKRAramHeap::sAramList;

#ifdef TARGET_PC
JKRAramHeap::JKRAramHeap(uintptr_t baseAddress, u32 size) : JKRDisposer() {
#else
JKRAramHeap::JKRAramHeap(u32 baseAddress, u32 size) : JKRDisposer() {
#endif
    OSInitMutex(&this->mMutex);
    this->mHeap = JKRHeap::findFromRoot(this);
    this->mSize = ALIGN_PREV(size, 0x20);
    this->mHeadAddress = ALIGN_NEXT(baseAddress, 0x20);
    this->mTailAddress = this->mHeadAddress + this->mSize;
    this->mGroupID = 0xFF;
    JKRAramBlock* block = new (this->mHeap, 0) JKRAramBlock(this->mHeadAddress, 0, this->mSize, 0xFF, false);
    sAramList.append(&block->mLink);
}

JKRAramHeap::~JKRAramHeap() {
    for (JSUListIterator<JKRAramBlock> it = sAramList.getFirst(); it != sAramList.getEnd();) {
        delete (it++).getObject();
    }
}

JKRAramBlock* JKRAramHeap::alloc(u32 size, JKRAramHeap::EAllocMode mode) {
    JKRAramBlock* block;
    this->lock();

    if (mode == Head) {
        block = this->allocFromHead(size);
    } else {
        block = this->allocFromTail(size);
    }

    this->unlock();
    return block;
}

/* Code retrieved from Twilight Princess Debug version & matched. Unused in AC.
 */
void JKRAramHeap::free(JKRAramBlock* block) {
    delete block;
}

JKRAramBlock* JKRAramHeap::allocFromHead(u32 size) {
    size = ALIGN_NEXT(size, 32);
    u32 min_size = 0xFFFFFFFFU;
    JKRAramBlock* block = nullptr;

    for (JSUListIterator<JKRAramBlock> it = sAramList.getFirst(); it != sAramList.getEnd(); it++) {
        JKRAramBlock* n_block = it.getObject();
        if (n_block->mFreeSize >= size && min_size > n_block->mFreeSize) {
            min_size = n_block->mFreeSize;
            block = n_block;
            if (block->mFreeSize == size) {
                break;
            }
        }
    }

    if (block != nullptr) {
        return block->allocHead(size, this->mGroupID, this);
    }

    return nullptr;
}

JKRAramBlock* JKRAramHeap::allocFromTail(u32 size) {
    JKRAramBlock* block = nullptr;
    size = ALIGN_NEXT(size, 32);

    for (JSUListIterator<JKRAramBlock> it = sAramList.getLast(); it != sAramList.getEnd(); it--) {
        JKRAramBlock* n_block = it.getObject();

        if (n_block->mFreeSize >= size) {
            block = n_block;
            break;
        }
    }

    if (block != nullptr) {
        return block->allocTail(size, this->mGroupID, this);
    }

    return nullptr;
}

/* Debug code retrieved from Twilight Princess Debug version */
void JKRAramHeap::dump() {
    this->lock();

    int total_used = 0;
    JREPORT("\nJKRAramHeap dump\n");
    JREPORT(" attr  address:   size    gid\n");

    for (JSUListIterator<JKRAramBlock> listItr = sAramList.getFirst(); listItr != sAramList.getEnd(); listItr++) {
        if (listItr->mSize != 0) {
            JREPORTF("%s %08x: %08x  %3d\n", listItr->isTempMemory() ? " temp" : "alloc", listItr->mAddress,
                     listItr->mSize, listItr->mGroupID);
        }

        if (listItr->mFreeSize != 0) {
            JREPORTF(" free %08x: %08x    0\n", listItr->mAddress + listItr->mSize, listItr->mFreeSize);
        }

        total_used += listItr->mSize;
    }

    JREPORTF("%d / %d bytes (%6.2f%%) used\n", total_used, this->mSize, (f32)total_used / (f32)this->mSize);

    this->unlock();
}

/* Not present in AC, recreated from TP debug. TODO: Check for matching. */
u32 JKRAramHeap::getFreeSize() {
    u32 max_free = 0;
    this->lock();

    for (JSUListIterator<JKRAramBlock> it = sAramList.getFirst(); it != sAramList.getEnd(); it++) {
        if (it->mFreeSize > max_free) {
            max_free = it->mFreeSize;
        }
    }

    this->unlock();
    return max_free;
}

/* Not present in AC, recreated from TP debug. TODO: Check for matching. */
u32 JKRAramHeap::getTotalFreeSize() {
    u32 total_free = 0;
    this->lock();

    for (JSUListIterator<JKRAramBlock> it = sAramList.getFirst(); it != sAramList.getEnd(); it++) {
        total_free += it->mFreeSize;
    }

    this->unlock();
    return total_free;
}

/* Not present in AC, recreated from TP debug. TODO: Check for matching. */
u32 JKRAramHeap::getUsedSize(u8 groupID) {
    u32 total_used = 0;
    this->lock();

    if (groupID == ARAM_GROUP_ID_ALL) {
        total_used = this->mSize - this->getTotalFreeSize();
    } else {
        for (JSUListIterator<JKRAramBlock> it = sAramList.getFirst(); it != sAramList.getEnd(); it++) {
            if (groupID == it->mGroupID) {
                total_used += it->mSize;
            }
        }
    }

    this->unlock();
    return total_used;
}
