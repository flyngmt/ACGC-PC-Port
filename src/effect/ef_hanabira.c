#include "ef_effect_control.h"
#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "m_debug.h"
#include "graph.h"

static void eHanabira_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eHanabira_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eHanabira_mv(eEC_Effect_c* effect, GAME* game);
static void eHanabira_dw(eEC_Effect_c* effect, GAME* game);
#define EFFECT_LIFETIME 60
extern Gfx ef_hana01_pa_a_modelT[], ef_hana01_co_a_modelT[], ef_hana01_tu_a_modelT[], ef_hana01_ha_a_modelT[];
Gfx* ef_hanabira_model_tbl[] = { ef_hana01_pa_a_modelT, ef_hana01_co_a_modelT, ef_hana01_tu_a_modelT,
                                 ef_hana01_ha_a_modelT };
eEC_PROFILE_c iam_ef_hanabira = {
    // clang-format off
    &eHanabira_init,
    &eHanabira_ct,
    &eHanabira_mv,
    &eHanabira_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eHanabira_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_HANABIRA, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void eHanabira_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    f32 v;
    effect->effect_specific[0] = effect->arg0 / 3;
    effect->effect_specific[1] = effect->arg0 % 3;
    effect->timer = EFFECT_LIFETIME;
    v = RANDOM_F(0.5f) + 3.f;

    if (effect->arg1 == 2 || effect->arg1 == 3 || effect->arg1 == 1) {
        v *= 1.5f;
    }

    eEC_CLIP->random_first_speed_proc(&effect->velocity, v, 32.f, 32.f);
    effect->acceleration.x = 0.f;
    effect->acceleration.y = -effect->velocity.y * 0.05f;
    effect->acceleration.z = 0.f;
    effect->offset = ZeroVec;
    effect->effect_specific[4] = qrand();
    effect->effect_specific[2] = qrand();
    effect->effect_specific[3] = qrand();
    effect->scale.x = effect->scale.y = effect->scale.z = 0.009f;
    effect->effect_specific[5] = FALSE;
}

static void eHanabira_mv(eEC_Effect_c* effect, GAME* game) {
    f32 dt = (f32)game->graph->dt_num_60fps_frames;

    effect->velocity.x += effect->acceleration.x * dt;
    effect->velocity.y += effect->acceleration.y * dt;
    effect->velocity.z += effect->acceleration.z * dt;
    effect->position.x += effect->velocity.x * dt;
    effect->position.y += effect->velocity.y * dt;
    effect->position.z += effect->velocity.z * dt;
    if (effect->effect_specific[5] == FALSE) {
        effect->effect_specific[4] += (s16)(0xa00 * dt);
        effect->effect_specific[2] += (s16)(0x280 * dt);
        effect->effect_specific[3] += (s16)(0x280 * dt);
        if (effect->velocity.y <= 0.f) {
            effect->effect_specific[5] = TRUE;
            effect->acceleration.y = -0.05f;
        }

    } else {
        f32 s = sin_s(effect->effect_specific[4]) * 2.f;
        effect->offset.x = s;
        effect->offset.y = 0.f;
        effect->offset.z = -s;
        effect->effect_specific[4] += (s16)(0xa00 * dt);
        effect->effect_specific[2] += (s16)(0x662 * dt);
        effect->effect_specific[3] += (s16)(0x662 * dt);
    }
}

static void eHanabira_dw(eEC_Effect_c* effect, GAME* game) {
    N64Mtx* m = GRAPH_ALLOC(game->graph, 0x40);
    int v = (u8)eEL_CalcAdjust_F(effect->lifetime, 0.0f, 20.0f, 0.f, 255.f);
    OPEN_DISP(game->graph);
    _texture_z_light_fog_prim_xlu(game->graph);
    suMtxMakeSRT_ZXY(m, effect->scale.x * (GETREG(MYKREG, 0x1b) * 0.01f + 1.f),
                     effect->scale.y * (GETREG(MYKREG, 0x1b) * 0.01f + 1.f),
                     effect->scale.z * (GETREG(MYKREG, 0x1b) * 0.01f + 1.f), effect->effect_specific[2], 0,
                     effect->effect_specific[3], effect->position.x + effect->offset.x,
                     effect->position.y + effect->offset.y, effect->position.z + effect->offset.z);
    switch (effect->effect_specific[1]) {
        case 0: {
            gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_8, g_fdinfo->field_palette.flower0_pal);
        } break;
        case 1: {
            gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_8, g_fdinfo->field_palette.flower1_pal);
        } break;
        default: {
            gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_8, g_fdinfo->field_palette.flower2_pal);
        } break;
    }
    gSPMatrix(NEXT_POLY_XLU_DISP, m, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 255, 255, 255, (u8)v);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_hanabira_model_tbl[effect->effect_specific[0]]);
    CLOSE_DISP(game->graph);
}
