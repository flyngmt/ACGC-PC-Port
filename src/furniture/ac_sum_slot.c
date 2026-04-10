extern cKF_Skeleton_R_c cKF_bs_r_int_sum_slot;
extern cKF_Animation_R_c cKF_ba_r_int_sum_slot;

static void aSumSlot_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_ct(keyframe, &cKF_bs_r_int_sum_slot, &cKF_ba_r_int_sum_slot, ftr_actor->joint, ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_stop(keyframe, &cKF_ba_r_int_sum_slot, NULL);
    keyframe->frame_control.speed = 0.5f;
    cKF_SkeletonInfo_R_play(keyframe);
    keyframe->frame_control.speed = 0.0f;
    ftr_actor->dynamic_work_s[0] = FALSE;
}

static void aSumSlot_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    if (ftr_actor->dynamic_work_s[0] == TRUE) {
        if (cKF_SkeletonInfo_R_play(keyframe) != cKF_STATE_STOPPED) {
            keyframe->frame_control.speed = 0.5f;
            ftr_actor->tex_animation.frame++;

            if (ftr_actor->tex_animation.frame >= 242 || ftr_actor->tex_animation.frame < 0) {
                ftr_actor->tex_animation.frame = 0;
            }

            if (aFTR_CAN_PLAY_SE(ftr_actor)) {
                sAdo_OngenPos((uintptr_t)ftr_actor, 2, &ftr_actor->position);
            }
        } else {
            ftr_actor->dynamic_work_s[0] = FALSE;
        }
    } else if (ftr_actor->switch_changed_flag) {
        ftr_actor->dynamic_work_s[0] = TRUE;
        keyframe->frame_control.current_frame = 1.0f;
        cKF_SkeletonInfo_R_play(keyframe);
        keyframe->frame_control.speed = 0.5f;
    }
}

extern u8 int_sum_slot_reel1_TA_tex_txt[];
extern u8 int_sum_slot_reel2_TA_tex_txt[];

static u8* aSumSlot_anim[] = { int_sum_slot_reel1_TA_tex_txt, int_sum_slot_reel2_TA_tex_txt };

static u8 aSumSlot_aime_idx[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
};

static void aSumSlot_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    int mtx_idx = game->frame_counter & 1;
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    Mtx* mtx = ftr_actor->skeleton_mtx[mtx_idx];
    int idx = ftr_actor->tex_animation.frame >> 1;

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, aSumSlot_anim[aSumSlot_aime_idx[idx]]);

    CLOSE_DISP(game->graph);

    cKF_Si3_draw_R_SV(game, keyframe, mtx, NULL, NULL, NULL);
}

static void aSumSlot_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static aFTR_vtable_c aSumSlot_func = {
    &aSumSlot_ct, &aSumSlot_mv, &aSumSlot_dw, &aSumSlot_dt, NULL,
};

aFTR_PROFILE iam_sum_slot = {
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
	&aSumSlot_func,
    // clang-format on
};
