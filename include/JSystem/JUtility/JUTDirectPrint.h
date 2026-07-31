#ifndef JUTDIRECTPRINT_H
#define JUTDIRECTPRINT_H

#include "types.h"
#ifdef TARGET_PC
#include <stdarg.h>
#else
#include "libc/stdarg.h"
#endif

#ifdef __cplusplus

class JUTDirectPrint {
  private:
    JUTDirectPrint();

  public:
    static JUTDirectPrint* start();
    void erase(int x, int y, int w, int h);
    void drawChar(int, int, int);
    void drawString(u16 x, u16 y, char* text);
    void drawString_f(u16 x, u16 y, const char* text, ...);
    void changeFrameBuffer(void* framebuffer, u16 w, u16 h);
    void printSub(u16, u16, const char*, va_list, bool); // TODO: Function signature
    void print(u16, u16, const char*, ...);

    bool isActive() const {
        return mFramebuffer != nullptr;
    }
    void* getFrameBuffer() {
        return mFramebuffer;
    }

    void changeFrameBuffer(void* fb) {
        changeFrameBuffer(fb, mFbWidth, mFbHeight);
    }

    static JUTDirectPrint* getManager() {
        return sDirectPrint;
    }

  private:
    static u8 sAsciiTable[128];
    static u32 sFontData[64];
    static u32 sFontData2[77];
    static JUTDirectPrint* sDirectPrint;

    void* mFramebuffer; // _00
    u16 mFbWidth;       // _04
    u16 mFbHeight;      // _06
    u16 mStride;        // _08
    size_t mFbSize;     // _0C
    u8 _10[0x4];        // _10 - unknown
    u16* mFrameMemory;  // _14
};

inline void JUTChangeFrameBuffer(void* buffer, u16 height, u16 width) {
    JUTDirectPrint::getManager()->changeFrameBuffer(buffer, width, height);
}
#endif

#endif
