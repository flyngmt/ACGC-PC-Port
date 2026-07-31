extern cKF_Skeleton_R_c cKF_bs_r_int_sum_okiagari01;
extern cKF_Animation_R_c cKF_ba_r_int_sum_okiagari01;

static void aSumOkiagari01_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_ct(keyframe, &cKF_bs_r_int_sum_okiagari01, &cKF_ba_r_int_sum_okiagari01, ftr_actor->joint,
                          ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_stop(keyframe, &cKF_ba_r_int_sum_okiagari01, NULL);
    cKF_SkeletonInfo_R_play(keyframe);
    keyframe->frame_control.speed = 0.5f;
}

static void aSumOkiagari01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    if (cKF_SkeletonInfo_R_play(keyframe) != cKF_STATE_STOPPED) {
        cKF_SkeletonInfo_R_play(keyframe);
        keyframe->frame_control.speed = 0.5f;
    } else if (ftr_actor->switch_changed_flag) {
        if (aFTR_CAN_PLAY_SE(ftr_actor)) {
            sAdo_OngenTrgStart(0x145, &ftr_actor->position);
        }

        keyframe->frame_control.current_frame = 1.0f;
        cKF_SkeletonInfo_R_play(keyframe);
        keyframe->frame_control.speed = 0.5f;
    }
}

static void aSumOkiagari01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    int mtx_idx = game->frame_counter & 1;
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    N64Mtx* mtx = ftr_actor->skeleton_mtx[mtx_idx];

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    CLOSE_DISP(game->graph);

    cKF_Si3_draw_R_SV(game, keyframe, mtx, NULL, NULL, NULL);
}

static aFTR_vtable_c aSumOkiagari01_func = {
    &aSumOkiagari01_ct, &aSumOkiagari01_mv, &aSumOkiagari01_dw, NULL, NULL,
};

aFTR_PROFILE iam_sum_okiagari01 = {
    // clang-format off
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    40.0f,
    0.01f,
    aFTR_SHAPE_TYPEA,
    mCoBG_FTR_TYPEA,
    0,
    0,
    0,
    0,
    &aSumOkiagari01_func,
    // clang-format on
};
