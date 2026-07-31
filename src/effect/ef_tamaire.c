#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_lib.h"
#include "m_rcp.h"
#include "sys_matrix.h"

extern Gfx ef_tamaire_shadow_modelT[];

extern Gfx ef_tamaire01_r_modelT[];
extern Gfx ef_tamaire01_w_modelT[];
static Gfx* tamaire_model[] = { ef_tamaire01_r_modelT, ef_tamaire01_w_modelT };

static void eTamaire_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eTamaire_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eTamaire_mv(eEC_Effect_c* effect, GAME* game);
static void eTamaire_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_tamaire = {
    // clang-format off
    &eTamaire_init,
    &eTamaire_ct,
    &eTamaire_mv,
    &eTamaire_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eTamaire_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_TAMAIRE, pos, NULL, game, &angle, item_name, prio, arg0, arg1);
}

static void eTamaire_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    s16 angle = *(s16*)ct_arg;

    effect->timer = 200;
    effect->scale.x = effect->scale.y = effect->scale.z = 0.005f;

    effect->velocity.x = cos_s(effect->arg1) * sin_s(angle);
    effect->velocity.y = sin_s(effect->arg1);
    effect->velocity.z = cos_s(effect->arg1) * cos_s(angle);

    xyz_t_mult_v(&effect->velocity, RANDOM_F(1.5f) + 4.9f);

    effect->acceleration = ZeroVec;
    effect->acceleration.y = -0.15f;

    effect->offset.y = effect->offset.z = mCoBG_GetBgY_AngleS_FromWpos(NULL, effect->position, 0.0f) + 3.0f;
    effect->offset.x = effect->position.y;

    effect->effect_specific[0] = qrand();
    effect->effect_specific[1] = DEG2SHORT_ANGLE(RANDOM2_F(7.5f) + 2.5f);
    effect->effect_specific[2] = 0;

    if (effect->arg0 != 0) {
        effect->arg0 = 1;
    }
    sAdo_OngenTrgStart(0x152, &effect->position);
}

static void eTamaire_mv(eEC_Effect_c* effect, GAME* game) {
    f32 dt = (f32)game->graph->dt_num_60fps_frames;
    mActor_name_t* item_p;
    xyz_t pos;

    effect->velocity.x += effect->acceleration.x * dt;
    effect->velocity.y += effect->acceleration.y * dt;
    effect->velocity.z += effect->acceleration.z * dt;
    effect->position.x += effect->velocity.x * dt;
    effect->position.y += effect->velocity.y * dt;
    effect->position.z += effect->velocity.z * dt;

    effect->offset.z = effect->offset.y;
    effect->offset.y = mCoBG_GetBgY_AngleS_FromWpos(NULL, effect->position, 0.0f) + 3.0f;

    if (effect->position.y < effect->offset.y) {
        if (effect->offset.y > effect->offset.z) {
            effect->position.x -= effect->velocity.x;
            effect->position.z -= effect->velocity.z;

            effect->velocity.x *= -RANDOM_F(0.8f);
            effect->velocity.y *= -0.5f;
            effect->velocity.z *= -RANDOM_F(0.8f);

            effect->offset.y = effect->offset.z;

            sAdo_OngenTrgStart(0x153, &effect->position);
        } else {
            item_p = mFI_GetUnitFG(effect->position);
            if ((item_p != NULL) && (*item_p == DUMMY_TURI)) {
                mFI_Wpos2UtCenterWpos(&pos, effect->position);

                pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(effect->position, 0.0f) + 60.0f;
                add_calc2(&effect->position.x, pos.x, CALC_EASE(0.5f), 1.0f);
                add_calc2(&effect->position.y, pos.y, CALC_EASE(0.5f), 0.5f);
                add_calc2(&effect->position.z, pos.z, CALC_EASE(0.5f), 1.0f);

                add_calc0(&effect->velocity.x, CALC_EASE(0.5f), 0.25f);
                add_calc0(&effect->velocity.y, CALC_EASE(0.5f), 0.25f);
                add_calc0(&effect->velocity.z, CALC_EASE(0.5f), 0.25f);

                effect->position.y = MAX(pos.y, effect->position.y);

                if ((effect->effect_specific[2] & 2) == 0) {
                    sAdo_OngenTrgStart(0x154, &effect->position);
                    effect->effect_specific[2] |= 2;
                }
                effect->effect_specific[2] |= 1;

                if (search_position_distance(&effect->position, &pos) < 1.0f) {
                    effect->timer = 0;
                    effect->lifetime = 0.0f;
                }
            } else {
                f32 bounce = DTCONV_GAME(0.5f, game);

                effect->position.y = effect->offset.y;

                effect->velocity.y *= -bounce;
                effect->velocity.x *= bounce;
                effect->velocity.z *= bounce;

                effect->effect_specific[1] >>= 1;

                if (effect->velocity.y > 2.0f) {
                    sAdo_OngenTrgStart(0x155, &effect->position);
                }
            }
        }
    }

    effect->effect_specific[0] += F32_TO_S16(effect->effect_specific[1] * dt);
    effect->scale.y = (ABS(effect->velocity.y) * 0.1f + 0.9f) * 0.005f;
}

static void eTamaire_dw(eEC_Effect_c* effect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    GRAPH* graph;
    f32 adjust, alpha, temp;
    u8 shadow_alpha;

    adjust = eEL_CalcAdjust_F(effect->lifetime, 0.0f, 20.0f, 0.0f, 1.0f);
    temp = ((effect->offset.y - effect->position.y + 300.0f) / 300.0f) * 0.5f;
    temp = (temp < 0.0f ? 0.0f : temp);
    temp = (temp > 0.5f ? 0.5f : temp) * play->kankyo.shadow_alpha;
    shadow_alpha = (int)(adjust * temp);
    alpha = adjust * 255.0f;

    graph = game->graph;
    OPEN_DISP(graph);

    _texture_z_light_fog_prim_xlu(graph);

    if ((effect->effect_specific[2] & 1) == 0) {
        Matrix_translate(effect->position.x, effect->offset.y - 3.0f, effect->position.z, MTX_LOAD);
        Matrix_scale(effect->scale.x, effect->scale.y, effect->scale.z, MTX_MULT);

        gDPSetPrimColor(NEXT_SHADOW_DISP, 0, 255, 0, 0, 0, shadow_alpha);
        gSPMatrix(NEXT_SHADOW_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(NEXT_SHADOW_DISP, ef_tamaire_shadow_modelT);
    }

    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
    Matrix_mult(&play->billboard_matrix, MTX_MULT);
    Matrix_scale(effect->scale.x, effect->scale.y, effect->scale.z, MTX_MULT);
    Matrix_RotateZ(effect->effect_specific[0], MTX_MULT);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 255, 255, 255, (u8)(int)alpha);
    gSPDisplayList(NEXT_POLY_XLU_DISP, tamaire_model[effect->arg0]);

    CLOSE_DISP(graph);
}
