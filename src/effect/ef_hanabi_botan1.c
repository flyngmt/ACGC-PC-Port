#include "ef_effect_control.h"
#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "m_debug.h"

static void eHanabiBotan1_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eHanabiBotan1_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eHanabiBotan1_mv(eEC_Effect_c* effect, GAME* game);
static void eHanabiBotan1_dw(eEC_Effect_c* effect, GAME* game);

#define CALC_EASE(x) (1.0f - sqrtf(1.0f - (x)))
#define EFFECT_LIFETIME 110

eEC_PROFILE_c iam_ef_hanabi_botan1 = {
    // clang-format off
    &eHanabiBotan1_init,
    &eHanabiBotan1_ct,
    &eHanabiBotan1_mv,
    &eHanabiBotan1_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
    // clang-format on
};

static void eHanabiBotan1_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_HANABI_BOTAN1, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void eHanabiBotan1_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = EFFECT_LIFETIME;
    effect->scale.x = 0.01f;
    effect->scale.y = 0.01f;
    effect->scale.z = 0.01f;
    effect->effect_specific[0] = 0;
    effect->effect_specific[1] = 0;
    effect->effect_specific[2] = 0;
    effect->offset.x = 0.f;
    effect->offset.y = 0.f;
    effect->offset.z = 0.f;
    effect->effect_specific[3] = ((u16)RANDOM_F(10.f)) & 1;
    effect->effect_specific[4] = 0; /* phase counter */
}

static void eHanabiBotan1_mv(eEC_Effect_c* effect, GAME* game) {
    f32 dt = (f32)game->graph->dt_num_60fps_frames;
    f32 t = (f32)EFFECT_LIFETIME - effect->lifetime;
    effect->effect_specific[0] += F32_TO_S16(0x300 * dt);
    effect->effect_specific[1] += F32_TO_S16(0x100 * dt);
    effect->effect_specific[2] += F32_TO_S16(0x80 * dt);
    effect->offset.x = sin_s(effect->effect_specific[1]) * 2.f;
    effect->offset.z = sin_s(-effect->effect_specific[1]) * 2.f;
    add_calc2(&effect->scale.x, 0.07, CALC_EASE(0.2f), 5.f);
    effect->scale.y = effect->scale.x;
    effect->scale.z = effect->scale.x;
    if (effect->effect_specific[4] < 1 && t >= 10.0f) {
        static rgba_t botan1_light[] = { { 75, 45, 30, 255 }, { 30, 90, 30, 255 } };
        rgba_t resultColor;
        effect->effect_specific[4] = 1;
        eEC_CLIP->decide_light_power_proc(&resultColor, botan1_light[effect->effect_specific[3]], effect->position,
                                          game, 2.f, 0.f, 480.f);
        if (effect->arg0) {
            resultColor.r = resultColor.r * (4.f / 3.f);
            resultColor.g = resultColor.g * (4.f / 3.f);
            resultColor.b = resultColor.b * (4.f / 3.f);
        }
        eEC_CLIP->regist_effect_light(resultColor, 20, 50, TRUE);
    }
    if (effect->effect_specific[4] < 2 && t >= 72.0f) {
        xyz_t p = effect->position;
        effect->effect_specific[4] = 2;
        p.y += 200.f;
        sAdo_OngenTrgStart(NA_SE_HANABI0, &p);
    }
}

eEC_morph_data_c eHanabiBotan1_morph_data1[] = {
    { 0, 0, FALSE, 255.f, 255.f }, { 0, 0, FALSE, 255.f, 255.f },  { 34, 44, TRUE, 0.f, 100.f },
    { 44, 54, TRUE, 150.f, 0.f },  { 10, 34, TRUE, 0.f, 255.f },   { 0, 0, FALSE, 255.f, 255.f },
    { 0, 0, FALSE, 0.f, 0.f },     { 34, 44, TRUE, 100.f, 255.f }, { 0, 0, FALSE, 255.f, 255.f },
};

eEC_morph_data_c eHanabiBotan1_morph_data2[] = {
    { 0, 0, FALSE, 255.f, 255.f }, { 0, 0, FALSE, 255.f, 255.f },  { 34, 44, TRUE, 0.f, 50.f },
    { 44, 54, TRUE, 150.f, 0.f },  { 10, 34, TRUE, 0.f, 255.f },   { 0, 0, FALSE, 0.f, 0.f },
    { 0, 0, FALSE, 255.f, 255.f }, { 34, 44, FALSE, 50.f, 255.f }, { 0, 0, FALSE, 255.f, 255.f },
};

eEC_morph_data_c* eHanabiBotan1_morph_table[] = { eHanabiBotan1_morph_data1, eHanabiBotan1_morph_data2 };

extern Gfx ef_hanabi_b_00_modelT[];

static void eHanabiBotan1_dw(eEC_Effect_c* effect, GAME* game) {
    u8 result[9];
    f32 v2, v;
    s16 index;
    f32 t = (f32)EFFECT_LIFETIME - effect->lifetime;
    s16 active_frames = (s16)t;
    v = (sin_s(effect->effect_specific[0]) + 1.f) * 0.5f * 0.14000005f + 0.93f;
    index = effect->effect_specific[3];
    v2 = eEL_CalcAdjust_F(t, 0.0f, (f32)(EFFECT_LIFETIME - 1), 0.0f, 0.01f) + effect->scale.x;
    eEC_CLIP->morph_combine_proc(result, eHanabiBotan1_morph_table[index], active_frames);
    OPEN_DISP(game->graph);
    _texture_z_light_fog_prim_xlu(game->graph);
    Matrix_translate(effect->position.x + effect->offset.x, effect->position.y + effect->offset.y,
                     effect->position.z + effect->offset.z, MTX_LOAD);
    Matrix_RotateX(DEG2SHORT_ANGLE2(270), MTX_MULT);
    Matrix_RotateZ(-effect->effect_specific[1], MTX_MULT);
    Matrix_scale(v, 1.f, 1.f, MTX_MULT);
    Matrix_RotateZ(effect->effect_specific[1], MTX_MULT);
    Matrix_scale(v2 * (GETREG(MYKREG, 0x1b) * 0.01f + 1.f), v2 * (GETREG(MYKREG, 0x1b) * 0.01f + 1.f),
                 v2 * (GETREG(MYKREG, 0x1b) * 0.01f + 1.f), MTX_MULT);
    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, result[4], result[0], result[1], result[2], result[3]);
    gDPSetEnvColor(NEXT_POLY_XLU_DISP, result[5], result[6], result[7], 255);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_hanabi_b_00_modelT);
    CLOSE_DISP(game->graph);
}
