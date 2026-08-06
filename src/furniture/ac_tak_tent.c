#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_tent_on_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_tent_on_pal[] = {
    #include "assets/int_tak_tent_on_pal.inc"
};
#endif

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_tak_tent_off_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_tak_tent_off_pal[] = {
    #include "assets/int_tak_tent_off_pal.inc"
};
#endif


static void fTTnt_ct(FTR_ACTOR* ftr_actor, u8* data) {
    ftr_actor->pal_p = (u16*)zelda_malloc_align(16 * sizeof(u16), 32);
    fFTR_MorphHousepaletteCt(ftr_actor->pal_p, int_tak_tent_off_pal, int_tak_tent_on_pal, ftr_actor);
}

static void fTTnt_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    fFTR_MorphHousePalette(ftr_actor->pal_p, int_tak_tent_off_pal, int_tak_tent_on_pal, ftr_actor);
}

static void fTTnt_dt(FTR_ACTOR* ftr_actor, u8* data) {
    if (ftr_actor->pal_p != NULL) {
        zelda_free(ftr_actor->pal_p);
    }
}

extern Gfx int_tak_tent_green_on_model[];
extern Gfx int_tak_tent_body_onT_model[];
extern Gfx int_tak_tent_etc_onT_model[];
extern Gfx int_tak_tent_light_offT_model[];

static void fTTnt_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    u16* pal_p = ftr_actor->pal_p;

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, pal_p);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_tak_tent_green_on_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_tak_tent_body_onT_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_tak_tent_etc_onT_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_tak_tent_light_offT_model);

    CLOSE_DISP(game->graph);
}

static aFTR_vtable_c fTTnt_func = {
    &fTTnt_ct, &fTTnt_mv, &fTTnt_dw, &fTTnt_dt, NULL,
};

aFTR_PROFILE iam_tak_tent = {
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
	aFTR_INTERACTION_TOGGLE,
	&fTTnt_func,
    // clang-format on
};
