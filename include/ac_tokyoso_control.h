#ifndef AC_TOKYOSO_CONTROL_H
#define AC_TOKYOSO_CONTROL_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aTKC_LAP_NUM 4
#define aTKC_SUBLAP_NUM (2 * aTKC_LAP_NUM) // split into half of the circuit
#define aTKC_NPC_NUM 2

#define aTKC_ANGLE_FOR_LAP_COMPLETION 4000 // approximately 22 degrees

#define aTKC_FLAG_DELETE_NPC0 (1 << 0)
#define aTKC_FLAG_DELETE_NPC1 (1 << 1)
#define aTKC_FLAG_DELETE_NPC2 (1 << 2)
#define aTKC_FLAG_DELETE_NPC3 (1 << 3)
#define aTKC_FLAG_DELETE_NPC4 (1 << 4)
#define aTKC_FLAG_STRETCH_TEAM0 (1 << 5)
#define aTKC_FLAG_STRETCH_TEAM1 (1 << 6)
#define aTKC_FLAG_READY_TEAM0 (1 << 7)
#define aTKC_FLAG_READY_TEAM1 (1 << 8)
#define aTKC_FLAG_READY_SHOOTER (1 << 9)
#define aTKC_FLAG_RACE_ACTIVE (1 << 10)
#define aTKC_FLAG_KANSEN_TEAM0 (1 << 11)
#define aTKC_FLAG_KANSEN_TEAM1 (1 << 12)
#define aTKC_FLAG_GOAL_TEAM0 (1 << 13)
#define aTKC_FLAG_GOAL_TEAM1 (1 << 14)
#define aTKC_FLAG_15 (1 << 15)

#define aTKC_STRETCH_ALL (aTKC_FLAG_STRETCH_TEAM0 | aTKC_FLAG_STRETCH_TEAM1)
#define aTKC_STRETCH_MASK aTKC_STRETCH_ALL

#define aTKC_READY_ALL (aTKC_FLAG_READY_TEAM0 | aTKC_FLAG_READY_TEAM1 | aTKC_FLAG_READY_SHOOTER)
#define aTKC_READY_MASK aTKC_READY_ALL

#define aTKC_KANSEN_ALL (aTKC_FLAG_KANSEN_TEAM0 | aTKC_FLAG_KANSEN_TEAM1)
#define aTKC_KANSEN_MASK aTKC_KANSEN_ALL

#define aTKC_GOAL_ALL (aTKC_FLAG_GOAL_TEAM0 | aTKC_FLAG_GOAL_TEAM1)
#define aTKC_GOAL_MASK aTKC_GOAL_ALL

#define aTKC_NPCID2IDX(id) ((id - SP_NPC_EV_TOKYOSO_0))
#define aTKC_NPCID2TEAM(id) (aTKC_NPCID2IDX(id) & 1) // 0 = team 0, 1 = team 1
#define aTKC_NPCID2ROLE(id) (aTKC_NPCID2IDX(id) & 2) // 0 = runner, 2 = spectator
#define aTKC_NPCIDX2DELETEFLG(n) (aTKC_FLAG_DELETE_NPC0 << aTKC_NPCID2IDX(n))
#define aTKC_NPCIDX2STRETCHFLG(n) (aTKC_FLAG_STRETCH_TEAM0 << aTKC_NPCID2TEAM(n))
#define aTKC_NPCIDX2READYLFG(n) (aTKC_FLAG_READY_TEAM0 << aTKC_NPCID2TEAM(n))
#define aTKC_NPCIDX2KANSENFLG(n) (aTKC_FLAG_KANSEN_TEAM0 << aTKC_NPCID2TEAM(n))
#define aTKC_NPCIDX2GOALFLG(n) (aTKC_FLAG_GOAL_TEAM0 << aTKC_NPCID2TEAM(n))

enum {
    aTKC_GOAL_NONE,
    aTKC_GOAL_WON,
    aTKC_GOAL_LOSE,

    aTKC_GOAL_NUM
};

typedef struct ac_tokyoso_event_s {
    u8 _00;
    u8 _01;
    u16 flags;
    s16 yasiro_pos[3]; // shrine pos (wishing well in AC and e+)
    s16 pos_0A[2][2];
    s16 angle[2];
    s16 next_angle[2];
    u8 lap[2];
    u8 goal[2];
} aEv_tokyoso_c;

typedef void (*aTKC_NEXT_RUN_PROC)(ACTOR* actorx);
typedef s16 (*aTKC_GET_ANGLE_PROC)(ACTOR* actorx);
typedef void (*aTKC_RUN_PROC)(ACTOR* actorx);
typedef s16 (*aTKC_RUN_CHECK_PROC)(ACTOR* actorx);
typedef s16 (*aTKC_TOP_CHECK_PROC)(ACTOR* actorx);
typedef s16 (*aTKC_GOAL_CHECK_PROC)(ACTOR* actorx);
typedef void (*aTKC_NPC1_THINK_INIT_PROC)(ACTOR* actorx, GAME_PLAY* play, u8 type);
typedef void (*aTKC_NEXT_POS_PROC)(ACTOR* actorx, int idx);
typedef void (*aTKC_NEXT_WARMUP_PROC)(ACTOR* actorx);
typedef void (*aTKC_SET_TALK_REQUEST_PROC)(ACTOR* actorx);

typedef struct tokyoso_control_clip_s {
    aTKC_NEXT_RUN_PROC next_run_proc;
    aTKC_GET_ANGLE_PROC get_angle_proc;
    aTKC_RUN_PROC run_proc;
    aTKC_RUN_CHECK_PROC run_check_proc;
    aTKC_TOP_CHECK_PROC top_check_proc;
    aTKC_GOAL_CHECK_PROC goal_check_proc;
    aTKC_NPC1_THINK_INIT_PROC npc1_think_init_proc;
    aTKC_NEXT_POS_PROC next_pos_proc;
    aTKC_NEXT_WARMUP_PROC next_warmup_proc;
    aTKC_SET_TALK_REQUEST_PROC set_talk_request_proc;
} aTKC_clip_c;

typedef struct tokyoso_control_actor_s TOKYOSO_CONTROL_ACTOR;

typedef void (*aTKC_PROC)(TOKYOSO_CONTROL_ACTOR* actor, GAME_PLAY* play);

struct tokyoso_control_actor_s {
    ACTOR actor_class;
    aTKC_clip_c clip;
    aTKC_PROC act_proc;
    int action;
    s16 timer;
#ifdef TARGET_PC
    f32 logic_accum;
#endif
};

extern ACTOR_PROFILE Tokyoso_Control_Profile;

#ifdef __cplusplus
}
#endif

#endif
