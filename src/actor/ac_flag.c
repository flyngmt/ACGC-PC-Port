#include "ac_flag.h"

#include "m_name_table.h"
#include "sys_matrix.h"
#include "m_lib.h"
#include "m_rcp.h"
#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_msg.h"
#include "m_debug.h"
#include "m_needlework.h"
#include "m_needlework_ovl.h"
#include "libultra/libultra.h"

enum {
    aFLAG_ACTION_WAIT,
    aFLAG_ACTION_TALK,
    aFLAG_ACTION_TALK_END,
    aFLAG_ACTION_OPEN_WAIT,
    aFLAG_ACTION_END_WAIT,
    aFLAG_ACTION_UP,
    aFLAG_ACTION_DOWN,

    aFLAG_ACTION_NUM
};

static void aFLAG_actor_ct(ACTOR* actor, GAME* game);
static void aFLAG_actor_dt(ACTOR* actor, GAME* game);
static void aFLAG_actor_init(ACTOR* actor, GAME* game);
static void aFLAG_actor_draw(ACTOR* actor, GAME* game);

ACTOR_PROFILE Flag_Profile = {
    mAc_PROFILE_FLAG,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET,
    FLAG,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(STRUCTURE_ACTOR),
    &aFLAG_actor_ct,
    &aFLAG_actor_dt,
    &aFLAG_actor_init,
    &aFLAG_actor_draw,
    NULL,
};

static u8 aFLAG_shadow_vtx_fix_flg_table[8] = { FALSE, TRUE, TRUE, FALSE, TRUE, FALSE, FALSE, TRUE };

extern Vtx obj_frag_shadow_v[];
extern Gfx obj_frag_shadowT_model[];
static bIT_ShadowData_c aFLAG_shadow_data = { 8, aFLAG_shadow_vtx_fix_flg_table, 60.0f, obj_frag_shadow_v,
                                              obj_frag_shadowT_model };

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_frag;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_frag;
extern cKF_Animation_R_c cKF_ba_r_obj_s_frag;
extern cKF_Animation_R_c cKF_ba_r_obj_w_frag;

extern u8 hakushi_tex[];
extern u16 hakushi_pal[];

static void aFLAG_setup_action(STRUCTURE_ACTOR* flag, int action);

static void aFLAG_actor_ct(ACTOR* actor, GAME* game) {
    static cKF_Skeleton_R_c* skl[] = { &cKF_bs_r_obj_s_frag, &cKF_bs_r_obj_w_frag };
    static cKF_Animation_R_c* ani[] = { &cKF_ba_r_obj_s_frag, &cKF_ba_r_obj_w_frag };

    STRUCTURE_ACTOR* flag;
    int isWinter;

    flag = (STRUCTURE_ACTOR*)actor;
    isWinter = Common_Get(time.season) == mTM_SEASON_WINTER;
    flag->action = 32;
    flag->arg1_f = 132.5f;

    cKF_SkeletonInfo_R_ct(&flag->keyframe, skl[isWinter], ani[isWinter], flag->work_area, flag->morph_area);
    cKF_SkeletonInfo_R_init_standard_repeat(&flag->keyframe, ani[isWinter], NULL);
    cKF_SkeletonInfo_R_play(&flag->keyframe);

    aFLAG_setup_action(flag, aFLAG_ACTION_WAIT);
}

static void aFLAG_actor_dt(ACTOR* actor, GAME* game) {
    STRUCTURE_ACTOR* flag = (STRUCTURE_ACTOR*)actor;
    cKF_SkeletonInfo_R_dt(&flag->keyframe);
}

static void aFLAG_set_talk_info(ACTOR* actor) {
    rgba_t window_color;

    mDemo_Set_msg_num(MSG_12390);
    mDemo_Set_talk_display_name(FALSE);
    mDemo_Set_ListenAble();

    window_color.r = 185;
    window_color.g = 60;
    window_color.b = 40;
    window_color.a = 255;

    mDemo_Set_talk_window_color(&window_color);
    mDemo_Set_camera(TRUE);
    mDemo_Set_use_zoom_sound(TRUE);
}

static void aFLAG_talk_end(STRUCTURE_ACTOR* flag, GAME_PLAY* game_play) {
    mMsg_Window_c* msg_p = mMsg_Get_base_window_p();

    if (mMsg_Check_main_wait(msg_p) != FALSE) {
        mMsg_request_main_forceoff();
        aFLAG_setup_action(flag, aFLAG_ACTION_WAIT);
    }
}

static void aFLAG_talk(STRUCTURE_ACTOR* flag, GAME_PLAY* game_play) {
    mMsg_Window_c* msg_p;
    PLAYER_ACTOR* player_actor;
    s16 target_y;
    s_xyz target_rot;

    msg_p = mMsg_Get_base_window_p();
    if (mDemo_Check(mDemo_TYPE_TALK, (ACTOR*)flag) != FALSE) {
        player_actor = get_player_actor_withoutCheck(game_play);

        target_rot = player_actor->actor_class.shape_info.rotation;
        target_y = search_position_angleY(&player_actor->actor_class.world.position, &flag->actor_class.world.position);
        add_calc_short_angle2(&target_rot.y, target_y, 0.3f, 0x1000, 0x100);

        (*get_player_actor_withoutCheck((GAME_PLAY*)gamePT)->Set_force_position_angle_proc)(
            gamePT, NULL, &target_rot, mPlayer_FORCE_POSITION_ANGLE_ROTY);

        if (mMsg_Check_MainNormalContinue(msg_p) == TRUE) {
            switch (mChoice_Get_ChoseNum(mChoice_Get_base_window_p())) {
                case mChoice_CHOICE0:
                    mMsg_request_main_disappear_wait_type1(mMsg_Get_base_window_p());
                    aFLAG_setup_action(flag, aFLAG_ACTION_DOWN);
                    break;

                case mChoice_CHOICE1:
                    mMsg_request_main_disappear_wait_type1(mMsg_Get_base_window_p());
                    aFLAG_setup_action(flag, aFLAG_ACTION_TALK_END);
                    break;
            }
        }
    } else {
        aFLAG_setup_action(flag, aFLAG_ACTION_WAIT);
    }
}

static void aFLAG_wait(STRUCTURE_ACTOR* flag, GAME_PLAY* game_play) {
    PLAYER_ACTOR* player_actor;
    if (mDemo_Check(mDemo_TYPE_TALK, (ACTOR*)flag) == FALSE) {
        player_actor = get_player_actor_withoutCheck(game_play);
        if (player_actor != NULL) {
            mDemo_Request(mDemo_TYPE_TALK, (ACTOR*)flag, aFLAG_set_talk_info);
        }
    } else {
        aFLAG_setup_action(flag, aFLAG_ACTION_TALK);
    }
}

static void aFLAG_menu_open_wait(STRUCTURE_ACTOR* flag, GAME_PLAY* game_play) {
    mSM_open_submenu(&game_play->submenu, mSM_OVL_NEEDLEWORK, 0, common_data.player_no);
    aFLAG_setup_action(flag, aFLAG_ACTION_END_WAIT);
}

static void aFLAG_menu_end_wait(STRUCTURE_ACTOR* flag, GAME_PLAY* game_play) {
    Submenu* submenu;
    Submenu_Item_c* sm_item;
    u8 design_index;

    submenu = &game_play->submenu;
    if (submenu->open_flag == FALSE) {
        sm_item = submenu->item_p;
        if (sm_item->item == RSV_NO) {
            design_index = mNW_get_image_no(submenu, sm_item->slot_no) & 7;

            bcopy(Player_Design_Get(design_index), Save_GetPointer(island.flag_design.design),
                  sizeof(mNW_original_tex_c));
            osWritebackDCache(Save_GetPointer(island.flag_design.design), sizeof(mNW_original_tex_c));

            Save_Get(island.flag_design).flag_design_set = TRUE;
            Save_Get(island.flag_design).palette = Player_Palette_Get(design_index);

            sAdo_OngenTrgStart(0x461, &flag->actor_class.world.position);

            mISL_SetNowPlayerAction(4);
        }

        sAdo_OngenTrgStart(0x163, &flag->actor_class.world.position);
        aFLAG_setup_action(flag, aFLAG_ACTION_UP);
    }
}

static void aFLAG_up(STRUCTURE_ACTOR* flag, GAME_PLAY* game_play) {
    f32 starting_x;
    f32 middle_x;
    f32 ending_x;
    f32 ending_frame;
    f32 third_point_frame;
    f32 second_point_frame;
    f32 first_point_frame;
    f32 normalized_x_length;

    // Flag moves from bottom to top in two distinct "phases" as if the rope was pulled twice
    starting_x = 72.5f;
    middle_x = 110.0f;
    ending_x = 132.5f;
    ending_frame = 100.0f;
    third_point_frame = 70.0f;
    second_point_frame = 55.0f;
    first_point_frame = 15.0f;

    if (REGADDR(NMREG, 0) != 0) {
        starting_x = REGADDR(NMREG, 0);
    }

    if (REGADDR(NMREG, 1) != 0) {
        ending_x = REGADDR(NMREG, 1);
    }

    if (REGADDR(NMREG, 2) != 0) {
        middle_x = REGADDR(NMREG, 2);
    }

    if (REGADDR(NMREG, 3) != 0) {
        ending_frame = REGADDR(NMREG, 3);
    }

    if (REGADDR(NMREG, 4) != 0) {
        second_point_frame = REGADDR(NMREG, 4);
    }

    if (REGADDR(NMREG, 5) != 0) {
        first_point_frame = REGADDR(NMREG, 5);
    }

    if (REGADDR(NMREG, 6) != 0) {
        third_point_frame = REGADDR(NMREG, 6);
    }

    if (flag->arg1 == second_point_frame) {
        sAdo_OngenTrgStart(0x163U, &flag->actor_class.world.position);
    }

    if (flag->arg1 <= first_point_frame) {
        normalized_x_length = (middle_x - starting_x) / (first_point_frame * second_point_frame);
        flag->arg1_f = starting_x + (normalized_x_length * flag->arg1 * flag->arg1);
    } else if (flag->arg1 <= second_point_frame) {
        normalized_x_length = (middle_x - starting_x) / (second_point_frame * (first_point_frame - second_point_frame));
        flag->arg1_f =
            middle_x + (normalized_x_length * (flag->arg1 - second_point_frame) * (flag->arg1 - second_point_frame));
    } else if (flag->arg1 <= third_point_frame) {
        normalized_x_length =
            (ending_x - middle_x) / ((third_point_frame - second_point_frame) * (ending_frame - second_point_frame));
        flag->arg1_f =
            middle_x + (normalized_x_length * (flag->arg1 - second_point_frame) * (flag->arg1 - second_point_frame));
    } else {
        normalized_x_length =
            (ending_x - middle_x) / ((ending_frame - second_point_frame) *
                                     ((third_point_frame - second_point_frame) - (ending_frame - second_point_frame)));
        flag->arg1_f = ending_x + (normalized_x_length * (flag->arg1 - ending_frame) * (flag->arg1 - ending_frame));
    }

    flag->arg1 += 1;
    if (flag->arg1 >= ending_frame) {
        flag->arg1 = 0;
        mMsg_request_main_forceoff();
        aFLAG_setup_action(flag, aFLAG_ACTION_WAIT);
    }
}

static void aFLAG_down(STRUCTURE_ACTOR* flag, GAME_PLAY* game_play) {
    f32 normalized_x_length;
    f32 x_length;
    f32 starting_x;
    f32 ending_x;
    f32 ending_frame;
    f32 midpoint_frame;

    if (mMsg_Check_main_wait(mMsg_Get_base_window_p()) != FALSE) {
        // Flag moves down in a smooth motion from top to bottom
        starting_x = 72.5;
        ending_x = 132.5;
        ending_frame = 40.0f;
        midpoint_frame = 16.0f;

        if (REGADDR(NMREG, 0) != 0) {
            starting_x = REGADDR(NMREG, 0);
        }

        if (REGADDR(NMREG, 1) != 0) {
            ending_x = REGADDR(NMREG, 1);
        }

        if (REGADDR(NMREG, 7) != 0) {
            ending_frame = REGADDR(NMREG, 7);
        }

        if (REGADDR(NMREG, 8) != 0) {
            midpoint_frame = REGADDR(NMREG, 8);
        }

        x_length = ending_x - starting_x;
        if (flag->arg1 == 2) {
            sAdo_OngenTrgStart(0x164U, &flag->actor_class.world.position);
        }

        // arg1_f is used to set the joint x position
        if (flag->arg1 <= midpoint_frame) {
            normalized_x_length = -(x_length / (midpoint_frame * ending_frame));
            flag->arg1_f = ending_x + (flag->arg1 * (normalized_x_length * flag->arg1));
        } else {
            normalized_x_length = -(x_length / (ending_frame * (midpoint_frame - ending_frame)));
            flag->arg1_f =
                starting_x + (normalized_x_length * (flag->arg1 - ending_frame) * (flag->arg1 - ending_frame));
        }

        flag->arg1 += 1;
        if (flag->arg1 >= ending_frame) {
            flag->arg1 = 0;
            aFLAG_setup_action(flag, aFLAG_ACTION_OPEN_WAIT);
        }
    }
}

static void aFLAG_setup_action(STRUCTURE_ACTOR* flag, int action) {
    static aSTR_MOVE_PROC process[aFLAG_ACTION_NUM] = {
        &aFLAG_wait, &aFLAG_talk, &aFLAG_talk_end, &aFLAG_menu_open_wait, &aFLAG_menu_end_wait, &aFLAG_up, &aFLAG_down
    };

    flag->action_proc = process[action];
}

static void aFLAG_actor_move(ACTOR* actor, GAME* game) {
    STRUCTURE_ACTOR* flag;
    f32 wind_power;
    s16 wind_angle;

    flag = (STRUCTURE_ACTOR*)actor;

    wind_power = mEnv_GetWindPowerF();
    flag->arg0_f = wind_power;
    flag->keyframe.frame_control.speed = flag->arg0_f * 0.5f + 0.5f;

    wind_angle = mEnv_GetWindAngleS();
    flag->arg2_f = wind_angle;

    cKF_SkeletonInfo_R_play(&flag->keyframe);

    (*flag->action_proc)(flag, (GAME_PLAY*)game);
}

static void aFLAG_actor_init(ACTOR* actor, GAME* game) {
    mFI_SetFG_common(DUMMY_FLAG, actor->home.position, FALSE);
    aFLAG_actor_move(actor, game);
    actor->mv_proc = &aFLAG_actor_move;
}

static int aFLAG_before_draw(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_idx, Gfx** joint_shape,
                             u8* joint_flags, void* arg, s_xyz* joint_rot, xyz_t* joint_pos) {
    STRUCTURE_ACTOR* flag = (STRUCTURE_ACTOR*)arg;
    if (joint_idx == 4) {
        joint_pos->x = flag->arg1_f * 100.0f;
    }

    return TRUE;
}

static void aFLAG_actor_draw(ACTOR* actor, GAME* game) {
    GRAPH* graph;
    cKF_SkeletonInfo_R_c* keyframe;
    Gfx* gfx;
    N64Mtx* mtx;
    STRUCTURE_ACTOR* flag;
    u16* pal;
    u8* texture;

    flag = (STRUCTURE_ACTOR*)actor;
    graph = game->graph;
    keyframe = &flag->keyframe;
    mtx = GRAPH_ALLOC_TYPE(graph, N64Mtx, keyframe->skeleton->num_shown_joints);
    if (mtx != NULL) {
        _texture_z_light_fog_prim_npc(graph);
        _texture_z_light_fog_prim_xlu(graph);

        if (Save_Get(island.flag_design).flag_design_set != FALSE) {
            pal = mNW_PaletteIdx2Palette(Save_Get(island.flag_design).palette);
            texture = (u8*)Save_GetPointer(island.flag_design.design);
        } else {
            pal = hakushi_pal;
            texture = hakushi_tex;
        }

        OPEN_DISP(graph);
        gfx = NOW_POLY_OPA_DISP;

        gSPSegment(gfx++, G_MWO_SEGMENT_8, pal);
        gSPSegment(gfx++, G_MWO_SEGMENT_9, texture);

        SET_POLY_OPA_DISP(gfx);
        CLOSE_DISP(graph);

        cKF_Si3_draw_R_SV(game, keyframe, mtx, &aFLAG_before_draw, NULL, actor);
        (*Common_Get(clip).bg_item_clip->draw_shadow_proc)(game, &aFLAG_shadow_data, FALSE);
    }
}
