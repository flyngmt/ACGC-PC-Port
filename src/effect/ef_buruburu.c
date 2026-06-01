#include "ef_effect_control.h"
#include "m_common_data.h"

extern u8 ef_buruburu01_0_int_i4[];
extern u8 ef_buruburu01_1_int_i4[];

extern Gfx ef_buruburu01_00_modelT[];

static void eBR_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eBR_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eBR_mv(eEC_Effect_c* effect, GAME* game);
static void eBR_dw(eEC_Effect_c* effect, GAME* game);


eEC_PROFILE_c iam_ef_buruburu = {
    // clang-format off
    &eBR_init,
    &eBR_ct,
    &eBR_mv,
    &eBR_dw,
    eEC_IMMEDIATE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static f32 eBR_scale_x[] = { 0.015f, 0.016f };
static f32 eBR_scale_z[] = { 0.01f, 0.011f };

static u8* eBR_tex_anime_table[] = {
    ef_buruburu01_0_int_i4,ef_buruburu01_1_int_i4,
};

static void eBR_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    xyz_t offs;

    offs.x = 0.0f;
    offs.y = -10.0f;
    offs.z = 0.0f;
    eEC_CLIP->make_effect_proc(eEC_EFFECT_BURUBURU,pos,&offs,game,NULL,item_name,prio,0,0);
}

static void eBR_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->scale.x = 0.01f;
    effect->scale.y = 0.01f;    
    effect->scale.z = 0.01f;
    effect->timer = 8;
}


static void eBR_mv(eEC_Effect_c* effect, GAME* game) {
    eEC_CLIP->set_continious_env_proc(effect,8,8);
    sAdo_OngenPos((uintptr_t) effect, 0x2D, &effect->position);
}

static void eBR_dw(eEC_Effect_c* effect, GAME* game) {
    s16 idx = (effect->timer >> 1) & 1; 
    
    effect->scale.x = eBR_scale_x[idx];
    effect->scale.z = eBR_scale_z[idx];
    
    OPEN_DISP(game->graph);

    eEC_CLIP->auto_matrix_xlu_offset_proc(game, &effect->position, &effect->scale, &effect->offset);
    gSPSegment(NEXT_POLY_XLU_DISP,G_MWO_SEGMENT_8,eBR_tex_anime_table[idx]);
    gSPDisplayList(NEXT_POLY_XLU_DISP,ef_buruburu01_00_modelT); 

    CLOSE_DISP(game->graph);
}
