extern aFTR_rig_c aSumMizunomi_sklkey;

extern cKF_Skeleton_R_c cKF_bs_r_int_sum_mizunomi;
extern cKF_Animation_R_c cKF_ba_r_int_sum_mizunomi;

aFTR_rig_c aSumMizunomi_sklkey= {
    &cKF_bs_r_int_sum_mizunomi,
    &cKF_ba_r_int_sum_mizunomi,
    1.0f,
};

static void aSumMizunomi_ct(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static void aSumMizunomi_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (aFTR_CAN_PLAY_SE(ftr_actor)) {
        cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

        if (cKF_FrameControl_passCheck_now(&keyframe->frame_control, 19.0f)) {
            sAdo_OngenTrgStart(0x12A, &ftr_actor->position);
        }
    }
}

static void aSumMizunomi_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    // nothing
}

static void aSumMizunomi_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static aFTR_vtable_c aSumMizunomi_func = {
    &aSumMizunomi_ct, &aSumMizunomi_mv, &aSumMizunomi_dw, &aSumMizunomi_dt, NULL,
};

aFTR_PROFILE iam_sum_mizunomi = {
    // clang-format off
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    &aSumMizunomi_sklkey,
    NULL,
    40.0f,
    0.01f,
    aFTR_SHAPE_TYPEA,
    mCoBG_FTR_TYPEA,
    0,
    2,
    0,
    0,
    &aSumMizunomi_func,
    // clang-format on
};
