static void fRT_ct(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static void fRT_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    aMR_RadioCommonMove(ftr_actor, my_room_actor);

    if (ftr_actor->switch_bit == TRUE) {
        int ticks = graph_dt_60hz_ticks(game, &ftr_actor->dynamic_work_f[0]);
        int t;
        for (t = 0; t < ticks; t++) {
            if (ftr_actor->dynamic_work_s[0] >= 36) {
                xyz_t pos = ftr_actor->position;

                pos.y -= 3.0f;

                (*Common_Get(clip).effect_clip->effect_make_proc)(eEC_EFFECT_KONPU, pos, 1,
                                                                  ftr_actor->s_angle_y + DEG2SHORT_ANGLE(337.5f), game,
                                                                  FTR_START(FTR_RADIO_TEST), 1, 0);
                ftr_actor->dynamic_work_s[0] = 0;
            }

            ftr_actor->dynamic_work_s[0]++;
        }
    }
}

extern Gfx radio_DL_model[];
#ifdef TARGET_PC
extern u16 obj_e_radio_pal[];
#else
ATTRIBUTE_ALIGN(32) static u16 radio_pal[] = {
#include "assets/radio_pal.inc"
};
#endif

static void fRT_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    OPEN_DISP(game->graph);

    Matrix_RotateY(DEG2SHORT_ANGLE(-157.5f), MTX_MULT);
    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
#ifdef TARGET_PC
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, obj_e_radio_pal);
#else
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, radio_pal);
#endif
    gSPDisplayList(NEXT_POLY_OPA_DISP, radio_DL_model);

    CLOSE_DISP(game->graph);
}

static void fRT_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static aFTR_vtable_c fRT_func = {
    &fRT_ct, &fRT_mv, &fRT_dw, &fRT_dt, NULL,
};

aFTR_PROFILE iam_radio_test = {
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
	0.009f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	aFTR_INTERACTION_RADIO_AEROBICS,
	&fRT_func,
    // clang-format on
};
