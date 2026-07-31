static void aSumLogHatoclk_StopAnimeInitNormal(cKF_SkeletonInfo_R_c* keyframe, cKF_Animation_R_c* anime, f32 speed) {
    cKF_SkeletonInfo_R_init_standard_stop(keyframe, anime, NULL);
    keyframe->frame_control.speed = speed;
    cKF_SkeletonInfo_R_play(keyframe);
}

extern cKF_Skeleton_R_c cKF_bs_r_int_sum_log_hatoclk;
extern cKF_Animation_R_c cKF_ba_r_int_sum_log_hatoclk;

static void aSumLogHatoclk_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_ct(keyframe, &cKF_bs_r_int_sum_log_hatoclk, &cKF_ba_r_int_sum_log_hatoclk, ftr_actor->joint,
                          ftr_actor->morph);
    aSumLogHatoclk_StopAnimeInitNormal(keyframe, &cKF_ba_r_int_sum_log_hatoclk, 1.0f);
    ftr_actor->dynamic_work_s[0] = 0;
}

extern Gfx int_sum_log_hatoclk_short_model[];
extern Gfx int_sum_log_hatoclk_long_model[];

static int aSumLogHatoclk_DwAfter(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                                  u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    FTR_ACTOR* ftr_actor = (FTR_ACTOR*)arg;
    GAME_PLAY* play = (GAME_PLAY*)game;
    xyz_t pos;
    xyz_t save_pos = { 0.0f, 0.0f, 0.0f };
    s16 base_angle_y = RAD2SHORT_ANGLE2(DEG2RAD(ftr_actor->angle_y));
    f32 scale_x = ftr_actor->scale.x * 0.01f;
    f32 scale_y = ftr_actor->scale.y * 0.01f;
    f32 scale_z = ftr_actor->scale.z * 0.01f;
    GRAPH* graph = game->graph;

    if (joint_idx == 7) {
        Matrix_Position(&save_pos, &pos);
        Matrix_push();
        Matrix_translate(pos.x, pos.y, pos.z, MTX_LOAD);
        Matrix_RotateY(base_angle_y, MTX_MULT);
        Matrix_RotateZ(DEG2SHORT_ANGLE(90.0f) - Common_Get(time.rad_hour), MTX_MULT);
        Matrix_translate(0.0f, 0.0f, 1.0f, MTX_MULT);
        Matrix_scale(scale_x, scale_y, scale_z, MTX_MULT);

        OPEN_DISP(graph);

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        Matrix_pull();
        gSPDisplayList(NEXT_POLY_OPA_DISP, int_sum_log_hatoclk_short_model);

        CLOSE_DISP(graph);
    } else if (joint_idx == 8) {
        Matrix_Position(&save_pos, &pos);
        Matrix_push();
        Matrix_translate(pos.x, pos.y, pos.z, MTX_LOAD);
        Matrix_RotateY(base_angle_y, MTX_MULT);
        Matrix_RotateZ(DEG2SHORT_ANGLE(90.0f) - Common_Get(time.rad_min), MTX_MULT);
        Matrix_translate(0.0f, 0.0f, 1.0f, MTX_MULT);
        Matrix_scale(scale_x, scale_y, scale_z, MTX_MULT);

        OPEN_DISP(graph);

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        Matrix_pull();
        gSPDisplayList(NEXT_POLY_OPA_DISP, int_sum_log_hatoclk_long_model);

        CLOSE_DISP(graph);
    }
    return TRUE;
}

static int aSumLogHatoclk_DwBefore(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                                   u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    if (joint_idx == 7 || joint_idx == 8) {
        *joint_shape = NULL;
    }

    return TRUE;
}

static void aSumLogHatoclk_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    N64Mtx* mtx = ftr_actor->skeleton_mtx[game->frame_counter & 1];

    cKF_Si3_draw_R_SV(game, keyframe, mtx, &aSumLogHatoclk_DwBefore, &aSumLogHatoclk_DwAfter, ftr_actor);
}
static void aSumLogHatoclk_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    lbRTC_time_c rtc_time = Common_Get(time.rtc_time);
    static u8 pappo_count_table[lbRTC_HOURS_PER_DAY] = {
        12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
    };

    switch (ftr_actor->dynamic_work_s[0]) {
        case 0: {
            if (rtc_time.min == 0) {
                ftr_actor->dynamic_work_s[1] = pappo_count_table[rtc_time.hour];
                ftr_actor->dynamic_work_s[0] = 1;
                aSumLogHatoclk_StopAnimeInitNormal(keyframe, &cKF_ba_r_int_sum_log_hatoclk, 1.0f);
                keyframe->frame_control.current_frame = 1.0f;
            } else if (rtc_time.min == 30) {
                ftr_actor->dynamic_work_s[1] = 1;
                ftr_actor->dynamic_work_s[0] = 1;
                aSumLogHatoclk_StopAnimeInitNormal(keyframe, &cKF_ba_r_int_sum_log_hatoclk, 1.0f);
                keyframe->frame_control.current_frame = 1.0f;
            }

            break;
        }

        case 1: {
            if (keyframe->frame_control.current_frame == ((f32)(int)GETREG(MYKREG, 33) + 2.0f)) {
                if (aFTR_CAN_PLAY_SE(ftr_actor)) {
                    sAdo_OngenTrgStart(0x133, &ftr_actor->position);
                }
            }

            if (cKF_SkeletonInfo_R_play(keyframe) == cKF_STATE_STOPPED) {
                if (keyframe->frame_control.speed == 0.0f) {
                    aSumLogHatoclk_StopAnimeInitNormal(keyframe, &cKF_ba_r_int_sum_log_hatoclk, 1.0f);
                    keyframe->frame_control.current_frame = 1.0f;
                    ftr_actor->dynamic_work_s[1]--;

                    if (ftr_actor->dynamic_work_s[1] <= 0) {
                        ftr_actor->dynamic_work_s[0] = 2; // last 'pappo' was played
                    }
                } else {
                    keyframe->frame_control.speed = 0.0f;
                }
            }

            break;
        }

        case 2: {
            if (rtc_time.min != 0 && rtc_time.min != 30) {
                ftr_actor->dynamic_work_s[0] = 0;
            }

            break;
        }
    }
}

static void aSumLogHatoclk_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static aFTR_vtable_c aSumLogHatoclk_func = {
    &aSumLogHatoclk_ct, &aSumLogHatoclk_mv, &aSumLogHatoclk_dw, &aSumLogHatoclk_dt, NULL,
};

aFTR_PROFILE iam_sum_log_hatoclk = {
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
    &aSumLogHatoclk_func,
    // clang-format on
};
