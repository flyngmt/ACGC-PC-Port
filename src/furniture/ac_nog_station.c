extern cKF_Skeleton_R_c cKF_bs_r_int_nog_station1;
extern cKF_Skeleton_R_c cKF_bs_r_int_nog_station2;
extern cKF_Skeleton_R_c cKF_bs_r_int_nog_station3;

extern cKF_Animation_R_c cKF_ba_r_int_nog_station1;
extern cKF_Animation_R_c cKF_ba_r_int_nog_station2;
extern cKF_Animation_R_c cKF_ba_r_int_nog_station3;

static cKF_Skeleton_R_c* fNSN_station_skel_table[] = {
    &cKF_bs_r_int_nog_station1, &cKF_bs_r_int_nog_station1, &cKF_bs_r_int_nog_station1, &cKF_bs_r_int_nog_station1,
    &cKF_bs_r_int_nog_station1, &cKF_bs_r_int_nog_station2, &cKF_bs_r_int_nog_station2, &cKF_bs_r_int_nog_station2,
    &cKF_bs_r_int_nog_station2, &cKF_bs_r_int_nog_station2, &cKF_bs_r_int_nog_station3, &cKF_bs_r_int_nog_station3,
    &cKF_bs_r_int_nog_station3, &cKF_bs_r_int_nog_station3, &cKF_bs_r_int_nog_station3, &cKF_bs_r_int_nog_station3,
};

static cKF_Animation_R_c* fNSN_station_anime_table[] = {
    &cKF_ba_r_int_nog_station1, &cKF_ba_r_int_nog_station1, &cKF_ba_r_int_nog_station1, &cKF_ba_r_int_nog_station1,
    &cKF_ba_r_int_nog_station1, &cKF_ba_r_int_nog_station2, &cKF_ba_r_int_nog_station2, &cKF_ba_r_int_nog_station2,
    &cKF_ba_r_int_nog_station2, &cKF_ba_r_int_nog_station2, &cKF_ba_r_int_nog_station3, &cKF_ba_r_int_nog_station3,
    &cKF_ba_r_int_nog_station3, &cKF_ba_r_int_nog_station3, &cKF_ba_r_int_nog_station3, &cKF_ba_r_int_nog_station3,
};

static void fNSN_ct(FTR_ACTOR* ftr_actor, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    int station_idx = (ftr_actor->name - 0x42A) & 15;

    cKF_SkeletonInfo_R_ct(keyframe, fNSN_station_skel_table[station_idx], fNSN_station_anime_table[station_idx],
                          ftr_actor->joint, ftr_actor->morph);
    cKF_SkeletonInfo_R_init_standard_repeat(keyframe, fNSN_station_anime_table[station_idx], NULL);
    keyframe->frame_control.speed = 0.5f;
    cKF_SkeletonInfo_R_play(keyframe);
}

static void fNSN_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;

    cKF_SkeletonInfo_R_play(keyframe);
}

static void fNSN_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static int fNSN_DrawBefore(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                           u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    if (joint_idx == 3) {
        joint_rot->z -= Common_Get(time.rad_hour);
    } else if (joint_idx == 4) {
        joint_rot->z -= Common_Get(time.rad_min);
    }

    return TRUE;
}

static int fNSN_DrawAfter(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape, u8* joint_flags,
                          void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    return TRUE;
}

#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_station1_a_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_station1_a_pal[] = {
#include "assets/int_nog_station1_a_pal.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_station1_b_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_station1_b_pal[] = {
#include "assets/int_nog_station1_b_pal.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_station1_c_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_station1_c_pal[] = {
#include "assets/int_nog_station1_c_pal.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_station1_d_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_station1_d_pal[] = {
#include "assets/int_nog_station1_d_pal.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_station1_e_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_station1_e_pal[] = {
#include "assets/int_nog_station1_e_pal.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_station2_a_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_station2_a_pal[] = {
#include "assets/int_nog_station2_a_pal.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_station2_b_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_station2_b_pal[] = {
#include "assets/int_nog_station2_b_pal.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_station2_c_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_station2_c_pal[] = {
#include "assets/int_nog_station2_c_pal.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_station2_d_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_station2_d_pal[] = {
#include "assets/int_nog_station2_d_pal.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_station2_e_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_station2_e_pal[] = {
#include "assets/int_nog_station2_e_pal.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_station3_a_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_station3_a_pal[] = {
#include "assets/int_nog_station3_a_pal.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_station3_b_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_station3_b_pal[] = {
#include "assets/int_nog_station3_b_pal.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_station3_c_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_station3_c_pal[] = {
#include "assets/int_nog_station3_c_pal.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_station3_d_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_station3_d_pal[] = {
#include "assets/int_nog_station3_d_pal.inc"
};
#endif
#ifdef TARGET_PC
ATTRIBUTE_ALIGN(32) u16 int_nog_station3_e_pal[0x20 / sizeof(u16)];
#else
ATTRIBUTE_ALIGN(32) u16 int_nog_station3_e_pal[] = {
#include "assets/int_nog_station3_e_pal.inc"
};
#endif

static u16* fMSM_palette_table[] = {
    int_nog_station1_a_pal, int_nog_station1_b_pal, int_nog_station1_c_pal, int_nog_station1_d_pal,
    int_nog_station1_e_pal, int_nog_station2_a_pal, int_nog_station2_b_pal, int_nog_station2_c_pal,
    int_nog_station2_d_pal, int_nog_station2_e_pal, int_nog_station3_a_pal, int_nog_station3_b_pal,
    int_nog_station3_c_pal, int_nog_station3_d_pal, int_nog_station3_e_pal, int_nog_station3_e_pal,
};

static void fNSN_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    int mtx_idx = game->frame_counter & 1;
    cKF_SkeletonInfo_R_c* keyframe = &ftr_actor->keyframe;
    N64Mtx* mtx = ftr_actor->skeleton_mtx[mtx_idx];
    int station_idx = (ftr_actor->name - 0x42A) & 15;
    u16* pal = fMSM_palette_table[station_idx];

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, pal);

    CLOSE_DISP(game->graph);

    cKF_Si3_draw_R_SV(game, keyframe, mtx, &fNSN_DrawBefore, &fNSN_DrawAfter, ftr_actor);
}

static aFTR_vtable_c fNSN_func = {
    &fNSN_ct, &fNSN_mv, &fNSN_dw, &fNSN_dt, NULL,
};

aFTR_PROFILE iam_nog_station = {
    // clang-format off
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
	aFTR_SHAPE_TYPEB_0,
	mCoBG_FTR_TYPEB_0,
	0,
	0,
	0,
	0,
	&fNSN_func,
    // clang-format on
};
