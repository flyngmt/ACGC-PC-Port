static void fIMS_ct(FTR_ACTOR* ftr_actor, u8* data) {
    ftr_actor->switch_bit = FALSE;
}

static void fIMS_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (aFTR_CAN_PLAY_SE(ftr_actor)) {
        if (ftr_actor->switch_bit == TRUE) {
            sAdo_OngenPos((uintptr_t)ftr_actor, 0x5F, &ftr_actor->position);
            mPlib_Set_change_color_request();
        }

        if (ftr_actor->switch_changed_flag && ftr_actor->switch_bit == TRUE) {
            aMR_SameFurnitureSwitchOFF(0x4C7);
            ftr_actor->switch_bit = TRUE;
        }
    }
}

extern u16 int_iku_mario_star_a_pal[];
extern u16 int_iku_mario_star_b_pal[];
extern u16 int_iku_mario_star_c_pal[];
extern u16 int_iku_mario_star_d_pal[];

static u16* fIMS_palette_table[] = {
    int_iku_mario_star_a_pal,
    int_iku_mario_star_b_pal,
    int_iku_mario_star_c_pal,
    int_iku_mario_star_d_pal,
};

extern Gfx int_iku_mario_star_model[];

static void fIMS_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    int ctr_ofs;
    int pal_idx;

    if (ftr_actor->ctr_type == aFTR_CTR_TYPE_GAME_PLAY) {
        ctr_ofs = play->game_frame;
    } else {
        ctr_ofs = game->frame_counter;
    }

    if (ftr_actor->ctr_type == aFTR_CTR_TYPE_GAME_PLAY) {
        if (ftr_actor->switch_bit == TRUE) {
            pal_idx = (ctr_ofs / 10) & 3;
        } else {
            pal_idx = 0;
        }
    } else {
        pal_idx = (ctr_ofs / 10) & 3;
    }

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_9, fIMS_palette_table[pal_idx]);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_iku_mario_star_model);

    CLOSE_DISP(game->graph);
}

static aFTR_vtable_c fIMS_func = {
    &fIMS_ct, &fIMS_mv, &fIMS_dw, NULL, NULL,
};

aFTR_PROFILE iam_iku_mario_star = {
    // clang-format off
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
	&fIMS_func,
    // clang-format on
};
