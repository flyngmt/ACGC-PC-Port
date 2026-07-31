#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_debug.h"
#include "m_lib.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "graph.h"

static void eBreak_Axe_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eBreak_Axe_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eBreak_Axe_mv(eEC_Effect_c* effect, GAME* game);
static void eBreak_Axe_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_break_axe = {
    // clang-format off
    &eBreak_Axe_init,
    &eBreak_Axe_ct,
    &eBreak_Axe_mv,
    &eBreak_Axe_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eBreak_Axe_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_BREAK_AXE, pos, NULL, game, &angle, item_name, prio, arg0, arg1);
}

static void eBreak_Axe_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    s16 angle = *(s16*)ct_arg + DEG2SHORT_ANGLE2(180.0f);
    f32 speed_xz;
    f32 speed_y;
    f32 tz;
    f32 ty;
    f32 tx;
    s16 add_angle;

    effect->timer = RANDOM(10) * 2 + (35 + GETREG(TAKREG, 60)) * 2;
    effect->effect_specific[5] = effect->timer;

    if (effect->arg0 > 1) {
        effect->scale.x = effect->scale.y = effect->scale.z = (1.0f + fqrand()) * 0.01f;
    } else {
        effect->scale.x = effect->scale.y = effect->scale.z = 0.01f;
    }

    effect->offset.x = effect->position.y;
    effect->offset.y = mCoBG_GetBgY_AngleS_FromWpos(NULL, effect->position, 0.0f);
    if (effect->arg0 == 0) {
        angle += (int)((40.0f + GETREG(TAKREG, 56) + RANDOM_F(20.0f + GETREG(TAKREG, 57))) * 182.04445f);
        effect->offset.y += 10.0f;
    } else if (effect->arg0 == 1) {
        angle += (int)((20.0f + GETREG(TAKREG, 58) + RANDOM_F(20.0f + GETREG(TAKREG, 59))) * 182.04445f);
        effect->offset.y += 15.0f;
    } else {
        angle += F32_TO_S16(RANDOM_F(14563.0f));
        effect->offset.y += 3.0f;
    }

    effect->effect_specific[4] = *(s16*)ct_arg;
    if (effect->arg0 == 0) {
        tx = -17.0f + GETREG(TAKREG, 32);
        ty = 34.0f + GETREG(TAKREG, 33);
        tz = 20.0f + GETREG(TAKREG, 34);

        effect->position.x += tz * sin_s(effect->effect_specific[4]) + tx * cos_s(effect->effect_specific[4]);
        effect->position.y += ty;
        effect->position.z += tz * cos_s(effect->effect_specific[4]) - tx * sin_s(effect->effect_specific[4]);

        effect->effect_specific[0] = (-20.0f + GETREG(TAKREG, 35)) * 182.04445f;
        add_angle = (int)((-77.0f + GETREG(TAKREG, 36)) * 182.04445f);
        effect->effect_specific[4] += add_angle;
        effect->effect_specific[2] = (0.0f + GETREG(TAKREG, 37)) * 182.04445f;
        effect->effect_specific[1] = qrand() & 0xFFF;
        effect->effect_specific[3] = qrand() & 0xFFF;

        speed_xz = (0.5f + GETREG(TAKREG, 48) * 0.1f) * 0.5f + RANDOM_F((1.5f + GETREG(TAKREG, 49) * 0.1f) * 0.5f);
        speed_y = (8.0f + GETREG(TAKREG, 50) * 0.1f) * 0.5f + RANDOM_F((2.0f + GETREG(TAKREG, 51) * 0.1f) * 0.5f);
    } else if (effect->arg0 == 1) {
        tz = -4.0f + GETREG(TAKREG, 38);
        ty = 27.0f + GETREG(TAKREG, 39);
        tx = 17.0f + GETREG(TAKREG, 40);

        effect->position.x += tx * sin_s(effect->effect_specific[4]) + tz * cos_s(effect->effect_specific[4]);
        effect->position.y += ty;
        effect->position.z += tx * cos_s(effect->effect_specific[4]) - tz * sin_s(effect->effect_specific[4]);

        effect->effect_specific[0] = (-20.0f + GETREG(TAKREG, 41)) * 182.04445f;
        add_angle = (int)((-77.0f + GETREG(TAKREG, 42)) * 182.04445f);
        effect->effect_specific[4] += add_angle;
        effect->effect_specific[2] = (0.0f + GETREG(TAKREG, 43)) * 182.04445f;
        effect->effect_specific[1] = qrand() & 0xFFF;
        effect->effect_specific[3] = qrand() & 0xFFF;

        speed_xz = (1.5f + GETREG(TAKREG, 52) * 0.1f) * 0.5f + RANDOM_F((1.0f + GETREG(TAKREG, 53) * 0.1f) * 0.5f);
        speed_y = (7.5f + GETREG(TAKREG, 54) * 0.1f) * 0.5f + RANDOM_F((3.0f + GETREG(TAKREG, 55) * 0.1f) * 0.5f);
    } else {
        effect->position.x += RANDOM2_F(10.0f);
        effect->position.y += RANDOM2_F(10.0f);
        effect->position.z += RANDOM2_F(10.0f);

        effect->effect_specific[0] = qrand();
        effect->effect_specific[2] = qrand();
        effect->effect_specific[1] = qrand() & 0x1FFF;
        effect->effect_specific[3] = qrand() & 0x1FFF;

        speed_xz = (2.0f + GETREG(TAKREG, 44) * 0.1f) * 0.5f + RANDOM_F((3.5f + GETREG(TAKREG, 45) * 0.1f) * 0.5f);
        speed_y = (8.0f + GETREG(TAKREG, 46) * 0.1f) * 0.5f + RANDOM_F((5.0f + GETREG(TAKREG, 47) * 0.1f) * 0.5f);
    }

    effect->velocity.x = speed_xz * sin_s(angle);
    effect->velocity.z = speed_xz * cos_s(angle);
    effect->velocity.y = speed_y;
    effect->acceleration.y = -0.25f;
}

static void eBreak_Axe_mv(eEC_Effect_c* effect, GAME* game) {
    u32 ut_attr = mCoBG_Wpos2Attribute(effect->position, NULL);
    f32 dt = (f32)game->graph->dt_num_60fps_frames;

    effect->offset.x = effect->position.y;
    effect->offset.z = effect->offset.y;
    effect->offset.y = mCoBG_GetBgY_AngleS_FromWpos(NULL, effect->position, 0.0f);

    if (effect->arg0 == 0) {
        effect->offset.y += 10.0f;
    } else if (effect->arg0 == 1) {
        effect->offset.y += 15.0f;
    }

    effect->velocity.x += effect->acceleration.x * dt;
    effect->velocity.y += effect->acceleration.y * dt;
    effect->velocity.z += effect->acceleration.z * dt;
    effect->position.x += effect->velocity.x * dt;
    effect->position.y += effect->velocity.y * dt;
    effect->position.z += effect->velocity.z * dt;

    effect->effect_specific[0] += F32_TO_S16(effect->effect_specific[1] * dt);
    effect->effect_specific[2] += F32_TO_S16(effect->effect_specific[3] * dt);

    if (effect->lifetime <= (f32)((35 + GETREG(TAKREG, 60)) * 2 - 5)) {
        if (effect->position.y < effect->offset.y && mCoBG_CheckWaterAttribute(ut_attr)) {
            xyz_t_mult_v(&effect->velocity, 0.8f);
            add_calc_short_angle2(&effect->effect_specific[1], 0, 1.0f - sqrtf(0.9f), 182, 9);
            add_calc_short_angle2(&effect->effect_specific[3], 0, 1.0f - sqrtf(0.9f), 182, 9);
        }

        if (effect->position.y < effect->offset.y && effect->offset.x >= effect->offset.y &&
            effect->velocity.y < 0.0f) {
            if (mCoBG_CheckWaterAttribute(ut_attr)) {
                if (effect->arg0 < 2) {
                    eEC_CLIP->effect_make_proc(eEC_EFFECT_AMI_MIZU, effect->position, effect->prio, 0, game,
                                               effect->item_name, 0, 0);
                    eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_HAMON, effect->position, effect->prio, 0, game,
                                               effect->item_name, 0, 0);
                }
            } else {
                f32 bounce = DTCONV_GAME(0.6f, game);

                effect->position.y = effect->offset.y;
                effect->velocity.x *= bounce;
                effect->velocity.y *= -bounce;
                effect->velocity.z *= bounce;

                effect->effect_specific[1] >>= 1;
                effect->effect_specific[3] >>= 1;
            }
        }

        if (effect->position.y < effect->offset.y && effect->position.y >= effect->offset.z) {
            effect->position.x -= effect->velocity.x;
            effect->position.y -= effect->velocity.y;
            effect->position.z -= effect->velocity.z;

            effect->velocity.x *= -0.6f;
            effect->velocity.z *= -0.6f;
        }
    }
}

extern Gfx ef_axe1_model[];
extern Gfx ef_axe2_model[];
extern Gfx ef_axe3_model[];

static void eBreak_Axe_dw(eEC_Effect_c* effect, GAME* game) {
    u8 a = (int)eEL_CalcAdjust_F(effect->lifetime, 0.0f, (f32)((15 + GETREG(TAKREG, 61)) * 2), 0.0f, 255.0f);

    _texture_z_light_fog_prim_xlu(game->graph);

    OPEN_DISP(game->graph);

    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
    Matrix_RotateY(effect->effect_specific[4] + (int)(GETREG(TAKREG, 21) * 182.04445f), MTX_MULT);
    Matrix_rotateXYZ(effect->effect_specific[0] + (int)(GETREG(TAKREG, 20) * 182.04445f), 0,
                     effect->effect_specific[2] + (int)(GETREG(TAKREG, 22) * 182.04445f), MTX_MULT);
    Matrix_scale(effect->scale.x, effect->scale.y, effect->scale.z, MTX_MULT);

    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 128, 255, 255, 255, a);
    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    if (effect->arg0 == 0) {
        gSPDisplayList(NEXT_POLY_XLU_DISP, ef_axe1_model);
    } else if (effect->arg0 == 1) {
        gSPDisplayList(NEXT_POLY_XLU_DISP, ef_axe2_model);
    } else {
        gSPDisplayList(NEXT_POLY_XLU_DISP, ef_axe3_model);
    }

    CLOSE_DISP(game->graph);
}
