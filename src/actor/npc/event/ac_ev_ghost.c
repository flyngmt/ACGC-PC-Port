#include "ac_ev_ghost.h"

#include "m_event.h"
#include "m_common_data.h"
#include "m_msg.h"
#include "m_string.h"
#include "libultra/libultra.h"
#include "m_player_lib.h"
#include "m_item_name.h"
#include "m_house.h"

enum {
  aEGH_TALK_END_WAIT,
  aEGH_TALK_GIVE_ME_WAIT,
  aEGH_TALK_SELECT_WAIT,
  aEGH_TALK_SELECT_ROOF,
  aEGH_TALK_GIVE_YOU_WAIT,
  aEGH_TALK_CLEAR_GRASS,

  aEGH_TALK_NUM
};

enum {
  aEGH_THINK_NORMAL_WAIT,
  aEGH_THINK_IRAI,
  aEGH_THINK_IRAI_AF,
  aEGH_THINK_BYE,
  aEGH_THINK_WELCOM,
  aEGH_THINK_BYEBYE,
  aEGH_THINK_SPEAK, // ?

  aEGH_THINK_NUM
};

enum {
  aEGH_THINK_INIT_NONE,
  aEGH_THINK_INIT_NORMAL_WAIT,
  aEGH_THINK_INIT_IRAI,
  aEGH_THINK_INIT_IRAI_AF,
  aEGH_THINK_INIT_BYE,
  aEGH_THINK_INIT_WELCOM,
  aEGH_THINK_INIT_BYEBYE,

  aEGH_THINK_INIT_NUM
};

enum {
  aEGH_THINK_PROC_NONE,
  aEGH_THINK_PROC_IRAI,
  aEGH_THINK_PROC_BYE,
  aEGH_THINK_PROC_BYEBYE,
  aEGH_THINK_PROC_SPEAK_BYEBYE,

  aEGH_THINK_PROC_NUM
};

enum {
  aEGH_TALK_REQUEST_NONE,
  aEGH_TALK_REQUEST_NORM,
  aEGH_TALK_REQUEST_FORCE,

  aEGH_TALK_REQUEST_NUM
};

typedef struct ghost_think_setup_s {
  u8 think_proc;
  u8 think_init_proc;
  u8 talk_request_proc;
  u8 talk_act;
  u8 talk_after_act;
} aEGH_setup_c;

static void aEGH_actor_ct(ACTOR*, GAME*);
static void aEGH_actor_dt(ACTOR*, GAME*);
static void aEGH_actor_move(ACTOR*, GAME*);
static void aEGH_actor_draw(ACTOR*, GAME*);
static void aEGH_actor_init(ACTOR*, GAME*);
static void aEGH_actor_save(ACTOR*, GAME*);

ACTOR_PROFILE Ev_Ghost_Profile = {
  mAc_PROFILE_EV_GHOST,
  ACTOR_PART_NPC,
  ACTOR_STATE_NONE,
  SP_NPC_EV_GHOST,
  ACTOR_OBJ_BANK_KEEP,
  sizeof(EV_GHOST_ACTOR),
  &aEGH_actor_ct,
  &aEGH_actor_dt,
  &aEGH_actor_init,
  mActor_NONE_PROC1,
  &aEGH_actor_save
};

static int aEGH_talk_init(ACTOR*, GAME*);
static int aEGH_talk_end_chk(ACTOR*, GAME*);

static int aEGH_change_talk_proc(EV_GHOST_ACTOR* ghost, u8 talk_act);
static void aEGH_setup_think_proc(EV_GHOST_ACTOR* ghost, GAME_PLAY* play, u8 think_act);
static void aEGH_schedule_proc(NPC_ACTOR* actorx, GAME_PLAY* play, int sched_type);

static int aEGH_bitset_func(u16 bit);
static int aEGH_bitclr_func(u16 bit);
static u16 aEGH_bitcheck_func(u16 bit);

static void aEGH_byebye_check(EV_GHOST_ACTOR* ghost, GAME_PLAY* play);

static void aEGH_actor_ct(ACTOR* actorx, GAME* game) {
  static aNPC_ct_data_c ct_data = {
    &aEGH_actor_move,
    &aEGH_actor_draw,
    5,
    (aNPC_TALK_REQUEST_PROC)&none_proc1,
    &aEGH_talk_init,
    &aEGH_talk_end_chk,
    0
  };

  mEv_gst_c* ghost_save = (mEv_gst_c*)mEv_get_save_area(mEv_EVENT_GHOST, 54);
  EV_GHOST_ACTOR* ghost = (EV_GHOST_ACTOR*)actorx;
  lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);

  if ((*Common_Get(clip).npc_clip->birth_check_proc)(actorx, game) == TRUE) {
    ghost->npc_class.schedule.schedule_proc = &aEGH_schedule_proc;
    (*Common_Get(clip).npc_clip->ct_proc)(actorx, game, &ct_data);
    ghost->npc_class.palActorIgnoreTimer = -1;
    ghost->_9A7 = 0;
    ghost->melody_inst = 0;
    ghost->npc_class.talk_info.melody_inst = 0;

    if (ghost_save == NULL) {
      mEv_reserve_save_area(mEv_EVENT_GHOST, 54);
      ghost_save = (mEv_gst_c*)mEv_get_save_area(mEv_EVENT_GHOST, 54);

      if (ghost_save != NULL) {
        ghost_save->flags = 0;
        ghost_save->okoruhito_str_no = RANDOM_F(32.0f);
        mTM_set_renew_time(&ghost_save->renew_time, rtc_time);
      }
    }
    else {
      if (
        rtc_time->year != ghost_save->renew_time.year ||
        rtc_time->month != ghost_save->renew_time.month ||
        rtc_time->day != ghost_save->renew_time.day
      ) {
        ghost_save->flags = 0;
        ghost_save->okoruhito_str_no = RANDOM_F(32.0f);
        mTM_set_renew_time(&ghost_save->renew_time, rtc_time);
      }

      if ((ghost_save->flags & mEv_GHOST_FLAG_RETURNED_SPIRITS) != 0) {
        Actor_delete(actorx);
      }
    }

    if (Common_Get(player_no) == mPr_FOREIGNER) {
      Actor_delete(actorx);
    }

    ghost->_9AA = 0;
    ghost->npc_class.talk_info.default_animation = 126;
    ghost->_9AC = 0;

    if (aEGH_bitcheck_func(aEGH_BIT_FOUND_GHOST) != FALSE) {
      ghost->alpha = 140;
    }
    else {
      if (mFI_GetItemNumField_BCT(GRASS_A, GRASS_C) < aEGH_MINIMUM_GRASS_COUNT) {
        Actor_delete(actorx);
      }

      ghost->alpha = 0;
    }
  }
}

static void aEGH_actor_save(ACTOR* actorx, GAME* game) {
  mNpc_RenewalSetNpc(actorx);
}

static void aEGH_actor_dt(ACTOR* actorx, GAME* game) {
  mEv_actor_dying_message(mEv_EVENT_GHOST, actorx);
  (*Common_Get(clip).npc_clip->dt_proc)(actorx, game);
}

static void aEGH_actor_init(ACTOR* actorx, GAME* game) {
  (*Common_Get(clip).npc_clip->init_proc)(actorx, game);
}

static int aEGH_set_request_act(EV_GHOST_ACTOR* ghost, u8 priority, u8 idx, u8 type, u16 arg0, u16 arg1, u16 arg2) {
  int res = FALSE;

  if (priority >= ghost->npc_class.request.act_priority) {
    u16 args[6];

    bzero(args, sizeof(args));
    args[0] = arg0;
    args[2] = arg1;
    args[3] = arg2;
    ghost->npc_class.request.act_priority = priority;
    ghost->npc_class.request.act_idx = idx;
    ghost->npc_class.request.act_type = type;
    mem_copy((u8*)ghost->npc_class.request.act_args, (u8*)args, sizeof(args));
    res = TRUE;
  }

  return res;
}

static void aEGH_actor_move(ACTOR* actorx, GAME* game) {
  EV_GHOST_ACTOR* ghost = (EV_GHOST_ACTOR*)actorx;
  GAME_PLAY* play = (GAME_PLAY*)game;
  int step;
  int alpha;
  int target_alpha;
  int delta_alpha;
#ifdef TARGET_PC
  int alpha_ticks = graph_dt_60hz_ticks(game, &ghost->alpha_accum);
#endif

  if (aEGH_bitcheck_func(aEGH_BIT_FOUND_GHOST) != FALSE) {
    actorx->actor_specific = 1;
  }
  else {
    actorx->actor_specific = 0;
  }

  (*Common_Get(clip).npc_clip->move_proc)(actorx, game);
  aEGH_byebye_check(ghost, play);

  if (ghost->npc_class.schedule.type == aNPC_SCHEDULE_TYPE_WALK_WANDER && ghost->think_act != aEGH_THINK_SPEAK) {
    ghost->_9AC = 1;
    (*Common_Get(clip).npc_clip->chg_schedule_proc)((NPC_ACTOR*)ghost, play, aNPC_SCHEDULE_TYPE_SPECIAL);
    actorx->status_data.weight = 255;
  }

  alpha = ghost->alpha;

  if (aEGH_bitcheck_func(aEGH_BIT_FOUND_GHOST) != FALSE) {
#ifdef TARGET_PC
    step = alpha_ticks;
#else
    step = 1;
#endif
    
    if (mDemo_Get_talk_actor() == actorx) {
      ghost->npc_class.draw.anim_speed_type = aNPC_ANIM_SPEED_TYPE_LOCKED;
      ghost->npc_class.draw.frame_speed = 0.5f;
      target_alpha = 190;
    }
    else {
      if (actorx->speed > 0.1f) {
        target_alpha = 80;
      }
      else {
        target_alpha = 140;
      }

      if (alpha <= 140) {
        step = 1;
      }

      ghost->npc_class.draw.anim_speed_type = aNPC_ANIM_SPEED_TYPE_FREE;
      ghost->npc_class.draw.frame_speed = 0.25f;
    }

    delta_alpha = alpha - target_alpha;
    if (ABS(delta_alpha) < step) {
      alpha = target_alpha;
    }
    else {
      if (delta_alpha < 0) {
        alpha += step;
      }
      else {
        alpha -= step;
      }
    }
  }
#ifdef TARGET_PC
  else {
    while (alpha_ticks-- > 0) {
      if (ghost->bye_bye_transparency_delay_timer != 0) {
        ghost->bye_bye_transparency_delay_timer--;
      }
      else {
        alpha -= 4;

        if (alpha < 0) {
          alpha = 0;
        }
      }
    }
  }
#else
  else if (ghost->bye_bye_transparency_delay_timer != 0) {
    ghost->bye_bye_transparency_delay_timer--;
  }
  else {
    alpha -= 4;

    if (alpha < 0) {
      alpha = 0;
    }
  }
#endif

  ghost->alpha = alpha;
  actorx->shape_info.draw_shadow = FALSE;
}

static void aEGH_actor_draw(ACTOR* actorx, GAME* game) {
  EV_GHOST_ACTOR* ghost = (EV_GHOST_ACTOR*)actorx;
  GRAPH* graph = game->graph;
  Gfx* gfx;

  OPEN_DISP(graph);
  gfx = NOW_POLY_XLU_DISP;

  gDPPipeSync(gfx++);
  gDPSetEnvColor(gfx++, 255, 255, 255, ghost->alpha);

  SET_POLY_XLU_DISP(gfx);
  CLOSE_DISP(graph);

  (*Common_Get(clip).npc_clip->draw_proc)(actorx, game);
}

#include "../src/actor/npc/event/ac_ev_ghost_talk.c_inc"
#include "../src/actor/npc/event/ac_ev_ghost_schedule.c_inc"
