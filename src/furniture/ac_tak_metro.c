extern cKF_Skeleton_R_c cKF_bs_r_int_tak_metro;
extern cKF_Animation_R_c cKF_ba_r_int_tak_metro;

#define aTakMetro_DISABLED(ftr_actor) (ftr_actor->dynamic_work_s[1])

static void aTakMetro_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_ct(keyframe, &cKF_bs_r_int_tak_metro, &cKF_ba_r_int_tak_metro, ftr_actor->joint,
                          ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_repeat(keyframe, &cKF_ba_r_int_tak_metro, NULL);
    keyframe->frame_control.current_frame = 16.0f;
    cKF_SkeletonInfo_R_play(keyframe);
    keyframe->frame_control.speed = 0.5f;

    ftr_actor->dynamic_work_s[0] = 0;

    if (ftr_actor->switch_bit) {
        aTakMetro_DISABLED(ftr_actor) = FALSE;
    } else {
        aTakMetro_DISABLED(ftr_actor) = TRUE;
    }
}

static void aTakMetro_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    f32 frame = keyframe->frame_control.current_frame;

    if (ftr_actor->switch_changed_flag) {
        switch (aTakMetro_DISABLED(ftr_actor)) {
            case FALSE:
                if (ftr_actor->dynamic_work_s[0] == 0) {
                    ftr_actor->dynamic_work_s[0] = 1;
                    sAdo_OngenTrgStart(0x17, &ftr_actor->position);
                }
                break;
            case TRUE:
                ftr_actor->dynamic_work_s[0] = 0;
                aTakMetro_DISABLED(ftr_actor) = FALSE;
                ftr_actor->switch_bit = TRUE;
                sAdo_OngenTrgStart(0x16, &ftr_actor->position);
                break;
        }
    }

    if (ftr_actor->dynamic_work_s[0] == 1 && (frame == 17.0f || frame == 47.0f)) {
        ftr_actor->dynamic_work_s[0] = 0;
        aTakMetro_DISABLED(ftr_actor) = TRUE;
        ftr_actor->switch_bit = FALSE;
    }

    if (aTakMetro_DISABLED(ftr_actor) == FALSE) {
        cKF_SkeletonInfo_R_play(keyframe);
        keyframe->frame_control.speed = 0.5f;
    }

    if (ftr_actor->dynamic_work_s[0] == 0 && aTakMetro_DISABLED(ftr_actor) == FALSE) {
        if (frame == 60.0f) {
            if (aFTR_CAN_PLAY_SE(ftr_actor)) {
                sAdo_OngenTrgStart(0x19, &ftr_actor->position);
            }
        } else if (frame == 30.0f) {
            if (aFTR_CAN_PLAY_SE(ftr_actor)) {
                sAdo_OngenTrgStart(0x19, &ftr_actor->position);
            }
        }
    }
}

static void aTakMetro_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    N64Mtx* mtx = ftr_actor->skeleton_mtx[game->frame_counter & 1];

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    CLOSE_DISP(game->graph);

    cKF_Si3_draw_R_SV(game, keyframe, mtx, NULL, NULL, NULL);
}

static void aTakMetro_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static aFTR_vtable_c aTakMetro_func = {
    &aTakMetro_ct, &aTakMetro_mv, &aTakMetro_dw, &aTakMetro_dt, NULL,
};

aFTR_PROFILE iam_tak_metro = {
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
	&aTakMetro_func,
    // clang-format on
};

#undef aTakMetro_DISABLED
