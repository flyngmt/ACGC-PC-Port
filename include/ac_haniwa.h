#ifndef AC_HANIWA_H
#define AC_HANIWA_H

#include "types.h"
#include "ac_common.h"
#include "m_collision_obj.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aHNW_JOINT_NUM 8

typedef struct actor_haniwa_s HANIWA_ACTOR;

typedef void (*HANIWA_ACTOR_PROC)(HANIWA_ACTOR*, GAME*);

enum haniwa_msg {
    aHNW_MSG_NO_OWNER,
    aHNW_MSG_PROCEEDS,
    aHNW_MSG_NORMAL,
    aHNW_MSG_OTHER_OWNER,
    aHNW_MSG_NEED_FRIEND,

    aHNW_MSG_NUM
};

enum haniwa_handover {
    aHNW_HANDOVER_YES,
    aHNW_HANDOVER_NO,

    aHNW_HANDOVER_NUM
};

enum haniwa_action {
    aHNW_ACTION_WAIT,
    aHNW_ACTION_DANCE,
    aHNW_ACTION_CHECK_PROCEEDS,
    aHNW_ACTION_TALK_WITH_MASTER,
    aHNW_ACTION_TALK_WITH_MASTER2,
    aHNW_ACTION_TALK_END_WAIT,
    aHNW_ACTION_MENU_OPEN_WAIT,
    aHNW_ACTION_MENU_END_WAIT,
    aHNW_ACTION_TALK_WITH_GUEST,
    aHNW_ACTION_MENU_OPEN_WAIT_FOR_GUEST,
    aHNW_ACTION_MENU_END_WAIT_FOR_GUEST,
    aHNW_ACTION_ROOF_CHECK,
    aHNW_ACTION_SAVE_CHECK,
    aHNW_ACTION_SAVE_END_WAIT,
    aHNW_ACTION_PL_APPROACH_DOOR,
    aHNW_ACTION_DOOR_OPEN_WAIT,
    aHNW_ACTION_DOOR_OPEN_TIMER,

    aHNW_ACTION_NUM
};

/* sizeof(HANIWA_ACTOR) == 0x288 */
struct actor_haniwa_s {
    /* 0x000 */ CMN_ACTOR common_actor_class;
    /* 0x210 */ char* bank_ram_start;
    /* 0x214 */ s_xyz keyframe_work_area[aHNW_JOINT_NUM];
    /* 0x244 */ s_xyz keyframe_morph_area[aHNW_JOINT_NUM];
    /* 0x274 */ HANIWA_ACTOR_PROC action_proc;
    /* 0x278 */ f32 anim_frame_speed;
    /* 0x27C */ int player_approach_door_stage;
    /* 0x280 */ u16 door_approach_frame;
    /* 0x282 */ u8 submenu_type;
    /* 0x283 */ u8 house_idx;
    /* 0x284 */ u8 playing_save_bgm;
#ifdef TARGET_PC
    f32 door_approach_accum;
#endif
};

extern ACTOR_PROFILE Haniwa_Profile;

#ifdef __cplusplus
}
#endif

#endif
