#include "ac_balloon.h"

#include "m_name_table.h"
#include "sys_matrix.h"
#include "m_player_lib.h"
#include "m_rcp.h"

enum {
    Ac_Balloon_MODE_HIDE,
    Ac_Balloon_MODE_FLY,

    Ac_Balloon_MODE_NUM
};

static void Ac_Balloon_dt(ACTOR* actorx, GAME* game) {
    // empty
}

extern void Ac_Balloon_request_hide(ACTOR* actorx, GAME* game) {
    BALLOON_ACTOR* balloon = (BALLOON_ACTOR*)actorx;

    balloon->setup_mode = Ac_Balloon_MODE_HIDE;
}

static void Ac_Balloon_setup_hide(ACTOR* actorx, GAME* game) {
    BALLOON_ACTOR* balloon = (BALLOON_ACTOR*)actorx;

    balloon->main_mode = Ac_Balloon_MODE_HIDE;
    balloon->setup_mode = -1;
}

static void Ac_Balloon_Movement_hide(ACTOR* actorx, GAME* game) {
    ACTOR* player_actor = GET_PLAYER_ACTOR_GAME_ACTOR(game);

    if (player_actor != NULL) {
        actorx->world.position = player_actor->world.position;
    }
}

static void Ac_Balloon_main_hide(ACTOR* actorx, GAME* game) {
    Ac_Balloon_Movement_hide(actorx, game);
}

extern void Ac_Balloon_request_fly(ACTOR* actorx, GAME* game, int balloon_type, const s_xyz* angle_p, s16 lean,
                                   const xyz_t* pos_p, f32 start_frame, f32 speed) {
    BALLOON_ACTOR* balloon = (BALLOON_ACTOR*)actorx;

    balloon->setup_mode = Ac_Balloon_MODE_FLY;
    balloon->balloon_type = balloon_type;
    balloon->angle = *angle_p;
    balloon->lean = lean;
    balloon->start_frame = start_frame;
    balloon->speed = speed;
    balloon->pos = *pos_p;
}

static void Ac_Balloon_setup_fly(ACTOR* actorx, GAME* game) {
    static int data[] = {
        mPlayer_ITEM_DATA_BALLOON1, mPlayer_ITEM_DATA_BALLOON2, mPlayer_ITEM_DATA_BALLOON3, mPlayer_ITEM_DATA_BALLOON4,
        mPlayer_ITEM_DATA_BALLOON5, mPlayer_ITEM_DATA_BALLOON6, mPlayer_ITEM_DATA_BALLOON7, mPlayer_ITEM_DATA_BALLOON8,
    };

    BALLOON_ACTOR* balloon = (BALLOON_ACTOR*)actorx;
    f32 start_frame;
    int data_type;
    int anim_type;
    cKF_SkeletonInfo_R_c* kf_p;
    cKF_Skeleton_R_c* skeleton;
    cKF_Animation_R_c* animation;

    balloon->main_mode = Ac_Balloon_MODE_FLY;
    balloon->saved_type = balloon->balloon_type;
    data_type = Ac_Balloon_TYPE_VALID(balloon->balloon_type) != FALSE ? data[balloon->balloon_type]
                                                                      : mPlayer_ITEM_DATA_BALLOON1;
    start_frame = balloon->start_frame;
    anim_type = start_frame < 1.0f ? mPlayer_ITEM_DATA_BALLOON_WAIT : mPlayer_ITEM_DATA_BALLOON_GYAZA;
    kf_p = &balloon->keyframe;
    skeleton = (cKF_Skeleton_R_c*)mPlib_Get_Item_DataPointer(data_type);
    animation = (cKF_Animation_R_c*)mPlib_Get_Item_DataPointer(anim_type);
    cKF_SkeletonInfo_R_ct(kf_p, skeleton, NULL, balloon->work, balloon->morph);
    cKF_SkeletonInfo_R_init_standard_repeat_setframeandspeedandmorph(kf_p, animation, NULL, start_frame, 0.0f, 0.0f);
    cKF_SkeletonInfo_R_play(kf_p);
    cKF_SkeletonInfo_R_init_standard_repeat_setframeandspeedandmorph(
        kf_p, mPlib_Get_Item_DataPointer(mPlayer_ITEM_DATA_BALLOON_WAIT), NULL, 1.0f, 0.5f, -5.0f);

    actorx->shape_info.rotation = balloon->angle;
    actorx->position_speed.y = 0.0f;
    actorx->max_velocity_y = balloon->speed;
    actorx->gravity = 0.2f;
    actorx->world.position = balloon->pos;
    balloon->setup_mode = -1;
}

static void Ac_Balloon_CulcAnimation_fly(ACTOR* actorx) {
    BALLOON_ACTOR* balloon = (BALLOON_ACTOR*)actorx;

    cKF_SkeletonInfo_R_play(&balloon->keyframe);
}

static void Ac_Balloon_Movement_fly(BALLOON_ACTOR* balloon) {
    add_calc_short_angle2(&balloon->actor_class.shape_info.rotation.x, 0, 1.0f - sqrtf(0.5f), 50, 5);
    add_calc_short_angle2(&balloon->actor_class.shape_info.rotation.z, 0, 1.0f - sqrtf(0.5f), 50, 5);
    add_calc_short_angle2(&balloon->lean, 0, 1.0f - sqrtf(0.5f), 50, 5);
    Actor_position_moveF(&balloon->actor_class);
}

static void Ac_Balloon_request_change_mode_fromFly(ACTOR* actorx, GAME* game) {
    ACTOR* player_actor = GET_PLAYER_ACTOR_GAME_ACTOR(game);

    if (player_actor != NULL && actorx->world.position.y - player_actor->world.position.y > 200.0f) {
        Ac_Balloon_request_hide(actorx, game);
    }
}

static void Ac_Balloon_main_fly(ACTOR* actorx, GAME* game) {
    BALLOON_ACTOR* balloon = (BALLOON_ACTOR*)actorx;

    Ac_Balloon_CulcAnimation_fly(actorx);
    Ac_Balloon_Movement_fly(balloon);
    Ac_Balloon_request_change_mode_fromFly(actorx, game);
}

typedef void (*Ac_Balloon_PROC)(ACTOR*, GAME*);

static void Ac_Balloon_main(ACTOR* actorx, GAME* game) {
    BALLOON_ACTOR* balloon = (BALLOON_ACTOR*)actorx;

    if (balloon->setup_mode >= 0 && balloon->setup_mode < Ac_Balloon_MODE_NUM) {
        static Ac_Balloon_PROC data[] = { &Ac_Balloon_setup_hide, &Ac_Balloon_setup_fly };

        if (data[balloon->setup_mode] != NULL) {
            (*data[balloon->setup_mode])(actorx, game);
        }
    }

    if (balloon->main_mode >= 0 && balloon->main_mode < Ac_Balloon_MODE_NUM) {
        static Ac_Balloon_PROC data[] = { &Ac_Balloon_main_hide, &Ac_Balloon_main_fly };

        if (data[balloon->main_mode] != NULL) {
            (*data[balloon->main_mode])(actorx, game);
        }
    }
}

static void Ac_Balloon_ct(ACTOR* actorx, GAME* game) {
    Ac_Balloon_request_hide(actorx, game);
}

static int Ac_Balloon_draw_Before(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                                  u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    switch (joint_idx) {
        case 1:
        case 2:
        case 3:
            OPEN_POLY_OPA_DISP(game->graph);

            gDPPipeSync(POLY_OPA_DISP++);
            gDPSetTexEdgeAlpha(POLY_OPA_DISP++, 80);

            CLOSE_POLY_OPA_DISP(game->graph);
            break;
    }

    return TRUE;
}

static int Ac_Balloon_draw_After(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                                 u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    switch (joint_idx) {
        case 1:
        case 2:
        case 3:
            OPEN_POLY_OPA_DISP(game->graph);

            gDPPipeSync(POLY_OPA_DISP++);
            gDPSetTexEdgeAlpha(POLY_OPA_DISP++, 144);

            CLOSE_POLY_OPA_DISP(game->graph);
            break;
    }

    return TRUE;
}

static void Ac_Balloon_draw_normal(ACTOR* actorx, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    s16 angle_x;
    s16 angle_y;
    BALLOON_ACTOR* balloon = (BALLOON_ACTOR*)actorx;
    int idx = game->frame_counter & 1;
    N64Mtx* mtx = balloon->mtx[idx];
    GRAPH* graph = game->graph;
    xyz_t* pos = &actorx->world.position;

    Matrix_push();
    angle_x = actorx->shape_info.rotation.x - DEG2SHORT_ANGLE2(90.0f);
    angle_y = actorx->shape_info.rotation.y;
    Matrix_translate(pos->x, pos->y, pos->z, MTX_LOAD);
    Matrix_RotateY(angle_y, MTX_MULT);
    Matrix_RotateX(angle_x, MTX_MULT);
    Matrix_RotateZ(DEG2SHORT_ANGLE2(90.0f), MTX_MULT);
    Matrix_RotateX(balloon->lean, MTX_MULT);
    Matrix_scale(actorx->scale.x, actorx->scale.y, actorx->scale.z, MTX_MULT);

    OPEN_POLY_OPA_DISP(graph);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    CLOSE_POLY_OPA_DISP(graph);

    _texture_z_light_fog_prim(graph);
    Setpos_HiliteReflect_init(pos, play);
    cKF_Si3_draw_R_SV((GAME*)play, &balloon->keyframe, mtx, &Ac_Balloon_draw_Before, &Ac_Balloon_draw_After, balloon);
    Matrix_pull();
}

static void Ac_Balloon_draw(ACTOR* actorx, GAME* game) {
    BALLOON_ACTOR* balloon = (BALLOON_ACTOR*)actorx;

    if (balloon->main_mode != Ac_Balloon_MODE_HIDE) {
        Ac_Balloon_draw_normal(actorx, game);
    }
}

ACTOR_PROFILE Balloon_Profile = {
    mAc_PROFILE_BALLOON,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    ITM_BALLOON_START,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(BALLOON_ACTOR),
    &Ac_Balloon_ct,
    &Ac_Balloon_dt,
    &Ac_Balloon_main,
    &Ac_Balloon_draw,
    NULL,
};
