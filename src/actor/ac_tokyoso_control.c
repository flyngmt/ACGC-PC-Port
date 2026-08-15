#include "ac_tokyoso_control.h"
#include "m_actor.h"
#include "m_actor_type.h"
#include "m_common_data.h"
#include "m_event.h"
#include "m_field_info.h"
#include "m_name_table.h"
#include "ac_tokyoso_npc1.h"
#include "libultra/libultra.h"

enum {
    aTKC_ACT_WAIT,
    aTKC_ACT_WAIT2,
    aTKC_ACT_STRECH,
    aTKC_ACT_READY,
    aTKC_ACT_SET,
    aTKC_ACT_GO,
    aTKC_ACT_GOAL,
    aTKC_ACT_IREKAE_1,
    aTKC_ACT_IREKAE_2,

    aTKC_ACT_NUM
};

static void aTKC_actor_ct(ACTOR* actorx, GAME* game);
static void aTKC_actor_dt(ACTOR* actorx, GAME* game);
static void aTKC_actor_move(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Tokyoso_Control_Profile = {
    mAc_PROFILE_TOKYOSO_CONTROL,
    ACTOR_PART_CONTROL,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(TOKYOSO_CONTROL_ACTOR),
    aTKC_actor_ct,
    aTKC_actor_dt,
    aTKC_actor_move,
    mActor_NONE_PROC1,
    NULL,
};
// clang-format on

static void aTKC_setupAction(TOKYOSO_CONTROL_ACTOR* actor, int action);

// clip declarations
static void aTKC_clip_next_run(ACTOR* actorx);
static s16 aTKC_clip_get_angle(ACTOR* actorx);
static void aTKC_clip_run_proc(ACTOR* actorx);
static s16 aTKC_clip_run_check(ACTOR* actorx);
static s16 aTKC_clip_top_check(ACTOR* actorx);
static s16 aTKC_clip_goal_check(ACTOR* actorx);
static void aTKC_clip_npc1_think_init(ACTOR* actorx, GAME_PLAY* play, u8 type);
static void aTKC_clip_next_pos(ACTOR* actorx, int idx);
static void aTKC_clip_next_warmup(ACTOR* actorx);
static void aTKC_clip_set_talk_request(ACTOR* actorx);

static void aTKC_actor_ct(ACTOR* actorx, GAME* game) {
    TOKYOSO_CONTROL_ACTOR* actor = (TOKYOSO_CONTROL_ACTOR*)actorx;
    aEv_tokyoso_c* tokyoso = (aEv_tokyoso_c*)mEv_get_save_area(mEv_EVENT_SPORTS_FAIR_FOOT_RACE, 8);

    if (tokyoso == NULL) {
        tokyoso = (aEv_tokyoso_c*)mEv_reserve_save_area(mEv_EVENT_SPORTS_FAIR_FOOT_RACE, 8);
        tokyoso->_00 = 0;
        tokyoso->flags = 0;
    }

    actor->clip.next_run_proc = aTKC_clip_next_run;
    actor->clip.get_angle_proc = aTKC_clip_get_angle;
    actor->clip.run_proc = aTKC_clip_run_proc;
    actor->clip.run_check_proc = aTKC_clip_run_check;
    actor->clip.top_check_proc = aTKC_clip_top_check;
    actor->clip.goal_check_proc = aTKC_clip_goal_check;
    actor->clip.npc1_think_init_proc = aTKC_clip_npc1_think_init;
    actor->clip.next_pos_proc = aTKC_clip_next_pos;
    actor->clip.next_warmup_proc = aTKC_clip_next_warmup;
    actor->clip.set_talk_request_proc = aTKC_clip_set_talk_request;
    CLIP(tokyoso_clip) = &actor->clip;
    aTKC_setupAction(actor, aTKC_ACT_WAIT);
#ifdef TARGET_PC
    actor->logic_accum = 0.0f;
#endif
}

static void aTKC_actor_dt(ACTOR* actorx, GAME* game) {
    CLIP(tokyoso_clip) = NULL;
    mEv_actor_dying_message(mEv_EVENT_SPORTS_FAIR_FOOT_RACE, actorx);
}

static void aTKC_actor_move(ACTOR* actorx, GAME* game) {
    TOKYOSO_CONTROL_ACTOR* actor = (TOKYOSO_CONTROL_ACTOR*)actorx;
    aEv_tokyoso_c* tokyoso = (aEv_tokyoso_c*)mEv_get_save_area(mEv_EVENT_SPORTS_FAIR_FOOT_RACE, 8);

#ifdef TARGET_PC
    int ticks = graph_dt_60hz_ticks(game, &actor->logic_accum);

    while (ticks-- > 0) {
        if (tokyoso->_00 == 3 && actor->action != aTKC_ACT_WAIT2) {
            aTKC_setupAction(actor, aTKC_ACT_WAIT2);
        } else {
            actor->act_proc(actor, (GAME_PLAY*)game);
        }
    }
#else
    if (tokyoso->_00 == 3 && actor->action != aTKC_ACT_WAIT2) {
        aTKC_setupAction(actor, aTKC_ACT_WAIT2);
    } else {
        actor->act_proc(actor, (GAME_PLAY*)game);
    }
#endif
}

static void aTKC_irekae_2(TOKYOSO_CONTROL_ACTOR* actor, GAME_PLAY* play) {
    aEv_tokyoso_c* tokyoso = (aEv_tokyoso_c*)mEv_get_save_area(mEv_EVENT_SPORTS_FAIR_FOOT_RACE, 8);

    if ((tokyoso->flags & aTKC_FLAG_KANSEN_TEAM0) == 0) {
        aTKC_setupAction(actor, aTKC_ACT_STRECH);
        actor->timer = 600;
    }
}

static void aTKC_irekae_1(TOKYOSO_CONTROL_ACTOR* actor, GAME_PLAY* play) {
    aEv_tokyoso_c* tokyoso = (aEv_tokyoso_c*)mEv_get_save_area(mEv_EVENT_SPORTS_FAIR_FOOT_RACE, 8);

    if ((tokyoso->flags & aTKC_FLAG_KANSEN_TEAM1) == 0) {
        aTKC_setupAction(actor, aTKC_ACT_IREKAE_2);
        tokyoso->flags |= aTKC_FLAG_STRETCH_TEAM0;
        tokyoso->flags |= aTKC_FLAG_KANSEN_TEAM0;
    }
}

static void aTKC_goal(TOKYOSO_CONTROL_ACTOR* actor, GAME_PLAY* play) {
    aEv_tokyoso_c* tokyoso = (aEv_tokyoso_c*)mEv_get_save_area(mEv_EVENT_SPORTS_FAIR_FOOT_RACE, 8);

    if ((tokyoso->flags & aTKC_GOAL_MASK) == aTKC_GOAL_ALL) {
        if (actor->timer > 0) {
            actor->timer--;
        } else {
            aTKC_setupAction(actor, aTKC_ACT_IREKAE_1);
            tokyoso->flags |= aTKC_FLAG_STRETCH_TEAM1;
            tokyoso->flags |= aTKC_FLAG_KANSEN_TEAM1;
            tokyoso->flags &= ~aTKC_FLAG_RACE_ACTIVE;
            tokyoso->flags &= ~aTKC_GOAL_MASK;
        }
    }
}

static void aTKC_go(TOKYOSO_CONTROL_ACTOR* actor, GAME_PLAY* play) {
    int i;
    aEv_tokyoso_c* tokyoso = (aEv_tokyoso_c*)mEv_get_save_area(mEv_EVENT_SPORTS_FAIR_FOOT_RACE, 8);

    for (i = 0; i < aTKC_NPC_NUM; i++) {
        if (tokyoso->lap[i] & 1) {
            if (tokyoso->angle[i] < -aTKC_ANGLE_FOR_LAP_COMPLETION) {
                tokyoso->lap[i]++;
            }
        } else {
            if (tokyoso->angle[i] > aTKC_ANGLE_FOR_LAP_COMPLETION) {
                tokyoso->lap[i]++;
            }
        }

        if (tokyoso->lap[i] > aTKC_SUBLAP_NUM && tokyoso->goal[i] == aTKC_GOAL_NONE) {
            if (tokyoso->goal[(i + 1) & 1] == aTKC_GOAL_NONE) {
                tokyoso->goal[i] = aTKC_GOAL_WON;
            } else {
                aTKC_setupAction(actor, aTKC_ACT_GOAL);
                tokyoso->goal[i] = aTKC_GOAL_LOSE;
                actor->timer = 600;
            }
        }
    }
}

static void aTKC_set(TOKYOSO_CONTROL_ACTOR* actor, GAME_PLAY* play) {
    aEv_tokyoso_c* tokyoso = (aEv_tokyoso_c*)mEv_get_save_area(mEv_EVENT_SPORTS_FAIR_FOOT_RACE, 8);

    if ((tokyoso->flags & aTKC_READY_ALL) == 0) {
        aTKC_setupAction(actor, aTKC_ACT_GO); // @BUG - this is called twice
        tokyoso->flags |= aTKC_FLAG_RACE_ACTIVE;
        tokyoso->lap[0] = tokyoso->lap[1] = 0;
        tokyoso->goal[0] = tokyoso->goal[1] = aTKC_GOAL_NONE;
        aTKC_setupAction(actor, aTKC_ACT_GO);
    }
}

static void aTKC_ready(TOKYOSO_CONTROL_ACTOR* actor, GAME_PLAY* play) {
    aEv_tokyoso_c* tokyoso = (aEv_tokyoso_c*)mEv_get_save_area(mEv_EVENT_SPORTS_FAIR_FOOT_RACE, 8);

    if ((tokyoso->flags & aTKC_READY_ALL) == 0) {
        if (actor->timer > 0) {
            actor->timer--;
        } else {
            aTKC_setupAction(actor, aTKC_ACT_SET);
            tokyoso->flags |= aTKC_READY_ALL;
        }
    }
}

static void aTKC_strech(TOKYOSO_CONTROL_ACTOR* actor, GAME_PLAY* play) {
    aEv_tokyoso_c* tokyoso = (aEv_tokyoso_c*)mEv_get_save_area(mEv_EVENT_SPORTS_FAIR_FOOT_RACE, 8);

    if ((tokyoso->flags & aTKC_STRETCH_MASK) == 0) {
        if (actor->timer > 0) {
            actor->timer--;
        } else {
            actor->timer = 120;
            aTKC_setupAction(actor, aTKC_ACT_READY);
            tokyoso->flags |= aTKC_READY_ALL;
        }
    }
}

static void aTKC_wait2(TOKYOSO_CONTROL_ACTOR* actor, GAME_PLAY* play) {
    aEv_tokyoso_c* tokyoso = (aEv_tokyoso_c*)mEv_get_save_area(mEv_EVENT_SPORTS_FAIR_FOOT_RACE, 8);

    if (tokyoso->_00 == 0) {
        tokyoso->_00 = 1;
        aTKC_setupAction(actor, aTKC_ACT_STRECH);
        actor->timer = 600;
    }
}

static void aTKC_wait(TOKYOSO_CONTROL_ACTOR* actor, GAME_PLAY* play) {
    aEv_tokyoso_c* tokyoso = (aEv_tokyoso_c*)mEv_get_save_area(mEv_EVENT_SPORTS_FAIR_FOOT_RACE, 8);

    if (mFI_SetOyasiroPos(tokyoso->yasiro_pos)) {
        tokyoso->_00 = 1;
        aTKC_setupAction(actor, aTKC_ACT_STRECH);
        actor->timer = 600;
    }
}

static void aTKC_setupAction(TOKYOSO_CONTROL_ACTOR* actor, int action) {
    // clang-format off
    static aTKC_PROC process[] = {
        aTKC_wait,
        aTKC_wait2,
        aTKC_strech,
        aTKC_ready,
        aTKC_set,
        aTKC_go,
        aTKC_goal,
        aTKC_irekae_1,
        aTKC_irekae_2,
    };
    // clang-format on

    actor->action = action;
    actor->act_proc = process[action];
}

#include "../src/actor/ac_tokyoso_clip.c_inc"
