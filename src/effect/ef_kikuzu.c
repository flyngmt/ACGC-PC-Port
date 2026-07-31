#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_lib.h"
#include "sys_matrix.h"
#include "m_rcp.h"

static void eKikuzu_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eKikuzu_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eKikuzu_mv(eEC_Effect_c* effect, GAME* game);
static void eKikuzu_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_kikuzu = {
    // clang-format off
    &eKikuzu_init,
    &eKikuzu_ct,
    &eKikuzu_mv,
    &eKikuzu_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eKikuzu_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_KIKUZU, pos, NULL, game, &angle, item_name, prio, arg0, arg1);
}

static void eKikuzu_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    f32 z = RANDOM_F(1.75f) + 0.5f;
    f32 y = RANDOM_F(4.0f) + 1.5f;
    s16* angle_p = (s16*)ct_arg;
    s16 angle = *angle_p + DEG2SHORT_ANGLE(180.0f) + RANDOM(DEG2SHORT_ANGLE2(80.0f));

    effect->timer = RANDOM(10) * 2 + 60;
    effect->scale.x = effect->scale.y = effect->scale.z = RANDOM2_F(0.002f) + 0.004f;
    effect->position.x += RANDOM2_F(10.0f);
    effect->position.y += RANDOM2_F(10.0f);
    effect->position.z += RANDOM2_F(10.0f);
    effect->offset.x = effect->position.y;
    effect->offset.y = mCoBG_GetBgY_AngleS_FromWpos(NULL, effect->position, 0.0f);
    effect->offset.y += 3.0f;
    effect->velocity.x = sin_s(angle) * z;
    effect->velocity.z = cos_s(angle) * z;
    effect->velocity.y = y;
    effect->acceleration.y = -0.25f;
    effect->effect_specific[0] = qrand();
    effect->effect_specific[2] = qrand();
    effect->effect_specific[1] = qrand() & 0x1FFF;
    effect->effect_specific[3] = qrand() & 0x1FFF;
}

static void eKikuzu_mv(eEC_Effect_c* effect, GAME* game) {
    f32 dt = (f32)game->graph->dt_num_60fps_frames;

    effect->offset.x = effect->position.y;
    effect->offset.z = effect->offset.y;
    effect->offset.y = mCoBG_GetBgY_AngleS_FromWpos(NULL, effect->position, 0.0f);
    effect->velocity.x += effect->acceleration.x * dt;
    effect->velocity.y += effect->acceleration.y * dt;
    effect->velocity.z += effect->acceleration.z * dt;
    effect->position.x += effect->velocity.x * dt;
    effect->position.y += effect->velocity.y * dt;
    effect->position.z += effect->velocity.z * dt;
    effect->effect_specific[0] += F32_TO_S16(effect->effect_specific[1] * dt);
    effect->effect_specific[2] += F32_TO_S16(effect->effect_specific[3] * dt);

    if (effect->position.y < effect->offset.y && effect->offset.x >= effect->offset.y && effect->velocity.y < 0.0f) {
        f32 bounce = DTCONV_GAME(0.6f, game);

        effect->position.y = effect->offset.y;
        effect->velocity.x *= bounce;
        effect->velocity.y *= -bounce;
        effect->velocity.z *= bounce;
        effect->effect_specific[1] >>= 1;
        effect->effect_specific[3] >>= 1;
    }

    if (effect->position.y < effect->offset.y && effect->position.y >= effect->offset.z) {
        effect->position.x -= effect->velocity.x;
        effect->position.y -= effect->velocity.y;
        effect->position.z -= effect->velocity.z;
        effect->velocity.x *= -0.6f;
        effect->velocity.z *= -0.6f;
    }
}

extern Gfx ef_kikuzu01_00_modelT[];

static void eKikuzu_dw(eEC_Effect_c* effect, GAME* game) {
    u8 a = (int)eEL_CalcAdjust_F(effect->lifetime, 0.0f, 16.0f, 0.0f, 255.0f);

    _texture_z_light_fog_prim_xlu(game->graph);
    OPEN_DISP(game->graph);

    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
    Matrix_RotateX(effect->effect_specific[0], MTX_MULT);
    Matrix_RotateZ(effect->effect_specific[2], MTX_MULT);
    Matrix_scale(effect->scale.x, effect->scale.y, effect->scale.z, MTX_MULT);

    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 255, 255, 200, a);
    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_kikuzu01_00_modelT);

    CLOSE_DISP(game->graph);
}
