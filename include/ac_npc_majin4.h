#ifndef AC_NPC_MAJIN4_H
#define AC_NPC_MAJIN4_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct npc_majin4_actor_s NPC_MAJIN4_ACTOR;

typedef void (*aMJN4_THINK_PROC)(NPC_MAJIN4_ACTOR* actor, GAME_PLAY* play);
typedef void (*aMJN4_TALK_PROC)(NPC_MAJIN4_ACTOR* actor, GAME_PLAY* play);

struct npc_majin4_actor_s {
    NPC_ACTOR npc_class;
    int think_idx;
    int next_think_idx;
    aMJN4_THINK_PROC think_proc;
    int talk_idx;
    aMJN4_TALK_PROC talk_proc;
    int reset_timer;
    int se_clear_timer;
#ifdef TARGET_PC
    f32 timing_accum;
#endif
};

extern ACTOR_PROFILE Npc_Majin4_Profile;

#ifdef __cplusplus
}
#endif

#endif
