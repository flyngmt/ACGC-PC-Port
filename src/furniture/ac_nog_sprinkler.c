static void fNS_ct(FTR_ACTOR* ftr_actor, u8* data) {
    f32 water_alpha;

    if (ftr_actor->switch_bit == TRUE) {
        ftr_actor->dynamic_work_s[0] = TRUE;
    } else {
        ftr_actor->dynamic_work_s[0] = FALSE;
    }

    if (ftr_actor->dynamic_work_s[0] == TRUE) {
        water_alpha = 100.0f;
    } else {
        water_alpha = 0.0f;
    }

    ftr_actor->dynamic_work_f[0] = water_alpha;
}

static void fNS_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    f32 target_water_alpha;

    if (ftr_actor->dynamic_work_s[0] == TRUE) {
        target_water_alpha = 100.0f;
    } else {
        target_water_alpha = 0.0f;
    }

    if (aFTR_CAN_PLAY_SE(ftr_actor)) {
        if (ftr_actor->dynamic_work_s[0] == TRUE) {
            sAdo_OngenPos((uintptr_t)ftr_actor, 0x5B, &ftr_actor->position);
        }
    }

    if (ftr_actor->dynamic_work_f[0] > target_water_alpha) {
        ftr_actor->dynamic_work_f[0] -= 4.0f;

        if (ftr_actor->dynamic_work_f[0] < target_water_alpha) {
            ftr_actor->dynamic_work_f[0] = target_water_alpha;
        }
    } else if (ftr_actor->dynamic_work_f[0] < target_water_alpha) {
        ftr_actor->dynamic_work_f[0] += 4.0f;

        if (ftr_actor->dynamic_work_f[0] > target_water_alpha) {
            ftr_actor->dynamic_work_f[0] = target_water_alpha;
        }
    } else if (ftr_actor->switch_changed_flag) {
        ftr_actor->dynamic_work_s[0] = (ftr_actor->dynamic_work_s[0] + 1) & 1;

        if (ftr_actor->dynamic_work_s[0] == TRUE) {
            sAdo_OngenTrgStart(0x16, &ftr_actor->position);
        } else {
            sAdo_OngenTrgStart(0x17, &ftr_actor->position);
        }
    }
}

static Gfx* fNS_GetTwoTileGfx(int x0, int y0, int x1, int y1, GAME* game) {
    return two_tex_scroll_dolphin(game->graph, 0, x0, y0, 16, 16, 1, x1, y1, 16, 16);
}

extern Gfx int_nog_sprinkler_bodyT_model[];
extern Gfx int_nog_sprinkler_water_model[];

static void fNS_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    u32 ctr_ofs;
    Gfx* scroll_gfx;
    u8 water_alpha;

    if (ftr_actor->ctr_type == aFTR_CTR_TYPE_GAME_PLAY) {
        ctr_ofs = play->game_frame;
    } else {
        ctr_ofs = game->frame_counter;
    }

    scroll_gfx = fNS_GetTwoTileGfx(0, 0, 0, -ctr_ofs * 10, game);

    if (ftr_actor->ctr_type == aFTR_CTR_TYPE_GAME_PLAY) {
        water_alpha = (u8)(int)ftr_actor->dynamic_work_f[0];
    } else {
        water_alpha = 100;
    }

    if (scroll_gfx != NULL) {
        OPEN_DISP(game->graph);

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(NEXT_POLY_OPA_DISP, int_nog_sprinkler_bodyT_model);
        gDPSetEnvColor(NEXT_POLY_XLU_DISP, 0, 180, 255, water_alpha);
        gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_8, scroll_gfx);
        gSPDisplayList(NEXT_POLY_XLU_DISP, int_nog_sprinkler_water_model);

        CLOSE_DISP(game->graph);
    }
}

static void fNS_dt(FTR_ACTOR* ftr_actor, u8* data) {
    ftr_actor->switch_bit = (u8)ftr_actor->dynamic_work_s[0];
}

static aFTR_vtable_c fNS_func = {
    &fNS_ct, &fNS_mv, &fNS_dw, &fNS_dt, NULL,
};

aFTR_PROFILE iam_nog_sprinkler = {
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
    0,
    0,
    aFTR_INTERACTION_START_DISABLED,
    &fNS_func,
    // clang-format on
};
