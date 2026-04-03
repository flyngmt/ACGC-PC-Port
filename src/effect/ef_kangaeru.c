#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "m_debug.h"

extern Gfx ef_think_l_modelT[];
extern Gfx ef_think_s_modelT[];

static void eKG_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eKG_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eKG_mv(eEC_Effect_c* effect, GAME* game);
static void eKG_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_kangaeru = {
    // clang-format off
    &eKG_init,
    &eKG_ct,
    &eKG_mv,
    &eKG_dw,
    7,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eKG_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    xyz_t vec = { 0.0f, 6.0f, 0.0f };
    pos.y += 15.0f;

    sMath_RotateY(&vec, SHORT2RAD_ANGLE2(angle));
    pos.x += vec.x;
    pos.y += vec.y;
    pos.z += vec.z;
    eEC_CLIP->make_effect_proc(eEC_EFFECT_KANGAERU, pos, NULL, game, NULL, item_name, prio, 0, 0);
}

static void eKG_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->scale.x = 0.01f;
    effect->scale.y = 0.01f;
    effect->scale.z = 0.01f;

    effect->timer = 36;

    effect->effect_specific[1] = 0;
    effect->effect_specific[2] = 0;
    effect->effect_specific[0] = 0;
}

static void eKG_mv(eEC_Effect_c* effect, GAME* game) {
    s16 orig_es1 = effect->effect_specific[1];
    eEC_CLIP->set_continious_env_proc(effect, 36, 20);

    if (effect->effect_specific[0] < FRAMERATE_TIMER(10)) {
        effect->effect_specific[1] += FRAMERATE_TIMER(DEG2SHORT_ANGLE(2.5f));
        effect->effect_specific[2] -= FRAMERATE_TIMER(DEG2SHORT_ANGLE(3.75f));
    }

    if ((effect->effect_specific[1] >= 0) && (orig_es1 < 0)) {
        effect->effect_specific[2] = 0;
        effect->effect_specific[1] = 0;
    }

    effect->effect_specific[0]++;

    if (effect->effect_specific[0] >= FRAMERATE_SELECT(25, 21)) {
        effect->effect_specific[0] = 0;
    }

    if (effect->state == eEC_STATE_FINISHED) {
        effect->effect_specific[4] = (u8)eEC_CLIP->calc_adjust_proc(7 - effect->timer, 0, 6, 255.0f, 0.0f);
    } else {
        sAdo_OngenPos((uintptr_t)effect, 0x58, &effect->position);
        effect->effect_specific[4] = 255;
    }
}

static void eKG_dw(eEC_Effect_c* effect, GAME* game) {
    s16 timer;
    GAME_PLAY* play = (GAME_PLAY*)game;

    switch (effect->state) {
        case eEC_STATE_NORMAL: {
            timer = 36 - effect->timer;
            effect->scale.z = 1.0f;
            effect->scale.x = effect->scale.y = eEC_CLIP->calc_adjust_proc(timer, 0, 7, 0.0f, 0.008f);
            break;
        }

        default: {
            effect->scale.x = 0.008f;
            effect->scale.y = 0.008f;
            effect->scale.z = 0.8f;
            break;
        }
    }

    OPEN_DISP(game->graph);

    _texture_z_light_fog_prim_xlu(game->graph);

    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
    Matrix_mult(&play->billboard_matrix, MTX_MULT);
    Matrix_translate(effect->offset.x + GETREG(MYKREG, 0x18), effect->offset.y - 6.0f + GETREG(MYKREG, 0x19),
                     effect->offset.z + 30.0f + GETREG(MYKREG, 0x1a), MTX_MULT);
    Matrix_scale(effect->scale.x, effect->scale.y, effect->scale.z, MTX_MULT);
    Matrix_translate(-475.0f, 950.0f, 0.0f, MTX_MULT);
    Matrix_RotateZ(effect->effect_specific[1], MTX_MULT);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 255, 255, 255, effect->effect_specific[4]);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_think_l_modelT);

    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
    Matrix_mult(&play->billboard_matrix, MTX_MULT);
    Matrix_translate(effect->offset.x + GETREG(MYKREG, 0x18), effect->offset.y - 6.0f + GETREG(MYKREG, 0x19),
                     effect->offset.z + 30.0f + GETREG(MYKREG, 0x1a), MTX_MULT);
    Matrix_scale(effect->scale.x, effect->scale.y, effect->scale.z, MTX_MULT);
    Matrix_translate(475.0f, 0.0f, 0.0f, MTX_MULT);
    Matrix_RotateZ(effect->effect_specific[2], MTX_MULT);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 255, 255, 255, (u8)effect->effect_specific[4]);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_think_s_modelT);

    CLOSE_DISP(game->graph);
}
