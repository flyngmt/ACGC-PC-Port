#include "ef_effect_control.h"

#include "graph.h"
#include "m_common_data.h"

static void eSSHN_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eSSHN_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eSSHN_mv(eEC_Effect_c* effect, GAME* game);
static void eSSHN_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_siawase_hana = {
    // clang-format off
    &eSSHN_init,
    &eSSHN_ct,
    &eSSHN_mv,
    &eSSHN_dw,
    eEC_IMMEDIATE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eSSHN_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    pos.y -= 10.0f;

    eEC_CLIP->make_effect_proc(eEC_EFFECT_SIAWASE_HANA, pos, NULL, game, NULL, item_name, prio, 0, 0);
}

static void eSSHN_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    int i;
    xyz_t pos;

    effect->timer = 22;
    effect->effect_specific[0] = 0;
    if ((eEC_CLIP != NULL) && ((effect->timer & 1) != 0)) {
        pos = effect->position;
        pos.y -= 5.0f;

        for (i = 0; i < 5; i++) {
            eEC_CLIP->effect_make_proc(eEC_EFFECT_SIAWASE_HANA_CH, pos, effect->prio, 0, game, effect->item_name, i * 4,
                                       0);
        };
    }
}

static void eSSHN_mv(eEC_Effect_c* effect, GAME* game) {
    int prio;
    u16 item_name;
    xyz_t pos;

    eEC_CLIP->set_continious_env_proc(effect, 22, 122);
    {
        effect->effect_specific[0] += F32_TO_S16((f32)game->graph->dt_num_60fps_frames * 100.0f);
        if (effect->effect_specific[0] >= 400) {
            effect->effect_specific[0] -= 400;
            item_name = effect->item_name;
            prio = effect->prio;
            if (eEC_CLIP != NULL) {
                pos = effect->position;
                pos.y -= 5.0f;
                eEC_CLIP->effect_make_proc(eEC_EFFECT_SIAWASE_HANA_CH, pos, prio, 0, game, item_name, 0, 0);
            }
        }
    }
}

static void eSSHN_dw(eEC_Effect_c* effect, GAME* game) {
    return;
}
