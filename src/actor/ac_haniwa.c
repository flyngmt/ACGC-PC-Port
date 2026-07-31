#include "ac_haniwa.h"

#include "m_play.h"
#include "m_bgm.h"
#include "m_rcp.h"
#include "m_name_table.h"
#include "m_house.h"
#include "m_font.h"
#include "m_msg.h"
#include "m_choice.h"
#include "m_demo.h"
#include "m_player.h"
#include "m_player_lib.h"
#include "m_clip.h"
#include "m_event.h"
#include "ac_intro_demo.h"
#include "ac_my_house.h"
#include "m_needlework_ovl.h"
#include "m_npc.h"
#include "m_submenu.h"
#include "m_field_info.h"
#include "m_common_data.h"

extern cKF_Skeleton_R_c cKF_bs_r_hnw;
extern cKF_Animation_R_c cKF_ba_r_hnw_move;
extern u8 hnw_tmem_txt[];
extern u16 hnw_face[];

static void aHNW_actor_ct(ACTOR* actor, GAME* game);
static void aHNW_actor_dt(ACTOR* actor, GAME* game);
static void aHNW_actor_init(ACTOR* actor, GAME* game);
static void aHNW_actor_draw(ACTOR* actor, GAME* game);

// clang-format off
ACTOR_PROFILE Haniwa_Profile = {
    mAc_PROFILE_HANIWA,
    ACTOR_PART_BG,
    ACTOR_STATE_NONE,
    ACTOR_PROP_HANIWA0,
    ACTOR_OBJ_BANK_12,
    sizeof(HANIWA_ACTOR),
    &aHNW_actor_ct,
    &aHNW_actor_dt,
    &aHNW_actor_init,
    mActor_NONE_PROC1,
    NULL,
};
// clang-format on

static ClObjPipeData_c AcHaniwaCoInfoData = { { 57, 32, ClObj_TYPE_PIPE }, { 1 }, { 20, 30, 0, { 0, 0, 0 } } };

static StatusData_c AcHaniwaStatusData = { 0, 20, 30, 0, MASSTYPE_HEAVY };

/* TODO: ct, dt, & draw are in their own TU */
static void aHNW_actor_ct(ACTOR* actor, GAME* game) {
    HANIWA_ACTOR* haniwa = (HANIWA_ACTOR*)actor;
    cKF_SkeletonInfo_R_c* keyframe = &haniwa->common_actor_class.anime.keyframe;

    cKF_SkeletonInfo_R_ct(keyframe, &cKF_bs_r_hnw, NULL, haniwa->keyframe_work_area, haniwa->keyframe_morph_area);
    {
        ClObjPipe_c* pipe = &haniwa->common_actor_class.col_pipe;
        ClObjPipe_ct(game, pipe);
        ClObjPipe_set5(game, pipe, actor, &AcHaniwaCoInfoData);
        CollisionCheck_Status_set3(&haniwa->common_actor_class.actor_class.status_data, &AcHaniwaStatusData);
    }

    haniwa->bank_ram_start = ((GAME_PLAY*)game)->object_exchange.banks[actor->data_bank_id].ram_start;
    haniwa->common_actor_class.anime.anime_no = 2;
    haniwa->house_idx = actor->npc_id - ACTOR_PROP_HANIWA0;
    actor->talk_distance = 43.0f;
}

static void aHNW_actor_dt(ACTOR* actor, GAME* game) {
    HANIWA_ACTOR* haniwa = (HANIWA_ACTOR*)actor;

    if (haniwa->playing_save_bgm) {
        mBGMPsComp_delete_ps_demo(BGM_ENTER_HOUSE, 0x168);
    }

    cKF_SkeletonInfo_R_dt(&haniwa->common_actor_class.anime.keyframe);
    ClObjPipe_dt(game, &haniwa->common_actor_class.col_pipe);
}

#include "../src/actor/ac_haniwa_move.c_inc"

static void aHNW_actor_draw(ACTOR* actor, GAME* game) {
    static Gfx hnw_tex_model[] = {
        gsDPLoadTLUT_Dolphin(15, 16, 1, hnw_face),
        gsSPEndDisplayList(),
    };

    HANIWA_ACTOR* haniwa = (HANIWA_ACTOR*)actor;
    cKF_SkeletonInfo_R_c* keyframe = &haniwa->common_actor_class.anime.keyframe;
    GRAPH* g = game->graph;
    N64Mtx* m = GRAPH_ALLOC_TYPE(g, N64Mtx, keyframe->skeleton->num_shown_joints);

    if (m != NULL) {
        int house_idx = haniwa->house_idx;

        _texture_z_light_fog_prim(g);

        OPEN_POLY_OPA_DISP(g);

        gSPSegment(POLY_OPA_DISP++, ANIME_4_TXT_SEG, hnw_tmem_txt);

        if (mPr_NullCheckPersonalID(&Save_Get(homes[house_idx]).ownerID) != TRUE &&
            Common_Get(player_no) == mHS_get_pl_no(house_idx)) {
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 128, 255, 255, 255, 255);
        } else {
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 128, 255, 255, 255, 255);
        }

        gSPDisplayList(POLY_OPA_DISP++, hnw_tex_model);

        CLOSE_POLY_OPA_DISP(g);

        cKF_Si3_draw_R_SV(game, keyframe, m, NULL, NULL, actor);
    }
}
