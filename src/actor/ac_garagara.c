#include "ac_garagara.h"

#include "m_common_data.h"
#include "m_malloc.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "libultra/libultra.h"

enum {
    aGRGR_STATUS_WAIT,
    aGRGR_STATUS_ROTATE,

    aGRGR_STATUS_NUM
};

enum {
    aGRBL_STATUS_NONE,
    aGRBL_STATUS_START,
    aGRBL_STATUS_KOROKORO,
    aGRBL_STATUS_DELETE,

    aGRBL_STATUS_NUM
};

static void Garagara_Actor_ct(ACTOR* actorx, GAME* game);
static void Garagara_Actor_dt(ACTOR* actorx, GAME* game);
static void Garagara_Actor_move_dummy(ACTOR* actorx, GAME* game);
static void Garagara_Actor_draw_dummy(ACTOR* actorx, GAME* game);
static void Garagara_Actor_move(ACTOR* actorx, GAME* game);
static void Garagara_Actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Garagara_Profile = {
    mAc_PROFILE_GARAGARA,
    ACTOR_PART_FG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(GARAGARA_ACTOR),
    &Garagara_Actor_ct,
    &Garagara_Actor_dt,
    &Garagara_Actor_move_dummy,
    &Garagara_Actor_draw_dummy,
    NULL,
};
// clang-format on

typedef void (*aGRGR_INIT_PROC)(ACTOR*, GAME*);
typedef void (*aGRGR_MOVE_PROC)(ACTOR*, GAME*);

static void aGaragara_WaitInit(ACTOR* actorx, GAME* game);
static void aGaragara_RotateInit(ACTOR* actorx, GAME* game);

static void aGaragara_WaitMove(ACTOR* actorx, GAME* game);
static void aGaragara_RotateMove(ACTOR* actorx, GAME* game);

static aGRGR_INIT_PROC aGaragara_init_proc_table[] = { &aGaragara_WaitInit, &aGaragara_RotateInit };
static aGRGR_MOVE_PROC aGaragara_move_proc_table[] = { &aGaragara_WaitMove, &aGaragara_RotateMove };

#include "../src/actor/ac_garagara_ball.c_inc"

static void aGRGR_AnimeCt(cKF_Skeleton_R_c* skeleton, cKF_Animation_R_c* animation, cKF_SkeletonInfo_R_c* kf,
                          s_xyz* work, s_xyz* morph, f32 speed) {
    cKF_SkeletonInfo_R_ct(kf, skeleton, animation, work, morph);
    cKF_SkeletonInfo_R_init_standard_stop(kf, animation, NULL);
    kf->frame_control.speed = speed;
    cKF_SkeletonInfo_R_play(kf);
}

static int aGaragara_RequestStatus(ACTOR* actorx, s16 status) {
    GARAGARA_ACTOR* garagara = (GARAGARA_ACTOR*)actorx;

    if (status >= 0 && status < aGRGR_STATUS_NUM) {
        garagara->request_flag = TRUE;
        garagara->request_status = status;
        return TRUE;
    }

    garagara->status = aGRGR_STATUS_WAIT;
    return FALSE;
}

static int aGaragara_GaragaraAnimeStart(int ball_type) {
    if (CLIP(garagara_clip) != NULL) {
        ACTOR* actorx = CLIP(garagara_clip)->actorx;
        GARAGARA_ACTOR* garagara = (GARAGARA_ACTOR*)actorx;

        if (actorx != NULL) {
            aGaragara_RequestStatus(actorx, aGRGR_STATUS_ROTATE);
            garagara->ball_type = ball_type & 3;
            return TRUE;
        }
    }

    return FALSE;
}

static int aGaragara_DeleteBall(void) {
    if (CLIP(garagara_clip) != NULL) {
        ACTOR* actorx = CLIP(garagara_clip)->actorx;
        GARAGARA_ACTOR* garagara = (GARAGARA_ACTOR*)actorx;

        garagara->ball.status = aGRBL_STATUS_NONE;
        return TRUE;
    }

    return FALSE;
}

static void aGRGR_DecideGaragaraMode(ACTOR* actorx) {
    GARAGARA_ACTOR* garagara = (GARAGARA_ACTOR*)actorx;

    if (Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_FUKUBIKI) {
        garagara->mode = aGRGR_MODE_FUKUBIKI;
    } else {
        garagara->mode = aGRGR_MODE_NONE;
    }
}

static void aGRGR_CommonCt(ACTOR* actorx, GAME* game) {
    GARAGARA_ACTOR* garagara = (GARAGARA_ACTOR*)actorx;

    garagara->clip.garagara_anime_start_proc = &aGaragara_GaragaraAnimeStart;
    garagara->clip.delete_ball_proc = &aGaragara_DeleteBall;
    garagara->clip.actorx = actorx;
    CLIP(garagara_clip) = &garagara->clip;
}

extern cKF_Skeleton_R_c cKF_bs_r_obj_gara;
extern cKF_Animation_R_c cKF_ba_r_obj_gara;

static void aGRGR_FukubikiDayCt(ACTOR* actorx, GAME* game) {
    GARAGARA_ACTOR* garagara = (GARAGARA_ACTOR*)actorx;

#ifdef TARGET_PC
    garagara->logic_accum = 0.0f;
#endif
    aGRGR_AnimeCt(&cKF_bs_r_obj_gara, &cKF_ba_r_obj_gara, &garagara->keyframe, garagara->work, garagara->morph, 0.0f);
    actorx->mv_proc = &Garagara_Actor_move;
    actorx->dw_proc = &Garagara_Actor_draw;
}

static void aGRGR_DummyCt(ACTOR* actorx, GAME* game) {
    // nothing
}

static void Garagara_Actor_ct(ACTOR* actorx, GAME* game) {
    static const mActor_proc construct_table[] = { &aGRGR_DummyCt, &aGRGR_FukubikiDayCt };
    GARAGARA_ACTOR* garagara = (GARAGARA_ACTOR*)actorx;

    aGRGR_DecideGaragaraMode(actorx);
    aGRGR_CommonCt(actorx, game);
    (*construct_table[garagara->mode & 1])(actorx, game);
}

static void Garagara_Actor_dt(ACTOR* actorx, GAME* game) {
    GARAGARA_ACTOR* garagara = (GARAGARA_ACTOR*)actorx;

    if (garagara->bank != NULL) {
        zelda_free(garagara->bank);
    }

    CLIP(garagara_clip) = NULL;
}

static void Garagara_Actor_draw_dummy(ACTOR* actorx, GAME* game) {
    // nothing
}

static void Garagara_Actor_draw(ACTOR* actorx, GAME* game) {
    GARAGARA_ACTOR* garagara = (GARAGARA_ACTOR*)actorx;
    cKF_SkeletonInfo_R_c* kf_p = &garagara->keyframe;
    int idx = game->frame_counter & 1;
    N64Mtx* mtx = garagara->mtx[idx];
    xyz_t* pos = &actorx->world.position;

    _texture_z_light_fog_prim(game->graph);
    Matrix_translate(pos->x, pos->y, pos->z, MTX_LOAD);
    Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    CLOSE_DISP(game->graph);

    cKF_Si3_draw_R_SV(game, kf_p, mtx, NULL, NULL, actorx);
    aGRBL_draw(&garagara->ball, game);
}

static void aGaragara_WaitInit(ACTOR* actorx, GAME* game) {
    GARAGARA_ACTOR* garagara = (GARAGARA_ACTOR*)actorx;

    aGRGR_AnimeCt(&cKF_bs_r_obj_gara, &cKF_ba_r_obj_gara, &garagara->keyframe, garagara->work, garagara->morph, 0.0f);
}

static void aGaragara_RotateInit(ACTOR* actorx, GAME* game) {
    GARAGARA_ACTOR* garagara = (GARAGARA_ACTOR*)actorx;

    aGRGR_AnimeCt(&cKF_bs_r_obj_gara, &cKF_ba_r_obj_gara, &garagara->keyframe, garagara->work, garagara->morph, 0.5f);
    sAdo_OngenTrgStart(MONO(NA_SE_51), &actorx->world.position);
}

static void aGaragara_WaitMove(ACTOR* actorx, GAME* game) {
    GARAGARA_ACTOR* garagara = (GARAGARA_ACTOR*)actorx;
    cKF_SkeletonInfo_R_c* kf_p = &garagara->keyframe;

    cKF_SkeletonInfo_R_play(kf_p);
}

static void aGaragara_RotateMove(ACTOR* actorx, GAME* game) {
    GARAGARA_ACTOR* garagara = (GARAGARA_ACTOR*)actorx;
    cKF_SkeletonInfo_R_c* kf_p = &garagara->keyframe;

    if (garagara->anime_frame == 46) {
        xyz_t pos;

        pos.x = actorx->world.position.x + 10.0f;
        pos.y = actorx->world.position.y + 10.0f;
        pos.z = actorx->world.position.z;

        aGRBL_make(&actorx->world.position, &garagara->ball, &pos, garagara->ball_type);
    }

    if (cKF_SkeletonInfo_R_play(kf_p) == cKF_STATE_STOPPED) {
        aGaragara_RequestStatus(actorx, aGRGR_STATUS_WAIT);
    }
}

static void Garagara_Actor_move_dummy(ACTOR* actorx, GAME* game) {
    // nothing
}

static void Garagara_Actor_move(ACTOR* actorx, GAME* game) {
    GARAGARA_ACTOR* garagara = (GARAGARA_ACTOR*)actorx;
#ifdef TARGET_PC
    double saved_dt;
    int ticks;
    int tick;

    ticks = graph_dt_60hz_ticks(game, &garagara->logic_accum);
    saved_dt = game->graph->dt_num_60fps_frames;
    game->graph->dt_num_60fps_frames = 1.0;
    for (tick = 0; tick < ticks; tick++) {
#endif
        aGRBL_move(&garagara->ball, game);
        if (garagara->request_flag) {
            (*aGaragara_init_proc_table[garagara->request_status])(actorx, game);
            garagara->status = garagara->request_status;
            garagara->request_flag = FALSE;
            garagara->anime_frame = 0;
        }

        if (garagara->status >= 0 && garagara->status < aGRGR_STATUS_NUM) {
            (*aGaragara_move_proc_table[garagara->status])(actorx, game);
            garagara->anime_frame++;
        } else {
            garagara->status = aGRGR_STATUS_WAIT;
        }
#ifdef TARGET_PC
    }
    game->graph->dt_num_60fps_frames = saved_dt;
#endif
}
