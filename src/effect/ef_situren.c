#include "audio.h"
#include "ef_effect_control.h"

#include "graph.h"
#include "libu64/u64types.h"
#include "m_common_data.h"
#include "m_lib.h"
#include "m_rcp.h"
#include "sys_math3d.h"
#include "sys_matrix.h"

extern Gfx ef_situren01_00_modelT[];
extern Gfx ef_situren01_01_modelT[];
extern Gfx ef_situren01_02_modelT[];

static void eSN_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eSN_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eSN_mv(eEC_Effect_c* effect, GAME* game);
static void eSN_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_situren = {
    // clang-format off
    &eSN_init,
    &eSN_ct,
    &eSN_mv,
    &eSN_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eSN_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    xyz_t vec = { 0.0f, 10.0f, 7.0f };

    sMath_RotateY(&vec, SHORT2RAD_ANGLE2(angle));
    pos.x += vec.x;
    pos.y += vec.y;
    pos.z += vec.z;

    eEC_CLIP->make_effect_proc(eEC_EFFECT_SITUREN, pos, NULL, game, NULL, item_name, prio, 0, 0);
}

static void eSN_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 128;

    effect->scale = ZeroVec;
    effect->offset = ZeroVec;

    effect->effect_specific[0] = 0;

    sAdo_OngenTrgStart(0x13d, &effect->position);
}

static void eSN_mv(eEC_Effect_c* effect, GAME* game) {
    f32 dt = (f32)game->graph->dt_num_60fps_frames;
    f32 t = 128.0f - effect->lifetime;

    effect->effect_specific[0] += F32_TO_S16(DEG2SHORT_ANGLE2(30.94f) * dt);

    if (t < 8.0f) {
        effect->position.y += 1.6f * dt;
    }
}

static void eSN_dw(eEC_Effect_c* effect, GAME* game) {
    Gfx* gfx;
    s16 angle;
    f32 t = 128.0f - effect->lifetime;
    f32 s, c, temp1, temp2, temp3;
    u8 alpha;

    angle = effect->effect_specific[0];

    s = sin_s(angle);
    c = cos_s(angle);

    temp1 = eEL_CalcAdjust_F(t, 0.0f, 6.0f, 0.0f, 0.0075f);
    temp2 = eEL_CalcAdjust_F(t, 0.0f, 42.0f, 1.4f, 1.0f);
    temp3 = eEL_CalcAdjust_F(t, 0.0f, 42.0f, 0.6f, 1.0f);
    alpha = (int)eEL_CalcAdjust_F(t, 108.0f, 128.0f, 255.0f, 0.0f);

    effect->scale.x = temp1 * (temp3 + ((s + 1.0f) * 0.5f * (temp2 - temp3)));
    effect->scale.y = temp1 * (temp3 + ((c + 1.0f) * 0.5f * (temp2 - temp3)));
    effect->scale.z = 0.0075f;

    /* Original swapped to model_01 for exactly 1 frame when timer == 60
     * (i.e. at t == 68). Preserve that 1-frame slice as a [68,69) window. */
    if (t < 68.0f) {
        gfx = ef_situren01_02_modelT;
    } else if (t < 69.0f) {
        gfx = ef_situren01_01_modelT;
    } else {
        gfx = ef_situren01_00_modelT;
    }

    OPEN_DISP(game->graph);

    _texture_z_light_fog_prim_xlu(game->graph);

    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
    Matrix_mult(&((GAME_PLAY*)game)->billboard_matrix, MTX_MULT);
    Matrix_translate(effect->offset.x, effect->offset.y, effect->offset.z, MTX_MULT);
    Matrix_scale(effect->scale.x, effect->scale.y, effect->scale.z, MTX_MULT);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 255, 200, 255, alpha);
    gSPDisplayList(NEXT_POLY_XLU_DISP, gfx);

    CLOSE_DISP(game->graph);
}
