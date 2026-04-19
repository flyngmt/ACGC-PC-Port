#include "ef_effect_control.h"

#include "m_common_data.h"

extern Gfx ef_siawase01_00_modelT[];
extern EVW_ANIME_DATA ef_siawase01_00_evw_anime;

static void eSSHKR_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eSSHKR_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eSSHKR_mv(eEC_Effect_c* effect, GAME* game);
static void eSSHKR_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_siawase_hikari = {
    // clang-format off
    &eSSHKR_init,
    &eSSHKR_ct,
    &eSSHKR_mv,
    &eSSHKR_dw,
    72,
    eEC_EFFECT_SIAWASE_HANA,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eSSHKR_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    xyz_t ofs;

    eEC_CLIP->effect_make_proc(eEC_EFFECT_SIAWASE_HANA, pos, prio, angle, game, item_name, 0, 0);

    ofs = ZeroVec;
    ofs.z = -22.0f;
    eEC_CLIP->make_effect_proc(eEC_EFFECT_SIAWASE_HIKARI, pos, &ofs, game, NULL, item_name, prio, 0, 0);
}

static void eSSHKR_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->scale.x = 0.0f;
    effect->scale.y = 0.0f;
    effect->scale.z = 0.0f;

    effect->effect_specific[0] = 150;

    effect->timer = 22;
}

static void eSSHKR_mv(eEC_Effect_c* effect, GAME* game) {
    f32 scale;

    sAdo_OngenPos((uintptr_t)effect, 14, &effect->position);

    eEC_CLIP->set_continious_env_proc(effect, 22, 122);

    if (effect->state == eEC_STATE_NORMAL) {
        scale = eEC_CLIP->calc_adjust_proc(22 - effect->timer, 0, 21, 0.0f, 0.015f);
        effect->scale.x = scale;
        effect->scale.y = scale;
        effect->scale.z = scale;
        effect->effect_specific[0] = 150;
    } else if (effect->state == eEC_STATE_CONTINUOUS) {
        effect->scale.x = 0.015f;
        effect->scale.y = 0.015f;
        effect->scale.z = 0.015f;
        effect->effect_specific[0] = 150;
    } else if (effect->state == eEC_STATE_FINISHED) {
        effect->effect_specific[0] = eEC_CLIP->calc_adjust_proc(72 - effect->timer, 0, 72, 150.0f, 0.0f);
    }
}

static void eSSHKR_dw(eEC_Effect_c* effect, GAME* game) {
    u8 alpha = effect->effect_specific[0];

    OPEN_DISP(game->graph);

    eEC_CLIP->auto_matrix_xlu_offset_proc(game, &effect->position, &effect->scale, &effect->offset);

    Evw_Anime_Set((GAME_PLAY*)game, &ef_siawase01_00_evw_anime);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 50, 255, 255, 200, alpha);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_siawase01_00_modelT);

    CLOSE_DISP(game->graph);
}
