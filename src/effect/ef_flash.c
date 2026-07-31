#include "ef_effect_control.h"

#include "graph.h"
#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"

static void eFlash_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eFlash_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eFlash_mv(eEC_Effect_c* effect, GAME* game);
static void eFlash_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_flash = {
    // clang-format off
    &eFlash_init,
    &eFlash_ct,
    &eFlash_mv,
    &eFlash_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
    // clang-format on
};

static void eFlash_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    (*eEC_CLIP->make_effect_proc)(eEC_EFFECT_FLASH, pos, NULL, game, NULL, item_name, prio, arg0, angle);
}

static void eFlash_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    s16 flash_length = 3.0f + RANDOM_F(7.0f);
    s16 end_frame = flash_length >> 1;

    if (effect->arg0 == 1) {
        static rgba_t light_color = { 27, 27, 27, 255 };

        (*eEC_CLIP->regist_effect_light)(light_color, flash_length, end_frame, TRUE);
    }

    effect->timer = 5;
    effect->acceleration.x = 0.3f + RANDOM_F(0.7f);
}

static void eFlash_mv(eEC_Effect_c* effect, GAME* game) {
    f32 t = 5.0f - effect->lifetime;
    f32 scale;

    if (t <= 4.0f) {
        scale = eEL_CalcAdjust_F(t, 0.0f, 2.0f, effect->acceleration.x * 0.005f, 0.01f);
    } else {
        scale = eEL_CalcAdjust_F(t, 3.0f, 4.0f, effect->acceleration.x * 0.01f, 0.0f);
    }

    effect->scale.x = scale;
    effect->scale.y = scale;
    effect->scale.z = scale;
}

extern Gfx ef_takurami01_normal_render_mode[];
extern Gfx ef_takurami01_kira_modelT[];

static void eFlash_dw(eEC_Effect_c* effect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
    Matrix_mult(&play->billboard_matrix, MTX_MULT);
    Matrix_scale(effect->scale.x, effect->scale.y, effect->scale.z, MTX_MULT);
    _texture_z_light_fog_prim_xlu(game->graph);

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 255, 255, 255, 200);
    gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_8, ef_takurami01_normal_render_mode);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_takurami01_kira_modelT);

    CLOSE_DISP(game->graph);
}

static void eFlashC_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eFlashC_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eFlashC_mv(eEC_Effect_c* effect, GAME* game);
static void eFlashC_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_flashC = {
    // clang-format off
    &eFlashC_init,
    &eFlashC_ct,
    &eFlashC_mv,
    &eFlashC_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
    // clang-format on
};

static void eFlashC_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    (*eEC_CLIP->make_effect_proc)(eEC_EFFECT_FLASHC, pos, NULL, game, NULL, item_name, prio, arg0, angle);
}

static void eFlashC_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 240;
    effect->effect_specific[0] = 0;
    effect->effect_specific[1] = 0;
}

static void eFlashC_mv(eEC_Effect_c* effect, GAME* game) {
    effect->effect_specific[1] += F32_TO_S16((f32)game->graph->dt_num_60fps_frames * 100.0f);
    if (effect->effect_specific[1] >= 800) {
        effect->effect_specific[1] -= 800;
        int size;

        switch (Save_Get(scene_no)) {
            case SCENE_MY_ROOM_S:
                size = 4;
                break;
            case SCENE_NPC_HOUSE:
            case SCENE_MY_ROOM_M:
            case SCENE_MY_ROOM_LL2:
            case SCENE_COTTAGE_NPC:
                size = 6;
                break;
            case SCENE_MY_ROOM_L:
            case SCENE_MY_ROOM_LL1:
            case SCENE_MY_ROOM_BASEMENT_S:
            case SCENE_MY_ROOM_BASEMENT_M:
            case SCENE_MY_ROOM_BASEMENT_L:
            case SCENE_MY_ROOM_BASEMENT_LL1:
            case SCENE_COTTAGE_MY:
                size = 8;
                break;
            default:
                size = -1;
                break;
        }

        if (size != -1) {
            xyz_t pos;

            pos.z = 43.0f;
            pos.x = 40.0f + RANDOM_F(size) * 40.0f;
            pos.y = -10.0f + RANDOM_F(20.0f) + 75.0f;

            (*eEC_CLIP->effect_make_proc)(eEC_EFFECT_FLASH, pos, effect->prio, 0, game, (u16)effect->item_name,
                                          effect->effect_specific[0] & 1, 0);
            effect->effect_specific[0]++;
        }
    }
}

static void eFlashC_dw(eEC_Effect_c* effect, GAME* game) {
    // nothing
}
