#include <dolphin/vi.h>
#include "JSystem/JUtility/JUTDirectPrint.h"
#include "JSystem/JUtility/JUTVideo.h"
#include "JSystem/JUtility/JUTXfb.h"

JUTVideo* JUTVideo::sManager;
OSTick JUTVideo::sVideoLastTick;
OSTick JUTVideo::sVideoInterval;

bool sDrawWaiting;

JUTVideo* JUTVideo::createManager(const GXRenderModeObj* renderModeObj) {
    if (sManager == nullptr) {
        sManager = JKR_NEW JUTVideo(renderModeObj);
    }
    return sManager;
}

void JUTVideo::destroyManager() {
    if (sManager != nullptr) {
        JKR_DELETE(sManager);
        sManager = nullptr;
    }
}

JUTVideo::JUTVideo(const GXRenderModeObj* renderModeObj) {
    mRenderModeObj = nullptr;
    VIInit();
    setRenderMode(renderModeObj);
    mIsSetBlack = true;
    mSetBlackFrameCount = 2;
    VISetBlack(TRUE);
    VIFlush();
    _08 = 0;
    mRetraceCount = VIGetRetraceCount();
    _10 = 1;
    _18 = 0;
    sVideoLastTick = OSGetTick();
    sVideoInterval = 670000;
    mPreviousPreRetraceCallback = VISetPreRetraceCallback(preRetraceProc);
    mPreviousPostRetraceCallback = VISetPostRetraceCallback(postRetraceProc);
    mPreRetraceCallback = nullptr;
    mPostRetraceCallback = nullptr;
    OSInitMessageQueue(&mMessageQueue, &mMessage, 1);
    GXSetDrawDoneCallback(drawDoneCallback);
}

JUTVideo::~JUTVideo() {
    VISetPreRetraceCallback(mPreviousPreRetraceCallback);
    VISetPostRetraceCallback(mPreviousPostRetraceCallback);
}

void JUTVideo::preRetraceProc(u32 retrace_count) {
    if (sManager->mPreRetraceCallback) {
        (*sManager->mPreRetraceCallback)(retrace_count);
    }

    OSTick tick = OSGetTick();
    sVideoInterval = OSDiffTick(tick, sVideoLastTick);
    sVideoLastTick = tick;

    JUTXfb* xfb = JUTXfb::getManager();
    if (!xfb) {
        VISetBlack(TRUE);
        VIFlush();
        return;
    }

    static void* frameBuffer = nullptr;

    if (frameBuffer) {
        JUTVideo* videoManager = JUTGetVideoManager();
        const GXRenderModeObj* renderMode = videoManager->getRenderMode();
        JUTDirectPrint* directPrint = JUTDirectPrint::getManager();
        directPrint->changeFrameBuffer(frameBuffer, renderMode->fbWidth, renderMode->efbHeight);
    }

    if (sManager->mIsSetBlack == 1) {
        s32 frame_count = sManager->mSetBlackFrameCount;
        if (frame_count > 0) {
            frame_count--;
        }

        sManager->mSetBlackFrameCount = frame_count;
        sManager->mIsSetBlack = frame_count != 0 ? true : false;
        VISetBlack(TRUE);
        VIFlush();
        return;
    }

    if (!xfb) {
        VISetBlack(TRUE);
        VIFlush();
        return;
    }

    if (xfb->getBufferNum() == 3 || xfb->getBufferNum() == 2) {
        if (!sDrawWaiting) {
            s16 index = xfb->getDrawnXfbIndex();
            xfb->setDisplayingXfbIndex(index);
            if (index < 0) {
                VISetBlack(TRUE);
                VIFlush();
            } else {
                VISetBlack(FALSE);
                VISetNextFrameBuffer(xfb->getDisplayingXfb());
                VIFlush();
                frameBuffer = xfb->getDisplayingXfb();
            }
        }
    } else if (xfb->getBufferNum() == 1) {
        if (xfb->getSDrawingFlag() == 0) {
            s16 index = xfb->getDrawnXfbIndex();
            if (index >= 0) {
                xfb->setDisplayingXfbIndex(index);
                GXCopyDisp(xfb->getDisplayingXfb(), GX_TRUE);
                GXFlush();
                xfb->setSDrawingFlag(2);
                frameBuffer = xfb->getDisplayingXfb();
                VISetBlack(FALSE);

            } else {
                VISetBlack(TRUE);
            }
        }
        VIFlush();
    }
}

void JUTVideo::drawDoneStart() {
    sDrawWaiting = true;
    GXSetDrawDone();
}

void JUTVideo::dummyNoDrawWait() {
    sDrawWaiting = false;
}

void JUTVideo::drawDoneCallback() {
    JUTXfb* xfb = JUTXfb::getManager();
    if (!xfb) {
        return;
    }

    sDrawWaiting = false;

    if (xfb->getBufferNum() == JUTXfb::SingleBuffer && xfb->getSDrawingFlag() == 1) {
        xfb->setSDrawingFlag(0);
        if (xfb->getDrawnXfb()) {
            VISetNextFrameBuffer(xfb->getDrawnXfb());
            VIFlush();
        }
    }
}

void JUTVideo::postRetraceProc(u32 p1) {
    if (sManager->mPostRetraceCallback != nullptr) {
        sManager->mPostRetraceCallback(p1);
    }
    u32 retraceCount = VIGetRetraceCount();
    OSSendMessage(&sManager->mMessageQueue, (void*)(uintptr_t)retraceCount, OS_MESSAGE_NOBLOCK);
}

void JUTVideo::setRenderMode(const GXRenderModeObj* newRenderModeObj) {
    if (mRenderModeObj && newRenderModeObj->viTVmode != mRenderModeObj->viTVmode) {
        mIsSetBlack = true;
        mSetBlackFrameCount = 4;
    }

    mRenderModeObj = (GXRenderModeObj*)newRenderModeObj;
    VIConfigure(mRenderModeObj);
    VIFlush();

    if (mIsSetBlack) {
        VIWaitForRetrace();
        VIWaitForRetrace();
    }
}

void JUTVideo::waitRetraceIfNeed() {
}

VIRetraceCallback JUTVideo::setPreRetraceCallback(VIRetraceCallback newCB) {
    VIRetraceCallback oldCB = mPreRetraceCallback;
    mPreRetraceCallback = newCB;
    return oldCB;
}

VIRetraceCallback JUTVideo::setPostRetraceCallback(VIRetraceCallback newCB) {
    VIRetraceCallback oldCB = mPostRetraceCallback;
    mPostRetraceCallback = newCB;
    return oldCB;
}
