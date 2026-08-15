#ifndef AC_COUNTDOWN_NPC1_H
#define AC_COUNTDOWN_NPC1_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct countdown_npc1_actor_s COUNTDOWN_NPC1_ACTOR;

typedef void (*aCD1_ACT_PROC)(COUNTDOWN_NPC1_ACTOR* actor);

struct countdown_npc1_actor_s {
    NPC_ACTOR npc_class;
    int action;
    int next_action;
    aCD1_ACT_PROC act_proc;
    int term;
    f32 fire_delay;
    int event_idx;
    s16 base_angle;
};

extern ACTOR_PROFILE Countdown_Npc1_Profile;

#ifdef __cplusplus
}
#endif

#endif
