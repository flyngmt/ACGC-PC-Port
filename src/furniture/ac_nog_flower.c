static void fNFL_ct(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static void fNFL_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    // nothing
}

static void fNFL_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

extern Gfx int_nog_pansy_model[];
extern Gfx int_nog_pansyT_model[];
extern Gfx int_nog_cosmos_model[];
extern Gfx int_nog_cosmosT_model[];
extern Gfx int_nog_turip_model[];
extern Gfx int_nog_turipT_model[];

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_flower_a_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_flower_a_pal[] = {
    #include "assets/int_nog_flower_a_pal.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_flower_b_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_flower_b_pal[] = {
    #include "assets/int_nog_flower_b_pal.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_flower_c_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_flower_c_pal[] = {
    #include "assets/int_nog_flower_c_pal.inc"
};
#endif

typedef struct {
    Gfx* model0;
    Gfx* model1;
    u16* pal;
} fNLF_model_info_c;

static fNLF_model_info_c fNFL_model_data[] = {
    { int_nog_pansy_model, int_nog_pansyT_model, int_nog_flower_a_pal },
    { int_nog_pansy_model, int_nog_pansyT_model, int_nog_flower_b_pal },
    { int_nog_pansy_model, int_nog_pansyT_model, int_nog_flower_c_pal },
    { int_nog_cosmos_model, int_nog_cosmosT_model, int_nog_flower_a_pal },
    { int_nog_cosmos_model, int_nog_cosmosT_model, int_nog_flower_b_pal },
    { int_nog_cosmos_model, int_nog_cosmosT_model, int_nog_flower_c_pal },
    { int_nog_turip_model, int_nog_turipT_model, int_nog_flower_a_pal },
    { int_nog_turip_model, int_nog_turipT_model, int_nog_flower_b_pal },
    { int_nog_turip_model, int_nog_turipT_model, int_nog_flower_c_pal },
};

static void fNFL_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    int idx = ftr_actor->name - 0x4DE;
    Gfx* model0 = fNFL_model_data[idx].model0;
    Gfx* model1 = fNFL_model_data[idx].model1;
    u16* pal = fNFL_model_data[idx].pal;

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, pal);
    gSPDisplayList(NEXT_POLY_OPA_DISP, model0);
    gSPDisplayList(NEXT_POLY_OPA_DISP, model1);

    CLOSE_DISP(game->graph);
}

static aFTR_vtable_c fNFL_func = {
    &fNFL_ct, &fNFL_mv, &fNFL_dw, &fNFL_dt, NULL,
};

aFTR_PROFILE iam_nog_flower = {
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
	aFTR_INTERACTION_NO_COLLISION,
	&fNFL_func,
    // clang-format on
};
