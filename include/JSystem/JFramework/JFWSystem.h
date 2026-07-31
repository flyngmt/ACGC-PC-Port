#ifndef _JSYSTEM_JFW_JFWSYSTEM_H
#define _JSYSTEM_JFW_JFWSYSTEM_H

#include <dolphin/gx.h>
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JKernel/JKRThread.h"
#include "JSystem/JUtility/JUTAssertion.h"
#include "JSystem/JUtility/JUTConsole.h"
#include "JSystem/JUtility/JUTDbPrint.h"
#include "JSystem/JUtility/JUTFont.h"
#include "types.h"

// Maybe these are namespaces?
struct JFWSystem {
    struct CSetUpParam {
        static int maxStdHeaps;
        static u32 sysHeapSize;
        static u32 fifoBufSize;
        static u32 aramAudioBufSize;
        static u32 aramGraphBufSize;
        static s32 streamPriority;
        static s32 decompPriority;
        static s32 aPiecePriority;
        static const ResFONT* systemFontRes;
        static const GXRenderModeObj* renderMode;
        static u32 exConsoleBufferSize;
    };

    static void firstInit();
    static void init();

    static JKRHeap* rootHeap;
    static JKRHeap* systemHeap;
    static JKRThread* mainThread;
    static JUTDbPrint* debugPrint;
    static JUTFont* systemFont;
    static JUTConsoleManager* systemConsoleManager;
    static JUTConsole* systemConsole;
    static bool sInitCalled;

    static void setMaxStdHeap(int stdHeaps) {
        JUT_ASSERT(sInitCalled == 0);
        CSetUpParam::maxStdHeaps = stdHeaps;
    }
    static void setSysHeapSize(u32 heapSize) {
        JUT_ASSERT(sInitCalled == 0);
        CSetUpParam::sysHeapSize = heapSize;
    }
    static void setFifoBufSize(u32 bufSize) {
        JUT_ASSERT(sInitCalled == 0);
        CSetUpParam::fifoBufSize = bufSize;
    }
    static void setAramAudioBufSize(u32 bufSize) {
        JUT_ASSERT(sInitCalled == 0);
        CSetUpParam::aramAudioBufSize = bufSize;
    }
    static void setAramGraphBufSize(u32 bufSize) {
        JUT_ASSERT(sInitCalled == 0);
        CSetUpParam::aramGraphBufSize = bufSize;
    }
    static void setRenderMode(const GXRenderModeObj* rmode) {
        JUT_ASSERT(sInitCalled == 0);
        CSetUpParam::renderMode = rmode;
    }
    static JKRHeap* getSystemHeap() {
        JUT_ASSERT(sInitCalled == 0);
        return systemHeap;
    }
    static JKRHeap* getRootHeap() {
        JUT_ASSERT(sInitCalled == 0);
        return rootHeap;
    }
    static JUTConsole* getSystemConsole() {
        JUT_ASSERT(sInitCalled == 0);
        return systemConsole;
    }
};

#endif
