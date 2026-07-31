#include "ac_train_door.h"

#include "audio.h"
#include "m_rcp.h"
#include "m_name_table.h"

static void aTRD_actor_ct(ACTOR* actor, GAME* game);
static void aTRD_actor_dt(ACTOR* actor, GAME* game);
static void aTRD_actor_move(ACTOR* actor, GAME* game);
static void aTRD_actor_draw(ACTOR* actor, GAME* game);

ACTOR_PROFILE TrainDoor_Profile = {
    mAc_PROFILE_TRAINDOOR,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    TRAIN_DOOR,
    ACTOR_OBJ_BANK_TRAINDOOR,
    sizeof(TRAINDOOR_ACTOR),
    &aTRD_actor_ct,
    &aTRD_actor_dt,
    &aTRD_actor_move,
    &aTRD_actor_draw,
    NULL,
};

extern cKF_Skeleton_R_c cKF_bs_r_obj_romtrain_door;
extern cKF_Animation_R_c cKF_ba_r_obj_romtrain_door;

static void aTRD_actor_ct(ACTOR* actor, GAME* game) {
    TRAINDOOR_ACTOR* traindoor = (TRAINDOOR_ACTOR*)actor;

    cKF_SkeletonInfo_R_ct(&traindoor->common_actor_class.anime.keyframe, &cKF_bs_r_obj_romtrain_door, NULL,
                          traindoor->work, traindoor->target);
    cKF_SkeletonInfo_R_init(&traindoor->common_actor_class.anime.keyframe,
                            traindoor->common_actor_class.anime.keyframe.skeleton, &cKF_ba_r_obj_romtrain_door, 1.0f,
                            51.0f, 1.0f, 0.0f, 0.0f, 0, NULL);
    traindoor->common_actor_class.anime.keyframe.morph_counter = 0.0f;
    cKF_SkeletonInfo_R_play(&traindoor->common_actor_class.anime.keyframe);
}

static void aTRD_actor_dt(ACTOR* actor, GAME* game) {
    TRAINDOOR_ACTOR* traindoor = (TRAINDOOR_ACTOR*)actor;

    cKF_SkeletonInfo_R_dt(&traindoor->common_actor_class.anime.keyframe);
}

static void aTRD_set_door_SE(ACTOR* actor) {
    TRAINDOOR_ACTOR* traindoor = (TRAINDOOR_ACTOR*)actor;

    static f32 chk_pat[] = { 2.0f, 27.0f };
    static u16 se_no[] = { NA_SE_TRAINDOOR0, NA_SE_TRAINDOOR1 };
    int i;

    for (i = 0; i < 2; i++) {
        if (cKF_FrameControl_passCheck_now(&traindoor->common_actor_class.anime.keyframe.frame_control, chk_pat[i])) {
            sAdo_OngenTrgStart(se_no[i], &traindoor->common_actor_class.actor_class.world.position);
            break;
        }
    }
}

static void aTRD_actor_move(ACTOR* actor, GAME* game) {
    TRAINDOOR_ACTOR* traindoor = (TRAINDOOR_ACTOR*)actor;

    if (traindoor->open_flag == TRUE) {
        traindoor->open_flag = FALSE;
        traindoor->common_actor_class.anime.keyframe.frame_control.speed = 0.5f;
    }

    if (cKF_SkeletonInfo_R_play(&traindoor->common_actor_class.anime.keyframe) == cKF_FRAMECONTROL_REPEAT) {
        traindoor->common_actor_class.anime.keyframe.frame_control.current_frame =
            traindoor->common_actor_class.anime.keyframe.frame_control.start_frame;
        traindoor->common_actor_class.anime.keyframe.frame_control.speed = 0.0f;
    }

    aTRD_set_door_SE(actor);
}

static void aTRD_actor_draw(ACTOR* actor, GAME* game) {
    TRAINDOOR_ACTOR* traindoor = (TRAINDOOR_ACTOR*)actor;

    cKF_SkeletonInfo_R_c* keyf = &traindoor->common_actor_class.anime.keyframe;
    N64Mtx* mtxp;

    mtxp = GRAPH_ALLOC_TYPE(game->graph, N64Mtx, (u32)keyf->skeleton->num_shown_joints);
    if (mtxp != NULL) {
        _texture_z_light_fog_prim(game->graph);
        texture_z_light_prim_xlu_disp(game->graph);
        cKF_Si3_draw_R_SV(game, keyf, mtxp, NULL, NULL, NULL);
    }
}
