#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"

extern Gfx ef_onpu01_00_modelT[];
extern Gfx ef_onpu01_01_modelT[];
extern Gfx ef_onpu01_02_modelT[];

static Gfx* eKONP_model_table[] = {
    ef_onpu01_00_modelT,
    ef_onpu01_01_modelT,
    ef_onpu01_02_modelT,
};

static void eKONP_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eKONP_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eKONP_mv(eEC_Effect_c* effect, GAME* game);
static void eKONP_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_konpu = {
    // clang-format off
    &eKONP_init,
    &eKONP_ct,
    &eKONP_mv,
    &eKONP_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

typedef struct {
    s16 angle;
} eKONP_dt_c;

static void eKONP_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eKONP_dt_c data;

    data.angle = angle;
    eEC_CLIP->make_effect_proc(eEC_EFFECT_KONPU, pos, NULL, game, &data, item_name, prio, arg0, arg1);
}

static void eKONP_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    static xyz_t default_start_offset = { 0.0f, 6.0f, 13.0f };
    eKONP_dt_c* data = (eKONP_dt_c*)ct_arg;
    xyz_t start_ofs = default_start_offset;
    f32 speed;

    effect->timer = 72;
    effect->effect_specific[0] = RANDOM(3);
    effect->effect_specific[1] = data->angle;
    effect->effect_specific[2] = 0;
    effect->effect_specific[3] = RANDOM(5);
    effect->effect_specific[4] = RAD2SHORT_ANGLE2(DEG2RAD(RANDOM_F(60.0f) - 30.0f));

    if (effect->arg0 == 0) {
        eEC_CLIP->random_first_speed_proc(&effect->velocity, 0.435f, 30.0f, 30.0f);
        effect->acceleration.x = 0.0f;
        effect->acceleration.y = 0.006f;
        effect->acceleration.z = 0.0f;
    } else {
        s16 angle_x = DEG2SHORT_ANGLE2(RANDOM2_F(30.0f));
        s16 angle_z = DEG2SHORT_ANGLE2(RANDOM2_F(30.0f));

        if (effect->arg0 == 1) {
            speed = (RANDOM_F(4.0f) + 8.0f) * 0.5f;
        } else {
            speed = (RANDOM_F(2.0f) + 8.0f) * 0.5f;
        }

        effect->velocity.x = speed * sin_s(angle_z);
        effect->velocity.y = speed * cos_s(angle_z) * cos_s(angle_x);
        effect->velocity.z = speed * cos_s(angle_z) * sin_s(angle_x);
        effect->acceleration = ZeroVec;
    }

    if (effect->arg0 == 1) {
        sMath_RotateX(&effect->velocity, DEG2RAD(25.0f));
        sMath_RotateY(&effect->velocity, SHORT2RAD_ANGLE2(effect->effect_specific[1]));
    } else {
        sAdo_OngenTrgStart(NA_SE_43F, &effect->position);
    }

    sMath_RotateY(&start_ofs, SHORT2RAD_ANGLE2(effect->effect_specific[1]));
    if (effect->arg0 == 0) {
        effect->position.x += start_ofs.x;
        effect->position.y += start_ofs.y;
        effect->position.z += start_ofs.z;
    }

    effect->scale.x = 0.00156f;
    effect->scale.y = 0.00156f;
    effect->scale.z = 0.00156f;
}

static void eKONP_mv(eEC_Effect_c* effect, GAME* game) {
    f32 dt = (f32)game->graph->dt_num_60fps_frames;
    effect->effect_specific[2] += F32_TO_S16((DEG2SHORT_ANGLE2(11.25f) - 1) * dt);
    effect->velocity.x += effect->acceleration.x * dt;
    effect->velocity.y += effect->acceleration.y * dt;
    effect->velocity.z += effect->acceleration.z * dt;
    effect->position.x += effect->velocity.x * dt;
    effect->position.y += effect->velocity.y * dt;
    effect->position.z += effect->velocity.z * dt;

    if (effect->arg0 != 0) {
        f32 decay = powf(sqrtf(0.8f), dt);
        effect->velocity.x *= decay;
        effect->velocity.y *= decay;
        effect->velocity.z *= decay;
    }
}

// @ 8057c438
static rgba_t eKONP_prim_color_data[5] = {
    {0xFF, 0xFF, 0x00, 0xFF},
    {0xFF, 0x96, 0xFF, 0xFF},
    {0x00, 0xFF, 0x00, 0xFF},
    {0x64, 0x78, 0xFF, 0xFF},
    {0xFF, 0x64, 0x32, 0xFF},
};

// @ 8057c44c
static rgba_t eKONP_env_color_data[5] = {
    {0x64, 0x32, 0x00, 0xFF},
    {0x96, 0x00, 0x96, 0xFF},
    {0x00, 0x46, 0x00, 0xFF},
    {0x00, 0x00, 0xC8, 0xFF},
    {0x96, 0x00, 0x00, 0xFF},
};

static void eKONP_dw(eEC_Effect_c* effect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    s16 idx = effect->effect_specific[0];
    f32 t = 72.0f - effect->lifetime;
    s16 angle = effect->effect_specific[2];
    s16 color_idx = effect->effect_specific[3];
    f32 sin_x = sin_s(angle);
    f32 sin_y = sin_s(DIFF_SHORT_ANGLE(angle, DEG2SHORT_ANGLE2(-180.0f)));
    f32 scale = eEL_CalcAdjust_F(t, 0.0f, 18.0f, 0.00156f, 0.0078f);
    f32 max_stretch = eEL_CalcAdjust_F(t, 0.0f, 30.0f, 1.3499999f, 0.85f);
    f32 min_stretch = eEL_CalcAdjust_F(t, 0.0f, 30.0f, 0.050000012f, 0.54999995f);
    u8 a = (int)eEL_CalcAdjust_F(t, 60.0f, 72.0f, 255.0f, 0.0f);

    effect->scale.x = scale * (min_stretch + ((sin_x + 1.0f) * 0.5f * (max_stretch - min_stretch)));
    effect->scale.y = scale * (min_stretch + ((sin_y + 1.0f) * 0.5f * (max_stretch - min_stretch)));
    effect->scale.z = scale;

    OPEN_DISP(game->graph);

    _texture_z_light_fog_prim_xlu(game->graph);
    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
    Matrix_mult(&play->billboard_matrix, MTX_MULT);
    Matrix_RotateZ(effect->effect_specific[4], MTX_MULT);
    Matrix_scale(effect->scale.x, effect->scale.y, effect->scale.z, MTX_MULT);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, eKONP_prim_color_data[color_idx].r, eKONP_prim_color_data[color_idx].g, eKONP_prim_color_data[color_idx].b, a);
    gDPSetEnvColor(NEXT_POLY_XLU_DISP, eKONP_env_color_data[color_idx].r, eKONP_env_color_data[color_idx].g, eKONP_env_color_data[color_idx].b, 255);
    gSPDisplayList(NEXT_POLY_XLU_DISP, eKONP_model_table[idx]);

    CLOSE_DISP(game->graph);
}
