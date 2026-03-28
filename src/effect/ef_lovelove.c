#include "ef_effect_control.h"

#include "m_common_data.h"

static void eLove_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eLove_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eLove_mv(eEC_Effect_c* effect, GAME* game);
static void eLove_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_lovelove = {
    // clang-format off
    &eLove_init,
    &eLove_ct,
    &eLove_mv,
    &eLove_dw,
    eEC_IMMEDIATE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eLove_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    pos.y -= 10.0f;
    eEC_CLIP->make_effect_proc(eEC_EFFECT_LOVELOVE, pos, NULL, game, NULL, item_name, prio, 0, 0);
}

static void eLove_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 52;
}

static void eLove_mv(eEC_Effect_c* effect, GAME* game) {
    s32 prio;
    u16 name;

    eEC_CLIP->set_continious_env_proc(effect, 52, 102);
    sAdo_OngenPos((uintptr_t)effect, 14, &effect->position);

    if ((effect->timer & 7) == 0) {
        name = effect->item_name;
        prio = effect->prio;
        if ((eEC_CLIP != NULL)) {
            eEC_CLIP->effect_make_proc(eEC_EFFECT_LOVELOVE_HEART, effect->position, prio, 0, game, name, 0, 0);
        }
    }
}

static void eLove_dw(eEC_Effect_c* effect, GAME* game) {
    return;
}
