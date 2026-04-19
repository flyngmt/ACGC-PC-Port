#include "ef_effect_control.h"
#include "m_common_data.h"

static void eAS2_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eAS2_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eAS2_mv(eEC_Effect_c* effect, GAME* game);
static void eAS2_dw(eEC_Effect_c* effect, GAME* game);

extern Gfx ef_ase02_00_modelT[];
extern Gfx ef_ase02_01_modelT[];
extern Gfx ef_ase02_02_modelT[];
extern Gfx ef_ase02_03_modelT[];

static Gfx* eAS2_model_table[] = {
    ef_ase02_00_modelT,
    ef_ase02_01_modelT,
    ef_ase02_02_modelT,
    ef_ase02_03_modelT,
};

eEC_PROFILE_c iam_ef_ase2 = {
    // clang-format off
    &eAS2_init,
    &eAS2_ct,
    &eAS2_mv,
    &eAS2_dw,
    eEC_IMMEDIATE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eAS2_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    xyz_t offs;

    offs.x = 0.0f;
    offs.y = 0.0f;
    offs.z = 30.0f;
    eEC_CLIP->make_effect_proc(eEC_EFFECT_ASE2, pos, &offs, game, NULL, item_name, prio, 0, 0);
}

static void eAS2_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->scale.x = 0.006f;
    effect->scale.y = 0.006f;
    effect->scale.z = 0.006f;
    effect->effect_specific[0] = 0;
    effect->timer = 26;
}

static void eAS2_mv(eEC_Effect_c* effect, GAME* game) {
    eEC_CLIP->set_continious_env_proc(effect, 26, 52);
    effect->effect_specific[0]++;
    sAdo_OngenPos((uintptr_t)effect, 0x29, &effect->position);
}

static void eAS2_dw(eEC_Effect_c* effect, GAME* game) {
    s16 idx = (s16)((effect->effect_specific[0] & 12) >> 2);

    OPEN_DISP(game->graph);

    eEC_CLIP->auto_matrix_xlu_offset_proc(game, &effect->position, &effect->scale, &effect->offset);
    gSPDisplayList(NEXT_POLY_XLU_DISP, eAS2_model_table[idx]);

    CLOSE_DISP(game->graph);
}
