static int aSumroboclk_DwAfter(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                               u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    return TRUE;
}

static int aSumroboclk_DwBefore(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                                u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    if (joint_idx == 4) {
        joint_rot->z -= Common_Get(time.rad_hour);
    } else if (joint_idx == 3) {
        joint_rot->z -= Common_Get(time.rad_min);
    }

    return TRUE;
}

extern u8 int_sum_roboclk_eye1_TA_tex_txt[];
extern u8 int_sum_roboclk_eye2_TA_tex_txt[];

static void aSumroboclk_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    int mtx_idx = game->frame_counter & 1;
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    N64Mtx* mtx = ftr_actor->skeleton_mtx[mtx_idx];
    int tex_idx = (int)ftr_actor->dynamic_work_f[0] & 3;
    static u8* texture_table[] = {
        int_sum_roboclk_eye1_TA_tex_txt,
        int_sum_roboclk_eye1_TA_tex_txt,
        int_sum_roboclk_eye2_TA_tex_txt,
        int_sum_roboclk_eye2_TA_tex_txt,
    };

    OPEN_DISP(game->graph);

    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, texture_table[tex_idx]);

    CLOSE_DISP(game->graph);

    cKF_Si3_draw_R_SV(game, keyframe, mtx, &aSumroboclk_DwBefore, &aSumroboclk_DwAfter, ftr_actor);
}

extern cKF_Skeleton_R_c cKF_bs_r_int_sum_roboclk;
extern cKF_Animation_R_c cKF_ba_r_int_sum_roboclk;

static void aSumroboclk_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_ct(keyframe, &cKF_bs_r_int_sum_roboclk, &cKF_ba_r_int_sum_roboclk, ftr_actor->joint,
                          ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_repeat(keyframe, &cKF_ba_r_int_sum_roboclk, NULL);
    cKF_SkeletonInfo_R_play(keyframe);
    keyframe->frame_control.speed = 0.5f;
}

static void aSumroboclk_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    ftr_actor->dynamic_work_f[0] += (f32)game->graph->dt_num_60fps_frames;
    while (ftr_actor->dynamic_work_f[0] >= 4.0f) {
        ftr_actor->dynamic_work_f[0] -= 4.0f;
    }

    cKF_SkeletonInfo_R_play(keyframe);
}

static void aSumroboclk_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static aFTR_vtable_c aSumroboclk_func = {
    &aSumroboclk_ct, &aSumroboclk_mv, &aSumroboclk_dw, &aSumroboclk_dt, NULL,
};

aFTR_PROFILE iam_sum_roboclk = {
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
	&aSumroboclk_func,
    // clang-format on
};
