extern cKF_Skeleton_R_c cKF_bs_r_int_nog_gong;
extern cKF_Animation_R_c cKF_ba_r_int_nog_gong;

static void aNogG_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_ct(keyframe, &cKF_bs_r_int_nog_gong, &cKF_ba_r_int_nog_gong, ftr_actor->joint, ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_stop(keyframe, &cKF_ba_r_int_nog_gong, NULL);
    cKF_SkeletonInfo_R_play(keyframe);
    keyframe->frame_control.speed = 0.5f;
}

static void aNogG_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    if (cKF_SkeletonInfo_R_play(keyframe) != cKF_STATE_STOPPED) {
        cKF_SkeletonInfo_R_play(keyframe);
        keyframe->frame_control.speed = 0.5f;
    } else if (ftr_actor->switch_changed_flag) {
        if (aFTR_CAN_PLAY_SE(ftr_actor)) {
            sAdo_OngenTrgStart(0x174, &ftr_actor->position);

            /* If the wall is ringside seating, play camera flashing effect */
            if (mRmTp_GetWallIdx() == WALL_NPC065) {
                sAdo_SysTrgStart(SE_SINGLETON(0x17E));
                (*Common_Get(clip).effect_clip->effect_make_proc)(eEC_EFFECT_FLASHC, ftr_actor->position, 2, 0, game,
                                                                  RSV_NO, 0, 0);
            }
        }

        keyframe->frame_control.current_frame = 1.0f;
        cKF_SkeletonInfo_R_play(keyframe);
        keyframe->frame_control.speed = 0.5f;
    }
}

static void aNogG_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    N64Mtx* mtx = ftr_actor->skeleton_mtx[game->frame_counter & 1];

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    CLOSE_DISP(game->graph);

    cKF_Si3_draw_R_SV(game, keyframe, mtx, NULL, NULL, NULL);
}

static aFTR_vtable_c aNogG_func = {
    &aNogG_ct, &aNogG_mv, &aNogG_dw, NULL, NULL,
};

aFTR_PROFILE iam_nog_gong = {
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
	&aNogG_func,
    // clang-format on
};
