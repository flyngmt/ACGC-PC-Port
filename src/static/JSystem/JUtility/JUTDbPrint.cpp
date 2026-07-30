#include "MSL_C/printf.h"
#include "JSystem/JUtility/JUTDbPrint.h"
#include "JSystem/J2D/J2DGrafContext.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JUtility/JUTFont.h"
#include "JSystem/JUtility/JUTVideo.h"
#include "types.h"

JUTDbPrint* JUTDbPrint::sDebugPrint;

JUTDbPrint::JUTDbPrint(JUTFont* font, JKRHeap* heap) : mColor() {
    mFont = font;
    mList = nullptr;
    mHeap = (heap) ? heap : JKRHeap::getCurrentHeap();
    mColor = TCOLOR_WHITE;
    mVisible = true;
}

JUTDbPrint::~JUTDbPrint() {
}

JUTDbPrint* JUTDbPrint::start(JUTFont* font, JKRHeap* heap) {
    if (!sDebugPrint) {
        if (!heap) {
            heap = JKRHeap::getCurrentHeap();
        }
        sDebugPrint = JKR_NEW JUTDbPrint(font, heap);
    }
    return sDebugPrint;
}

JUTFont* JUTDbPrint::changeFont(JUTFont* newFont) {
    JUTFont* oldFont = mFont;
    if (newFont) {
        mFont = newFont;
    }
    return oldFont;
}

void JUTDbPrint::enter(int x, int y, int duration, const char* txt, int len) {
    if (len > 0) {
        JUTDbPrintList* pList = (JUTDbPrintList*)JKRAllocFromHeap(mHeap, sizeof(JUTDbPrintList) + len, -4);
        if (pList) {
            pList->mX = x;
            pList->mY = y;
            pList->mDuration = duration;
            pList->mLen = len;
            strcpy((char*)&pList->mStr, txt);
            pList->mNext = mList;
            mList = pList;
        }
    }
}

void JUTDbPrint::flush() {
    // eyebrow raise emoji
    JUTDbPrintList* pList = (JUTDbPrintList*)&mList;
    JUTDbPrintList* currList = mList;

    if (mFont) {
        if (currList) {
            J2DOrthoGraph orthograph(0.0f, 0.0f, 640.0f, 480.0f, -1.0f, 1.0f);
            orthograph.setPort();
            mFont->setGX();
            mFont->setCharColor(mColor);
            while (currList) {
                if (mVisible) {
                    drawString(currList->mX, currList->mY, currList->mLen, &currList->mStr);
                }
                if (--currList->mDuration <= 0) {
                    JUTDbPrintList* next = currList->mNext;
                    JKRFreeToHeap(mHeap, currList);
                    pList->mNext = next;
                    currList = next;
                } else {
                    pList = currList;
                    currList = currList->mNext;
                }
            }
        }
    }
}

void JUTDbPrint::flush(int left, int top, int right, int bottom) {
}

void JUTDbPrint::drawString(int x, int y, int len, const unsigned char* str) {
    mFont->drawString_size(x, y, reinterpret_cast<const char*>(str), len, true);
}

void JUTReport(int x, int y, const char* fmt, ...) {
    va_list vl;
    va_start(vl, fmt);
    char buf[128];
    s32 n = vsnprintf(buf, sizeof(buf), fmt, vl);
    if (n >= 0) {
        JUTDbPrint::getManager()->enter(x, y, 1, buf, n < 256 ? n : 255);
    }
    va_end(vl);
}

void JUTReport(int x, int y, int duration, const char* fmt, ...) {
    va_list vl;
    va_start(vl, fmt);
    char buf[256];
    s32 n = vsnprintf(buf, sizeof(buf), fmt, vl);
    if (n >= 0) {
        JUTDbPrint::getManager()->enter(x, y, duration, buf, n < 256 ? n : 255);
    }
    va_end(vl);
}
