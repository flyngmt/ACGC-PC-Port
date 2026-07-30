/* fixNES integration for Animal Crossing PC port.
 *
 * Based on fixNES by FIX94 (https://github.com/FIX94/fixNES)
 * MIT License. Stripped of GLUT/OpenAL, adapted as a library with
 * init/frame/render/cleanup API for the game's famicom.cpp integration.
 *
 * Produces a 256x240 RGB565 framebuffer for the host presenter.
 * Audio samples are pushed to the game's audio system via AIInitDMA. */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

/* Include fixNES headers BEFORE any game headers to avoid BUTTON_A etc conflicts */
#include "mapper.h"
#include "cpu.h"
#include "ppu.h"
#include "apu.h"
#include "mem.h"
#include "input.h"

/* Undef fixNES button defines before game headers clobber them */
#undef BUTTON_A
#undef BUTTON_B
#undef BUTTON_SELECT
#undef BUTTON_START
#undef BUTTON_UP
#undef BUTTON_DOWN
#undef BUTTON_LEFT
#undef BUTTON_RIGHT

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

#include "fm2play.h"
#include "audio.h"
#include "pc_platform.h"
#include "pc_settings.h"

/* ======================================================================
 * Global variables required by fixNES modules (normally in main.c)
 * ====================================================================== */

/* Framebuffer — fixNES PPU writes pixels here */
uint16_t textureImage[VISIBLE_DOTS * VISIBLE_LINES];

/* Global state flags */
bool nesPAL = false;
bool nesPause = false;
bool ppuDebugPauseFrame = false;
bool doOverscan = false;
bool nesEmuNSFPlayback = false;
uint8_t emuInitialNT = NT_UNKNOWN;
bool emuSaveEnabled = false;
bool emuFdsHasSideB = false;
bool emuSkipFrame = false;

/* Cycle timers */
uint32_t cpuCycleTimer;
uint32_t vrc7CycleTimer;

/* ROM data pointers (fixNES modules reference these) */
uint8_t *emuNesROM = NULL;
uint32_t emuNesROMsize = 0;
uint8_t *emuPrgRAM = NULL;
uint32_t emuPrgRAMsize = 0;

/* Mapper special-case flags (defined in mapper .c files, referenced here) */
extern bool m30_flashable;
extern bool m30_singlescreen;
extern bool m32_singlescreen;
extern bool m78_m78a;
extern bool ppuMapper5;

/* Input state — written by set_input, read by fixNES input.c */
extern uint8_t inValReads[8];

/* Audio output to game engine */
extern void AIInitDMA(uintptr_t addr, uint32_t size);

static int fixnes_initialized = 0;

/* fixNES writes a linear BGR565 framebuffer (COL_TEX_BSWAP). Aurora's PC
 * texture format accepts linear RGBA8 directly, so expand once here rather
 * than tiling RGB565 only for Aurora to decode it again. */
#define FIXNES_PRESENT_WIDTH 256
#define FIXNES_PRESENT_HEIGHT 224
#define FIXNES_SOURCE_TOP 8
#define FIXNES_GX_TEXTURE_SIZE (FIXNES_PRESENT_WIDTH * FIXNES_PRESENT_HEIGHT * 4)

static uint8_t fixnes_gx_texture[FIXNES_GX_TEXTURE_SIZE] ATTRIBUTE_ALIGN(32);
static GXTexObj fixnes_tex_obj;
static int fixnes_tex_obj_initialized = 0;

static void fixnes_convert_frame(const uint16_t *fb) {
    uint8_t *dst = fixnes_gx_texture;

    for (int y = 0; y < FIXNES_PRESENT_HEIGHT; y++) {
        const uint16_t *src = fb + (y + FIXNES_SOURCE_TOP) * VISIBLE_DOTS;
        for (int x = 0; x < FIXNES_PRESENT_WIDTH; x++) {
            const uint16_t bgr565 = src[x];
            *dst++ = (uint8_t)(((bgr565 & 0x001F) * 255) / 31);
            *dst++ = (uint8_t)((((bgr565 >> 5) & 0x003F) * 255) / 63);
            *dst++ = (uint8_t)((((bgr565 >> 11) & 0x001F) * 255) / 31);
            *dst++ = 255;
        }
    }
}

static void fixnes_set_projection(int pillarbox) {
    Mtx44 projection;
    AuroraMtx identity;

    C_MTXOrtho(projection, 1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 10.0f);
    C_MTXIdentity(identity);
    g_pc_widescreen_stretch = pillarbox ? 2 : 1;
    pc_widescreen_set_projection(projection, GX_ORTHOGRAPHIC);
    GXLoadPosMtxImm(identity, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
}

static void fixnes_draw_black_background(void) {
    fixnes_set_projection(0);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX,
                  GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3s8(-1, 1, -5);
    GXColor4u8(0, 0, 0, 255);
    GXPosition3s8(1, 1, -5);
    GXColor4u8(0, 0, 0, 255);
    GXPosition3s8(1, -1, -5);
    GXColor4u8(0, 0, 0, 255);
    GXPosition3s8(-1, -1, -5);
    GXColor4u8(0, 0, 0, 255);
    GXEnd();
}

static void fixnes_draw_texture(void) {
    fixnes_set_projection(g_pc_settings.nes_aspect != 0);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0,
                      GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_FALSE, 0, 0);
    GXSetTexCoordBias(GX_TEXCOORD0, GX_FALSE, GX_FALSE);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXLoadTexObj(&fixnes_tex_obj, GX_TEXMAP0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S8, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3s8(-1, 1, -5);
    GXTexCoord2s8(0, 0);
    GXPosition3s8(1, 1, -5);
    GXTexCoord2s8(1, 0);
    GXPosition3s8(1, -1, -5);
    GXTexCoord2s8(1, 1);
    GXPosition3s8(-1, -1, -5);
    GXTexCoord2s8(0, 1);
    GXEnd();
}

/* ======================================================================
 * Audio buffer capture — convert fixNES APU output to stereo s16 for
 * the game's audio system
 * ====================================================================== */
#define FIXNES_AUDIO_BUF_SIZE 2048
static int16_t fixnes_audio_buf[FIXNES_AUDIO_BUF_SIZE * 2]; /* stereo */
static int fixnes_audio_pos = 0;

static void fixnes_capture_audio(void) {
    uint32_t buf_size = apuGetBufSize();
    if (buf_size == 0) return;

    uint8_t *raw = apuGetBuf();
    if (!raw) return;

    /* fixNES APU outputs stereo int16_t samples (L,R interleaved).
     * curBufPos advances by 2 per sample, so buf_size = curBufPos * 2 bytes.
     * Total stereo frames = buf_size / (2 * sizeof(int16_t)). */
    int16_t *src = (int16_t *)raw;
    int num_frames = buf_size / (2 * sizeof(int16_t)); /* stereo frames */

    /* Downsample from fixNES APU frequency to game's 32kHz audio output */
    #define FIXNES_OUTPUT_RATE 32000
    int target_frames = FIXNES_OUTPUT_RATE / 60;
    if (target_frames > FIXNES_AUDIO_BUF_SIZE)
        target_frames = FIXNES_AUDIO_BUF_SIZE;

    fixnes_audio_pos = 0;
    if (num_frames > 0) {
        for (int i = 0; i < target_frames; i++) {
            int src_frame = (int)((int64_t)i * num_frames / target_frames);
            if (src_frame >= num_frames) src_frame = num_frames - 1;
            fixnes_audio_buf[fixnes_audio_pos * 2 + 0] = src[src_frame * 2 + 0]; /* L */
            fixnes_audio_buf[fixnes_audio_pos * 2 + 1] = src[src_frame * 2 + 1]; /* R */
            fixnes_audio_pos++;
        }
    }

    if (fixnes_audio_pos > 0) {
        AIInitDMA((uintptr_t)fixnes_audio_buf, fixnes_audio_pos * 4);
    }
}

/* ======================================================================
 * Public API
 * ====================================================================== */

void pc_fixnes_init(uint8_t *ines_data, int ines_size) {
    /* Reset all state */
    nesPAL = false;
    nesPause = false;
    nesEmuNSFPlayback = false;
    emuSaveEnabled = false;
    emuFdsHasSideB = false;
    emuSkipFrame = false;
    m30_flashable = false;
    m30_singlescreen = false;
    m32_singlescreen = false;
    m78_m78a = false;
    ppuMapper5 = false;
    emuInitialNT = NT_UNKNOWN;
    fixnes_initialized = 0;

    /* Free any previous allocation */
    if (emuPrgRAM) {
        free(emuPrgRAM);
        emuPrgRAM = NULL;
    }

    /* Store ROM pointer */
    emuNesROM = ines_data;
    emuNesROMsize = (uint32_t)ines_size;

    /* Parse iNES header */
    if (ines_size < 16)
        return;

    uint8_t mapper = ((emuNesROM[6] & 0xF0) >> 4) | ((emuNesROM[7] & 0xF0));
    emuSaveEnabled = (emuNesROM[6] & (1<<1)) != 0;
    bool trainer = (emuNesROM[6] & (1<<2)) != 0;
    uint32_t ROMsize = emuNesROMsize - 16;
    uint32_t prgROMsize = emuNesROM[4] * 0x4000;
    if (prgROMsize > ROMsize)
        prgROMsize = ROMsize;
    ROMsize -= prgROMsize;
    uint32_t chrROMsize = emuNesROM[5] * 0x2000;
    if (prgROMsize == 0) {
        prgROMsize = ROMsize;
        if (chrROMsize)
            chrROMsize = 0;
    } else if (chrROMsize > ROMsize) {
        chrROMsize = ROMsize;
    }

    /* Allocate PRG RAM */
    if (mapper == 5)
        emuPrgRAMsize = 0x10000;
    else {
        emuPrgRAMsize = emuNesROM[8] * 0x2000;
        if (emuPrgRAMsize == 0) emuPrgRAMsize = 0x2000;
    }
    emuPrgRAM = malloc(emuPrgRAMsize);
    memset(emuPrgRAM, 0, emuPrgRAMsize);

    uint8_t *prgROM = emuNesROM + 16;
    if (trainer) prgROM += 512;

    uint8_t *chrROM = NULL;
    if (chrROMsize) {
        chrROM = emuNesROM + 16 + prgROMsize;
        if (trainer) chrROM += 512;
    }

    /* Initialize fixNES subsystems */
    apuInitBufs();
    cpuInit();
    ppuInit();
    memInit();
    apuInit();
    inputInit();

    /* Set nametable mirroring */
    if (emuNesROM[6] & 8) {
        emuInitialNT = NT_4SCREEN;
        ppuSetNameTbl4Screen();
    } else if (emuNesROM[6] & 1) {
        emuInitialNT = NT_VERTICAL;
        ppuSetNameTblVertical();
    } else {
        emuInitialNT = NT_HORIZONTAL;
        ppuSetNameTblHorizontal();
    }

    if (mapper == 5)
        ppuMapper5 = true;

    /* Initialize mapper */
    if (!mapperInit(mapper, prgROM, prgROMsize, emuPrgRAM, emuPrgRAMsize, chrROM, chrROMsize))
        return;

    cpuCycleTimer = nesPAL ? 16 : 12;
    vrc7CycleTimer = 432 / cpuCycleTimer;
    fixnes_initialized = 1;

    memset(textureImage, 0, sizeof(textureImage));
    memset(fixnes_gx_texture, 0, sizeof(fixnes_gx_texture));
    fixnes_audio_pos = 0;
}

void pc_fixnes_write_wram(unsigned int ofs, const uint8_t *data, unsigned int size) {
    /* Targeted write to fixNES internal RAM — used by update_highscore_raw
     * to inject saved high scores into the running NES game. */
    uint8_t *mem = memGetMainMem();
    if (mem && data && ofs + size <= 0x800)
        memcpy(mem + ofs, data, size);
}

void pc_fixnes_sync_wram(uint8_t *dst_wram) {
    /* Copy fixNES internal 2KB RAM → ksNes sp->wram so
     * nesinfo_update_highscore can detect high-score changes. */
    uint8_t *src = memGetMainMem();
    if (src && dst_wram)
        memcpy(dst_wram, src, 0x800);
}

void pc_fixnes_reset(void) {
    // Console soft reset (L+R+Start)
    if (fixnes_initialized)
        ppuSoftReset();
}

void pc_fixnes_set_input(uint8_t buttons) {
    /* buttons: bit0=A, bit1=B, bit2=Select, bit3=Start,
     *          bit4=Up, bit5=Down, bit6=Left, bit7=Right
     * fixNES inValReads[]: index 0=A, 1=B, 2=Select, ... 7=Right */
    for (int i = 0; i < 8; i++)
        inValReads[i] = (buttons >> i) & 1;
}

uint16_t *pc_fixnes_frame(void) {
    if (!fixnes_initialized) return textureImage;

    /* Run one full NES frame: cycle CPU/PPU/APU until ppuDrawDone() */
    while (1) {
        if (!cpuCycle())
            break; /* CPU halted */
        ppuCycle();
        apuCycle();
        mapperCycle();
        if (ppuDrawDone()) {
            /* Frame complete — capture audio BEFORE apuUpdate resets curBufPos */
            fixnes_capture_audio();
            apuUpdate();
            break;
        }
    }

    return textureImage;
}

void pc_fixnes_cleanup(void) {
    /* Free APU output buffers */
    apuDeinitBufs();

    /* Free PRG RAM */
    if (emuPrgRAM) {
        free(emuPrgRAM);
        emuPrgRAM = NULL;
    }

    /* Don't free emuNesROM — it's owned by the famicom system, not us. famicom_cleanup frees this, this is NOT a memory leak. */
    emuNesROM = NULL;
    emuNesROMsize = 0;

    fixnes_initialized = 0;

    if (fixnes_tex_obj_initialized) {
        GXDestroyTexObj(&fixnes_tex_obj);
        fixnes_tex_obj_initialized = 0;
    }

}

int pc_fixnes_is_initialized(void) {
    return fixnes_initialized;
}

void pc_fixnes_render_frame(uint16_t *fb) {
    if (!fixnes_initialized) return;
    if (!fb) fb = textureImage;

    fixnes_convert_frame(fb);
    if (!fixnes_tex_obj_initialized) {
        GXInitTexObj(&fixnes_tex_obj, fixnes_gx_texture,
                     FIXNES_PRESENT_WIDTH, FIXNES_PRESENT_HEIGHT,
                     GX_TF_RGBA8_PC, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXInitTexObjLOD(&fixnes_tex_obj, GX_NEAR, GX_NEAR,
                        0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
        fixnes_tex_obj_initialized = 1;
    } else {
        GXInitTexObjData(&fixnes_tex_obj, fixnes_gx_texture);
    }

    GXSetScissor(0, 0, PC_GC_WIDTH, PC_GC_HEIGHT);
    pc_widescreen_set_viewport(0.0f, 0.0f, (float)PC_GC_WIDTH, (float)PC_GC_HEIGHT, 0.0f, 1.0f);
    GXSetClipMode(GX_CLIP_ENABLE);
    GXSetColorUpdate(GX_TRUE);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZCompLoc(GX_TRUE);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_COPY);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);

    fixnes_draw_black_background();
    fixnes_draw_texture();
}
