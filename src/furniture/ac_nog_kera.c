extern aFTR_rig_c aNogKera_key_anime_data;

extern cKF_Skeleton_R_c cKF_bs_r_int_nog_kera;
extern cKF_Animation_R_c cKF_ba_r_int_nog_kera;

aFTR_rig_c aNogKera_key_anime_data= {
    &cKF_bs_r_int_nog_kera,
    &cKF_ba_r_int_nog_kera,
    1.0f,
};

static void fNgKr_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (aFTR_CAN_PLAY_SE(ftr_actor)) {
        sAdo_RoomIncectPos((uintptr_t)ftr_actor, 0x42, &ftr_actor->position);
    }
}

static aFTR_vtable_c fNgKr_func = {
    NULL, &fNgKr_mv, NULL, NULL, NULL,
};

aFTR_PROFILE iam_nog_kera = {
    // clang-format off
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    &aNogKera_key_anime_data,
    NULL,
    30.0f,
    0.01f,
    aFTR_SHAPE_TYPEA,
    mCoBG_FTR_TYPEA,
    0,
    2,
    0,
    aFTR_INTERACTION_INSECT,
    &fNgKr_func,
    // clang-format on
};
