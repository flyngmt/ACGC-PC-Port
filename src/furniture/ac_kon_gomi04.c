extern cKF_Skeleton_R_c cKF_bs_r_int_kon_gomi04;
extern cKF_Animation_R_c cKF_ba_r_int_kon_gomi04;

static void aKonGomi04_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_ct(keyframe, &cKF_bs_r_int_kon_gomi04, &cKF_ba_r_int_kon_gomi04, ftr_actor->joint,
                          ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_stop(keyframe, &cKF_ba_r_int_kon_gomi04, NULL);
    keyframe->frame_control.speed = 0.0f;
    cKF_SkeletonInfo_R_play(keyframe);
    ftr_actor->dynamic_work_s[0] = FALSE;
}

static void aKonGomi04_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    if (ftr_actor->dynamic_work_s[0] == TRUE) {
        int current_frame = (int)keyframe->frame_control.current_frame;
        // missing 'static' qualifier
        int frame_se_table[] = { 0, 18, 33, 48, 63, 78, 95, 107, 124 };
        // missing 'static' qualifier
        u16 se_table[] = { 0x425, 0x403, 0x404, 0x405, 0x406, 0x407, 0x408, 0x409, 0x40A };
        int i;

        for (i = 0; i < ARRAY_COUNT(frame_se_table); i++) {
            if (current_frame == frame_se_table[i] + 15) {
                sAdo_OngenTrgStart(se_table[i], &ftr_actor->position);
                break;
            }
        }

        if (cKF_SkeletonInfo_R_play(keyframe) != cKF_STATE_STOPPED) {
            keyframe->frame_control.speed = 0.5f;
        } else {
            ftr_actor->dynamic_work_s[0] = FALSE;
        }
    } else if (ftr_actor->switch_changed_flag) {
        ftr_actor->dynamic_work_s[0] = TRUE;
        keyframe->frame_control.current_frame = 1.0f;
        keyframe->frame_control.speed = 0.5f;
    }
}

static void aKonGomi04_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    N64Mtx* mtx = ftr_actor->skeleton_mtx[game->frame_counter & 1];

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    CLOSE_DISP(game->graph);

    cKF_Si3_draw_R_SV(game, keyframe, mtx, NULL, NULL, NULL);
}

static void aKonGomi04_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static aFTR_vtable_c aKonGomi04_func = {
    &aKonGomi04_ct, &aKonGomi04_mv, &aKonGomi04_dw, &aKonGomi04_dt, NULL,
};

aFTR_PROFILE iam_kon_gomi04 = {
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
	&aKonGomi04_func,
	//clang-format on
};
