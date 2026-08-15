#include "ac_tunahiki_control.h"

#include "m_actor.h"
#include "m_event.h"
#include "m_name_table.h"
#include "m_play.h"

enum {
    aTNC_ACT_WAIT,

    aTNC_ACT_NUM
};

static void aTNC_actor_ct(ACTOR* actorx, GAME* game);
static void aTNC_actor_dt(ACTOR* actorx, GAME* game);
static void aTNC_actor_move(ACTOR* actorx, GAME* game);


// clang-format off
ACTOR_PROFILE Tunahiki_Control_Profile = {
    mAc_PROFILE_TUNAHIKI_CONTROL,
    ACTOR_PART_CONTROL,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(TUNAHIKI_CONTROL_ACTOR),
    aTNC_actor_ct,
    aTNC_actor_dt,
    aTNC_actor_move,
    mActor_NONE_PROC1,
    NULL,
};
// clang-format on

static void aTNC_setupAction(TUNAHIKI_CONTROL_ACTOR* actor, int action);

static void aTNC_actor_ct(ACTOR* actorx, GAME* game) {
    TUNAHIKI_CONTROL_ACTOR* actor = (TUNAHIKI_CONTROL_ACTOR*)actorx;
    aEv_tunahiki_c* tunahiki = (aEv_tunahiki_c*)mEv_get_save_area(mEv_EVENT_SPORTS_FAIR_TUG_OF_WAR, 9);

    aTNC_setupAction(actor, aTNC_ACT_WAIT);
#ifdef TARGET_PC
    actor->logic_accum = 0.0f;
#endif
    if (tunahiki == NULL) {
        tunahiki = (aEv_tunahiki_c*)mEv_reserve_save_area(mEv_EVENT_SPORTS_FAIR_TUG_OF_WAR, 9);
        if (tunahiki != NULL) {
            tunahiki->rope = 0.0f;
            tunahiki->rope_base = 0.0f;
            tunahiki->flag = 0;
            tunahiki->npc_state = aTNC_NPC_STATE0;
            tunahiki->_14 = 0;
        }
    }
}

static void aTNC_actor_dt(ACTOR* actorx, GAME* game) {
    mEv_actor_dying_message(mEv_EVENT_SPORTS_FAIR_TUG_OF_WAR, actorx);
}

static void aTNC_actor_move(ACTOR* actorx, GAME* game) {
    TUNAHIKI_CONTROL_ACTOR* actor = (TUNAHIKI_CONTROL_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

#ifdef TARGET_PC
    int ticks = graph_dt_60hz_ticks(game, &actor->logic_accum);
    u32 saved_game_frame = play->game_frame;
    u32 first_logic_frame = (u32)graph_dt_frame_time(game) - (u32)ticks + 1;
    int tick;

    for (tick = 0; tick < ticks; tick++) {
        play->game_frame = first_logic_frame + (u32)tick;
        actor->act_proc(actor, play);
    }
    play->game_frame = saved_game_frame;
#else
    actor->act_proc(actor, play);
#endif
}

static void aTNC_wait(TUNAHIKI_CONTROL_ACTOR* actor, GAME_PLAY* play) {
    aEv_tunahiki_c* tunahiki = (aEv_tunahiki_c*)mEv_get_save_area(mEv_EVENT_SPORTS_FAIR_TUG_OF_WAR, 9);
    f32 shake = 0.0f;

    if (tunahiki->flag & aTNC_FLAG_SHAKE) {
        if (play->game_frame & 1) {
            shake = 0.3f;
        } else {
            shake = -0.3f;
        }

        if ((tunahiki->flag & aTNC_FLAG_NPC_TALK_ALL) == 0) {
            tunahiki->rope_base += tunahiki->speed * 0.025f;
            if (tunahiki->rope_base < -10.0f) {
                tunahiki->rope_base = -10.0f;
                tunahiki->speed = 0.0f;
            } else if (tunahiki->rope_base > 10.0f) {
                tunahiki->rope_base = 10.0f;
                tunahiki->speed = 0.0f;
            }
        }
    }

    {
        f32 rope = tunahiki->rope_base + shake;
        aEv_tunahiki_c* _tunahiki = (aEv_tunahiki_c*)mEv_get_save_area(mEv_EVENT_SPORTS_FAIR_TUG_OF_WAR, 9);

        _tunahiki->rope = rope;
    }

    tunahiki->counter++;
    if (tunahiki->counter >= 65) {
        tunahiki->counter = 2;
    }
}

static void aTNC_setupAction(TUNAHIKI_CONTROL_ACTOR* actor, int action) {
    static aTNC_PROC process[] = { aTNC_wait };

    actor->action = action;
    actor->act_proc = process[action];
}
