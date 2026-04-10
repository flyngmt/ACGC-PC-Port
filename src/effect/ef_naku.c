#include "ef_effect_control.h"

#include "m_common_data.h"

static void eNaku_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eNaku_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eNaku_mv(eEC_Effect_c* effect, GAME* game);
static void eNaku_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_naku = {
    // clang-format off
    &eNaku_init,
    &eNaku_ct,
    &eNaku_mv,
    &eNaku_dw,
    eEC_IMMEDIATE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eNaku_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    xyz_t base_ofs = { 0.0f, 0.0f, -6.0f };
    s16 _angle = angle;

    sMath_RotateY(&base_ofs, SHORT2RAD_ANGLE2(_angle));
    pos.x += base_ofs.x;
    pos.y += base_ofs.y;
    pos.z += base_ofs.z;
    eEC_CLIP->make_effect_proc(eEC_EFFECT_NAKU, pos, NULL, game, &_angle, item_name, prio, 0, 0);
}

static void eNaku_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->effect_specific[0] = *(s16*)ct_arg;
    effect->effect_specific[1] = 0;
    effect->timer = 32;
}

static void eNaku_mv(eEC_Effect_c* effect, GAME* game) {
    s32 prio;
    u16 item_name;
    GAME_PLAY* play = (GAME_PLAY*)game;

    item_name = effect->item_name;
    prio = effect->prio;
    eEC_CLIP->set_continious_env_proc(effect, 32, 18);

    if ((effect->timer & 1) && (eEC_CLIP != NULL)) {
        eEC_CLIP->effect_make_proc(eEC_EFFECT_NAMIDA, effect->position, prio, effect->effect_specific[0], &play->game,
                                   item_name, effect->effect_specific[1] & 1, 0);
        effect->effect_specific[1]++;
    }

    sAdo_OngenPos((uintptr_t)effect, 0x2E, &effect->position);
}

static void eNaku_dw(eEC_Effect_c* effect, GAME* game) {
    return;
}
