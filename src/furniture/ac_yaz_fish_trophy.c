#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_yaz_fish_trophy_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) extern u16 int_yaz_fish_trophy_pal[] = {
    #include "assets/int_yaz_fish_trophy_pal.inc"
};
#endif
extern Gfx int_yaz_fish_trophy_cup_model[];
extern Gfx int_yaz_fish_trophy_base_model[];

static void fYFT_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, int_yaz_fish_trophy_pal);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_yaz_fish_trophy_cup_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_yaz_fish_trophy_base_model);

    CLOSE_DISP(game->graph);
}

static aFTR_vtable_c fYFT_func = {
    NULL, NULL, &fYFT_dw, NULL, NULL,
};

aFTR_PROFILE iam_yaz_fish_trophy = {
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
	1,
	0,
	0,
	&fYFT_func,
    // clang-format on
};
