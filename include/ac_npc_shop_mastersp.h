#ifndef AC_NPC_SHOP_MASTERSP_H
#define AC_NPC_SHOP_MASTERSP_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"
#include "m_shop.h"
#include "m_player_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aSHM_REQ_TICKET_NUM 5

#define aSHM_FIRST_PLACE_PERCENT 5
#define aSHM_SECOND_PLACE_PERCENT (10 + aSHM_FIRST_PLACE_PERCENT)
#define aSHM_THIRD_PLACE_PERCENT (20 + aSHM_SECOND_PLACE_PERCENT)

typedef struct npc_shop_mastersp_actor_s NPC_SHOP_MASTERSP_ACTOR;

typedef void (*aSHM_THINK_PROC)(NPC_SHOP_MASTERSP_ACTOR*, GAME_PLAY*);
typedef void (*aSHM_TALK_PROC)(NPC_SHOP_MASTERSP_ACTOR*, GAME_PLAY*);

struct npc_shop_mastersp_actor_s {
    NPC_ACTOR npc_class;
    int think_idx;
    int next_think_idx;
    int move_think_idx;
    aSHM_THINK_PROC think_proc;
    int talk_idx;
    aSHM_TALK_PROC talk_proc;
    s16 result;
    s16 timer;
    s16 root;
    s16 root_idx;
    s16 now_idx;
    int month;
    int ut[2];
    int melody_bak;
    s16 base_pos[11][2];
#ifdef TARGET_PC
    f32 timer_accum;
#endif
};

extern ACTOR_PROFILE Npc_Shop_Mastersp_Profile;

#ifdef __cplusplus
}
#endif

#endif
