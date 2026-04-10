static void fTL_ct(FTR_ACTOR* ftr_actor, u8* data) {
    f32 l;

    if (ftr_actor->switch_bit == TRUE) {
        ftr_actor->dynamic_work_s[0] = TRUE;
    } else {
        ftr_actor->dynamic_work_s[0] = FALSE;
    }

    if (ftr_actor->dynamic_work_s[0] == TRUE) {
        l = 126.0f;
    } else {
        l = 0.0f;
    }

    ftr_actor->dynamic_work_f[0] = l;
}

static void fTL_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    f32 l;

    if (ftr_actor->dynamic_work_s[0] == 1) {
        l = 126.0f;
    } else {
        l = 0.0f;
    }

    if (ftr_actor->dynamic_work_s[0] == 1) {
        if (aFTR_CAN_PLAY_SE(ftr_actor)) {
            sAdo_OngenPos((uintptr_t)ftr_actor, 0x4A, &ftr_actor->position);
        }
    }

    if (ftr_actor->dynamic_work_f[0] > l) {
        ftr_actor->dynamic_work_f[0] -= 4.0f;
        if (ftr_actor->dynamic_work_f[0] < l) {
            ftr_actor->dynamic_work_f[0] = l;
        }
    } else if (ftr_actor->dynamic_work_f[0] < l) {
        ftr_actor->dynamic_work_f[0] += 4.0f;
        if (ftr_actor->dynamic_work_f[0] > l) {
            ftr_actor->dynamic_work_f[0] = l;
        }
    } else {
        if (ftr_actor->switch_changed_flag) {
            ftr_actor->dynamic_work_s[0] = (ftr_actor->dynamic_work_s[0] + 1) & 1;
        }
    }
}

static Gfx* fTL_GetTwoTileGfx(int x0, int y0, int x1, int y1, GAME* game) {
    return two_tex_scroll_dolphin(game->graph, 0, x0, y0, 8, 8, 1, x1, y1, 8, 8);
}

extern Gfx int_tak_lion_on_model[];
extern Gfx int_tak_lion_onT_model[];
extern Gfx int_tak_lion_alphaT_model[];

static void fTL_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    u32 ctr_ofs;
    Gfx* scroll_gfx;
    u8 l;

    if (ftr_actor->ctr_type == aFTR_CTR_TYPE_GAME_PLAY) {
        ctr_ofs = play->game_frame;
    } else {
        ctr_ofs = game->frame_counter;
    }

    scroll_gfx = fTL_GetTwoTileGfx(-ctr_ofs, ctr_ofs * 4, ctr_ofs, ctr_ofs * 4, game);

    if (ftr_actor->ctr_type == aFTR_CTR_TYPE_GAME_PLAY) {
        l = (int)ftr_actor->dynamic_work_f[0];
    } else {
        l = 156;
    }

    if (scroll_gfx != NULL) {
        OPEN_DISP(game->graph);

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(NEXT_POLY_OPA_DISP, int_tak_lion_on_model);
        gSPDisplayList(NEXT_POLY_OPA_DISP, int_tak_lion_onT_model);
        gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, l, 255, 255, 255, 127);
        gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_8, scroll_gfx);
        gSPDisplayList(NEXT_POLY_XLU_DISP, int_tak_lion_alphaT_model);

        CLOSE_DISP(game->graph);
    }
}

static void fTL_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static void fTL_dt(FTR_ACTOR* ftr_actor, u8* data) {
    ftr_actor->switch_bit = ftr_actor->dynamic_work_s[0];
}

static aFTR_vtable_c fTL_func = {
    &fTL_ct, &fTL_mv, &fTL_dw, &fTL_dt, NULL,
};

aFTR_PROFILE iam_tak_lion = {
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
	0,
	&fTL_func,
    // clang-format on
};
