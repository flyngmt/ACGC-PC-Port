#ifndef _JSYSTEM_JFW_JFWDISPLAY_H
#define _JSYSTEM_JFW_JFWDISPLAY_H

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JUtility/JUTDirectPrint.h"
#include "JSystem/JUtility/JUTFader.h"
#include "JSystem/JUtility/JUTProcBar.h"
#include "JSystem/JUtility/JUTVideo.h"
#include "JSystem/JUtility/JUTXfb.h"
#include "JSystem/JUtility/TColor.h"
#include "types.h"

typedef void (*JFWDisplayUnkFunc)(void);

extern Mtx e_mtx;

class JFWAlarm : public OSAlarm { // everything here seems to be auto inlined or unused
  public:
    // Contructor and Destructor are both present in map but unused, not sure if it belongs here
    JFWAlarm() {
    }
    ~JFWAlarm() {
    }
    void createAlarm() {
        OSCreateAlarm(this);
    }
    void cancelAlarm() {
        OSCancelAlarm(this);
    }

    OSThread* getThread() const {
        return mThread;
    }
    void setThread(OSThread* thread) {
        mThread = thread;
    }

    static JSUList<JFWAlarm> sList; //

  public:
    /* 0x28 */ OSThread* mThread;
};

class JFWDisplay {
  public:
    enum EDrawDone {
        /* 0x0 */ UNK_METHOD_0 = 0,
        /* 0x1 */ UNK_METHOD_1 = 1
    };

    static JFWDisplay* createManager(const GXRenderModeObj*, JKRHeap*, JUTXfb::EXfbNumber, bool); // 0x80015bfc
    void waitBlanking(int);                                                                        // 0x8001684c
    void threadSleep(s64);                                                                         // 0x800169fc
    void clearEfb_init();                                                                          // 0x80016ab8
    void clearEfb();                                                                               // 0x80016b2c
    void clearEfb(GXColor);                                                                        // 0x80016b58
    void clearEfb(int, int, int, int, GXColor);                                                    // 0x80016b9c
    void calcCombinationRatio();                                                                   // 0x80016f0c

    void ctor_subroutine(const GXRenderModeObj*, bool);
    JFWDisplay(const GXRenderModeObj*, JKRHeap*, JUTXfb::EXfbNumber, bool);

    static void destroyManager();
    void prepareCopyDisp();
    void drawendXfb_single();
    void exchangeXfb_double();
    void exchangeXfb_triple();
    void copyXfb_triple();
    void preGX();
    void endGX();
    void* changeToSingleXfb(int);
    void* changeToDoubleXfb();

    // UNUSED
    JFWDisplay(void*, bool);
    JFWDisplay(void*, void*, bool);
    JFWDisplay(void*, void*, void*, bool);
    void createManager(const GXRenderModeObj*, void*, bool);
    void createManager(const GXRenderModeObj*, void*, void*, bool);
    void createManager(const GXRenderModeObj*, void*, void*, void*, bool);
    void deleteToSingleXfb(int);
    void deleteToSingleXfb(void*);
    void addToDoubleXfb(void*, bool);
    void addToDoubleXfb(JKRHeap*);
    void clearAllXfb();
    s32 frameToTick(float);
    static void setForOSResetSystem();

    // Virtual functions
    virtual void beginRender(); // 0x80015e0c
    virtual void endRender();   // 0x8001633c
    virtual void endFrame();    // 0x8001669c
    virtual ~JFWDisplay();      // 0x80015b80

    static JFWDisplay* getManager() {
        return sManager;
    }

    const GXRenderModeObj* getRenderMode() const {
        return mRMode;
    }

    int getEfbHeight() const {
        return getRenderMode() ->efbHeight;
    }

    int getEfbWidth() const {
        return getRenderMode() ->fbWidth;
    }

    JUTFader* getFader() const {
        return mFader;
    }
    void setFader(JUTFader* fader) {
        mFader = fader;
    }

    bool startFadeOut(int duration) {
        if (mFader != nullptr) {
            return mFader->startFadeOut(duration);
        }
        return true;
    }

    bool startFadeIn(int duration) {
        if (mFader != nullptr) {
            return mFader->startFadeIn(duration);
        }
        return true;
    }

    void setTickRate(u32 rate) {
        mTickRate = rate;
        mFrameRate = 0;
    }
    JUtility::TColor getClearColor() const {
        return mClearColor;
    }

    void setClearColor(u8 r, u8 g, u8 b, u8 a) {
        mClearColor.set(r, g, b, a);
    }

    void setClearColor(JUtility::TColor color) {
        mClearColor = color;
    }

    void setFBAlpha(bool enable) {
        mEnableAlpha = enable;
    }

    bool getFBAlpha() {
        return mEnableAlpha;
    }

    void setGamma(u16 gamma) {
        mGamma = gamma;
    }

    void setFrameRate(u16 framerate) {
        mFrameRate = framerate;
        mTickRate = 0;
    }

    static JFWDisplay* sManager; // 0x80415718

  private:
    JUTFader* mFader;              // 04
    const GXRenderModeObj* mRMode; // 08
    JUtility::TColor mClearColor;  // 0c
    u32 mZClear;                   // 10
    JUTXfb* mXfb;                  // 14
    u16 mGamma;                    // 18
    EDrawDone mDrawDoneMethod;     // 1c
    u16 mFrameRate;                // 20
    u32 mTickRate;                 // 24
    bool mEnableAlpha;             // 28
    u16 mClamp;                    // 2a
    f32 mCombinationRatio;         // 2c
    u32 mStartTick;                // 30, tick of when the frame starts rendering
    u32 mFrameTime;                // 34, time it took to render a frame/amount of ticks beginRender took
    u32 mVideoFrameTime;           // 38, time between mStartTick and the last Video Tick
    s16 mDrawingXfbNo;             // 3c
    bool mIsSingleXfb;             // 3e
};

#endif
