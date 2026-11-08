#ifndef AC_T_NPC_SAO_H
#define AC_T_NPC_SAO_H

#include "types.h"
#include "m_actor.h"
#include "ac_tools.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct npc_sao_tool_s NPC_SAO_TOOL_ACTOR;
typedef void (*aTNS_ACTION_PROC)(NPC_SAO_TOOL_ACTOR*);

struct npc_sao_tool_s {
  TOOLS_ACTOR tool_class;
  aTNS_ACTION_PROC action_proc; // 0x1cc
  u8 action; // 0x1d0
  short rotation_y; // 0x1d2
  f32 pos_x; // 0x1d4
  f32 pos_y; // 0x1d8
  f32 pos_z; // 0x1dc
  f32 rotation_y_accum;
};

extern void aTNS_actor_ct(ACTOR* actorx, GAME* game);
extern void aTNS_actor_move(ACTOR* actorx, GAME* game);
extern void aTNS_actor_draw(ACTOR* actorx, GAME* game);

extern ACTOR_PROFILE T_NpcSao_Profile;

#ifdef __cplusplus
}
#endif

#endif

