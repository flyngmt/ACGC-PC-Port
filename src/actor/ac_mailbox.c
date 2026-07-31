#include "ac_mailbox.h"

#include "m_common_data.h"
#include "sys_matrix.h"
#include "m_rcp.h"
#include "m_house.h"
#include "m_player_lib.h"

enum {
    aMBX_ACT_WAIT,
    aMBX_ACT_PL_WAIT,
    aMBX_ACT_OPEN_AND_CLOSE,
    aMBX_ACT_PL_OPEN,
    aMBX_ACT_PL_CLOSE,

    aMBX_ACT_NUM
};

enum {
    aMBX_ANIME_WAIT,
    aMBX_ANIME_OPEN_AND_CLOSE,
    aMBX_ANIME_PL_OPEN,
    aMBX_ANIME_PL_CLOSE,
    aMBX_ANIME_FLAG_UP,
    aMBX_ANIME_FLAG_UP_WAIT,
    aMBX_ANIME_FLAG_DOWN,

    aMBX_ANIME_NUM
};

static void aMBX_actor_ct(ACTOR* actorx, GAME* game);
static void aMBX_actor_dt(ACTOR* actorx, GAME* game);
static void aMBX_actor_move(ACTOR* actorx, GAME* game);
static void aMBX_actor_init(ACTOR* actorx, GAME* game);
static void aMBX_actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE MailBox_Profile = {
    mAc_PROFILE_MAILBOX,
    ACTOR_PART_ITEM,
    ACTOR_STATE_NONE,
    ACTOR_PROP_MAILBOX0,
    ACTOR_OBJ_BANK_26,
    sizeof(MAILBOX_ACTOR),
    aMBX_actor_ct,
    aMBX_actor_dt,
    aMBX_actor_init,
    mActor_NONE_PROC1,
    NULL,
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_post;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_post;
extern cKF_Animation_R_c cKF_ba_r_obj_s_post_delivery1;
extern cKF_Animation_R_c cKF_ba_r_obj_s_post_flag_off1;
extern cKF_Animation_R_c cKF_ba_r_obj_s_post_flag_on1;
extern cKF_Animation_R_c cKF_ba_r_obj_s_post_flag_on_wait1;
extern cKF_Animation_R_c cKF_ba_r_obj_s_post_open1;
extern cKF_Animation_R_c cKF_ba_r_obj_s_post;

typedef struct {
    cKF_Animation_R_c* anim;
    f32 start;
    f32 end;
} aMBX_anime_info_c;

static aMBX_anime_info_c aMBX_animeTable[7] = {
    { &cKF_ba_r_obj_s_post, 1.0f, 2.0f },
    { &cKF_ba_r_obj_s_post_delivery1, 1.0f, 98.0f },
    { &cKF_ba_r_obj_s_post_open1, 1.0f, 31.0f },
    { &cKF_ba_r_obj_s_post_open1, 31.0f, 1.0f },
    { &cKF_ba_r_obj_s_post_flag_on1, 1.0f, 17.0f },
    { &cKF_ba_r_obj_s_post_flag_on_wait1, 1.0f, 31.0f },
    { &cKF_ba_r_obj_s_post_flag_off1, 1.0f, 17.0f },
};

static int aMBX_animeSeqNoTable[5] = {
    aMBX_ANIME_WAIT,
    aMBX_ANIME_WAIT,
    aMBX_ANIME_OPEN_AND_CLOSE,
    aMBX_ANIME_PL_OPEN,
    aMBX_ANIME_PL_CLOSE,
};

static cKF_Skeleton_R_c* aMBX_skeleton[2] = { &cKF_bs_r_obj_s_post, &cKF_bs_r_obj_w_post };

static void aMBX_check_flag(MAILBOX_ACTOR* actor);
static void aMBX_setupAction(MAILBOX_ACTOR* actor, int action);

static void aMBX_actor_ct(ACTOR* actorx, GAME* game) {
    static s16 angle_table[] = {
        DEG2SHORT_ANGLE(90.0f),
        DEG2SHORT_ANGLE(0.0f),
        DEG2SHORT_ANGLE(90.0f),
        DEG2SHORT_ANGLE(0.0f),
    };

    MAILBOX_ACTOR* actor = (MAILBOX_ACTOR*)actorx;
    int season = Common_Get(time.season) == mTM_SEASON_WINTER;
    int idx = actorx->npc_id - ACTOR_PROP_MAILBOX0;
    cKF_Skeleton_R_c* skeleton_p = aMBX_skeleton[season];

    cKF_SkeletonInfo_R_ct(&actor->kf0, skeleton_p, NULL, actor->joint0, actor->morph0);
    cKF_SkeletonInfo_R_ct(&actor->kf1, skeleton_p, NULL, actor->joint1, actor->morph1);
    actor->segp = ((GAME_PLAY*)game)->object_exchange.banks[actorx->data_bank_id].ram_start;
    actor->anim_idx0 = aMBX_ANIME_NUM;
    actor->arrange_idx = idx;
    actor->anim_idx1 = aMBX_ANIME_NUM;
    actorx->shape_info.rotation.y = angle_table[idx];
    aMBX_check_flag(actor);
    actor->kf0.frame_control.current_frame = actor->kf0.frame_control.end_frame;
}

static void aMBX_actor_dt(ACTOR* actorx, GAME* game) {
    MAILBOX_ACTOR* actor = (MAILBOX_ACTOR*)actorx;

    cKF_SkeletonInfo_R_dt(&actor->kf0); // @BUG - why not dt on the second skeleton??
}

#include "../src/actor/ac_mailbox_move.c_inc"

static Gfx post_flag_saki_common_DL[] = {
    gsSPTexture(65535, 65535, 0, 0, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

static Gfx post_flag_saki_model_type0[] = {
    gsSPDisplayList(post_flag_saki_common_DL),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_1_txt, G_IM_FMT_CI, 16, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsDPSetTileSize(0, 0, 0, 124, 124),
    gsSPEndDisplayList(),
};

static Gfx post_flag_saki_model_type1[] = {
    gsSPDisplayList(post_flag_saki_common_DL),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTextureBlock_4b_Dolphin(anime_2_txt, G_IM_FMT_CI, 16, 32, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPEndDisplayList(),
};

static int aMBX_actor_draw_before(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                                  u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    static Gfx* post_flag_saki_model[] = { post_flag_saki_model_type0, post_flag_saki_model_type1 };
    MAILBOX_ACTOR* actor = (MAILBOX_ACTOR*)arg;

    if (joint_idx == 3) {
        GRAPH* graph = game->graph;
        int idx = actor->anim_idx1 == aMBX_ANIME_FLAG_UP_WAIT;

        OPEN_POLY_OPA_DISP(graph);

        gSPDisplayList(POLY_OPA_DISP++, post_flag_saki_model[idx]);

        CLOSE_POLY_OPA_DISP(graph);
    }

    return TRUE;
}

extern u8 obj_s_post_flag2_TA_tex_txt[];
extern u8 obj_w_post_flag2_TA_tex_txt[];

extern EVW_ANIME_DATA obj_s_post_flag_on_wait1_evw_anime;
extern EVW_ANIME_DATA obj_w_post_flag_on_wait1_evw_anime;

static void aMBX_actor_draw(ACTOR* actorx, GAME* game) {
    static u8* tex_table[] = { obj_s_post_flag2_TA_tex_txt, obj_w_post_flag2_TA_tex_txt };
    static EVW_ANIME_DATA* evw_table[] = { &obj_s_post_flag_on_wait1_evw_anime, &obj_w_post_flag_on_wait1_evw_anime };
    MAILBOX_ACTOR* actor = (MAILBOX_ACTOR*)actorx;
    cKF_SkeletonInfo_R_c* kf0 = &actor->kf0;
    GRAPH* graph = game->graph;
    GAME_PLAY* play = (GAME_PLAY*)game;
    N64Mtx* mtx = GRAPH_ALLOC_TYPE(graph, N64Mtx, kf0->skeleton->num_shown_joints);

    if (mtx != NULL) {
        _texture_z_light_fog_prim(graph);

        if (actor->anim_idx1 == aMBX_ANIME_FLAG_UP_WAIT) {
            static f32 mbx_se_accum = 0.0f;
            Evw_Anime_Set(play, evw_table[Common_Get(time.season) == mTM_SEASON_WINTER]);
            if (Common_Get(player_no) == mHS_get_pl_no(actor->arrange_idx) &&
                graph_dt_period_elapsed(game, &mbx_se_accum, (f32)FRAMES_PER_SECOND)) {
                sAdo_OngenTrgStart(0x43B, &actorx->world.position);
            }
        } else {
            OPEN_POLY_OPA_DISP(graph);

            gSPSegment(POLY_OPA_DISP++, ANIME_1_TXT_SEG, tex_table[Common_Get(time.season) == mTM_SEASON_WINTER]);

            CLOSE_POLY_OPA_DISP(graph);
        }

        cKF_Si3_draw_R_SV(game, kf0, mtx, aMBX_actor_draw_before, NULL, actorx);
    }
}
