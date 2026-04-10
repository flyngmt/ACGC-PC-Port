// Aus version changed the naming to use their 'standard'
// It also updates the mv func to remove the animation frame logic.
// The dw function was updated to use the game frame instead of an internal counter.
#if VERSION >= VER_GAFU01_00
static void fKST_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fKST_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fKST_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fKST_dt(FTR_ACTOR* ftr_actor, u8* data);

extern u8 int_kon_snowtv07a_TA_tex_txt[];
extern u8 int_kon_snowtv07b_TA_tex_txt[];
extern u8 int_kon_snowtv07c_TA_tex_txt[];
extern u8 int_kon_snowtv07d_TA_tex_txt[];

extern Gfx int_kon_snowtv_body_model[];
extern Gfx int_kon_snowtv_face_model[];

u8* fKST_on_anime_table[] = {
    int_kon_snowtv07b_TA_tex_txt, int_kon_snowtv07b_TA_tex_txt, int_kon_snowtv07b_TA_tex_txt,
    int_kon_snowtv07b_TA_tex_txt, int_kon_snowtv07b_TA_tex_txt, int_kon_snowtv07b_TA_tex_txt,
    int_kon_snowtv07b_TA_tex_txt, int_kon_snowtv07b_TA_tex_txt, int_kon_snowtv07b_TA_tex_txt,
    int_kon_snowtv07b_TA_tex_txt, int_kon_snowtv07c_TA_tex_txt, int_kon_snowtv07c_TA_tex_txt,
    int_kon_snowtv07c_TA_tex_txt, int_kon_snowtv07c_TA_tex_txt, int_kon_snowtv07c_TA_tex_txt,
    int_kon_snowtv07c_TA_tex_txt, int_kon_snowtv07c_TA_tex_txt, int_kon_snowtv07c_TA_tex_txt,
    int_kon_snowtv07c_TA_tex_txt, int_kon_snowtv07c_TA_tex_txt, int_kon_snowtv07d_TA_tex_txt,
    int_kon_snowtv07d_TA_tex_txt, int_kon_snowtv07d_TA_tex_txt, int_kon_snowtv07d_TA_tex_txt,
    int_kon_snowtv07d_TA_tex_txt, int_kon_snowtv07d_TA_tex_txt, int_kon_snowtv07d_TA_tex_txt,
    int_kon_snowtv07d_TA_tex_txt, int_kon_snowtv07d_TA_tex_txt, int_kon_snowtv07d_TA_tex_txt,
};

static void fKST_ct(FTR_ACTOR* ftr_actor, u8* data) {
}

static void fKST_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {

    if (ftr_actor->switch_bit != FALSE) {
        if (aFTR_CAN_PLAY_SE(ftr_actor)) {
            sAdo_OngenPos((uintptr_t)ftr_actor, 0x2B, &ftr_actor->position);
        }
    }

    if (ftr_actor->switch_changed_flag != FALSE) {
        if (ftr_actor->switch_bit != FALSE) {
            sAdo_OngenTrgStart(0x16, &ftr_actor->position);
        } else {
            sAdo_OngenTrgStart(0x17, &ftr_actor->position);
        }
    }
}

static void fKST_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    u8* anime;
    u32 ctr_ofs;

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    if (ftr_actor->switch_bit != FALSE) {
        if (ftr_actor->ctr_type == aFTR_CTR_TYPE_GAME_PLAY) {
            ctr_ofs = play->game_frame;
        } else {
            ctr_ofs = game->frame_counter;
        }
        anime = fKST_on_anime_table[(ctr_ofs >> 1) % ARRAY_COUNT(fKST_on_anime_table)];
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, anime);
    } else {
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, int_kon_snowtv07a_TA_tex_txt);
    }

    gSPDisplayList(NEXT_POLY_OPA_DISP, int_kon_snowtv_face_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_kon_snowtv_body_model);

    CLOSE_DISP(game->graph);
}

static void fKST_dt(FTR_ACTOR* ftr_actor, u8* data) {
}

static aFTR_vtable_c fKST_func = {
    &fKST_ct, &fKST_mv, &fKST_dw, &fKST_dt, NULL,
};

aFTR_PROFILE iam_kon_snowtv = {
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
    &fKST_func,
};
#else
static void aKonsnowtv_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aKonsnowtv_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonsnowtv_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonsnowtv_dt(FTR_ACTOR* ftr_actor, u8* data);

extern u8 int_kon_snowtv07a_TA_tex_txt[];
extern u8 int_kon_snowtv07b_TA_tex_txt[];
extern u8 int_kon_snowtv07c_TA_tex_txt[];
extern u8 int_kon_snowtv07d_TA_tex_txt[];

extern Gfx int_kon_snowtv_body_model[];
extern Gfx int_kon_snowtv_face_model[];

u8* aKonsnowtv_on_anime[] = {
    int_kon_snowtv07b_TA_tex_txt, int_kon_snowtv07b_TA_tex_txt, int_kon_snowtv07b_TA_tex_txt,
    int_kon_snowtv07b_TA_tex_txt, int_kon_snowtv07b_TA_tex_txt, int_kon_snowtv07b_TA_tex_txt,
    int_kon_snowtv07b_TA_tex_txt, int_kon_snowtv07b_TA_tex_txt, int_kon_snowtv07b_TA_tex_txt,
    int_kon_snowtv07b_TA_tex_txt, int_kon_snowtv07c_TA_tex_txt, int_kon_snowtv07c_TA_tex_txt,
    int_kon_snowtv07c_TA_tex_txt, int_kon_snowtv07c_TA_tex_txt, int_kon_snowtv07c_TA_tex_txt,
    int_kon_snowtv07c_TA_tex_txt, int_kon_snowtv07c_TA_tex_txt, int_kon_snowtv07c_TA_tex_txt,
    int_kon_snowtv07c_TA_tex_txt, int_kon_snowtv07c_TA_tex_txt, int_kon_snowtv07d_TA_tex_txt,
    int_kon_snowtv07d_TA_tex_txt, int_kon_snowtv07d_TA_tex_txt, int_kon_snowtv07d_TA_tex_txt,
    int_kon_snowtv07d_TA_tex_txt, int_kon_snowtv07d_TA_tex_txt, int_kon_snowtv07d_TA_tex_txt,
    int_kon_snowtv07d_TA_tex_txt, int_kon_snowtv07d_TA_tex_txt, int_kon_snowtv07d_TA_tex_txt,
};

static void aKonsnowtv_ct(FTR_ACTOR* ftr_actor, u8* data) {
}
static void aKonsnowtv_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {

    if (ftr_actor->switch_bit != FALSE) {
        if (aFTR_CAN_PLAY_SE(ftr_actor)) {
            sAdo_OngenPos((uintptr_t)ftr_actor, 0x2B, &ftr_actor->position);
        }
        ftr_actor->tex_animation.frame++;

        if (ftr_actor->tex_animation.frame >= 60 || ftr_actor->tex_animation.frame < 0) {
            ftr_actor->tex_animation.frame = 0;
        }
    }

    if (ftr_actor->switch_changed_flag != FALSE) {
        if (ftr_actor->switch_bit != FALSE) {
            sAdo_OngenTrgStart(0x16, &ftr_actor->position);
        } else {
            sAdo_OngenTrgStart(0x17, &ftr_actor->position);
        }
    }
}
static void aKonsnowtv_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    if (ftr_actor->switch_bit != FALSE) {
        u8* anime = aKonsnowtv_on_anime[(s16)(ftr_actor->tex_animation.frame >> 1)];
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, anime);
    } else {
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, int_kon_snowtv07a_TA_tex_txt);
    }

    gSPDisplayList(NEXT_POLY_OPA_DISP, int_kon_snowtv_face_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_kon_snowtv_body_model);

    CLOSE_DISP(game->graph);
}
static void aKonsnowtv_dt(FTR_ACTOR* ftr_actor, u8* data) {
}

static aFTR_vtable_c aKonsnowtv_func = {
    &aKonsnowtv_ct, &aKonsnowtv_mv, &aKonsnowtv_dw, &aKonsnowtv_dt, NULL,
};

aFTR_PROFILE iam_kon_snowtv = {
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
    &aKonsnowtv_func,
};
#endif
