#include "ef_effect_control.h"
#include "graph.h"
#include "m_common_data.h"

static void eClacker_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eClacker_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eClacker_mv(eEC_Effect_c* effect, GAME* game);
static void eClacker_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_clacker = {
    // clang-format off
    &eClacker_init,
    &eClacker_ct,
    &eClacker_mv,
    &eClacker_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eClacker_Make_Effect(eEC_Effect_c* effect, GAME* game) {
    static s16 angle_tbl[] = {0x071C, 0x58E3, 0xAAAB};
    int i;

    for (i = 0; i < 3; i++) {
        eEC_CLIP->effect_make_proc(eEC_EFFECT_TAPE, effect->position, effect->prio,
                                   effect->effect_specific[0] + angle_tbl[i], game, effect->item_name,
                                   effect->effect_specific[0], 0x1000);
    }

    for (i = 0; i < 20; i++) {
        s16 arg0;

        if (i < 5) {
            arg0 = 0;
        } else if (i < 10) {
            arg0 = 1;
        } else if (i < 15) {
            arg0 = 2;
        } else {
            arg0 = 3;
        }
        eEC_CLIP->effect_make_proc(eEC_EFFECT_KAMIFUBUKI, effect->position, effect->prio, effect->effect_specific[0],
                                   game, effect->item_name, arg0, 0x1000);
    }
}

static void eClacker_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->effect_make_proc(eEC_EFFECT_DUST, pos, prio, 0, game, item_name, arg0, 3);

    eEC_CLIP->make_effect_proc(eEC_EFFECT_CLACKER, pos, NULL, game, &angle, item_name, prio, arg0, arg1);
}

static void eClacker_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    s16* arg = ct_arg;
    effect->effect_specific[0] = arg[0];
    effect->timer = 0x50;
    effect->velocity.x = 4.6f * sin_s(0x1000) * sin_s(effect->effect_specific[0]);
    effect->velocity.y = 4.6f * cos_s(0x1000);
    effect->velocity.z = 4.6f * sin_s(0x1000) * cos_s(effect->effect_specific[0]);
    effect->acceleration = ZeroVec;
    effect->acceleration.y = -0.125f;
    effect->effect_specific[1] = 0; /* burst-fired flag */
    effect->effect_specific[2] = 0;
}

static void eClacker_mv(eEC_Effect_c* effect, GAME* game) {
    /* lifetime starts at 80, "timer < 68" means t > 12, so emit once we
     * cross t==12 and continue every 8 ticks until effect dies. */
    f32 t = 80.0f - effect->lifetime;
    if (t >= 12.0f) {
        effect->effect_specific[2] += F32_TO_S16((f32)game->graph->dt_num_60fps_frames * 100.0f);
        if (effect->effect_specific[2] >= 800) {
            effect->effect_specific[2] -= 800;
            xyz_t pos = effect->position;
            pos.x += RANDOM2_F(100.0f);
            pos.y += RANDOM2_F(30.0f);
            pos.z += RANDOM2_F(100.0f);
            eEC_CLIP->effect_make_proc(eEC_EFFECT_KIGAE_LIGHT, pos, effect->prio, 0, game, effect->item_name, 0, 0);
        }
    }
    /* one-shot at original timer == 76 (t == 4). */
    if (effect->effect_specific[1] == 0 && t >= 4.0f) {
        eClacker_Make_Effect(effect, game);
        effect->effect_specific[1] = 1;
    }
    if (t >= 4.0f) {
        f32 dt = (f32)game->graph->dt_num_60fps_frames;
        f32 decay = powf(sqrtf(0.9f), dt);
        effect->velocity.x += effect->acceleration.x * dt;
        effect->velocity.y += effect->acceleration.y * dt;
        effect->velocity.z += effect->acceleration.z * dt;
        effect->position.x += effect->velocity.x * dt;
        effect->position.y += effect->velocity.y * dt;
        effect->position.z += effect->velocity.z * dt;
        effect->velocity.x *= decay;
        effect->velocity.y *= decay;
        effect->velocity.z *= decay;
    }
}

static void eClacker_dw(eEC_Effect_c* effect, GAME* game) {

}
