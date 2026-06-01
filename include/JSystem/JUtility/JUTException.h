#ifndef _JSYSTEM_JUT_JUTEXCEPTION_H
#define _JSYSTEM_JUT_JUTEXCEPTION_H

#include <dolphin/os.h>
#include "JSystem/JKernel/JKRThread.h"
#include "JSystem/JSupport/JSUList.h"
#include "JSystem/JUtility/JUTGamePad.h"
#include "JSystem/JUtility/JUTXfb.h"
#include "types.h"

struct JUTConsole;
struct JUTDirectPrint;

typedef void (*JUTErrorHandler)(OSError error, OSContext* context, u32 dsisr, u32 dar);

enum ExPrintFlags {
    EXPRINTFLAG_GPR = 0x1,
    EXPRINTFLAG_GPRMap = 0x2,
    EXPRINTFLAG_Float = 0x4,
    EXPRINTFLAG_Stack = 0x8,
    EXPRINTFLAG_All = 0xFF,
};

/**
 * @size{0xA4}
 */
struct JUTException : public JKRThread {
    enum EInfoPage {
        INFOPAGE_GPR = 1,
        INFOPAGE_Float = 2,
        INFOPAGE_Stack = 3,
        INFOPAGE_GPRMap = 4,

    };

    // size: 0x14
    struct JUTExMapFile {
        inline JUTExMapFile(const char* fileName) : mLink(this) {
            mFileName = (char*)fileName;
        }

        char* mFileName;             // _00
        JSULink<JUTExMapFile> mLink; // _04
    };

    /** @fabricated */
    struct ExCallbackObject {
        JUTErrorHandler mErrorHandler; // _00
        s32 mError;                    // _04
        OSContext* mContext;           // _08
        u32 _0C;                       // _0C
        u32 _10;                       // _10
    };

    JUTException(JUTDirectPrint*); // unused/inlined

    virtual ~JUTException() {}; // _08 (weak)
    virtual void* run();        // _0C

    void showFloat(OSContext*);
    void showStack(OSContext*);
    void showMainInfo(u16, OSContext*, u32, u32);
    bool showMapInfo_subroutine(u32, bool);
    void showGPRMap(OSContext*);
    void printDebugInfo(JUTException::EInfoPage, u16, OSContext*, u32, u32);
    bool readPad(u32*, u32*);
    void printContext(u16, OSContext*, u32, u32);
    void createFB();

#ifdef TARGET_PC
    static void waitTime(s32);
#else
    static void waitTime(long);
#endif
    static JUTErrorHandler setPreUserCallback(JUTErrorHandler);
    static void appendMapFile(const char*);
#ifdef TARGET_PC
    static bool queryMapAddress(char*, u32, s32, u32*, u32*, char*, u32, bool, bool);
    static bool queryMapAddress_single(char*, u32, s32, u32*, u32*, char*, u32, bool, bool);
#else
    static bool queryMapAddress(char*, u32, long, u32*, u32*, char*, u32, bool, bool);
    static bool queryMapAddress_single(char*, u32, long, u32*, u32*, char*, u32, bool, bool);
#endif

    static JUTException* create(JUTDirectPrint*);
    static void createConsole(void* buffer, u32 bufferSize);
    static void panic_f(const char* file, int line, const char* msg, ...);
    static void errorHandler(u16, OSContext*, u32, u32);
    static void setFPException(u32);
    static bool searchPartialModule(u32, u32*, u32*, u32*, u32*);

    // unused/inlined:
    static void panic_f_va(const char*, int, const char*, va_list);
    static JUTErrorHandler setPostUserCallback(JUTErrorHandler);

    // Inline
    static void panic(const char* file, int line, const char* msg) {
        panic_f(file, line, "%s", msg);
    }

    void showFloatSub(int, f32);
    void showGPR(OSContext*);
    void showSRR0Map(OSContext*);
    bool isEnablePad() const;
    static u32 getFpscr();
    void setFpscr(u32);
    void enableFpuException();
    void disableFpuException();

    JUTExternalFB* getFrameMemory() const {
        return mFrameMemory;
    }

    void setTraceSuppress(u32 supress) {
        mTraceSuppress = supress;
    }

    void setGamePad(JUTGamePad* gamePad) {
        mGamePad = gamePad;
        mPadPort = JUTGamePad::Port_Invalid;
    }

    void enterAllPad() {
        setGamePad((JUTGamePad*)-1);
    }

    static JUTException* getManager() {
        return sErrorManager;
    }
    static JUTConsole* getConsole() {
        return sConsole;
    }

    static JUTConsole* sConsole;
    static void* sConsoleBuffer;
    static size_t sConsoleBufferSize;
    static JUTException* sErrorManager;
    static OSMessageQueue sMessageQueue;
    static void* sMessageBuffer[1];
    static JUTErrorHandler sPreUserCallback;
    static JUTErrorHandler sPostUserCallback;
    static u32 msr;
    static u32 fpscr;
    static const char* sCpuExpName[16];
    static JSUList<JUTExMapFile> sMapFileList;

    // _00     = VTBL
    // _00-_7C = JKRThread
    JUTExternalFB* mFrameMemory;   // _7C
    JUTDirectPrint* mDirectPrint;  // _80
    JUTGamePad* mGamePad;          // _84
    JUTGamePad::EPadPort mPadPort; // _88
    int mPrintWaitTime0;           // _8C
    int mPrintWaitTime1;           // _90
    u32 mTraceSuppress;            // _94
    u32 _98;                       // _98
    u32 mPrintFlags;               // _9C, see ExPrintFlags enum
};

#endif
