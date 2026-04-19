static void fTSW_ct(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static void fTSW_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    if (aFTR_CAN_PLAY_SE(ftr_actor)) {
        u32 frame = play->game_frame;

        sAdo_OngenPos((uintptr_t)ftr_actor, 0x54, &ftr_actor->position);

        if ((frame & 7) == 0) {
            xyz_t effect_pos = ftr_actor->position;

            effect_pos.y += 15.0f;
            (*Common_Get(clip).effect_clip->effect_make_proc)(eEC_EFFECT_SOBA_YUGE, effect_pos, 1, 0, game, RSV_NO, 10,
                                                              0);
        }
    }
}

static void fTSW_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

extern u8 int_tak_stew_a1_tex[];
extern u8 int_tak_stew_a2_tex_rgb_ci4[];

static u8* fTSW_texture_table[] = { int_tak_stew_a1_tex, int_tak_stew_a2_tex_rgb_ci4 };

extern Gfx int_tak_stew_nabe_on_model[];
extern Gfx int_tak_stew_nabe_onT_model[];
extern Gfx int_tak_stew_a1T_model[];

static void fTSW_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    u32 ctr_ofs;

    if (ftr_actor->ctr_type == aFTR_CTR_TYPE_GAME_PLAY) {
        ctr_ofs = play->game_frame;
    } else {
        ctr_ofs = game->frame_counter;
    }

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, fTSW_texture_table[(ctr_ofs / 6) & 1]);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_tak_stew_nabe_on_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_tak_stew_nabe_onT_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_tak_stew_a1T_model);

    CLOSE_DISP(game->graph);
}

static aFTR_vtable_c fTSW_func = {
    &fTSW_ct, &fTSW_mv, &fTSW_dw, &fTSW_dt, NULL,
};

aFTR_PROFILE iam_tak_stew = {
    // clang-format off
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	15.7f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	0,
	&fTSW_func,
    // clang-format on
};
