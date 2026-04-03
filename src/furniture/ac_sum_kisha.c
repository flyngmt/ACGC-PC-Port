static void aSumKisha_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumKisha_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumKisha_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumKisha_dt(FTR_ACTOR* ftr_actor, u8* data);

extern cKF_Skeleton_R_c cKF_bs_r_int_sum_kisha;
extern cKF_Animation_R_c cKF_ba_r_int_sum_kisha;

static void aSumKisha_ControlSwitchSE(FTR_ACTOR* ftr_actor){
    if (ftr_actor->switch_bit != FALSE){
        sAdo_OngenTrgStart(0x16,&ftr_actor->position);
    }
    else{
        sAdo_OngenTrgStart(0x17,&ftr_actor->position);
    }
}

static void aSumKisha_ChangeSwitch(FTR_ACTOR* ftr_actor){
    if (ftr_actor->switch_changed_flag != FALSE){
        aSumKisha_ControlSwitchSE(ftr_actor);
    }
} 

static void aSumKisha_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_ct(keyframe, &cKF_bs_r_int_sum_kisha, &cKF_ba_r_int_sum_kisha, ftr_actor->joint, ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_repeat(keyframe, &cKF_ba_r_int_sum_kisha, NULL);
    cKF_SkeletonInfo_R_play(keyframe);
    keyframe->frame_control.speed = 0.5f;
    
    if (ftr_actor->switch_bit != FALSE) {
        ftr_actor->dynamic_work_f[0] = 0.5f;
    }
    else {
        ftr_actor->dynamic_work_f[0] = 0.0f;
    }
}

static void aSumKisha_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    aSumKisha_ChangeSwitch(ftr_actor);

    if (ftr_actor->switch_bit != FALSE) {
        add_calc(&ftr_actor->dynamic_work_f[0], 0.5f, 1.0f - sqrtf(0.95), 0.25f, 0.0005f);

        if (aFTR_CAN_PLAY_SE(ftr_actor)) {
            sAdo_OngenPos((uintptr_t)ftr_actor, 3, &ftr_actor->position);
        }
    }
    else {
        add_calc(&ftr_actor->dynamic_work_f[0], 0.0f, 1.0f - sqrtf(0.9), 0.25f, 0.0005f);
    }

    keyframe->frame_control.speed = ftr_actor->dynamic_work_f[0];
    cKF_SkeletonInfo_R_play(keyframe);
}

static void aSumKisha_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    Mtx* mtx = ftr_actor->skeleton_mtx[game->frame_counter & 1];
    
    OPEN_DISP(game->graph);
    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    CLOSE_DISP(game->graph);

    cKF_Si3_draw_R_SV(game, keyframe, mtx, NULL, NULL, NULL);
}

static void aSumKisha_dt(FTR_ACTOR* ftr_actor, u8* data) {
}

static aFTR_vtable_c aSumKisha_func = {
	&aSumKisha_ct,
	&aSumKisha_mv,
	&aSumKisha_dw,
	&aSumKisha_dt,
	NULL,
};

aFTR_PROFILE iam_sum_kisha = {
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
	aFTR_SHAPE_TYPEC,
	mCoBG_FTR_TYPEC,
	0,
	0,
	0,
	0,
	&aSumKisha_func,
};
