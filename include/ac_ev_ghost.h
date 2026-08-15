#ifndef AC_EV_GHOST_H
#define AC_EV_GHOST_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aEGH_MINIMUM_GRASS_COUNT 8

#define aEGH_BIT_FOUND_GHOST 1

enum {
  aEGH_ITEM_LIST_FTR_A,
  aEGH_ITEM_LIST_FTR_B,
  aEGH_ITEM_LIST_FTR_C,
  aEGH_ITEM_LIST_FTR_EVENT,
  aEGH_ITEM_LIST_FTR_LOTTERY,
  aEGH_ITEM_LIST_CARPET_A,
  aEGH_ITEM_LIST_CARPET_B,
  aEGH_ITEM_LIST_CARPET_C,
  aEGH_ITEM_LIST_CARPET_EVENT,
  aEGH_ITEM_LIST_WALL_A,
  aEGH_ITEM_LIST_WALL_B,
  aEGH_ITEM_LIST_WALL_C,
  aEGH_ITEM_LIST_WALL_EVENT,
  aEGH_ITEM_LIST_CLOTH_A,
  aEGH_ITEM_LIST_CLOTH_B,
  aEGH_ITEM_LIST_CLOTH_C,
  aEGH_ITEM_LIST_CLOTH_EVENT,
  aEGH_ITEM_LIST_BINSEN_A,
  aEGH_ITEM_LIST_BINSEN_B,
  aEGH_ITEM_LIST_BINSEN_C,
  aEGH_ITEM_LIST_HANIWA,
  aEGH_ITEM_LIST_UMBRELLA,

  aEGH_ITEM_LIST_NUM
};

typedef struct ev_ghost_s EV_GHOST_ACTOR;

typedef void (*aEGH_PROC)(EV_GHOST_ACTOR*, GAME_PLAY*);

struct ev_ghost_s {
  /* 0x000 */ NPC_ACTOR npc_class;
  /* 0x994 */ aEGH_PROC think_proc;
  /* 0x998 */ int msg_no;
  /* 0x99C */ mActor_name_t give_item;
  /* 0x99E */ s16 bye_bye_angle;
  /* 0x9A0 */ u8 bye_bye_timer;
  /* 0x9A1 */ u8 bye_bye_scale_timer;
  /* 0x9A2 */ u8 bye_bye_transparency_delay_timer;
  /* 0x9A3 */ u8 think_act;
  /* 0x9A4 */ u8 after_talk_think_act;
  /* 0x9A5 */ u8 _9A5;
  /* 0x9A6 */ u8 talk_act;
  /* 0x9A7 */ u8 _9A7;
  /* 0x9A8 */ u8 melody_inst;
  /* 0x9A9 */ u8 alpha;
  /* 0x9AA */ u8 _9AA;
  /* 0x9AB */ u8 roof_pal;
  /* 0x9AC */ u8 _9AC;
#ifdef TARGET_PC
  f32 alpha_accum;
  f32 byebye_accum;
#endif
};

extern ACTOR_PROFILE Ev_Ghost_Profile;

#ifdef __cplusplus
}
#endif

#endif

