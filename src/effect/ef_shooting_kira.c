#include "ef_effect_control.h"

#include "m_common_data.h"
#include "sys_matrix.h"
#include "m_rcp.h"
#include "m_debug.h"

static void eShootingKira_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eShootingKira_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eShootingKira_mv(eEC_Effect_c* effect, GAME* game);
static void eShootingKira_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_shooting_kira = {
    // clang-format off
    &eShootingKira_init,
    &eShootingKira_ct,
    &eShootingKira_mv,
    &eShootingKira_dw,
    eEC_IMMEDIATE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eShootingKira_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_SHOOTING_KIRA, pos, NULL, game, NULL, item_name, prio, arg0, angle);
}

static void eShootingKira_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    static xyz_t scale0 = { 0.0f, 0.0f, 0.0f };
    f32 speed_scale = effect->arg0 * 0.01f;

    effect->timer = 42 + GETREG(MYKREG, 32);
    effect->scale = scale0;
    
    effect->acceleration = effect->position;
    effect->acceleration.x -= 115.0f * speed_scale * sin_s(effect->arg1);
    effect->acceleration.z -= 115.0f * speed_scale * cos_s(effect->arg1);

    effect->velocity = effect->position;
    effect->velocity.x += 115.0f * speed_scale * sin_s(effect->arg1);
    effect->velocity.z += 115.0f * speed_scale * cos_s(effect->arg1);
}

static void eShootingKira_mv(eEC_Effect_c* effect, GAME* game) {
    f32 max = (f32)(42 + GETREG(MYKREG, 32));
    f32 t = max - effect->lifetime;
    s16 fadein = max * 0.7f;
    f32 scale;

    if (t < (f32)fadein) {
        scale = eEL_CalcAdjust_F(t, 0, max * 0.7f, 0.0f, 0.0065f);
    } else {
        s16 fadein2 = max * 0.87f;

        if (t < (f32)fadein2) {
            scale = eEL_CalcAdjust_F(t, max * 0.7f, max * 0.87f, 0.0065f, 0.00975f);
        } else {
            scale = eEL_CalcAdjust_F(t, max * 0.7f, max, 0.00975f, 0.0f);
        }
    }

    effect->scale.x = scale;
    effect->scale.y = scale;
    effect->scale.z = scale;

    effect->position.x = eEL_CalcAdjust_F(t, 0, 42 + GETREG(MYKREG, 32), effect->acceleration.x, effect->velocity.x);
    effect->position.z = eEL_CalcAdjust_F(t, 0, 42 + GETREG(MYKREG, 32), effect->acceleration.z, effect->velocity.z);
}

extern Gfx ef_takurami01_normal_render_mode[];
extern Gfx ef_takurami01_kira_modelT[];

static void eShootingKira_dw(eEC_Effect_c* effect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    f32 max = (f32)(42 + GETREG(MYKREG, 32));
    f32 t = max - effect->lifetime;
    s16 fadeout = max * 0.87f;
    f32 alpha;
    s16 angle_z;

    if (t <= (f32)fadeout) {
        alpha = eEL_CalcAdjust_F(t, 0, max * 0.87f, 100.0f, 150.0f);
    } else {
        alpha = eEL_CalcAdjust_F(t, max * 0.87f, max, 150.0f, 100.0f);
    }

    angle_z = F32_TO_S16(eEL_CalcAdjust_F(t, 0.0f, max, 0.0f, 0x20000));
    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
    Matrix_mult(&play->billboard_matrix, MTX_MULT);
    Matrix_RotateZ(angle_z, MTX_MULT);
    Matrix_scale(effect->scale.x, effect->scale.y, effect->scale.z, MTX_MULT);
    _texture_z_light_fog_prim_xlu(game->graph);

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 255, 255, 255, (u8)(int)alpha);
    gSPSegment(NEXT_POLY_XLU_DISP, ANIME_1_TXT_SEG, ef_takurami01_normal_render_mode);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_takurami01_kira_modelT);

    CLOSE_DISP(game->graph);
}
