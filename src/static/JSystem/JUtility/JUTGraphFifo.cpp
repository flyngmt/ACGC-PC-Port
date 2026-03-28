#include <dolphin/gx.h>
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JUtility/JUTGraphFifo.h"

bool JUTGraphFifo::sInitiated;
JUTGraphFifo* JUTGraphFifo::sCurrentFifo;
GXBool JUTGraphFifo::mGpStatus[5];

JUTGraphFifo::JUTGraphFifo(u32 size) {
    mSize = ALIGN_NEXT(size, 32);
    if (sInitiated) {
        mFifo = (GXFifoObj*)JKRAllocFromSysHeap(mSize + sizeof(GXFifoObj), 32);
        mBase = mFifo + 1;
        GXInitFifoBase(mFifo, mBase, mSize);
        GXInitFifoPtrs(mFifo, mBase, mBase);
    } else {
        /** TODO: Figure out what has sizeof 0xA0. */
        mBase = JKRAllocFromSysHeap(mSize + 0xA0, 32);
#ifdef TARGET_PC
        mBase = (void*)ALIGN_NEXT((uintptr_t)mBase, 32);
#else
        mBase = (void*)ALIGN_NEXT((u32)mBase, 32);
#endif
        mFifo = GXInit(mBase, mSize);
        sInitiated = true;
        sCurrentFifo = this;
    }
}

JUTGraphFifo::~JUTGraphFifo() {
    sCurrentFifo->save();

    while (isGPActive()) {
        ;
    }

    if (sCurrentFifo == this) {
        sCurrentFifo = nullptr;
    }

    JKRFreeToSysHeap(mBase);
}
