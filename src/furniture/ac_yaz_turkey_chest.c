extern cKF_Skeleton_R_c cKF_bs_r_int_yaz_turkey_chest;
extern cKF_Animation_R_c cKF_ba_r_int_yaz_turkey_chest;

static void fYTCST_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_ct(keyframe, &cKF_bs_r_int_yaz_turkey_chest, &cKF_ba_r_int_yaz_turkey_chest, ftr_actor->joint,
                          ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_stop(keyframe, &cKF_ba_r_int_yaz_turkey_chest, NULL);
    keyframe->frame_control.speed = 0.0f;
    cKF_SkeletonInfo_R_play(keyframe);
}

static void fYTCST_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (Common_Get(clip).my_room_clip != NULL) {
        (*Common_Get(clip).my_room_clip->open_close_common_move_proc)(ftr_actor, my_room_actor, game, 1.0f, 10.0f);
    }
}

static void fYTCST_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    N64Mtx* mtx = ftr_actor->skeleton_mtx[game->frame_counter & 1];

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    CLOSE_DISP(game->graph);

    cKF_Si3_draw_R_SV(game, keyframe, mtx, NULL, NULL, NULL);
}

static void fYTCST_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static aFTR_vtable_c fYTCST_func = {
    &fYTCST_ct, &fYTCST_mv, &fYTCST_dw, &fYTCST_dt, NULL,
};

aFTR_PROFILE iam_yaz_turkey_chest = {
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
    aFTR_SHAPE_TYPEB_0,
    mCoBG_FTR_TYPEB_0,
    0,
    0,
    0,
    aFTR_INTERACTION_STORAGE_DRAWERS,
    &fYTCST_func,
    // clang-format on
};
