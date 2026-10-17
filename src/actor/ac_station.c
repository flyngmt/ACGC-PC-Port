#include "ac_station.h"

#include "m_name_table.h"
#include "bg_item_h.h"
#include "m_common_data.h"
#include "m_house.h"
#include "m_player_lib.h"
#include "m_demo.h"
#include "ac_intro_demo.h"
#include "m_bgm.h"
#include "sys_matrix.h"
#include "m_rcp.h"
#include "libforest/gbi_extensions.h"
#include "ac_station_clip.h"
#include "ac_npc_station_master.h"
#include "m_msg.h"
#include "m_font.h"
#include "m_string.h"
#include "m_card.h"
#include "m_cpak.h"
#ifdef TARGET_PC
#include "pc_town_select.h"
#endif

enum {
    aSTA_ACTION_WAIT,

    aSTA_ACTION_NUM
};

static void aSTA_actor_ct(ACTOR* actorx, GAME* game);
static void aSTA_actor_dt(ACTOR* actorx, GAME* game);
static void aSTA_actor_init(ACTOR* actorx, GAME* game);
static void aSTA_actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Station_Profile = {
    mAc_PROFILE_STATION,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET,
    TRAIN_STATION,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(STATION_ACTOR),
    &aSTA_actor_ct,
    &aSTA_actor_dt,
    &aSTA_actor_init,
    &aSTA_actor_draw,
    NULL
};
// clang-format on

// clang-format off
static u8 aSTA_shadow_vtx_fix_flg_table0[] = {
    FALSE, FALSE, TRUE, TRUE,
    FALSE, FALSE, TRUE, TRUE,
    FALSE, TRUE, TRUE, FALSE,
    TRUE, TRUE, FALSE, FALSE,
    TRUE, TRUE, FALSE, FALSE,
    TRUE, FALSE, TRUE, TRUE,
    TRUE, FALSE, FALSE, TRUE,
    TRUE, TRUE, FALSE,
};
// clang-format on

// clang-format off
static u8 aSTA_shadow_vtx_fix_flg_table1[] = {
    TRUE,   FALSE,   FALSE,   TRUE,
    TRUE,   FALSE,   TRUE,   FALSE,
    TRUE,   FALSE,   TRUE,   FALSE,
    TRUE,   FALSE,   TRUE,   FALSE,
    TRUE,   FALSE,   TRUE,   FALSE,
    TRUE,   FALSE,   FALSE,   TRUE,
    TRUE,   FALSE,   FALSE,   TRUE,
    TRUE,   FALSE,   FALSE,   TRUE,
    TRUE,   FALSE,   FALSE,   TRUE,
    TRUE,   FALSE,   FALSE,   TRUE,
    TRUE,   FALSE,   FALSE,   TRUE,
    FALSE,   TRUE,   TRUE,   TRUE,
    FALSE,   FALSE,   TRUE,   TRUE,
    FALSE,   TRUE,   TRUE,   FALSE,
    FALSE,   TRUE,   TRUE,   FALSE,
    FALSE,   TRUE,   TRUE,   TRUE,
};
// clang-format on

// clang-format off
static u8 aSTA_shadow_vtx_fix_flg_table2[] = {
    FALSE,   TRUE,   TRUE,   FALSE,
    FALSE,   TRUE,   TRUE,   FALSE,
    TRUE,   FALSE,   FALSE,   FALSE,
    FALSE,   FALSE,   TRUE,   TRUE,
    TRUE,   TRUE,   TRUE,   TRUE,
    TRUE,   FALSE,   TRUE,   FALSE,
    FALSE,   TRUE,   FALSE,   FALSE,
    TRUE,   TRUE,   FALSE,   TRUE,
    TRUE,   FALSE,   FALSE,   FALSE,
    TRUE,   FALSE,   FALSE,   FALSE,
    TRUE,   FALSE,   TRUE,   TRUE,
    TRUE,   FALSE,   FALSE,   TRUE,
    TRUE,   FALSE,   FALSE,   TRUE,
    TRUE,   TRUE,   FALSE,   FALSE,
    TRUE,   TRUE,   FALSE,   TRUE,
    TRUE,   FALSE,
};
// clang-format on

extern Vtx obj_station1_shadow_v[];
extern Vtx obj_station2_shadow_v[];
extern Vtx obj_station3_shadow_v[];

extern Gfx obj_station1_shadow_lowT_model[];
extern Gfx obj_station1_shadow_hiT_model[];
extern Gfx obj_station2_shadow_low_model[];
extern Gfx obj_station2_shadow_hi_model[];
extern Gfx obj_station3_shadow_low_model[];
extern Gfx obj_station3_shadow_hi_model[];

// clang-format off
static bIT_ShadowData_c aSTA_shadow_low_data0 = {
    ARRAY_COUNT(aSTA_shadow_vtx_fix_flg_table0),
    aSTA_shadow_vtx_fix_flg_table0,
    60.0f,
    obj_station1_shadow_v,
    obj_station1_shadow_lowT_model,
};
// clang-format on

// clang-format off
static bIT_ShadowData_c aSTA_shadow_hi_data0 = {
    ARRAY_COUNT(aSTA_shadow_vtx_fix_flg_table0),
    aSTA_shadow_vtx_fix_flg_table0,
    60.0f,
    obj_station1_shadow_v,
    obj_station1_shadow_hiT_model,
};
// clang-format on

// clang-format off
static bIT_ShadowData_c aSTA_shadow_low_data1 = {
    ARRAY_COUNT(aSTA_shadow_vtx_fix_flg_table1),
    aSTA_shadow_vtx_fix_flg_table1,
    60.0f,
    obj_station2_shadow_v,
    obj_station2_shadow_low_model,
};
// clang-format on

// clang-format off
static bIT_ShadowData_c aSTA_shadow_hi_data1 = {
    ARRAY_COUNT(aSTA_shadow_vtx_fix_flg_table1),
    aSTA_shadow_vtx_fix_flg_table1,
    60.0f,
    obj_station2_shadow_v,
    obj_station2_shadow_hi_model,
};
// clang-format on

// clang-format off
static bIT_ShadowData_c aSTA_shadow_low_data2 = {
    ARRAY_COUNT(aSTA_shadow_vtx_fix_flg_table2),
    aSTA_shadow_vtx_fix_flg_table2,
    60.0f,
    obj_station3_shadow_v,
    obj_station3_shadow_low_model,
};
// clang-format on

// clang-format off
static bIT_ShadowData_c aSTA_shadow_hi_data2 = {
    ARRAY_COUNT(aSTA_shadow_vtx_fix_flg_table2),
    aSTA_shadow_vtx_fix_flg_table2,
    60.0f,
    obj_station3_shadow_v,
    obj_station3_shadow_hi_model,
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_station1;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_station1;
extern cKF_Skeleton_R_c cKF_bs_r_obj_s_station2;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_station2;
extern cKF_Skeleton_R_c cKF_bs_r_obj_s_station3;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_station3;

extern cKF_Animation_R_c cKF_ba_r_obj_s_station1;
extern cKF_Animation_R_c cKF_ba_r_obj_w_station1;
extern cKF_Animation_R_c cKF_ba_r_obj_s_station2;
extern cKF_Animation_R_c cKF_ba_r_obj_w_station2;
extern cKF_Animation_R_c cKF_ba_r_obj_s_station3;
extern cKF_Animation_R_c cKF_ba_r_obj_w_station3;

static void aSTA_setup_action(STATION_ACTOR* station, int action);
static void aSTC_clip_ct(void);
static void aSTC_clip_dt(void);

static void aSTA_actor_ct(ACTOR* actorx, GAME* game) {
    // clang-format off
    static cKF_Skeleton_R_c* skl[][2] = {
        { &cKF_bs_r_obj_s_station1, &cKF_bs_r_obj_w_station1 },
        { &cKF_bs_r_obj_s_station2, &cKF_bs_r_obj_w_station2 },
        { &cKF_bs_r_obj_s_station3, &cKF_bs_r_obj_w_station3 },
    };
    // clang-format on

    STATION_ACTOR* station = (STATION_ACTOR*)actorx;
    int season;
    int type = Save_Get(station_type);

    station->struct_class.season = Common_Get(time).season;
    season = station->struct_class.season == mTM_SEASON_WINTER;
    station->struct_class.arg0 = type / 5;
    station->struct_class.structure_type = aSTR_TYPE_STATION1 + station->struct_class.arg0;
    station->struct_class.structure_pal = aSTR_PAL_STATION1_A + type;
    
    cKF_SkeletonInfo_R_ct(&station->struct_class.keyframe,
                          skl[station->struct_class.arg0][season], NULL,
                          station->struct_class.work_area, station->struct_class.morph_area);
    aSTA_setup_action(station, aSTA_ACTION_WAIT);
    actorx->world.position.x += -mFI_UT_WORLDSIZE_HALF_X_F;
    actorx->cull_width = 1260.0f;
    actorx->cull_radius = 420.0f;
    station->struct_class.keyframe_state = cKF_SkeletonInfo_R_play(&station->struct_class.keyframe);
    aSTC_clip_ct();
}

static void aSTA_actor_dt(ACTOR* actorx, GAME* game) {
    STATION_ACTOR* station = (STATION_ACTOR*)actorx;

    cKF_SkeletonInfo_R_dt(&station->struct_class.keyframe);
    actorx->world.position.x = actorx->world.position.x - -mFI_UT_WORLDSIZE_HALF_X_F;
    aSTC_clip_dt();
}

#include "../src/actor/ac_station_move.c_inc"
#include "../src/actor/ac_station_draw.c_inc"
#include "../src/actor/ac_station_clip.c_inc"
