extern aFTR_rig_c aKonSisiodosi_sklkey;
static void aKonSisiodosi_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aKonSisiodosi_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);


extern cKF_Skeleton_R_c cKF_bs_r_int_kon_sisiodosi;
extern cKF_Animation_R_c cKF_ba_r_int_kon_sisiodosi;

aFTR_rig_c aKonSisiodosi_sklkey= {
    &cKF_bs_r_int_kon_sisiodosi,
    &cKF_ba_r_int_kon_sisiodosi,
    1.0f,
};

static void aKonSisiodosi_ct(FTR_ACTOR* ftr_actor, u8* data){
    ftr_actor->keyframe.frame_control.current_frame = (int)(1.0f + RANDOM_F(119.0f));
}

static void aKonSisiodosi_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){

    if(cKF_FrameControl_passCheck_now(&ftr_actor->keyframe.frame_control, 20.0f)){
        if(aFTR_CAN_PLAY_SE(ftr_actor)){
            sAdo_OngenTrgStart(0x18, &ftr_actor->position);
        }
    }
}

static aFTR_vtable_c aKonSisiodosi_func = {
	&aKonSisiodosi_ct,
	&aKonSisiodosi_mv,
	NULL,
	NULL,
	NULL,
};

aFTR_PROFILE iam_kon_sisiodosi = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&aKonSisiodosi_sklkey,
	NULL,
	18.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	2,
	0,
	0,
	&aKonSisiodosi_func,
};
