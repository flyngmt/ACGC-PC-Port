#include "ef_effect_control.h"

#include "m_common_data.h"

extern Gfx ef_neboke_awa01_modelT[];

static void eNeboke_Akubi_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eNeboke_Akubi_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eNeboke_Akubi_mv(eEC_Effect_c* effect, GAME* game);
static void eNeboke_Akubi_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_neboke_akubi = {
    // clang-format off
    &eNeboke_Akubi_init,
    &eNeboke_Akubi_ct,
    &eNeboke_Akubi_mv,
    &eNeboke_Akubi_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eNeboke_Akubi_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_NEBOKE_AKUBI, pos, NULL, game, &angle, item_name, prio, arg0, arg1);
}

static void eNeboke_Akubi_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    xyz_t vec = { 0.0f, 7.0f, 13.5f };
    f32 x, y, z;

    x = RANDOM2_F(3.0f);
    y = RANDOM2_F(3.0f);
    z = RANDOM2_F(3.0f);

    effect->timer = 80;

    effect->effect_specific[0] = *(s16*)ct_arg;
    effect->effect_specific[1] = qrand();

    sMath_RotateY(&vec, SHORT2RAD_ANGLE2(effect->effect_specific[0]));
    effect->position.x += vec.x + x;
    effect->position.y += vec.y + y;
    effect->position.z += vec.z + z;

    eEC_CLIP->random_first_speed_proc(&effect->velocity, 0.15f, 30.0f, 0.0f);
    sMath_RotateX(&effect->velocity, DEG2RAD(20.0f));
    sMath_RotateY(&effect->velocity, SHORT2RAD_ANGLE2(effect->effect_specific[0]));

    effect->acceleration.x = 0.0f;
    effect->acceleration.y = 0.003425f;
    effect->acceleration.z = 0.0f;
}

static void eNeboke_Akubi_mv(eEC_Effect_c* effect, GAME* game) {
    f32 dt = (f32)game->graph->dt_num_60fps_frames;

    effect->velocity.x += effect->acceleration.x * dt;
    effect->velocity.y += effect->acceleration.y * dt;
    effect->velocity.z += effect->acceleration.z * dt;
    effect->position.x += effect->velocity.x * dt;
    effect->position.y += effect->velocity.y * dt;
    effect->position.z += effect->velocity.z * dt;

    effect->effect_specific[1] += F32_TO_S16(DEG2SHORT_ANGLE2(11.25f) * dt);
}

static void eNeboke_Akubi_dw(eEC_Effect_c* effect, GAME* game) {
    static f32 scale_base[] = { 0.005f, 0.0015f };
    f32 t = 80.0f - effect->lifetime;

    effect->scale.x = eEL_CalcAdjust_F(t, 0.0f, 4.0f, 0.0f, scale_base[effect->arg0]);
    if (t < 1.0f) {
        effect->effect_specific[2] = 200;
        effect->scale.x *= 1.2f;
    } else {
        effect->effect_specific[2] = 255;
    }
    effect->scale.z = effect->scale.y = effect->scale.x;
    effect->scale.x *= sin_s(effect->effect_specific[1]) * 0.2f + 1.0f;
    effect->scale.y *= cos_s(effect->effect_specific[1]) * 0.2f + 1.0f;

    OPEN_DISP(game->graph);

    eEC_CLIP->auto_matrix_xlu_proc(game, &effect->position, &effect->scale);

    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 128, 255, 255, 255, effect->effect_specific[2]);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_neboke_awa01_modelT);

    CLOSE_DISP(game->graph);
}
