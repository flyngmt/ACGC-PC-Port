#include <libc/string.h>
#ifdef TARGET_PC
#include <string.h>
#endif
#include <dolphin/vi.h>
#include "_mem.h"
#include "JSystem/J2D/J2DGrafContext.h"
#include "JSystem/JUtility/JUTAssertion.h"
#include "JSystem/JUtility/JUTConsole.h"
#include "JSystem/JUtility/JUTDbPrint.h"
#include "JSystem/JUtility/JUTVideo.h"
#include "JSystem/JUtility/JUTProcBar.h"
#include "JSystem/JFramework/JFWDisplay.h"

// Sources: https://github.com/zeldaret/tp/blob/master/libs/JSystem/JFramework/JFWDisplay.cpp
// https://github.com/kiwi515/ogws/blob/master/src/egg/core/eggAsyncDisplay.cpp
// gpHang: https://github.com/valentinaslover/paper-mar/blob/master/source/sdk/DEMOInit.c#L280

GC_Mtx e_mtx = { { 1.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f, 0.0f } };

JFWDisplay* JFWDisplay::sManager;

extern void JFWThreadAlarmHandler(OSAlarm*, OSContext*);
extern void JFWGXAbortAlarmHandler(OSAlarm*, OSContext*);
void waitForTick(u32, u16);
void diagnoseGpHang();

inline void JFWDrawDoneAlarm() {
    OSAlarm alarm;
    OSCreateAlarm(&alarm);
    OSSetAlarm(&alarm, (OS_TIMER_CLOCK), JFWGXAbortAlarmHandler);
    GXDrawDone();
    OSCancelAlarm(&alarm);
}

void JFWDisplay::ctor_subroutine(const GXRenderModeObj* rmode, bool enableAlpha) {
    mEnableAlpha = enableAlpha;
    mClamp = GX_CLAMP_TOP | GX_CLAMP_BOTTOM;
    mClearColor.set(0, 0, 0, 0);

    mZClear = 0xFFFFFF;
    mRMode = (rmode) ? rmode : JUTVideo::sManager->getRenderMode();

    mGamma = 0;
    mFader = nullptr;
    mFrameRate = 1;
    mTickRate = 0;
    mCombinationRatio = 0.0f;

    mFrameTime = 0;
    mStartTick = OSGetTick();
    mVideoFrameTime = 0;
    mDrawingXfbNo = 0;
    mIsSingleXfb = false;
    mDrawDoneMethod = UNK_METHOD_0;
    clearEfb_init();
    JUTProcBar::create();
    JUTProcBar::clear();
}

JFWDisplay::JFWDisplay(const _GXRenderModeObj* rmode, JKRHeap* heap, JUTXfb::EXfbNumber bufferCount, bool p3) {
    ctor_subroutine(rmode, p3);
    mXfb = JUTXfb::createManager(rmode, heap, bufferCount);
}

JFWDisplay::~JFWDisplay() {
    waitBlanking(2);
    JUTProcBar::destroy();
    JUTXfb::destroyManager();
}

JFWDisplay* JFWDisplay::createManager(const GXRenderModeObj* rmode, JKRHeap* heap, JUTXfb::EXfbNumber bufferCount,
                                      bool p4) {
    JUT_CONFIRM_MESSAGE(sManager == 0);

    if (sManager == nullptr)
        sManager = new JFWDisplay(rmode, heap, bufferCount, p4);

    return sManager;
}

void JFWDisplay::destroyManager() {
    JUT_CONFIRM_MESSAGE(sManager);
    delete sManager;
    sManager = nullptr;
}

void callDirectDraw() {
    JUTChangeFrameBuffer(JUTXfb::getManager()->getDrawingXfb(), JUTVideo::getManager()->getEfbHeight(),
                         JUTVideo::getManager()->getFbWidth());
    JUTAssertion::flushMessage();
}

void JFWDisplay::prepareCopyDisp() {
    GXRenderModeObj* rmode = JUTVideo::getManager()->getRenderMode();
    u16 width = (u16)JUTVideo::getManager()->getFbWidth();
    u16 height = (u16)JUTVideo::getManager()->getEfbHeight();
    u16 xfbHeight = (u16)JUTVideo::getManager()->getXfbHeight();

    GXSetCopyClear(mClearColor, mZClear);
    GXSetDispCopySrc(0, 0, width, height);
    GXSetDispCopyDst(width, xfbHeight);
    GXSetDispCopyYScale(xfbHeight / (f32)height);
    VIFlush();
    GXSetCopyFilter((GXBool)rmode->aa, rmode->sample_pattern, GX_ENABLE, rmode->vfilter);
    GXSetCopyClamp((GXFBClamp)mClamp);
    GXSetDispCopyGamma((GXGamma)mGamma);
    GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
    if (mEnableAlpha) {
        GXSetAlphaUpdate(GX_ENABLE);
    }
}

void JFWDisplay::drawendXfb_single() {
    JUTXfb* manager = JUTXfb::getManager();
    if (manager->getDrawingXfbIndex() >= 0) {
        prepareCopyDisp();
        JFWDrawDoneAlarm();
        GXFlush();
        manager->setDrawnXfbIndex(manager->getDrawingXfbIndex());
    }
}

void JFWDisplay::exchangeXfb_double() {
    JUTXfb* xfbMng = JUTXfb::getManager();

    if (xfbMng->getDrawnXfbIndex() == xfbMng->getDisplayingXfbIndex()) {
        if (xfbMng->getDrawingXfbIndex() >= 0) {
            prepareCopyDisp();
            GXCopyDisp(xfbMng->getDrawingXfb(), GX_TRUE);
            if (mDrawDoneMethod == UNK_METHOD_0) {
                GXDrawDone();
                JUTVideo::dummyNoDrawWait();
            } else {
                JUTVideo::drawDoneStart();
            }

            if (mDrawDoneMethod == UNK_METHOD_0) {
                callDirectDraw();
            }
        }
        int cur_xfb_index = xfbMng->getDrawingXfbIndex();
        xfbMng->setDrawnXfbIndex(cur_xfb_index);
        xfbMng->setDrawingXfbIndex(cur_xfb_index >= 0 ? cur_xfb_index ^ 1 : 0);
    } else {
        clearEfb(JUtility::TColor(0, 0, 0, 0xff));
        if (xfbMng->getDrawingXfbIndex() < 0) {
            xfbMng->setDrawingXfbIndex(0);
        }
    }
}

void JFWDisplay::exchangeXfb_triple() {
    JUTXfb* xfbMng = JUTXfb::getManager();

    if (xfbMng->getDrawingXfbIndex() >= 0) {
        callDirectDraw();
    }

    xfbMng->setDrawnXfbIndex(xfbMng->getDrawingXfbIndex());

    s16 drawing_idx = xfbMng->getDrawingXfbIndex() + 1;
    do {
        if (drawing_idx >= 3 || drawing_idx < 0) {
            drawing_idx = 0;
        }
    } while (drawing_idx == xfbMng->getDisplayingXfbIndex());
    xfbMng->setDrawingXfbIndex(drawing_idx);
}

void JFWDisplay::copyXfb_triple() {
    JUTXfb* xfbMng = JUTXfb::getManager();

    if (xfbMng->getDrawingXfbIndex() >= 0) {
        prepareCopyDisp();
        GXCopyDisp(xfbMng->getDrawingXfb(), GX_TRUE);
        GXPixModeSync();
    }
}

void JFWDisplay::preGX() {
    GXInvalidateTexAll();
    GXInvalidateVtxCache();

    if (mRMode->aa) {
        GXSetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
        GXSetDither(GX_ENABLE);
    } else {
        if (mEnableAlpha) {
            GXSetPixelFmt(GX_PF_RGBA6_Z24, GX_ZC_LINEAR);
            GXSetDither(GX_ENABLE);
        } else {
            GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
            GXSetDither(GX_DISABLE);
        }
    }
}

void JFWDisplay::endGX() {
    u32 width = JUTVideo::getManager()->getFbWidth();
    u32 height = JUTVideo::getManager()->getEfbHeight();

    J2DOrthoGraph ortho(0.0f, 0.0f, width, height, -1.0f, 1.0f);

    if (mFader != nullptr) {
        ortho.setPort();
        mFader->control();
    }

    JUTDbPrint::getManager()->flush();

    if (JUTConsoleManager::getManager() != nullptr) {
        JUTConsoleManager::getManager()->draw();
    }

    ortho.setPort();
    JUTProcBar::getManager()->draw();

    if (mDrawDoneMethod != UNK_METHOD_0 || JUTXfb::getManager()->getBufferNum() == 1) {
        JUTAssertion::flushMessage_dbPrint();
    }
    GXFlush();
}

void JFWDisplay::beginRender() {
    JUTProcBar::getManager()->wholeLoopEnd();
    JUTProcBar::getManager()->wholeLoopStart();
    JUTProcBar::getManager()->idleStart();

    waitForTick(mTickRate, mFrameRate);
    JUTVideo::getManager()->waitRetraceIfNeed();

    u32 tick = OSGetTick();
    mFrameTime = tick - mStartTick;
    mStartTick = tick;
    mVideoFrameTime = mStartTick - JUTVideo::getVideoLastTick();

    JUTProcBar::getManager()->idleEnd();
    JUTProcBar::getManager()->gpStart();

    JUTXfb* xfbMgr = JUTXfb::getManager();
    switch (xfbMgr->getBufferNum()) {
        case 1:
            if (xfbMgr->getSDrawingFlag() != 2) {
                xfbMgr->setSDrawingFlag(1);
                clearEfb(JUtility::TColor(0, 0, 0, 0xff));
            } else {
                xfbMgr->setSDrawingFlag(1);
            }
            xfbMgr->setDrawingXfbIndex(mDrawingXfbNo);
            break;
        case 2:
            exchangeXfb_double();
            break;
        case 3:
            exchangeXfb_triple();
            break;
        default:
            break;
    }

    preGX();
}

void JFWDisplay::endRender() {
    endGX();

    switch (JUTXfb::getManager()->getBufferNum()) {
        case 1:
            drawendXfb_single();
        case 2:
            break;
        case 3:
            copyXfb_triple();
        default:
            break;
    }

    JUTProcBar::getManager()->cpuStart();
    calcCombinationRatio();
}

void JFWDisplay::endFrame() {
    JUTProcBar::getManager()->cpuEnd();
    JUTProcBar::getManager()->gpWaitStart();

    switch (JUTXfb::getManager()->getBufferNum()) {
        case 1:
            break;
        case 2:
            JFWDrawDoneAlarm();
            GXFlush();
            break;
        case 3:
            JFWDrawDoneAlarm();
            GXFlush();
            break;
        default:
            break;
    }

    JUTProcBar::getManager()->gpWaitEnd();
    JUTProcBar::getManager()->gpEnd();

    static u32 prevFrame = VIGetRetraceCount();
    u32 retrace_cnt = VIGetRetraceCount();
    JUTProcBar::getManager()->setCostFrame(retrace_cnt - prevFrame);
    prevFrame = retrace_cnt;
}

void JFWDisplay::waitBlanking(int p1) {
    while (p1-- > 0) {
        waitForTick(mTickRate, mFrameRate);
    }
}

void waitForTick(u32 p1, u16 p2) {
    if (p1 != 0) {
        static s64 nextTick = OSGetTime();
        s64 time = OSGetTime();
        while (time < nextTick) {
            JFWDisplay::getManager()->threadSleep((nextTick - time));
            time = OSGetTime();
        }
        nextTick = time + p1;
    } else {
        static u32 nextCount = VIGetRetraceCount();
        u32 uVar1 = (p2 == 0) ? 1 : p2;
        OSMessage msg;
        do {
            if (!OSReceiveMessage(JUTVideo::getManager()->getMessageQueue(), &msg, OS_MESSAGE_BLOCK)) {
                msg = 0;
            }
        } while (((int)msg - (int)nextCount) < 0);
        nextCount = (int)msg + uVar1;
    }
}

void JFWThreadAlarmHandler(OSAlarm* p_alarm, OSContext* p_ctx) {
    JFWAlarm* alarm = static_cast<JFWAlarm*>(p_alarm);
    OSResumeThread(alarm->getThread());
}

void JFWDisplay::threadSleep(s64 time) {
    JFWAlarm alarm;
    alarm.createAlarm();
    alarm.setThread(OSGetCurrentThread());
    s32 status = OSDisableInterrupts();

    OSSetAlarm(&alarm, time, JFWThreadAlarmHandler);
    OSSuspendThread(alarm.getThread());
    OSRestoreInterrupts(status);
}

static GXTexObj clear_z_tobj;
static u8 clear_z_TX[]
    __attribute__((aligned(32))) = { 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00,
                                     0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff,
                                     0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                     0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                                     0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

void* JFWDisplay::changeToSingleXfb(int index) {
    JUTXfb* xfb = JUTXfb::getManager();
    s16 xfbNo = !index ? 1 : 0;

    // Check if xfb is single buffered
    if (xfb->getBufferNum() != 2) {
        return nullptr;
    }

    if (mIsSingleXfb) {
        return nullptr;
    }

    VIWaitForRetrace();

    if (xfbNo != xfb->getDisplayingXfbIndex()) {
        u32 xfbSize = xfb->accumeXfbSize();
        DCInvalidateRange(xfb->getDrawingXfb(), xfbSize);
        memcpy(xfb->getDrawingXfb(), xfb->getDisplayingXfb(), xfbSize);
        DCStoreRange(xfb->getDrawingXfb(), xfbSize);
        xfb->setDrawnXfbIndex(xfb->getDrawingXfbIndex());
        VISetNextFrameBuffer(xfb->getDrawingXfb());
        VIFlush();
        VIWaitForRetrace();
    }

    xfb->setSDrawingFlag(99);
    xfb->setBufferNum(1);
    mDrawingXfbNo = xfbNo;
    mIsSingleXfb = true;
    return xfb->getXfb(index);
}

void* JFWDisplay::changeToDoubleXfb() {
    JUTXfb* xfb = JUTXfb::getManager();

    // Check if xfb is not single buffered already
    if (!mIsSingleXfb) {
        return nullptr;
    }

    VIWaitForRetrace();
    if (xfb->getSDrawingFlag() != 0) {
        VIWaitForRetrace();
    }

    s16 xfbNo = !mDrawingXfbNo ? 1 : 0;
    xfb->setDrawnXfbIndex(mDrawingXfbNo);
    xfb->setDisplayingXfbIndex(xfbNo);
    xfb->setDrawingXfbIndex(xfbNo);
    xfb->setBufferNum(2);
    mIsSingleXfb = false;
    return xfb->getXfb(xfbNo);
}

void JFWDisplay::clearEfb_init() {
    GXInitTexObj(&clear_z_tobj, &clear_z_TX, 4, 4, GX_TF_Z24X8, GX_REPEAT, GX_REPEAT, GX_FALSE);
    GXInitTexObjLOD(&clear_z_tobj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
}

void JFWDisplay::clearEfb(GXColor color) {
    Mtx44 mtx;
    u16 height = mRMode->efbHeight;
    u16 width = mRMode->fbWidth;

    C_MTXOrtho(mtx, 0.0f, height, 0.0f, width, 0.0f, 1.0f);
    GXSetProjection(mtx, GX_ORTHOGRAPHIC);
    GXSetViewport(0.0f, 0.0f, width, height, 0.0f, 1.0f);
    GXSetScissor(0, 0, width, height);

    GXLoadPosMtxImm(e_mtx, GX_PNMTX0);
    GXSetCurrentMtx(0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGB, GX_RGBX8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_CLR_RGBA, GX_RGB565, 0);
    GXSetNumChans(0);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_COLOR1A1, GX_DISABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 60, GX_DISABLE, 125);
    GXLoadTexObj(&clear_z_tobj, GX_TEXMAP0);
    GXSetNumTevStages(1);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_ENABLE, GX_TEVPREV);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetZTexture(GX_ZT_REPLACE, GX_TF_Z24X8, 0);
    GXSetZCompLoc(GX_DISABLE);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ZERO, GX_LO_NOOP);

    if (mEnableAlpha) {
        GXSetAlphaUpdate(GX_ENABLE);
        GXSetDstAlpha(GX_ENABLE, 0);
    }
    GXSetZMode(GX_ENABLE, GX_ALWAYS, GX_ENABLE);
    GXSetCullMode(GX_CULL_BACK);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition2u16(0, 0);
    GXTexCoord2u8(0, 0);

    GXPosition2u16(0 + width, 0);
    GXTexCoord2u8(1, 0);

    GXPosition2u16(0 + width, 0 + height);
    GXTexCoord2u8(1, 1);

    GXPosition2u16(0, 0 + height);
    GXTexCoord2u8(0, 1);
    GXEnd();

    GXSetZTexture(GX_ZT_DISABLE, GX_TF_Z24X8, 0);
    GXSetZCompLoc(GX_ENABLE);
    if (mEnableAlpha) {
        GXSetDstAlpha(GX_DISABLE, 0);
    }
}

void JFWDisplay::calcCombinationRatio() {
    u32 vidInterval = JUTVideo::getVideoInterval();
    s32 unk30 = mFrameTime * 2;

    s32 i = vidInterval;
    for (; i < unk30; i += vidInterval) {}

    s32 tmp = (i - unk30) - mVideoFrameTime;
    if (tmp < 0) {
        tmp += vidInterval;
    }
    mCombinationRatio = (f32)tmp / (f32)mFrameTime;
    if (mCombinationRatio > 1.0f) {
        mCombinationRatio = 1.0f;
    }
}

void JFWGXAbortAlarmHandler(OSAlarm* param_0, OSContext* param_1) {
    diagnoseGpHang();
    GXAbortFrame();
    GXSetDrawDone();
}

void diagnoseGpHang() {
    u32 xfTop0, xfBot0, suRdy0, r0Rdy0;
    u32 xfTop1, xfBot1, suRdy1, r0Rdy1;
    u32 xfTopD, xfBotD, suRdyD, r0RdyD;
    GXBool readIdle, cmdIdle, junk;

    GXReadXfRasMetric(&xfBot0, &xfTop0, &r0Rdy0, &suRdy0);
    GXReadXfRasMetric(&xfBot1, &xfTop1, &r0Rdy1, &suRdy1);

    xfTopD = (xfTop1 - xfTop0) == 0;
    xfBotD = (xfBot1 - xfBot0) == 0;
    suRdyD = (suRdy1 - suRdy0) > 0;
    r0RdyD = (r0Rdy1 - r0Rdy0) > 0;

    GXGetGPStatus(&junk, &junk, &readIdle, &cmdIdle, &junk);
    OSReport("GP status %d%d%d%d%d%d --> ", readIdle, cmdIdle, xfTopD, xfBotD, suRdyD, r0RdyD);

    if (!xfBotD && suRdyD)
        OSReport("GP hang due to XF stall bug.\n");
    else if (!xfTopD && xfBotD && suRdyD)
        OSReport("GP hang due to unterminated primitive.\n");
    else if (!cmdIdle && xfTopD && xfBotD && suRdyD)
        OSReport("GP hang due to illegal instruction.\n");
    else if (readIdle && cmdIdle && xfTopD && xfBotD && suRdyD && r0RdyD)
        OSReport("GP appears to be not hung (waiting for input).\n");
    else
        OSReport("GP is in unknown state.\n");
}
