extern cKF_Skeleton_R_c cKF_bs_r_int_nog_balloon1;
extern cKF_Skeleton_R_c cKF_bs_r_int_nog_balloon2;
extern cKF_Skeleton_R_c cKF_bs_r_int_nog_balloon3;
extern cKF_Skeleton_R_c cKF_bs_r_int_nog_balloon4;
extern cKF_Skeleton_R_c cKF_bs_r_int_nog_balloon5;
extern cKF_Skeleton_R_c cKF_bs_r_int_nog_balloon6;
extern cKF_Skeleton_R_c cKF_bs_r_int_nog_balloon7;
extern cKF_Skeleton_R_c cKF_bs_r_int_nog_balloon8;

extern cKF_Animation_R_c cKF_ba_r_int_nog_balloon1;
extern cKF_Animation_R_c cKF_ba_r_int_nog_balloon2;
extern cKF_Animation_R_c cKF_ba_r_int_nog_balloon3;
extern cKF_Animation_R_c cKF_ba_r_int_nog_balloon4;
extern cKF_Animation_R_c cKF_ba_r_int_nog_balloon5;
extern cKF_Animation_R_c cKF_ba_r_int_nog_balloon6;
extern cKF_Animation_R_c cKF_ba_r_int_nog_balloon7;
extern cKF_Animation_R_c cKF_ba_r_int_nog_balloon8;

static cKF_Skeleton_R_c* fNBC_balloon_skel_table[] = {
    &cKF_bs_r_int_nog_balloon1, &cKF_bs_r_int_nog_balloon2, &cKF_bs_r_int_nog_balloon3, &cKF_bs_r_int_nog_balloon4,
    &cKF_bs_r_int_nog_balloon5, &cKF_bs_r_int_nog_balloon6, &cKF_bs_r_int_nog_balloon7, &cKF_bs_r_int_nog_balloon8,
};

static cKF_Animation_R_c* fNBC_balloon_anime_table[] = {
    &cKF_ba_r_int_nog_balloon1, &cKF_ba_r_int_nog_balloon2, &cKF_ba_r_int_nog_balloon3, &cKF_ba_r_int_nog_balloon4,
    &cKF_ba_r_int_nog_balloon5, &cKF_ba_r_int_nog_balloon6, &cKF_ba_r_int_nog_balloon7, &cKF_ba_r_int_nog_balloon8,
};

static void fNBC_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    int balloon_no = (ftr_actor->name - 0x3FC) & 7;

    cKF_SkeletonInfo_R_ct(keyframe, fNBC_balloon_skel_table[balloon_no], fNBC_balloon_anime_table[balloon_no],
                          ftr_actor->joint, ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_repeat(keyframe, fNBC_balloon_anime_table[balloon_no], NULL);
    ftr_actor->dynamic_work_f[0] = 0.0f;
    ftr_actor->dynamic_work_f[1] = 0.5f;
    keyframe->frame_control.speed = ftr_actor->dynamic_work_f[0];
    cKF_SkeletonInfo_R_play(keyframe);
}

static void fNBC_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    if (ftr_actor->switch_changed_flag) {
        ftr_actor->dynamic_work_f[1] = 1.25f;
    } else if (ftr_actor->dynamic_work_f[0] >= 1.25f) {
        ftr_actor->dynamic_work_f[1] = 0.5f;
    }

    if (ftr_actor->dynamic_work_f[0] < ftr_actor->dynamic_work_f[1]) {
        ftr_actor->dynamic_work_f[0] += 0.01f;
        if (ftr_actor->dynamic_work_f[0] > ftr_actor->dynamic_work_f[1]) {
            ftr_actor->dynamic_work_f[0] = ftr_actor->dynamic_work_f[1];
        }
    } else if (ftr_actor->dynamic_work_f[0] > ftr_actor->dynamic_work_f[1]) {
        ftr_actor->dynamic_work_f[0] -= 0.01f;
        if (ftr_actor->dynamic_work_f[0] < ftr_actor->dynamic_work_f[1]) {
            ftr_actor->dynamic_work_f[0] = ftr_actor->dynamic_work_f[1];
        }
    }

    keyframe->frame_control.speed = ftr_actor->dynamic_work_f[0];
    cKF_SkeletonInfo_R_play(keyframe);
}

static int fNBC_DrawBalloonBefore(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                                  u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    return TRUE;
}

static int fNBC_DrawBalloonAfter(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                                 u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    return TRUE;
}

static void fNBC_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    N64Mtx* mtx = ftr_actor->skeleton_mtx[game->frame_counter & 1];

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    CLOSE_DISP(game->graph);

    cKF_Si3_draw_R_SV(game, keyframe, mtx, &fNBC_DrawBalloonBefore, &fNBC_DrawBalloonAfter, ftr_actor);
}

static void fNBC_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static aFTR_vtable_c fNBC_func = {
    &fNBC_ct, &fNBC_mv, &fNBC_dw, &fNBC_dt, NULL,
};

aFTR_PROFILE iam_nog_balloon_common = {
    // clang-format off
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	15.7f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	1,
	0,
	0,
	&fNBC_func,
    // clang-format on
};
