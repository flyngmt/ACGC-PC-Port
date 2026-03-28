static void aSumTukutuku_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumTukutuku_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumTukutuku_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

extern cKF_Animation_R_c cKF_ba_r_int_sum_tukutuku;
extern cKF_Skeleton_R_c cKF_bs_r_int_sum_tukutuku;

static void aSumTukutuku_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_ct(keyframe, &cKF_bs_r_int_sum_tukutuku, &cKF_ba_r_int_sum_tukutuku, ftr_actor->joint, ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_stop(keyframe, &cKF_ba_r_int_sum_tukutuku, NULL);
    cKF_SkeletonInfo_R_play(keyframe);
    keyframe->frame_control.speed = 0.0f;
}

static void aSumTukutuku_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe;
    int valid;

    if (aFTR_CAN_PLAY_SE(ftr_actor)) {
        keyframe = &ftr_actor->keyframe;
        valid = sAdo_RoomIncectPos((uintptr_t)ftr_actor, 63, &ftr_actor->position);

        if (valid != 0) {
            cKF_SkeletonInfo_R_init_standard_stop(keyframe, &cKF_ba_r_int_sum_tukutuku, NULL);
            keyframe->frame_control.speed = 0.5f;
        } 
        cKF_SkeletonInfo_R_play(keyframe);
    }

}

static void aSumTukutuku_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    Mtx* mtx = ftr_actor->skeleton_mtx[game->frame_counter & 1];

    cKF_Si3_draw_R_SV(game, keyframe, mtx, NULL, NULL, ftr_actor);
}

static aFTR_vtable_c aSumTukutuku_func = {
	&aSumTukutuku_ct,
	&aSumTukutuku_mv,
	&aSumTukutuku_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_sum_tukutuku = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	30.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	2,
	0,
	aFTR_INTERACTION_INSECT,
	&aSumTukutuku_func,
};
