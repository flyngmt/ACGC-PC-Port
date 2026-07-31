#include "ac_house_clock.h"

#include "m_scene.h"
#include "m_name_table.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "m_malloc.h"
#include "m_common_data.h"

enum {
    aHC_ENV_MAP_NONE,
    aHC_ENV_MAP_OPA,
    aHC_ENV_MAP_XLU,

    aHC_ENV_MAP_NUM
};

typedef struct house_clock_draw_data_s {
    cKF_Skeleton_R_c* skeleton;
    cKF_Animation_R_c* animation;
    s16 short_joint_no;
    s16 long_joint_no;
    Gfx* short_model;
    Gfx* long_model;
    s16 env_map_type;
} aHC_draw_data_c;

extern cKF_Skeleton_R_c cKF_bs_r_obj_clock_shop1;
extern cKF_Skeleton_R_c cKF_bs_r_obj_clock_shop2;
extern cKF_Skeleton_R_c cKF_bs_r_obj_clock_shop3;
extern cKF_Skeleton_R_c cKF_bs_r_obj_clock_shop4;
extern cKF_Skeleton_R_c cKF_bs_r_obj_clock_yub;
extern cKF_Skeleton_R_c cKF_bs_r_obj_clock_koban;
extern cKF_Skeleton_R_c cKF_bs_r_obj_clock_museum1;
extern cKF_Skeleton_R_c cKF_bs_r_obj_clock_tailor;

extern cKF_Animation_R_c cKF_ba_r_obj_clock_shop1;
extern cKF_Animation_R_c cKF_ba_r_obj_clock_shop2;
extern cKF_Animation_R_c cKF_ba_r_obj_clock_shop3;
extern cKF_Animation_R_c cKF_ba_r_obj_clock_shop4;
extern cKF_Animation_R_c cKF_ba_r_obj_clock_yub;
extern cKF_Animation_R_c cKF_ba_r_obj_clock_koban;
extern cKF_Animation_R_c cKF_ba_r_obj_clock_museum1;
extern cKF_Animation_R_c cKF_ba_r_obj_clock_tailor;

extern Gfx obj_clock_shop1_short_model[];
extern Gfx obj_clock_shop1_long_model[];

extern Gfx obj_clock_shop2_short_model[];
extern Gfx obj_clock_shop2_long_model[];

extern Gfx obj_clock_shop3_short_model[];
extern Gfx obj_clock_shop3_long_model[];

extern Gfx obj_clock_shop4_short_model[];
extern Gfx obj_clock_shop4_long_model[];

extern Gfx obj_clock_yub_short_model[];
extern Gfx obj_clock_yub_long_model[];

extern Gfx obj_clock_koban_short_model[];
extern Gfx obj_clock_koban_long_model[];

extern Gfx obj_clock_museum1_short_model[];
extern Gfx obj_clock_museum1_long_model[];

extern Gfx obj_clock_tailor_short_model[];
extern Gfx obj_clock_tailor_long_model[];

// clang-format off
static aHC_draw_data_c aHC_draw_data[] = {
    {
        &cKF_bs_r_obj_clock_shop1, &cKF_ba_r_obj_clock_shop1,
        5, 6,
        obj_clock_shop1_short_model, obj_clock_shop1_long_model,
        aHC_ENV_MAP_NONE
    },
    {
        &cKF_bs_r_obj_clock_shop2, &cKF_ba_r_obj_clock_shop2,
        3, 4,
        obj_clock_shop2_short_model, obj_clock_shop2_long_model,
        aHC_ENV_MAP_NONE
    },
    {
        &cKF_bs_r_obj_clock_shop3, &cKF_ba_r_obj_clock_shop3,
        3, 4,
        obj_clock_shop3_short_model, obj_clock_shop3_long_model,
        aHC_ENV_MAP_NONE
    },
    {
        &cKF_bs_r_obj_clock_shop4, &cKF_ba_r_obj_clock_shop4,
        5, 6,
        obj_clock_shop4_short_model, obj_clock_shop4_long_model,
        aHC_ENV_MAP_NONE
    },
    {
        &cKF_bs_r_obj_clock_shop4, &cKF_ba_r_obj_clock_shop4,
        5, 6,
        obj_clock_shop4_short_model, obj_clock_shop4_long_model,
        aHC_ENV_MAP_NONE
    },
    {
        &cKF_bs_r_obj_clock_yub, &cKF_ba_r_obj_clock_yub,
        3, 4,
        obj_clock_yub_short_model, obj_clock_yub_long_model,
        aHC_ENV_MAP_NONE
    },
    {
        &cKF_bs_r_obj_clock_koban, &cKF_ba_r_obj_clock_koban,
        3, 4,
        obj_clock_koban_short_model, obj_clock_koban_long_model,
        aHC_ENV_MAP_NONE
    },
    {
        &cKF_bs_r_obj_clock_museum1, &cKF_ba_r_obj_clock_museum1,
        3, 4,
        obj_clock_museum1_short_model, obj_clock_museum1_long_model,
        aHC_ENV_MAP_NONE
    },
    {
        &cKF_bs_r_obj_clock_tailor, &cKF_ba_r_obj_clock_tailor,
        5, 6,
        obj_clock_tailor_short_model, obj_clock_tailor_long_model,
        aHC_ENV_MAP_NONE
    },
};
// clang-format on

typedef struct house_clock_pos_data_s {
    int scene_no;
    xyz_t pos;
} aHC_pos_data_c;

// clang-format off
static aHC_pos_data_c aHC_position_data[] = {
    { SCENE_SHOP0, { 200.0f, 40.0f, 40.0f } },
    { SCENE_CONVENI, { 240.0f, 0.0f, 40.0f } },
    { SCENE_SUPER, { 160.0f, 0.0f, 40.0f } },
    { SCENE_DEPART, { 240.0f, 0.0f, 120.0f } },
    { SCENE_DEPART_2, { 240.0f, 0.0f, 120.0f } },
    { SCENE_POST_OFFICE, { 120.0f, 55.0f, 135.0f } },
    { SCENE_POLICE_BOX, { 200.0f, 0.0f, 30.0f } },
    { SCENE_MUSEUM_ENTRANCE, { 0.0f, 0.0f, 0.0f } },
    { SCENE_NEEDLEWORK, { 0.0f, 0.0f, 0.0f } },
};
// clang-format on

static void House_Clock_Actor_ct(ACTOR* actorx, GAME* game);
static void House_Clock_Actor_dt(ACTOR* actorx, GAME* game);
static void House_Clock_Actor_move(ACTOR* actorx, GAME* game);
static void House_Clock_Actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE House_Clock_Profile = {
    mAc_PROFILE_HOUSE_CLOCK,
    ACTOR_PART_FG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(HOUSE_CLOCK_ACTOR),
    &House_Clock_Actor_ct,
    &House_Clock_Actor_dt,
    &House_Clock_Actor_move,
    &House_Clock_Actor_draw,
    NULL,
};
// clang-format on

static void House_Clock_Actor_no_draw(ACTOR* actorx, GAME* game) {
    // nothing
}

static void aHC_dummy(ACTOR* actorx, GAME* game) {
    // nothing
}

static int aHC_SetClockNum(ACTOR* actorx) {
    HOUSE_CLOCK_ACTOR* house_clock = (HOUSE_CLOCK_ACTOR*)actorx;
    int i;
    int scene_no = Save_Get(scene_no);

    house_clock->clock.clock_num = 0;
    for (i = 0; i < aHC_TYPE_NUM; i++) {
        if (scene_no == aHC_position_data[i].scene_no) {
            house_clock->clock.clock_num = i;
            house_clock->clock.pos = aHC_position_data[house_clock->clock.clock_num].pos;
            return TRUE;
        }
    }

    actorx->mv_proc = &aHC_dummy;
    actorx->dw_proc = &aHC_dummy;
    actorx->dt_proc = &aHC_dummy;
    return FALSE;
}

static void aHC_InitClockAnimation(ACTOR* actorx) {
    HOUSE_CLOCK_ACTOR* house_clock = (HOUSE_CLOCK_ACTOR*)actorx;
    aHC_clock_c* clock = &house_clock->clock;
    cKF_SkeletonInfo_R_c* kf_p = &clock->keyframe;
    s16 clock_num = clock->clock_num;

    cKF_SkeletonInfo_R_ct(kf_p, aHC_draw_data[clock_num].skeleton, aHC_draw_data[clock_num].animation, clock->work,
                          clock->morph);
    cKF_SkeletonInfo_R_init_standard_repeat(kf_p, aHC_draw_data[clock_num].animation, NULL);
    cKF_SkeletonInfo_R_play(kf_p);
    kf_p->frame_control.speed = 0.5f;
}

static void House_Clock_Actor_ct(ACTOR* actorx, GAME* game) {
    HOUSE_CLOCK_ACTOR* house_clock = (HOUSE_CLOCK_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

    if (aHC_SetClockNum(actorx)) {
        aHC_InitClockAnimation(actorx);
        house_clock->phase_frame = (f32)(play->game_frame % 120);
        house_clock->clock.pos =
            aHC_position_data[house_clock->clock.clock_num].pos; // @cleanup - this is already done in aHC_SetClockNum

        // Don't render the clock if the monthly raffle is taking place
        if (Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_FUKUBIKI && house_clock->clock.clock_num <= 4) {
            actorx->dw_proc = &House_Clock_Actor_no_draw;
        }
    }
}

static int aHC_CrossedFrame(f32 prev, f32 now, f32 target) {
    if (prev <= now) {
        return prev < target && now >= target;
    }

    return prev < target || now >= target;
}

static void House_Clock_Actor_dt(ACTOR* actorx, GAME* game) {
    HOUSE_CLOCK_ACTOR* house_clock = (HOUSE_CLOCK_ACTOR*)actorx;

    if (house_clock->clock.bank != NULL) {
        zelda_free(house_clock->clock.bank);
    }
}

static void aHC_SetEnvMapping(ACTOR* actorx, GAME* game) {
    HOUSE_CLOCK_ACTOR* house_clock = (HOUSE_CLOCK_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

    switch (aHC_draw_data[house_clock->clock.clock_num].env_map_type) {
        case aHC_ENV_MAP_OPA:
            _texture_z_light_fog_prim(game->graph);
            Setpos_HiliteReflect_init(&house_clock->clock.pos, play);
            break;
        case aHC_ENV_MAP_XLU:
            _texture_z_light_fog_prim_xlu(game->graph);
            Setpos_HiliteReflect_xlu_init(&house_clock->clock.pos, play);
            break;
    }
}

static int aHC_DrawClockBefore(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                               u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    HOUSE_CLOCK_ACTOR* house_clock = (HOUSE_CLOCK_ACTOR*)arg;
    s16 clock_num = house_clock->clock.clock_num;

    if (joint_idx == aHC_draw_data[clock_num].short_joint_no || joint_idx == aHC_draw_data[clock_num].long_joint_no) {
        *joint_shape = NULL;
    }

    return TRUE;
}

static int aHC_DrawClockAfter(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                               u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    HOUSE_CLOCK_ACTOR* house_clock = (HOUSE_CLOCK_ACTOR*)arg;
    s16 clock_num = house_clock->clock.clock_num;
    xyz_t pos;
    xyz_t ofs = { 0.0f, 0.0f, 0.0f };

    if (clock_num == aHC_TYPE_MUSEUM) {
        Global_kankyo_set_room_prim(game);
    }

    if (joint_idx == aHC_draw_data[clock_num].short_joint_no) {
        OPEN_DISP(game->graph);

        Matrix_Position(&ofs, &pos);
        Matrix_push();
        Matrix_translate(pos.x, pos.y, pos.z, MTX_LOAD);
        Matrix_RotateZ(DEG2SHORT_ANGLE2(90.0f) - Common_Get(time).rad_hour, MTX_MULT);
        Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);
        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        Matrix_pull();
        gSPDisplayList(NEXT_POLY_OPA_DISP, aHC_draw_data[clock_num].short_model);

        CLOSE_DISP(game->graph);
    } else if (joint_idx == aHC_draw_data[clock_num].long_joint_no) {
        OPEN_DISP(game->graph);

        Matrix_Position(&ofs, &pos);
        Matrix_push();
        Matrix_translate(pos.x, pos.y, pos.z, MTX_LOAD);
        Matrix_RotateZ(DEG2SHORT_ANGLE2(90.0f) - Common_Get(time).rad_min, MTX_MULT);
        Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);
        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        Matrix_pull();
        gSPDisplayList(NEXT_POLY_OPA_DISP, aHC_draw_data[clock_num].long_model);

        CLOSE_DISP(game->graph);
    }

    return TRUE;
}

static void aHC_DrawClock(ACTOR* actorx, GAME* game) {
    HOUSE_CLOCK_ACTOR* house_clock = (HOUSE_CLOCK_ACTOR*)actorx;
    int idx = game->frame_counter & 1;
    N64Mtx* mtx = house_clock->clock.mtx[idx];

    _texture_z_light_fog_prim(game->graph);
    OPEN_DISP(game->graph);

    Matrix_translate(house_clock->clock.pos.x, house_clock->clock.pos.y, house_clock->clock.pos.z, MTX_LOAD);
    Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    CLOSE_DISP(game->graph);

    cKF_Si3_draw_R_SV(game, &house_clock->clock.keyframe, mtx, &aHC_DrawClockBefore, &aHC_DrawClockAfter, actorx);
}

static void House_Clock_Actor_draw(ACTOR* actorx, GAME* game) {
    aHC_SetEnvMapping(actorx, game);
    aHC_DrawClock(actorx, game);
}

static void aHC_OperateAnime(ACTOR* actorx, GAME* game) {
    HOUSE_CLOCK_ACTOR* house_clock = (HOUSE_CLOCK_ACTOR*)actorx;
    aHC_clock_c* clock = &house_clock->clock;
    cKF_SkeletonInfo_R_c* kf_p = &clock->keyframe;
    f32 prev_frame = house_clock->phase_frame;
    f32 frame = prev_frame + (f32)game->graph->dt_num_60fps_frames;

    while (frame >= 120.0f) {
        frame -= 120.0f;
    }
    house_clock->phase_frame = frame;

    if (aHC_CrossedFrame(prev_frame, frame, 0.0f)) {
        cKF_SkeletonInfo_R_init_standard_repeat(kf_p, aHC_draw_data[clock->clock_num].animation, NULL);
        cKF_SkeletonInfo_R_play(kf_p);
        kf_p->frame_control.speed = 0.5f;
    }

    if (aHC_CrossedFrame(prev_frame, frame, 15.0f) || aHC_CrossedFrame(prev_frame, frame, 45.0f)) {
        sAdo_OngenTrgStart(NA_SE_12D, &clock->pos);
    }
}

static void House_Clock_Actor_move(ACTOR* actorx, GAME* game) {
    HOUSE_CLOCK_ACTOR* house_clock = (HOUSE_CLOCK_ACTOR*)actorx;
    aHC_clock_c* clock = &house_clock->clock;
    cKF_SkeletonInfo_R_c* kf_p = &clock->keyframe;

    cKF_SkeletonInfo_R_play(kf_p);
    kf_p->frame_control.speed = 0.5f;
    aHC_OperateAnime(actorx, game);
}
