#ifndef AC_NPC_CURATOR_H
#define AC_NPC_CURATOR_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aCR_SLEEP_WAIT_TIMER  (6 * 60) // 6 seconds (calculated in frames frames)
#define aCR_SLEEP_TIME_START  ( 6 * mTM_SECONDS_IN_HOUR)
#define aCR_SLEEP_TIME_END    (18 * mTM_SECONDS_IN_HOUR)

typedef struct npc_curator_actor_s NPC_CURATOR_ACTOR;

typedef void (*aCR_SETUPTALKACTION_PROC)(NPC_CURATOR_ACTOR*, GAME_PLAY*, int);
typedef void (*aCR_ACTION_PROC)(NPC_ACTOR*, GAME_PLAY*);
typedef void (*aCR_ACT_PROC)(NPC_CURATOR_ACTOR*, GAME_PLAY*);
typedef void (*aCR_TALK_ACT_PROC)(NPC_CURATOR_ACTOR*, GAME_PLAY*);

struct npc_curator_actor_s {
  NPC_ACTOR npc_class;
  int action;
  aCR_ACT_PROC action_proc;
  int sleep_wait_timer;
  int talk_act_idx;
  aCR_TALK_ACT_PROC talk_proc;
  aCR_SETUPTALKACTION_PROC setupTalkAction_proc;
  int msg_no;
  int _9B0; // might be unused 'awake' state
  mActor_name_t donated_item;
#ifdef TARGET_PC
  f32 sleep_wait_accum;
#endif
};

extern ACTOR_PROFILE Npc_Curator_Profile;

#ifdef __cplusplus
}
#endif

#endif

