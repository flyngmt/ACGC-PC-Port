extern aFTR_rig_c aSumMezaClock_sklkey;
extern Gfx int_sum_mezaclock_short_model[];
extern Gfx int_sum_mezaclock_long_model[];

extern cKF_Skeleton_R_c cKF_bs_r_int_sum_mezaclock;
extern cKF_Animation_R_c cKF_ba_r_int_sum_mezaclock;

aFTR_rig_c aSumMezaClock_sklkey= {
    &cKF_bs_r_int_sum_mezaclock,
    &cKF_ba_r_int_sum_mezaclock,
    1.0f,
};

static int aSumMezaClock_DwAfter(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                                 u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    if (joint_idx == 3) {
        OPEN_DISP(game->graph);

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(NEXT_POLY_OPA_DISP, int_sum_mezaclock_short_model);

        CLOSE_DISP(game->graph);
    } else if (joint_idx == 4) {
        OPEN_DISP(game->graph);

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(NEXT_POLY_OPA_DISP, int_sum_mezaclock_long_model);

        CLOSE_DISP(game->graph);
    }

    return TRUE;
}

static int aSumMezaClock_DwBefore(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                                  u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    if (joint_idx == 3) {
        joint_rot->z -= Common_Get(time.rad_hour);
    } else if (joint_idx == 4) {
        joint_rot->z -= Common_Get(time.rad_min);
    }

    return TRUE;
}

static void aSumMezaClock_Dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    int mtx_idx = game->frame_counter & 1;
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    N64Mtx* mtx = ftr_actor->skeleton_mtx[mtx_idx];

    cKF_Si3_draw_R_SV(game, keyframe, mtx, &aSumMezaClock_DwBefore, &aSumMezaClock_DwAfter, ftr_actor);
}

static aFTR_vtable_c aSumMezaClock_func = {
    NULL, NULL, &aSumMezaClock_Dw, NULL, NULL,
};

aFTR_PROFILE iam_sum_mezaclock = {
    // clang-format off
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    &aSumMezaClock_sklkey,
    NULL,
    18.0f,
    0.01f,
    aFTR_SHAPE_TYPEA,
    mCoBG_FTR_TYPEA,
    0,
    0,
    0,
    0,
    &aSumMezaClock_func,
    // clang-format on
};
