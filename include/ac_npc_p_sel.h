#ifndef AC_NPC_P_SEL_H
#define AC_NPC_P_SEL_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct npc_p_sel_s NPC_P_SEL_ACTOR;

typedef void (*aNPS_TALK_PROC)(NPC_P_SEL_ACTOR*, GAME_PLAY*);

/* sizeof(NPC_P_SEL_ACTOR) == 0x9B0 */
struct npc_p_sel_s {
    /* 0x000 */ NPC_ACTOR npc_class;
    /* 0x994 */ int talk_idx;
    /* 0x998 */ int next_talk_idx;
    /* 0x99C */ aNPS_TALK_PROC talk_proc;
    /* 0x9A0 */ int talk_end_flag;
    /* 0x9A4 */ f32 silent_counter;
    /* 0x9A8 */ f32 strum_timer;
    /* 0x9AC */ f32 bgm_stop_timer;
};

extern ACTOR_PROFILE Npc_P_Sel_Profile;

#ifdef __cplusplus
}
#endif

#endif

