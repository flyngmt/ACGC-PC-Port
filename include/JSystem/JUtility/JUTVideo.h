#ifndef JUTVIDEO_H
#define JUTVIDEO_H

#include "types.h"
#include "dolphin/os/OSTime.h"
#include "dolphin/os.h"
#include "dolphin/gx.h"
#include "dolphin/vi.h"

#ifdef __cplusplus

typedef u8 (*Pattern)[2];

struct JUTVideo {
    JUTVideo(const GXRenderModeObj*);

    virtual ~JUTVideo(); // _08

    static JUTVideo* createManager(const GXRenderModeObj*);
    static void destroyManager();
#ifdef TARGET_PC
    static void preRetraceProc(u32);
    static void postRetraceProc(u32);
#else
    static void preRetraceProc(unsigned long);
    static void postRetraceProc(unsigned long);
#endif
    static void drawDoneCallback();

    u32 getEfbHeight() const {
        return mRenderModeObj->efbHeight;
    }
    u32 getXfbHeight() const {
        return mRenderModeObj->xfbHeight & 0xffff;
    }
    u32 getFbWidth() const {
        return (u16)mRenderModeObj->fbWidth;
    }
    void getBounds(u16& width, u16& height) const {
        width = getFbWidth();
        height = getEfbHeight();
    }
    GXRenderModeObj* getRenderMode() const {
        return mRenderModeObj;
    }
    u32 isAntiAliasing() const {
        return mRenderModeObj->aa;
    }
    Pattern getSamplePattern() const {
        return mRenderModeObj->sample_pattern;
    }
    u8* getVFilter() const {
        return mRenderModeObj->vfilter;
    }
    OSMessageQueue* getMessageQueue() {
        return &mMessageQueue;
    };
    static void drawDoneStart();
    static void dummyNoDrawWait();
    void setRenderMode(const GXRenderModeObj*);
    void waitRetraceIfNeed(); // blr, global
    VIRetraceCallback setPostRetraceCallback(VIRetraceCallback);

    // Unused/inlined:
    void getDrawWait();
    VIRetraceCallback setPreRetraceCallback(VIRetraceCallback);
    void getPixelAspect(const GXRenderModeObj*);
    void getPixelAspect() const;

    // Static inline gets
    static JUTVideo* getManager() {
        return sManager;
    }
    static OSTick getVideoInterval() {
        return sVideoInterval;
    }
    static OSTick getVideoLastTick() {
        return sVideoLastTick;
    }

    // _00 VTBL
    GXRenderModeObj* mRenderModeObj;                // _04
    u32 _08;                                        // _08
    u32 mRetraceCount;                              // _0C
    int _10;                                        // _10
    u8 _14[4];                                      // _14
    u32 _18;                                        // _18
    VIRetraceCallback mPreviousPreRetraceCallback;  // _1C
    VIRetraceCallback mPreviousPostRetraceCallback; // _20
    VIRetraceCallback mPreRetraceCallback;          // _24
    VIRetraceCallback mPostRetraceCallback;         // _28
    bool mIsSetBlack;                               // _2C
    s32 mSetBlackFrameCount;                        // _30
    OSMessage mMessage;                             // _34
    OSMessageQueue mMessageQueue;                   // _38

    static JUTVideo* sManager;
    static OSTick sVideoLastTick;
    static OSTick sVideoInterval;
};

inline JUTVideo* JUTGetVideoManager() {
    return JUTVideo::getManager();
}

extern bool sDrawWaiting;
#endif

#endif
