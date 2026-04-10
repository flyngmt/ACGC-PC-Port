static void fIKD_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fIKD_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

extern Gfx int_ike_kama_danro01_on_model[];
extern Gfx int_ike_kama_danrofire_off_model[];

static void fIKD_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){

    if(aFTR_CAN_PLAY_SE(ftr_actor)){
        sAdo_OngenPos((uintptr_t)ftr_actor, 0x46, &ftr_actor->position);
    }
}
static Gfx* fIKD_GetTwoTileGfx(int x0, int y0, int x1, int y1, GAME* game) { 
    return two_tex_scroll_dolphin(game->graph, 0, x0, y0, 32, 32, 1, x1, y1, 32, 64);
}

static void fIKD_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){
    GAME_PLAY* play = (GAME_PLAY*)game;
    int ctr;
    Gfx* gfx;

    if(ftr_actor->ctr_type == aFTR_CTR_TYPE_GAME_PLAY){
        ctr = play->game_frame;
    }
    else{
        ctr = game->frame_counter;
    } 

    gfx = fIKD_GetTwoTileGfx(0,0,0,-ctr << 2,game);

    if(gfx != NULL){
        OPEN_DISP(game->graph);
        gSPMatrix(NEXT_POLY_OPA_DISP,_Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPMatrix(NEXT_POLY_XLU_DISP,_Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_9, gfx);
        gSPDisplayList(NEXT_POLY_OPA_DISP,int_ike_kama_danro01_on_model);
        gSPDisplayList(NEXT_POLY_XLU_DISP,int_ike_kama_danrofire_off_model);
        CLOSE_DISP(game->graph);
    }
}

static aFTR_vtable_c fIKD_func = {
	NULL,
	&fIKD_mv,
	&fIKD_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_ike_kama_danro01 = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	41.0f,
	0.01f,
	aFTR_SHAPE_TYPEB_0,
	mCoBG_FTR_TYPEB_0,
	0,
	0,
	0,
	0,
	&fIKD_func,
};
