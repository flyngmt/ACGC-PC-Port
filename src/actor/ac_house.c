#include "ac_house.h"

#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_bgm.h"
#include "sys_matrix.h"
#include "m_rcp.h"
#include "m_debug.h"

enum {
    aHUS_ACTION_WAIT,
    aHUS_ACTION_OPEN_DOOR_WAIT,
    aHUS_ACTION_OPEN_DOOR,
    aHUS_ACTION_NEXT_SCENE_WAIT,

    aHUS_ACTION_NUM
};

enum {
    aHUS_MSG_NONE,
    aHUS_MSG_AWAY,
    aHUS_MSG_SLEEP,
    
    aHUS_MSG_NUM
};

enum {
    aHUS_REQUEST_NPC_CLOSE_DOOR,
    aHUS_REQUEST_NPC_OPEN_DOOR,
    aHUS_REQUEST_PLAYER_ENTER,
    aHUS_REQUEST_PLAYER_LEAVE,

    aHUS_REQUEST_NUM
};

#define aHUS_GET_LOOKS(h) ((h)->arg0)
#ifdef TARGET_PC
#define aHUS_GET_ANIMAL_P(h) (Save_GetPointer(animals[(h)->arg2]))
#else
#define aHUS_GET_ANIMAL_P(h) ((Animal_c*)(h)->arg1)
#endif
#define aHUS_GET_ANIMAL_IDX(h) ((h)->arg2)
#define aHUS_GET_LIGHT_PERCENT(h) ((h)->arg1_f)

#define aHUS_SET_LOOKS(h, v) ((h)->arg0 = (v))
#ifdef TARGET_PC
#define aHUS_SET_ANIMAL_P(h, v)
#else
#define aHUS_SET_ANIMAL_P(h, v) ((h)->arg1 = (int)(v))
#endif
#define aHUS_SET_ANIMAL_IDX(h, v) ((h)->arg2 = (v))
#define aHUS_SET_LIGHT_PERCENT(h, v) ((h)->arg1_f = (v))

static void aHUS_actor_ct(ACTOR* actorx, GAME* game);
static void aHUS_actor_dt(ACTOR* actorx, GAME* game);
static void aHUS_actor_init(ACTOR* actorx, GAME* game);
static void aHUS_actor_move(ACTOR* actorx, GAME* game);
static void aHUS_actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE House_Profile = {
    mAc_PROFILE_HOUSE,
    ACTOR_PART_ITEM,
    ACTOR_STATE_NONE,
    NPC_HOUSE_START,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(HOUSE_ACTOR),
    &aHUS_actor_ct,
    &aHUS_actor_dt,
    &aHUS_actor_init,
    &aHUS_actor_draw,
    NULL,
};
// clang-format on

static void aHUS_setup_animation(HOUSE_ACTOR* house, f32 speed);
static void aHUS_setup_action(HOUSE_ACTOR* house, int action);
static void change_FGUnit(ACTOR* actorx, int keep_flag);
static void aHUS_set_bgOffset(ACTOR* actorx, int idx);
static f32 aHUS_ctrl_light(HOUSE_ACTOR* house);

extern Vtx obj_house1_shadow_v[];
extern Gfx obj_house1_shadow_model[];

extern Vtx obj_s_house2_shadow_v[];
extern Gfx obj_s_house2_shadow_model[];

extern Vtx obj_s_house3_shadow_v[];
extern Gfx obj_s_house3_shadow_model[];

extern Vtx obj_s_house4_shadow_v[];
extern Gfx obj_s_house4_shadow_model[];

extern Vtx obj_s_house5_shadow_v[];
extern Gfx obj_s_house5_shadow_model[];

// clang-format off
static u8 aHUS_shadow_vtx_fix_flg_table0[] = {
    TRUE, FALSE, FALSE, TRUE,
    FALSE, TRUE, TRUE, FALSE,
    FALSE, TRUE, TRUE, FALSE,
    TRUE, FALSE, FALSE, TRUE,
    FALSE, TRUE, FALSE, TRUE,
};
// clang-format on

// clang-format off
static u8 aHUS_shadow_vtx_fix_flg_table1[] = {
    TRUE, FALSE, FALSE, TRUE,
    FALSE, TRUE, FALSE, TRUE,
    TRUE, FALSE, FALSE, TRUE,
    TRUE, FALSE, FALSE, TRUE,
    TRUE, FALSE, FALSE, TRUE,
    FALSE, TRUE, TRUE, FALSE,
    TRUE, FALSE, FALSE, TRUE,
};
// clang-format on

// clang-format off
static u8 aHUS_shadow_vtx_fix_flg_table2[] = {
    TRUE, FALSE, FALSE, TRUE,
    FALSE, TRUE, FALSE, TRUE,
    TRUE, FALSE, FALSE, TRUE,
    TRUE, FALSE, FALSE, TRUE,
    TRUE, FALSE, FALSE, TRUE,
    FALSE, TRUE, TRUE, FALSE,
};
// clang-format on

static bIT_ShadowData_c aHUS_shadow_data0 = {
    ARRAY_COUNT(aHUS_shadow_vtx_fix_flg_table0),
    aHUS_shadow_vtx_fix_flg_table0,
    60.0f,
    obj_house1_shadow_v,
    obj_house1_shadow_model,
};

static bIT_ShadowData_c aHUS_shadow_data1 = {
    ARRAY_COUNT(aHUS_shadow_vtx_fix_flg_table1),
    aHUS_shadow_vtx_fix_flg_table1,
    60.0f,
    obj_s_house2_shadow_v,
    obj_s_house2_shadow_model,
};

static bIT_ShadowData_c aHUS_shadow_data2 = {
    ARRAY_COUNT(aHUS_shadow_vtx_fix_flg_table2),
    aHUS_shadow_vtx_fix_flg_table2,
    60.0f,
    obj_s_house3_shadow_v,
    obj_s_house3_shadow_model,
};

static bIT_ShadowData_c aHUS_shadow_data3 = {
    ARRAY_COUNT(aHUS_shadow_vtx_fix_flg_table1),
    aHUS_shadow_vtx_fix_flg_table1,
    60.0f,
    obj_s_house4_shadow_v,
    obj_s_house4_shadow_model,
};

static bIT_ShadowData_c aHUS_shadow_data4 = {
    ARRAY_COUNT(aHUS_shadow_vtx_fix_flg_table1),
    aHUS_shadow_vtx_fix_flg_table1,
    60.0f,
    obj_s_house5_shadow_v,
    obj_s_house5_shadow_model,
};

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_house1;
extern cKF_Skeleton_R_c cKF_bs_r_obj_s_house2;
extern cKF_Skeleton_R_c cKF_bs_r_obj_s_house3;
extern cKF_Skeleton_R_c cKF_bs_r_obj_s_house4;
extern cKF_Skeleton_R_c cKF_bs_r_obj_s_house5;

extern cKF_Skeleton_R_c cKF_bs_r_obj_w_house1;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_house2;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_house3;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_house4;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_house5;

// clang-format off
static cKF_Skeleton_R_c* aHUS_house_model_normal[] = {
    &cKF_bs_r_obj_s_house1,
    &cKF_bs_r_obj_s_house2,
    &cKF_bs_r_obj_s_house3,
    &cKF_bs_r_obj_s_house4,
    &cKF_bs_r_obj_s_house5,
};
// clang-format on

// clang-format off
static cKF_Skeleton_R_c* aHUS_house_model_winter[] = {
    &cKF_bs_r_obj_w_house1,
    &cKF_bs_r_obj_w_house2,
    &cKF_bs_r_obj_w_house3,
    &cKF_bs_r_obj_w_house4,
    &cKF_bs_r_obj_w_house5,
};
// clang-format on

static cKF_Skeleton_R_c** aHUS_house_model[] = { aHUS_house_model_normal, aHUS_house_model_winter };

// clang-format off
static bIT_ShadowData_c* aHUS_shadow_data[] = {
    &aHUS_shadow_data0,
    &aHUS_shadow_data1,
    &aHUS_shadow_data2,
    &aHUS_shadow_data3,
    &aHUS_shadow_data4,
};
// clang-format on

static void aHUS_actor_ct(ACTOR* actorx, GAME* game) {
    HOUSE_ACTOR* house = (HOUSE_ACTOR*)actorx;
    int season;
    s16 shape;
    s16 pal;
    int idx = mNpc_SearchAnimalinfo(Save_Get(animals), NPC_START + (actorx->npc_id - NPC_HOUSE_START), ANIMAL_NUM_MAX);

    if (idx >= 0) {
        aHUS_SET_LOOKS(house, mNpc_GetLooks(Common_Get(npclist[idx]).name));
        aHUS_SET_ANIMAL_P(house, Save_GetPointer(animals[idx]));
        aHUS_SET_ANIMAL_IDX(house, idx);
        house->season = Common_Get(time.season);
        season = house->season == mTM_SEASON_WINTER;
        shape = Common_Get(npclist[idx]).house_data.type;
        pal = Common_Get(npclist[idx]).house_data.palette;
        house->structure_type = aSTR_TYPE_HOUSE1 + shape;
        house->structure_pal = aSTR_PAL_HOUSE1_A + (s16)(pal + (shape * 5));
    } else {
        aHUS_SET_LOOKS(house, mNpc_LOOKS_GIRL);
        aHUS_SET_ANIMAL_P(house, Save_GetPointer(animals[0]));
        aHUS_SET_ANIMAL_IDX(house, 0);
        house->season = Common_Get(time.season);
        shape = 0;
        pal = 0;
        season = house->season == mTM_SEASON_WINTER;
        house->structure_type = aSTR_TYPE_HOUSE1;
        house->structure_pal = aSTR_PAL_HOUSE1_A;
    }

    cKF_SkeletonInfo_R_ct(&house->keyframe, aHUS_house_model[season][shape], NULL, house->work_area, house->morph_area);
    aHUS_set_bgOffset(actorx, 1);
    change_FGUnit(actorx, TRUE);
    aHUS_setup_action(house, aHUS_ACTION_WAIT);
    aHUS_setup_animation(house, 0.0f);
    cKF_SkeletonInfo_R_play(&house->keyframe);
    aHUS_SET_LIGHT_PERCENT(house, aHUS_ctrl_light(house));
}

static void aHUS_actor_dt(ACTOR* actorx, GAME* game) {
    HOUSE_ACTOR* house = (HOUSE_ACTOR*)actorx;

    change_FGUnit(actorx, FALSE);
    cKF_SkeletonInfo_R_dt(&house->keyframe);
}

#include "../src/actor/ac_house_move.c_inc"
#include "../src/actor/ac_house_draw.c_inc"
