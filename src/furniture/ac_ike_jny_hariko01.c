static void fIJH_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fIJH_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fIJH_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

extern cKF_Skeleton_R_c cKF_bs_r_int_ike_jny_hariko01;
extern cKF_Animation_R_c cKF_ba_r_int_ike_jny_hariko01;

static void fIJH_ct(FTR_ACTOR* ftr_actor, u8* data){
    cKF_SkeletonInfo_R_c* keyf;

    keyf = &ftr_actor->keyframe;
    cKF_SkeletonInfo_R_ct(keyf, &cKF_bs_r_int_ike_jny_hariko01, &cKF_ba_r_int_ike_jny_hariko01, ftr_actor->joint, ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_stop(keyf, &cKF_ba_r_int_ike_jny_hariko01, NULL);
    cKF_SkeletonInfo_R_play(keyf);
    keyf->frame_control.speed = 0.0f;
}


static void fIJH_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){
    cKF_SkeletonInfo_R_c* keyf;

    keyf = &ftr_actor->keyframe;
    if (ftr_actor->keyframe.frame_control.speed == 0.0f){
        if (ftr_actor->switch_changed_flag != 0){
            if (aFTR_CAN_PLAY_SE(ftr_actor)){
                sAdo_OngenTrgStart(0x7B, &ftr_actor->position);
            } 
            keyf->frame_control.current_frame = 1.0f;
            cKF_SkeletonInfo_R_play(keyf);
            keyf->frame_control.speed = 0.25f;
        }
    }
    else{
        if (cKF_SkeletonInfo_R_play(keyf) != cKF_STATE_STOPPED){
            cKF_SkeletonInfo_R_play(keyf);
            keyf->frame_control.speed = 0.25f;
        }
        else{
            keyf->frame_control.speed = 0.0f;   
        }

    }
}

static void fIJH_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){

    N64Mtx* mtx = ftr_actor->skeleton_mtx[game->frame_counter & 1];
    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP,_Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    cKF_Si3_draw_R_SV(game,&ftr_actor->keyframe,mtx,NULL,NULL,NULL);
    CLOSE_DISP(game->graph);
} 

static aFTR_vtable_c fIJH_func = {
	&fIJH_ct,
	&fIJH_mv,
	&fIJH_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_ike_jny_hariko01 = {
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
	&fIJH_func,
};
