extern Gfx int_sum_x_clk_evw_model[];
extern Gfx int_sum_x_clk_short_model[];
extern Gfx int_sum_x_clk_long_model[];

static int aSumXClk_DwAfter(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
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

    if (joint_idx == 6) {
        _texture_z_light_fog_prim_xlu(graph);
        Setpos_HiliteReflect_xlu_init(&ftr_actor->position, play);
        Matrix_Position(&save_pos, &pos);
        Matrix_push();
        Matrix_translate(pos.x, pos.y, pos.z, MTX_LOAD);
        Matrix_RotateY(base_angle_y, MTX_MULT);
        Matrix_RotateZ(DEG2SHORT_ANGLE(90.0f), MTX_MULT);
        Matrix_scale(scale_x, scale_y, scale_z, MTX_MULT);

        OPEN_DISP(graph);

        gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        Matrix_pull();
        gSPDisplayList(NEXT_POLY_XLU_DISP, int_sum_x_clk_evw_model);

        CLOSE_DISP(graph);
    } else if (joint_idx == 3) {
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
        gSPDisplayList(NEXT_POLY_OPA_DISP, int_sum_x_clk_short_model);

        CLOSE_DISP(graph);
    } else if (joint_idx == 7) {
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
        gSPDisplayList(NEXT_POLY_OPA_DISP, int_sum_x_clk_long_model);

        CLOSE_DISP(graph);
    }

    return TRUE;
}

static int aSumXClk_DwBefore(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                             u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    if (joint_idx == 3 || joint_idx == 7 || joint_idx == 6) {
        *joint_shape = NULL;
    }

    return TRUE;
}

static void aSumXClk_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    N64Mtx* mtx = ftr_actor->skeleton_mtx[game->frame_counter & 1];

    cKF_Si3_draw_R_SV(game, keyframe, mtx, &aSumXClk_DwBefore, &aSumXClk_DwAfter, ftr_actor);
}

extern cKF_Skeleton_R_c cKF_bs_r_int_sum_x_clk;
extern cKF_Animation_R_c cKF_ba_r_int_sum_x_clk;

static void aSumXClk_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_ct(keyframe, &cKF_bs_r_int_sum_x_clk, &cKF_ba_r_int_sum_x_clk, ftr_actor->joint,
                          ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_repeat(keyframe, &cKF_ba_r_int_sum_x_clk, NULL);
    cKF_SkeletonInfo_R_play(keyframe);
    keyframe->frame_control.speed = 0.5f;
}

static void aSumXClk_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (Common_Get(clip).my_room_clip != NULL) {
        cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
        aMR_clock_info_c* clock_info = Common_Get(clip).my_room_clip->clock_info_p;

        if (clock_info->tick_stop) {
            cKF_SkeletonInfo_R_init_standard_repeat(keyframe, &cKF_ba_r_int_sum_x_clk, NULL);
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

static void aSumXClk_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static aFTR_vtable_c aSumXClk_func = {
    &aSumXClk_ct, &aSumXClk_mv, &aSumXClk_dw, &aSumXClk_dt, NULL,
};

aFTR_PROFILE iam_sum_x_clk = {
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
	&aSumXClk_func,
    // clang-format on
};
