// Aus version changed the naming to use their 'standard'
// It also updates the mv func to remove the animation frame logic.
// The dw function was updated to use the game frame instead of an internal counter.
#if VERSION >= VER_GAFU01_00
static void fST01_ct(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static void fST01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (ftr_actor->switch_bit) {
        if (aFTR_CAN_PLAY_SE(ftr_actor)) {
            sAdo_OngenPos((uintptr_t)ftr_actor, 5, &ftr_actor->position);
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

extern u8 int_sum_tv01_front1_TA_tex_txt[];
extern u8 int_sum_tv01_front2_TA_tex_txt[];
extern u8 int_sum_tv01_front3_TA_tex_txt[];
extern u8 int_sum_tv01_front4_TA_tex_txt[];

extern Gfx int_sum_tv01_on_model[];
extern Gfx int_sum_tv01_off_model[];

static u8* fST01_on_anime[] = {
    int_sum_tv01_front2_TA_tex_txt, int_sum_tv01_front2_TA_tex_txt, int_sum_tv01_front2_TA_tex_txt,
    int_sum_tv01_front3_TA_tex_txt, int_sum_tv01_front3_TA_tex_txt, int_sum_tv01_front3_TA_tex_txt,
    int_sum_tv01_front2_TA_tex_txt, int_sum_tv01_front2_TA_tex_txt, int_sum_tv01_front2_TA_tex_txt,
    int_sum_tv01_front3_TA_tex_txt, int_sum_tv01_front3_TA_tex_txt, int_sum_tv01_front3_TA_tex_txt,
    int_sum_tv01_front2_TA_tex_txt, int_sum_tv01_front2_TA_tex_txt, int_sum_tv01_front2_TA_tex_txt,
    int_sum_tv01_front3_TA_tex_txt, int_sum_tv01_front3_TA_tex_txt, int_sum_tv01_front3_TA_tex_txt,
    int_sum_tv01_front4_TA_tex_txt, int_sum_tv01_front4_TA_tex_txt, int_sum_tv01_front4_TA_tex_txt,
    int_sum_tv01_front4_TA_tex_txt, int_sum_tv01_front2_TA_tex_txt, int_sum_tv01_front2_TA_tex_txt,
    int_sum_tv01_front2_TA_tex_txt, int_sum_tv01_front2_TA_tex_txt, int_sum_tv01_front2_TA_tex_txt,
};

static void fST01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    u32 ctr_ofs;
    u8* tex;

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    if (ftr_actor->switch_bit) {
        if (ftr_actor->ctr_type == aFTR_CTR_TYPE_GAME_PLAY) {
            ctr_ofs = play->game_frame;
        } else {
            ctr_ofs = game->frame_counter;
        }

        tex = fST01_on_anime[(ctr_ofs >> 1) % ARRAY_COUNT(fST01_on_anime)];
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, tex);
    } else {
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, int_sum_tv01_front1_TA_tex_txt);
    }

    gSPDisplayList(NEXT_POLY_OPA_DISP, int_sum_tv01_on_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_sum_tv01_off_model);

    CLOSE_DISP(game->graph);
}

static void fST01_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static aFTR_vtable_c fST01_func = {
    &fST01_ct, &fST01_mv, &fST01_dw, &fST01_dt, NULL,
};

aFTR_PROFILE iam_sum_tv01 = {
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
	&fST01_func,
    // clang-format on
};
#else
static void aSumTv01_ct(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static void aSumTv01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (ftr_actor->switch_bit) {
        if (aFTR_CAN_PLAY_SE(ftr_actor)) {
            sAdo_OngenPos((uintptr_t)ftr_actor, 5, &ftr_actor->position);
        }

        ftr_actor->tex_animation.frame++;
        if (ftr_actor->tex_animation.frame >= 54 || ftr_actor->tex_animation.frame < 0) {
            ftr_actor->tex_animation.frame = 0;
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

extern u8 int_sum_tv01_front1_TA_tex_txt[];
extern u8 int_sum_tv01_front2_TA_tex_txt[];
extern u8 int_sum_tv01_front3_TA_tex_txt[];
extern u8 int_sum_tv01_front4_TA_tex_txt[];

extern Gfx int_sum_tv01_on_model[];
extern Gfx int_sum_tv01_off_model[];

static u8* aSumTv01_on_anime[] = {
    int_sum_tv01_front2_TA_tex_txt, int_sum_tv01_front2_TA_tex_txt, int_sum_tv01_front2_TA_tex_txt,
    int_sum_tv01_front3_TA_tex_txt, int_sum_tv01_front3_TA_tex_txt, int_sum_tv01_front3_TA_tex_txt,
    int_sum_tv01_front2_TA_tex_txt, int_sum_tv01_front2_TA_tex_txt, int_sum_tv01_front2_TA_tex_txt,
    int_sum_tv01_front3_TA_tex_txt, int_sum_tv01_front3_TA_tex_txt, int_sum_tv01_front3_TA_tex_txt,
    int_sum_tv01_front2_TA_tex_txt, int_sum_tv01_front2_TA_tex_txt, int_sum_tv01_front2_TA_tex_txt,
    int_sum_tv01_front3_TA_tex_txt, int_sum_tv01_front3_TA_tex_txt, int_sum_tv01_front3_TA_tex_txt,
    int_sum_tv01_front4_TA_tex_txt, int_sum_tv01_front4_TA_tex_txt, int_sum_tv01_front4_TA_tex_txt,
    int_sum_tv01_front4_TA_tex_txt, int_sum_tv01_front2_TA_tex_txt, int_sum_tv01_front2_TA_tex_txt,
    int_sum_tv01_front2_TA_tex_txt, int_sum_tv01_front2_TA_tex_txt, int_sum_tv01_front2_TA_tex_txt,
};

static void aSumTv01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    if (ftr_actor->switch_bit) {
        int frame = (s16)(ftr_actor->tex_animation.frame >> 1);
        u8* tex = aSumTv01_on_anime[frame];

        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, tex);
    } else {
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, int_sum_tv01_front1_TA_tex_txt);
    }

    gSPDisplayList(NEXT_POLY_OPA_DISP, int_sum_tv01_on_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_sum_tv01_off_model);

    CLOSE_DISP(game->graph);
}

static void aSumTv01_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static aFTR_vtable_c aSumTv01_func = {
    &aSumTv01_ct, &aSumTv01_mv, &aSumTv01_dw, &aSumTv01_dt, NULL,
};

aFTR_PROFILE iam_sum_tv01 = {
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
	&aSumTv01_func,
    // clang-format on
};
#endif
