#include "ef_effect_control.h"

#include "graph.h"
#include "m_common_data.h"
#include "m_debug.h"
#include "m_rcp.h"
#include "sys_matrix.h"

extern Gfx ef_reset_hole_modelT[];

static void eReset_Hole_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eReset_Hole_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eReset_Hole_mv(eEC_Effect_c* effect, GAME* game);
static void eReset_Hole_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_reset_hole = {
    // clang-format off
    &eReset_Hole_init,
    &eReset_Hole_ct,
    &eReset_Hole_mv,
    &eReset_Hole_dw,
    24,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eReset_Hole_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    pos.y += 1.0f;

    eEC_CLIP->make_effect_proc(eEC_EFFECT_RESET_HOLE, pos, NULL, game, &angle, item_name, prio, arg0, arg1);
}

static void eReset_Hole_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 16;

    if (effect->arg0 == 1) {
        if (effect->arg1 == 0) {
            effect->scale.x = effect->scale.y = effect->scale.z = 0.01f;
        } else {
            effect->scale.x = effect->scale.y = effect->scale.z = (GETREG(TAKREG, 0x32) * 0.01f + 0.93f) * 0.01f;
        }
    } else {
        effect->scale = ZeroVec;
    }

    effect->effect_specific[0] = *(s16*)ct_arg;
    effect->effect_specific[1] = 0; /* emit toggle counter */
    effect->effect_specific[2] = 0;
    effect->effect_specific[3] = 0;
}

static void eReset_Hole_mv(eEC_Effect_c* effect, GAME* game) {
    s16 angle;
    f32 scale;
    int i;

    eEC_CLIP->set_continious_env_proc(effect, 16, 120);

    if ((effect->state == eEC_STATE_NORMAL) && (effect->arg0 != 1)) {
        if (effect->arg1 == 0) {
            scale = 0.01f;
        } else {
            scale = (GETREG(TAKREG, 0x32) * 0.01f + 0.93f) * 0.01f;
        }
        effect->scale.x = effect->scale.y = effect->scale.z =
            eEL_CalcAdjust_F(effect->lifetime, 0.0f, 16.0f, scale, 0.0f);

        {
            effect->effect_specific[2] += F32_TO_S16((f32)game->graph->dt_num_60fps_frames * 100.0f);
            if (effect->effect_specific[2] >= 800) {
                effect->effect_specific[2] -= 800;
                int rotate_180 = ((effect->effect_specific[1] & 1) == 0);
                for (i = 0; i < 3; i++) {
                    static s16 angle_tbl[] = { DEG2SHORT_ANGLE(0.0f), DEG2SHORT_ANGLE(135.0f), DEG2SHORT_ANGLE(270.0f) };
                    xyz_t pos = effect->position;

                    angle = angle_tbl[i];
                    if (rotate_180) {
                        angle += DEG2SHORT_ANGLE2(180.0f);
                    }

                    eEC_CLIP->effect_make_proc(eEC_EFFECT_DIG_MUD, pos, effect->prio, angle, game, effect->item_name,
                                               effect->arg0, DEG2SHORT_ANGLE(-179.965f));
                }
                effect->effect_specific[1]++;
            }
        }
    } else if (effect->state == eEC_STATE_FINISHED) {
        if (effect->arg1 == 0) {
            scale = 0.01f;
        } else {
            scale = (GETREG(TAKREG, 0x32) * 0.01f + 0.93f) * 0.01f;
        }
        effect->scale.x = effect->scale.y = effect->scale.z =
            eEL_CalcAdjust_F(effect->lifetime, 0.0f, 24.0f, 0.0f, scale);

        if (effect->lifetime > 8.0f) {
            effect->effect_specific[3] += F32_TO_S16((f32)game->graph->dt_num_60fps_frames * 100.0f);
            if (effect->effect_specific[3] >= 800) {
                effect->effect_specific[3] -= 800;
                int rotate_180 = ((effect->effect_specific[1] & 1) == 0);
                for (i = 0; i < 3; i++) {
                    static s16 angle_tbl[] = { DEG2SHORT_ANGLE(0.0f), DEG2SHORT_ANGLE(135.0f), DEG2SHORT_ANGLE(270.0f) };
                    xyz_t pos = effect->position;

                    angle = angle_tbl[i];
                    if (rotate_180) {
                        angle += DEG2SHORT_ANGLE2(180.0f);
                    }

                    eEC_CLIP->effect_make_proc(eEC_EFFECT_DIG_MUD, pos, effect->prio, angle, game, effect->item_name,
                                               effect->arg0, DEG2SHORT_ANGLE(-179.965f));
                }
                effect->effect_specific[1]++;
            }
        }
    } else {
        if (effect->arg1 == 0) {
            scale = 0.01f;
        } else {
            scale = (GETREG(TAKREG, 0x32) * 0.01f + 0.93f) * 0.01f;
        }
        effect->scale.x = effect->scale.y = effect->scale.z = scale;
    }
}

static void eReset_Hole_dw(eEC_Effect_c* effect, GAME* game) {
    f32 scale;

    OPEN_DISP(game->graph);

    _texture_z_light_fog_prim_xlu(game->graph);

    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);

    scale = GETREG(MYKREG, 0x1b) * 0.01f + 1.0f;
    Matrix_scale(effect->scale.x * scale, effect->scale.y * scale, effect->scale.z * scale, MTX_MULT);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_reset_hole_modelT);

    CLOSE_DISP(game->graph);
}
