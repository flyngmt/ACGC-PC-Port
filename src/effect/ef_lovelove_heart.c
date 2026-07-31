#include "ef_effect_control.h"

#include "m_common_data.h"

extern Gfx ef_lovelove01_00_modelT[];

static void eLoveH_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eLoveH_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eLoveH_mv(eEC_Effect_c* effect, GAME* game);
static void eLoveH_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_lovelove_heart = {
    // clang-format off
    &eLoveH_init,
    &eLoveH_ct,
    &eLoveH_mv,
    &eLoveH_dw,
    eEC_IMMEDIATE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eLoveH_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_LOVELOVE_HEART, pos, NULL, game, NULL, item_name, prio, 0, 0);
}

static void eLoveH_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    eEC_CLIP->random_first_speed_proc(&effect->velocity, 0.55f, 170.0f, 0.0f);

    effect->timer = 120;

    effect->scale.x = 0.0f;
    effect->scale.y = 0.0f;
    effect->scale.z = 0.0f;

    effect->effect_specific[0] = 0;

    effect->acceleration.x = 0.0f;
    effect->acceleration.y = 0.0f;
    effect->acceleration.z = 0.0f;
}

static void eLoveH_mv(eEC_Effect_c* effect, GAME* game) {
    f32 dt = (f32)game->graph->dt_num_60fps_frames;
    f32 t = 120.0f - effect->lifetime;

    effect->velocity.x += effect->acceleration.x * dt;
    effect->velocity.y += effect->acceleration.y * dt;
    effect->velocity.z += effect->acceleration.z * dt;
    effect->position.x += effect->velocity.x * dt;
    effect->position.y += effect->velocity.y * dt;
    effect->position.z += effect->velocity.z * dt;

    effect->effect_specific[0] += F32_TO_S16(DEG2SHORT_ANGLE2(10.55f) * dt);
    effect->acceleration.y = eEL_CalcAdjust_F(t, 20.0f, 120.0f, 0.0f, 0.0425f);
}

static void eLoveH_dw(eEC_Effect_c* effect, GAME* game) {
    f32 temp1, temp2, temp3;
    u8 alpha;

    xyz_t* scale = &effect->scale;
    f32 t = 120.0f - effect->lifetime;
    s16 angle = effect->effect_specific[0];
    f32 sin = sin_s(angle);
    f32 cos = cos_s(angle);

    temp1 = eEL_CalcAdjust_F(t, 0.0f, 120.0f, 0.0f, 0.01f);
    temp2 = eEL_CalcAdjust_F(t, 0.0f, 30.0f, 1.3499999f, 0.85f);
    temp3 = eEL_CalcAdjust_F(t, 0.0f, 30.0f, 0.050000012f, 0.54999995f);
    alpha = (s8)eEL_CalcAdjust_F(t, 60.0f, 120.0f, 255.0f, 0.0f);

    scale->x = temp1 * (temp3 + ((sin + 1.0f) * 0.5f * (temp2 - temp3)));
    scale->y = temp1 * (temp3 + ((cos + 1.0f) * 0.5f * (temp2 - temp3)));
    scale->z = temp1;

    OPEN_DISP(game->graph);

    eEC_CLIP->auto_matrix_xlu_proc(game, &effect->position, scale);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 255, 255, 255, alpha);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_lovelove01_00_modelT);

    CLOSE_DISP(game->graph);
}
