static void aSumgenji_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumgenji_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumgenji_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumgenji_dt(FTR_ACTOR* ftr_actor, u8* data);

extern cKF_Animation_R_c cKF_ba_r_int_sum_genji;
extern cKF_Skeleton_R_c cKF_bs_r_int_sum_genji;

static void aSumgenji_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_ct(keyframe, &cKF_bs_r_int_sum_genji, &cKF_ba_r_int_sum_genji, ftr_actor->joint, ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_repeat(keyframe, &cKF_ba_r_int_sum_genji, NULL);
    cKF_SkeletonInfo_R_play(keyframe);
    keyframe->frame_control.speed = 0.5f;
}
static Gfx* aSumgenji_GetPrimDisp(GAME* game, u8 prim_r, u8 prim_g, u8 prim_b, u8 prim_a, u8 prim_l, u8 env_r, u8 env_g, u8 env_b, u8 env_a) {
    Gfx* g = GRAPH_ALLOC_TYPE(game->graph, Gfx, 4);

    gDPPipeSync(g + 0);
    gDPSetPrimColor(g + 1, 0, prim_l, prim_r, prim_g, prim_b, prim_a);
    gDPSetEnvColor(g + 2, env_r, env_g, env_b, env_a);
    gSPEndDisplayList(g + 3);

    return g;
}

static void aSumgenji_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    N64Mtx* mtx = ftr_actor->skeleton_mtx[game->frame_counter & 1];
    static u8 prim_a_table[] = {
       255, 255, 255, 255,
       240, 225, 210, 195,
       180, 165, 150, 135,
       120, 105,  90,  75,
        50,  35,  20,   5,
         0,   0,   0,   0,
         0,   0,   0,   0,
         0,   0,   0,   0,
         0,   0,   0,   0,
         0,   0,   0,   0,
         0,   0,   0,   0,
         0,   0,   0,   0,
         5,  20,  35,  50,
        75,  90, 105, 120,
       135, 150, 165, 180,
       195, 210, 225, 240,
       255, 255, 255, 255
    };
    int prim_a_idx = ABS((int)ftr_actor->dynamic_work_s[0] % ARRAY_COUNT(prim_a_table));
    Gfx* prim_disp = aSumgenji_GetPrimDisp(game, 255, 180, 0, prim_a_table[prim_a_idx], 255, 0, 255, 0, 255);

    OPEN_DISP(game->graph);

    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, prim_disp);
    gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_8, prim_disp);
    
    CLOSE_DISP(game->graph);
    
    cKF_Si3_draw_R_SV(game, keyframe, mtx, NULL, NULL, NULL);
}

static void aSumgenji_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_play(keyframe);
    keyframe->frame_control.speed = 0.5f;
    ftr_actor->dynamic_work_s[0]++;
}

static void aSumgenji_dt(FTR_ACTOR* ftr_actor, u8* data) {
}

static aFTR_vtable_c aSumgenji_func = {
	&aSumgenji_ct,
	&aSumgenji_mv,
	&aSumgenji_dw,
	&aSumgenji_dt,
	NULL,
};

aFTR_PROFILE iam_sum_genji = {
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
	&aSumgenji_func,
};
