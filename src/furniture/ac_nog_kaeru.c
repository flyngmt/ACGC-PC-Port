extern aFTR_rig_c aNogKaeru_key_anime_data;

extern cKF_Skeleton_R_c cKF_bs_r_int_nog_kaeru;
extern cKF_Animation_R_c cKF_ba_r_int_nog_kaeru;

aFTR_rig_c aNogKaeru_key_anime_data= {
    &cKF_bs_r_int_nog_kaeru,
    &cKF_ba_r_int_nog_kaeru,
    1.0f,
};

static void fNKR_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (aFTR_CAN_PLAY_SE(ftr_actor)) {
        sAdo_RoomIncectPos((uintptr_t)ftr_actor, 0x41, &ftr_actor->position);
    }
}

static aFTR_vtable_c fNKR_func = {
    NULL, &fNKR_mv, NULL, NULL, NULL,
};

aFTR_PROFILE iam_nog_kaeru = {
    // clang-format off
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&aNogKaeru_key_anime_data,
	NULL,
	30.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	2,
	0,
	aFTR_INTERACTION_FISH,
	&fNKR_func,
    // clang-format on
};
