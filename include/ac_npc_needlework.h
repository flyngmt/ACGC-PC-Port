#ifndef AC_NPC_NEEDLEWORK_H
#define AC_NPC_NEEDLEWORK_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aNNW_GBA_STATE_NOT_CONNECTED -1
#define aNNW_GBA_STATE_TRANSMITTING 0
#define aNNW_GBA_STATE_READY 1
#define aNNW_GBA_STATE_EDITOR_READY 2

#define aNNW_DESIGN_PRICE 350
#define aNNW_TALK_DAYS_MAX 10

enum {
    aNNW_SISTER0,
    aNNW_SISTER1,

    aNNW_SISTER_NUM
};

typedef struct npc_needlework_actor_s NPC_NEEDLEWORK_ACTOR;

typedef void (*aNNW_THINK_PROC)(NPC_NEEDLEWORK_ACTOR* actor, GAME_PLAY* play);

struct npc_needlework_actor_s {
    NPC_ACTOR npc_class;
    aNNW_THINK_PROC think_proc;
    f32 saved_keyframe_current;
    u8 design_name[mNW_ORIGINAL_DESIGN_NAME_LEN];
    u8 proc_delay_frames;
    u8 delay_frames;
    u8 _9AE;
    u8 think_idx;
    u8 think_idx_after_talk;
    u8 _9B1;
    u8 talk_idx;
    u8 _9B3;
    u8 _9B4;
    u8 buy_ut_idx;
    u8 _9B6;
    u8 my_proc_idx;
    u8 pl_area;
    u8 now_area;
    u8 sister_state;
    u8 _9BB;
    u8 gba_ready;
    u8 gba_wait_frames;
#ifdef TARGET_PC
    f32 proc_delay_accum;
    f32 delay_accum;
#endif
};

extern ACTOR_PROFILE Npc_Needlework_Profile;

#ifdef __cplusplus
}
#endif

#endif
