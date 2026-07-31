static void fIJHOUI_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fIJHOUI_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fIJHOUI_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

extern cKF_Animation_R_c cKF_ba_r_int_ike_jny_houi01;
extern cKF_Skeleton_R_c cKF_bs_r_int_ike_jny_houi01;

static void fIJHOUI_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyf;

    keyf = &ftr_actor->keyframe;
    cKF_SkeletonInfo_R_ct(keyf, &cKF_bs_r_int_ike_jny_houi01, &cKF_ba_r_int_ike_jny_houi01, ftr_actor->joint,
                          ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_stop(keyf, &cKF_ba_r_int_ike_jny_houi01, NULL);
    cKF_SkeletonInfo_R_play(keyf);
    keyf->frame_control.speed = 0.0f;
    ftr_actor->dynamic_work_s[0] = ftr_actor->state;
}

static void fIJHOUI_Status2SetMode(FTR_ACTOR* arg0, FTR_ACTOR* ftr_actor) {
    switch (arg0->state) {
        case aFTR_STATE_STOP:
        case aFTR_STATE_PUSH:
        case aFTR_STATE_PULL:
        default:
            break;
        case aFTR_STATE_WAIT_LROTATE:
        case aFTR_STATE_WAIT_RROTATE:
            ftr_actor->dynamic_work_s[1] = 0;
            break;
        case aFTR_STATE_LROTATE:
            ftr_actor->dynamic_work_s[1]++;
            if (ftr_actor->dynamic_work_s[1] == 8) {
                ftr_actor->dynamic_work_s[2] = 0;
                ftr_actor->dynamic_work_f[0] =
                    (ftr_actor->dynamic_work_f[0] * sin_s(ftr_actor->dynamic_work_s[2])) - 45.0f;
                if (ftr_actor->dynamic_work_f[0] < -45.0f) {
                    ftr_actor->dynamic_work_f[0] = -45.0f;
                }
            }
            break;
        case aFTR_STATE_RROTATE:
            ftr_actor->dynamic_work_s[1]++;
            if (ftr_actor->dynamic_work_s[1] == 8) {
                ftr_actor->dynamic_work_s[2] = 0;
                ftr_actor->dynamic_work_f[0] =
                    45.0f + (ftr_actor->dynamic_work_f[0] * sin_s(ftr_actor->dynamic_work_s[2]));
                if (ftr_actor->dynamic_work_f[0] > 45.0f) {
                    ftr_actor->dynamic_work_f[0] = 45.0f;
                }
            }
            break;
    }
}

static void fIJHOUI_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyf = &ftr_actor->keyframe;
    FTR_ACTOR* parent;

    parent = aMR_GetParentFactor(ftr_actor, my_room_actor);
    fIJHOUI_Status2SetMode(ftr_actor, ftr_actor);

    if (parent != NULL) {
        fIJHOUI_Status2SetMode(parent, ftr_actor);
    }

    cKF_SkeletonInfo_R_play(keyf);

    if (ftr_actor->dynamic_work_f[0] > 0.0f) {
        ftr_actor->dynamic_work_f[0] -= (0.2f + (0.01f * GETREG(CRV, 81)));
        if (ftr_actor->dynamic_work_f[0] < 0.0f) {
            ftr_actor->dynamic_work_f[0] = 0.0f;
        }
    } else if (ftr_actor->dynamic_work_f[0] < 0.0f) {
        ftr_actor->dynamic_work_f[0] = ftr_actor->dynamic_work_f[0] + (0.2f + (0.01f * GETREG(CRV, 81)));
        if (ftr_actor->dynamic_work_f[0] > 0.0f) {
            ftr_actor->dynamic_work_f[0] = 0.0f;
        }
    }
    if (0.0f != ftr_actor->dynamic_work_f[0]) {
        ftr_actor->dynamic_work_s[2] += 0x320 + GETREG(CRV, 80);
    } else {
        ftr_actor->dynamic_work_s[2] = 0;
    }

    add_calc(&ftr_actor->dynamic_work_f[1], ftr_actor->dynamic_work_f[0] * sin_s(ftr_actor->dynamic_work_s[2]), 0.3f,
             100.0f, 0.0001f);
    ftr_actor->dynamic_work_s[0] = ftr_actor->state;
}

static int fIJHOUI_DrawBefore(GAME* game, cKF_SkeletonInfo_R_c* keyf, int jointNum, Gfx** joint, u8* jointFlag,
                              void* arg, s_xyz* joint1, xyz_t* trans) {
    FTR_ACTOR* actor = (FTR_ACTOR*)arg;

    int offset = 10430.378f * (0.017453292f * actor->dynamic_work_f[1]);

    if (jointNum == 3) {
        ACTOR* my_room_actor;
        int exists = FALSE;

        if ((Common_Get(clip).my_room_clip != NULL && Common_Get(clip).my_room_clip->my_room_actor_p != NULL)) {
            exists = TRUE;
        }

        if (exists != FALSE) {
            my_room_actor = Common_Get(clip).my_room_clip->my_room_actor_p;
        } else {
            my_room_actor = NULL;
        }

        joint1->y -= actor->s_angle_y + (aMR_GetParentAngleOffset(actor, my_room_actor)) + offset;
    }

    return 1;
}

static int fIJHOUI_DrawAfter(GAME* game, cKF_SkeletonInfo_R_c* keyf, int jointNum, Gfx** joint, u8* jointFlag,
                             void* arg, s_xyz* joint1, xyz_t* trans) {
    return 1;
}

static void fIJHOUI_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    N64Mtx* mtx = ftr_actor->skeleton_mtx[game->frame_counter & 1];

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    cKF_Si3_draw_R_SV(game, &ftr_actor->keyframe, mtx, fIJHOUI_DrawBefore, fIJHOUI_DrawAfter, ftr_actor);
    CLOSE_DISP(game->graph);
}

static aFTR_vtable_c fIJHOUI_func = {
    &fIJHOUI_ct, &fIJHOUI_mv, &fIJHOUI_dw, NULL, NULL,
};

aFTR_PROFILE iam_ike_jny_houi01 = {
    NULL, NULL, NULL, NULL, NULL,          NULL, NULL, NULL, 40.0f, 0.01f, aFTR_SHAPE_TYPEA, mCoBG_FTR_TYPEA,
    0,    2,    0,    0,    &fIJHOUI_func,
};
