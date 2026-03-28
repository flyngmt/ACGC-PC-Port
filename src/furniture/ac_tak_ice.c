extern cKF_Skeleton_R_c cKF_bs_r_int_tak_ice;
extern cKF_Animation_R_c cKF_ba_r_int_tak_ice;

static void fTIC_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_ct(keyframe, &cKF_bs_r_int_tak_ice, &cKF_ba_r_int_tak_ice, ftr_actor->joint, ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_repeat(keyframe, &cKF_ba_r_int_tak_ice, NULL);
    cKF_SkeletonInfo_R_play(keyframe);

    if (ftr_actor->switch_bit == TRUE) {
        keyframe->frame_control.speed = 0.5f;
        ftr_actor->dynamic_work_f[0] = 1.0f;
    } else {
        keyframe->frame_control.speed = 0.0f;
        ftr_actor->dynamic_work_f[0] = 0.0f;
    }
}

static void fTIC_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    f32 target = ftr_actor->switch_bit ? 1.0f : 0.0f;
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    if (ftr_actor->dynamic_work_f[0] < target) {
        ftr_actor->dynamic_work_f[0] += 0.01f;

        if (ftr_actor->dynamic_work_f[0] > target) {
            ftr_actor->dynamic_work_f[0] = target;
        }
    } else if (ftr_actor->dynamic_work_f[0] > target) {
        ftr_actor->dynamic_work_f[0] -= 0.01f;

        if (ftr_actor->dynamic_work_f[0] < target) {
            ftr_actor->dynamic_work_f[0] = target;
        }
    }

    keyframe->frame_control.speed = ftr_actor->dynamic_work_f[0] * 0.5f;
    cKF_SkeletonInfo_R_play(keyframe);

    if (aFTR_CAN_PLAY_SE(ftr_actor)) {
        if (ftr_actor->switch_changed_flag) {
            if (ftr_actor->switch_bit == TRUE) {
                sAdo_OngenTrgStart(0x16, &ftr_actor->position);
            } else {
                sAdo_OngenTrgStart(0x17, &ftr_actor->position);
            }
        }

        if (ftr_actor->dynamic_work_f[0] >= 0.01f && ftr_actor->switch_bit == TRUE) {
            sAdo_OngenPos((uintptr_t)ftr_actor, 0x51, &ftr_actor->position);
        }
    }
}

static int fTIC_DrawBefore(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                           u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    FTR_ACTOR* ftr_actor = (FTR_ACTOR*)arg;
    GAME_PLAY* play = (GAME_PLAY*)game;

    if (joint_idx == 3 || joint_idx == 4) {
        *joint_shape = NULL;
    }

    return TRUE;
}

static Gfx* fTIC_GetTwoTileGfx(int x0, int y0, int x1, int y1, GAME* game) {
    return two_tex_scroll_dolphin(game->graph, 0, x0, y0, 8, 32, 1, x1, y1, 8, 32);
}

extern Gfx int_tak_ice_block_model[];
extern Gfx int_tak_ice_yuki_model[];

static int fTIC_DrawAfter(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape, u8* joint_flags,
                          void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    FTR_ACTOR* ftr_actor = (FTR_ACTOR*)arg;
    cKF_SkeletonInfo_R_c* ftr_keyframe = &ftr_actor->keyframe;
    GAME_PLAY* play = (GAME_PLAY*)game;
    u32 ctr_ofs;

    if (ftr_actor->ctr_type == aFTR_CTR_TYPE_GAME_PLAY) {
        ctr_ofs = play->game_frame;
    } else {
        ctr_ofs = game->frame_counter;
    }

    if (joint_idx == 3) {
        OPEN_DISP(game->graph);

        gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(NEXT_POLY_XLU_DISP, int_tak_ice_block_model);

        CLOSE_DISP(game->graph);
    } else if (joint_idx == 4) {
        Gfx* scroll_gfx = fTIC_GetTwoTileGfx(0, ctr_ofs * 8, 0, 0, game);
        u8 a = (int)((ftr_keyframe->frame_control.speed / 0.5f) * 255.0f);

        if (scroll_gfx != NULL) {
            OPEN_DISP(game->graph);

            gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 255, 255, 255, a);
            gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_9, scroll_gfx);
            gSPDisplayList(NEXT_POLY_XLU_DISP, int_tak_ice_yuki_model);

            CLOSE_DISP(game->graph);
        }
    }

    return TRUE;
}

static void fTIC_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    Mtx* mtx = ftr_actor->skeleton_mtx[game->frame_counter & 1];

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    CLOSE_DISP(game->graph);

    cKF_Si3_draw_R_SV(game, keyframe, mtx, &fTIC_DrawBefore, &fTIC_DrawAfter, ftr_actor);
}

static aFTR_vtable_c fTIC_func = {
    &fTIC_ct, &fTIC_mv, &fTIC_dw, NULL, NULL,
};

aFTR_PROFILE iam_tak_ice = {
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
    aFTR_SHAPE_TYPEA,
    mCoBG_FTR_TYPEA,
    0,
    2,
    0,
    aFTR_INTERACTION_START_DISABLED,
    &fTIC_func,
};
