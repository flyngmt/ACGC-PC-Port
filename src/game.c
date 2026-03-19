#include "game.h"

#ifdef TARGET_PC
#include "pc_platform.h"
#include "pc_diag.h"
extern int g_pc_model_viewer;
#endif

#include "m_debug.h"
#include "zurumode.h"
#include "libforest/gbi_extensions.h"
#include "famicom_emu.h"
#include "m_play.h"
#include "gfxalloc.h"
#include "gamealloc.h"
#include "THA_GA.h"
#include "jsyswrap.h"
#include "m_debug_mode.h"
#include "padmgr.h"
#include "m_bgm.h"
#include "libu64/debug.h"
#include "libc64/malloc.h"
#include "GBA/gba.h"
#include "m_vibctl.h"

GAME* gamePT = NULL;

static u16 last_button[MAXCONTROLLERS];
static u16 last_now_button[MAXCONTROLLERS];
static u16 last_on_trigger[MAXCONTROLLERS];

u8 game_GameFrame;
f32 game_GameFrameF;
f32 game_GameFrame_2F;
f32 game_GameFrame__1F;

GAME* game_class_p;

static void game_move_first(GAME* this) {
    if (zurumode_flag) {
        Debug_mode_input(&this->pads[1]);
    }

    JC_JUTProcBar_setVisible(JC_JUTProcBar_getManager(), GETREG(SREG, 0) != 0);
    JC_JUTProcBar_setVisibleHeapBar(JC_JUTProcBar_getManager(), GETREG(SREG, 0) != 0);
}

extern void game_debug_draw_last(GAME* this, GRAPH* graph) {
    int i;
    Gfx* gfx;
    Gfx* close;

    if (zurumode_flag) {
        OPEN_DISP(graph);

        gfx = NOW_POLY_OPA_DISP;
        close = gfxopen(gfx);
        gSPDisplayList(NOW_OVERLAY_DISP++, close);

        for (i = 0; i < MAXCONTROLLERS; i++) {
            pad_t* pad = &this->pads[i];
            if (pad->now.errno == 0) {
                last_now_button[i] = pad->now.button;
                last_on_trigger[i] = pad->on.button;
                last_button[i] = last_now_button[i] | last_on_trigger[i];
            } else {
                last_now_button[i] = 0;
                last_on_trigger[i] = 0;
                last_button[i] = i == 0 ? 0xffff : 0;
            }

            SETREG(HREG, 40 + i, last_button[i]);
        }

        gSPEndDisplayList(close++);
        gfxclose(gfx, close);
        SET_POLY_OPA_DISP(close);

        CLOSE_DISP(graph);
    }

    if (zurumode_flag) {
        Debug_mode_output(graph);
    }
}

static void game_draw_first(GRAPH* graph) {
    OPEN_DISP(graph);

    gSPSegment(NOW_BG_OPA_DISP++, G_MWO_NUMLIGHT, 0x80000000);

    CLOSE_DISP(graph);
}

extern void game_draw_last(GRAPH* graph) {
    Gfx* close;
    Gfx* poly_gfx;

    OPEN_DISP(graph);

    poly_gfx = NOW_POLY_OPA_DISP;
    close = gfxopen(poly_gfx);

    gSPDisplayList(NOW_OVERLAY_DISP++, close);
    gSPEndDisplayList(close++);

    gfxclose(poly_gfx, close);
    SET_POLY_OPA_DISP(close);

    CLOSE_DISP(graph);
}

extern void game_get_controller(GAME* this) {
    if (this->pad_initialized == TRUE) {
        padmgr_RequestPadData(this->pads, 1);
    } else {
        padmgr_ClearPadData(this->pads);
    }
}

extern void SetGameFrame(int frame) {
    if (game_GameFrame != frame) {
        game_GameFrame = frame;
        game_GameFrameF = (int)(u8)frame;
        game_GameFrame_2F = game_GameFrameF * 0.5f;
        game_GameFrame__1F = 1.0f / game_GameFrameF;

        SETREG(SREG, 30, (u16)frame);

        if (GETREG(SREG, 29) > 0) {
            frame = GETREG(SREG, 29);
        }

        JC_JFWDisplay_setFrameRate(JC_JFWDisplay_getManager(), frame);
    }
}

extern void game_main(GAME* this) {
    GRAPH* graph = this->graph;

    if (GETREG(SREG, 30) != game_GameFrame || GETREG(SREG, 29)) {
        SetGameFrame(GETREG(SREG, 30));
    }

    game_draw_first(graph);
    PC_DIAG(5, "game_main: draw_first done, calling mTM_time\n");
    GRAPH_SET_DOING_POINT(graph, GAME_TIME);
    mTM_time();
    GRAPH_SET_DOING_POINT(graph, GAME_TIME_FINISHED);
    PC_DIAG(5, "game_main: mTM_time done, calling exec=%p\n", (void*)this->exec);
    GRAPH_SET_DOING_POINT(graph, GAME_EXEC);
#ifdef TARGET_PC
    {
        static jmp_buf game_exec_jmpbuf;
        pc_crash_set_jmpbuf(&game_exec_jmpbuf);
        if (setjmp(game_exec_jmpbuf) != 0) {
            /* Recovered from crash in game exec */
            printf("[PC] CRASH in game exec! doing_point=%d specific=0x%02X addr=%p data=%p\n",
                this->doing_point, this->doing_point_specific,
                (void*)pc_crash_get_addr(), (void*)pc_crash_get_data_addr());
        } else {
            this->exec(this);
        }
        pc_crash_set_jmpbuf(NULL);
    }
#else
    this->exec(this);
#endif
    GRAPH_SET_DOING_POINT(graph, GAME_EXEC_FINISHED);
    GRAPH_SET_DOING_POINT(graph, GAME_BGM);
#ifdef TARGET_PC
    if (!g_pc_model_viewer) {
#endif
        mBGM_main(this);
#ifdef TARGET_PC
    }
#endif
    GRAPH_SET_DOING_POINT(graph, GAME_BGM_FINISHED);
    game_move_first(this);
    this->frame_counter++;
}

static void game_init_hyral(GAME* this, size_t size) {
    u8* hyral = (u8*)gamealloc_malloc(&this->gamealloc, size);
    if (hyral != NULL) {
        THA_ct(&this->tha, (char*)hyral, size);
    } else {
        THA_ct(&this->tha, NULL, 0);
#if VERSION == VER_GAFU01_00
        _dbg_hungup(__FILE__, 565);
#elif VERSION == VER_GAFE01_00
        _dbg_hungup(__FILE__, 559);
#endif
    }
}

extern void game_resize_hyral(GAME* this, int size) {
    size_t max_size, free_size, alloc_size;
    u8* old_hyral;
    u8* hyral;

    old_hyral = (u8*)this->tha.buf_p;
    THA_dt(&this->tha);
    gamealloc_free(&this->gamealloc, old_hyral);
    GetFreeArena(&max_size, &free_size, &alloc_size);
    max_size -= 0x50;

    if (size <= 0) {
        size = max_size + size;
        if (size < 0) {
            size = 0;
        }
    } else {
        if (size > max_size) {
            size = max_size;
        }
    }

    hyral = (u8*)gamealloc_malloc(&this->gamealloc, (u32)size);
    if (hyral != NULL) {
        THA_ct(&this->tha, (char*)hyral, (u32)size);
    } else {
        THA_ct(&this->tha, NULL, 0);
#if VERSION == VER_GAFU01_00
        _dbg_hungup(__FILE__, 639);
#elif VERSION == VER_GAFE01_00
        _dbg_hungup(__FILE__, 633);
#endif
    }
}

extern void game_ct(GAME* this, void (*init)(GAME*), GRAPH* graph) {
    gamePT = this;
    graph->need_viupdate = TRUE;
    mCon_ct();
    this->graph = graph;
    this->frame_counter = 0;
    this->exec = NULL;
    this->cleanup = NULL;
    this->doing = TRUE;
    this->pad_initialized = TRUE;
    GAME_NEXT_GAME_NULL(this);
    gamealloc_init(&this->gamealloc);
    game_init_hyral(this, GAME_HYRAL_SIZE);
    SetGameFrame(GAME_FRAME);
    __gfxprint_default_flags |= GFXPRINT_FLAG_HIGHRES;
    init(this);
    mBGM_init();
#if VERSION < VER_GAFU01_00
    GBAInit();
#endif
    mVibctl_init();
}

extern void game_dt(GAME* this) {
    mCon_dt();
    mBGM_cleanup();
    if (this->cleanup != NULL) {
        this->cleanup(this);
    }

    mVibctl_cleanup();
    THA_dt(&this->tha);
    gamealloc_cleanup(&this->gamealloc);
    gamePT = NULL;
}

extern void (*game_get_next_game_init(GAME* this))(GAME*) {
    return this->next_game_init;
}

/* @fabricated */
MATCH_FORCESTRIP extern size_t game_get_next_game_class_size(GAME* this) {
    return this->next_game_class_size;
}

extern int game_is_doing(GAME* this) {
    return this->doing;
}

extern int game_getFreeBytes(GAME* this) {
    return THA_getFreeBytes16(&this->tha);
}

extern void game_goto_next_game_play(GAME* this) {
    GAME_GOTO_NEXT(this, play, PLAY);
}

/* @fabricated */
MATCH_FORCESTRIP extern void game_goto_next_game_famicom_emu(GAME* this) {
    GAME_GOTO_NEXT(this, famicom_emu, FAMICOM_EMU);
}
