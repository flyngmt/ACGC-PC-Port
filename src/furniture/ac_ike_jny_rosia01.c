static void aIkeJnyRosia01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aIkeJnyRosia01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aIkeJnyRosia01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aIkeJnyRosia01_dt(FTR_ACTOR* ftr_actor, u8* data);

extern cKF_Animation_R_c cKF_ba_r_int_ike_jny_rosia01;
extern cKF_Skeleton_R_c cKF_bs_r_int_ike_jny_rosia01;

static void aIkeJnyRosia01_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyf = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_ct(keyf, &cKF_bs_r_int_ike_jny_rosia01, &cKF_ba_r_int_ike_jny_rosia01, ftr_actor->joint,
                          ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_stop(keyf, &cKF_ba_r_int_ike_jny_rosia01, NULL);
    keyf->frame_control.speed = 0.0f;
    keyf->frame_control.start_frame = 1.0f;
    keyf->frame_control.end_frame = cKF_ba_r_int_ike_jny_rosia01.frames;
    ftr_actor->dynamic_work_s[0] = (ftr_actor->switch_bit == TRUE);
    if (ftr_actor->dynamic_work_s[0] == 0) {
        keyf->frame_control.current_frame = cKF_ba_r_int_ike_jny_rosia01.frames;
    }
    cKF_SkeletonInfo_R_play(keyf);
}

static void aIkeJnyRosia01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyf = &ftr_actor->keyframe;

    if ((ftr_actor->switch_changed_flag != FALSE) && (keyf->frame_control.speed == 0.0f)) {
        ftr_actor->dynamic_work_s[0] = ftr_actor->dynamic_work_s[0] + 1 & 1;
        if (ftr_actor->dynamic_work_s[0] != 0) {
            keyf->frame_control.speed = 0.5f;
            keyf->frame_control.start_frame = cKF_ba_r_int_ike_jny_rosia01.frames;
            keyf->frame_control.end_frame = 1.0f;
            sAdo_OngenTrgStart(0x7A, &ftr_actor->position);
        } else {
            keyf->frame_control.speed = 0.5f;
            keyf->frame_control.start_frame = 1.0f;
            keyf->frame_control.end_frame = cKF_ba_r_int_ike_jny_rosia01.frames;
            sAdo_OngenTrgStart(0x7A, &ftr_actor->position);
        }
    }
    if (cKF_SkeletonInfo_R_play(keyf) == cKF_STATE_STOPPED) {
        keyf->frame_control.speed = 0.0f;
    }
}

static void aIkeJnyRosia01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    N64Mtx* mtx = ftr_actor->skeleton_mtx[game->frame_counter & 1];
    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    cKF_Si3_draw_R_SV(game, &ftr_actor->keyframe, mtx, NULL, NULL, NULL);
    CLOSE_DISP(game->graph);
}

static void aIkeJnyRosia01_dt(FTR_ACTOR* ftr_actor, u8* data){
    if (ftr_actor->dynamic_work_s[0] != FALSE){
        ftr_actor->switch_bit = TRUE;
    }
    else{
        ftr_actor->switch_bit = FALSE;
    }
}

static aFTR_vtable_c aIkeJnyRosia01_func = {
	&aIkeJnyRosia01_ct,
	&aIkeJnyRosia01_mv,
	&aIkeJnyRosia01_dw,
	&aIkeJnyRosia01_dt,
	NULL,
};

aFTR_PROFILE iam_ike_jny_rosia01 = {
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
	aFTR_SHAPE_TYPEB_0,
	mCoBG_FTR_TYPEB_0,
	0,
	0,
	0,
	0,
	&aIkeJnyRosia01_func,
};
