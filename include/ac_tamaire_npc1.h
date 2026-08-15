#ifndef AC_TAMAIRE_NPC1_H
#define AC_TAMAIRE_NPC1_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tamaire_npc1_actor_s TAMAIRE_NPC1_ACTOR;

typedef void (*aTMN1_THINK_PROC)(TAMAIRE_NPC1_ACTOR* actor, GAME_PLAY* play);
typedef void (*aTMN1_TALK_PROC)(TAMAIRE_NPC1_ACTOR* actor, GAME_PLAY* play);

struct tamaire_npc1_actor_s {
    NPC_ACTOR npc_class;
    aTMN1_THINK_PROC think_proc;
    aTMN1_TALK_PROC talk_proc;
    int base_msg;
    s16 timer;
    s16 move_pos[2];
    s16 yasiro_pos[2];
    u8 think_idx;
    u8 next_think_idx;
    u8 move_think_idx;
    u8 talk_idx;
    u8 change_flag;
    u8 left;
    u8 right;
#ifdef TARGET_PC
    f32 timer_accum;
#endif
};

extern ACTOR_PROFILE Tamaire_Npc1_Profile;

#ifdef __cplusplus
}
#endif

#endif
