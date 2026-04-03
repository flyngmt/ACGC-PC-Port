static void fNNB_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fNNB_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fNNB_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fNNB_dt(FTR_ACTOR* ftr_actor, u8* data);

extern cKF_Animation_R_c cKF_ba_r_int_nog_nabe;
extern cKF_Skeleton_R_c cKF_bs_r_int_nog_nabe;

extern u8 int_nog_nabe_fire1_TA_tex_txt[];
extern u8 int_nog_nabe_fire2_TA_tex_txt[];
extern u8 int_nog_nabe_fire3_TA_tex_txt[];

u8* fNNB_texture_table[] = {
    int_nog_nabe_fire2_TA_tex_txt,int_nog_nabe_fire2_TA_tex_txt,int_nog_nabe_fire3_TA_tex_txt,int_nog_nabe_fire3_TA_tex_txt,
};

extern Gfx int_nog_nabe_fire_model[];
void fNNB_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyf;

    keyf = &ftr_actor->keyframe;
    cKF_SkeletonInfo_R_ct(keyf, &cKF_bs_r_int_nog_nabe, &cKF_ba_r_int_nog_nabe, ftr_actor->joint, ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_stop(keyf, &cKF_ba_r_int_nog_nabe, NULL);
    keyf->frame_control.speed = 0.0f;
    keyf->frame_control.start_frame = 1.0f;
    keyf->frame_control.end_frame = cKF_ba_r_int_nog_nabe.frames;
    ftr_actor->dynamic_work_s[0] = ftr_actor->switch_bit != TRUE;
    if (!ftr_actor->dynamic_work_s[0]) {
        keyf->frame_control.current_frame = cKF_ba_r_int_nog_nabe.frames;
    }
    cKF_SkeletonInfo_R_play(keyf);
    ftr_actor->dynamic_work_s[1] = ftr_actor->dynamic_work_s[0];
}

void fNNB_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    xyz_t pos;
    cKF_SkeletonInfo_R_c* keyf = &ftr_actor->keyframe;

    if (ftr_actor->dynamic_work_s[0] == 1) {
        if (aFTR_CAN_PLAY_SE(ftr_actor)) {
            sAdo_OngenPos((uintptr_t)ftr_actor, 0x50, &ftr_actor->position);
            if (ftr_actor->dynamic_work_s[2] < 0) {
                pos = ftr_actor->position;

                pos.y += 18.0f;

                Common_Get(clip).effect_clip->effect_make_proc(0x71, pos, 1, 0, game, 0xFFFF, 6, 0);
                ftr_actor->dynamic_work_s[2] = (int)(10.0f + RANDOM_F(20.0f));
            } else {
                ftr_actor->dynamic_work_s[2]--;
            }
        }
    }
    if ((ftr_actor->switch_changed_flag != FALSE) && (keyf->frame_control.speed == 0.0f) &&
        (ftr_actor->dynamic_work_s[3] == 0)) {
        ftr_actor->dynamic_work_s[0] = (ftr_actor->dynamic_work_s[0] + 1) & 1;
        if (ftr_actor->dynamic_work_s[0] != 0) {
            keyf->frame_control.speed = 0.5f;
            keyf->frame_control.start_frame = cKF_ba_r_int_nog_nabe.frames;
            keyf->frame_control.end_frame = 1.0f;
            sAdo_OngenTrgStart(0x17, &ftr_actor->position);
        } else {
            keyf->frame_control.speed = 0.5f;
            keyf->frame_control.start_frame = 1.0f;
            keyf->frame_control.end_frame = cKF_ba_r_int_nog_nabe.frames;
            sAdo_OngenTrgStart(0x16, &ftr_actor->position);
        }
        ftr_actor->dynamic_work_s[3] = 0x13;
    }
        if (ftr_actor->dynamic_work_s[3] == 0) {
            ftr_actor->dynamic_work_s[1] = ftr_actor->dynamic_work_s[0];
        }
        if (cKF_SkeletonInfo_R_play(keyf) == 1) {
            keyf->frame_control.speed = 0.0f;
        }
        if (ftr_actor->dynamic_work_s[3] > 0) {
            ftr_actor->dynamic_work_s[3]--;
        }
}


void fNNB_dt(FTR_ACTOR* ftr_actor, u8* data) {
    if (ftr_actor->dynamic_work_s[0] != 0) {
        ftr_actor->switch_bit = TRUE;
    }
    else{
        ftr_actor->switch_bit = FALSE;
    }
}

static int fNNB_DrawBefore(GAME* game, cKF_SkeletonInfo_R_c* keyf, int jointNum, Gfx** joint, u8* jointFlag, void* arg,
                       s_xyz* joint1, xyz_t* trans){

    if(jointNum == 2){
        *joint = NULL;
    }

    return 1;
}

static int fNNB_DrawAfter(GAME* game, cKF_SkeletonInfo_R_c* keyf, int jointNum, Gfx** joint, u8* jointFlag, void* arg,
                       s_xyz* joint1, xyz_t* trans){

    if(jointNum == 2){
        OPEN_DISP(game->graph);

        gSPMatrix(NEXT_POLY_XLU_DISP,_Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gSPDisplayList(NEXT_POLY_XLU_DISP,int_nog_nabe_fire_model);
        CLOSE_DISP(game->graph);
    }

    return 1;
}

void fNNB_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    cKF_SkeletonInfo_R_c* keyf;
    Mtx* mtx;
    int fctr;
    s16 ctr;


    int txt_type;
    u8* txt;

    fctr = game->frame_counter;
    keyf = &ftr_actor->keyframe;
    ctr = ftr_actor->ctr_type;
    mtx = ftr_actor->skeleton_mtx[fctr & 1];

    if(ctr == aFTR_CTR_TYPE_GAME_PLAY){
        fctr = play->game_frame;
    }

    if(ctr == aFTR_CTR_TYPE_GAME_PLAY){
        txt_type = ((ftr_actor->dynamic_work_s[1] == 1) || (ctr != 1)) ? 1 : 0;
        txt = (txt_type != 0) ? fNNB_texture_table[fctr & 3] : int_nog_nabe_fire1_TA_tex_txt;
    }
    else if (keyf->frame_control.end_frame == cKF_ba_r_int_nog_nabe.frames) {
        txt_type = ((ftr_actor->dynamic_work_s[1] == 1) || (ctr != 1)) ? 1 : 0;
        txt = (txt_type != 0) ? fNNB_texture_table[fctr & 3] : int_nog_nabe_fire1_TA_tex_txt;  
    }
    else{
        txt = int_nog_nabe_fire1_TA_tex_txt;
    }

    
    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP,_Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_8,txt);
    cKF_Si3_draw_R_SV(game, keyf, mtx, fNNB_DrawBefore, fNNB_DrawAfter, ftr_actor);


    CLOSE_DISP(game->graph);
}

static aFTR_vtable_c fNNB_func = {
	&fNNB_ct,
	&fNNB_mv,
	&fNNB_dw,
	&fNNB_dt,
	NULL,
};

aFTR_PROFILE iam_nog_nabe = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	15.7f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	0,
	&fNNB_func,
};
