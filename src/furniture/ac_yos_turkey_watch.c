static int fYTW_DwAfter(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape, u8* joint_flags,
                        void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    return TRUE;
}

static int fYTW_DwBefore(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape, u8* joint_flags,
                         void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    if (joint_idx == 3) {
        joint_rot->z -= Common_Get(time.rad_hour);
    } else if (joint_idx == 4) {
        joint_rot->z -= Common_Get(time.rad_min);
    }

    return TRUE;
}

static void fYTW_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    N64Mtx* mtx = ftr_actor->skeleton_mtx[game->frame_counter & 1];

    cKF_Si3_draw_R_SV(game, keyframe, mtx, &fYTW_DwBefore, &fYTW_DwAfter, ftr_actor);
}

extern cKF_Skeleton_R_c cKF_bs_r_int_yos_turkey_watch;
extern cKF_Animation_R_c cKF_ba_r_int_yos_turkey_watch;

static void fYTW_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_ct(keyframe, &cKF_bs_r_int_yos_turkey_watch, &cKF_ba_r_int_yos_turkey_watch, ftr_actor->joint,
                          ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_repeat(keyframe, &cKF_ba_r_int_yos_turkey_watch, NULL);
    cKF_SkeletonInfo_R_play(keyframe);
    keyframe->frame_control.speed = 0.5f;
}

static void fYTW_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_play(keyframe);
}

static void fYTW_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static aFTR_vtable_c fYTW_func = {
    &fYTW_ct, &fYTW_mv, &fYTW_dw, &fYTW_dt, NULL,
};

aFTR_PROFILE iam_yos_turkey_watch = {
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
	&fYTW_func,
    // clang-format on
};
