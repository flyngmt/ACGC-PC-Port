#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_debug.h"
#include "m_rcp.h"
#include "sys_matrix.h"

extern Gfx ef_doyon01_00_modelT[];
extern Gfx ef_otikomi_us2_model[];

static void eOMN_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eOMN_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eOMN_mv(eEC_Effect_c* effect, GAME* game);
static void eOMN_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_otikomi = {
    // clang-format off
    &eOMN_init,
    &eOMN_ct,
    &eOMN_mv,
    &eOMN_dw,
    10,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eOMN_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    static xyz_t offset = { 0.0f, 0.0f, 19.0f };

    eEC_CLIP->make_effect_proc(eEC_EFFECT_OTIKOMI, pos, &offset, game, NULL, item_name, prio, 0, 0);
}

static void eOMN_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 22;

    effect->effect_specific[0] = 0;
    effect->effect_specific[1] = 0;

    effect->acceleration.x = 10000.0f;

    effect->velocity.x = 0.4f;
    effect->velocity.y = 0.0f;
    effect->velocity.z = 0.0f;

    effect->position.y += 17.0f;
}

static void eOMN_mv(eEC_Effect_c* effect, GAME* game) {
    float vel;

    effect->effect_specific[0] += DEG2SHORT_ANGLE2(2.29f);
    effect->effect_specific[1] += (int)effect->acceleration.x;

    vel = effect->velocity.x * sin_s(effect->effect_specific[1]);
    effect->velocity.y = 1.0f - vel;
    effect->velocity.z = 1.0f + vel;

    add_calc(&effect->velocity.x, 0.025f, 0.022f, 0.1f, 0.001f);
    add_calc(&effect->acceleration.x, 2000.0f, 0.022f, 6000.0f, 0.01f);

    eEC_CLIP->set_continious_env_proc(effect, 22, 100);
}

static void eOMN_dw(eEC_Effect_c* effect, GAME* game) {
    Gfx* gfx;
    s16 timer;
    u8 alpha, alpha2;
    f32 scale_m, scale_y;
    GAME_PLAY* play = (GAME_PLAY*)game;

    gfx = two_tex_scroll_dolphin(game->graph, 0, 0, 0, 16, 16, 1, 0, play->game_frame * 25, 64, 32);

    switch (effect->state) {
        case eEC_STATE_NORMAL:
            timer = 22 - effect->timer;
            scale_m = eEC_CLIP->calc_adjust_proc(timer, 0, 10, 0.0f, 0.01f);
            scale_y = eEC_CLIP->calc_adjust_proc(timer, 10, 21, 0.0f, 0.0135f);
            alpha = 255;
            alpha2 = 100;
            sAdo_OngenPos((uintptr_t)effect, 0x59, &effect->position);
            break;

        case eEC_STATE_CONTINUOUS:
            sAdo_OngenPos((uintptr_t)effect, 0x59, &effect->position);
            scale_m = 0.01f;
            alpha = 255;
            scale_y = 0.0135f;
            alpha2 = 100;
            break;

        default:
            timer = 10 - effect->timer;
            scale_m = 0.01f;
            scale_y = 0.0135f;
            alpha = (int)eEC_CLIP->calc_adjust_proc(timer, 0, 9, 255.0f, 0.0f);
            alpha2 = (int)eEC_CLIP->calc_adjust_proc(timer, 0, 9, 100.0f, 0.0f);
            break;
    }

    _texture_z_light_fog_prim_xlu(game->graph);

    OPEN_DISP(game->graph);

    Matrix_translate(effect->position.x, effect->position.y + 4.0f, effect->position.z, MTX_LOAD);
    Matrix_mult(&play->billboard_matrix, MTX_MULT);
    Matrix_translate(effect->offset.x + GETREG(MYKREG, 0x18), effect->offset.y + GETREG(MYKREG, 0x19),
                     effect->offset.z + 2.0f + GETREG(MYKREG, 0x1a), MTX_MULT);
    if (GETREG(MYKREG, 0)) {
        Matrix_RotateZ(-effect->effect_specific[0], MTX_MULT);
        Matrix_scale(scale_m * 1.025f, scale_m, scale_m, MTX_MULT);
        Matrix_RotateZ(effect->effect_specific[0], MTX_MULT);
    } else {
        Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);
    }
    Matrix_scale(effect->velocity.z * 1.3f, effect->velocity.y, 1.0f, MTX_MULT);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 40, 30, 40, alpha);
    gDPSetEnvColor(NEXT_POLY_XLU_DISP, 100, 100, 255, 255);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_doyon01_00_modelT);

    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
    Matrix_mult(&play->billboard_matrix, MTX_MULT);
    Matrix_translate(effect->offset.x + GETREG(MYKREG, 0x18), effect->offset.y + GETREG(MYKREG, 0x19),
                     effect->offset.z + GETREG(MYKREG, 0x1a), MTX_MULT);
    Matrix_scale(0.015f, scale_y, 0.01f, MTX_MULT);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 0, 255, 255, alpha2);
    gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_9, gfx);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_otikomi_us2_model);

    CLOSE_DISP(game->graph);
}
