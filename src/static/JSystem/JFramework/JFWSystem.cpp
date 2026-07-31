#include "dolphin/dvd.h"
#include "dolphin/gx.h"
#include "dolphin/os.h"
#include "JSystem/JKernel/JKRAram.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JKernel/JKRExpHeap.h"
#include "JSystem/JKernel/JKRThread.h"
#include "JSystem/JUtility/JUTConsole.h"
#include "JSystem/JUtility/JUTAssertion.h"
#include "JSystem/JUtility/JUTDbPrint.h"
#include "JSystem/JUtility/JUTDirectPrint.h"
#include "JSystem/JUtility/JUTException.h"
#include "JSystem/JUtility/JUTFont.h"
#include "JSystem/JUtility/JUTGamePad.h"
#include "JSystem/JUtility/JUTGraphFifo.h"
#include "JSystem/JUtility/JUTVideo.h"
#include "JSystem/JFramework/JFWSystem.h"

#ifdef TARGET_PC
#include "pc_bswap.h"

/* Font buffer loaded from DOL at runtime (replaces .s file's .incbin) */
unsigned char JUTResFONT_Ascfont_fix12[0x4160] ATTRIBUTE_ALIGN(32);

/* BFN1 byte-swap: swap multi-byte header/block fields, skip glyph pixel data */
static void bswap_bfn1(u8* data, u32 total_size) {
    u32 num_blocks, i;
    u8* block;

    if (total_size < 0x20) return;

    /* ResFONT header */
    pc_bswap32_array(data + 0x00, 2);  /* magic (as two u32s) */
    pc_bswap32_array(data + 0x08, 1);  /* fileSize */
    pc_bswap32_array(data + 0x0C, 1);  /* numBlocks */

    num_blocks = *(u32*)(data + 0x0C);
    block = data + 0x20;

    for (i = 0; i < num_blocks && block < data + total_size; i++) {
        u32 block_size, magic;

        /* BlockHeader: u32 magic, u32 size */
        pc_bswap32_array(block, 2);
        magic = *(u32*)(block + 0x00);
        block_size = *(u32*)(block + 0x04);

        if (block_size < 8 || block + block_size > data + total_size)
            break;

        switch (magic) {
            case 0x494E4631: /* INF1 */
                pc_bswap16_array(block + 0x08, 6);
                break;
            case 0x57494431: /* WID1 */
                pc_bswap16_array(block + 0x08, 2);
                break;
            case 0x474C5931: /* GLY1 */
                pc_bswap16_array(block + 0x08, 4);
                pc_bswap32_array(block + 0x10, 1);
                pc_bswap16_array(block + 0x14, 6);
                /* glyph pixel data at 0x20+ is byte-level, no swap */
                break;
            case 0x4D415031: /* MAP1 */
                pc_bswap16_array(block + 0x08, 4);
                if (block_size > 0x10) {
                    pc_bswap16_array(block + 0x10, (int)((block_size - 0x10) / 2));
                }
                break;
        }

        block += block_size;
    }
}

extern "C" {
extern void pc_load_asset(const char*, void*, unsigned int, unsigned int, int, int);
void _pc_load_JUTResFONT_Ascfont_fix12(void) {
    pc_load_asset(NULL, (void*)&JUTResFONT_Ascfont_fix12, 0x4160, 0x0A8260, 1 /* SRC_DOL */, 0 /* SWAP_NONE */);
    bswap_bfn1((u8*)&JUTResFONT_Ascfont_fix12, 0x4160);
}
}
#endif /* TARGET_PC */

int JFWSystem::CSetUpParam::maxStdHeaps = 2;
u32 JFWSystem::CSetUpParam::sysHeapSize = 0x400000;
u32 JFWSystem::CSetUpParam::fifoBufSize = 0x40000;
u32 JFWSystem::CSetUpParam::aramAudioBufSize = 0x800000;
u32 JFWSystem::CSetUpParam::aramGraphBufSize = 0x600000;
s32 JFWSystem::CSetUpParam::streamPriority = 8;
s32 JFWSystem::CSetUpParam::decompPriority = 7;
s32 JFWSystem::CSetUpParam::aPiecePriority = 6;
#ifdef TARGET_PC
const ResFONT* JFWSystem::CSetUpParam::systemFontRes = (const ResFONT*)JUTResFONT_Ascfont_fix12;
#else
const ResFONT* JFWSystem::CSetUpParam::systemFontRes = &JUTResFONT_Ascfont_fix12;
#endif
const GXRenderModeObj* JFWSystem::CSetUpParam::renderMode = &GXNtsc480IntDf;
u32 JFWSystem::CSetUpParam::exConsoleBufferSize = 0x24F8;

JKRHeap* JFWSystem::rootHeap;
JKRHeap* JFWSystem::systemHeap;
JKRThread* JFWSystem::mainThread;
JUTDbPrint* JFWSystem::debugPrint;
JUTFont* JFWSystem::systemFont;
JUTConsoleManager* JFWSystem::systemConsoleManager;
JUTConsole* JFWSystem::systemConsole;
bool JFWSystem::sInitCalled;

void JFWSystem::firstInit() {
    JUT_ASSERT(rootHeap == 0);
    OSInit();
    DVDInit();
    rootHeap = JKRExpHeap::createRoot(CSetUpParam::maxStdHeaps, false);
    systemHeap = JKRExpHeap::create(CSetUpParam::sysHeapSize, rootHeap, false);
}

void JFWSystem::init() {
    JUT_ASSERT(sInitCalled == false);

    if (rootHeap == 0)
        firstInit();

    sInitCalled = true;
    JKRAram::create(CSetUpParam::aramAudioBufSize, CSetUpParam::aramGraphBufSize, CSetUpParam::streamPriority,
                    CSetUpParam::decompPriority, CSetUpParam::aPiecePriority);

    mainThread = JKR_NEW JKRThread(OSGetCurrentThread(), 4);
    JUTVideo::createManager(CSetUpParam::renderMode);
    JUTCreateFifo(CSetUpParam::fifoBufSize);
    JUTGamePad::init();
    JUTDirectPrint* directPrint = JUTDirectPrint::start();
    JUTAssertion::create();
    JUTException::create(directPrint);
    systemFont = JKR_NEW JUTResFont(CSetUpParam::systemFontRes, nullptr);
    debugPrint = JUTDbPrint::start(nullptr, nullptr);
    debugPrint->changeFont(systemFont);
    systemConsoleManager = JUTConsoleManager::createManager(nullptr);
    systemConsole = JUTConsole::create(60, 200, nullptr);
    systemConsole->setFont(systemFont);

    if (CSetUpParam::renderMode->efbHeight < 300) {
        systemConsole->setFontSize(systemFont->getWidth() * 0.85f, systemFont->getHeight() * 0.5f);
        systemConsole->setPosition(20, 25);
    } else {
        systemConsole->setFontSize(systemFont->getWidth() * 0.85f, systemFont->getHeight());
        systemConsole->setPosition(20, 50);
    }
    systemConsole->setHeight(25);
    systemConsole->setVisible(false);
    systemConsole->setOutput(JUTConsole::OUTPUT_OSREPORT | JUTConsole::OUTPUT_CONSOLE);
    JUTSetReportConsole(systemConsole);
    JUTSetWarningConsole(systemConsole);
    void* mem = systemHeap->alloc(CSetUpParam::exConsoleBufferSize, 4);
    JUTException::createConsole(mem, CSetUpParam::exConsoleBufferSize);
}
