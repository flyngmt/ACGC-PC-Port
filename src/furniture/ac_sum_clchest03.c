static void aSumClChest03_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumClChest03_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumClChest03_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumClChest03_dt(FTR_ACTOR* ftr_actor, u8* data);

extern cKF_Skeleton_R_c cKF_bs_r_int_sum_clchest03;
extern cKF_Animation_R_c cKF_ba_r_int_sum_clchest03;

static void aSumClChest03_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_ct(keyframe, &cKF_bs_r_int_sum_clchest03, &cKF_ba_r_int_sum_clchest03, ftr_actor->joint, ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_stop(keyframe, &cKF_ba_r_int_sum_clchest03, NULL);
    keyframe->frame_control.speed = 0.0f;
    cKF_SkeletonInfo_R_play(keyframe);
}

static void aSumClChest03_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    if (Common_Get(clip).my_room_clip != NULL) {
        (*Common_Get(clip).my_room_clip->open_close_common_move_proc)(ftr_actor, my_room_actor, game, 1.0f, 16.0f);
    }
}

static void aSumClChest03_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    N64Mtx* mtx = ftr_actor->skeleton_mtx[game->frame_counter & 1];
    
    OPEN_DISP(game->graph);
    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    CLOSE_DISP(game->graph);

    cKF_Si3_draw_R_SV(game, keyframe, mtx, NULL, NULL, NULL);
}

static void aSumClChest03_dt(FTR_ACTOR* ftr_actor, u8* data) {
}

static aFTR_vtable_c aSumClChest03_func = {
	&aSumClChest03_ct,
	&aSumClChest03_mv,
	&aSumClChest03_dw,
	&aSumClChest03_dt,
	NULL,
};

aFTR_PROFILE iam_sum_clchest03 = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	18.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	aFTR_INTERACTION_STORAGE_CLOSET,
	&aSumClChest03_func,
};
