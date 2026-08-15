#ifndef AC_TUNAHIKI_CONTROL_H
#define AC_TUNAHIKI_CONTROL_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aTNC_FLAG_NPC_DELETE0 (1 << 0)
#define aTNC_FLAG_NPC_DELETE1 (1 << 1)
#define aTNC_FLAG_NPC_DELETE2 (1 << 2)
#define aTNC_FLAG_NPC_DELETE3 (1 << 3)
#define aTNC_FLAG_NPC_DELETE4 (1 << 4)
#define aTNC_FLAG_NPC_TALK0 (1 << 5)
#define aTNC_FLAG_NPC_TALK1 (1 << 6)
#define aTNC_FLAG_NPC_TALK2 (1 << 7)
#define aTNC_FLAG_NPC_TALK3 (1 << 8)
#define aTNC_FLAG_NPC_TALK4 (1 << 9)
#define aTNC_FLAG_NPC_TALK_ALL (aTNC_FLAG_NPC_TALK0 | aTNC_FLAG_NPC_TALK1 | aTNC_FLAG_NPC_TALK2 | aTNC_FLAG_NPC_TALK3 | aTNC_FLAG_NPC_TALK4)

#define aTNC_FLAG_SHAKE (1 << 15)

#define aTNC_NPCID2IDX(id) ((id - SP_NPC_EV_TUNAHIKI_0))
#define aTNC_NPCID2MEMBER(id) (aTNC_NPCID2IDX(id) & 1)
#define aTNC_NPCID2TEAM(id) (aTNC_NPCID2IDX(id) & 2)

#define aTNC_NPCIDX2DELETEFLG(n) (aTNC_FLAG_NPC_DELETE0 << aTNC_NPCID2IDX(n))
#define aTNC_NPCIDX2TALKFLG(n) (aTNC_FLAG_NPC_TALK0 << aTNC_NPCID2IDX(n))

enum {
    aTNC_NPC_STATE0,
    aTNC_NPC_STATE1,
    aTNC_NPC_STATE2,

    aTNC_NPC_STATE_NUM
};

typedef struct tunahiki_event_s {
    f32 rope;
    f32 rope_base;
    f32 speed;
    f32 next_speed;
    s16 npc_state;
    u16 flag;
    s16 _14;
    u16 counter;
} aEv_tunahiki_c;

typedef struct tunahiki_control_actor_s TUNAHIKI_CONTROL_ACTOR;

typedef void (*aTNC_PROC)(TUNAHIKI_CONTROL_ACTOR* actor, GAME_PLAY* play);

struct tunahiki_control_actor_s {
    ACTOR actor_class;
    aTNC_PROC act_proc;
    int action;
#ifdef TARGET_PC
    f32 logic_accum;
#endif
};

extern ACTOR_PROFILE Tunahiki_Control_Profile;

#ifdef __cplusplus
}
#endif

#endif
