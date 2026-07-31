#include "ac_bridge_a.h"

#include "m_common_data.h"
#include "m_name_table.h"
#include "m_field_info.h"
#include "m_player_lib.h"
#include "m_rcp.h"
#include "m_debug.h"

static void aBridgeA_actor_ct(ACTOR* actorx, GAME* game);
static void aBridgeA_actor_dt(ACTOR* actorx, GAME* game);
static void aBridgeA_actor_init(ACTOR* actorx, GAME* game);
static void aBridgeA_actor_move(ACTOR* actorx, GAME* game);
static void aBridgeA_actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Bridge_A_Profile = {
    mAc_PROFILE_BRIDGE_A,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET,
    BRIDGE_A0,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(STRUCTURE_ACTOR),
    &aBridgeA_actor_ct,
    &aBridgeA_actor_dt,
    &aBridgeA_actor_init,
    &aBridgeA_actor_draw,
    NULL,
};
// clang-format on

static void aBridgeA_set_BgOffset(ACTOR* actorx) {
    // clang-format off
    static const mCoBG_OffsetTable_c rewrite_data[] = {
        { mCoBG_ATTRIBUTE_31, 4, 4, 4, 4, 4, 0 },
        { mCoBG_ATTRIBUTE_27, 4, 0, 4, 4, 4, 1 },
        { mCoBG_ATTRIBUTE_28, 4, 4, 0, 4, 4, 1 },
        { mCoBG_ATTRIBUTE_29, 4, 4, 4, 0, 4, 1 },
        { mCoBG_ATTRIBUTE_30, 4, 4, 4, 4, 0, 1 },
        { mCoBG_ATTRIBUTE_31, 0, 0, 0, 0, 0, 0 },
    };
    // clang-format on

    static s_xyz unit_offset_a0[] = {
        { 0, 0, 0 }, { 0, 1, -1 }, { -1, 1, 0 }, { 1, 3, 0 }, { 0, 3, 1 }, { 1, 5, -1 }, { -1, 5, 1 },
    };

    static s_xyz unit_offset_a1[] = {
        { 0, 0, 0 }, { 0, 4, -1 }, { 1, 4, 0 }, { -1, 2, 0 }, { 0, 2, 1 }, { -1, 5, -1 }, { 1, 5, 1 },
    };

    f32 dist_to_ground = mCoBG_GetBgY_OnlyCenter_FromWpos2(actorx->world.position, 0.0f);
    s_xyz* unit_offset = actorx->npc_id == BRIDGE_A0 ? unit_offset_a0 : unit_offset_a1;
    int i;

    for (i = 0; i < 7; i++) {
        xyz_t pos = actorx->world.position;
        f32 ut_dist_to_ground;

        pos.x += unit_offset[i].x * mFI_UNIT_BASE_SIZE_F;
        pos.z += unit_offset[i].z * mFI_UNIT_BASE_SIZE_F;
        ut_dist_to_ground = mCoBG_GetBgY_OnlyCenter_FromWpos2(pos, 0.0f);

        /* s_xyz->y is repurposed to be the index into 'rewrite_data' array (could be new struct too) */
        if (unit_offset[i].y == 5 && ut_dist_to_ground == dist_to_ground) {
            mCoBG_SetPluss5PointOffset_file(pos, rewrite_data[0], __FILE__, 217);
        } else {
            mCoBG_SetPluss5PointOffset_file(pos, rewrite_data[unit_offset[i].y], __FILE__, 220);
        }

        /* Update all bridge units other than the main item unit */
        if (i != 0) {
            mFI_SetFG_common(RSV_NO, pos, FALSE);
        }
    }
}

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_bridgeA;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_bridgeA;

extern cKF_Animation_R_c cKF_ba_r_obj_s_bridgeA;
extern cKF_Animation_R_c cKF_ba_r_obj_w_bridgeA;

static void aBridgeA_actor_ct(ACTOR* actorx, GAME* game) {
    static cKF_Skeleton_R_c* skl[] = { &cKF_bs_r_obj_s_bridgeA, &cKF_bs_r_obj_w_bridgeA };
    static cKF_Animation_R_c* anm[] = { &cKF_ba_r_obj_s_bridgeA, &cKF_ba_r_obj_w_bridgeA };

    STRUCTURE_ACTOR* bridge = (STRUCTURE_ACTOR*)actorx;
    int idx;

    if (Common_Get(time).season == mTM_SEASON_WINTER) {
        idx = 1;
    } else {
        idx = 0;
    }

    bridge->actor_class.world.position.y += 1.5f;
    cKF_SkeletonInfo_R_ct(&bridge->keyframe, skl[idx], anm[idx], bridge->work_area, bridge->morph_area);
    cKF_SkeletonInfo_R_init_standard_repeat(&bridge->keyframe, anm[idx], NULL);
    cKF_SkeletonInfo_R_play(&bridge->keyframe);

    if (actorx->npc_id == BRIDGE_A0) {
        actorx->shape_info.rotation.y = DEG2SHORT_ANGLE2(0.0f);
    } else {
        actorx->shape_info.rotation.y = DEG2SHORT_ANGLE2(-90.0f);
    }

    aBridgeA_set_BgOffset(actorx);
    bridge->arg1_f = 0.0f;
    bridge->arg0_f = 0.0f;
    sAdo_RegistPlussBridge(&actorx->world.position);
}

static void aBridgeA_actor_dt(ACTOR* actorx, GAME* game) {
    sAdo_DeletePlussBridge();
}

static f32 aBridge_player_check(STRUCTURE_ACTOR* bridge, GAME_PLAY* play) {
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR(play);
    xyz_t player_pos = player->actor_class.world.position;
    xyz_t bridge_pos = bridge->actor_class.world.position;
    xyz_t player_dist_from_bridge;
    f32 bridge_run_speed = player->actor_class.speed * (0.75f + (f32)GETREG(TAKREG, 23) * 0.01f);
    f32 dist0;
    f32 dist1;

    xyz_t_sub(&player_pos, &bridge_pos, &player_dist_from_bridge);
    if (bridge->actor_class.npc_id == BRIDGE_A1) {
        dist0 = player_dist_from_bridge.x - player_dist_from_bridge.z;
        dist1 = player_dist_from_bridge.x + player_dist_from_bridge.z;
    } else {
        dist0 = player_dist_from_bridge.x + player_dist_from_bridge.z;
        dist1 = player_dist_from_bridge.x - player_dist_from_bridge.z;
    }

    if ((dist0 > -mFI_UNIT_BASE_SIZE_F && dist0 < mFI_UNIT_BASE_SIZE_F) &&
        (dist1 > -mFI_UNIT_BASE_SIZE_F * 2 && dist1 < mFI_UNIT_BASE_SIZE_F * 2)) {
        if (bridge_run_speed > bridge->arg0_f) {
            bridge->arg1_f = 1.0f + (f32)GETREG(TAKREG, 20) * 0.01f;
            bridge->arg0_f = bridge_run_speed;
        } else if (bridge_run_speed > 0.1f) {
            add_calc(&bridge->arg0_f, bridge_run_speed, 0.1f + (f32)GETREG(TAKREG, 22) * 0.01f, 0.1f, 0.01f);
            add_calc(&bridge->arg1_f, 1.0f, 0.1f + (f32)GETREG(TAKREG, 24) * 0.01f, 0.1f, 0.01f);
            return;
        }
    }

    add_calc(&bridge->arg1_f, 0.0f, (0.08f + (f32)GETREG(TAKREG, 21) * 0.01f) * (0.4f + bridge->arg0_f * 0.1f), 0.1f,
             0.01f);
}

static void aBridgeA_actor_move(ACTOR* actorx, GAME* game) {
    STRUCTURE_ACTOR* bridge = (STRUCTURE_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

    aBridge_player_check(bridge, play);
    bridge->keyframe.frame_control.speed = bridge->arg0_f * 0.5f;
    cKF_SkeletonInfo_R_play(&bridge->keyframe);
    if (bridge->arg1_f == 0.0f) {
        bridge->arg1_f = 0.0f;
        bridge->arg0_f = 0.0f;
        bridge->keyframe.frame_control.current_frame = 0.0f;
    }
}

static void aBridgeA_actor_init(ACTOR* actorx, GAME* game) {
    mFI_SetFG_common(DUMMY_BRIDGE, actorx->home.position, FALSE);
    aBridgeA_actor_move(actorx, game);
    actorx->mv_proc = &aBridgeA_actor_move;
}

static int aBridgeA_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                                u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    static s16 base_r_table[] = {
        DEG2SHORT_ANGLE2(0.0f),       DEG2SHORT_ANGLE2(0.0f),        DEG2SHORT_ANGLE2(314.703369f),
        DEG2SHORT_ANGLE2(90.296631f), DEG2SHORT_ANGLE2(270.302124f), DEG2SHORT_ANGLE2(44.697876f),
    };

    STRUCTURE_ACTOR* bridge = (STRUCTURE_ACTOR*)arg;
    f32 rot = bridge->arg1_f;

    if (joint_idx > 1) {
        f32 inv = 1.0f - rot;

        joint_rot->z = rot * (f32)joint_rot->z + inv * (f32)base_r_table[joint_idx];
    }

    return TRUE;
}

static void aBridgeA_actor_draw(ACTOR* actorx, GAME* game) {
    STRUCTURE_ACTOR* bridge = (STRUCTURE_ACTOR*)actorx;
    N64Mtx* mtx_p = (N64Mtx*)GRAPH_ALLOC_TYPE(game->graph, N64Mtx, bridge->keyframe.skeleton->num_shown_joints);

    _texture_z_light_fog_prim(game->graph);
    cKF_Si3_draw_R_SV(game, &bridge->keyframe, mtx_p, &aBridgeA_before_disp, NULL, actorx);
}
