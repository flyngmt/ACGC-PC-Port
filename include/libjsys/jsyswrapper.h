#ifndef JSYSWRAPPER_H
#define JSYSWRAPPER_H

#include <stdarg.h>
#include "dolphin/pad.h"
#include "types.h"
#include "JSystem/JKernel/JKREnum.h"
#include "JSystem/JUtility/JUTEnum.h"
// #include "va_args.h"
#include "dolphin/gx.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    u16 mFileID;     // _00
    u16 mHash;       // _02
    u32 mFlag;       // _04
    u32 mDataOffset; // _08
    u32 mSize;       // _0C
    void* mData;     // _10
} CSDIFileEntry;

extern void* JC_JUTVideo_getManager();
extern u32 JC_JUTVideo_getFbWidth(void* manager);
extern u32 JC_JUTVideo_getEfbHeight(void* manager);
extern void JC_JUTVideo_setRenderMode(void* manager, GXRenderModeObj* renderMode);

extern void JC_JKRAramHeap_dump(void* heap);
extern void* JC_JKRAram_getAramHeap();

extern u32 JC_JKRAramArchive_getAramAddress_byName(void* archive, u32 root_name, const char* res_name);
extern CSDIFileEntry* JC__JKRGetResourceEntry_byName(u32 root_name, const char* res_name, void* archive);

extern void* JC__JKRDvdToMainRam_byName(const char* name, u8* buf, JKRExpandSwitch expandSwitch);
extern void JC__JKRDetachResource(void* ptr);

extern int JC_JUTConsole_isVisible(void* console);
extern void JC_JUTConsole_setVisible(void* console, BOOL visible);
extern void JC_JUTConsole_clear(void* console);
extern void JC_JUTConsole_scroll(void* console, int scroll);
extern int JC_JUTConsole_getPositionX(void* console);
extern void JC_JUTConsole_setPosition(void* console, int x, int y);
extern int JC_JUTConsole_getOutput(void* console);
extern int JC_JUTConsole_getLineOffset(void* console);
extern void JC_JUTConsole_dumpToTerminal(void* console, int lines);
extern void JC_JUTConsole_setOutput(void* console, int output);
extern void JC_JUTConsole_scrollToLastLine(void* console);
extern void JC_JUTConsole_scrollToFirstLine(void* console);
extern void JC_JUTConsole_scroll(void* console, int amount);
extern u32 JC_JUTConsole_getHeight(void* console);
extern u32 JC_JUTConsole_getUsedLine(void* console);
extern void JC_JUTConsole_print_f_va(void* console, const char* fmt, va_list arg);
extern void JC_JUTConsole_print_f(void* console, const char* fmt, ...);

extern void* JC_JUTConsoleManager_getManager();
extern void JC_JUTConsoleManager_drawDirect(void* manager, int direct);

extern void* JC_JUTDbPrint_getManager();
extern void JC_JUTDbPrint_setVisible(void* dbprint, BOOL visible);

extern void* JC_JUTProcBar_getManager();
extern void JC_JUTProcBar_setVisible(void* procbar, BOOL visible);
extern void JC_JUTProcBar_setVisibleHeapBar(void* procbar, BOOL visible);

extern void* JC_JUTException_getManager();
extern void* JC_JUTException_getConsole();
extern BOOL JC_JUTException_isEnablePad(void* manager);
extern int JC_JUTException_readPad(void* mgr, u32* trigger, u32* button);
extern void JC_JUTException_waitTime(u32 time);
extern void JC_JUTException_enterAllPad(void* manager);
extern void JC_JUTException_setMapFile(const char* path);
extern void JC_JUTException_setPreUserCallback(void* callback);
extern void JC_JUTException_setPostUserCallback(void* callback);

extern void JC_JUTAssertion_changeDevice(int device);
extern void JC_JUTAssertion_changeDisplayTime(int displayTime);

extern void JC_JUTGamePad_read();
extern PADStatus JC_JUTGamePad_getPadStatus(u32 port);
extern u8 JC_JUTGamePad_recalibrate(u32 port);

extern void* JC_JFWDisplay_getManager();
extern int JC_JFWDisplay_startFadeIn(void* manager, int len);
extern void JC_JFWDisplay_setFrameRate(void* manager, u16 framerate);
extern void JC_JFWDisplay_endFrame(void* manager);
extern void JC_JFWDisplay_beginRender(void* manager);
extern void JC_JFWDisplay_endRender(void* manager);
extern void JC_JFWDisplay_setClearColor(void* manager, GXColor color);
extern int JC_JFWDisplay_startFadeOut(void* manager, int fadeout);
extern void JC_JFWDisplay_clearEfb(void* manager, GXColor color);
extern const GXRenderModeObj* JC_JFWDisplay_getRenderMode(void* manager);
extern void* JC_JFWDisplay_changeToSingleXfb(void* manager, int index);
extern void* JC_JFWDisplay_changeToDoubleXfb(void* manager);
extern int JC_JFWDisplay_getEfbWidth(void* manager);
extern int JC_JFWDisplay_getEfbHeight(void* manager);
extern void* JC_JFWDisplay_createManager_0(GXRenderModeObj* renderMode, void* heap, int exfbNumber, int enableAlpha);
extern void JC_JFWDisplay_setFader(void* manager, void* fader);
extern void JC_JFWDisplay_setGamma(void* manager, int gamma);
extern void JC_JFWDisplay_destroyManager();

extern void JC_JFWSystem_setMaxStdHeap(int max);
extern void JC_JFWSystem_setSysHeapSize(u32 size);
extern void JC_JFWSystem_setFifoBufSize(u32 size);
extern void JC_JFWSystem_setAramAudioBufSize(u32 size);
extern void JC_JFWSystem_setAramGraphBufSize(u32 size);
extern void JC_JFWSystem_init();
extern void* JC_JFWSystem_getSystemConsole();
extern void* JC_JFWSystem_getRootHeap();
extern void* JC_JFWSystem_getSystemHeap();

extern void* JC_J2DOrthoGraph_new();
extern void JC_J2DOrthoGraph_delete(void* orthograph);

extern void* JC_JUTFader_new(int ul_x, int ul_y, int br_x, int br_y, u32* color);
extern void JC_JUTFader_delete(void* fader);

extern void* JC__JKRGetResource(const char* resourceName);

extern void JC__JKRRemoveResource(void* res);

extern void JC_J2DOrthoGraph_setOrtho(void* orthograph, int ul_x, int ul_y, int br_x, int br_y);
extern void JC_J2DOrthoGraph_setPort(void* orthograph);

extern void* JC_JKRAramArchive_new();
extern BOOL JC__JKRMountFixedAramArchive(void* aram_archive, const char* file);
extern void JC__JKRUnmountFixedAramArchive(void* aram_archive);
extern void JC_JKRAramArchive_delete(void* aram_archive);

extern u32 JC_JKRHeap_getFreeSize(void* heap);
extern void* JC_JKRHeap_alloc(void* heap, u32 size, int align);
extern void JC_JKRHeap_free(void* heap, void* mem);
extern size_t JC_JKRHeap_getSize(void* heap, void* mem);
extern s32 JC_JKRHeap_resize(void* heap, void* ptr, s32 new_size);
extern int JC_JKRHeap_dump(void* heap);
extern s32 JC_JKRHeap_getTotalFreeSize(void* heap);
extern u32 JC__JKRGetMemBlockSize(void* heap, void* ptr);

extern u8 JC_JKRExpHeap_changeGroupID(void* expheap, u8 groupId);

extern void* JC__JKRAllocFromAram(size_t size);
extern u8* JC__JKRAramToMainRam_block(void* aramBlock, u8* ramDst, size_t size);
extern void* JC__JKRMainRamToAram_block(u8* ramAddr, void* aramBlock, size_t size);

extern void* JW_Alloc(size_t size, int align);
extern void JW_Free(void* ptr);
extern s32 JW_Resize(void* ptr, size_t new_size);
extern size_t JW_GetMemBlockSize(void* ptr);
extern void JW_JUTXfb_clearIndex(void);
extern void JW_JUTReport(int x, int y, int show_count, const char* fmt, ...);

extern int JC_JKRDecomp_checkCompressed(u8* bufp);
extern void JC_JKRDecomp_decode(u8* comp_bufp, u8* decomp_bufp, u32 decomp_buf_size, u32 skipCount);

extern void* JC__JKRMountArchive(const char* path, int mount_mode, void* heap, int mount_direction);

extern void* JC__JKRGetSystemHeap();

extern void* JC_JUTXfb_getManager();
extern void JC_JUTXfb_clearIndex(void* manager);

extern u32 JC_JKRAramBlock_getAddress(void* aramBlock);

#ifdef JSYSWRAPPER_DEBUG
#define JSYSWRAPPER_PRINTF(console, fmt, ...) JC_JUTConsole_print_f(console, fmt, ...)
#else
#define JSYSWRAPPER_PRINTF(console, fmt, ...)
#endif

#ifdef __cplusplus
}
#endif

#endif
