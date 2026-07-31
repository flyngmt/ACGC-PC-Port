static void aSumRoboconpo_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumRoboconpo_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumRoboconpo_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumRoboconpo_dt(FTR_ACTOR* ftr_actor, u8* data);

extern cKF_Skeleton_R_c cKF_bs_r_int_sum_roboconpo;
extern cKF_Animation_R_c cKF_ba_r_int_sum_roboconpo;

extern u8 int_sum_roboconpo_face1_TA_tex_txt[];
extern u8 int_sum_roboconpo_face2_TA_tex_txt[];

static void aSumRoboconpo_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    
    cKF_SkeletonInfo_R_ct(keyframe, &cKF_bs_r_int_sum_roboconpo, &cKF_ba_r_int_sum_roboconpo, ftr_actor->joint, ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_repeat(keyframe, &cKF_ba_r_int_sum_roboconpo, NULL);
    cKF_SkeletonInfo_R_play(keyframe);
    keyframe->frame_control.speed = 0.5f;
}

static void aSumRoboconpo_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    ftr_actor->dynamic_work_f[0] += (f32)game->graph->dt_num_60fps_frames;
    while (ftr_actor->dynamic_work_f[0] >= 4.0f) {
        ftr_actor->dynamic_work_f[0] -= 4.0f;
    }

    if (Common_Get(clip).my_room_clip != NULL) {
        (*Common_Get(clip).my_room_clip->mini_disk_common_move_proc)(ftr_actor, my_room_actor, game, 0.0f, 0.0f);
    }
    
    cKF_SkeletonInfo_R_play(keyframe);
    keyframe->frame_control.speed = 0.5f;
}

static void aSumRoboconpo_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    N64Mtx* mtx = ftr_actor->skeleton_mtx[game->frame_counter & 1];

    static u8* anime_table[] = {
        int_sum_roboconpo_face1_TA_tex_txt,
        int_sum_roboconpo_face1_TA_tex_txt,
        int_sum_roboconpo_face2_TA_tex_txt,
        int_sum_roboconpo_face2_TA_tex_txt
    };
    
    OPEN_DISP(game->graph);
    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    if (ftr_actor->switch_bit != FALSE) {
        u32 idx = (int)ftr_actor->dynamic_work_f[0] % ARRAY_COUNT(anime_table);
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, anime_table[idx]);
    }
    else {
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, int_sum_roboconpo_face1_TA_tex_txt);
    }

    CLOSE_DISP(game->graph);
    cKF_Si3_draw_R_SV(game, keyframe, mtx, NULL, NULL, NULL);
}

static void aSumRoboconpo_dt(FTR_ACTOR* ftr_actor, u8* data) {
}

static aFTR_vtable_c aSumRoboconpo_func = {
	&aSumRoboconpo_ct,
	&aSumRoboconpo_mv,
	&aSumRoboconpo_dw,
	&aSumRoboconpo_dt,
	NULL,
};

aFTR_PROFILE iam_sum_roboconpo = {
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
	aFTR_INTERACTION_MUSIC_DISK,
	&aSumRoboconpo_func,
};
