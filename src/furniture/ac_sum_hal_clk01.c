extern Gfx int_sum_hal_clk01_short_model[];
extern Gfx int_sum_hal_clk01_long_model[];

static int aSumHalClk01_DwAfter(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                                u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    FTR_ACTOR* ftr_actor = (FTR_ACTOR*)arg;
    GAME_PLAY* play = (GAME_PLAY*)game;
    xyz_t pos;
    xyz_t save_pos = { 0.0f, 0.0f, 0.0f };
    s16 base_angle_y = RAD2SHORT_ANGLE2(DEG2RAD(ftr_actor->angle_y));
    f32 scale_x = ftr_actor->scale.x * 0.01f;
    f32 scale_y = ftr_actor->scale.y * 0.01f;
    f32 scale_z = ftr_actor->scale.z * 0.01f;
    GRAPH* graph = game->graph;

    if (joint_idx == 3) {
        Matrix_Position(&save_pos, &pos);
        Matrix_push();
        Matrix_translate(pos.x, pos.y, pos.z, MTX_LOAD);
        Matrix_RotateY(base_angle_y, MTX_MULT);
        Matrix_RotateZ(DEG2SHORT_ANGLE(90.0f) - Common_Get(time.rad_hour), MTX_MULT);
        Matrix_translate(0.0f, 0.0f, 1.0f, MTX_MULT);
        Matrix_scale(scale_x, scale_y, scale_z, MTX_MULT);

        OPEN_DISP(graph);

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        Matrix_pull();
        gSPDisplayList(NEXT_POLY_OPA_DISP, int_sum_hal_clk01_short_model);

        CLOSE_DISP(graph);
    } else if (joint_idx == 4) {
        Matrix_Position(&save_pos, &pos);
        Matrix_push();
        Matrix_translate(pos.x, pos.y, pos.z, MTX_LOAD);
        Matrix_RotateY(base_angle_y, MTX_MULT);
        Matrix_RotateZ(DEG2SHORT_ANGLE(90.0f) - Common_Get(time.rad_min), MTX_MULT);
        Matrix_translate(0.0f, 0.0f, 1.0f, MTX_MULT);
        Matrix_scale(scale_x, scale_y, scale_z, MTX_MULT);

        OPEN_DISP(graph);

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        Matrix_pull();
        gSPDisplayList(NEXT_POLY_OPA_DISP, int_sum_hal_clk01_long_model);

        CLOSE_DISP(graph);
    }

    return TRUE;
}

static int aSumHalClk01_DwBefore(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                                 u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    if (joint_idx == 3) {
        *joint_shape = NULL;
    } else if (joint_idx == 4) {
        *joint_shape = NULL;
    }

    return TRUE;
}

static void aSumHalClk01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    N64Mtx* mtx = ftr_actor->skeleton_mtx[game->frame_counter & 1];

    cKF_Si3_draw_R_SV(game, keyframe, mtx, &aSumHalClk01_DwBefore, &aSumHalClk01_DwAfter, ftr_actor);
}

extern cKF_Skeleton_R_c cKF_bs_r_int_sum_hal_clk01;
extern cKF_Animation_R_c cKF_ba_r_int_sum_hal_clk01;

static void aSumHalClk01_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_ct(keyframe, &cKF_bs_r_int_sum_hal_clk01, &cKF_ba_r_int_sum_hal_clk01, ftr_actor->joint,
                          ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_repeat(keyframe, &cKF_ba_r_int_sum_hal_clk01, NULL);
    cKF_SkeletonInfo_R_play(keyframe);
    keyframe->frame_control.speed = 0.5f;
}

static void aSumHalClk01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_play(keyframe);
}

static void aSumHalClk01_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static aFTR_vtable_c aSumHalClk01_func = {
    &aSumHalClk01_ct, &aSumHalClk01_mv, &aSumHalClk01_dw, &aSumHalClk01_dt, NULL,
};

aFTR_PROFILE iam_sum_hal_clk01 = {
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
	0,
	0,
	0,
	&aSumHalClk01_func,
    // clang-format on
};
