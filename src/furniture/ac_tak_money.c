extern cKF_Skeleton_R_c cKF_bs_r_int_tak_money;
extern cKF_Animation_R_c cKF_ba_r_int_tak_money;

static void fTMny_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_ct(keyframe, &cKF_bs_r_int_tak_money, &cKF_ba_r_int_tak_money, ftr_actor->joint,
                          ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_repeat(keyframe, &cKF_ba_r_int_tak_money, NULL);
    cKF_SkeletonInfo_R_play(keyframe);
    keyframe->frame_control.speed = 0.0f;
}

static f32 fTMny_GetSpeed(FTR_ACTOR* ftr_actor) {
    f32 spd_x = ABS(ftr_actor->position.x - ftr_actor->last_position.x);
    f32 spd_z = ABS(ftr_actor->position.z - ftr_actor->last_position.z);
    f32 speed_sq = spd_x * spd_x + spd_z * spd_z;

    return sqrtf(speed_sq);
}

static void fTMny_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    aMR_contact_info_c* contact_info = aMR_GetContactInfoLayer1();
    f32 speed = fTMny_GetSpeed(ftr_actor);

    if (contact_info != NULL) {
        speed = (0.1f + speed / 1.55f) * 0.5f;

        if (ftr_actor->state == aFTR_STATE_WAIT_PUSH || ftr_actor->state == aFTR_STATE_WAIT_PUSH2 ||
            ftr_actor->state == aFTR_STATE_WAIT_PUSH3 || ftr_actor->state == aFTR_STATE_PUSH) {
            switch (contact_info->contact_direction) {
                case aMR_CONTACT_DIR_LEFT:
                    // play animation normally
                    keyframe->frame_control.speed = speed;
                    keyframe->frame_control.start_frame = 1.0f;
                    keyframe->frame_control.end_frame = cKF_ba_r_int_tak_money.frames;
                    break;
                case aMR_CONTACT_DIR_RIGHT:
                    // play animation but in reverse
                    keyframe->frame_control.speed = speed;
                    keyframe->frame_control.start_frame = cKF_ba_r_int_tak_money.frames;
                    keyframe->frame_control.end_frame = 1.0f;
                    break;
                default:
                    // no animation from other directions
                    keyframe->frame_control.speed = 0.0f;
                    break;
            }
        } else if (ftr_actor->state == aFTR_STATE_WAIT_PULL || ftr_actor->state == aFTR_STATE_WAIT_PULL2 ||
                   ftr_actor->state == aFTR_STATE_PULL) {
            switch (contact_info->contact_direction) {
                case aMR_CONTACT_DIR_RIGHT:
                    // play animation normally
                    keyframe->frame_control.speed = speed;
                    keyframe->frame_control.start_frame = 1.0f;
                    keyframe->frame_control.end_frame = cKF_ba_r_int_tak_money.frames;
                    break;
                case aMR_CONTACT_DIR_LEFT:
                    // play animation but in reverse
                    keyframe->frame_control.speed = speed;
                    keyframe->frame_control.start_frame = cKF_ba_r_int_tak_money.frames;
                    keyframe->frame_control.end_frame = 1.0f;
                    break;
                default:
                    // no animation from other directions
                    keyframe->frame_control.speed = 0.0f;
                    break;
            }
        } else {
            keyframe->frame_control.speed = 0.0f;
        }
    } else {
        keyframe->frame_control.speed = 0.0f;
    }

    cKF_SkeletonInfo_R_play(keyframe);
}

static void fTMny_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    N64Mtx* mtx = ftr_actor->skeleton_mtx[game->frame_counter & 1];

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    CLOSE_DISP(game->graph);

    cKF_Si3_draw_R_SV(game, keyframe, mtx, NULL, NULL, NULL);
}

static aFTR_vtable_c fTMny_func = {
    &fTMny_ct, &fTMny_mv, &fTMny_dw, NULL, NULL,
};

aFTR_PROFILE iam_tak_money = {
    // clang-format off
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	40.0f,
	0.01f,
	aFTR_SHAPE_TYPEB_0,
	mCoBG_FTR_TYPEB_0,
	0,
	0,
	0,
	0,
	&fTMny_func,
    // clang-format on
};
