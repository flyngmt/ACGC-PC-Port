static void fITT_ct(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static void fITT_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (ftr_actor->switch_bit) {
        if (aFTR_CAN_PLAY_SE(ftr_actor)) {
            sAdo_OngenPos((uintptr_t)ftr_actor, 0x5E, &ftr_actor->position);
        }
    }

    if (ftr_actor->switch_changed_flag) {
        if (ftr_actor->switch_bit) {
            sAdo_OngenTrgStart(0x16, &ftr_actor->position);
        } else {
            sAdo_OngenTrgStart(0x17, &ftr_actor->position);
        }
    }
}

extern u8 int_iku_turkey_TV_f_tex_txt[];
extern u8 int_iku_turkey_TV_g_tex_txt[];
extern u8 int_iku_turkey_TV_h_tex_txt[];
extern u8 int_iku_turkey_TV_i_tex_txt[];

extern Gfx int_iku_turkey_TV_model_a_model[];
extern Gfx int_iku_turkey_TV_model_b_model[];

static u8* fITT_switch_on_texture_table[] = {
    int_iku_turkey_TV_g_tex_txt,
    int_iku_turkey_TV_h_tex_txt,
    int_iku_turkey_TV_i_tex_txt,
    int_iku_turkey_TV_h_tex_txt,
};

static void fITT_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    u32 ctr_ofs;

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    if (ftr_actor->switch_bit) {
        u32 ofs;

        if (ftr_actor->ctr_type == aFTR_CTR_TYPE_GAME_PLAY) {
            ctr_ofs = play->game_frame;
        } else {
            ctr_ofs = game->frame_counter;
        }

        /* Store TV on texture */
        ofs = (int)ctr_ofs / 6;
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8,
                   fITT_switch_on_texture_table[ofs % ARRAY_COUNT(fITT_switch_on_texture_table)]);
    } else {
        /* Store TV off texture */
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, int_iku_turkey_TV_f_tex_txt);
    }

    gSPDisplayList(NEXT_POLY_OPA_DISP, int_iku_turkey_TV_model_b_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_iku_turkey_TV_model_a_model);

    CLOSE_DISP(game->graph);
}

static void fITT_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static aFTR_vtable_c fITT_func = {
    &fITT_ct, &fITT_mv, &fITT_dw, &fITT_dt, NULL,
};

aFTR_PROFILE iam_iku_turkey_TV = {
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
	aFTR_INTERACTION_START_DISABLED,
	&fITT_func,
    // clang-format on
};
