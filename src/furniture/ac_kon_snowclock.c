static void aKonSnowclock_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aKonSnowclock_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonSnowclock_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonSnowclock_dt(FTR_ACTOR* ftr_actor, u8* data);

extern cKF_Animation_R_c cKF_ba_r_int_kon_snowclock;
extern cKF_Skeleton_R_c cKF_bs_r_int_kon_snowclock;
extern Gfx int_kon_snowclock_long_model[];
extern Gfx int_kon_snowclock_short_model[];

static int aKonSnowclock_DwAfter(GAME* game, cKF_SkeletonInfo_R_c* keyf, int jointNum, Gfx** joint, u8* jointFlag, void* arg,
                      s_xyz* joint1, xyz_t* trans) {


    if(jointNum == 6){
        OPEN_DISP(game->graph);

        gSPMatrix(NEXT_POLY_OPA_DISP,_Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gSPDisplayList(NEXT_POLY_OPA_DISP,int_kon_snowclock_short_model);
        
        CLOSE_DISP(game->graph);
    }
    else if(jointNum == 7){
        OPEN_DISP(game->graph);

        gSPMatrix(NEXT_POLY_OPA_DISP,_Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gSPDisplayList(NEXT_POLY_OPA_DISP,int_kon_snowclock_long_model);
        
        CLOSE_DISP(game->graph);        
    }
    return 1;
}

static int aKonSnowclock_DwBefore(GAME* game, cKF_SkeletonInfo_R_c* keyf, int jointNum, Gfx** joint, u8* jointFlag, void* arg,
                      s_xyz* joint1, xyz_t* trans) {

    if(jointNum == 6){
        joint1->z -= Common_Get(time).rad_hour;
    }
    else if(jointNum == 7){
        joint1->z -= Common_Get(time).rad_min;
    }

    return 1;
}

static void aKonSnowclock_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){
    N64Mtx* mtx = ftr_actor->skeleton_mtx[game->frame_counter & 1];
    
    cKF_Si3_draw_R_SV(game, &ftr_actor->keyframe, mtx , aKonSnowclock_DwBefore, aKonSnowclock_DwAfter, ftr_actor);
}

static void aKonSnowclock_ct(FTR_ACTOR* ftr_actor, u8* data){
    cKF_SkeletonInfo_R_c* keyf;

    keyf = &ftr_actor->keyframe;
    cKF_SkeletonInfo_R_ct(keyf, &cKF_bs_r_int_kon_snowclock, &cKF_ba_r_int_kon_snowclock, ftr_actor->joint, ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_repeat(keyf, &cKF_ba_r_int_kon_snowclock, NULL);
    cKF_SkeletonInfo_R_play(keyf);
    keyf->frame_control.speed = 0.5f;

}

static void aKonSnowclock_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){
    cKF_SkeletonInfo_R_c* keyf;

    keyf = &ftr_actor->keyframe;
    cKF_SkeletonInfo_R_play(keyf);
}

static void aKonSnowclock_dt(FTR_ACTOR* ftr_actor, u8* data){
    
}



static aFTR_vtable_c aKonSnowclock_func = {
	&aKonSnowclock_ct,
	&aKonSnowclock_mv,
	&aKonSnowclock_dw,
	&aKonSnowclock_dt,
	NULL,
};

aFTR_PROFILE iam_kon_snowclock = {
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
	0,
	&aKonSnowclock_func,
};
