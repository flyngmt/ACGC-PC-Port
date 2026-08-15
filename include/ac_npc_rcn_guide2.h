#ifndef AC_NPC_RCN_GUIDE2_H
#define AC_NPC_RCN_GUIDE2_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct npc_rcn_guide2_s NPC_RCN_GUIDE2_ACTOR;

typedef void (*aNRG2_THINK_PROC)(NPC_RCN_GUIDE2_ACTOR*, GAME_PLAY*);
typedef void (*aNRG2_TALK_PROC)(NPC_RCN_GUIDE2_ACTOR*);

/* sizeof(NPC_RCN_GUIDE2_ACTOR) == 0x9BC */
struct npc_rcn_guide2_s {
    /* 0x000 */ NPC_ACTOR npc_class;
    /* 0x994 */ int _994;
    /* 0x998 */ int think_idx;
    /* 0x99C */ int next_think_idx;
    /* 0x9A0 */ aNRG2_THINK_PROC think_proc;
    /* 0x9A4 */ int talk_idx;
    /* 0x9A8 */ int talk_proc_idx;
    /* 0x9AC */ aNRG2_TALK_PROC talk_proc;
    /* 0x9B0 */ int counter;
    /* 0x9B4 */ int daily_speak_flag;
    /* 0x9B8 */ int can_ask_again_flag;
#ifdef TARGET_PC
    f32 wipe_wait_accum;
#endif
};

extern ACTOR_PROFILE Npc_Rcn_Guide2_Profile;

#ifdef __cplusplus
}
#endif

#endif
