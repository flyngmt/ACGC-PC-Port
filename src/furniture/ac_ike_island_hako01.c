static void fIIH_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fIIH_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fIIH_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fIIH_dt(FTR_ACTOR* ftr_actor, u8* data);

extern cKF_Animation_R_c cKF_ba_r_int_ike_island_hako01;
extern cKF_Animation_R_c cKF_ba_r_int_ike_island_hako02;
extern cKF_Skeleton_R_c cKF_bs_r_int_ike_island_hako01;

static void fIIH_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyf;
    s_xyz* joint_work;
    s_xyz* morph_work;

    joint_work = ftr_actor->joint;
    morph_work = ftr_actor->morph;
    keyf = &ftr_actor->keyframe;

    if ((Save_Get(scene_no) == SCENE_NPC_HOUSE) || (Save_Get(scene_no) == SCENE_COTTAGE_NPC)) {
        ftr_actor->switch_bit = FALSE;
    } else {
        ftr_actor->dynamic_work_s[0] = ftr_actor->switch_bit == TRUE;
    }

    if (ftr_actor->dynamic_work_s[0] == TRUE) {
        cKF_SkeletonInfo_R_ct(keyf, &cKF_bs_r_int_ike_island_hako01, &cKF_ba_r_int_ike_island_hako01, joint_work,
                              morph_work);
        cKF_SkeletonInfo_R_init_standard_stop(keyf, &cKF_ba_r_int_ike_island_hako01, NULL);
        keyf->frame_control.speed = 0.0f;
        keyf->frame_control.start_frame = 1.0f;
        keyf->frame_control.end_frame = cKF_ba_r_int_ike_island_hako01.frames;
        keyf->frame_control.current_frame = cKF_ba_r_int_ike_island_hako01.frames;
    } else {
        cKF_SkeletonInfo_R_ct(keyf, &cKF_bs_r_int_ike_island_hako01, &cKF_ba_r_int_ike_island_hako02, joint_work,
                              morph_work);
        cKF_SkeletonInfo_R_init_standard_stop(keyf, &cKF_ba_r_int_ike_island_hako02, NULL);
        keyf->frame_control.speed = 0.0f;
        keyf->frame_control.start_frame = 1.0f;
        keyf->frame_control.end_frame = cKF_ba_r_int_ike_island_hako02.frames;
        keyf->frame_control.current_frame = cKF_ba_r_int_ike_island_hako02.frames;
    }
    cKF_SkeletonInfo_R_play(keyf);
}

// Aus version reworks the treasure chest movement animation to process the state
// on the current frame instead of the previous frame's state.
#if VERSION >= VER_GAFU01_00
void fIIH_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyf = &ftr_actor->keyframe;
    int state = cKF_SkeletonInfo_R_play(keyf);

    if (state == cKF_STATE_STOPPED) {
        keyf->frame_control.speed = 0.0f;
    }

    if ((ftr_actor->switch_changed_flag != FALSE) &&
        (aMR_GetContactInfoLayer1()->contact_direction == aMR_CONTACT_DIR_FRONT) &&
        (state == cKF_STATE_STOPPED)) {
        ftr_actor->dynamic_work_s[0] = (ftr_actor->dynamic_work_s[0] + 1) & 1;
        if (ftr_actor->dynamic_work_s[0] != FALSE) {
            cKF_SkeletonInfo_R_init_standard_stop(keyf, &cKF_ba_r_int_ike_island_hako01, NULL);
            keyf->frame_control.start_frame = 1.0f;
            keyf->frame_control.end_frame = cKF_ba_r_int_ike_island_hako01.frames;
            keyf->frame_control.speed = 0.5f;
            sAdo_OngenTrgStart(0x16AU, &ftr_actor->position);
        } else {
            cKF_SkeletonInfo_R_init_standard_stop(keyf, &cKF_ba_r_int_ike_island_hako02, NULL);
            keyf->frame_control.start_frame = 1.0f;
            keyf->frame_control.end_frame = cKF_ba_r_int_ike_island_hako02.frames;
            keyf->frame_control.speed = 0.5f;
            sAdo_OngenTrgStart(0x16B, &ftr_actor->position);
        }
    }
    if (aFTR_CAN_PLAY_SE(ftr_actor)) {
        if (ftr_actor->dynamic_work_s[0] != 0) {
            if (keyf->frame_control.current_frame > 25.0f) {
                sAdo_OngenPos((uintptr_t)ftr_actor, 0x52, &ftr_actor->position);
            }
        } else if (keyf->frame_control.current_frame < 25.0f) {
            sAdo_OngenPos((uintptr_t)ftr_actor, 0x52, &ftr_actor->position);
        }
    }
}
#else
void fIIH_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyf;

    keyf = &ftr_actor->keyframe;
    if ((ftr_actor->switch_changed_flag != FALSE) &&
        (aMR_GetContactInfoLayer1()->contact_direction == aMR_CONTACT_DIR_FRONT) &&
        (0.0f == keyf->frame_control.speed)) {
        ftr_actor->dynamic_work_s[0] = (ftr_actor->dynamic_work_s[0] + 1) & 1;
        if (ftr_actor->dynamic_work_s[0] != FALSE) {
            cKF_SkeletonInfo_R_init_standard_stop(keyf, &cKF_ba_r_int_ike_island_hako01, NULL);
            keyf->frame_control.start_frame = 1.0f;
            keyf->frame_control.end_frame = cKF_ba_r_int_ike_island_hako01.frames;
            keyf->frame_control.speed = 0.5f;
            sAdo_OngenTrgStart(0x16AU, &ftr_actor->position);
        } else {
            cKF_SkeletonInfo_R_init_standard_stop(keyf, &cKF_ba_r_int_ike_island_hako02, NULL);
            keyf->frame_control.start_frame = 1.0f;
            keyf->frame_control.end_frame = cKF_ba_r_int_ike_island_hako02.frames;
            keyf->frame_control.speed = 0.5f;
            sAdo_OngenTrgStart(0x16B, &ftr_actor->position);
        }
    }
    if (aFTR_CAN_PLAY_SE(ftr_actor)) {
        if (ftr_actor->dynamic_work_s[0] != 0) {
            if (keyf->frame_control.current_frame > 25.0f) {
                sAdo_OngenPos((uintptr_t)ftr_actor, 0x52, &ftr_actor->position);
            }
        } else if (keyf->frame_control.current_frame < 25.0f) {
            sAdo_OngenPos((uintptr_t)ftr_actor, 0x52, &ftr_actor->position);
        }
    }
    if (cKF_SkeletonInfo_R_play(keyf) == cKF_STATE_STOPPED) {
        keyf->frame_control.speed = 0.0f;
    }
}
#endif

void fIIH_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    cKF_SkeletonInfo_R_c* keyf = &ftr_actor->keyframe;
    Mtx* mtx = ftr_actor->skeleton_mtx[game->frame_counter & 1];
    int scroll;
    Gfx* gfx1;
    Gfx* gfx2;
    Gfx* gfx3;

    scroll = (mSc_IS_SCENE_BASEMENT(Save_Get(scene_no)) && mEnv_PointLightMin() != 0) ? 0 : 2;

    gfx1 = fFTR_GetTwoTileGfx(32, 8, scroll, 0, 32, 8, 0, 0, play, ftr_actor, 0);
    gfx2 = fFTR_GetTwoTileGfx(32, 8, scroll, 0, 32, 8, 0, 0, play, ftr_actor, 5);
    gfx3 = fFTR_GetTwoTileGfx(32, 8, scroll, 0, 32, 8, 0, 0, play, ftr_actor, 15);

    if ((gfx1 != NULL) && (gfx2 != NULL) && (gfx3 != NULL)) {
        OPEN_DISP(game->graph);

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gSPSegment(NEXT_POLY_OPA_DISP, 8, gfx1);
        gSPSegment(NEXT_POLY_OPA_DISP, 9, gfx2);
        gSPSegment(NEXT_POLY_OPA_DISP, 10, gfx3);

        cKF_Si3_draw_R_SV(game, keyf, mtx, NULL, NULL, NULL);
        CLOSE_DISP(game->graph);
    }
}

void fIIH_dt(FTR_ACTOR* ftr_actor, u8* data) {
    if (ftr_actor->dynamic_work_s[0] != FALSE) {
        ftr_actor->switch_bit = TRUE;
    } else {
        ftr_actor->switch_bit = FALSE;
    }
}

static aFTR_vtable_c fIIH_func = {
    &fIIH_ct, &fIIH_mv, &fIIH_dw, &fIIH_dt, NULL,
};

aFTR_PROFILE iam_ike_island_hako01 = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    15.7f,
    0.009f,
    aFTR_SHAPE_TYPEA,
    mCoBG_FTR_TYPEA,
    0,
    1,
    0,
    aFTR_INTERACTION_START_DISABLED,
    &fIIH_func,
};
