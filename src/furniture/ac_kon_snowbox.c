static void aKonSnowbox_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aKonSnowbox_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonSnowbox_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonSnowbox_dt(FTR_ACTOR* ftr_actor, u8* data);

extern cKF_Animation_R_c cKF_ba_r_int_kon_snowbox;
extern cKF_Skeleton_R_c cKF_bs_r_int_kon_snowbox;

static void aKonSnowbox_ct(FTR_ACTOR* ftr_actor, u8* data){
    cKF_SkeletonInfo_R_c* keyf;

    keyf = &ftr_actor->keyframe;
    cKF_SkeletonInfo_R_ct(keyf, &cKF_bs_r_int_kon_snowbox, &cKF_ba_r_int_kon_snowbox, ftr_actor->joint, ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_stop(keyf, &cKF_ba_r_int_kon_snowbox, NULL);
    cKF_SkeletonInfo_R_play(keyf);
    keyf->frame_control.speed = 0.0f;

}

static void aKonSnowbox_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){

    if(Common_Get(clip).my_room_clip != NULL){
        Common_Get(clip).my_room_clip->open_close_common_move_proc(ftr_actor,my_room_actor,game,1.0f,16.0f);
    }
}

static void aKonSnowbox_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){
    N64Mtx* mtx = ftr_actor->skeleton_mtx[game->frame_counter & 1];

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP,_Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    
    CLOSE_DISP(game->graph);

    cKF_Si3_draw_R_SV(game, &ftr_actor->keyframe, mtx , NULL, NULL, NULL);
}


static void aKonSnowbox_dt(FTR_ACTOR* ftr_actor, u8* data){
    
}

static aFTR_vtable_c aKonSnowbox_func = {
	&aKonSnowbox_ct,
	&aKonSnowbox_mv,
	&aKonSnowbox_dw,
	&aKonSnowbox_dt,
	NULL,
};

aFTR_PROFILE iam_kon_snowbox = {
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
	aFTR_INTERACTION_STORAGE_CLOSET,
	&aKonSnowbox_func,
};
