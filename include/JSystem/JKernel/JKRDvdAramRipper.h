#ifndef JKRDVDARAMRIPPER_H
#define JKRDVDARAMRIPPER_H

#include "JSystem/JKernel/JKRAram.h"
#include "JSystem/JKernel/JKRDvdFile.h"
#include "JSystem/JSupport/JSUList.h"
#include "types.h"

#ifdef __cplusplus
class JKRADCommand {
  public:
#ifdef TARGET_PC
    typedef void (*LoadCallback)(uintptr_t);
#else
    typedef void (*LoadCallback)(u32);
#endif
    JKRADCommand();
    ~JKRADCommand();

    // Fields might need more swapping
    JSULink<JKRADCommand> mLink;
    JKRDvdFile* mDvdFile;                 // _28
    u32 _14;                              // _14
    u32 _18;                              // _18, probably size
    u32 _1C;                              // _1C
    JKRAramBlock* mBlock;                 // _20
    JKRExpandSwitch mExpandSwitch;        // _24
    u8 _28[0x10];                         // _28 - unknown/padding
    u32* _3C;                             // _3C
    s32 _40;                              // _40
    LoadCallback mCallBack;               // _40
    u8 _44;                               // _44
    JKRAramStreamCommand* mStreamCommand; // _48
};

class JKRDvdAramRipper {
  public:
    static JKRAramBlock* loadToAram(char const*, u32, JKRExpandSwitch, u32, u32);
    static JKRAramBlock* loadToAram(s32, u32, JKRExpandSwitch, u32, u32);
    static JKRAramBlock* loadToAram(JKRDvdFile*, u32, JKRExpandSwitch, u32, u32);
    static JKRADCommand* loadToAram_Async(JKRDvdFile*, u32, JKRExpandSwitch, JKRADCommand::LoadCallback, u32, u32);
    static JKRADCommand* callCommand_Async(JKRADCommand*);
    static bool syncAram(JKRADCommand*, int);

    // unused/inlined:
    static JKRADCommand* loadToAram_Async(const char*, u32, JKRExpandSwitch, JKRADCommand::LoadCallback, u32, u32);
    static JKRADCommand* loadToAram_Async(s32, u32, JKRExpandSwitch, JKRADCommand::LoadCallback, u32, u32);
    static void syncAramAll(int);
    static void countLeftSync();
    static void afterAramAsync(JKRADCommand*);

    static int getSZSBufferSize() {
        return sSZSBufferSize;
    }
    static bool isErrorRetry() {
        return errorRetry;
    }

    static bool errorRetry;
    static int sSZSBufferSize;
    static JSUList<JKRADCommand> sDvdAramAsyncList;
};

inline JKRAramBlock* JKRDvdToAram(s32 entrynum, u32 p2, JKRExpandSwitch expSwitch, u32 p4, u32 p5) {
    return JKRDvdAramRipper::loadToAram(entrynum, p2, expSwitch, p4, p5);
}

#endif
#endif
