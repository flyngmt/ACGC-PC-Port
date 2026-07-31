extern cKF_Skeleton_R_c cKF_bs_r_int_tak_toudai;
extern cKF_Animation_R_c cKF_ba_r_int_tak_toudai;

static void fTTD_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_ct(keyframe, &cKF_bs_r_int_tak_toudai, &cKF_ba_r_int_tak_toudai, ftr_actor->joint,
                          ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_repeat(keyframe, &cKF_ba_r_int_tak_toudai, NULL);
    cKF_SkeletonInfo_R_play(keyframe);

    if (ftr_actor->switch_bit == TRUE) {
        keyframe->frame_control.speed = 1.0f;
        ftr_actor->dynamic_work_f[0] = 1.0f;
    } else {
        keyframe->frame_control.speed = 0.0f;
        ftr_actor->dynamic_work_f[0] = 0.0f;
    }
}

static void fTTD_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    f32 target;

    if (ftr_actor->switch_bit == TRUE) {
        target = 1.0f;
    } else {
        target = 0.0f;
    }

    add_calc(&ftr_actor->dynamic_work_f[0], target, 0.3f, 0.3f, 0.0001f);
    keyframe->frame_control.speed = ftr_actor->dynamic_work_f[0] * 0.5f * 2.0f;
    cKF_SkeletonInfo_R_play(keyframe);
}

static int fTTD_DrawBefore(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                           u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    FTR_ACTOR* ftr_actor = (FTR_ACTOR*)arg;
    GAME_PLAY* play = (GAME_PLAY*)game;

    if (joint_idx == 3 || joint_idx == 7) {
        *joint_shape = NULL;
    }

    return TRUE;
}

extern Gfx int_tak_toudai_evw_model[];
extern Gfx int_tak_toudai_right_model[];

static int fTTD_DrawAfter(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape, u8* joint_flags,
                          void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    FTR_ACTOR* ftr_actor = (FTR_ACTOR*)arg;
    GAME_PLAY* play = (GAME_PLAY*)game;
    u8 l = (int)(ftr_actor->dynamic_work_f[0] * 255.0f);

    if (joint_idx == 3) {
        OPEN_DISP(game->graph);

        gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(NEXT_POLY_XLU_DISP, int_tak_toudai_evw_model);

        CLOSE_DISP(game->graph);
    } else if (joint_idx == 7) {
        OPEN_DISP(game->graph);

        gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, l, 255, 255, 150, 255);
        gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(NEXT_POLY_XLU_DISP, int_tak_toudai_right_model);

        CLOSE_DISP(game->graph);
    }

    return TRUE;
}

static void fTTD_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    N64Mtx* mtx = ftr_actor->skeleton_mtx[game->frame_counter & 1];

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    CLOSE_DISP(game->graph);

    cKF_Si3_draw_R_SV(game, keyframe, mtx, &fTTD_DrawBefore, &fTTD_DrawAfter, ftr_actor);
}

static aFTR_vtable_c fTTD_func = {
    &fTTD_ct, &fTTD_mv, &fTTD_dw, NULL, NULL,
};

aFTR_PROFILE iam_tak_toudai = {
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
	2,
	0,
	aFTR_INTERACTION_TOGGLE,
	&fTTD_func,
    // clang-format on
};
