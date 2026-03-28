static void aNogFan_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aNogFan_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aNogFan_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aNogFan_dt(FTR_ACTOR* ftr_actor, u8* data);

extern cKF_Animation_R_c cKF_ba_r_int_nog_fan;
extern cKF_Skeleton_R_c cKF_bs_r_int_nog_fan;

extern u8 int_nog_fan_fan1_TA_tex_txt[];
extern u8 int_nog_fan_fan2_TA_tex_txt[];
extern u8 int_nog_fan_fan3_TA_tex_txt[];

static u8* aNogFan_nog_fan01_anim[] = {
    int_nog_fan_fan1_TA_tex_txt,
    int_nog_fan_fan2_TA_tex_txt,
    int_nog_fan_fan3_TA_tex_txt,
};

static void aNogFan_ControlSwitchSE(FTR_ACTOR* ftr_actor) {
    if (ftr_actor->switch_bit != FALSE) {
        sAdo_OngenTrgStart(0x16, &ftr_actor->position);
    } else {
        sAdo_OngenTrgStart(0x17, &ftr_actor->position);
    }
}

static void aNogFan_ChangeSwitch(FTR_ACTOR* ftr_actor) {
    if (ftr_actor->switch_changed_flag != FALSE) {
        aNogFan_ControlSwitchSE(ftr_actor);
    }
}

static void aNogFan_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyf;

    keyf = &ftr_actor->keyframe;
    cKF_SkeletonInfo_R_ct(keyf, &cKF_bs_r_int_nog_fan, &cKF_ba_r_int_nog_fan, ftr_actor->joint, ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_repeat(keyf, &cKF_ba_r_int_nog_fan, NULL);
    cKF_SkeletonInfo_R_play(keyf);
    keyf->frame_control.speed = 0.5f;

    ftr_actor->dynamic_work_s[0] = 0;

    if (ftr_actor->switch_bit != FALSE) {
        ftr_actor->dynamic_work_f[0] = 0.5f;
    } else {
        ftr_actor->dynamic_work_f[0] = 0.0f;
    }
}

static void aNogFan_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
#if VERSION >= VER_GAFU01_00
    static int fan_rot_frame_counter_dat[] = { 1, 1, 1, 2, 2, 2, 2, 2, 3, -1 };
#else
    static int fan_kurukuru_data[] = { 1, 1, 1, 2, 2, 2, 2, 2, 3, -1 };
#endif
    int num;
    int idx;

    cKF_SkeletonInfo_R_c* keyf;

    keyf = &ftr_actor->keyframe;

    aNogFan_ChangeSwitch(ftr_actor);
    if (ftr_actor->switch_bit != FALSE) {
        add_calc(&ftr_actor->dynamic_work_f[0], 0.5f, CALC_EASE(0.05f), 0.25f, 0.0005f);

        if (aFTR_CAN_PLAY_SE(ftr_actor)) {
            sAdo_OngenPos((uintptr_t)ftr_actor, 1, &ftr_actor->position);
        }
    } else {
        add_calc(&ftr_actor->dynamic_work_f[0], 0.0f, CALC_EASE(0.05f), 0.25f, 0.0005f);
    }

    keyf->frame_control.speed = ftr_actor->dynamic_work_f[0];
    cKF_SkeletonInfo_R_play(keyf);

    idx = 9.0f - (2.0f * (ftr_actor->dynamic_work_f[0] * 9.0f));
    
#if VERSION >= VER_GAFU01_00
    if ((idx != ARRAY_COUNT(fan_rot_frame_counter_dat) - 1)) {
        ftr_actor->dynamic_work_s[0]++;
        num = fan_rot_frame_counter_dat[idx];
        if ((ftr_actor->dynamic_work_s[0] >= num)) {
            ftr_actor->dynamic_work_s[0] = 0;
            ftr_actor->tex_animation.frame++;

            if (ftr_actor->tex_animation.frame >= 6 || ftr_actor->tex_animation.frame < 0) {
                ftr_actor->tex_animation.frame = 0;
            }
        }
    }
#else
    ftr_actor->dynamic_work_s[0]++;
    num = fan_kurukuru_data[idx];
    if ((num != -1) && (ftr_actor->dynamic_work_s[0] >= num)) {
        ftr_actor->dynamic_work_s[0] = 0;
        ftr_actor->tex_animation.frame++;

        if (ftr_actor->tex_animation.frame >= 6 || ftr_actor->tex_animation.frame < 0) {
            ftr_actor->tex_animation.frame = 0;
        }
    }
#endif
}

static void aNogFan_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    int idx;
    cKF_SkeletonInfo_R_c* keyf;
    Mtx* mtx;

    keyf = &ftr_actor->keyframe;

    mtx = ftr_actor->skeleton_mtx[game->frame_counter & 1];

    if (ftr_actor->ctr_type == aFTR_CTR_TYPE_GAME_PLAY) {
        idx = ftr_actor->tex_animation.frame >> 1;
    } else {
        int fctr = ABS((int)game->frame_counter % 6);
        idx = fctr >> 1;
    }

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, aNogFan_nog_fan01_anim[idx]);
    cKF_Si3_draw_R_SV(game, keyf, mtx, NULL, NULL, NULL);

    CLOSE_DISP(game->graph);
}

static void aNogFan_dt(FTR_ACTOR* ftr_actor, u8* data) {
}

static aFTR_vtable_c aNogFan_func = {
    &aNogFan_ct, &aNogFan_mv, &aNogFan_dw, &aNogFan_dt, NULL,
};

aFTR_PROFILE iam_nog_fan01 = {
    NULL, NULL, NULL, NULL, NULL,          NULL, NULL, NULL, 40.0f, 0.01f, aFTR_SHAPE_TYPEA, mCoBG_FTR_TYPEA,
    0,    0,    0,    0,    &aNogFan_func,
};
