#ifndef AC_NPC_MASK_CAT2_H
#define AC_NPC_MASK_CAT2_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct npc_mask_cat2_s NPC_MASK_CAT2_ACTOR;
typedef void (*aNM2_TALK_PROC)(NPC_MASK_CAT2_ACTOR*, GAME_PLAY*);
typedef void (*aNM2_INIT_PROC)(NPC_MASK_CAT2_ACTOR*, GAME_PLAY*);
typedef void (*aNM2_MOVE_PROC)(ACTOR*, GAME*);

/* sizeof(np_mask_cat2) == 0x9d0 */
struct npc_mask_cat2_s {
    /* 0x000 */ NPC_ACTOR npc_class;
    /* 0x994 */ int action;
    /* 0x998 */ aNM2_MOVE_PROC move_proc;
    /* 0x99C */ BOOL lock_camera_flag;
#ifdef TARGET_PC
    /* 0x9A0 */ f32 camera_morph_counter;
#else
    /* 0x9A0 */ int camera_morph_counter;
#endif
    /* 0x9A4 */ s16 camera_move;
    /* 0x9A6 */ s8 camera_move_cnt;
    /* 0x9A7 */ s8 camera_move_set_counter;
    /* 0x9A8 */ float camera_move_y;
    /* 0x9AC */ float camera_move_range;
    /* 0x9B0 */ ACTOR* train_door_actor;
    /* 0x9B4 */ int obj_look_type;
    /* 0x9B8 */ float obj_dist_ground;
    /* 0x9BC */ BOOL camera_eyes_flag;
    /* 0x9C0 */ float wait_timer;
#ifdef TARGET_PC
    /* 0x9C4 */ f32 conductor_spawn_timer;
#else
    /* 0x9C4 */ int conductor_spawn_timer;
#endif
    /* 0x9C8 */ u32 arg;
    /* 0x9CC */ ACTOR* sasho_actor;
};

extern ACTOR_PROFILE Npc_Mask_Cat2_Profile;
// clang-format off
enum {
    aNM2_INIT_ANNOUNCE_START_WAIT,        // 0
    aNM2_INIT_NONE_1,                     // 1
    aNM2_INIT_NONE_2,                     // 2
    aNM2_INIT_NONE_3,                     // 3
    aNM2_INIT_ANNOUNCE_START_WAIT2,       // 4
    aNM2_INIT_NONE_4,                     // 5
    aNM2_INIT_NONE_5,                     // 6
    aNM2_INIT_NONE_6,                     // 7
    aNM2_INIT_WALK_DECK,                  // 8
    aNM2_INIT_TURN_DECK,                  // 9
    aNM2_INIT_KEITAI_OFF_START_WAIT,      // 10
    aNM2_INIT_KEITAI_OFF_END_WAIT,        // 11
    aNM2_INIT_NONE_7,                     // 12
    aNM2_INIT_NONE_8,                     // 13
    aNM2_INIT_APPROACH,                   // 14
    aNM2_INIT_TALK_START_WAIT,            // 15
    aNM2_INIT_TALK_START_WAIT2,           // 16
    aNM2_INIT_SITDOWN_START_WAIT,         // 17
    aNM2_INIT_SITDOWN,                    // 18
    aNM2_INIT_NONE_9,                     // 19
    aNM2_INIT_DRAW_MENU_OPEN_WAIT,        // 20
    aNM2_INIT_DRAW_MENU_CLOSE_WAIT,       // 21
    aNM2_INIT_MSG_WIN_OPEN_WAIT,          // 22
    aNM2_INIT_TALK_END_WAIT,              // 23
    aNM2_INIT_SCENE_CHANGE_WAIT,          // 24

    aNM2_INIT_PROC_NUM
};

enum {
    aNM2_MOVE_ANNOUNCE_START_WAIT,       // 0
    aNM2_MOVE_SAVE_START_WAIT,           // 1
    aNM2_MOVE_SAVE_END_WAIT,             // 2
    aNM2_MOVE_ANNOUNCE_END_WAIT,         // 3
    aNM2_MOVE_ANNOUNCE_START_WAIT_DUPE_1,// 4
    aNM2_MOVE_SAVE_START_WAIT_DUPE_1,    // 5
    aNM2_MOVE_SAVE_END_WAIT_DUPE_1,      // 6
    aNM2_MOVE_ANNOUNCE_END_WAIT_DUPE_1,  // 7
    aNM2_MOVE_WALK_DECK,                 // 8
    aNM2_MOVE_TURN_DECK,                 // 9
    aNM2_MOVE_KEITAI_OFF_START_WAIT,     // 10
    aNM2_MOVE_KEITAI_OFF_END_WAIT,       // 11
    aNM2_MOVE_ENTER,                     // 12
    aNM2_MOVE_ENTER_DUPE_1,              // 13
    aNM2_MOVE_APPROACH,                  // 14
    aNM2_MOVE_TALK_START_WAIT,           // 15
    aNM2_MOVE_TALK_START_WAIT2,          // 16
    aNM2_MOVE_SITDOWN_START_WAIT,        // 17
    aNM2_MOVE_SITDOWN,                   // 18
    aNM2_MOVE_SDON_AND_PB_WAIT,          // 19
    aNM2_MOVE_DRAW_MENU_OPEN_WAIT,       // 20
    aNM2_MOVE_DRAW_MENU_CLOSE_WAIT,      // 21
    aNM2_MOVE_MSG_WIN_OPEN_WAIT,         // 22
    aNM2_MOVE_TALK_END_WAIT,             // 23
    aNM2_MOVE_NONE,                      // 24

    aNM2_MOVE_PROC_NUM
};

// clang-format on
#ifdef __cplusplus
}
#endif

#endif
