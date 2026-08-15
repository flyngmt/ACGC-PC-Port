#ifndef AC_TOKYOSO_NPC1_H
#define AC_TOKYOSO_NPC1_H

#include "lb_reki.h"
#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tokyoso_npc1_actor_s TOKYOSO_NPC1_ACTOR;

typedef void (*aTKN1_THINK_PROC)(TOKYOSO_NPC1_ACTOR* actor, GAME_PLAY* play);

struct tokyoso_npc1_actor_s {
    NPC_ACTOR npc_class;
    aTKN1_THINK_PROC think_proc;
    int base_msg;
    f32 speed;
    s16 timer;
    s16 start_pos[2];
    s16 run_timer;
    u8 think_idx;
    u8 next_think_idx;
    u8 move_think_idx;
    u8 talk_idx;
    u8 change_flag;
    u8 flags;
#ifdef TARGET_PC
    f32 timer_accum;
    f32 dash_effect_accum;
#endif
};

extern ACTOR_PROFILE Tokyoso_Npc1_Profile;

#ifdef __cplusplus
}
#endif

#endif
