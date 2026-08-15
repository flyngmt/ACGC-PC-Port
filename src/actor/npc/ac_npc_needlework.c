#include "ac_npc_needlework.h"

#include "m_needlework.h"
#include "m_needlework_ovl.h"
#include "m_cporiginal_ovl.h"
#include "m_gba_ovl.h"
#include "libultra/libultra.h"
#include "m_common_data.h"
#include "m_msg.h"
#include "m_font.h"
#include "m_eappli.h"
#include "m_player_lib.h"
#include "m_string.h"
#include "m_ledit_ovl.h"
#include "m_bgm.h"
#include "GBA2/gba2.h"

enum {
    aNNW_TALK_WHAT_HAPPEN_FIRST,
    aNNW_TALK_WHAT_HAPPEN,
    aNNW_TALK_OTHER_HAPPEN,
    aNNW_TALK_OTHER_HAPPEN2,
    aNNW_TALK_CHECK_LISTEN,
    aNNW_TALK_LISTEN_SISTER,
    aNNW_TALK_LISTEN_SISTER2,
    aNNW_TALK_LISTEN_SISTER3,
    aNNW_TALK_LISTEN_SISTER4,
    aNNW_TALK_ANE_0,
    aNNW_TALK_ANE_1,
    aNNW_TALK_ANE_2,
    aNNW_TALK_DESIGN_CHECK,
    aNNW_TALK_DESIGN_WHICH,
    aNNW_TALK_DESIGN_OPEN,
    aNNW_TALK_DESIGN_CLOSE,
    aNNW_TALK_DESIGN_CLOSE2,
    aNNW_TALK_DESIGN_CLOSE2_END,
    aNNW_TALK_DESIGN_WHICH2,
    aNNW_TALK_DESIGN_OPEN3,
    aNNW_TALK_DESIGN_CLOSE3,
    aNNW_TALK_TRADE_CHECK,
    aNNW_TALK_TRADE_WHICH,
    aNNW_TALK_TRADE_OPEN,
    aNNW_TALK_TRADE_CLOSE,
    aNNW_TALK_GIVE_ADMISSION,
    aNNW_TALK_TRADE_WHICH2,
    aNNW_TALK_TRADE_OPEN2,
    aNNW_TALK_TRADE_CLOSE2,
    aNNW_TALK_GIVE_ADMISSION2,
    aNNW_TALK_TRADE_WHICH3,
    aNNW_TALK_TRADE_OPEN3,
    aNNW_TALK_TRADE_CLOSE3,
    aNNW_TALK_GBA_WHICH,
    aNNW_TALK_GBA_TOOL_BF,
    aNNW_TALK_GBA_TOOL,
    aNNW_TALK_GBA_TOOL_0,
    aNNW_TALK_GBA_TOOL_AF,
    aNNW_TALK_GBA_TOOL_AF2,
    aNNW_TALK_GBA_TOOL_AF3,
    aNNW_TALK_GBA_LOAD_BF,
    aNNW_TALK_GBA_LOAD,
    aNNW_TALK_GBA_LOAD_CHECK,
    aNNW_TALK_GBA_LOAD_AF,
    aNNW_TALK_TREND_CLOTH,
    aNNW_TALK_BYEBYE,
    aNNW_TALK_EXIT,
    aNNW_TALK_CLOTH_CHANGE,
    aNNW_TALK_CLOTH_WAIT,
    aNNW_TALK_CLOTH_CHANGE2,
    aNNW_TALK_CLOTH_WAIT2,
    aNNW_TALK_CLOTH_CHANGE3,
    aNNW_TALK_CLOTH_WAIT3,
    aNNW_TALK_CLOTH_CHANGE4,
    aNNW_TALK_CLOTH_WAIT4,
    aNNW_TALK_CPORIGINAL0,
    aNNW_TALK_CPORIGINAL1,
    aNNW_TALK_CPORIGINAL2,
    aNNW_TALK_GBA_MENU0,
    aNNW_TALK_GBA_MENU1,
    aNNW_TALK_ANE_3,
    aNNW_TALK_GBA_OVER_SAVE,
    aNNW_TALK_GBA_TOOL_BF_2,
    aNNW_TALK_GBA_TOOL_2,
    aNNW_TALK_GBA_TOOL_AF3_2,
    aNNW_TALK_END_WAIT,
    aNNW_TALK_CARD_E_LOAD_BF_0_0,
    aNNW_TALK_CARD_E_LOAD_BF_0,
    aNNW_TALK_CARD_E_LOAD_BF_1,
    aNNW_TALK_CARD_E_LOAD,
    aNNW_TALK_CARD_E_MENU0,
    aNNW_TALK_CARD_E_MENU1,
    aNNW_TALK_CARD_E_MENU2,
    aNNW_TALK_CARD_E_LOAD_PRG_BF_0,
    aNNW_TALK_CARD_E_LOAD_PRG_BF_1,
    aNNW_TALK_CARD_E_LOAD_PRG_0,
    aNNW_TALK_CARD_E_LOAD_PRG_AF,

    aNNW_TALK_NUM
};

enum {
    aNNW_THINK_PROC_NONE,
    aNNW_THINK_PROC_IKAGADESYOU,
    aNNW_THINK_PROC_OMATIKUDASI,
    aNNW_THINK_PROC_OMATIKUDASI2,
    aNNW_THINK_PROC_MISIN_WAIT,
    aNNW_THINK_PROC_AINOTE,
    aNNW_THINK_PROC_AINOTE3,
    aNNW_THINK_PROC_TURN,

    aNNW_THINK_PROC_NUM
};

enum {
    aNNW_THINK_INIT_NONE,
    aNNW_THINK_INIT_NORMAL_WAIT,
    aNNW_THINK_INIT_MISIN_WAIT,
    aNNW_THINK_INIT_AINOTE,
    aNNW_THINK_INIT_NEXT,
    aNNW_THINK_INIT_TURN,

    aNNW_THINK_INIT_NUM
};

enum {
    aNNW_THINK_NORMAL_WAIT,
    aNNW_THINK_IKAGADESYOU,
    aNNW_THINK_TURN,
    aNNW_THINK_MISIN_WAIT,
    aNNW_THINK_AINOTE3,
    aNNW_THINK_OMATIKUDASI,
    aNNW_THINK_OMATIKUDASI2,
    aNNW_THINK_AINOTE,
    aNNW_THINK_8,
    aNNW_THINK_9,
    aNNW_THINK_10,
    aNNW_THINK_11,
    aNNW_THINK_12,
    aNNW_THINK_13,
    aNNW_THINK_14,

    aNNW_THINK_NUM
};

enum {
    aNNW_TALK_REQUEST_PROC_NONE,
    aNNW_TALK_REQUEST_PROC_NORM,
    aNNW_TALK_REQUEST_PROC_FORCE,

    aNNW_TALK_REQUEST_PROC_NUM
};

enum {
    aNNW_MY_PROC_WAIT,
    aNNW_MY_PROC_PLAYER,
    aNNW_MY_PROC_TURN_P,
    aNNW_MY_PROC_RUN,
    aNNW_MY_PROC_TURN,

    aNNW_MY_PROC_NUM
};

static void aNNW_actor_ct(ACTOR* actorx, GAME* game);
static void aNNW_actor_dt(ACTOR* actorx, GAME* game);
static void aNNW_actor_init(ACTOR* actorx, GAME* game);
static void aNNW_actor_save(ACTOR* actorx, GAME* game);
static void aNNW_actor_move(ACTOR* actorx, GAME* game);
static void aNNW_actor_draw(ACTOR* actorx, GAME* game);
static BOOL aNNW_talk_init(ACTOR* actorx, GAME* game);
static BOOL aNNW_talk_end_chk(ACTOR* actorx, GAME* game);
static void aNNW_schedule_proc(NPC_ACTOR*, GAME_PLAY*, int);
static void aNNW_talk_request(ACTOR* actorx, GAME* game);
static int aNNW_change_talk_proc(NPC_NEEDLEWORK_ACTOR*, u8);
static int aNNW_change_talk_proc_next(NPC_NEEDLEWORK_ACTOR*);
static void aNNW_setup_think_proc(NPC_NEEDLEWORK_ACTOR* actor, GAME_PLAY* play, u8 think_idx);
static void aNNW_my_proc_init(NPC_NEEDLEWORK_ACTOR* actor, GAME_PLAY* play, u8 my_proc_idx);

// clang-format off
ACTOR_PROFILE Npc_Needlework_Profile = {
    mAc_PROFILE_NPC_NEEDLEWORK,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_NEEDLEWORK0,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_NEEDLEWORK_ACTOR),
    aNNW_actor_ct,
    aNNW_actor_dt,
    aNNW_actor_init,
    mActor_NONE_PROC1,
    aNNW_actor_save
};
// clang-format on

static void aNNW_actor_ct(ACTOR* actorx, GAME* game) {
    // clang-format off
    static aNPC_ct_data_c ct_data = {
        aNNW_actor_move,
        aNNW_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        (aNPC_TALK_REQUEST_PROC)none_proc1,
        aNNW_talk_init,
        aNNW_talk_end_chk,
        0
    };
    // clang-format on

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        NPC_NEEDLEWORK_ACTOR* actor = (NPC_NEEDLEWORK_ACTOR*)actorx;

        actor->npc_class.schedule.schedule_proc = aNNW_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
        actor->npc_class.palActorIgnoreTimer = -1;
        actor->_9B3 = 0;
        actor->_9B4 = 0;
        actor->proc_delay_frames = 0;
        actor->delay_frames = 0;
#ifdef TARGET_PC
        actor->proc_delay_accum = 0.0f;
        actor->delay_accum = 0.0f;
#endif
        actor->gba_ready = FALSE;
    }
}

static void aNNW_actor_save(ACTOR* actorx, GAME* game) {
    mNpc_RenewalSetNpc(actorx);
}

static void aNNW_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
}

static void aNNW_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static int aNNW_set_request_act(NPC_NEEDLEWORK_ACTOR* actor, u8 priority, u8 act_idx, u8 act_type, u16 act_obj, s16 move_x, s16 move_z) {
    int ret = FALSE;

    if (priority >= actor->npc_class.request.act_priority) {
        u16 arg_data[aNPC_REQUEST_ARG_NUM];

        bzero(arg_data, sizeof(arg_data));
        arg_data[0] = act_obj;
        arg_data[2] = move_x;
        arg_data[3] = move_z;

        actor->npc_class.request.act_priority = priority;
        actor->npc_class.request.act_idx = act_idx;
        actor->npc_class.request.act_type = act_type;
        mem_copy((u8*)actor->npc_class.request.act_args, (u8*)arg_data, sizeof(arg_data));
        ret = TRUE;
    }

    return ret;
}

static void aNNW_actor_move(ACTOR* actorx, GAME* game) {
    NPC_CLIP->move_proc(actorx, game);
}

static void aNNW_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../src/actor/npc/ac_npc_needlework_gba.c_inc"
#include "../src/actor/npc/ac_npc_needlework_talk.c_inc"
#include "../src/actor/npc/ac_npc_needlework_schedule.c_inc"
