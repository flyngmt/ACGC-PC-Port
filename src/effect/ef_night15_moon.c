#include "ef_effect_control.h"

#include "m_common_data.h"
#include "sys_matrix.h"
#include "m_rcp.h"

static void eNight15Moon_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eNight15Moon_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eNight15Moon_mv(eEC_Effect_c* effect, GAME* game);
static void eNight15Moon_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_night15_moon = {
    // clang-format off
    &eNight15Moon_init,
    &eNight15Moon_ct,
    &eNight15Moon_mv,
    &eNight15Moon_dw,
    60,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
    // clang-format on
};

static int eNight15Moon_GetPoolBlockCenter(xyz_t* center_pos) {
    xyz_t base = { 0.0f, 0.0f, 0.0f };
    int bx = 0;
    int bz = 0;

    *center_pos = base;

    if (mFI_BlockKind2BkNum(&bx, &bz, mRF_BLOCKKIND_POOL) && mFI_BkNum2WposXZ(&base.x, &base.z, bx, bz)) {
        center_pos->x = base.x + mFI_BK_WORLDSIZE_HALF_X_F;
        center_pos->z = base.z + mFI_BK_WORLDSIZE_HALF_Z_F;
        center_pos->y = mFI_BkNum2BaseHeight(bx, bz) + 19.0f;
        return TRUE;
    }

    return FALSE;
}

static xyz_t eNight15Moon_GetNowMoonPos(xyz_t center_pos) {
    f32 right_x = center_pos.x + 100.0f;
    lbRTC_time_c rtc_time = Common_Get(time.rtc_time);
    xyz_t pos;

    if (rtc_time.hour >= 18 && rtc_time.hour < 21) {
        f32 sec = (rtc_time.min * 60.0f + rtc_time.sec) * (1.0f / 54.0f);

        pos.x = right_x - (rtc_time.hour - 18) * 66.666666f;
        pos.x -= sec;
    } else if (rtc_time.hour < 18) {
        pos.x = right_x;
    } else {
        pos.x = center_pos.x - 100.0f;
    }

    pos.z = center_pos.z;
    pos.y = center_pos.y;
    return pos;
}

static void eNight15Moon_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_NIGHT15_MOON, pos, NULL, game, NULL, item_name, prio, 0, 0);
}

static void eNight15Moon_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    xyz_t pos = { 0.0f, 0.0f, 0.0f };

    effect->effect_specific[3] = 0;
    effect->effect_specific[0] = 0;
    effect->effect_specific[1] = 0;
    effect->effect_specific[2] = 0;
    effect->offset.x = 0.0f;
    effect->offset.y = 0.0f;
    effect->offset.z = 0.0f;

    if (eNight15Moon_GetPoolBlockCenter(&pos)) {
        effect->timer = 20000;
        effect->effect_specific[3] = 1;
    } else {
        effect->timer = 0;
    }

    effect->acceleration = pos;
    effect->position = eNight15Moon_GetNowMoonPos(effect->acceleration);
}

static void eNight15Moon_mv(eEC_Effect_c* effect, GAME* game) {
    f32 dt = (f32)game->graph->dt_num_60fps_frames;
    f32 sin = sin_s(effect->effect_specific[2]);

    if (effect->effect_specific[3] == 0 && effect->timer == 0) {
        xyz_t pos;

        if (eNight15Moon_GetPoolBlockCenter(&pos)) {
            effect->effect_specific[3] = 1;
            effect->acceleration = pos;
        }
    }

    effect->effect_specific[0] += F32_TO_S16(150 * dt);
    effect->effect_specific[1] -= F32_TO_S16(100 * dt);
    effect->effect_specific[2] += F32_TO_S16(256 * dt);

    eEC_CLIP->set_continious_env_proc(effect, 20000, 20000);
    effect->position = eNight15Moon_GetNowMoonPos(effect->acceleration);
    effect->offset.x = 1.5f * sin;
    effect->offset.z = -1.5f * sin;
}

extern EVW_ANIME_DATA ef_moon01_00_evw_anime;
extern Gfx ef_moon01_00_modelT[];

static void eNight15Moon_dw(eEC_Effect_c* effect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    
    if (eEC_CLIP->check_lookat_block_proc(effect->position) || effect->state == eEC_STATE_FINISHED) {
        s16 angle0 = effect->effect_specific[0];
        s16 angle1 = effect->effect_specific[1];

        OPEN_DISP(game->graph);

        _texture_z_light_fog_prim_xlu(game->graph);
        Matrix_translate(effect->position.x + effect->offset.x, effect->position.y + effect->offset.y, effect->position.z + effect->offset.z, MTX_LOAD);
        Matrix_RotateY(-angle0, MTX_MULT);
        Matrix_scale(1.075f, 1.0f, 1.0f, MTX_MULT);
        Matrix_RotateY(angle0, MTX_MULT);
        Matrix_RotateY(-angle1, MTX_MULT);
        Matrix_scale(1.0f, 1.0f, 1.075f, MTX_MULT);
        Matrix_RotateY(angle1, MTX_MULT);
        Matrix_scale(0.049f, 1.0f, 0.049f, MTX_MULT);

        gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 40, 255, 255, 100, 170);
        Evw_Anime_Set(play, &ef_moon01_00_evw_anime);
        gSPDisplayList(NEXT_POLY_XLU_DISP, ef_moon01_00_modelT);

        CLOSE_DISP(game->graph);
    }
}
