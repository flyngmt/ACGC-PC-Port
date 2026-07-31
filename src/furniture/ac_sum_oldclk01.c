extern cKF_Skeleton_R_c cKF_bs_r_int_sum_oldclk01;
extern cKF_Animation_R_c cKF_ba_r_int_sum_oldclk01;

static void aSumOldClk01_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_ct(keyframe, &cKF_bs_r_int_sum_oldclk01, &cKF_ba_r_int_sum_oldclk01, ftr_actor->joint,
                          ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_repeat(keyframe, &cKF_ba_r_int_sum_oldclk01, NULL);
    cKF_SkeletonInfo_R_play(keyframe);
    keyframe->frame_control.speed = 0.5f;
}

static int aSumOldClk01_dwAfter(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                                u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    return TRUE;
}

static int aSumOldClk01_dwBefore(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                                 u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    if (joint_idx == 5) {
        joint_rot->z -= Common_Get(time.rad_hour);
    } else if (joint_idx == 7) {
        joint_rot->z -= Common_Get(time.rad_min);
    }

    return TRUE;
}

static void aSumOldClk01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    int mtx_idx = game->frame_counter & 1;
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    N64Mtx* mtx = ftr_actor->skeleton_mtx[mtx_idx];

    cKF_Si3_draw_R_SV(game, keyframe, mtx, &aSumOldClk01_dwBefore, &aSumOldClk01_dwAfter, ftr_actor);
}

static void aSumOldClk01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (Common_Get(clip).my_room_clip != NULL) {
        cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
        aMR_clock_info_c* clock_info = Common_Get(clip).my_room_clip->clock_info_p;

        if (clock_info->tick_stop) {
            cKF_SkeletonInfo_R_init_standard_repeat(keyframe, &cKF_ba_r_int_sum_oldclk01, NULL);
            cKF_SkeletonInfo_R_play(keyframe);
            keyframe->frame_control.speed = 0.5f;
        } else if (clock_info->tick0 == TRUE || clock_info->tick1 == TRUE) {
            if (aFTR_CAN_PLAY_SE(ftr_actor)) {
                sAdo_OngenTrgStart(0x12D, &ftr_actor->position);
            }

            cKF_SkeletonInfo_R_play(keyframe);
        } else {
            cKF_SkeletonInfo_R_play(keyframe);
        }
    }
}

static void aSumOldClk01_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static aFTR_vtable_c aSumOldClk01_func = {
    &aSumOldClk01_ct, &aSumOldClk01_mv, &aSumOldClk01_dw, &aSumOldClk01_dt, NULL,
};

aFTR_PROFILE iam_sum_oldclk01 = {
    // clang-format off
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    18.0f,
    0.01f,
    aFTR_SHAPE_TYPEA,
    mCoBG_FTR_TYPEA,
    0,
    2,
    0,
    0,
    &aSumOldClk01_func,
    // clang-format on
};
