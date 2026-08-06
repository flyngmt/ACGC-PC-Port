#include "m_msg.h"

#include "main.h"
#include "m_font.h"
#include "m_string.h"
#include "m_handbill.h"
#include "m_common_data.h"
#include "jsyswrap.h"
#include "m_bgm.h"
#include "libforest/emu64/emu64_wrapper.h"
#include "sys_matrix.h"
#ifdef TARGET_PC
#include "pc_bswap.h"
#endif

#ifdef PC_LLM_DIALOGUE
#include "llm/llm_api.h"
#endif

static u32 Msg_table_rom_start = 0;
static u32 Msg_rom_start = 0;

static mMsg_Data_c mMsg_data;
static mMsg_Window_c mMsg_window;

typedef int (*mMsg_CONTROL_CODE_PROC)(mMsg_Window_c*, int*);
typedef void (*mMsg_MAIN_PROC)(mMsg_Window_c*, GAME*);

static void mMsg_MainSetup_Window(mMsg_Window_c* msg_p, GAME* game);
static int mMsg_end_to_disappear(mMsg_Window_c* msg_p);

#include "../src/game/m_msg_ctrl.c_inc"

static void mMsg_sound_MessageSpeedForce(f32 timer);
static void mMsg_sound_MessageStatus(u8 status);

#include "../src/game/m_msg_main.c_inc"
#include "../src/game/m_msg_sound.c_inc"
#include "../src/game/m_msg_hide.c_inc"
#include "../src/game/m_msg_appear.c_inc"
#include "../src/game/m_msg_normal.c_inc"
#include "../src/game/m_msg_cursol.c_inc"
#include "../src/game/m_msg_disappear.c_inc"
#include "../src/game/m_msg_appear_wait.c_inc"
#include "../src/game/m_msg_wait.c_inc"
#include "../src/game/m_msg_disappear_wait.c_inc"

#include "../src/game/m_msg_data.c_inc"
#include "../src/game/m_msg_draw_window.c_inc"
#include "../src/game/m_msg_draw_font.c_inc"

static void mMsg_MainSetup_Window(mMsg_Window_c* msg_p, GAME* game) {
    static mMsg_MAIN_PROC proc[mMsg_INDEX_NUM] = {
        &mMsg_MainSetup_Hide,      &mMsg_MainSetup_Appear,      &mMsg_MainSetup_Normal, &mMsg_MainSetup_Cursol,
        &mMsg_MainSetup_Disappear, &mMsg_MainSetup_Appear_wait, &mMsg_MainSetup_Wait,   &mMsg_MainSetup_Disappear_wait,
    };

    int idx = msg_p->requested_main_index;

    if (idx >= 0) {
        if (idx >= mMsg_INDEX_NUM || proc[idx] == NULL) {
            return;
        }

        (*proc[idx])(msg_p, game);
    }
}

static void mMsg_Main_Window(mMsg_Window_c* msg_p, GAME* game) {
    static mMsg_MAIN_PROC proc[mMsg_INDEX_NUM] = {
        &mMsg_Main_Hide,      &mMsg_Main_Appear,      &mMsg_Main_Normal, &mMsg_Main_Cursol,
        &mMsg_Main_Disappear, &mMsg_Main_Appear_wait, &mMsg_Main_Wait,   &mMsg_Main_Disappear_wait,
    };

    int idx = msg_p->main_index;

    if (idx >= 0) {
        if (idx >= mMsg_INDEX_NUM || proc[idx] == NULL) {
            return;
        }

        (*proc[idx])(msg_p, game);
    }
}

static void mMsg_Draw_Window(mMsg_Window_c* msg_p, GAME* game) {
    if (msg_p->draw_flag && msg_p->data_loaded) {
        mFont_SetMatrix(game->graph, mFont_MODE_FONT);
        mMsg_SetMatrix(msg_p, game, mFont_MODE_FONT);
        mMsg_DrawWindowBody(msg_p, game, mFont_MODE_FONT);
        mMsg_UnSetMatrix();
        mFont_UnSetMatrix(game->graph, mFont_MODE_FONT);

        if (msg_p->msg_data->data_loaded) {
            mMsg_draw_font(msg_p, game);
        }

        mChoice_Draw(&msg_p->choice_window, game, mFont_MODE_FONT);
    }
}

extern void mMsg_aram_init() {
    mChoice_aram_init();
    mString_aram_init();
    mHandbill_aram_init();
}

extern void mMsg_aram_init2() {
    Msg_table_rom_start = JW_GetAramAddress(RESOURCE_MESSAGE_TABLE);
    Msg_rom_start = JW_GetAramAddress(RESOURCE_MESSAGE);
}

extern void mMsg_ct(GAME* game) {
    mMsg_init(game);
    mChoice_ct(&mMsg_window.choice_window, game);
}

extern void mMsg_dt(GAME* game) {
    mChoice_dt(&mMsg_window.choice_window, game);
}

extern void mMsg_debug_draw(gfxprint_t* gfxprint) {
    if (mMsg_window.msg_data != NULL) {
        gfxprint_color(gfxprint, 245, 255, 250, 255);
        gfxprint_locate8x8(gfxprint, 3, 6);
        gfxprint_printf(gfxprint, "%5d", mMsg_window.msg_data->msg_no);
    }
}

extern void mMsg_Main(GAME* game) {
    mMsg_Main_Window(&mMsg_window, game);
    mChoice_Main(&mMsg_window.choice_window, game);
}

extern void mMsg_Draw(GAME* game) {
    mMsg_Draw_Window(&mMsg_window, game);
}
