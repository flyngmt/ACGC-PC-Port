#include "ac_npc_hem.h"
#include "m_name_table.h"
#include "ac_npc.h"
#include "ac_npc_h.h"
#include "m_common_data.h"
#include "m_msg.h"
#include "m_soncho.h"
#include "ac_shrine.h"

enum {
    aNHM_ACT_APPEAR_WAIT,
    aNHM_ACT_DISAPPEAR_WAIT,

    aNHM_ACT_NUM
};

enum {
    aNHM_TALK_TRANS_DEMO_START_WAIT,
    aNHM_TALK_TRANS_DEMO_END_WAIT,
    aNHM_TALK_END_WAIT,

    aNHM_TALK_TRANS_NUM
};

typedef struct npc_hem_actor_s NPC_HEM_ACTOR;

typedef void (*aNHM_PROC)(NPC_HEM_ACTOR* actor, GAME_PLAY* play);

typedef struct npc_hem_actor_s {
    NPC_ACTOR actor;
    int action;
    aNHM_PROC act_proc;
    aNHM_PROC talk_proc;
    u8 disappear_flag;
    u8 trans_flag;
    s16 talk_timer;
#ifdef TARGET_PC
    f32 talk_timer_accum;
#endif
} NPC_HEM_ACTOR;

static void aNHM_actor_ct(ACTOR* actorx, GAME* game);
static void aNHM_actor_dt(ACTOR* actorx, GAME* game);
static void aNHM_actor_init(ACTOR* actorx, GAME* game);
static void aNHM_actor_save(ACTOR* actorx, GAME* game);
static void aNHM_actor_move(ACTOR* actorx, GAME* game);
static void aNHM_actor_draw(ACTOR* actorx, GAME* game);
static BOOL aNHM_talk_init(ACTOR* actorx, GAME* game);
static BOOL aNHM_talk_end_chk(ACTOR* actorx, GAME* game);
static void aNHM_schedule_proc(NPC_ACTOR*, GAME_PLAY*, int);
static void aNHM_talk_request(ACTOR* actorx, GAME* game);
static void aNHM_change_talk_proc(NPC_HEM_ACTOR*, int);

// clang-format off
ACTOR_PROFILE Npc_Hem_Profile = {
    mAc_PROFILE_NPC_HEM,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_HEM,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_HEM_ACTOR),
    aNHM_actor_ct,
    aNHM_actor_dt,
    aNHM_actor_init,
    mActor_NONE_PROC1,
    aNHM_actor_save
};
// clang-format on

static void aNHM_actor_ct(ACTOR* actorx, GAME* game) {
    // clang-format off
    static aNPC_ct_data_c ct_data = {
        aNHM_actor_move,
        aNHM_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        (aNPC_TALK_REQUEST_PROC)none_proc1,
        aNHM_talk_init,
        aNHM_talk_end_chk,
        0
    };
    // clang-format on

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        NPC_HEM_ACTOR* actor = (NPC_HEM_ACTOR*)actorx;

        actor->actor.schedule.schedule_proc = aNHM_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
    }
}

static void aNHM_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aNHM_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
}

static void aNHM_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aNHM_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../../actor/npc/ac_npc_hem.c_inc"
