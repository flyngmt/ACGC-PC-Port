#include "ef_effect_control.h"

#include "libultra/libultra.h"
#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"

extern Gfx ef_sleep01_modelT[];

static void eSleep_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eSleep_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eSleep_mv(eEC_Effect_c* effect, GAME* game);
static void eSleep_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_neboke_awa = {
    // clang-format off
    &eSleep_init,
    &eSleep_ct,
    &eSleep_mv,
    &eSleep_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eSleep_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_NEBOKE_AWA, pos, NULL, game, &angle, item_name, prio, arg0, arg1);
}

static void eSleep_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    xyz_t vec;
    u16 angle = *(s16*)ct_arg;

    effect->effect_specific[0] = angle;

    if (angle < DEG2SHORT_ANGLE2(180.0f)) {
        vec.x = 5.0f;
        vec.y = 10.0f;
        vec.z = 13.0f;
    } else {
        vec.x = -5.0f;
        vec.y = 10.0f;
        vec.z = 13.0f;
    }

    effect->timer = 64;

    sMath_RotateY(&vec, SHORT2RAD_ANGLE2(effect->effect_specific[0]));
    effect->position.x += vec.x;
    effect->position.y += vec.y;
    effect->position.z += vec.z;

    bzero(&effect->velocity, 12);
    effect->velocity.y = 0.18f;

    bzero(&effect->acceleration, 12);
    effect->acceleration.y = 0.008f;

    bzero(&effect->scale, 12);

    effect->offset = effect->position;
}

static void eSleep_mv(eEC_Effect_c* effect, GAME* game) {
    f32 dt = (f32)game->graph->dt_num_60fps_frames;
    f32 t = 64.0f - effect->lifetime;

    effect->effect_specific[2] += F32_TO_S16(DEG2SHORT_ANGLE2(11.25f) * dt);
    effect->effect_specific[3] += F32_TO_S16(DEG2SHORT_ANGLE2(6.33f) * dt);

    effect->velocity.x += effect->acceleration.x * dt;
    effect->velocity.y += effect->acceleration.y * dt;
    effect->velocity.z += effect->acceleration.z * dt;
    effect->position.x += effect->velocity.x * dt;
    effect->position.y += effect->velocity.y * dt;
    effect->position.z += effect->velocity.z * dt;

    effect->scale.x = eEL_CalcAdjust_F(t, 0.0f, 40.0f, 0.0f, 0.003f);
    effect->scale.y = effect->scale.x;
    effect->scale.z = effect->scale.x;
    effect->effect_specific[1] = 255;
    effect->scale.x *= sin_s(effect->effect_specific[2]) * 0.3f + 1.0f;
    effect->scale.x *= cos_s(effect->effect_specific[2]) * 0.3f + 1.0f;
}

static void eSleep_dw(eEC_Effect_c* effect, GAME* game) {
    s16 atan;
    xyz_t vec;

    vec.x = effect->position.x + sin_s(effect->effect_specific[3]) * 2.7f;
    vec.y = effect->position.y;
    vec.z = effect->position.z;

    OPEN_DISP(game->graph);

    _texture_z_light_fog_prim_xlu(game->graph);

    Matrix_translate(vec.x, vec.y, vec.z, MTX_LOAD);
    Matrix_mult(&((GAME_PLAY*)game)->billboard_matrix, MTX_MULT);
    atan = atans_table(vec.y - effect->offset.y, vec.x - effect->offset.x);
    Matrix_RotateZ(-(atan + DEG2SHORT_ANGLE2(180.0f)), MTX_MULT);
    Matrix_scale(effect->scale.x, effect->scale.y, effect->scale.z, MTX_MULT);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 128, 255, 255, 255, (u8)effect->effect_specific[1]);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_sleep01_modelT);

    effect->offset = vec;

    CLOSE_DISP(game->graph);
}
