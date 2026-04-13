/* fixNES integration for Animal Crossing PC port.
 *
 * Based on fixNES by FIX94 (https://github.com/FIX94/fixNES)
 * MIT License. Stripped of GLUT/OpenAL, adapted as a library with
 * init/frame/render/cleanup API for the game's famicom.cpp integration.
 *
 * Produces a 256x240 RGB565 framebuffer uploaded as a GL texture.
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

/* Now include GL via SDL2 (avoid pc_platform.h which pulls in game types.h) */
#include <SDL2/SDL.h>
#include <glad/gl.h>
#include "fm2play.h"
#include "audio.h"

/* From pc_gx.c — restore game's GL state after NES emulation */
extern void pc_gx_restore_after_nes(void);

/* Externed directly (not via headers) to avoid fixNES symbol clashes. */
extern int g_pc_window_w;
extern int g_pc_window_h;
extern int pc_settings_get_nes_aspect(void);

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
extern void AIInitDMA(uint32_t addr, uint32_t size);

/* ======================================================================
 * GL rendering state
 * ====================================================================== */
static GLuint fixnes_shader = 0;
static GLuint fixnes_vao = 0;
static GLuint fixnes_vbo = 0;
static GLuint fixnes_texture = 0;
static GLint fixnes_tex_uniform = -1;
static int fixnes_initialized = 0;

static GLuint fixnes_compile_shader(GLenum type, const char *src) {
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &src, NULL);
    glCompileShader(s);
    GLint ok;
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char buf[512];
        glGetShaderInfoLog(s, sizeof(buf), NULL, buf);
        printf("[fixNES] Shader error: %s\n", buf);
    }
    return s;
}

static void fixnes_init_gl(void) {
    const char *vs =
        "#version 330 core\n"
        "layout(location=0) in vec2 pos;\n"
        "layout(location=1) in vec2 uv;\n"
        "out vec2 v_uv;\n"
        "void main() { gl_Position = vec4(pos, 0, 1); v_uv = uv; }\n";
    const char *fs =
        "#version 330 core\n"
        "in vec2 v_uv;\n"
        "out vec4 fragColor;\n"
        "uniform sampler2D tex;\n"
        "void main() { fragColor = texture(tex, v_uv); }\n";

    GLuint v = fixnes_compile_shader(GL_VERTEX_SHADER, vs);
    GLuint f = fixnes_compile_shader(GL_FRAGMENT_SHADER, fs);
    fixnes_shader = glCreateProgram();
    glAttachShader(fixnes_shader, v);
    glAttachShader(fixnes_shader, f);
    glLinkProgram(fixnes_shader);
    glDeleteShader(v);
    glDeleteShader(f);

    float quad[] = {
        -1, -1,  0, 1,
         1, -1,  1, 1,
         1,  1,  1, 0,
        -1, -1,  0, 1,
         1,  1,  1, 0,
        -1,  1,  0, 0,
    };
    glGenVertexArrays(1, &fixnes_vao);
    glGenBuffers(1, &fixnes_vbo);
    glBindVertexArray(fixnes_vao);
    glBindBuffer(GL_ARRAY_BUFFER, fixnes_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 16, (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 16, (void*)8);
    glBindVertexArray(0);

    fixnes_tex_uniform = glGetUniformLocation(fixnes_shader, "tex");

    glGenTextures(1, &fixnes_texture);
    glBindTexture(GL_TEXTURE_2D, fixnes_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
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
        AIInitDMA((uint32_t)(uintptr_t)fixnes_audio_buf, fixnes_audio_pos * 4);
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

    /* Restore game's GL state — NES emulator used its own shader/VAO */
    pc_gx_restore_after_nes();
}

void pc_fixnes_render_frame(uint16_t *fb) {
    if (!fixnes_shader) fixnes_init_gl();

    /* Upload framebuffer — fixNES outputs RGB565 with COL_TEX_BSWAP
     * (R in low bits) — upload with GL_UNSIGNED_SHORT_5_6_5_REV.
     * Skip top 8 rows (often garbage), show 224 lines. */
    glBindTexture(GL_TEXTURE_2D, fixnes_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 224, 0,
                 GL_RGB, GL_UNSIGNED_SHORT_5_6_5_REV, fb + 256 * 8);

    /* 0 = stretch to window, 1 = centered 4:3 with pillar/letterbox. */
    int win_w = g_pc_window_w;
    int win_h = g_pc_window_h;
    int vp_w, vp_h, vp_x, vp_y;
    if (pc_settings_get_nes_aspect() == 0) {
        vp_w = win_w; vp_h = win_h; vp_x = 0; vp_y = 0;
    } else if (win_w * 3 > win_h * 4) {
        vp_h = win_h;
        vp_w = (win_h * 4) / 3;
        vp_x = (win_w - vp_w) / 2;
        vp_y = 0;
    } else {
        vp_w = win_w;
        vp_h = (win_w * 3) / 4;
        vp_x = 0;
        vp_y = (win_h - vp_h) / 2;
    }

    /* Clear full window first so the bars are black, not stale pixels. */
    glDisable(GL_SCISSOR_TEST);
    glViewport(0, 0, win_w, win_h);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glViewport(vp_x, vp_y, vp_w, vp_h);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glUseProgram(fixnes_shader);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fixnes_texture);
    glUniform1i(fixnes_tex_uniform, 0);
    glBindVertexArray(fixnes_vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    glViewport(0, 0, win_w, win_h);
}
