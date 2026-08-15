extern aFTR_rig_c aKonCracker_sklkey;
static void aKonCracker_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aKonCracker_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonCracker_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonCracker_dt(FTR_ACTOR* ftr_actor, u8* data);

extern cKF_Skeleton_R_c cKF_bs_r_int_kon_cracker;
extern cKF_Animation_R_c cKF_ba_r_int_kon_cracker;

aFTR_rig_c aKonCracker_sklkey = {
    &cKF_bs_r_int_kon_cracker,
    &cKF_ba_r_int_kon_cracker,
    1.0f,
};

static void aKonCracker_ct(FTR_ACTOR* ftr_actor, u8* data) {
    
}

static void aKonCracker_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_FrameControl_c* frame_control = &ftr_actor->keyframe.frame_control;

    if (aFTR_CAN_PLAY_SE(ftr_actor) && (cKF_FrameControl_passCheck_now(frame_control, 8.0f) ||
                                        cKF_FrameControl_passCheck_now(frame_control, 24.0f))) {
        sAdo_OngenTrgStart(0x812C, &ftr_actor->position);
    }
}

static void aKonCracker_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    
}

static void aKonCracker_dt(FTR_ACTOR* ftr_actor, u8* data) {
    
}

static aFTR_vtable_c aKonCracker_func = {
	&aKonCracker_ct,
	&aKonCracker_mv,
	&aKonCracker_dw,
	&aKonCracker_dt,
	NULL,
};

aFTR_PROFILE iam_kon_cracker = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&aKonCracker_sklkey,
	NULL,
	18.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	0,
	&aKonCracker_func,
};
