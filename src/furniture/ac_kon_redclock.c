static void aKonRedclock_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aKonRedclock_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonRedclock_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonRedclock_dt(FTR_ACTOR* ftr_actor, u8* data);

extern cKF_Animation_R_c cKF_ba_r_int_kon_redclock;
extern cKF_Skeleton_R_c cKF_bs_r_int_kon_redclock;

static int aKonRedclock_DwAfter(GAME* game, cKF_SkeletonInfo_R_c* keyf, int jointNum, Gfx** joint, u8* jointFlag, void* arg,
                      s_xyz* joint1, xyz_t* trans) {
    return 1;
}

static int aKonRedclock_DwBefore(GAME* game, cKF_SkeletonInfo_R_c* keyf, int jointNum, Gfx** joint, u8* jointFlag, void* arg,
                      s_xyz* joint1, xyz_t* trans) {

    if(jointNum == 3){
        joint1->z -= Common_Get(time).rad_hour;
    }
    else if(jointNum == 4){
        joint1->z -= Common_Get(time).rad_min;
    }

    return 1;
}

static void aKonRedclock_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){
    N64Mtx* mtx = ftr_actor->skeleton_mtx[game->frame_counter & 1];
    
    cKF_Si3_draw_R_SV(game, &ftr_actor->keyframe, mtx , aKonRedclock_DwBefore, aKonRedclock_DwAfter, ftr_actor);
}

static void aKonRedclock_ct(FTR_ACTOR* ftr_actor, u8* data){
    cKF_SkeletonInfo_R_c* keyf;

    keyf = &ftr_actor->keyframe;
    cKF_SkeletonInfo_R_ct(keyf, &cKF_bs_r_int_kon_redclock, &cKF_ba_r_int_kon_redclock, ftr_actor->joint, ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_repeat(keyf, &cKF_ba_r_int_kon_redclock, NULL);
    cKF_SkeletonInfo_R_play(keyf);
    keyf->frame_control.speed = 0.5f;

}

static void aKonRedclock_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){
    cKF_SkeletonInfo_R_c* keyf;

    keyf = &ftr_actor->keyframe;
    cKF_SkeletonInfo_R_play(keyf);
}

static void aKonRedclock_dt(FTR_ACTOR* ftr_actor, u8* data){
    
}

static aFTR_vtable_c aKonRedclock_func = {
	&aKonRedclock_ct,
	&aKonRedclock_mv,
	&aKonRedclock_dw,
	&aKonRedclock_dt,
	NULL,
};

aFTR_PROFILE iam_kon_redclock = {
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
	2,
	0,
	0,
	&aKonRedclock_func,
};
