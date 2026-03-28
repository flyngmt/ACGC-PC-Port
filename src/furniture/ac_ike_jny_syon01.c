static void fIJS_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fIJS_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fIJS_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

extern Gfx int_ike_jny_syon01_off_model[];
extern Gfx int_ike_jny_syon01_on_model[];

static void fIJS_ct(FTR_ACTOR* ftr_actor, u8* data){
    f32 alpha;

    if (ftr_actor->switch_bit == 1) {
        ftr_actor->dynamic_work_s[0] = TRUE;
    } else {
        ftr_actor->dynamic_work_s[0] = FALSE;
    }
    if (ftr_actor->dynamic_work_s[0] == TRUE) {
        alpha = 255.0f;
    } else {
        alpha = 0.0f;
    }
    ftr_actor->dynamic_work_f[0] = alpha;
}

static void fIJS_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    f32 alpha;

    if (ftr_actor->dynamic_work_s[0] == TRUE) {
        alpha = 255.0f;
    } else {
        alpha = 0.0f;
    }
    if (ftr_actor->dynamic_work_s[0] == TRUE) {
        if (aFTR_CAN_PLAY_SE(ftr_actor)) {
            sAdo_OngenPos((uintptr_t) ftr_actor, 0x4B, &ftr_actor->position);
        }
    }
    if (ftr_actor->dynamic_work_f[0]  > alpha) {
        ftr_actor->dynamic_work_f[0]  -= 6.0f;
        if (ftr_actor->dynamic_work_f[0]  < alpha) {
            ftr_actor->dynamic_work_f[0]  = alpha;
        }
    } else if (ftr_actor->dynamic_work_f[0]  < alpha) {
        ftr_actor->dynamic_work_f[0]  += 6.0f;
        if (ftr_actor->dynamic_work_f[0]  > alpha) {
            ftr_actor->dynamic_work_f[0]  = alpha;
        }
    } else if (ftr_actor->switch_changed_flag != FALSE) {
        ftr_actor->dynamic_work_s[0] = ((ftr_actor->dynamic_work_s[0] + 1) & 1);
    }
}

static Gfx* fIJS_GetTwoTileGfx(int x0, int y0, int x1, int y1, GAME* game) { 
    return two_tex_scroll_dolphin(game->graph, 0, x0, y0, 32, 32, 1, x1, y1, 32, 32);
}

static void fIJS_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    u32 ctr_ofs;
    Gfx* scroll;
    u8 alpha;

    if (ftr_actor->ctr_type == aFTR_CTR_TYPE_GAME_PLAY) {
        ctr_ofs = play->game_frame;
    } else {
        ctr_ofs = game->frame_counter;
    }

    scroll = fIJS_GetTwoTileGfx(0,ctr_ofs * 6, 0, 0, game);

    if (ftr_actor->ctr_type == aFTR_CTR_TYPE_GAME_PLAY) {
        alpha = (u8)(int)ftr_actor->dynamic_work_f[0];
    } else {
        alpha = 255;
    }

    if (scroll != NULL) {
        OPEN_DISP(game->graph); 

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(NEXT_POLY_OPA_DISP, int_ike_jny_syon01_on_model);
        gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0,255, 120,160,255, alpha);
        gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_9, scroll); 
        gSPDisplayList(NEXT_POLY_XLU_DISP, int_ike_jny_syon01_off_model);
 
        CLOSE_DISP(game->graph);
    }
}

static aFTR_vtable_c fIJS_func = {
	&fIJS_ct,
	&fIJS_mv,
	&fIJS_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_ike_jny_syon01 = {
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
	0,
	0,
	0,
	&fIJS_func,
};
