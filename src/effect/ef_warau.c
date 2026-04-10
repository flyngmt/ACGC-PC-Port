#include "ef_effect_control.h"

#include "m_common_data.h"

static void eWU_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eWU_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eWU_mv(eEC_Effect_c* effect, GAME* game);
static void eWU_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_warau = {
    // clang-format off
    &eWU_init,
    &eWU_ct,
    &eWU_mv,
    &eWU_dw,
    eEC_IMMEDIATE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eWU_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_WARAU, pos, NULL, game, NULL, item_name, prio, 0, 0);
}

static void eWU_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->scale.x = 0.0045f;
    effect->scale.y = 0.0045f;
    effect->scale.z = 0.0045f;
    effect->offset.x = 0.0f;
    effect->offset.y = 0.0f;
    effect->offset.z = 0.0f;
    effect->timer = 24;
}

static void eWU_mv(eEC_Effect_c* effect, GAME* game) {
    sAdo_OngenPos((uintptr_t)effect, 15, &effect->position);
    eEC_CLIP->set_continious_env_proc(effect, 24, 24);
}

extern Gfx ef_warau01_00_modelT[];
extern Gfx ef_warau01_01_modelT[];
extern Gfx ef_warau01_02_modelT[];
extern Gfx ef_warau01_03_modelT[];

static Gfx* eWU_DispTable[12] = {
    // clang-format off
    NULL,
    NULL,
    ef_warau01_00_modelT,
    ef_warau01_00_modelT,
    ef_warau01_01_modelT,
    ef_warau01_01_modelT,
    ef_warau01_02_modelT,
    ef_warau01_02_modelT,
    ef_warau01_03_modelT,
    ef_warau01_03_modelT,
    NULL,
    NULL,
    // clang-format on
};

static void eWU_dw(eEC_Effect_c* effect, GAME* game) {
    s16 counter = (24 - effect->timer) >> 1;
    xyz_t* pos = &effect->position;
    xyz_t* ofs = &effect->offset;
    xyz_t* scale = &effect->scale;

    counter = CLAMP(counter, 0, 11);

    if (eWU_DispTable[counter] != NULL) {
        OPEN_DISP(game->graph);

        eEC_CLIP->auto_matrix_xlu_offset_proc(game, pos, scale, ofs);
        gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 128, 255, 255, 255, 255);
        gDPSetEnvColor(NEXT_POLY_XLU_DISP, 0, 0, 255, 255);
        gSPDisplayList(NEXT_POLY_XLU_DISP, eWU_DispTable[counter]);

        CLOSE_DISP(game->graph);
    }
}
