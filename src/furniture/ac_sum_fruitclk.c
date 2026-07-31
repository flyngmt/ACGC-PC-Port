extern Gfx int_sum_hal_clk01_short_model[];
extern Gfx int_sum_hal_clk01_long_model[];

static int aSumfruitclk_DwAfter(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                                u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    return TRUE;
}

static int aSumfruitclk_DwBefore(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                                 u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    if (joint_idx == 3) {
        joint_rot->z -= Common_Get(time.rad_hour);
    } else if (joint_idx == 4) {
        joint_rot->z -= Common_Get(time.rad_min);
    }

    return TRUE;
}

static void aSumfruitclk_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    N64Mtx* mtx = ftr_actor->skeleton_mtx[game->frame_counter & 1];

    cKF_Si3_draw_R_SV(game, keyframe, mtx, &aSumfruitclk_DwBefore, &aSumfruitclk_DwAfter, ftr_actor);
}

extern cKF_Skeleton_R_c cKF_bs_r_int_sum_fruitclk;
extern cKF_Animation_R_c cKF_ba_r_int_sum_fruitclk;

static void aSumfruitclk_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_ct(keyframe, &cKF_bs_r_int_sum_fruitclk, &cKF_ba_r_int_sum_fruitclk, ftr_actor->joint,
                          ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_repeat(keyframe, &cKF_ba_r_int_sum_fruitclk, NULL);
    cKF_SkeletonInfo_R_play(keyframe);
    keyframe->frame_control.speed = 0.5f;
}

static void aSumfruitclk_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_play(keyframe);
}

static void aSumfruitclk_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static aFTR_vtable_c aSumfruitclk_func = {
    &aSumfruitclk_ct, &aSumfruitclk_mv, &aSumfruitclk_dw, &aSumfruitclk_dt, NULL,
};

aFTR_PROFILE iam_sum_fruitclk = {
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
    &aSumfruitclk_func,
    // clang-format on
};
