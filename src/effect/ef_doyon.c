#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"

static void eDoyon_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eDoyon_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eDoyon_mv(eEC_Effect_c* effect, GAME* game);
static void eDoyon_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_doyon = {
    // clang-format off
    &eDoyon_init,
    &eDoyon_ct,
    &eDoyon_mv,
    &eDoyon_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eDoyon_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_DOYON, pos, NULL, game, &angle, item_name, prio, arg0, arg1);
}

static void eDoyon_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    s16 rng = qrand();
    s16 rng_angle = (s16)((f32)rng * 0.75f);

    effect->position.x += 10.0f * sin_s(rng_angle);
    effect->position.y += 10.0f * cos_s(rng_angle);

    effect->velocity.x += sin_s(rng_angle) * 0.5f;
    effect->velocity.y += cos_s(rng_angle) * 0.5f;

    effect->offset.z = 20.0f;

    effect->scale = ZeroVec;
    effect->scale.z = 0.1f;

    effect->timer = 60;
    sAdo_OngenTrgStart(NA_SE_DOYON, &effect->position);
}

static void eDoyon_mv(eEC_Effect_c* effect, GAME* game) {
    f32 progress = eEC_CLIP->calc_adjust_proc(effect->timer, 0, 60, 0.0f, 5.0f);
    f32 dt = (f32)game->graph->dt_num_60fps_frames;
    f32 decay = powf(sqrtf(0.95f), dt);

    effect->velocity.x += effect->acceleration.x * dt;
    effect->velocity.y += effect->acceleration.y * dt;
    effect->velocity.z += effect->acceleration.z * dt;
    effect->position.x += effect->velocity.x * dt;
    effect->position.y += effect->velocity.y * dt;
    effect->position.z += effect->velocity.z * dt;

    effect->effect_specific[0] += F32_TO_S16(DEG2SHORT_ANGLE2(5.625f) * dt);
    effect->effect_specific[1] += F32_TO_S16(DEG2SHORT_ANGLE2(5.625f) * dt);

    effect->velocity.x *= decay;
    effect->velocity.y *= decay;

    if (effect->timer > 50) {
        f32 scale = (60 - effect->timer) * 0.00065f;

        effect->scale.x = scale * (1.0f + 0.2f * cos_s(effect->effect_specific[0]));
        effect->scale.y = scale * (1.0f + 0.2f * sin_s(effect->effect_specific[0]));
    } else {
        effect->scale.x = (1.0f + 0.2f * cos_s(effect->effect_specific[0])) * 0.0065f;
        effect->scale.y = (1.0f + 0.2f * sin_s(effect->effect_specific[0])) * 0.0065f;
    }

    effect->offset.x = progress * cos_s(effect->effect_specific[1]);
    effect->offset.y = progress * sin_s(effect->effect_specific[1]);
}

extern Gfx ef_doyon01_00_modelT[];

static void eDoyon_dw(eEC_Effect_c* effect, GAME* game) {
    u8 a = (int)eEC_CLIP->calc_adjust_proc(effect->timer, 0, 8, 0.0f, 220.0f);

    OPEN_DISP(game->graph);

    eEC_CLIP->auto_matrix_xlu_offset_proc(game, &effect->position, &effect->scale, &effect->offset);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 40, 30, 40, a);
    gDPSetEnvColor(NEXT_POLY_XLU_DISP, 100, 100, 255, 255);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_doyon01_00_modelT);

    CLOSE_DISP(game->graph);
}
