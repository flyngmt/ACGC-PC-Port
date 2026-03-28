extern cKF_Skeleton_R_c cKF_bs_r_int_tak_ham1;
extern cKF_Animation_R_c cKF_ba_r_int_tak_ham1;

static void fTHM1_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_ct(keyframe, &cKF_bs_r_int_tak_ham1, &cKF_ba_r_int_tak_ham1, ftr_actor->joint, ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_repeat(keyframe, &cKF_ba_r_int_tak_ham1, NULL);
    cKF_SkeletonInfo_R_play(keyframe);
}

static void fTHM1_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    keyframe->frame_control.speed = 1.0f;
    cKF_SkeletonInfo_R_play(keyframe);
    sAdo_OngenPos((uintptr_t)ftr_actor, 0x56, &ftr_actor->position);
}

extern u8 int_tak_ham1_a1_tex_txt[];
extern u8 int_tak_ham1_a2_tex_pic_ci4[];

static u8* tak_ham1_texture_table[] = { int_tak_ham1_a1_tex_txt, int_tak_ham1_a2_tex_pic_ci4 };

static void fTHM1_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    Mtx* mtx = ftr_actor->skeleton_mtx[game->frame_counter & 1];

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8,
               tak_ham1_texture_table[(game->frame_counter / 5) % ARRAY_COUNT(tak_ham1_texture_table)]);

    CLOSE_DISP(game->graph);

    cKF_Si3_draw_R_SV(game, keyframe, mtx, NULL, NULL, ftr_actor);
}

static aFTR_vtable_c fTHM1_func = {
    &fTHM1_ct, &fTHM1_mv, &fTHM1_dw, NULL, NULL,
};

aFTR_PROFILE iam_tak_ham1 = {
    // clang-format off
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
	&fTHM1_func,
    // clang-format on
};
