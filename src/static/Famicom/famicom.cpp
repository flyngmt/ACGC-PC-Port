#include "Famicom/famicomPriv.h"
#include "Famicom/famicomInternal.hpp"

#ifdef TARGET_PC
#include <stdio.h>
extern "C" {
    void pc_fixnes_init(unsigned char* ines_data, int ines_size);
    void pc_fixnes_set_input(unsigned char buttons);
    unsigned short* pc_fixnes_frame(void);
    void pc_fixnes_render_frame(unsigned short* fb);
    void pc_fixnes_cleanup(void);

    /* fixNES battery RAM — sync with famicomCommon.bbramp for save persistence */
    extern unsigned char* emuPrgRAM;
    extern unsigned int emuPrgRAMsize;

    /* fixNES WRAM → sp->wram sync for high-score persistence */
    void pc_fixnes_sync_wram(unsigned char* dst_wram);

    /* Card slot for current town (A=0 home, B=1 visiting) */
    int mCD_GetThisLandSlotNo(void);
}

static const char* pc_nes_save_dir(void) {
    return (mCD_GetThisLandSlotNo() == 1) ? "save/card_b" : "save/card_a";
}

static void pc_sync_bbramp_to_prgram() {
    if (!emuPrgRAM || !famicomCommon.bbramp) return;
    u32 copy_size = emuPrgRAMsize < KS_NES_BBRAM_SIZE ? emuPrgRAMsize : KS_NES_BBRAM_SIZE;
    memcpy(emuPrgRAM, famicomCommon.bbramp, copy_size);
}

static void pc_sync_prgram_to_bbramp() {
    if (!emuPrgRAM || !famicomCommon.bbramp) return;
    u32 copy_size = emuPrgRAMsize < KS_NES_BBRAM_SIZE ? emuPrgRAMsize : KS_NES_BBRAM_SIZE;
    memcpy(famicomCommon.bbramp, emuPrgRAM, copy_size);
}
#endif

#include "libc/string.h"
#include "dolphin/gx.h"
#include "dolphin/os.h"
#include "dolphin/mtx.h"
#include "dolphin/card.h"
#include "_mem.h"
#include "libultra/libultra.h"
#include "m_personal_id.h"
#include "JSystem/JUtility/JUTDbPrint.h"
#include "JSystem/JKernel/JKRFileFinder.h"
#include "JSystem/JKernel/JKRFileLoader.h"
#include "JSystem/JKernel/JKRArchive.h"
#include "JSystem/JKernel/JKRAram.h"
#include "JSystem/ResTIMG.h"
#include "JSystem/J2D/J2DGrafContext.h"
#include "libc64/sprintf.h"
#include "libjsys/jsyswrapper.h"
#include "jsyswrap_cpp.h"
#include "MSL_C/printf.h"
#include "jaudio_NES/emusound.h"
#include "JSystem/JUtility/JUTProcBar.h"
#include "JSystem/JUtility/JUTGamePad.h"
#include "nintendo_hi_0.h"
#include "m_nmibuf.h"
// #include "JSystem/J2D/J2DGrafContext.h" // needed for ~J2DOrthoGraph

/* For some reason, there are a bunch of unused implicit one-byte 4-byte-aligned bss variables */
#ifdef MUST_MATCH
static u8 __unused_implicit[0x40] ATTRIBUTE_ALIGN(32);
#endif

static u8 commentImageBuffer[CARD_COMMENT_SIZE + 0x5800] ATTRIBUTE_ALIGN(32);
u8 save_game_image = false;
FamicomCommon famicomCommon;
u8 famicomCommonSave[0x1980 + sizeof(FamicomSaveDataHeader)];
u8** nesrom_filename_ptrs = nullptr;
static char* nesrom_filename_strbuf = nullptr;
u8 InputValid[4];
u32 InputData[4];
u32 InputButton[4];
u32 InputTrigger[4];
u32 InputRepeat[4];
u32 InputRepeatCount[4];
static u8 filer_mode_enable = FALSE;
static u8 filer_mode = 0;
static u8 filer_demo_mode = FILER_DEMO_MODE_NORMAL;
static int filer_demo_count = 0;
static int nesrom_idx_loaded = 0;
static int nesrom_idx = 0;
static int nesrom_count = 0;
static int rapid_count = 0;
static u8 rapid_mode_a = FALSE;
static u8 rapid_mode_b = FALSE;
static u8 nines_over_double_click = FALSE;
static u8 nines_over_mode = FALSE;
static u8 hispeed_mode = FALSE;
static u8 slow_mode = FALSE;
static u8 slow_mode_sub = FALSE;
static u8 speed_show = FALSE;
static FAMICOM_GETSAVECHAN_PROC famicom_getSaveChanCallback = nullptr;
Famicom_MallocInfo* my_malloc_current = nullptr;
static JKRArchive* famicom_arc = nullptr;
static bool famicom_arc_mounting = FALSE;
static OSThread ksnes_thread;
static s8 errorChan = -1;

/* @unused decode_szs__FPUcPUc - static void decode_szs(u8*, u8*) */

static u8 calcSum(u8* data, size_t len) {
    u8 checksum = 0;
    size_t i;

    for (i = 0; i != len; i++) {
        checksum += *data++;
    }

    return checksum;
}

extern int famicom_getErrorChan() {
#ifdef TARGET_PC
    /* PC skips the card path so errorChan stays -1; aMR_SetSlotString would
     * then always display "Card B". Report the real save slot instead. */
    return mCD_GetThisLandSlotNo();
#else
    return errorChan;
#endif
}

static void famicom_save_data_setup(FamicomSaveDataHeader* header, u32 size, u8* identifier) {
    if (strncmp((char*)header->name, (char*)identifier, FAMICOM_SAVE_DATA_NAME_LEN) == 0 &&
        calcSum((u8*)header, FAMICOM_SAVE_HEADER_SIZE) == 0 &&
        header->_08 == 1 &&
        header->_09 == 0 &&
        header->headerSize == FAMICOM_SAVE_HEADER_SIZE &&
        header->size == size) {
        // The header ID & checksum are correct.
        OSReport("ヘッダID&チェックサムは正しいです\n");
    }
    else {
        // Repairing the header.
        OSReport("ヘッダを修復します\n");
        header->_08 = 1;
        header->_09 = 0;
        header->headerSize = FAMICOM_SAVE_HEADER_SIZE;
        header->size = size;
        memcpy(header->name, identifier, FAMICOM_SAVE_DATA_NAME_LEN);
        int checksum = calcSum((u8*)header, FAMICOM_SAVE_HEADER_SIZE);
        header->checksum -= checksum;
    }

    u8* data = ((u8*)header) + header->headerSize;
    for (u32 i = 0; i < PLAYER_NUM; i++) {
        int versionTag = data[1] >> 4;
        int versionNo = data[1] & 0xF;

        if (data[0] == 'D' && calcSum(data, size) == 0 &&
            versionTag == 3 && versionNo <= 1 && // check version character is either '0' or '1'
            data[3] == (u8)i) {
            // The personal data checksum %d is correct.
            OSReport("個人データチェックサム%dは正しいです\n", i);
        }
        else {
            // Repairing personal data %d.
            OSReport("個人データ%dを修復します\n", i);
            data[0] = 'D';
            data[1] = '1';
            data[3] = i;
            data[2] -= calcSum(data, size);
        }

        data += size;
    }
}

static void famicom_save_data_init(FamicomSaveDataHeader* header, u32 size, u8* identifier) {
    bzero(header, FAMICOM_SAVE_HEADER_SIZE + size * PLAYER_NUM);
    header->no_save = TRUE;
    famicom_save_data_setup(header, size, identifier);
}

static int famicom_save_data_check(const FamicomSaveDataHeader* header, int ignore_player_no, const u8* identifier) {
    if (strncmp((char*)header->name, (char*)identifier, FAMICOM_SAVE_DATA_NAME_LEN) == 0) {
        // The header ID is correct.
        OSReport("ヘッダIDは正しいです\n");

        if (calcSum((u8*)header, FAMICOM_SAVE_HEADER_SIZE) == 0) {
            // The header checksum is correct.
            OSReport("ヘッダチェックサムは正しいです\n");

            if (((header->_08 == 1 && header->_09 == 0) || (header->_08 == 0 && header->_09 == 1)) && header->headerSize == FAMICOM_SAVE_HEADER_SIZE) {
                // The version and header size match.
                OSReport("バージョンとヘッダサイズが合致しました\n");

                int i;
                u8* data = ((u8*)header) + header->headerSize;

                for (i = 0; i < PLAYER_NUM; i++) {
                    if (i != ignore_player_no) {
                        if (data[0] != 'D' || calcSum(data, header->size) != 0) {
                            goto fail;
                        }

                        // The personal ID & data checksum %d is correct.
                        OSReport("個人ID&データチェックサム%dは正しいです\n", i);
                    }

                    data += header->size;
                }

                return 0;
            }
        }
    }

    fail:
    // The Famicom common save is invalid.
    OSReport("ファミコン共通セーブは不正です\n");
    return -1;
}

static void process_filer_mode() {
    static const Vec camPt = { 0.0f, 0.0f, 800.0f };
    static const Vec at = { 0.0f, 0.0f, -100.0f };
    static const Vec up = { 0.0f, 1.0f, 0.0f };
    Mtx44 m;
    Mtx34 lookat_m;

    GXInvalidateTexAll();
    GXInvalidateVtxCache();
    GXSetClipMode(GX_CLIP_DISABLE);
    GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
    GXSetCopyFilter(GX_FALSE, nullptr, GX_FALSE, nullptr);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetZTexture(GX_ZT_DISABLE, GX_TF_Z8, 0);
    GXSetZCompLoc(GX_FALSE);
    GXSetColorUpdate(GX_TRUE);
    GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetTevSwapMode(GX_TEVSTAGE3, GX_TEV_SWAP0, GX_TEV_SWAP0);
    C_MTXOrtho(m, 0.0, -480.0, 0.0, 640.0, 0.0, 2000.0);
    GXSetProjection(m, GX_ORTHOGRAPHIC);
    C_MTXLookAt(lookat_m, &camPt, &up, &at);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXLoadPosMtxImm(lookat_m, GX_PNMTX0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);

    // Vertex 0
    GXPosition2s16(0, 0);
    GXColor1u32(0x00500000);
    // Vertex 1
    GXPosition2s16(640, 0);
    GXColor1u32(0x00000000);
    // Vertex 2
    GXPosition2s16(640, -480);
    GXColor1u32(0x00005000);
    // Vertex 3
    GXPosition2s16(0, -480);
    GXColor1u32(0x00000000);

    int start_idx;
    if (nesrom_idx < 10 || nesrom_count < 18) {
        start_idx = 0;
    }
    else if ((nesrom_idx + 10) > nesrom_count) {
        start_idx = nesrom_count - 18;
    }
    else {
        start_idx = nesrom_idx - 9;
    }

    JUTReport(20, 60, 1, "QFC ver.011012   (C)2001 Nintendo");
    if (filer_demo_mode != FILER_DEMO_MODE_NORMAL) {
        JUTReport(30, 80, 1, "[%d/%d]   -auto demo-  R: cancel", nesrom_idx + 1, nesrom_count);
    }
    else {
        JUTReport(30, 80, 1, "[%d/%d]   R: back  B: demo", nesrom_idx + 1, nesrom_count);
    }

    if (famicomCommon.nesrom_memcard == FALSE) {
        for (u32 i = 0; i < 18; i++) {
            u32 idx = start_idx + i;

            if (idx < nesrom_count) {
                JUTReport(30, 100 + i * 20, 1, "%s%s", (nesrom_idx == idx && (filer_demo_mode == FILER_DEMO_MODE_NORMAL || (filer_demo_count & 0x20) == 0)) ? "->" : "  ", nesrom_filename_ptrs[idx]);
            }
        }
    }

    if (famicomCommon.nesrom_memcard == FALSE) {
        u32 cur_idx;
    
        if ((InputTrigger[0] & (JUTGamePad::MAINSTICK_LEFT | JUTGamePad::DPAD_LEFT))) {
            cur_idx = nesrom_idx;
            nesrom_idx--;
    
            do {
                nesrom_idx--;
    
                while (nesrom_idx < 0) {
                    nesrom_idx += nesrom_count;  
                }
            } while (nesrom_filename_ptrs[nesrom_idx][0] != ':' && cur_idx != nesrom_idx);
        }
    
        if ((InputTrigger[0] & (JUTGamePad::MAINSTICK_RIGHT | JUTGamePad::DPAD_RIGHT))) {
            cur_idx = nesrom_idx;
            do {
                nesrom_idx++;
    
                if (nesrom_idx >= nesrom_count) {
                    nesrom_idx = 0;
                }
            } while (nesrom_filename_ptrs[nesrom_idx][0] != ':' && cur_idx != nesrom_idx);
        }
    
        if ((InputRepeat[0] & (JUTGamePad::MAINSTICK_UP | JUTGamePad::DPAD_UP))) {
            cur_idx = nesrom_idx;
            do {
                if (nesrom_idx > 0) {
                    nesrom_idx--;
                }
                else {
                    nesrom_idx = nesrom_count - 1;
                }
            } while (nesrom_filename_ptrs[nesrom_idx][0] == ':' && cur_idx != nesrom_idx);
        }
    
        if ((InputRepeat[0] & (JUTGamePad::MAINSTICK_DOWN | JUTGamePad::DPAD_DOWN)) != 0) {
            if (nesrom_idx < nesrom_count - 1) {
                nesrom_idx++;
            }
            else {
                nesrom_idx = 0;
            }
        }
    }

    if ((InputTrigger[0] & BUTTON_DLEFT)) {
        filer_mode = 0;
        filer_demo_mode = FILER_DEMO_MODE_AUTO;
        filer_demo_count = 0;
    }
    
    if ((InputTrigger[0] & BUTTON_START)) {
        filer_mode = 0;
        filer_demo_mode = FILER_DEMO_MODE_NORMAL;
    }
}

extern void famicom_setCallback_getSaveChan(FAMICOM_GETSAVECHAN_PROC proc) {
    famicom_getSaveChanCallback = proc;
}

static s32 memcard_mount(int, void*);

static const s32 checkTableNG[] = {
    CARD_RESULT_FATAL_ERROR,
    CARD_RESULT_IOERROR,
    CARD_RESULT_BROKEN,
    CARD_RESULT_ENCODING,
    CARD_RESULT_WRONGDEVICE
};

static s32 famicom_getSaveChan(int nesrom_memcard, s32* result) {
    s32 chan_result[2];
    s32 card_err;
    int chan;
    int mounted = FALSE;
    void* workArea = nullptr;
    char* file_name;

    chan_result[0] = CARD_RESULT_READY;
    chan_result[1] = CARD_RESULT_READY;

    if (nesrom_memcard == FALSE) {
        if (famicom_getSaveChanCallback != NULL) {
            chan = famicom_getSaveChanCallback(nullptr, chan_result);

            if (chan >= 0) {
                errorChan = chan;
            }
        }
        else {
            chan = -1;
            card_err = CARD_RESULT_FATAL_ERROR;
            goto exit;
        }
        
        if (chan < 0 && famicomCommon._8C) {
            nesrom_memcard = TRUE;
        }
    }

    if (nesrom_memcard != FALSE) {
        file_name = (char*)famicomCommon.mura_save_name;
        workArea = my_malloc(CARD_WORKAREA_SIZE, 32);
        if (workArea == nullptr) {
            card_err = CARD_RESULT_FATAL_ERROR;
            chan = -1;
            goto exit;
        }

        for (chan = 0; chan < CARD_NUM_CHANS; chan++) {
            if (mounted) {
                CARDUnmount(chan);
            }
            
            s32 mount_res = memcard_mount(chan, workArea);
            chan_result[chan] = mount_res;
            mounted = mount_res == CARD_RESULT_READY;

            if (mounted) {
                if (file_name != nullptr) {
                    CARDFileInfo file_info;
                    card_err = CARDOpen(chan, file_name, &file_info);

                    chan_result[chan] = card_err;
                    if (card_err == CARD_RESULT_READY) {
                        CARDClose(&file_info);
                        OSReport("チェックファイル存在\n"); // Check file exists.
                        errorChan = chan;
                        goto exit;
                    }
                }

                CARDUnmount(chan);
                mounted = FALSE;
            }
        }
        
        chan = -1;
        card_err = CARD_RESULT_NOFILE;
    }

    if (chan < 0) {    
        for (int i = 0; i < ARRAY_COUNT(checkTableNG); i++) {        
            if (chan_result[0] == checkTableNG[i]) {
                card_err = *(s32*)(chan_result + 0);
                errorChan = 0;
                goto exit;
            }
            
            if (chan_result[1] == checkTableNG[i]) {
                card_err = *(s32*)(chan_result + 1);
                errorChan = 1;
                goto exit;
            }
        }

        if ((chan_result[0] == CARD_RESULT_NOFILE || chan_result[0] == CARD_RESULT_NOCARD || chan_result[0] == CARD_RESULT_READY) &&
            (chan_result[1] == CARD_RESULT_NOFILE || chan_result[1] == CARD_RESULT_NOCARD || chan_result[1] == CARD_RESULT_READY)) {
            card_err = nesrom_memcard ? CARD_RESULT_NOFILE : CARD_RESULT_NOCARD;
            errorChan = CARD_NUM_CHANS;
        }
        else {
            card_err = CARD_RESULT_FATAL_ERROR;
        }
    }

    exit:
    if (mounted) {
        CARDUnmount(chan);
    }

    if (workArea != nullptr) {
        my_free(workArea);
    }

    if (result != nullptr) {
        *result = card_err;
    }

    return chan;
}

static s32 memcard_mount(int chan, void* workArea) {
    s32 result;
    s32 sector_size;

    // Checking whether the memory card is inserted in the slot.
    OSReport("メモリーカードが、スロットに挿入されているかどうかを調べます。\n");

    do {
        result = CARDProbeEx(chan, nullptr, &sector_size);
    } while (result == CARD_RESULT_BUSY);

    if (result == CARD_RESULT_READY) {
        if (sector_size != 0x2000) {
            // The sector size is not 8KB.
            OSReport("セクターサイズが8KBではありません。\n");
            result = CARD_RESULT_WRONGDEVICE;
        }
        else {
            // Mounting the memory card.
            OSReport("メモリーカードをマウントする\n");
            result = CARDMount(chan, workArea, nullptr);
            
            if (result == CARD_RESULT_READY || result == CARD_RESULT_BROKEN || result == CARD_RESULT_ENCODING) {
                // The memory card has been mounted.
                OSReport("メモリーカードはマウント状態になった\n");

                if (result == CARD_RESULT_READY || result == CARD_RESULT_BROKEN) {
                    if (result == CARD_RESULT_BROKEN) {
                        // The memory card is damaged.
                        OSReport("メモリーカードは壊れています\n");
                        // Attempting to repair the memory card.
                        OSReport("メモリーカードの修復を試みます\n");
                    }
                    
                    result = CARDCheck(chan);
                    if (result != CARD_RESULT_READY) {
                        // Failed to repair the memory card.
                        OSReport("メモリーカードの修復に失敗しました\n");
                        CARDUnmount(chan);
                    }
                }
                else {
                    // The character encoding of the memory card does not match.
                    OSReport("メモリーカードの文字コードがあっていません\n");
                    CARDUnmount(chan);
                }
            }
        }
    }
    else if (result != CARD_RESULT_NOCARD) {
        // The memory card is not inserted.
        OSReport("メモリーカードは刺さってない\n");
    }

    if (result != CARD_RESULT_READY && result != CARD_RESULT_NOCARD && result != CARD_RESULT_FATAL_ERROR) {
        errorChan = chan;
    }

    return result;
}

static s32 memcard_getFreeBlocks(s32 chan, s32* unused_bytes, s32* unused_files) {
    s32 result;
    int mounted = FALSE;
    void* workArea = my_malloc(CARD_WORKAREA_SIZE, 32);

    if (workArea == nullptr) {
        result = CARD_RESULT_FATAL_ERROR;
    }
    else {
        result = memcard_mount(chan, workArea);
        mounted = result == CARD_RESULT_READY;

        if (mounted) {
            result = CARDFreeBlocks(chan, unused_bytes, unused_files);
        }
    }

    if (result != CARD_RESULT_READY && result != CARD_RESULT_NOCARD && result != CARD_RESULT_FATAL_ERROR) {
        errorChan = chan;
    }

    if (result != CARD_RESULT_READY) {
        // Error code = %d
        OSReport("エラーコード＝%d\n", result);
    }

    if (mounted) {
        CARDUnmount(chan);
    }

    if (workArea != nullptr) {
        my_free(workArea);
    }

    return result;
}

/* @unused @fabricated - strings necessary for matching */
static s32 memcard_list(int chan) {
    OSReport("No. Name Co B FileName                         (YYYY/MM/DD hh:mm:ss) IconAddr IFmt ISpd Pm Cp StB Lng Com\n");
    OSReport("%3d %.4s %.2s %d %-32.32s (%04d/%02d/%02d %02d:%02d:%02d) %03x %04x %04x %02x %2d %3d %3d %04x\n");
}

static size_t getBannerSizeFromFormat(u8 format) {
    switch (format) {
        case CARD_STAT_BANNER_C8:
            return 0xE00;
        case CARD_STAT_BANNER_RGB5A3:
            return 0x1800;
        default:
            return 0;
    }
}

static size_t getIconSizeFromFormat(u16 format) {
    size_t size = 0;
    int has_palette = FALSE;
    
    for (int i = 0; i < CARD_ICON_MAX; i++) {
        switch ((format >> (i * 2)) & CARD_STAT_ICON_MASK) {
            case CARD_STAT_ICON_C8:
            {
                has_palette = TRUE;
                size += 0x400;
                break;
            }

            case CARD_STAT_ICON_RGB5A3:
            {
                size += 0x800;
                break;
            }
        }
    }

    if (has_palette) {
        size += 0x200;
    }

    return size;
}

static int SetupResBanner(const ResTIMG*, u8*, size_t, size_t*, u8*);
static int SetupResIcon(const ResTIMG*, u8*, size_t, size_t*, u16*, u16*);

static void SetupExternCommentImage(u8* embedded_save_comment_img, u8* dst, u8* rom_file_comment_img) {
    u32 size;

    switch (famicomCommon.memcard_game_header.flags0.comment_type) {
        case MEMCARD_COMMENT_TYPE_NONE:
            break;
        case MEMCARD_COMMENT_TYPE_COPY_ROM: {
            memcpy(dst, rom_file_comment_img, CARD_COMMENT_SIZE);
            u8 temp = dst[CARD_COMMENT_SIZE];
            dst[CARD_COMMENT_SIZE] = '\0';
            char* image_name_end = strstr((char*)dst + 32, "] ROM ");
            dst[CARD_COMMENT_SIZE] = temp;

            if (image_name_end != nullptr) {
                strncpy(image_name_end, "] SAVE", 6);
                dst += CARD_COMMENT_SIZE;
                break;
            }
            // Fallthrough in the case where "] ROM " doesn't exist
        }
        case MEMCARD_COMMENT_TYPE_DEFAULT: {
            strncpy((char*)dst, "Animal Crossing", 32);
            strncpy((char*)dst + 32, "NES Cassette Save Data  ", 32);
            dst += CARD_COMMENT_SIZE;
            break;
        }
        case MEMCARD_COMMENT_TYPE_COPY_EMBEDDED: {
            memcpy(dst, embedded_save_comment_img, CARD_COMMENT_SIZE);
            dst += CARD_COMMENT_SIZE;
            embedded_save_comment_img += CARD_COMMENT_SIZE;
            break;
        }
    }

    rom_file_comment_img += CARD_COMMENT_SIZE;
    switch (famicomCommon.memcard_game_header.flags0.banner_type) {
        case MEMCARD_BANNER_TYPE_NONE:
            break;
        case MEMCARD_BANNER_TYPE_DEFAULT: {
            void* banner = JKRFileLoader::getGlbResource("/FAMICOM/newdisk_system.bti.szs");
            ResTIMG* banner_data = (ResTIMG*)banner;
            if (banner_data != nullptr) {
                u8 banner_fmt;
                SetupResBanner(banner_data, dst, 0x1800, &size, &banner_fmt);
                JKRFileLoader::removeResource(banner_data, nullptr);
                dst += size;
                famicomCommon.memcard_game_header.flags1.banner_fmt = banner_fmt;
            }
            break;
        }
        case MEMCARD_BANNER_TYPE_COPY_ROM: {
            size = getBannerSizeFromFormat(famicomCommon.memcard_game_header.flags1.banner_fmt);
            memcpy(dst, rom_file_comment_img, size);
            dst += size;
            break;
        }
        case MEMCARD_BANNER_TYPE_COPY_EMBEDDED: {
            size = getBannerSizeFromFormat(famicomCommon.memcard_game_header.flags1.banner_fmt);
            memcpy(dst, embedded_save_comment_img, size);
            dst += size;
            embedded_save_comment_img += size;
            break;
        }
    }

    size_t banner_size = getBannerSizeFromFormat(famicomCommon.memcard_game_header.flags1.banner_fmt);
    rom_file_comment_img += banner_size;
    switch (famicomCommon.memcard_game_header.flags0.icon_type) {
        case MEMCARD_ICON_TYPE_NONE:
            break;
        case MEMCARD_ICON_TYPE_DEFAULT: {
            void* icon = JKRFileLoader::getGlbResource("/FAMICOM/newdisk.bti.szs");
            ResTIMG* icon_data = (ResTIMG*)icon;
            if (icon_data != nullptr) {
                u16 icon_fmts;
                u16 icon_flags;
                SetupResIcon(icon_data, dst, 0x800, nullptr, &icon_fmts, &icon_flags);
                JKRFileLoader::removeResource(icon_data, nullptr);
                famicomCommon.memcard_game_header.icon_format = icon_fmts;
                famicomCommon.memcard_game_header.icon_flags = icon_flags;
                size = getIconSizeFromFormat(icon_fmts);
            }
            break;
        }
        case MEMCARD_ICON_TYPE_COPY_ROM: {
            size = getIconSizeFromFormat(famicomCommon.memcard_game_header.icon_format);
            memcpy(dst, rom_file_comment_img, size);
            break;
        }
        case MEMCARD_ICON_TYPE_COPY_EMBEDDED: {
            size = getIconSizeFromFormat(famicomCommon.memcard_game_header.icon_format);
            memcpy(dst, embedded_save_comment_img, size);
            break;
        }
    }
    
    size_t icon_size = getIconSizeFromFormat(famicomCommon.memcard_game_header.icon_format); // unnecessary
}

static void SetupInternalCommentImage(u8* data) {
    u8* data_p = data;

    // Setup comment
    famicomCommon.memcard_game_header.flags0.comment_type = MEMCARD_COMMENT_TYPE_DEFAULT;
    strncpy((char*)data, "Animal Crossing", 32);
    strncpy((char*)data + 32, "NES Save Data           ", 32);
    data += CARD_COMMENT_SIZE;

    // Setup banner
    famicomCommon.memcard_game_header.flags0.banner_type = MEMCARD_BANNER_TYPE_NONE;
    famicomCommon.memcard_game_header.flags1.banner_fmt = CARD_STAT_BANNER_NONE;

    // Setup icon
    void* icon = JKRFileLoader::getGlbResource("/FAMICOM/famikon.bti.szs");
    ResTIMG* icon_res = (ResTIMG*)icon;
    if (icon_res != nullptr) {
        u16 icon_fmts;
        u16 icon_flags;
        
        SetupResIcon(icon_res, data, 0x800, nullptr, &icon_fmts, &icon_flags);
        JKRFileLoader::removeResource(icon_res, nullptr);
        famicomCommon.memcard_game_header.flags0.icon_type = MEMCARD_ICON_TYPE_DEFAULT;
        famicomCommon.memcard_game_header.icon_format = icon_fmts;
        famicomCommon.memcard_game_header.icon_flags = icon_flags;
        data += getIconSizeFromFormat(icon_fmts);
    }
    else {
        famicomCommon.memcard_game_header.flags0.icon_type = MEMCARD_ICON_TYPE_NONE;
        famicomCommon.memcard_game_header.icon_format = 0;
        famicomCommon.memcard_game_header.icon_flags = 0;
    }

    famicomCommon.memcard_game_header.comment_img_size = (u32)data - (u32)data_p;
}

static s32 memcard_data_save(
    int chan,
    const char* file_name,
    const char* check_file_name,
    const FamicomSaveDataHeader* header,
    size_t save_data_size,
    const u8* comment_img,
    u8 banner_fmt,
    u32 icon_addr,
    u16 icon_fmts,
    u16 icon_flags,
    u32 comment_addr,
    int do_not_save
) {
    char temp_name[33];
    s32 result;
    size_t save_data_size_block_aligned;
    int mounted = FALSE;
    int opened = FALSE;
    void* workArea;
    u8* save_data = nullptr;
    void* buf = nullptr;
    CARDFileInfo fileInfo;
    u8 cardAttr;
    size_t save_size = 0;
    size_t comment_img_size;
    
    // format temp string using file_name as "file_name~"
    sprintf(temp_name, "%-.31s~", file_name);
    workArea = my_malloc(CARD_WORKAREA_SIZE, 32);

    if (workArea == nullptr) {
        result = CARD_RESULT_FATAL_ERROR;
        goto exit;
    }

    save_size = icon_addr != 0xFFFFFFFF ? icon_addr : 0;
    save_size += getBannerSizeFromFormat(banner_fmt);
    save_size += getIconSizeFromFormat(icon_fmts);
    comment_img_size = save_size;
    save_size += save_data_size;
    save_data_size_block_aligned = ALIGN_NEXT(save_size, 0x2000);
    save_data = (u8*)my_malloc(save_data_size_block_aligned, 32);

    if (save_data == nullptr) {
        result = CARD_RESULT_FATAL_ERROR;
        goto exit;
    }

    bzero(save_data, save_data_size_block_aligned);
    memcpy(save_data, comment_img, comment_img_size); // copy memcard file info data
    memcpy(save_data + comment_img_size, header, save_data_size); // copy data header & save data

    result = memcard_mount(chan, workArea);
    mounted = result == CARD_RESULT_READY;

    if (mounted) {
        if (check_file_name != nullptr) {
            result = CARDOpen(chan, check_file_name, &fileInfo);
            if (result != CARD_RESULT_READY) {
                // The check file does not exist.
                OSReport("チェックファイル存在しないよ\n");
                goto exit;
            }

            CARDClose(&fileInfo);
        }

        buf = my_malloc(save_data_size_block_aligned, 32);
        if (buf == nullptr) {
            result = CARD_RESULT_FATAL_ERROR;
            // Not enough memory!
            OSReport("メモリが足りん！\n");
            goto exit;
        }

        // Add the contents of the file (check for need to save).
        OSReport("ファイルの内容を取り込む(セーブの必要性チェック)\n");
        result = CARDOpen(chan, file_name, &fileInfo);
        if (result == CARD_RESULT_READY) {
            if (do_not_save) {
                result = CARD_RESULT_FATAL_ERROR;
                goto exit;
            }

            result = CARDRead(&fileInfo, buf, save_data_size_block_aligned, 0);
            if (result != CARD_RESULT_READY) {
                goto exit;
            }

            bool save_updated = bcmp(save_data, buf, save_data_size_block_aligned) == 0;
            if (save_updated) {
                // No need to save, so the process has completed successfully.
                OSReport("セーブする必要が無いので正常終了\n");
                goto exit;
            }

            // Need to save (update mode).
            OSReport("セーブする必要がある(更新モード)\n");
        }
        else {
            if (result != CARD_RESULT_NOFILE) {
                goto exit;
            }

            // Need to save (new creation mode).
            OSReport("セーブする必要がある(新規作成モード)\n");
        }

        result = CARDRename(chan, file_name, temp_name);
        if (result == CARD_RESULT_EXIST) {
            result = CARDDelete(chan, temp_name); // delete temp file
            if (result != CARD_RESULT_READY) {
                goto exit; // failed to delete
            }
            result = CARDRename(chan, file_name, temp_name); // try renaming again
            if (result != CARD_RESULT_READY) {
                goto exit; // failed to rename after deleting
            }
        }
        else if (result != CARD_RESULT_NOFILE && result != CARD_RESULT_READY) {
            goto exit;
        }

        // Creating file chan=%d [%s] length=%d.
        OSReport("ファイル作成 chan=%d [%s] length=%d\n", chan, file_name, save_data_size_block_aligned);
        result = CARDCreate(chan, file_name, save_data_size_block_aligned, &fileInfo);
        switch (result) {
            case CARD_RESULT_READY:
                break; // success
            case CARD_RESULT_NOENT:
            case CARD_RESULT_INSSPACE: {
                s32 del_res = CARDDelete(chan, temp_name);
                if (del_res == CARD_RESULT_NOFILE) {
                    goto exit; // temp file didn't exist?
                }

                // check for other errors
                if (del_res != CARD_RESULT_READY) {
                    result = del_res;
                    goto exit;
                }

                result = CARDCreate(chan, file_name, save_data_size_block_aligned, &fileInfo);
                if (result != CARD_RESULT_READY) {
                    goto exit; // still failed to create
                }
                break;
            }
            default:
                // Failed to create file.
                OSReport("ファイル作成失敗\n");
                goto exit;
        }

        CARDGetAttributes(chan, fileInfo.fileNo, &cardAttr);
        u8 saved_attr = cardAttr;

        if ((famicomCommon.memcard_game_header.flags0.no_copy_flag)) {
            saved_attr |= CARD_ATTR_NO_COPY;
        }

        if ((famicomCommon.memcard_game_header.flags1.no_move_flag)) {
            saved_attr |= CARD_ATTR_NO_MOVE;
        }

        saved_attr |= cardAttr;
        if ((saved_attr) != 0) {
            CARDSetAttributes(chan, fileInfo.fileNo, saved_attr);
        }

        // Writing the entire file.
        OSReport("ファイル全体の書き込み\n");
        result = CARDWrite(&fileInfo, save_data, save_data_size_block_aligned, 0);
        if (result == CARD_RESULT_READY) {
            // Verifying the entire file.
            OSReport("ファイル全体のベリファイ\n");
            result = CARDRead(&fileInfo, buf, save_data_size_block_aligned, 0);
            if (result == CARD_RESULT_READY) {
                if (bcmp(save_data, buf, save_data_size_block_aligned) == 0) {
                    // Verification successful.
                    OSReport("ベリファイ成功\n");
                }
                else {
                    // Verification failed.
                    OSReport("ベリファイ失敗\n");
                    result = CARD_RESULT_IOERROR;
                    goto exit;
                }
                
                // Close.
                OSReport("クローズ\n");
                result = CARDClose(&fileInfo);
                if (result != CARD_RESULT_READY) {
                    // Failed to close?
                    OSReport("クローズに失敗って？\n");
                    goto exit;
                }
                else {
                    // Get status.
                    opened = FALSE;
                    OSReport("ステータス取得\n");
                }

                CARDStat status;
                result = CARDGetStatus(chan, fileInfo.fileNo, &status);
                if (result != CARD_RESULT_READY) {
                    // Failed to get status.
                    OSReport("ステータス取得失敗\n");
                    goto exit;
                }

                status.bannerFormat = banner_fmt;
                status.iconSpeed = icon_flags;
                status.iconAddr = icon_addr;
                status.iconFormat = icon_fmts;
                status.commentAddr = comment_addr;
                // Change status.
                OSReport("ステータス変更\n");
                result = CARDSetStatus(chan, fileInfo.fileNo, &status);
                if (result != CARD_RESULT_READY) {
                    // Failed to change status.
                    OSReport("ステータス変更失敗\n");
                }
                else {
                    result = CARDDelete(chan, temp_name);
                    if (result == CARD_RESULT_NOFILE) {
                        result = CARD_RESULT_READY; // successfully deleted temp file
                    }
                }
            }
        }
    }

exit:
    if (result != CARD_RESULT_READY && result != CARD_RESULT_NOCARD && result != CARD_RESULT_FATAL_ERROR) {
        errorChan = chan;
    }

    if (result != CARD_RESULT_READY) {
        // Error code = %d.
        OSReport("エラーコード＝%d\n", result);
    }

    if (buf != nullptr) {
        my_free(buf);
    }

    if (save_data != nullptr) {
        my_free(save_data);
    }

    if (opened) {
        CARDClose(&fileInfo);
    }

    if (mounted) {
        CARDUnmount(chan);
    }

    if (workArea != nullptr) {
        my_free(workArea);
    }

    return result;
}

static s32 memcard_data_load(
    int chan,
    const char* file_name,
    const char* check_file_name,
    FamicomSaveDataHeader* save_header,
    size_t save_data_size,
    const u8* comment_img
) {
    char temp_name[33];
    s32 result;
    int mounted = FALSE;
    void* workArea;
    u8* save_data = nullptr;
    int i;
    void* buf = nullptr;
    CARDFileInfo fileInfo;
    CARDStat status;
    
    // format temp string using file_name as "file_name~"
    sprintf(temp_name, "%-.31s~", file_name);
    workArea = my_malloc(CARD_WORKAREA_SIZE, 32);

    if (workArea == nullptr) {
        // Not enough memory!
        OSReport("メモリが足りん！！\n");
        result = CARD_RESULT_FATAL_ERROR;
        goto exit;
    }

    result = memcard_mount(chan, workArea);
    mounted = result == CARD_RESULT_READY;

    if (!mounted) {
        // Can't mount!
        OSReport("マウントできない！\n");
        goto exit;
    }
    
    if (check_file_name != nullptr) {
        result = CARDOpen(chan, check_file_name, &fileInfo);
        if (result != CARD_RESULT_READY) {
            // The check file does not exist.
            OSReport("チェックファイル存在しないよ\n");
            goto exit;
        }

        CARDClose(&fileInfo);
    }

    for (i = 0; i < 2; i++) {
        // Opening file [%s]
        OSReport("ファイルのオープン [%s]\n", i == 0 ? file_name : temp_name);
        result = CARDOpen(chan, i == 0 ? file_name : temp_name, &fileInfo);
        if (result != CARD_RESULT_READY) {
            // Can't open the file.
            OSReport("ファイルがオープンできない\n");
            continue;
        }
        
        if (buf != nullptr) {
            my_free(buf);
            buf = nullptr;
        }

        result = CARDGetStatus(chan, fileInfo.fileNo, &status);
        if (status.offsetData == 0) {
            // File has no icon
            OSReport("アイコンのないファイル\n");

            if (status.commentAddr == 0xFFFFFFFF) {
                // File has no comment
                OSReport("コメントもないファイル\n");
                // The file is currently being saved
                OSReport("どう考えてもセーブ中のファイル\n");
                if (CARDDelete(chan, file_name) == CARD_RESULT_READY) {
                    // Erased the file that was being saved.
                    OSReport("セーブ中のファイルを消しました\n");
                }

                continue;
            }
        }
        
        size_t len = status.length;
        buf = my_malloc(len, 32);

        if (buf == nullptr) {
            // Not enough memory!
            OSReport("メモリが足りん！！\n");
            result = CARD_RESULT_FATAL_ERROR;
            goto exit;
        }

        // Read the file.
        OSReport("ファイル読む\n");
        result = CARDRead(&fileInfo, buf, len, 0);
        if (result != CARD_RESULT_READY) {
            // Can't read the file.
            OSReport("ファイル読めない\n");
            continue;
        }

        // Close the file.
        OSReport("ファイル閉じる\n");
        result = CARDClose(&fileInfo);
        if (result != CARD_RESULT_READY) {
            // Can't close the file.
            OSReport("ファイル閉じれない\n");
            continue;
        }

        // Reading successful!
        OSReport("読み込み成功！！\n");
        FamicomSaveDataHeader* read_save_header = (FamicomSaveDataHeader*)((u32)buf + status.offsetData);
        
        if (famicom_save_data_check(read_save_header, -1, comment_img) == 0) {
            // The data is normal!
            OSReport("データは正常！！\n");
            
            if (i == 0) {
                if (CARDDelete(chan, temp_name) == CARD_RESULT_READY) {
                    // Deleted the old data backup.
                    OSReport("旧データバックアップを消しました\n");
                }
            }
            else {
                if (CARDDelete(chan, file_name) == CARD_RESULT_READY) {
                    // Deleted invalid 'real' file.
                    OSReport("不正なホンチャンファイルを消しました\n");
                }

                if (CARDRename(chan, temp_name, file_name) == CARD_RESULT_READY) {
                    // Renamed backup file to 'real' file.
                    OSReport("バックアップをホンチャンにリネームしました\n");
                }
            }

            if (save_header != nullptr) {
                memcpy(save_header, read_save_header, save_data_size);
            }

            break;
        }
        
        result = CARD_RESULT_NOFILE;
    }

exit:
    if (result != CARD_RESULT_READY && result != CARD_RESULT_FATAL_ERROR) {
        errorChan = chan;
    }

    if (result != CARD_RESULT_READY) {
        // Error code = %d.
        OSReport("エラーコード＝%d\n", result);
    }

    if (buf != nullptr) {
        my_free(buf);
    }

    if (save_data != nullptr) {
        my_free(save_data);
    }

    if (mounted) {
        CARDUnmount(chan);
    }

    if (workArea != nullptr) {
        my_free(workArea);
    }

    return result;
}

static s32 memcard_game_load(
    u8* nesromp,
    int rom_idx,
    u8** tags_pp,
    char* mura_save_name,
    char* famicom_save_name,
    MemcardGameHeader_t* game_header,
    u8* memcard_save_comment,
    size_t unused_save_data_start_ofs,
    u8* chr_to_i8_bufp,
    size_t chr_to_i8_buf_size
) {
    s32 result;
    s32 chan;
    CARDFileInfo fileInfo;
    int mounted = FALSE;
    CARDStat cardStatus;
    int now_rom_idx = 0;
    void* workArea;
    s32 fileNo;
    
    workArea = my_malloc(CARD_WORKAREA_SIZE, 32);
    if (workArea != nullptr) {
        for (chan = 0; chan < CARD_NUM_CHANS; chan++) {
            result = memcard_mount(chan, workArea);
            mounted = result == CARD_RESULT_READY;
    
            if (mounted) {
                for (fileNo = 0; fileNo < 127; fileNo++) {
                    result = CARDGetStatus(chan, fileNo, &cardStatus);
                    if (result == CARD_RESULT_READY) {
                        if (
                            memcmp(cardStatus.gameName, "GAFE", 4) == 0 &&
                            memcmp(cardStatus.company, "01", 2) == 0 &&
                            memcmp(cardStatus.fileName, "DobutsunomoriP_F_", 17) == 0 &&
                            strcmp(&cardStatus.fileName[17], "SAVE") != 0 /* filename can't be Doubutsunomori_P_F_SAVE* */
                        ) {
                            if (rom_idx == now_rom_idx) {
                                /* Incorporate the contents of the file. */
                                OSReport("ファイルの内容を取り込む\n");
                                result = CARDFastOpen(chan, fileNo, &fileInfo);
                                if (result != CARD_RESULT_READY) {
                                    goto exit;
                                }
    
                                if (cardStatus.offsetData == 0) {
                                    result = CARD_RESULT_FATAL_ERROR;
                                    goto exit;
                                }
    
                                /* Reading the entire file. */
                                OSReport("ファイル全体の読み出し\n");
                                u8* data_bufp = cardStatus.length <= chr_to_i8_buf_size ? chr_to_i8_bufp : nullptr;
    
                                if (data_bufp == nullptr) {
                                    result = CARD_RESULT_FATAL_ERROR;
                                    goto exit;
                                }
    
                                result = CARDRead(&fileInfo, data_bufp, cardStatus.length, 0);
                                if (result != CARD_RESULT_READY) {
                                    goto exit;
                                }
    
                                /* File close. */
                                OSReport("ファイルクローズ\n");
                                result = CARDClose(&fileInfo);
                                if (result != CARD_RESULT_READY) {
                                    goto exit;
                                }
    
                                /* Unmount. */
                                OSReport("アンマウント\n");
                                result = CARDUnmount(chan);
                                mounted = FALSE;
                                if (result != CARD_RESULT_READY) {
                                    goto exit;
                                }
    
                                /* Reading successful! */
                                OSReport("読み込み成功！！\n");
                                if (calcSum(data_bufp, cardStatus.length) != 0 || cardStatus.offsetData == 0) {
                                    result = CARD_RESULT_FATAL_ERROR;
                                    goto exit;
                                }
    
                                if (mura_save_name != nullptr) {
                                    memcpy(mura_save_name, cardStatus.fileName, 32);
                                }
    
                                if (famicom_save_name != nullptr) {
                                    memcpy(famicom_save_name, cardStatus.fileName, 32);
                                    famicom_save_name[15] = 'S';
                                }
    
                                u8* datap = &data_bufp[cardStatus.offsetData];
                                memcpy(game_header, datap, sizeof(MemcardGameHeader_t));
                                datap += sizeof(MemcardGameHeader_t);
    
                                /* Copy nesinfo tags */
                                size_t tags_size = game_header->nestags_size;
                                if (tags_size != 0) {
                                    if (tags_pp != nullptr) {
                                        *tags_pp = (u8*)my_malloc(tags_size, 1);
                                    }
    
                                    /* @BUG - tags_pp might be a nullptr but we're dereferencing it anyway */
                                    memcpy(*tags_pp, datap, tags_size);
                                }
                                else {
                                    /* @BUG - tags_pp might be a nullptr but we're dereferencing it anyway */
                                    *tags_pp = nullptr;
                                }
    
                                datap += ALIGN_NEXT(tags_size, 16);
    
                                size_t comment_img_size;
                                if (game_header->flags0.has_comment_img && (comment_img_size = game_header->comment_img_size, comment_img_size != 0)) {
                                    if (JC_JKRDecomp_checkCompressed(datap) == JKRCOMPRESSION_NONE) {
                                        SetupExternCommentImage(datap, memcard_save_comment, data_bufp);
                                    }
                                    else {
                                        JC_JKRDecomp_decode(datap, nesromp, CHR_TO_I8_BUF_SIZE, 0);
                                        SetupExternCommentImage(nesromp, memcard_save_comment, data_bufp);
                                    }
    
                                    datap += ALIGN_NEXT(comment_img_size, 16);
                                }
                                else {
                                    SetupExternCommentImage(nullptr, memcard_save_comment, data_bufp);
                                }
    
                                if (game_header->nesrom_size != 0) {
                                    u32 real_size = game_header->nesrom_size << 4;
    
                                    if (JC_JKRDecomp_checkCompressed(datap) == JKRCOMPRESSION_NONE) {
                                        memcpy(nesromp, datap, real_size);
                                        nesinfo_data_size = real_size;
                                    }
                                    else {
                                        JC_JKRDecomp_decode(datap, nesromp, CHR_TO_I8_BUF_SIZE, 0);
                                        nesinfo_data_size = (u32)((datap[4] << 24) | (datap[5] << 16) | (datap[6]<< 8) | datap[7]);
                                    }
                                }
    
                                result = CARD_RESULT_READY;
                                goto exit; // success
                            }
                            else {
                                now_rom_idx++;
                            }
                        }
                    }
                    else if (result != CARD_RESULT_NOFILE) {
                        goto exit;
                    }
                }
    
                if (fileNo >= 127) {
                    /* There was no target game image in slot %d. */
                    OSReport("スロット%dには目的のゲームイメージがありませんでした\n", chan);
                    CARDUnmount(chan);
                    mounted = FALSE;
                }
            }
        }
        
        /* The rom file was not found */
        result = CARD_RESULT_NOFILE;
    }
    else {
        result = CARD_RESULT_FATAL_ERROR;
    }

exit:
    if (result != CARD_RESULT_READY && result != CARD_RESULT_FATAL_ERROR) {
        errorChan = chan;
    }

    if (result != CARD_RESULT_READY) {
        // Error code = %d.
        OSReport("エラーコード＝%d\n", result);
    }

    if (mounted) {
        CARDUnmount(chan);
    }

    if (workArea != nullptr) {
        my_free(workArea);
    }

    return result;
}

static s32 memcard_game_list(
    int* n_games,
    char* namebufp,
    int namebuf_size
) {
    CARDFileInfo fileInfo;
    CARDStat cardStatus;
    s32 result;
    s32 chan;
    int mounted = FALSE;
    int game_count = 0;
    void* workArea;
    s32 fileNo;
    void* buf = nullptr;
    u32 data_ofs;

    workArea = my_malloc(CARD_WORKAREA_SIZE, 32);
    if (workArea == nullptr) {
        result = CARD_RESULT_FATAL_ERROR;
        goto exit;
    }

    buf = my_malloc(0x200, 32);
    if (buf == nullptr) {
        result = CARD_RESULT_FATAL_ERROR;
        goto exit;
    }

    for (chan = 0; chan < CARD_NUM_CHANS; chan++) {
        mounted = memcard_mount(chan, workArea) == CARD_RESULT_READY;

        if (mounted) {
            for (fileNo = 0; fileNo < 127; fileNo++) {
                result = CARDGetStatus(chan, fileNo, &cardStatus);
                if (result == CARD_RESULT_READY) {
                    if (
                        memcmp(cardStatus.gameName, "GAFE", 4) == 0 &&
                        memcmp(cardStatus.company, "01", 2) == 0 &&
                        memcmp(cardStatus.fileName, "DobutsunomoriP_F_", 17) == 0 &&
                        strcmp(&cardStatus.fileName[17], "SAVE") != 0 /* filename can't be Doubutsunomori_P_F_SAVE* */
                    ) {
                        if (namebuf_size >= 16) {
                            int invalid_game = FALSE;

                            /* Incorporate the contents of the file. */
                            OSReport("ファイルの内容を取り込む\n");
                            static char brokenTitle[] = "##BROKEN GAME##";

                            if (CARDFastOpen(chan, fileNo, &fileInfo) != CARD_RESULT_READY) {
                                invalid_game = TRUE;
                            }
                            else if (cardStatus.offsetData == 0) {
                                invalid_game = TRUE;
                            }
                            else {
                                /* Reading the beginning of the data. */
                                OSReport("データ先頭の読み出し\n");
                                data_ofs = cardStatus.offsetData - ALIGN_PREV(cardStatus.offsetData, 0x200);
                                if (CARDRead(&fileInfo, buf, 0x200, ALIGN_PREV(cardStatus.offsetData, 0x200)) != CARD_RESULT_READY) {
                                    invalid_game = TRUE;
                                }
                                else {
                                    /* File close. */
                                    OSReport("ファイルクローズ\n");
                                    if (CARDClose(&fileInfo) != CARD_RESULT_READY) {
                                        invalid_game = TRUE;
                                    }
                                }
                            }

                            if (invalid_game == FALSE) {
                                /* Reading successful! */
                                OSReport("読み込み成功！！\n");
                                memcpy(namebufp, (u8*)buf + data_ofs + 2, MURA_GAME_NAME_SIZE); // read mori name
                            }
                            else {
                                /* Reading failed! */
                                OSReport("読み込み失敗！！\n");
                                memcpy(namebufp, brokenTitle, MURA_GAME_NAME_SIZE);
                            }

                            namebufp += MURA_GAME_NAME_SIZE;
                            namebuf_size -= MURA_GAME_NAME_SIZE;
                        }

                        (*n_games)++;
                        game_count++;
                    }
                }
                else if (result != CARD_RESULT_NOFILE) {
                    goto exit;
                }
            }

            if (fileNo >= 127) {
                /* Finished searching slot %d. */
                OSReport("スロット%d検索終了\n", chan);
                CARDUnmount(chan);
                mounted = FALSE;
            }
        }
    }

    result = CARD_RESULT_READY;
    *n_games = game_count;
exit:
    if (result != CARD_RESULT_READY) {
        // Error code = %d.
        OSReport("エラーコード＝%d\n", result);
    }

    if (buf != nullptr) {
        my_free(buf);
    }

    if (mounted) {
        CARDUnmount(chan);
    }

    if (workArea != nullptr) {
        my_free(workArea);
    }

    return result;
}

inline JKRFileFinder* getFirstFile(const char* dir) {
    return JKRFileLoader::findFirstFile(dir);
}

static size_t entrylist(const char* dir, char* filename_strbuf) {
    char pathbuf[256];
    u8* filename_buf = (u8*)filename_strbuf;
    JKRFileFinder* fileFinder;
    s32 dir_path_len;
    size_t len;
    
    fileFinder = getFirstFile(dir);
    dir_path_len = strlen(dir);

    if (filename_strbuf != nullptr) {
        filename_strbuf[0] = ':';
        memcpy(filename_strbuf + 1, dir, dir_path_len + 1);
        nesrom_filename_ptrs[nesrom_count] = filename_buf;
    }

    nesrom_count++;
    len = dir_path_len + 2;
    if (fileFinder != nullptr) {
        while (fileFinder->isAvailable()) {
            if (fileFinder->mBase.mFileName[0] != '.') {
                snprintf(pathbuf, sizeof(pathbuf), "%s/%s", dir, fileFinder->mBase.mFileName);
                dir_path_len = strlen(pathbuf);
                if (fileFinder->mIsDir) {
                    len += entrylist(pathbuf, filename_strbuf != nullptr ? filename_strbuf + len : nullptr);
                }
                else {
                    if (filename_strbuf != nullptr) {
                        u8* romname_p = filename_buf + len;

                        memcpy(romname_p, pathbuf, dir_path_len + 1);
                        nesrom_filename_ptrs[nesrom_count] = romname_p;
                    }

                    nesrom_count++;
                    len = 1 + dir_path_len + len;
                }
            }

            fileFinder->findNextFile();
        }

        delete fileFinder;
    }

    return len;
}

static void select_game() {
    int rom_no = famicomCommon.rom_no;
    int rom = rom_no;

    if (famicomCommon.nesrom_memcard == FALSE) {
        nesrom_idx = 0;
        
        while (TRUE) {
            if (*nesrom_filename_ptrs[nesrom_idx] != ':' &&--rom <= 0) {
                break;
            }
            
            nesrom_idx++;

            if (nesrom_idx >= nesrom_count) {
                if (nesrom_idx_loaded < 0) {
                    OSPanic(__FILE__, 4239, "no nesfile specified");
                    continue;
                }

                nesrom_idx = 0;
            }
        }
    }
    else {
        nesrom_idx = rom_no;
    }
}

extern int famicom_mount_archive_end_check() {
#ifdef TARGET_PC
    /* On PC, don't block the title screen if famicom.arc failed to mount.
     * The archive is only needed when actually playing NES games. */
    return 1;
#endif
    return famicom_arc != nullptr;
}

extern void famicom_mount_archive() {
    if (famicom_arc == nullptr && famicom_arc_mounting == false) {
        famicom_arc_mounting = true;
#ifdef TARGET_PC
        /* Use MOUNT_ARAM on PC — JKRAramArchive has byte-swap support for RARC headers */
        famicom_arc = (JKRArchive*)JC__JKRMountArchive("famicom.arc", JKRArchive::MOUNT_ARAM, JC__JKRGetSystemHeap(), JKRArchive::MOUNT_DIRECTION_HEAD);
#else
        famicom_arc = (JKRArchive*)JC__JKRMountArchive("famicom.arc", JKRArchive::MOUNT_COMP, JC__JKRGetSystemHeap(), JKRArchive::MOUNT_DIRECTION_HEAD);
#endif

        if (famicom_arc == nullptr) {
#ifdef TARGET_PC
            printf("[FAMICOM] famicom.arc mount failed — NES games unavailable\n");
#else
            OSDVDFatalError();
#endif
        }

        famicom_arc_mounting = false;
    }

#ifndef TARGET_PC
    JKRAram::getAramHeap()->dump();
#endif
}

static void famicom_mount_archive_wait() {
    if (famicom_arc == nullptr) {
        // Waiting because famicom.arc has not been mounted yet.
        OSReport("famicom.arc がまだマウントされていないので待っています\n");

        do {
            VIWaitForRetrace();
        } while (famicom_arc == nullptr);
    }
}

// clang-format off
#define MALLOC_MALLOC(type, size, dst, line) \
    if (dst != nullptr) {   \
        OSPanic(__FILE__, line, "MALLOC_MALLOC: " #dst " isn't NULL");  \
    }   \
    dst = (type *)my_malloc(size, 32);  \
    if (dst == nullptr) {   \
        /* MALLOC_MALLOC: %s %s %dByte allocation failed. */    \
        OSReport("MALLOC_MALLOC: %s %s %dByte 確保失敗\n", #type, #size, size); \
        goto exit;  \
    }   \
    /* MALLOC_MALLOC: %s %s %dByte successfully allocated. */    \
    OSReport("MALLOC_MALLOC: %s %s %dByte 確保成功\n", #type, #size, size);
// clang-format on

#define CONV_BYTE_KB(bytes) ((f32)(bytes) / 1024.0f)

extern int famicom_init(int rom_idx, Famicom_MallocInfo* malloc_info, int player_no) {
    famicom_mount_archive_wait();
    bzero(&famicomCommon, sizeof(FamicomCommon));
    my_malloc_current = malloc_info;
    
    if (player_no >= 0 && player_no < PLAYER_NUM) {
        famicomCommon.save_pl_no = player_no;
    }
    else {
        famicomCommon.save_pl_no = 0;
    }
    
    if (rom_idx == 0) {
        filer_mode_enable = TRUE;
    }
    else {
        filer_mode_enable = FALSE;
    }
    
    filer_mode = 0;
    filer_demo_mode = FILER_DEMO_MODE_NORMAL;
    filer_demo_count = 0;
    nesrom_idx_loaded = -1;

    if (rom_idx == 0) {
        famicomCommon.nesrom_memcard = FALSE;
        famicomCommon.rom_no = 0;
        nesrom_idx = 1;
    }
    else if (rom_idx > 0) {
        famicomCommon.nesrom_memcard = FALSE;
        famicomCommon.rom_no = rom_idx;

        if (famicomCommon.save_pl_no >= 0 && save_game_image == 0) {
            famicomCommon.save_data_name = (u8*)"GAFEFSC\x1A";
            famicomCommon.save_data_single_size = 0x660;
            famicomCommon.save_data_total_size = sizeof(FamicomSaveDataHeader) + 0x660 * PLAYER_NUM;
            famicomCommon.save_data_header = (FamicomSaveDataHeader*)famicomCommonSave;
            famicomCommon.internal_save_datap = famicomCommonSave + sizeof(FamicomSaveDataHeader) + 0x660 * famicomCommon.save_pl_no;
        }

        nesrom_idx = famicomCommon.rom_no + 1;
        strncpy((char*)famicomCommon.mura_save_name, "DobutsunomoriP_MURA", 32);
        strncpy((char*)famicomCommon.famicom_save_name, "DobutsunomoriP_F_SAVE", 32);
        famicomCommon.unused_save_data_start_ofs = 0x640;
    }
    else if (rom_idx < 0) {
        famicomCommon.nesrom_memcard = TRUE;
        famicomCommon.rom_no = -rom_idx;
        famicomCommon.unused_save_data_start_ofs = 0x3040;
    }

    nesrom_count = 0;
    rapid_count = 0;
    rapid_mode_a = 0;
    rapid_mode_b = 0;
    nines_over_double_click = 0;
    nines_over_mode = 0;
    hispeed_mode = 0;
    slow_mode = 0;
    slow_mode_sub = 0;
    speed_show = 0;
    JKRFileLoader::changeDirectory("/FAMICOM/");
    size_t unused_totalfreesize = my_gettotalfreesize();

    MALLOC_MALLOC(u8, CHR_TO_I8_BUF_SIZE, famicomCommon.chr_to_i8_bufp, 4497);
    MALLOC_MALLOC(u8, KS_NES_NESFILE_HEADER_SIZE + KS_NES_PRGROM_SIZE + KS_NES_CHRROM_SIZE, famicomCommon.nesromp, 4499);
    MALLOC_MALLOC(ksNesCommonWorkObj, sizeof(ksNesCommonWorkObj), famicomCommon.wp, 4501);
    MALLOC_MALLOC(ksNesStateObj, sizeof(ksNesStateObj), famicomCommon.sp, 4502);
    MALLOC_MALLOC(u8, KS_NES_CHRRAM_SIZE, famicomCommon.chrramp, 4505);
    MALLOC_MALLOC(u8, KS_NES_BBRAM_SIZE, famicomCommon.bbramp, 4510);
    MALLOC_MALLOC(u8, KS_NES_NOISE_DATA_SIZE, famicomCommon.noise_bufp, 4515);
    MALLOC_MALLOC(u8, KS_NES_DRAW_RESULT_BUF_SIZE, famicomCommon.result_bufp, 4517);

    famicomCommon.memcard_save_comment = commentImageBuffer;

    OSReport("buffer used:\n");
    OSReport("wp            =%8.3fKB\n", CONV_BYTE_KB(my_getmemblocksize(famicomCommon.wp)));
    OSReport("sp            =%8.3fKB\n", CONV_BYTE_KB(my_getmemblocksize(famicomCommon.sp)));
    OSReport("nesromp       =%8.3fKB\n", CONV_BYTE_KB(my_getmemblocksize(famicomCommon.nesromp)));
    OSReport("chrramp       =%8.3fKB\n", CONV_BYTE_KB(my_getmemblocksize(famicomCommon.chrramp)));
    OSReport("bbramp        =%8.3fKB\n", CONV_BYTE_KB(my_getmemblocksize(famicomCommon.bbramp)));
    OSReport("noise_bufp    =%8.3fKB\n", CONV_BYTE_KB(my_getmemblocksize(famicomCommon.noise_bufp)));
    OSReport("chr_to_i8_bufp=%8.3fKB\n", CONV_BYTE_KB(my_getmemblocksize(famicomCommon.chr_to_i8_bufp)));
    OSReport("result_bufp   =%8.3fKB\n", CONV_BYTE_KB(my_getmemblocksize(famicomCommon.result_bufp)));
    OSReport("total          %8.3fKB.\nif chrrom-type, and no bbram, minimum total size: %8.3fKB + nesrom size max + (nesrom chr size max * 4) bytes.\n",
        CONV_BYTE_KB(my_getmemblocksize(famicomCommon.wp)) +
        CONV_BYTE_KB(my_getmemblocksize(famicomCommon.sp)) +
        CONV_BYTE_KB(my_getmemblocksize(famicomCommon.nesromp)) +
        CONV_BYTE_KB(my_getmemblocksize(famicomCommon.chrramp)) +
        CONV_BYTE_KB(my_getmemblocksize(famicomCommon.bbramp)) +
        CONV_BYTE_KB(my_getmemblocksize(famicomCommon.noise_bufp)) +
        CONV_BYTE_KB(my_getmemblocksize(famicomCommon.chr_to_i8_bufp)) +
        CONV_BYTE_KB(my_getmemblocksize(famicomCommon.result_bufp)),
        CONV_BYTE_KB(my_getmemblocksize(famicomCommon.wp)) +
        CONV_BYTE_KB(my_getmemblocksize(famicomCommon.sp)) +
        CONV_BYTE_KB(my_getmemblocksize(famicomCommon.noise_bufp)) +
        CONV_BYTE_KB(my_getmemblocksize(famicomCommon.result_bufp))
    );

    if (famicomCommon.noise_bufp == nullptr || JKRFileLoader::readGlbResource(famicomCommon.noise_bufp, KS_NES_NOISE_DATA_SIZE, "noise.bin.szs", EXPAND_SWITCH_DECOMPRESS)) {
        if (famicomCommon.noise_bufp != nullptr) {
#ifndef TARGET_PC
            /* On PC, fixNES handles NES audio directly — skip jaudio_NES */
            EmuSound_Start(famicomCommon.noise_bufp + 0x2000);
#endif
        }

        nesrom_idx_loaded = -1;
        if (famicomCommon.nesrom_memcard == FALSE) {
            for (u32 i = 0; i < 2; i++) {
                nesrom_count = 0;
                size_t length = entrylist("GAME", nesrom_filename_strbuf);
                if (i == 0) {
                    if (nesrom_count == 0) {
                        OSReport("no nesfile specified\n");
                        goto exit;
                    }

                    MALLOC_MALLOC(u8 *, nesrom_count * sizeof(u8*), nesrom_filename_ptrs, 4676);
                    MALLOC_MALLOC(char, length, nesrom_filename_strbuf, 4677);
                }
            }
        }
        else {
            nesrom_count = 0;
        }

        select_game();
        JUTProcBar::getManager()->setVisible(false);
        famicomCommon.low_res_mode = true;
        JW_SetFamicomMode(TRUE);
        JW_SetLowResoMode(famicomCommon.low_res_mode);
        return 0; // success
    }

    // error
exit:
    if (famicomCommon.wp != nullptr) {
        my_free(famicomCommon.wp);
    }
    famicomCommon.wp = nullptr;
    
    if (famicomCommon.sp != nullptr) {
        my_free(famicomCommon.sp);
    }
    famicomCommon.sp = nullptr;
    
    if (famicomCommon.nesromp != nullptr) {
        my_free(famicomCommon.nesromp);
    }
    famicomCommon.nesromp = nullptr;
    
    if (famicomCommon.chrramp != nullptr) {
        my_free(famicomCommon.chrramp);
    }
    famicomCommon.chrramp = nullptr;
    
    if (famicomCommon.bbramp != nullptr) {
        my_free(famicomCommon.bbramp);
    }
    famicomCommon.bbramp = nullptr;
    
    if (famicomCommon.noise_bufp != nullptr) {
        my_free(famicomCommon.noise_bufp);
    }
    famicomCommon.noise_bufp = nullptr;
    
    if (famicomCommon.chr_to_i8_bufp != nullptr) {
        my_free(famicomCommon.chr_to_i8_bufp);
    }
    famicomCommon.chr_to_i8_bufp = nullptr;
    
    if (famicomCommon.result_bufp != nullptr) {
        my_free(famicomCommon.result_bufp);
    }
    famicomCommon.result_bufp = nullptr;
    
    if (famicomCommon.highscore_flagsp != nullptr) {
        my_free(famicomCommon.highscore_flagsp);
    }
    famicomCommon.highscore_flagsp = nullptr;

    if (famicomCommon.nesinfo_tagsp != nullptr) {
        my_free(famicomCommon.nesinfo_tagsp);
    }
    famicomCommon.nesinfo_tagsp = nullptr;
    
    return -1;
}

static int SetupResBanner(const ResTIMG* img, u8* dst, size_t max_size, size_t* size, u8* type) {
    size_t banner_size;
    u8* data_p = dst;
    int banner_type;

    if (img != nullptr) {
        banner_size = img->getWidth() * img->getHeight();
        if (img->mTextureFormat != ResTIMG_FORMAT_C8) {
            banner_size *= sizeof(u16);
            banner_type = CARD_STAT_BANNER_RGB5A3;
        }
        else {
            banner_type = CARD_STAT_BANNER_C8;
        }

        bcopy(((u8*)img) + img->mImageDataOffset, data_p, banner_size);
        data_p += banner_size;

        if (img->mPaletteFormat != ResTIMG_NO_PALETTE) {
            size_t pal_size = img->mPaletteEntryCount * sizeof(u16);

            bcopy(((u8*)img) + img->mPaletteOffset, data_p, pal_size);
            bzero(data_p + pal_size, (256 * sizeof(u16)) - pal_size); // zero out unused entries
            data_p += 256 * sizeof(u16);
        }
    }
    else {
        banner_type = CARD_STAT_BANNER_NONE;
    }

    if (size != nullptr) {
        *size = (u32)data_p - (u32)dst;
    }

    if (type != nullptr) {
        *type = banner_type;
    }

    return 0;
}

static int SetupResIcon(const ResTIMG* img, u8* dst, size_t max_size, size_t* size_p, u16* icon_fmt_p, u16* icon_flags_p) {
    u8* data_p = dst;
    size_t icon_size;
    u16 icon_fmt;
    u16 icon_flags;
    int banner_type;
    u32 icon_type;
    int i;
    u32 icon_count;
    int j;

    if (img != nullptr) {
        icon_size = img->getWidth() * img->getHeight();
        icon_count = icon_size / 0x400;

        if (img->mTextureFormat != ResTIMG_FORMAT_C8) {
            icon_size *= sizeof(u16);
            icon_type = CARD_STAT_ICON_RGB5A3;
        }
        else {
            icon_type = CARD_STAT_ICON_C8;
        }

        /* Make icon format flags & speed flags for each frame */
        icon_fmt = 0;
        icon_flags = 0;
        i = 0;
        
        for (j = 0; j < icon_count; j++) {
            icon_fmt |= (icon_type << (i * 2));
            icon_flags |= (CARD_STAT_SPEED_MIDDLE << (i * 2));
            i++;
        }

        bcopy(((u8*)img) + img->mImageDataOffset, data_p, icon_size);
        data_p += icon_size;

        if (img->mPaletteFormat != ResTIMG_NO_PALETTE) {
            size_t pal_size = img->mPaletteEntryCount * sizeof(u16);

            bcopy(((u8*)img) + img->mPaletteOffset, data_p, pal_size);
            bzero(data_p + pal_size, (256 * sizeof(u16)) - pal_size); // zero out unused entries
            data_p += 256 * sizeof(u16);
        }
    }
    else {
        icon_fmt = CARD_STAT_ICON_NONE;
    }

    if (size_p != nullptr) {
        *size_p = (u32)data_p - (u32)dst;
    }

    if (icon_fmt_p != nullptr) {
        *icon_fmt_p = icon_fmt;
    }

    if (icon_flags_p != nullptr) {
        *icon_flags_p = icon_flags;
    }

    return 0;
}

extern int famicom_cleanup() {
    int res = FALSE;

#ifdef TARGET_PC
    /* Sync fixNES battery RAM back to bbramp before save extraction */
    pc_sync_prgram_to_bbramp();
    pc_fixnes_cleanup();
#endif

    if (nesrom_idx_loaded != -1 && save_game_image == 0) {
        OSReport("nesrom_memcard = %d nesrom_idx = %d\n", famicomCommon.nesrom_memcard, nesrom_idx);

        if (famicomCommon.internal_save_datap != nullptr) {
            nesinfo_tag_process3(famicomCommon.internal_save_datap);
        }

        if (famicomCommon.save_pl_no >= 0 && famicomCommon.save_data_header != nullptr) {
            if (famicom_save_data_check((FamicomSaveDataHeader*)famicomCommon.save_data_header, famicomCommon.save_pl_no, famicomCommon.save_data_name) == 0) {
                famicom_save_data_setup((FamicomSaveDataHeader*)famicomCommon.save_data_header, famicomCommon.save_data_single_size, famicomCommon.save_data_name);
            }
            else {
                // Will not save because the common save area is damaged.
                OSReport(VT_COL(RED, WHITE) "共通セーブ領域が壊れているのでセーブしません\n" VT_RST);
                res = TRUE;
            }
        }
    }

    if (famicomCommon.noise_bufp != nullptr) {
        EmuSound_Exit();
    }

    if (famicomCommon.wp != nullptr) {
        my_free(famicomCommon.wp);
    }
    famicomCommon.wp = nullptr;
    
    if (famicomCommon.sp != nullptr) {
        my_free(famicomCommon.sp);
    }
    famicomCommon.sp = nullptr;
    
    if (famicomCommon.nesromp != nullptr) {
        my_free(famicomCommon.nesromp);
    }
    famicomCommon.nesromp = nullptr;
    
    if (famicomCommon.chrramp != nullptr) {
        my_free(famicomCommon.chrramp);
    }
    famicomCommon.chrramp = nullptr;
    
    if (famicomCommon.bbramp != nullptr) {
        my_free(famicomCommon.bbramp);
    }
    famicomCommon.bbramp = nullptr;
    
    if (famicomCommon.noise_bufp != nullptr) {
        my_free(famicomCommon.noise_bufp);
    }
    famicomCommon.noise_bufp = nullptr;
    
    if (famicomCommon.chr_to_i8_bufp != nullptr) {
        my_free(famicomCommon.chr_to_i8_bufp);
    }
    famicomCommon.chr_to_i8_bufp = nullptr;
    
    if (famicomCommon.result_bufp != nullptr) {
        my_free(famicomCommon.result_bufp);
    }
    famicomCommon.result_bufp = nullptr;
    
    if (famicomCommon.highscore_flagsp != nullptr) {
        my_free(famicomCommon.highscore_flagsp);
    }
    famicomCommon.highscore_flagsp = nullptr;

    if (nesrom_filename_ptrs != nullptr) {
        my_free(nesrom_filename_ptrs);
    }
    nesrom_filename_ptrs = nullptr;

    if (nesrom_filename_strbuf != nullptr) {
        my_free(nesrom_filename_strbuf);
    }
    nesrom_filename_strbuf = nullptr;

    my_malloc_current = nullptr;
    JW_SetLowResoMode(FALSE);
    JW_SetFamicomMode(FALSE);
    return res;
}

static s32 famicom_common_save_initial();

static int famicom_rom_load() {
    int nesrom_buffer_size = my_getmemblocksize(famicomCommon.nesromp);
    nesinfo_init();
    OSReport("nesrom_buffer_size=%d\n", nesrom_buffer_size);

    if (nesrom_buffer_size >= KS_NES_CHRROM_SIZE) {
        bzero(famicomCommon.nesromp, KS_NES_CHRROM_SIZE);
    }

    if (famicomCommon.nesrom_memcard != FALSE) {
        /* Loading the game image from the memory card. */
        OSReport("ゲームイメージをメモリーカードから読み込みます\n");
        s32 load_res = memcard_game_load(
            famicomCommon.nesromp,
            famicomCommon.rom_no - 1,
            &famicomCommon.nesinfo_tagsp,
            (char*)famicomCommon.mura_save_name,
            (char*)famicomCommon.famicom_save_name,
            &famicomCommon.memcard_game_header,
            famicomCommon.memcard_save_comment, // comment & images
            famicomCommon.unused_save_data_start_ofs,
            famicomCommon.chr_to_i8_bufp,
            CHR_TO_I8_BUF_SIZE
        );

        if (load_res == CARD_RESULT_READY) {
            /* Loaded the game image from the memory card. */
            OSReport("ゲームイメージをメモリーカードから読み込みました\n");
            nesinfo_tags_start = famicomCommon.nesinfo_tagsp;
            nesinfo_tags_end = nesinfo_tags_start + famicomCommon.memcard_game_header.nestags_size;
            nesinfo_tags_size = nesinfo_tags_end - nesinfo_tags_start;
            nesinfo_data_start = famicomCommon.nesromp;
            nesinfo_data_end = nesinfo_data_start + nesinfo_data_size;
        }
        else {
            /* Failed to load game [%d]. */
            OSReport("ゲーム読み込みに失敗しました [%d]\n", load_res);
            return -1;
        }
    }
    else {
        const char* filename = (char*)nesrom_filename_ptrs[nesrom_idx];
        OSReport("%d:<%s>\n", nesrom_idx, filename);
        bzero(famicomCommon.nesromp, nesrom_buffer_size);
        size_t loaded_size = JKRFileLoader::readGlbResource(famicomCommon.nesromp, nesrom_buffer_size, filename, EXPAND_SWITCH_DECOMPRESS);
        if (loaded_size == 0) {
            return -1;
        }

        nesinfo_tags_set(famicomCommon.rom_no - 1);

        nesinfo_data_size = loaded_size;
        nesinfo_data_start = famicomCommon.nesromp;
        nesinfo_data_end = nesinfo_data_start + loaded_size;

        MemcardGameHeader_t* memcard_game_header = &famicomCommon.memcard_game_header;
        bzero(memcard_game_header, sizeof(MemcardGameHeader_t));
        memcard_game_header->_00 = 'G';
        memcard_game_header->_01 = 0;
        strncpy((char*)memcard_game_header->mori_name, (char*)nesinfo_get_moriName(), MURA_GAME_NAME_SIZE);
        memcard_game_header->nesrom_size = 0;
        memcard_game_header->nestags_size = 0;
        memcard_game_header->flags0.has_comment_img = TRUE;
        memcard_game_header->flags0.no_copy_flag = FALSE;
        memcard_game_header->flags1.no_move_flag = FALSE;
#ifndef TARGET_PC
        SetupInternalCommentImage(famicomCommon.memcard_save_comment);
#endif
    }

    u32 max_ofs = 0;
    tcs_bad = false;
    ics_bad = false;

    nesinfo_tag_process1(nullptr, 0, &max_ofs);

    if (ics_bad || tcs_bad) {
        if (tcs_bad) {
            // Tag checksum is incorrect.
            OSReport(VT_COL(YELLOW, BLACK) "タグチェックサムが違います\n" VT_RST);
        }

        if (ics_bad) {
            // Image checksum is incorrect.
            OSReport(VT_COL(YELLOW, BLACK) "イメージチェックサムが違います\n" VT_RST);
        }

        return -1;
    }

    if (famicomCommon.nesrom_memcard && famicomCommon.save_pl_no >= 0) {
        famicomCommon.save_data_name = (u8*)"GAFEFSE\x1A";
        famicomCommon.save_data_single_size = max_ofs + 0xB;
        famicomCommon.save_data_total_size = famicomCommon.save_data_single_size * PLAYER_NUM + sizeof(FamicomSaveDataHeader);
        famicomCommon.save_data_header = (FamicomSaveDataHeader*)nintendo_hi_0; // overwritten for use with save data
        famicomCommon.internal_save_datap = nintendo_hi_0 + sizeof(FamicomSaveDataHeader) + famicomCommon.save_data_single_size * famicomCommon.save_pl_no;
        bzero(famicomCommon.save_data_header, famicomCommon.save_data_total_size);
    }

    if (famicomCommon.nesrom_memcard == FALSE) {
        famicomCommon.internal_save_datap = famicomCommonSave + sizeof(FamicomSaveDataHeader) + 0x660 * famicomCommon.save_pl_no;
    }
    else if (famicomCommon.save_data_header != nullptr) {
        famicom_common_save_initial();
    }

    if (famicomCommon.internal_save_datap != nullptr) {
        nesinfo_tag_process1(famicomCommon.internal_save_datap, 1, nullptr);
    }

    famicomCommon.highscore_flagsp = (u8*)my_malloc(nesinfo_get_highscore_num(), 32);
    highscore_setup_flags(famicomCommon.highscore_flagsp);
    nesinfo_tag_process2();
    
    ksNesCommonWorkObj* wp = famicomCommon.wp;
    wp->nesromp = famicomCommon.nesromp;
    u32 flags = 0;
    wp->prg_size = KS_NES_PRGROM_SIZE;
    wp->noise_bufp = famicomCommon.noise_bufp;
    wp->fds_disk_count = 4;
    wp->chr_to_u8_bufp = famicomCommon.chr_to_i8_bufp;
    wp->chr_to_i8_buf_size = CHR_TO_I8_BUF_SIZE;
    wp->result_bufp = famicomCommon.result_bufp;
    wp->total_cpu_cycles = 0;

    if (famicomCommon.noise_bufp == nullptr) {
        flags |= 0x40; // no sound?
    }

    int reset_res = ksNesReset(wp, famicomCommon.sp, flags | 0x10, famicomCommon.chrramp, famicomCommon.bbramp);
    if (reset_res != 0) {
        OSReport("err code=%d (0x%x), %x,%x,%x,%x,%x,%x\n",
            reset_res, reset_res, famicomCommon.wp, famicomCommon.sp,
            famicomCommon.wp->draw_ctx.sprite_scanline_limit, famicomCommon.wp->draw_ctx.ppu_scanline_regs,
            famicomCommon.wp->draw_ctx.post_process_lut, famicomCommon.sp->ppu_chr_banks
        );
        OSReport("NES emu reset failed!!");
    }
    else {
#ifdef TARGET_PC
        /* Initialize fixNES with the loaded ROM, then load battery RAM save */
        pc_fixnes_init(famicomCommon.nesromp, nesrom_buffer_size);
        pc_sync_bbramp_to_prgram();
        /* Fill sp->wram with 0xFF so the HSC UNSET→SET check doesn't
         * prematurely match all-zero initial values before the NES game
         * boots and writes its own defaults. On GC, ksNesReset leaves
         * wram[0x000..0x1FF] as heap garbage, achieving the same effect.
         * The first forward sync (after fixNES runs a few frames) will
         * overwrite this with real Main_Mem data. */
        memset(famicomCommon.sp->wram, 0xFF, KS_NES_WRAM_SIZE);
#endif
        OSReport("ksNesReset() OK PC=%x, prg_size = 0x%x, chr_size = 0x%x\n",
            famicomCommon.sp->PC, famicomCommon.sp->prg_size, famicomCommon.sp->chr_size);
        nesrom_idx_loaded = nesrom_idx;
        return 0;
    }

    return -1;
}

static void famicom_key_convert() {
    u32 input;
    
    for (int i = 0; i < PAD_MAX_CONTROLLERS; i++) {

        if (InputValid[i]) {
            input = InputData[i];
        }
        else {
            input = 0;
        }

        if (rapid_mode_a && (input & JUTGamePad::A) && (rapid_count & 0x80000000)) {
            input ^= JUTGamePad::A;
        }

        if (rapid_mode_b && (input & JUTGamePad::B) && (rapid_count & 0x40000000)) {
            input ^= JUTGamePad::B;
        }

        if (filer_mode != 0 || filer_demo_mode != FILER_DEMO_MODE_NORMAL) {
            input &= ~(JUTGamePad::A | JUTGamePad::B);
        }

        input =
          (((input >>  2) & 3) << 26) // DPad up & down
        | (((input >>  0) & 1) << 25) // DPad left (0x02000000)
        | (((input >>  1) & 1) << 24) // DPad right (0x01000000)
        | (((input >>  8) & 1) << 31) // A -> A (0x80000000)
        | (((input >>  9) & 1) << 30) // B -> B (0x40000000)
        | (((input >> 10) & 1) << 29) // X -> Select (0x20000000)
        | (((input >>  4) & 1) << 29) // Z -> Select (0x20000000)
        | (((input >> 11) & 1) << 28) // Y -> Start (0x10000000)
        | (((input >> 12) & 1) << 28) // Start -> Start (0x10000000)
        | (((input >> 24) & 1) ? (1 << 25) : (0 << 25)) // Left analog stick -> Pad Left
        | (((input >> 25) & 1) ? (1 << 24) : (0 << 24)) // Right analog stick -> Pad Right
        | (((input >> 26) & 1) ? (1 << 26) : (0 << 26))     // Down analog stick -> Pad Down
        | (((input >> 27) & 1) ? (1 << 27) : (0 << 27))     // Up analog stick -> Pad Up
        ;
        
        switch (i) {
            case 0:
                famicomCommon.wp->pads[0] = input;
                break;
            case 1:
                famicomCommon.wp->pads[2] = input;
                break;
            case 2:
                famicomCommon.wp->pads[1] = input;
                break;
            case 3:
                famicomCommon.wp->pads[3] = input;
                break;
        }
    }

    rapid_count += 0xABCD0000;
}

static void famicom_draw() {
    GXTexObj famicomTexObj;

    GXSetScissor(0, 0, 640, 480);
    GXSetViewport(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    ksNesDrawInit(famicomCommon.wp);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetNumIndStages(0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGB, GX_RGBA4, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_CLR_RGBA, GX_RGBX8, 9);
    GXInitTexObj(&famicomTexObj, famicomCommon.wp->result_bufp, (u16)KS_NES_WIDTH, (u16)KS_NES_HEIGHT, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&famicomTexObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&famicomTexObj, GX_TEXMAP0);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_FALSE, 0, 0);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);

    int n2; // r0
    int n0; // r4
    int n3; // r3
    int n1; // r6

    if (filer_mode != 0 || filer_demo_mode != FILER_DEMO_MODE_NORMAL) {
        n2 = 256;
        n0 = KS_NES_HEIGHT;
        n3 = -288;
        n1 = KS_NES_HEIGHT;

    }
    else {
        n2 = 256;
        n0 = KS_NES_HEIGHT;
        n3 = 30;
        n1 = 6;
    }
    

    // vertex 0
    GXPosition2s16(320 - n3, -8 - n1);
    GXTexCoord2s16(512, 0);
    
    // vertex 1
    GXPosition2s16(320 - n3, -8 - n1 - n0);
    GXTexCoord2s16(512, 512);
    
    // vertex 2
    GXPosition2s16(320 - n3 - n2, -8 - n1 - n0);
    GXTexCoord2s16(0, 512);

    // vertex 3
    GXPosition2s16(320 - n3 - n2, -8 - n1);
    GXTexCoord2s16(0, 0);

    ksNesDrawEnd();
}

static void* ksnes_proc(void* param) {
    u32* flags_p = (u32*)param;

    ksNesEmuFrame(famicomCommon.wp, famicomCommon.sp, *flags_p);
    return nullptr;
}

static void ksnes_thread_kill(OSAlarm* alarm, OSContext* context) {
    /* Famicom emulator crashed. */
    OSReport(VT_COL(YELLOW, BLACK) "ファミコンエミュ死亡\n" VT_RST);
    OSCancelThread(&ksnes_thread);
}

static int ksnes_thread_exec(u32 flags) {
#ifdef TARGET_PC
    /* On PC, use fixNES emulator for NES rendering + audio */
    {
        /* Convert AC pad format to fixNES format.
         * AC pads[0] bits: 31=A, 30=B, 29=Select, 28=Start, 27=Up, 26=Down, 25=Left, 24=Right
         * fixNES expects:  bit0=A, bit1=B, bit2=Select, ..., bit7=Right */
        static unsigned int turbo_counter = 0;
        turbo_counter++;
        unsigned int pad = famicomCommon.wp->pads[0];
        unsigned char raw = (unsigned char)((pad >> 24) & 0xFF);
        /* Reverse bit order */
        unsigned char buttons = 0;
        for (int b = 0; b < 8; b++)
            buttons |= ((raw >> (7 - b)) & 1) << b;
        /* GC X → turbo A, GC Y → turbo B (read from raw InputData) */
        {
            unsigned int raw_input = InputValid[0] ? InputData[0] : 0;
            /* GC X = bit 10, GC Y = bit 11 */
            if ((raw_input & (1 << 10)) && (turbo_counter & 2))
                buttons |= 1; /* turbo A (bit 0) */
            if ((raw_input & (1 << 11)) && (turbo_counter & 2))
                buttons |= 2; /* turbo B (bit 1) */
        }
        pc_fixnes_set_input(buttons);
        unsigned short* fb = pc_fixnes_frame();
        pc_fixnes_render_frame(fb);
        /* Sync fixNES internal RAM → ksNes wram every 2 frames so
         * nesinfo_update_highscore can detect high-score changes. */
        if (famicomCommon.sp != nullptr && (turbo_counter & 1) == 0) {
            pc_fixnes_sync_wram(famicomCommon.sp->wram);
        }
    }
    return 0;
#endif
    int res;
    u8* ksnes_emu_stack = (u8*)my_malloc(KS_NES_EMU_STACK_SIZE, 32);

    if (ksnes_emu_stack != nullptr) {
        OSTime timeout = OSMillisecondsToTicks(2000); // 2 second timeout

        if (famicomCommon.sp->motor_timer != 0) {
            // Disk motor is on.
            OSReport("ディスクモーターオン\n");
        }
        
        OSTime frame_start_time = OSGetTime();
        s32 prio = OSGetThreadPriority(OSGetCurrentThread());
        OSAlarm alarm;

        OSCreateThread(&ksnes_thread, &ksnes_proc, &flags, ksnes_emu_stack + KS_NES_EMU_STACK_SIZE, KS_NES_EMU_STACK_SIZE, prio + 1, 0);
        OSCreateAlarm(&alarm);
        OSResumeThread(&ksnes_thread);
        OSSetAlarm(&alarm, timeout, &ksnes_thread_kill);
        OSJoinThread(&ksnes_thread, (void**)&res);
        OSCancelAlarm(&alarm);

        OSTime frame_end_time = OSGetTime();

        if ((frame_end_time - frame_start_time) > OSMillisecondsToTicks(16)) {
            OSTime ms = OSTicksToMicroseconds(frame_end_time - frame_start_time); // isn't this supposed to be OSTicksToMilliseconds?

            // Emulator slow %d ms.
            OSReport(VT_COL(YELLOW, BLACK) "エミュ遅い %d ms\n" VT_RST, ms);
        }

        my_free(ksnes_emu_stack);
        return res;
    }
    else {
        return -2; // failed to allocate stack
    }
}

#pragma dont_inline on // @HACK - necessary to not inline JUTGamePad::getPortStatus
static void nogbaInput() {
    int port;
    u32 disconnected_ports = 0;

    for (port = 0; port < PAD_MAX_CONTROLLERS; port++) {
        InputValid[port] = false;

        // switch (GetPortStatus(port)) {
        switch ((int)JUTGamePad::getPortStatus((JUTGamePad::EPadPort)port)) {
            case PAD_ERR_NONE:
            {
                InputValid[port] = true;

                InputData[port] = ((JUTGamePad*)gamePad)[port].mButtons.mButton;
                
                if (((JUTGamePad*)gamePad)[port].mButtons.mAnalogL != 0) {
                    InputData[port] |= JUTGamePad::L;
                }

                if (((JUTGamePad*)gamePad)[port].mButtons.mAnalogR != 0) {
                    InputData[port] |= JUTGamePad::R;
                }
                break;
            }

            case PAD_ERR_NO_CONTROLLER:
            {
                disconnected_ports |= (0x80000000 >> port);
                break;
            }
        }
    }

    if (disconnected_ports != 0) {
        PADReset(disconnected_ports);
    }

    for (int port = 0; port < PAD_MAX_CONTROLLERS; port++) {
        if (InputValid[port]) {            
            InputTrigger[port] = InputData[port] & (InputButton[port] ^ InputData[port]); // Update trigger to only newly pressed buttons
            InputButton[port] = InputData[port]; // update pressed buttons

            if (InputButton[port] == 0) {
                InputRepeat[port] = 0;
            }
            else if (InputTrigger[port] != 0) {
                InputRepeat[port] = InputButton[port];
                InputRepeatCount[port] = 15;
            }
            else {
                if (InputRepeatCount[port] != 0) {
                    InputRepeatCount[port]--;
                    InputRepeat[port] = 0;
                }
                else {
                    InputRepeatCount[port] = 0;
                    InputRepeat[port] = InputButton[port];
                }
            }
        }
        else {
            InputButton[port] = 0;
            InputTrigger[port] = 0;
            InputRepeat[port] = 0;
        }
    }
}
#pragma dont_inline reset

// @HACK - we need to force J2DOrthoGraph's dtor to emit
static void fake() {
    J2DOrthoGraph graph;

    graph.~J2DOrthoGraph();
}

extern void famicom_1frame() {
    nogbaInput();
    u32 flags = 0;

    if (famicomCommon.noise_bufp == nullptr) {
        flags |= 0x1000;
    }

    famicom_key_convert();
    famicomCommon.wp->pads[4] = 0;
    famicomCommon.wp->pads[5] = 0;
    famicomCommon.wp->pads[6] = 0;

    /* Special input modes activated when L & R are held */
    /*
        Always - L + R + START = reset console
        Zurumode 1 - L + R + D-Left = Toggle obj 9 'over' mode
        Zurumode 1 - L + R + A = Toggle rapid A mode
        Zurumode 1 - L + R + B = Toggle rapid B mode
    */
    if ((InputButton[0] & (JUTGamePad::L | JUTGamePad::R)) == (JUTGamePad::L | JUTGamePad::R) &&
        filer_mode == 0 && filer_demo_mode == FILER_DEMO_MODE_NORMAL) {
        if ((InputTrigger[0] & JUTGamePad::START)) {
            if (famicomCommon.internal_save_datap != nullptr) {
                nesinfo_update_highscore(famicomCommon.internal_save_datap, 1);
            }

            ksNesPushResetButton(famicomCommon.sp);
        }

        if (APPNMI_ZURUMODE_GET()) {
            if ((InputTrigger[0] & JUTGamePad::DPAD_LEFT)) {
                nines_over_mode ^= TRUE;

                JUTReport(30, 46, 30, "OBJ 9'S OVER %s", nines_over_mode ? "DISABLED" : "ENABLED");
            }

            if ((InputTrigger[0] & JUTGamePad::DPAD_RIGHT)) {
                famicomCommon.low_res_mode ^= TRUE;
            }

            if ((InputTrigger[0] & JUTGamePad::A)) {
                rapid_mode_a ^= TRUE;
            }

            if ((InputTrigger[0] & JUTGamePad::B)) {
                rapid_mode_b ^= TRUE;
            }
        }
    }

    if (nesrom_idx_loaded != -1 &&
        ((InputButton[0] & (JUTGamePad::L | JUTGamePad::R)) !=  (JUTGamePad::L | JUTGamePad::R) || ((InputButton[0] & JUTGamePad::START) == 0 && APPNMI_ZURUMODE_GET() == 0))) {
        u32 frames = 1;
        
        if (APPNMI_ZURUMODE_GET() && (InputButton[0] & JUTGamePad::L)) {
            /* When zurumode 1 is enabled, L + C-Stick (Left/Right) adjusts emulation speed */
            JUTGamePad* pad = (JUTGamePad*)&gamePad[0];
            if (pad->mSubStick.mX > 0.1) {
                hispeed_mode = 2.0f + (pad->mSubStick.mX - 0.1f) * 8.9f;
                slow_mode = 0;
                speed_show = 60;
            }
            else if (pad->mSubStick.mX < -0.1) {
                slow_mode = 2.0f + (-pad->mSubStick.mX - 0.1f) * 3.4f;
                hispeed_mode = 0;
                speed_show = 60;
            }
            else {
                slow_mode = 0;
                hispeed_mode = 0;
                speed_show = 0;
            }
        }

        if (nines_over_mode) {
            flags |= KS_NES_FLAG_NINES_OVER_MODE;
        }

        
        if (slow_mode != 0) {
            frames = 1;
            if (speed_show != 0) {
                JUTReport(32, 48, 1, "1/%d SPEED", slow_mode);
            }
        }


        if (hispeed_mode != 0) {
            frames = hispeed_mode;
            if (speed_show != 0) {
                JUTReport(32, 48, 1, "%2dX SPEED", hispeed_mode);
            }
        }

        if (speed_show != 0) {
            speed_show--;
        }

        famicomCommon.wp->cpu_cycle_count = 0;
        famicomCommon.wp->frames = frames;

        do {
            if (slow_mode != 0) {
                slow_mode_sub++;
                if (slow_mode_sub < slow_mode) {
                    for (int j = 0; j < 262; j++) {
                        Sound_Write(0, 0, j * 114);   
                    }
                    break;
                }

                slow_mode_sub = 0;
            }

            ksnes_thread_exec(flags);
        } while (--frames > 0);
    }
    else {
        for (int j = 0; j < 262; j++) {
            Sound_Write(0, 0, j * 114);   
        }
    }

#ifndef TARGET_PC
    GXSetScissor(0, 0, 640, 480);
    GXSetViewport(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    ksNesDraw(famicomCommon.wp, famicomCommon.sp);
#endif

    if (filer_mode != 0 || filer_demo_mode != FILER_DEMO_MODE_NORMAL) {
        JW_SetLowResoMode(FALSE);
        process_filer_mode();
    }
    else {
        JW_SetLowResoMode(famicomCommon.low_res_mode);
    }

    JW_SetFamicomMode(TRUE);

    famicom_draw();

    /* If filer mode is enabled, controller 4 L press toggles process profiling bar */
    if (filer_mode_enable && (((JUTGamePad*)gamePad)[3].mButtons.mTrigger & JUTGamePad::L)) {
        JUTProcBar::getManager()->setVisible(JUTProcBar::getManager()->isVisible() ? FALSE : TRUE);
    }

    if (filer_demo_mode != FILER_DEMO_MODE_NORMAL) {
        filer_demo_count++;

        if (filer_demo_count > 1200) {
            filer_demo_count = 0;
            nesrom_idx = nesrom_idx < (nesrom_count - 1) ? (nesrom_idx + 1) : 0;
        }

        if ((InputTrigger[0] & (
            JUTGamePad::MAINSTICK_LEFT |
            JUTGamePad::MAINSTICK_RIGHT |
            JUTGamePad::MAINSTICK_DOWN |
            JUTGamePad::MAINSTICK_UP |
            JUTGamePad::DPAD_LEFT |
            JUTGamePad::DPAD_RIGHT |
            JUTGamePad::DPAD_DOWN |
            JUTGamePad::DPAD_UP |
            JUTGamePad::L |
            JUTGamePad::R |
            JUTGamePad::A |
            JUTGamePad::X |
            JUTGamePad::Y
        ))) {
            filer_demo_mode = FILER_DEMO_MODE_NORMAL;
            filer_mode = 1;
        }
    }

    if (filer_mode_enable != FALSE && (InputTrigger[0] & JUTGamePad::R)) {
        filer_mode ^= 1;
        filer_demo_mode = FILER_DEMO_MODE_NORMAL;
    }

    if ((flags & 0x400) != 0 && famicomCommon.sp->motor_timer != 0 && (famicomCommon.sp->vblank_frame_counter & 0x10)) {
        // Please wait
        JUTReport(400, 350, 1, "omati kudasai...");
    }

    if (famicomCommon.internal_save_datap != nullptr) {
        nesinfo_update_highscore(famicomCommon.internal_save_datap, 0);
    }
}

extern int famicom_rom_load_check() {
    if (famicomCommon.nesrom_memcard == FALSE) {
        while (*nesrom_filename_ptrs[nesrom_idx] == ':') {
            nesrom_idx++;
            if (nesrom_idx >= nesrom_count) {
                if (nesrom_idx_loaded < 0) {
                    OSPanic(__FILE__, 6072, "no nesfile specified");
                    continue;
                }

                nesrom_idx = 0;
            }
        }
    }

    if (nesrom_idx_loaded != nesrom_idx) {
        if (famicom_rom_load() == 0) {
            nesrom_idx_loaded = nesrom_idx;
        }
        else {
            nesrom_idx_loaded = -1;
        }
    }

    return nesrom_idx_loaded;
}

static int famicom_cardResultToMiyake(s32 cardResult) {
    switch (cardResult) {
        case CARD_RESULT_READY:
            return FAMICOM_RESULT_OK;
        case CARD_RESULT_INSSPACE:
            return FAMICOM_RESULT_NOSPACE;
        case CARD_RESULT_NOENT:
            return FAMICOM_RESULT_NOENTRY;
        case CARD_RESULT_BROKEN:
            return FAMICOM_RESULT_BROKEN;
        case CARD_RESULT_WRONGDEVICE:
            return FAMICOM_RESULT_WRONGDEVICE;
        case CARD_RESULT_ENCODING:
            return FAMICOM_RESULT_WRONGENCODING;
        case CARD_RESULT_NOCARD:
            return FAMICOM_RESULT_NOCARD;
        case CARD_RESULT_NOFILE:
            return FAMICOM_RESULT_NOFILE;
        default:
            return -1;
    }
}

extern int famicom_internal_data_load() {
#ifdef TARGET_PC
    /* PC: Load NES save data from local file */
    bzero(&famicomCommon, sizeof(FamicomCommon));
    famicomCommon.nesrom_memcard = FALSE;
    strncpy((char*)famicomCommon.mura_save_name, "DobutsunomoriP_MURA", 32);
    strncpy((char*)famicomCommon.famicom_save_name, "DobutsunomoriP_F_SAVE", 32);
    famicomCommon.save_data_name = (u8*)"GAFEFSC\x1A";
    famicomCommon.save_data_single_size = 0x660;
    famicomCommon.save_data_total_size = sizeof(FamicomSaveDataHeader) + 0x660 * PLAYER_NUM;
    famicomCommon.save_data_header = (FamicomSaveDataHeader*)famicomCommonSave;
    famicomCommon.internal_save_datap = nullptr;
    {
        char nes_path[300];
        snprintf(nes_path, sizeof(nes_path), "%s/DobutsunomoriP_F_SAVE.sav", pc_nes_save_dir());
        FILE* f = fopen(nes_path, "rb");
        if (f) {
            fread(famicomCommonSave, 1, sizeof(famicomCommonSave), f);
            fclose(f);
        }
    }
    return 0;
#endif
    famicom_mount_archive_wait();
    bzero(&famicomCommon, sizeof(FamicomCommon));
    famicomCommon.nesrom_memcard = FALSE;
    strncpy((char*)famicomCommon.mura_save_name, "DobutsunomoriP_MURA", 32);
    strncpy((char*)famicomCommon.famicom_save_name, "DobutsunomoriP_F_SAVE", 32);
    famicomCommon.save_data_name = (u8*)"GAFEFSC\x1A";
    famicomCommon.save_data_single_size = 0x660;
    famicomCommon.save_data_total_size = sizeof(FamicomSaveDataHeader) + 0x660 * PLAYER_NUM;
    famicomCommon.save_data_header = (FamicomSaveDataHeader*)famicomCommonSave;
    famicomCommon.internal_save_datap = nullptr;

    s32 cardResult = famicom_common_save_initial();
    s32 chan;
    if (cardResult == CARD_RESULT_NOFILE) {
        chan = famicom_getSaveChan(famicomCommon.nesrom_memcard, &cardResult);
        if (chan >= 0) {
            s32 freeBytes;
            s32 freeEntries;

            cardResult = memcard_getFreeBlocks(chan, &freeBytes, &freeEntries);
            if (cardResult == CARD_RESULT_READY) {
                if (freeEntries < 1) {
                    cardResult = CARD_RESULT_NOENT;
                }
                else if (freeBytes < 0x2000) {
                    cardResult = CARD_RESULT_INSSPACE;
                }
            }
        }
    }

    /* @BUG - chan can be an invalid value due to being allocted on the stack & cardResult not being CARD_RESULT_NOFILE */
    if (cardResult != CARD_RESULT_READY && cardResult != CARD_RESULT_FATAL_ERROR && chan >= 0) {
        errorChan = chan;
    }

    return famicom_cardResultToMiyake(cardResult);
}

extern int famicom_internal_data_save() {
#ifdef TARGET_PC
    /* PC: Write NES save data to local file */
    {
        char nes_path[300];
        snprintf(nes_path, sizeof(nes_path), "%s/DobutsunomoriP_F_SAVE.sav", pc_nes_save_dir());
        FILE* f = fopen(nes_path, "wb");
        if (f) {
            fwrite(famicomCommonSave, 1, sizeof(famicomCommonSave), f);
            fclose(f);
        }
    }
    return 0;
#endif
    s32 result;
    s32 chan;

    famicom_mount_archive_wait();
    bzero(&famicomCommon, sizeof(FamicomCommon));
    famicomCommon.nesrom_memcard = FALSE;
    strncpy((char*)famicomCommon.mura_save_name, "DobutsunomoriP_MURA", 32);
    strncpy((char*)famicomCommon.famicom_save_name, "DobutsunomoriP_F_SAVE", 32);
    famicomCommon.save_data_name = (u8*)"GAFEFSC\x1A";
    famicomCommon.save_data_single_size = 0x660;
    famicomCommon.save_data_total_size = sizeof(FamicomSaveDataHeader) + 0x660 * PLAYER_NUM;
    famicomCommon.save_data_header = (FamicomSaveDataHeader*)famicomCommonSave;
    famicomCommon.internal_save_datap = nullptr;

    chan = famicom_getSaveChan(FALSE, &result);
    if (chan >= 0) {
        famicomCommon.unused_save_data_start_ofs = 0x640;
        famicomCommon.memcard_save_comment = commentImageBuffer;
        famicomCommon.memcard_game_header.flags0.no_copy_flag = FALSE;
        famicomCommon.memcard_game_header.flags1.no_move_flag = FALSE;
        SetupInternalCommentImage(commentImageBuffer);

        if (famicom_save_data_check(famicomCommon.save_data_header, famicomCommon.save_pl_no, famicomCommon.save_data_name) == 0) {
            int no_save = famicomCommon.save_data_header->no_save;
            famicomCommon.save_data_header->no_save = FALSE;

            famicom_save_data_setup(famicomCommon.save_data_header, famicomCommon.save_data_single_size, famicomCommon.save_data_name);
            memcard_data_load(chan, (char*)famicomCommon.famicom_save_name, (char*)famicomCommon.mura_save_name, nullptr, famicomCommon.save_data_total_size, famicomCommon.save_data_name);
            
            result = memcard_data_save(
                chan,
                (char*)famicomCommon.famicom_save_name,
                (char*)famicomCommon.mura_save_name,
                famicomCommon.save_data_header,
                famicomCommon.save_data_total_size,
                famicomCommon.memcard_save_comment,
                famicomCommon.memcard_game_header.flags1.banner_fmt,
                famicomCommon.memcard_game_header.flags0.comment_type == MEMCARD_COMMENT_TYPE_NONE ? 0xFFFFFFFF : CARD_COMMENT_SIZE,
                famicomCommon.memcard_game_header.icon_format,
                famicomCommon.memcard_game_header.icon_flags,
                famicomCommon.memcard_game_header.flags0.comment_type == MEMCARD_COMMENT_TYPE_NONE ? 0xFFFFFFFF : 0,
                no_save
            );
        }
    }

    if (result != CARD_RESULT_READY && result != CARD_RESULT_FATAL_ERROR && chan >= 0) {
        errorChan = chan;
    }

    return famicom_cardResultToMiyake(result);
}

extern int famicom_external_data_save() {
#ifdef TARGET_PC
    return 0;
#endif
    s32 result;
    s32 chan;

    famicom_mount_archive_wait();
    if (famicomCommon.nesrom_memcard == FALSE) {
        result = CARD_RESULT_FATAL_ERROR;
    }
    else if (famicomCommon.save_data_header == nullptr) {
        result = CARD_RESULT_NOCARD;
        chan = 2;
    }
    else {
        chan = famicom_getSaveChan(TRUE, &result);
        if (chan >= 0) {
            if (famicom_save_data_check((FamicomSaveDataHeader*)famicomCommon.save_data_header, -1, famicomCommon.save_data_name) == 0) {
                if (famicomCommon.nesrom_memcard && famicomCommon.memcard_game_header.flags0.has_comment_img) {
                    int no_save = ((FamicomSaveDataHeader*)famicomCommon.save_data_header)->no_save;
                    ((FamicomSaveDataHeader*)famicomCommon.save_data_header)->no_save = FALSE;

                    famicom_save_data_setup((FamicomSaveDataHeader*)famicomCommon.save_data_header, famicomCommon.save_data_single_size, famicomCommon.save_data_name);
                    memcard_data_load(chan, (char*)famicomCommon.famicom_save_name, (char*)famicomCommon.mura_save_name, nullptr, famicomCommon.save_data_total_size, famicomCommon.save_data_name);
                    
                    result = memcard_data_save(
                        chan,
                        (char*)famicomCommon.famicom_save_name,
                        (char*)famicomCommon.mura_save_name,
                        (FamicomSaveDataHeader*)famicomCommon.save_data_header,
                        famicomCommon.save_data_total_size,
                        famicomCommon.memcard_save_comment,
                        famicomCommon.memcard_game_header.flags1.banner_fmt,
                        famicomCommon.memcard_game_header.flags0.comment_type == MEMCARD_COMMENT_TYPE_NONE ? 0xFFFFFFFF : CARD_COMMENT_SIZE,
                        famicomCommon.memcard_game_header.icon_format,
                        famicomCommon.memcard_game_header.icon_flags,
                        famicomCommon.memcard_game_header.flags0.comment_type == MEMCARD_COMMENT_TYPE_NONE ? 0xFFFFFFFF : 0,
                        no_save
                    );
                }
                else {
                    result = CARD_RESULT_READY;
                }
            }
            else {
                result = CARD_RESULT_FATAL_ERROR;
            }
        }
    }

    if (result != CARD_RESULT_READY && result != CARD_RESULT_FATAL_ERROR && chan >= 0) {
        errorChan = chan;
    }

    return famicom_cardResultToMiyake(result);
}

extern int famicom_external_data_save_check() {
    return FALSE;
}

static s32 famicom_common_save_initial() {
    s32 result;
    s32 chan = famicom_getSaveChan(famicomCommon.nesrom_memcard, &result);

    if (chan >= 0) {
        // Loading Famicom save data.
        OSReport("ファミコンセーブデータを読み込みます\n");
        result = memcard_data_load(chan, (char*)famicomCommon.famicom_save_name, (char*)famicomCommon.mura_save_name, (FamicomSaveDataHeader*)famicomCommon.save_data_header, famicomCommon.save_data_total_size, famicomCommon.save_data_name);

        if (famicom_save_data_check((FamicomSaveDataHeader*)famicomCommon.save_data_header, -1, famicomCommon.save_data_name) != 0) {
            famicom_save_data_init((FamicomSaveDataHeader*)famicomCommon.save_data_header, famicomCommon.save_data_single_size, famicomCommon.save_data_name);
        }
    }

    return result;
}

extern int famicom_get_disksystem_titles(int* n_games, char* title_name_bufp, int namebuf_size) {
    famicom_mount_archive_wait();
    return memcard_game_list(n_games, title_name_bufp, namebuf_size) == CARD_RESULT_READY;
}
