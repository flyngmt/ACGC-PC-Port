extern Gfx sugi_barbecue_model[];
extern Gfx sugi_barbecue_b_model[];

static void gSBBQ_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    if (aFTR_CAN_PLAY_SE(ftr_actor)) {
        u32 ctr = play->game_frame;

        sAdo_OngenPos((uintptr_t)ftr_actor, 0x55, &ftr_actor->position);
        if ((ctr & 15) == 0) {
            xyz_t pos = ftr_actor->position;

            pos.y += 30.0f;
            (*Common_Get(clip).effect_clip->effect_make_proc)(eEC_EFFECT_SOBA_YUGE, pos, 1, 0, game, RSV_NO, 9, 0);
        }
    }
}

static aFTR_vtable_c gSBBQ_func = {
    NULL, &gSBBQ_mv, NULL, NULL, NULL,
};

aFTR_PROFILE iam_sugi_barbecue = {
    // clang-format off
	sugi_barbecue_model,
	sugi_barbecue_b_model,
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
	&gSBBQ_func,
    // clang-format on
};
