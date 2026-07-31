#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"

extern Gfx ef_siawase01_01_modelT[];

static void eSSHNC_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eSSHNC_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eSSHNC_mv(eEC_Effect_c* effect, GAME* game);
static void eSSHNC_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_siawase_hana_ch = {
    // clang-format off
    &eSSHNC_init,
    &eSSHNC_ct,
    &eSSHNC_mv,
    &eSSHNC_dw,
    eEC_IMMEDIATE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static u8 eSSHNC_pink_prim[] = { 255, 255, 255, 255 };
static u8 eSSHNC_pink_env[] = { 255, 0, 255, 255 };
static u8 eSSHNC_yellow_prim[] = { 255, 255, 0, 255 };
static u8 eSSHNC_yellow_env[] = { 255, 0, 0, 255 };
static u8* eSSHNC_color_info[] = { eSSHNC_pink_prim, eSSHNC_pink_env, eSSHNC_yellow_prim, eSSHNC_yellow_env };

static void eSSHNC_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_SIAWASE_HANA_CH, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void eSSHNC_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    int i;
    int rand = RANDOM(10.0f);

    effect->timer = 92;

    eEC_CLIP->random_first_speed_proc(&effect->velocity, 0.4f, 180.0f, 0.0f);

    effect->acceleration.x = 0.0f;
    effect->acceleration.y = 0.01f;
    effect->acceleration.z = 0.0f;

    effect->scale.x = 0.0f;
    effect->scale.y = 0.0f;
    effect->scale.z = 0.0f;

    effect->effect_specific[0] = rand & 1;
    effect->effect_specific[1] = 0;
    if (effect->velocity.x > 0.0f) {
        effect->effect_specific[2] = DEG2SHORT_ANGLE2(6.96f);
    } else {
        effect->effect_specific[2] = DEG2SHORT_ANGLE2(-6.96f);
    }

    if (effect->arg0 != 0) {
        i = effect->arg0;

        effect->timer -= effect->arg0 << 1;

        while (i-- != 0) {
            xyz_t_add(&effect->velocity, &effect->acceleration, &effect->velocity);
            xyz_t_add(&effect->position, &effect->velocity, &effect->position);
        };
    }
}

static void eSSHNC_mv(eEC_Effect_c* effect, GAME* game) {
    f32 dt = (f32)game->graph->dt_num_60fps_frames;
    f32 scale;
    f32 t = 92.0f - effect->lifetime;

    if (t >= 58.0f) {
        effect->acceleration.y = 0.01f;
    } else {
        effect->acceleration.y = eEL_CalcAdjust_F(t, 40.0f, 58.0f, 0.0f, 0.01f);
    }

    effect->velocity.x += effect->acceleration.x * dt;
    effect->velocity.y += effect->acceleration.y * dt;
    effect->velocity.z += effect->acceleration.z * dt;
    effect->position.x += effect->velocity.x * dt;
    effect->position.y += effect->velocity.y * dt;
    effect->position.z += effect->velocity.z * dt;

    effect->effect_specific[1] += F32_TO_S16(effect->effect_specific[2] * dt);

    scale = eEL_CalcAdjust_F(t, 40.0f, 58.0f, 0.0f, 0.005f);
    effect->scale.x = scale;
    effect->scale.y = scale;
    effect->scale.z = scale;
}

static void eSSHNC_dw(eEC_Effect_c* effect, GAME* game) {
    GRAPH* graph;
    u8 prim_a;
    f32 t = 92.0f - effect->lifetime;
    u8* prim = eSSHNC_color_info[2 * effect->effect_specific[0]];
    u8* env = eSSHNC_color_info[2 * effect->effect_specific[0] + 1];

    if (t >= 66.0f) {
        prim_a = (int)eEL_CalcAdjust_F(t, 66.0f, 92.0f, 255.0f, 0.0f);
    } else {
        prim_a = 255;
    }

    graph = game->graph;
    OPEN_DISP(graph);

    _texture_z_light_fog_prim_xlu(graph);

    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
    Matrix_mult(&((GAME_PLAY*)game)->billboard_matrix, MTX_MULT);
    Matrix_scale(effect->scale.x, effect->scale.y, effect->scale.z, MTX_MULT);
    Matrix_RotateZ(effect->effect_specific[1], MTX_MULT);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, prim[0], prim[1], prim[2], prim_a);
    gDPSetEnvColor(NEXT_POLY_XLU_DISP, env[0], env[1], env[2], env[3]);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_siawase01_01_modelT);

    CLOSE_DISP(graph);
}
