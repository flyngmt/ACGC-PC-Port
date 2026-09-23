#include "m_choice.h"

#ifdef TARGET_PC
#include "pc_mouse_input.h"
#endif

#include "audio.h"
#include "jsyswrap.h"
#include "libultra/libultra.h"
#include "m_common_data.h"
#include "m_font.h"
#include "m_msg.h"
#include "sys_matrix.h"

typedef void (*mChoice_MAIN_PROC)(mChoice_c*, GAME*);

static void mChoice_MainSetup(mChoice_c* choice, GAME* game);

static u32 Choice_table_rom_start = 0;
static u32 Choice_rom_start = 0;

static void mChoice_MainSetup_Hide(mChoice_c*, GAME*);
static void mChoice_MainSetup_Appear(mChoice_c*, GAME*);
static void mChoice_MainSetup_Normal(mChoice_c*, GAME*);
static void mChoice_MainSetup_Disappear(mChoice_c*, GAME*);

static void mChoice_init(mChoice_c* choice, GAME* game);
static void mChoice_check_ct(mChoice_c* choice);
static void mChoice_SetMatrix(mChoice_c* choice, GAME* game, int type);
static void mChoice_SetMatrixDisplay(mChoice_c* choice, GAME* game, int type);
static void mChoice_UnSetMatrix();
static void mChoice_UnSetMatrixDisplay(GAME* game, int type);
static void mChoice_DrawWindowBody(mChoice_c* choice, GAME* game, int type);
static void mChoice_DrawFont(mChoice_c* choice, GAME* game, int type);

static void mChoice_Main_Hide(mChoice_c*, GAME*);
static void mChoice_Main_Appear(mChoice_c*, GAME*);
static void mChoice_Main_Normal(mChoice_c*, GAME*);
static void mChoice_Main_Disappear(mChoice_c*, GAME*);

static void mChoice_MainSetup(mChoice_c* choice, GAME* game) {
    static mChoice_MAIN_PROC proc[mChoice_MAIN_INDEX_NUM] = {
        &mChoice_MainSetup_Hide,
        &mChoice_MainSetup_Appear,
        &mChoice_MainSetup_Normal,
        &mChoice_MainSetup_Disappear,
    };

    int index = choice->requested_main_index;

    /* This is necessary lol */
    if (index < 0) {
        return;
    } else if (index < 0 || index >= mChoice_MAIN_INDEX_NUM || proc[index] == NULL) {
        return;
    }

    (*proc[index])(choice, game);
}

extern void mChoice_Main(mChoice_c* choice, GAME* game) {
    static mChoice_MAIN_PROC proc[mChoice_MAIN_INDEX_NUM] = {
        &mChoice_Main_Hide,
        &mChoice_Main_Appear,
        &mChoice_Main_Normal,
        &mChoice_Main_Disappear,
    };

    int index = choice->main_index;

    if (index < 0 || index >= mChoice_MAIN_INDEX_NUM || proc[index] == NULL) {
        return;
    }

    (*proc[index])(choice, game);
}

extern void mChoice_Draw(mChoice_c* choice, GAME* game, int mode) {
    if (choice->window_visible_flag) {
        mFont_SetMatrix(game->graph, mode);
        mChoice_SetMatrix(choice, game, mode);
        mChoice_SetMatrixDisplay(choice, game, mode);
        mChoice_DrawWindowBody(choice, game, mode);
        mChoice_UnSetMatrixDisplay(game, mode);
        mChoice_DrawFont(choice, game, mode);
        mChoice_UnSetMatrix();
        mFont_UnSetMatrix(game->graph, mode);
    }
}

extern void mChoice_aram_init() {
    Choice_table_rom_start = JW_GetAramAddress(RESOURCE_SELECT_TABLE);
    Choice_rom_start = JW_GetAramAddress(RESOURCE_SELECT);
}

extern void mChoice_ct(mChoice_c* choice, GAME* game) {
    mChoice_check_ct(choice);
    mChoice_init(choice, game);
}

extern void mChoice_dt(mChoice_c* choice, GAME* game) {
}

#include "../src/game/m_choice_main.c_inc"
#include "../src/game/m_choice_sound.c_inc"
#include "../src/game/m_choice_main_hide.c_inc"
#include "../src/game/m_choice_main_appear.c_inc"
#include "../src/game/m_choice_main_normal.c_inc"
#include "../src/game/m_choice_main_disappear.c_inc"
#include "../src/game/m_choice_draw.c_inc"
