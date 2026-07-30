#include <dolphin/gx.h>
#include <dolphin/vi.h>
#include "JSystem/JUtility/JUTAssertion.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JUtility/JUTVideo.h"
#include "JSystem/JUtility/JUTXfb.h"

JUTXfb* JUTXfb::sManager;

void JUTXfb::clearIndex() {
    mDrawingXfbIndex = -1;
    mDrawnXfbIndex = -1;
    mDisplayingXfbIndex = -1;
}

void JUTXfb::common_init(int xfbNum) {
    mBufferNum = xfbNum;
    clearIndex();
    mSDrawingFlag = 99;
}

JUTXfb::JUTXfb(const GXRenderModeObj* rmode, JKRHeap* heap, JUTXfb::EXfbNumber number) {
    common_init(number);

    if (rmode) {
        initiate(rmode->fbWidth, rmode->xfbHeight, heap, number);
    } else {
        u16 efbWidth = JUTVideo::getManager()->getRenderMode()->fbWidth;
        u16 xfbHeight = JUTVideo::getManager()->getRenderMode()->xfbHeight;
        u16 efbHeight = JUTVideo::getManager()->getRenderMode()->efbHeight;

        initiate(efbWidth, xfbHeight, heap, number);
    }
}

JUTXfb::~JUTXfb() {
    for (int i = 0; i < 3; i++) {
        delXfb(i);
    }
    sManager = nullptr;
}

void JUTXfb::delXfb(int xfbIdx) {
    if (mXfbAllocated[xfbIdx] && mBuffer[xfbIdx]) {
        delete mBuffer[xfbIdx];
    }
}

JUTXfb* JUTXfb::createManager(const GXRenderModeObj* rmode, JKRHeap* heap, JUTXfb::EXfbNumber number) {
    JUT_CONFIRM_MESSAGE(sManager == 0);
    if (sManager == nullptr) {
        sManager = JKR_NEW JUTXfb(rmode, heap, number);
    }
    return sManager;
}

void JUTXfb::destroyManager() {
    JUT_CONFIRM_MESSAGE(sManager);
    delete sManager;
    sManager = nullptr;
}

void JUTXfb::initiate(u16 w, u16 h, JKRHeap* heap, JUTXfb::EXfbNumber number) {
    if (heap == nullptr) {
        heap = JKRGetSystemHeap();
    }

    u32 size = (u16)ALIGN_NEXT((u16)w, 16) * h;

    mBuffer[0] = new (heap, 32) u16[size];
    mXfbAllocated[0] = true;
    if (number >= DoubleBuffer) {
        mBuffer[1] = new (heap, 32) u16[size];
        mXfbAllocated[1] = true;
    } else {
        mBuffer[1] = nullptr;
        mXfbAllocated[1] = false;
    }

    if (number >= TripleBuffer) {
        mBuffer[2] = new (heap, 32) u16[size];
        mXfbAllocated[2] = true;
    } else {
        mBuffer[2] = nullptr;
        mXfbAllocated[2] = false;
    }
}

u32 JUTXfb::accumeXfbSize() {
    JUTVideo* video = JUTVideo::getManager();
    u16 height = video->getXfbHeight();
    u16 width = video->getFbWidth();
    return (u16)ALIGN_NEXT(width, 16) * height * 2;
}
