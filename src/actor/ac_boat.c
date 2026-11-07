#include "ac_boat.h"

#include "ac_boat_demo.h"
#include "m_play.h"
#include "m_common_data.h"
#include "m_field_info.h"
#include "m_rcp.h"
#include "m_player_lib.h"
#include "libultra/libultra.h"
#include "sys_matrix.h"

#define aBT_FURROW_MAX_SPEED FRAMERATE_ADJ(0.625f)

enum {
    aBT_DIRECTION_TO_ISLAND,
    aBT_DIRECTION_FROM_ISLAND,

    aBT_DIRECTION_NUM
};

enum {
    aBT_ACTION_DEMO_CTRL_BIRTH_WAIT,
    aBT_ACTION_WAIT,
    aBT_ACTION_PL_RIDE_MOVE_START_WAIT,
    aBT_ACTION_PL_RIDE_MOVE_END_WAIT,
    aBT_ACTION_PL_RIDE_ON_START_WAIT,
    aBT_ACTION_PL_RIDE_ON_END_WAIT,
    aBT_ACTION_SITDOWN_END_WAIT,
    aBT_ACTION_MOVE_WAIT,
    aBT_ACTION_MOVE,
    aBT_ACTION_MOMENT,
    aBT_ACTION_DRAW_UP,
    aBT_ACTION_ARRIVE_CALL_END_WAIT,
    aBT_ACTION_PL_RIDE_OFF_START_WAIT,
    aBT_ACTION_PL_RIDE_OFF_END_WAIT,
    aBT_ACTION_ANCHOR,

    aBT_ACTION_NUM
};

static void aBT_actor_ct(ACTOR*, GAME*);
static void aBT_actor_dt(ACTOR*, GAME*);
static void aBT_actor_init(ACTOR*, GAME*);
static void aBT_actor_draw(ACTOR*, GAME*);

ACTOR_PROFILE Boat_Profile = {
    mAc_PROFILE_BOAT,
    ACTOR_PART_ITEM,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_TA_SET | ACTOR_STATE_NO_MOVE_WHILE_CULLED |
        ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    BOAT,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(BOAT_ACTOR),
    &aBT_actor_ct,
    &aBT_actor_dt,
    &aBT_actor_init,
    &aBT_actor_draw,
    NULL,
};

static xyz_t aBT_chk_point[] = {
    // Position                    Z-X       X     Z
    { 3420.0f, 0.0f, 4260.0f }, // F-5 unit  5.5 - 10.5
    { 3380.0f, 0.0f, 4300.0f }, // F-5 unit  4.5 - 11.5
    { 3340.0f, 0.0f, 4380.0f }, // F-5 unit  3.5 - 13.5
    { 3340.0f, 0.0f, 4620.0f }, // G-5 unit  3.5 -  3.5
    { 3740.0f, 0.0f, 4980.0f }, // G-5 unit 13.5 - 12.5
    { 3740.0f, 0.0f, 5220.0f }, // H-5 unit 13.5 -  2.5
    { 3700.0f, 0.0f, 5300.0f }, // H-5 unit 12.5 -  4.5
    { 3660.0f, 0.0f, 5340.0f }, // H-5 unit 11.5 -  5.5
};

static int aBT_last_point_idx[aBT_DIRECTION_NUM] = { 7, 0 };

s16 aBT_init_angleY[aBT_DIRECTION_NUM] = {
    DEG2SHORT_ANGLE(-45.0f), // 0xE000
    DEG2SHORT_ANGLE(135.0f), // 0x6000
};

static void aBT_setupAction(BOAT_ACTOR* boat_actor, GAME_PLAY* play, int action);
static int aBT_check_other_boat(ACTOR* actorx, GAME* game);

extern cKF_Skeleton_R_c cKF_bs_r_obj_e_boat;
extern cKF_Animation_R_c cKF_ba_r_obj_e_boat;

static void aBT_actor_ct(ACTOR* actorx, GAME* game) {
    BOAT_ACTOR* boat_actor = (BOAT_ACTOR*)actorx;

    if (aBT_check_other_boat(actorx, game) == TRUE) {
        GAME_PLAY* play = (GAME_PLAY*)game;
        cKF_SkeletonInfo_R_c* keyframe = &boat_actor->keyframe;
        int direction = aBT_DIRECTION_TO_ISLAND;

        if (actorx->block_z != 6) {
            direction = aBT_DIRECTION_FROM_ISLAND;
        }

#if VERSION >= VER_GAFU01_00
        actorx->world.position.y = 1.0f + mCoBG_GetWaterHeight_File(actorx->world.position, __FILE__, 333);
#else
        actorx->world.position.y = 1.0f + mCoBG_GetWaterHeight_File(actorx->world.position, __FILE__, 326);
#endif
        actorx->shape_info.rotation.y = aBT_init_angleY[direction];
        actorx->world.angle.y = aBT_init_angleY[direction];
        xyz_t_move(&actorx->home.position, &actorx->world.position);

        /* Load & play boat rocking animation */
        cKF_SkeletonInfo_R_ct(keyframe, &cKF_bs_r_obj_e_boat, NULL, boat_actor->work, boat_actor->morph);
        cKF_SkeletonInfo_R_init(keyframe, keyframe->skeleton, &cKF_ba_r_obj_e_boat, 1.0f, 81.0f, 1.0f, 0.0f, 0.0f,
                                cKF_FRAMECONTROL_REPEAT, NULL);
        cKF_SkeletonInfo_R_play(keyframe);

        actorx->gravity = 0.003f;
        actorx->max_velocity_y = 0.1f;
        actorx->position_speed.y = 0.1f;
        boat_actor->roll_cycle = 0;
        boat_actor->roll_timer = 200;
        boat_actor->roll_timer_accum = 0.0f;
        boat_actor->roll_cycle_accum = 0.0f;
        boat_actor->logic_accum = 0.0f;
        boat_actor->direction = direction;
        aBT_setupAction(boat_actor, play, aBT_ACTION_DEMO_CTRL_BIRTH_WAIT);
        mCoBG_MakeBoatCollision(actorx, &actorx->world.position, &actorx->shape_info.rotation.y);
    } else {
        Actor_delete(actorx); // another boat already exists
    }
}

static void aBT_actor_dt(ACTOR* actorx, GAME* game) {
    BOAT_ACTOR* boat_actor = (BOAT_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;
    cKF_SkeletonInfo_R_c* keyframe = &boat_actor->keyframe;
    BOAT_DEMO_ACTOR* boat_demo;

    cKF_SkeletonInfo_R_dt(keyframe);
    mFI_SetFG_common(BOAT, actorx->home.position, FALSE);

    boat_demo = (BOAT_DEMO_ACTOR*)actorx->parent_actor;
    if (boat_demo != NULL && boat_demo->boat_actor == boat_actor) {
        boat_demo->boat_actor = NULL;
    }

    mCoBG_DeleteBoatCollision(actorx);
}

#include "../src/actor/ac_boat_move.c_inc"

static u32 aBT_calc_furrow_alpha(BOAT_ACTOR* boat_actor) {
    f32 speed = boat_actor->actor_class.speed;

    if (speed > aBT_FURROW_MAX_SPEED) {
        speed = aBT_FURROW_MAX_SPEED;
    }

    return (u32)((speed / aBT_FURROW_MAX_SPEED) * 150.0f);
}

static int aBT_actor_draw_before(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                                 u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    BOAT_ACTOR* boat_actor = (BOAT_ACTOR*)arg;

    switch (joint_idx) {
        case 3: {
            Matrix_translate(boat_actor->actor_class.world.position.x, boat_actor->actor_class.world.position.y,
                             boat_actor->actor_class.world.position.z, MTX_LOAD);
            Matrix_RotateY(boat_actor->actor_class.shape_info.rotation.y, MTX_MULT);
            Matrix_scale(boat_actor->actor_class.scale.x, boat_actor->actor_class.scale.y,
                         boat_actor->actor_class.scale.z, MTX_MULT);
            break;
        }

        case 5: {
            joint_rot->x = 0;
            joint_rot->y = 0;
            joint_rot->z = boat_actor->wave_angl0;
            break;
        }

        case 6: {
            joint_rot->x = 0;
            joint_rot->y = 0;
            joint_rot->z = boat_actor->wave_angl1;
            break;
        }
    }

    return TRUE;
}

static void aBT_actor_draw(ACTOR* actorx, GAME* game) {
    BOAT_ACTOR* boat_actor = (BOAT_ACTOR*)actorx;
    cKF_SkeletonInfo_R_c* keyframe = &boat_actor->keyframe;
    GRAPH* graph = game->graph;
    Gfx* scroll_gfx;
    f32 furrow_scroll = boat_actor->furrow_scroll - actorx->speed * 0.5f * (f32)graph->dt_num_60fps_frames;

    while (furrow_scroll < -32.0f) {
        furrow_scroll += 32.0f;
    }

    boat_actor->furrow_scroll = furrow_scroll;
    scroll_gfx = two_tex_scroll_dolphin(graph, 0, 0, 0, 32, 32, 1, 0, furrow_scroll * 8.0f, 32, 32);

    if (scroll_gfx != NULL) {
        N64Mtx* mtx = GRAPH_ALLOC_TYPE(graph, N64Mtx, keyframe->skeleton->num_shown_joints);

        if (mtx != NULL) {
            Gfx* gfx;
            u16* pal = Common_Get(clip).structure_clip->get_pal_segment_proc(aSTR_PAL_BOAT);

            _texture_z_light_fog_prim(graph);
            _texture_z_light_fog_prim_xlu(graph);

            OPEN_DISP(graph);

            gfx = NOW_POLY_OPA_DISP;
            gDPPipeSync(gfx++);
            gDPLoadTLUT_Dolphin(gfx++, 15, 16, 1, pal);
            SET_POLY_OPA_DISP(gfx);

            gfx = NOW_POLY_XLU_DISP;
            gDPPipeSync(gfx++);
            gSPSegment(gfx++, G_MWO_SEGMENT_9, scroll_gfx);
            gDPLoadTLUT_Dolphin(gfx++, 15, 16, 1, pal);
            gDPSetEnvColor(gfx++, 155, 155, 255, aBT_calc_furrow_alpha(boat_actor));
            SET_POLY_XLU_DISP(gfx);

            CLOSE_DISP(graph);

            cKF_Si3_draw_R_SV(game, keyframe, mtx, &aBT_actor_draw_before, NULL, actorx);
        }
    }
}
