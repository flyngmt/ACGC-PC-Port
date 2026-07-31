extern cKF_Skeleton_R_c cKF_bs_r_int_nog_pawnW;
extern cKF_Animation_R_c cKF_ba_r_int_nog_pawnW;

static void aNogpawnW_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_ct(keyframe, &cKF_bs_r_int_nog_pawnW, &cKF_ba_r_int_nog_pawnW, ftr_actor->joint,
                          ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_repeat(keyframe, &cKF_ba_r_int_nog_pawnW, NULL);
    keyframe->frame_control.speed = 0.5f;
    cKF_SkeletonInfo_R_play(keyframe);
}

static void aNogpawnW_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_play(keyframe);
    keyframe->frame_control.speed = 0.5f;
}

extern Gfx int_nog_pawnW_top_model[];

static int aNogpawnW_DwAfter(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                             u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    FTR_ACTOR* ftr_actor = (FTR_ACTOR*)arg;
    GAME_PLAY* play = (GAME_PLAY*)game;
    xyz_t pos;
    xyz_t old_pos = { 0.0f, 0.0f, 0.0f };

    if (joint_idx == 1) {
        f32 scale_x = ftr_actor->scale.x * 0.01f;
        f32 scale_y = ftr_actor->scale.y * 0.01f;
        f32 scale_z = ftr_actor->scale.z * 0.01f;

        OPEN_DISP(game->graph);

        Matrix_Position(&old_pos, &pos);
        Matrix_push();
        Matrix_translate(pos.x, pos.y, pos.z, MTX_LOAD);
        Matrix_mult(&play->billboard_matrix, MTX_MULT);
        Matrix_RotateY(DEG2SHORT_ANGLE(-90.0f), MTX_MULT);
        Matrix_scale(scale_x, scale_y, scale_z, MTX_MULT);

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        Matrix_pull();
        gSPDisplayList(NEXT_POLY_OPA_DISP, int_nog_pawnW_top_model);

        CLOSE_DISP(game->graph);
    }

    return TRUE;
}

static int aNogpawnW_DwBefore(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                              u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    if (joint_idx == 1) {
        *joint_shape = NULL;
    }

    return TRUE;
}

static void aNogpawnW_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    int mtx_idx = game->frame_counter & 1;
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    N64Mtx* mtx = ftr_actor->skeleton_mtx[mtx_idx];

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    CLOSE_DISP(game->graph);

    cKF_Si3_draw_R_SV(game, keyframe, mtx, &aNogpawnW_DwBefore, &aNogpawnW_DwAfter, ftr_actor);
}

static void aNogpawnW_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static aFTR_vtable_c aNogpawnW_func = {
    &aNogpawnW_ct, &aNogpawnW_mv, &aNogpawnW_dw, &aNogpawnW_dt, NULL,
};

aFTR_PROFILE iam_nog_pawnW = {
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
    &aNogpawnW_func,
    // clang-format on
};
