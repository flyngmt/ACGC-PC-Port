#include "ac_cottage.h"

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

enum {
    Cottage_DATA_PLAYER_STANDARD,
    Cottage_DATA_PLAYER_WINTER,

    Cottage_DATA_NPC_STANDARD,
    Cottage_DATA_NPC_WINTER,

    Cottage_DATA_NUM
};

enum {
    Cottage_ACTION_NONE,
    Cottage_ACTION_DOOR_OPEN,
    Cottage_ACTION_OPEN_PL_OUT_INIT,
    Cottage_ACTION_OPEN_IN_INIT,
    Cottage_ACTION_NPC_OUT_INIT,
    Cottage_ACTION_SPEAK_GO_OUT,

    Cottage_ACTION_NUM
};

static void Cottage_my_actor_ct(ACTOR* actor, GAME* game);
static void Cottage_my_actor_dt(ACTOR* actor, GAME* game);

static void Cottage_npc_actor_ct(ACTOR* actor, GAME* game);
static void Cottage_npc_actor_dt(ACTOR* actor, GAME* game);

static void Cottage_actor_init(ACTOR* actor, GAME* game);
static void Cottage_actor_draw(ACTOR* actor, GAME* game);

// clang-format off
ACTOR_PROFILE Cottage_My_Profile = {
    mAc_PROFILE_COTTAGE_MY,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET,
    COTTAGE_MY,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(STRUCTURE_ACTOR),
    &Cottage_my_actor_ct,
    &Cottage_my_actor_dt,
    &Cottage_actor_init,
    &Cottage_actor_draw,
    NULL
};
// clang-format on

// clang-format off
ACTOR_PROFILE Cottage_Npc_Profile = {
    mAc_PROFILE_COTTAGE_NPC,
    ACTOR_PART_ITEM,
    ACTOR_STATE_NONE,
    COTTAGE_NPC,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(STRUCTURE_ACTOR),
    &Cottage_npc_actor_ct,
    &Cottage_npc_actor_dt,
    &Cottage_actor_init,
    &Cottage_actor_draw,
    NULL
};
// clang-format on

// clang-format off
static u8 Shadow_vtx_fix_flg_cottage_my[] = {
    FALSE, FALSE, TRUE, TRUE,
    FALSE, FALSE, TRUE, TRUE,
    TRUE, TRUE, FALSE, FALSE,
    FALSE, FALSE, TRUE, TRUE,
    TRUE, FALSE, TRUE, FALSE,
    FALSE, TRUE, FALSE, FALSE
};
// clang-format on

extern Vtx obj_s_myhome_i_shadow_v[];
extern Gfx obj_s_myhome_i_shadowT_model[];

// clang-format off
static bIT_ShadowData_c bIT_DR_SHADOW_c_cottage_my = {
    22,
    Shadow_vtx_fix_flg_cottage_my,
    60.0f,
    obj_s_myhome_i_shadow_v,
    obj_s_myhome_i_shadowT_model
};
// clang-format on

// clang-format off
static u8 Shadow_vtx_fix_flg_cottage_npc[] = {
    TRUE, FALSE, FALSE, TRUE,
    FALSE, FALSE, TRUE, TRUE,
    TRUE, FALSE, FALSE, TRUE,
    TRUE, FALSE, FALSE, TRUE,
    TRUE, TRUE, FALSE, FALSE,
    TRUE, TRUE, FALSE, FALSE,
    TRUE, FALSE, FALSE, TRUE
};
// clang-format on

extern Vtx obj_s_house_i_shadow_v[];
extern Gfx obj_s_house_i_shadowT_model[];

// clang-format off
static bIT_ShadowData_c bIT_DR_SHADOW_c_cottage_npc = {
    28,
    Shadow_vtx_fix_flg_cottage_npc,
    60.0f,
    obj_s_house_i_shadow_v,
    obj_s_house_i_shadowT_model
};
// clang-format on

// clang-format off
static Door_data_c Door_data_cottage_my = {
    SCENE_COTTAGE_MY,
    mSc_DIRECT_NORTH,
    FALSE,
    0,
    {200, 0, 380},
    EMPTY_NO,
    1,
    {0, 0, 0},
};
// clang-format on

// clang-format off
static Door_data_c Door_data_cottage_npc = {
    SCENE_COTTAGE_NPC,
    mSc_DIRECT_NORTH,
    FALSE,
    0,
    {160, 0, 300},
    EMPTY_NO,
    1,
    {0, 0, 0},
};
// clang-format on

// My cottage
static void Cottage_my_rewrite_door(ACTOR* actor, GAME_PLAY* play);
static void Cottage_my_set_bgOffset(STRUCTURE_ACTOR* cottage, int offs);
static int Cottage_my_check_door_pl_in(STRUCTURE_ACTOR* cottage, GAME_PLAY* play);
static int Cottage_my_check_go_out(STRUCTURE_ACTOR* cottage, GAME_PLAY* play);
static void Cottage_my_demo_door_open(ACTOR* actor);
static f32 Cottage_my_light_aim(STRUCTURE_ACTOR* cottage);
static void Cottage_my_ctrl_light(STRUCTURE_ACTOR* cottage);

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_myhome_i;
extern cKF_Animation_R_c cKF_ba_r_obj_s_myhome_i;
extern cKF_Animation_R_c cKF_ba_r_obj_s_myhome_i_out;
extern Gfx obj_s_myhome_i_window_model[];

// NPC cottage
static void Cottage_npc_rewrite_door(ACTOR* actor, GAME_PLAY* play);
static void Cottage_npc_set_bgOffset(STRUCTURE_ACTOR* cottage, int offs);
static int Cottage_npc_check_door_pl_in(STRUCTURE_ACTOR* cottage, GAME_PLAY* play);
static int Cottage_npc_check_go_out(STRUCTURE_ACTOR* cottage, GAME_PLAY* play);
static void Cottage_npc_demo_door_open(ACTOR* actor);
static f32 Cottage_npc_light_aim(STRUCTURE_ACTOR* cottage);
static void Cottage_npc_ctrl_light(STRUCTURE_ACTOR* cottage);

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_house_i;
extern cKF_Animation_R_c cKF_ba_r_obj_s_house_i;
extern cKF_Animation_R_c cKF_ba_r_obj_s_house_i_out;
extern Gfx obj_s_house_i_window_model[];

// clang-format off
static const COTTAGE_DATA Cottage_data[4] = {
    {
        &cKF_bs_r_obj_s_myhome_i,     // skl
        &cKF_ba_r_obj_s_myhome_i,     // in_anim
        &cKF_ba_r_obj_s_myhome_i_out, // out_anim
        aSTR_TYPE_COTTAGE_MY,         // structure_type
        aSTR_PAL_MYHOME_ISLAND,       // structure_palette
        obj_s_myhome_i_window_model,  // model
        &bIT_DR_SHADOW_c_cottage_my,  // shadow_data
        DUMMY_COTTAGE_MY,             // actor_name
        &Door_data_cottage_my,        // door_data
        &Cottage_my_rewrite_door,     // rewrite_door_proc
        &Cottage_my_set_bgOffset,     // set_bg_offset_proc
        &Cottage_my_check_door_pl_in, // check_door_in_proc
        &Cottage_my_check_go_out,     // check_door_out_proc
        &Cottage_my_demo_door_open,   // demo_door_open_proc
        &Cottage_my_light_aim,        // light_aim_proc
        &Cottage_my_ctrl_light        // light_control_proc
    },

    {
        &cKF_bs_r_obj_s_myhome_i,     // skl
        &cKF_ba_r_obj_s_myhome_i,     // in_anim
        &cKF_ba_r_obj_s_myhome_i_out, // out_anim
        aSTR_TYPE_COTTAGE_MY,         // structure_type
        aSTR_PAL_MYHOME_ISLAND,       // structure_palette
        obj_s_myhome_i_window_model,  // model
        &bIT_DR_SHADOW_c_cottage_my,  // shadow_data
        DUMMY_COTTAGE_MY,             // actor_name
        &Door_data_cottage_my,        // door_data
        &Cottage_my_rewrite_door,     // rewrite_door_proc
        &Cottage_my_set_bgOffset,     // set_bg_offset_proc
        &Cottage_my_check_door_pl_in, // check_door_in_proc
        &Cottage_my_check_go_out,     // check_door_out_proc
        &Cottage_my_demo_door_open,   // demo_door_open_proc
        &Cottage_my_light_aim,        // light_aim_proc
        &Cottage_my_ctrl_light        // light_control_proc
    },

    {
        &cKF_bs_r_obj_s_house_i,       // skl
        &cKF_ba_r_obj_s_house_i,       // in_anim
        &cKF_ba_r_obj_s_house_i_out,   // out_anim
        aSTR_TYPE_COTTAGE_NPC,         // structure_type
        aSTR_PAL_HOUSE_I,              // structure_palette
        obj_s_house_i_window_model,    // model
        &bIT_DR_SHADOW_c_cottage_npc,  // shadow_data
        DUMMY_COTTAGE_NPC,             // actor_name
        &Door_data_cottage_npc,        // door_data
        &Cottage_npc_rewrite_door,     // rewrite_door_proc
        &Cottage_npc_set_bgOffset,     // set_bg_offset_proc
        &Cottage_npc_check_door_pl_in, // check_door_in_proc
        &Cottage_npc_check_go_out,     // check_door_out_proc
        &Cottage_npc_demo_door_open,   // demo_door_open_proc
        &Cottage_npc_light_aim,        // light_aim_proc
        &Cottage_npc_ctrl_light        // light_control_proc
    },

    {
        &cKF_bs_r_obj_s_house_i,       // skl
        &cKF_ba_r_obj_s_house_i,       // in_anim
        &cKF_ba_r_obj_s_house_i_out,   // out_anim
        aSTR_TYPE_COTTAGE_NPC,         // structure_type
        aSTR_PAL_HOUSE_I,              // structure_palette
        obj_s_house_i_window_model,    // model
        &bIT_DR_SHADOW_c_cottage_npc,  // shadow_data
        DUMMY_COTTAGE_NPC,             // actor_name
        &Door_data_cottage_npc,        // door_data
        &Cottage_npc_rewrite_door,     // rewrite_door_proc
        &Cottage_npc_set_bgOffset,     // set_bg_offset_proc
        &Cottage_npc_check_door_pl_in, // check_door_in_proc
        &Cottage_npc_check_go_out,     // check_door_out_proc
        &Cottage_npc_demo_door_open,   // demo_door_open_proc
        &Cottage_npc_light_aim,        // light_aim_proc
        &Cottage_npc_ctrl_light        // light_control_proc
    }
};
// clang-format on

static const COTTAGE_DATA* Cottage_data_get(STRUCTURE_ACTOR* cottage) {
    return &Cottage_data[cottage->arg0];
}

static f32 Cottage_my_light_aim(STRUCTURE_ACTOR* cottage) {
    return mRmTp_Index2LightSwitchStatus(mRmTp_LIGHT_SWITCH_COTTAGE_MY) ? 1.0f : 0.0f;
}

static f32 Cottage_npc_light_aim(STRUCTURE_ACTOR* cottage) {
    int now_sec;
    Animal_c* island_villager;
    mNPS_schedule_c* schedule;

    island_villager = &Get_Island_Villager();
    schedule = mNPS_get_schedule_area(&island_villager->id);
    now_sec = Common_Get(time.now_sec);

// Aus changes the NPC islander cottage's lights to be on as long as they aren't asleep,
// instead of only being on when they're inside and awake.
#if VERSION >= VER_GAFU01_00
    if (schedule != NULL && schedule->current_type != mNPS_SCHED_SLEEP && island_villager->is_home != FALSE &&
#else
    if (schedule != NULL && schedule->current_type == mNPS_SCHED_IN_HOUSE && island_villager->is_home != FALSE &&
#endif
        (now_sec >= (18 * mTM_SECONDS_IN_HOUR) || now_sec <= (5 * mTM_SECONDS_IN_HOUR)) && cottage->request_type != Cottage_ACTION_OPEN_PL_OUT_INIT) {
        return 1.0f;
    }

    return 0.0f;
}

static void Cottage_my_ctrl_light(STRUCTURE_ACTOR* cottage) {
    cottage->arg0_f = Cottage_my_light_aim(cottage);
}

static void Cottage_npc_ctrl_light(STRUCTURE_ACTOR* cottage) {
    f32 target;
    target = Cottage_npc_light_aim(cottage);
    chase_f(&cottage->arg0_f, target, 0.019532442f);
}

static void Cottage_set_doorSE(STRUCTURE_ACTOR* cottage) {
    static const f32 chk_pat_in[] = { 10.0f, 14.0f, 35.0f, 50.0f };
    static const f32 chk_pat_out[] = { 2.0f, 8.0f, 33.0f, 40.0f };

    static const u16 se_no[] = { 6, 7, 8, 9 };

    const f32* chk_pat_p;
    int i;

    switch (cottage->request_type) {
        case Cottage_ACTION_DOOR_OPEN:
        case Cottage_ACTION_OPEN_IN_INIT:
            chk_pat_p = chk_pat_in;
            break;
        default:
            chk_pat_p = chk_pat_out;
            break;
    }

    for (i = 0; i < 4; ++i, chk_pat_p++) {
        if (cKF_FrameControl_passCheck_now(&cottage->keyframe.frame_control, *chk_pat_p) != FALSE) {
            sAdo_OngenTrgStart(se_no[i], &cottage->actor_class.world.position);
            break;
        }
    }
}

static int Cottage_my_check_door_pl_in(STRUCTURE_ACTOR* cottage, GAME_PLAY* play) {
    f32 xOffs;
    f32 zOffs;
    int y;
    PLAYER_ACTOR* player;

    player = GET_PLAYER_ACTOR(play);

    if (player != NULL) {
        xOffs = (player->actor_class.world.position.x - (cottage->actor_class.world.position.x + 20.0f));
        zOffs = (player->actor_class.world.position.z - (cottage->actor_class.world.position.z + 20.0f));

        if ((SQ(xOffs) + SQ(zOffs)) < 1600.0f && (xOffs + zOffs) < 40.0f) {
            y = player->actor_class.shape_info.rotation.y;
#ifdef TARGET_PC
            // -DEG2SHORT_ANGLE(180.0f) becomes +32768 on GCC (s16 cast wraps, unary minus
            // promotes to int) making the lower bound unreachable.
            if (y > -32768 && y < -DEG2SHORT_ANGLE(90.0f) && chkTrigger(BUTTON_A) != FALSE) {
#else
            if (y > -DEG2SHORT_ANGLE(180.0f) && y < -DEG2SHORT_ANGLE(90.0f) && chkTrigger(BUTTON_A) != FALSE) {
#endif
                return TRUE;
            }
        }
    }

    return FALSE;
}

static int Cottage_npc_check_door_pl_in(STRUCTURE_ACTOR* cottage, GAME_PLAY* play) {
    PLAYER_ACTOR* player;
    const COTTAGE_DATA* cottage_data;

    player = GET_PLAYER_ACTOR(play);
    cottage_data = Cottage_data_get(cottage);

    return (player != NULL && player->item_in_front == cottage_data->actor_name && chkTrigger(BUTTON_A) != FALSE);
}

static int Cottage_my_check_go_out(STRUCTURE_ACTOR* cottage, GAME_PLAY* play) {
    return FALSE;
}

static int Cottage_npc_check_go_out(STRUCTURE_ACTOR* cottage, GAME_PLAY* play) {
    Animal_c* island_villager;
    mNPS_schedule_c* schedule;
    int res;

    island_villager = &Get_Island_Villager();
    schedule = mNPS_get_schedule_area(&island_villager->id);
    res = FALSE;

    if (island_villager->is_home != FALSE && schedule != NULL && schedule->current_type == mNPS_SCHED_SLEEP) {
        res = TRUE;
    }

    return res;
}

static int Cottage_check_door_action(STRUCTURE_ACTOR* cottage, GAME_PLAY* play) {
    const COTTAGE_DATA* cottage_data;
    int res;
    int request_type;

    GET_PLAYER_ACTOR(play);
    res = Cottage_ACTION_NONE;
    cottage_data = Cottage_data_get(cottage);

    request_type = cottage->request_type;
    if ((*cottage_data->check_door_in_proc)(cottage, play) != FALSE) {
        if ((*cottage_data->check_door_out_proc)(cottage, play) != FALSE) {
            res = Cottage_ACTION_SPEAK_GO_OUT;
        } else {
            res = Cottage_ACTION_DOOR_OPEN;
            cottage->request_type = Cottage_ACTION_OPEN_IN_INIT;
        }
    } else {
        if (request_type == Cottage_ACTION_DOOR_OPEN) {
            res = Cottage_ACTION_OPEN_IN_INIT;
        } else if (request_type == Cottage_ACTION_OPEN_PL_OUT_INIT) {
            res = Cottage_ACTION_NPC_OUT_INIT;
        } else if (request_type == Cottage_ACTION_NPC_OUT_INIT && mPlib_check_player_outdoor_start(&play->game) != FALSE) {
            res = Cottage_ACTION_OPEN_PL_OUT_INIT;
        }
    }

    return res;
}

static void Cottage_reset_door_action(STRUCTURE_ACTOR* cottage) {
    cottage->request_type = Cottage_ACTION_NONE;
    cottage->arg1 = Cottage_ACTION_NONE;
}

static void Cottage_my_set_bgOffset(STRUCTURE_ACTOR* cottage, int offs) {
    // clang-format off
    static const s_xz unit_offset[] = {
        { -1, -1 },
        { 0, -1 },
        { 1, -1 },
        { 2, -1 },
        { -1, 0 },
        { 0, 0 },
        { 1, 0 },
        { 2, 0 },
        { -1, 1 },
        { 0, 1 },
        { 1, 1 },
        { 2, 1 },
        { -1, 2 },
        { 0, 2 },
        { 1, 2 },
        { 2, 2 }
    };
    // clang-format on

    // clang-format off
    static const mCoBG_OffsetTable_c rewrite_data[] = {
        { mCoBG_ATTRIBUTE_NONE, 4, 4, 4, 4, 4, 0 },
        { mCoBG_ATTRIBUTE_NONE, 10, 4, 10, 10, 10, 1 },
        { mCoBG_ATTRIBUTE_NONE, 10, 10, 10, 10, 4, 1 },
        { mCoBG_ATTRIBUTE_NONE, 4, 4, 4, 4, 4, 0 },
        { mCoBG_ATTRIBUTE_NONE, 10, 4, 10, 10, 10, 1 },
        { mCoBG_ATTRIBUTE_NONE, 10, 10, 10, 10, 10, 0 },
        { mCoBG_ATTRIBUTE_NONE, 10, 10, 10, 10, 10, 0 },
        { mCoBG_ATTRIBUTE_NONE, 4, 4, 4, 4, 4, 0 },
        { mCoBG_ATTRIBUTE_NONE, 10, 10, 4, 10, 10, 1 },
        { mCoBG_ATTRIBUTE_NONE, 10, 10, 10, 10, 10, 0 },
        { mCoBG_ATTRIBUTE_NONE, 10, 10, 10, 0, 10, 1 },
        { mCoBG_ATTRIBUTE_NONE, 0, 0, 0, 0, 0, 0 },
        { mCoBG_ATTRIBUTE_NONE, 4, 4, 4, 4, 4, 0 },
        { mCoBG_ATTRIBUTE_NONE, 4, 4, 4, 4, 4, 0 },
        { mCoBG_ATTRIBUTE_NONE, 0, 0, 0, 0, 0, 0 },
        { mCoBG_ATTRIBUTE_NONE, 0, 0, 0, 0, 0, 0 }
    };
    // clang-format on

    xyz_t pos;
    int i;

    pos.y = 0.0f;
    for (i = 0; i < 16; i++) {
        pos.x = cottage->actor_class.home.position.x + ((mFI_UT_WORLDSIZE_X_F * (f32)unit_offset[i].x));
        pos.z = cottage->actor_class.home.position.z + ((mFI_UT_WORLDSIZE_Z_F * (f32)unit_offset[i].z));

#if VERSION >= VER_GAFU01_00
        mCoBG_SetPluss5PointOffset_file(pos, rewrite_data[i], __FILE__, 790);
#else
        mCoBG_SetPluss5PointOffset_file(pos, rewrite_data[i], __FILE__, 787);
#endif
    }
}

static void Cottage_npc_set_bgOffset(STRUCTURE_ACTOR* cottage, int offs) {
    // clang-format off
    static mCoBG_OffsetTable_c height_table_ct[] = {
        { mCoBG_ATTRIBUTE_NONE, 7, 7, 7, 7, 7, 0 },
        { mCoBG_ATTRIBUTE_NONE, 0, 0, 0, 0, 0, 0 },
        { mCoBG_ATTRIBUTE_NONE, 7, 7, 7, 7, 7, 0 },
        { mCoBG_ATTRIBUTE_NONE, 7, 7, 7, 7, 7, 0 },
        { mCoBG_ATTRIBUTE_NONE, 7, 7, 7, 7, 7, 0 },
        { mCoBG_ATTRIBUTE_NONE, 7, 7, 7, 7, 7, 0 },
        { mCoBG_ATTRIBUTE_NONE, 7, 7, 7, 7, 7, 0 },
        { mCoBG_ATTRIBUTE_NONE, 7, 7, 7, 7, 7, 0 },
        { mCoBG_ATTRIBUTE_NONE, 7, 7, 7, 7, 7, 0 }
    };
    // clang-format on

    static mCoBG_OffsetTable_c* height_table[] = { height_table_ct, height_table_ct };

    static f32 addX[] = { -mFI_UT_WORLDSIZE_X_F, 0.0f, mFI_UT_WORLDSIZE_X_F };
    static f32 addZ[] = { mFI_UT_WORLDSIZE_Z_F, 0.0f, -mFI_UT_WORLDSIZE_Z_F };

    mCoBG_OffsetTable_c* offset;
    int i;
    xyz_t pos;

    offset = height_table[offs];
    for (i = 0; i < 3; i++) {
#if VERSION >= VER_GAFU01_00
        pos.z = cottage->actor_class.home.position.z + addZ[i];

        pos.x = cottage->actor_class.home.position.x + addX[0];
        mCoBG_SetPluss5PointOffset_file(pos, offset[0], __FILE__, 839);

        pos.x = cottage->actor_class.home.position.x + addX[1];
        mCoBG_SetPluss5PointOffset_file(pos, offset[1], __FILE__, 843);

        pos.x = cottage->actor_class.home.position.x + addX[2];
        mCoBG_SetPluss5PointOffset_file(pos, offset[2], __FILE__, 847);
#else
        pos.z = cottage->actor_class.home.position.z + addZ[i];

        pos.x = cottage->actor_class.home.position.x + addX[0];
        mCoBG_SetPluss5PointOffset_file(pos, offset[0], __FILE__, 836);

        pos.x = cottage->actor_class.home.position.x + addX[1];
        mCoBG_SetPluss5PointOffset_file(pos, offset[1], __FILE__, 840);

        pos.x = cottage->actor_class.home.position.x + addX[2];
        mCoBG_SetPluss5PointOffset_file(pos, offset[2], __FILE__, 844);
#endif

        offset += 3;
    }
}

static void Cottage_change_FGUnit(ACTOR* actor, int type) {
    xyz_t pos;

    xyz_t_move(&pos, &actor->world.position);
    pos.z += 80.0f;

    if (type == 0) {
        return;
    }

    mFI_SetFG_common(RSV_NO, pos, TRUE);
}

static void Cottage_my_rewrite_door(ACTOR* actor, GAME_PLAY* play) {
    Door_data_c* door_data;
    xyz_t pos;

    door_data = Common_GetPointer(structure_exit_door_data);
    if (play->fb_wipe_mode != WIPE_MODE_NONE) {
        return;
    }

    door_data->next_scene_id = Save_Get(scene_no);
    door_data->exit_orientation = mSc_DIRECT_SOUTH_EAST;
    door_data->exit_type = 0;
    door_data->extra_data = 2;

    pos.x = actor->world.position.x + 48.29f;
    pos.z = actor->world.position.z + 48.29f;
    pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(pos, 0.0f);

    door_data->exit_position.x = pos.x;
    door_data->exit_position.y = pos.y;
    door_data->exit_position.z = pos.z;

    door_data->door_actor_name = actor->npc_id;

    door_data->wipe_type = WIPE_TYPE_TRIFORCE;

    Common_Get(house_owner_name) = 0;
}

static void Cottage_npc_rewrite_door(ACTOR* actor, GAME_PLAY* play) {
    Door_data_c* door_data;
    xyz_t pos;

    door_data = Common_GetPointer(structure_exit_door_data);
    if (play->fb_wipe_mode != WIPE_MODE_NONE) {
        return;
    }

    door_data->next_scene_id = Save_Get(scene_no);
    door_data->exit_orientation = mSc_DIRECT_SOUTH;
    door_data->exit_type = 0;
    door_data->extra_data = 2;

    pos.x = actor->home.position.x;
    pos.z = actor->home.position.z + 60.0f;
    pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(pos, 0.0f);

    door_data->exit_position.x = pos.x;
    door_data->exit_position.y = pos.y;
    door_data->exit_position.z = pos.z;

    door_data->door_actor_name = actor->npc_id;

    door_data->wipe_type = WIPE_TYPE_TRIFORCE;

    Common_Get(house_owner_name) = 0;
}

static void Cottage_my_demo_door_open(ACTOR* actor) {
    mDemo_Set_house_info(0.0f, 3);
    mDemo_Set_camera(CAMERA2_PROCESS_DOOR);
}

static void Cottage_npc_demo_door_open(ACTOR* actor) {
    mDemo_Set_house_info(40.0f, 4);
    mDemo_Set_camera(CAMERA2_PROCESS_DOOR);
}

static void Cottage_demo_speak_go_out(ACTOR* actor) {
    static rgba_t window_color = { 145, 60, 40, 255 };

    Animal_c* island_villager;
    u8 looks;

    island_villager = &Get_Island_Villager();

    looks = mNpc_GetLooks(island_villager->id.npc_id);
    mDemo_Set_msg_num((looks & 0xFF) + MSG_ISLANDER_NOENTRY_SLEEPING_BASE);
    mDemo_Set_talk_display_name(FALSE);
    mDemo_Set_camera(TRUE);
    mPlib_Set_able_hand_all_item_in_demo(TRUE);
    mDemo_Set_ListenAble();
    mDemo_Set_talk_window_color(&window_color);
}

static void Cottage_actor_ct(ACTOR* actor, GAME* game) {
    STRUCTURE_ACTOR* cottage;
    cKF_SkeletonInfo_R_c* keyframe;
    const COTTAGE_DATA* cottage_data;

    cottage = (STRUCTURE_ACTOR*)actor;
    keyframe = &cottage->keyframe;
    cottage_data = Cottage_data_get(cottage);
    cKF_SkeletonInfo_R_ct(keyframe, cottage_data->skl, NULL, cottage->work_area, cottage->morph_area);
    cKF_SkeletonInfo_R_init(keyframe, keyframe->skeleton, cottage_data->in_anim, 1.0f, 51.0f, 1.0f, 0.5f, 0.0f, cKF_FRAMECONTROL_STOP,
                            NULL);
    cKF_SkeletonInfo_R_play(keyframe);
    (*cottage_data->set_bg_offset_proc)(cottage, 1);
    cottage->arg0_f = (*cottage_data->light_aim_proc)(cottage);
}

static void Cottage_move_closed_init(STRUCTURE_ACTOR* cottage);

static void Cottage_my_actor_ct(ACTOR* actor, GAME* game) {
    STRUCTURE_ACTOR* cottage;

    cottage = (STRUCTURE_ACTOR*)actor;

    if (Common_Get(time.season) == mTM_SEASON_WINTER) {
        cottage->arg0 = Cottage_DATA_PLAYER_WINTER;
    } else {
        cottage->arg0 = Cottage_DATA_PLAYER_STANDARD;
    }

    actor->world.position.x += 20.0f;
    actor->world.position.z += 20.0f;

    Cottage_actor_ct(actor, game);
    Cottage_move_closed_init(cottage);
}

static void Cottage_npc_actor_ct(ACTOR* actor, GAME* game) {
    STRUCTURE_ACTOR* cottage;

    cottage = (STRUCTURE_ACTOR*)actor;

    if (Common_Get(time.season) == mTM_SEASON_WINTER) {
        cottage->arg0 = Cottage_DATA_NPC_WINTER;
    } else {
        cottage->arg0 = Cottage_DATA_NPC_STANDARD;
    }

    Cottage_actor_ct(actor, game);
    Cottage_change_FGUnit(actor, 1);
    Cottage_move_closed_init(cottage);
}

static void Cottage_actor_dt(ACTOR* actor, GAME* game) {
    STRUCTURE_ACTOR* cottage;

    cottage = (STRUCTURE_ACTOR*)actor;
    cKF_SkeletonInfo_R_dt(&cottage->keyframe);
}

static void Cottage_my_actor_dt(ACTOR* actor, GAME* game) {
    Cottage_actor_dt(actor, game);
}

static void Cottage_npc_actor_dt(ACTOR* actor, GAME* game) {
    Cottage_change_FGUnit(actor, 0);
    Cottage_actor_dt(actor, game);
}

static void Cottage_move_closed(STRUCTURE_ACTOR* cottage, GAME_PLAY* play);

static void Cottage_move_closed_init(STRUCTURE_ACTOR* cottage) {
    Cottage_reset_door_action(cottage);
    cottage->action_proc = &Cottage_move_closed;
}

static void Cottage_move_wait_pl_in_init(STRUCTURE_ACTOR* cottage);
static void Cottage_move_wait_pl_out_init(STRUCTURE_ACTOR* cottage);
static void Cottage_move_open_in_init(STRUCTURE_ACTOR* cottage);
static void Cottage_move_open_pl_out_init(STRUCTURE_ACTOR* cottage);
static void Cottage_move_open_npc_out_init(STRUCTURE_ACTOR* cottage);

static void Cottage_move_closed(STRUCTURE_ACTOR* cottage, GAME_PLAY* play) {
    int door_action;
    const COTTAGE_DATA* cottage_data;

    if (mDemo_Check(mDemo_TYPE_DOOR, &cottage->actor_class) != FALSE) {
        if (cottage->arg1 == Cottage_ACTION_DOOR_OPEN) {
            Cottage_move_wait_pl_in_init(cottage);
        } else {
            Cottage_move_wait_pl_out_init(cottage);
        }
        return;
    }

    if (mDemo_Check(mDemo_TYPE_SPEAK, &cottage->actor_class) != FALSE) {
        return;
    }

    door_action = Cottage_check_door_action(cottage, play);
    cottage_data = Cottage_data_get(cottage);
    if (door_action != Cottage_ACTION_NONE) {
        cottage->arg1 = door_action;
    }

    if (door_action == Cottage_ACTION_DOOR_OPEN) {
        mDemo_Request(mDemo_TYPE_DOOR, &cottage->actor_class, cottage_data->demo_door_open_proc);
    } else if (door_action == Cottage_ACTION_OPEN_IN_INIT) {
        Cottage_move_open_in_init(cottage);
    } else if (door_action == Cottage_ACTION_OPEN_PL_OUT_INIT) {
        Cottage_move_open_pl_out_init(cottage);
    } else if (door_action == Cottage_ACTION_NPC_OUT_INIT) {
        Cottage_move_open_npc_out_init(cottage);
    } else if (door_action == Cottage_ACTION_SPEAK_GO_OUT) {
        mDemo_Request(mDemo_TYPE_SPEAK, &cottage->actor_class, &Cottage_demo_speak_go_out);
    }
}

static void Cottage_move_wait_pl_in(STRUCTURE_ACTOR* cottage, GAME_PLAY* play);

static void Cottage_move_wait_pl_in_init(STRUCTURE_ACTOR* cottage) {
    cottage->action_proc = &Cottage_move_wait_pl_in;
}

static void Cottage_move_wait_pl_in(STRUCTURE_ACTOR* cottage, GAME_PLAY* play) {
    if ((*GET_PLAYER_ACTOR_NOW()->get_door_label_proc)(gamePT) != cottage) {
        return;
    }

    mBGMPsComp_make_ps_wipe(0x249);
    Cottage_move_open_in_init(cottage);
}

static void Cottage_move_wait_pl_out(STRUCTURE_ACTOR* cottage, GAME_PLAY* play);

static void Cottage_move_wait_pl_out_init(STRUCTURE_ACTOR* cottage) {
    cottage->action_proc = &Cottage_move_wait_pl_out;
}

static void Cottage_move_wait_pl_out(STRUCTURE_ACTOR* cottage, GAME_PLAY* play) {
    if (mPlib_check_player_outdoor_start(&play->game) == FALSE) {
        return;
    }

    Cottage_move_open_pl_out_init(cottage);
}

static void Cottage_move_open_in(STRUCTURE_ACTOR* cottage, GAME_PLAY* play);

static void Cottage_move_open_in_init(STRUCTURE_ACTOR* cottage) {
    const COTTAGE_DATA* cottage_data;
    cKF_SkeletonInfo_R_c* keyframe;

    keyframe = &cottage->keyframe;
    cottage_data = Cottage_data_get(cottage);

    cKF_SkeletonInfo_R_init(keyframe, keyframe->skeleton, cottage_data->in_anim, 1.0f, 51.0f, 1.0f, 0.5f, 0.0f, cKF_FRAMECONTROL_STOP,
                            NULL);
    cottage->action_proc = &Cottage_move_open_in;
}

static void Cottage_move_next_init(STRUCTURE_ACTOR* cottage);

static void Cottage_move_open_in(STRUCTURE_ACTOR* cottage, GAME_PLAY* play) {
    const COTTAGE_DATA* cottage_data;

    Cottage_set_doorSE(cottage);
    if (cKF_SkeletonInfo_R_play(&cottage->keyframe) != cKF_STATE_STOPPED) {
        return;
    }

    if (cottage->arg1 == Cottage_ACTION_DOOR_OPEN) {
        cottage_data = Cottage_data_get(cottage);

        (*cottage_data->rewrite_door_proc)(&cottage->actor_class, play);

        goto_other_scene(play, cottage_data->door_data, FALSE);

        play->fb_fade_type = FADE_TYPE_DEMO;
        mDemo_End(&cottage->actor_class);

        Cottage_move_next_init(cottage);
    } else {
        Cottage_move_closed_init(cottage);
    }
}

static void Cottage_move_open_out(STRUCTURE_ACTOR* cottage, GAME_PLAY* play);

static void Cottage_move_open_pl_out_init(STRUCTURE_ACTOR* cottage) {
    const COTTAGE_DATA* cottage_data;
    cKF_SkeletonInfo_R_c* keyframe;

    keyframe = &cottage->keyframe;
    cottage_data = Cottage_data_get(cottage);
    cKF_SkeletonInfo_R_init(keyframe, keyframe->skeleton, cottage_data->out_anim, 25.0f, 51.0f, 25.0f, 0.5f, 0.0f,
                            cKF_FRAMECONTROL_STOP, NULL);
    cottage->action_proc = Cottage_move_open_out;
}

static void Cottage_move_open_npc_out_init(STRUCTURE_ACTOR* cottage) {
    const COTTAGE_DATA* cottage_data;
    cKF_SkeletonInfo_R_c* keyframe;

    keyframe = &cottage->keyframe;
    cottage_data = Cottage_data_get(cottage);
    cKF_SkeletonInfo_R_init(keyframe, keyframe->skeleton, cottage_data->out_anim, 1.0f, 51.0f, 1.0f, 0.5f, 0.0f,
                            cKF_FRAMECONTROL_STOP, NULL);
    cottage->action_proc = Cottage_move_open_out;
}

static void Cottage_move_open_out(STRUCTURE_ACTOR* cottage, GAME_PLAY* play) {
    Cottage_set_doorSE(cottage);
    if (cKF_SkeletonInfo_R_play(&cottage->keyframe) != cKF_STATE_STOPPED) {
        return;
    }

    Cottage_move_closed_init(cottage);
}

static void Cottage_move_next(STRUCTURE_ACTOR* cottage, GAME_PLAY* play);

static void Cottage_move_next_init(STRUCTURE_ACTOR* cottage) {
    cottage->action_proc = &Cottage_move_next;
}

static void Cottage_move_next(STRUCTURE_ACTOR* cottage, GAME_PLAY* play) {
}

static void Cottage_actor_move(ACTOR* actor, GAME* game) {
    const COTTAGE_DATA* cottage_data;
    STRUCTURE_ACTOR* cottage;
    GAME_PLAY* play;

    cottage = (STRUCTURE_ACTOR*)actor;
    play = (GAME_PLAY*)game;

    cottage_data = Cottage_data_get(cottage);
    (*cottage->action_proc)(cottage, play);
    (*cottage_data->light_control_proc)(cottage);
}

static void Cottage_actor_init(ACTOR* actor, GAME* game) {
    const COTTAGE_DATA* cottage_data;
    STRUCTURE_ACTOR* cottage;
    xyz_t pos;

    cottage = (STRUCTURE_ACTOR*)actor;

    cottage_data = Cottage_data_get(cottage);

    pos = actor->home.position;
    mFI_SetFG_common(cottage_data->actor_name, pos, FALSE);

    Cottage_actor_move(actor, game);
    actor->mv_proc = Cottage_actor_move;
}

static int Cottage_actor_draw_before(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                                     u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    STRUCTURE_ACTOR* cottage;
    GRAPH* graph;
    f32 color;
    Gfx* gfx;

    cottage = (STRUCTURE_ACTOR*)arg;
    graph = game->graph;

    if (joint_idx == 5) {
        OPEN_DISP(graph);
        color = cottage->arg0_f;
        gfx = NOW_POLY_OPA_DISP;

        gDPSetPrimColor(gfx++, 0, 0, (int)(0.5f + (255.0f * color)), (int)(0.5f + (255.0f * color)),
                        (int)(0.5f + (150.0f * color)), 255);

        SET_POLY_OPA_DISP(gfx);
        CLOSE_DISP(graph);
    }

    if (joint_idx == 6) {
        *joint_shape = NULL;
    }

    return TRUE;
}

static int Cottage_actor_draw_after(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                                    u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {

    GRAPH* graph;
    Mtx* mtx;
    const COTTAGE_DATA* cottage_data;
    int l;
    int r;
    int g;
    int b;
    STRUCTURE_ACTOR* cottage;
    Gfx* gfx;

    cottage = (STRUCTURE_ACTOR*)arg;
    graph = game->graph;

    if (joint_idx == 6) {
        mtx = _Matrix_to_Mtx_new(graph);

        if (mtx != NULL) {
            cottage_data = Cottage_data_get(cottage);
            if (cottage->arg0_f > 0.0f) {
                r = 255;
                g = 255;
                b = 150;
                l = (0.5f + (120.0f * cottage->arg0_f));
            } else {
                l = 0;
                r = 0;
                g = 0;
                b = 0;
            }

            _texture_z_light_fog_prim_shadow(graph);

            OPEN_DISP(graph);
            gfx = NOW_SHADOW_DISP;

            gDPSetPrimColor(gfx++, 0, l, r, g, b, 0);
            gSPMatrix(gfx++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            gSPLoadGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | 0x00000050);
            gSPDisplayList(gfx++, cottage_data->model);

            gSPLoadGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH | 0x00000040);
            gSPDisplayList(gfx++, cottage_data->model);

            gSPClearGeometryMode(gfx++, 0x00000050);

            SET_SHADOW_DISP(gfx);
            CLOSE_DISP(graph);
        }
    }

    return TRUE;
}

static void Cottage_actor_draw(ACTOR* actor, GAME* game) {
    GRAPH* graph;
    cKF_SkeletonInfo_R_c* keyframe;
    Mtx* mtx;
    const COTTAGE_DATA* cottage_data;
    Gfx* gfx;
    u16* pal;
    GAME_PLAY* play;
    STRUCTURE_ACTOR* cottage;

    graph = game->graph;
    play = (GAME_PLAY*)game;
    cottage = (STRUCTURE_ACTOR*)actor;
    cottage_data = Cottage_data_get(cottage);
    keyframe = &cottage->keyframe;

    mtx = GRAPH_ALLOC_TYPE(graph, Mtx, (u32)keyframe->skeleton->num_shown_joints);
    if (mtx == NULL) {
        return;
    }

    pal = Common_Get(clip).structure_clip->get_pal_segment_proc(cottage_data->structure_palette);

    _texture_z_light_fog_prim_npc(graph);

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    gSPSegment(gfx++, G_MWO_SEGMENT_8, pal);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);

    cKF_Si3_draw_R_SV(game, keyframe, mtx, &Cottage_actor_draw_before, &Cottage_actor_draw_after, actor);
    (*Common_Get(clip).bg_item_clip->draw_shadow_proc)(game, cottage_data->shadow_data, TRUE);
}
