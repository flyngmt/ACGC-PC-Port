#include "ac_npc_totakeke.h"

#include "m_event.h"
#include "m_common_data.h"
#include "m_npc.h"
#include "m_msg.h"
#include "m_choice.h"
#include "m_bgm.h"
#include "m_player_lib.h"
#include "m_string_data.h"
#include "m_ledit_ovl.h"

#ifdef TARGET_PC
static void aNTT_schedule_proc(NPC_TOTAKEKE_ACTOR* totakeke, GAME_PLAY* play, int schedule_id);
static int aNTT_change_talk_proc(NPC_TOTAKEKE_ACTOR*, int);
static void aNTT_setup_think_proc(NPC_TOTAKEKE_ACTOR*, GAME_PLAY*, u8);
static int aNTT_enso_init(NPC_TOTAKEKE_ACTOR*);
#else
void aNTT_schedule_proc(NPC_TOTAKEKE_ACTOR* totakeke, GAME_PLAY* play, int schedule_id);
int aNTT_change_talk_proc(NPC_TOTAKEKE_ACTOR*, int);
void aNTT_setup_think_proc(NPC_TOTAKEKE_ACTOR*, GAME_PLAY*, u8);
int aNTT_enso_init(NPC_TOTAKEKE_ACTOR*);
#endif
#ifdef TARGET_PC
static void aNTT_actor_ct(ACTOR* actorx, GAME* game);
static void aNTT_actor_dt(ACTOR* actorx, GAME* game);
static void aNTT_actor_init(ACTOR* actorx, GAME* game);
static void aNTT_actor_save(ACTOR* actorx, GAME* game);
static void aNTT_actor_move(ACTOR* actorx, GAME* game);
static void aNTT_actor_draw(ACTOR* actorx, GAME* game);
static int aNTT_talk_init(ACTOR* actorx, GAME* game);
static int aNTT_talk_end_chk(ACTOR* actorx, GAME* game);
#else
void aNTT_actor_ct(ACTOR* actorx, GAME* game);
void aNTT_actor_dt(ACTOR* actorx, GAME* game);
void aNTT_actor_init(ACTOR* actorx, GAME* game);
void aNTT_actor_save(ACTOR* actorx, GAME* game);
void aNTT_actor_move(ACTOR* actorx, GAME* game);
void aNTT_actor_draw(ACTOR* actorx, GAME* game);
int aNTT_talk_init(ACTOR* actorx, GAME* game);
int aNTT_talk_end_chk(ACTOR* actorx, GAME* game);
#endif

// clang-format off
ACTOR_PROFILE Npc_Totakeke_Profile = {
    mAc_PROFILE_NPC_TOTAKEKE,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_TOTAKEKE,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_TOTAKEKE_ACTOR),
    &aNTT_actor_ct,
    &aNTT_actor_dt,
    &aNTT_actor_init,
    (mActor_proc)none_proc1,
    &aNTT_actor_save,
};

static void aNTT_actor_ct(ACTOR *actorx, GAME *game) {
    static aNPC_ct_data_c ct_data = {
        &aNTT_actor_move,
        &aNTT_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        (mActor_proc)none_proc1,
        &aNTT_talk_init,
        &aNTT_talk_end_chk,
        0x0
    };
    aNTT_event_save_c *save = (aNTT_event_save_c *)mEv_get_save_area(mEv_EVENT_KK_SLIDER, 0xa);
    aNTT_event_common_c *common = (aNTT_event_common_c *)mEv_get_common_area(mEv_EVENT_KK_SLIDER, 0x10);

    if (Common_Get(reset_flag) == TRUE) {
        Actor_delete(actorx);
        actorx->sv_proc = NULL;
        actorx->dt_proc = NULL;
        mNpc_RenewalSetNpc(actorx);
        mEv_actor_dying_message(mEv_EVENT_KK_SLIDER, actorx);
    } else if (CLIP(npc_clip)->birth_check_proc(actorx, game) == TRUE) {
        xyz_t wpos;
        NPC_TOTAKEKE_ACTOR *totakeke = (NPC_TOTAKEKE_ACTOR *)actorx;

        totakeke->npc_class.schedule.schedule_proc = (aNPC_SCHEDULE_PROC)aNTT_schedule_proc;
#ifdef TARGET_PC
        /* Staff-roll state is authored in integer 60 Hz ticks. */
        totakeke->staffroll_logic_accum = 0.0f;
#endif
        CLIP(npc_clip)->ct_proc(actorx, game, &ct_data);
        totakeke->npc_class.palActorIgnoreTimer = -1;
        totakeke->npc_class.condition_info.hide_flg = FALSE;
        totakeke->npc_class.collision.check_kind = aNPC_BG_CHECK_TYPE_NONE;
        actorx->world.position.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(actorx->world.position, 0.0f);
        actorx->position_speed.y = 0.0f;
        actorx->gravity = 0.0f;
        actorx->max_velocity_y = 0.0f;
        totakeke->npc_class.talk_info.default_animation = aNPC_ANIM_WAIT_E1;
        totakeke->npc_class.talk_info.default_act = aNPC_ACT_TALK2;
        totakeke->npc_class.talk_info.turn = aNPC_TALK_TURN_NONE;

        aNTT_enso_init(totakeke);
        totakeke->_9a1 = FALSE;

        if (save == NULL) {
            save = (aNTT_event_save_c *)mEv_reserve_save_area(mEv_EVENT_KK_SLIDER, 0xa);
            save->bitfield = 0;
        }

        save->bitfield &= ~(aNTT_FLAG_SP_ROLL_END | aNTT_FLAG_SP_ROLL_DRAW);

        {
            int i;
            for (i = 0; i < aNTT_REQUEST_STR_LEN; i++) {
                save->request_str[i] = 0;
            }
        }

        save->roll_flag = FALSE;
        save->copyright_alpha = 0;

        if (common == NULL) {
            common = (aNTT_event_common_c *)mEv_reserve_common_area(mEv_EVENT_KK_SLIDER, 0x10);
            common->foreigner_bitfield = 0;
        }
        totakeke->npc_class.collision.pipe.attribute.pipe.radius = 30;
        totakeke->melody_inst = 0;
        totakeke->majin_flag = 0;
        totakeke->_99f = 0xff;
        mCoBG_SetPlussOffset(actorx->world.position, 3, mCoBG_ATTRIBUTE_NONE);
    }
}

static void aNTT_actor_save(ACTOR *actorx, GAME *game) {
    mNpc_RenewalSetNpc(actorx);
}

static void aNTT_actor_dt(ACTOR *actorx, GAME *game) {
    mEv_actor_dying_message(mEv_EVENT_KK_SLIDER, actorx);
    CLIP(npc_clip)->dt_proc(actorx, game);
    mCoBG_SetPlussOffset(actorx->world.position, 0x0, 0x64);
}

static void aNTT_actor_init(ACTOR *actorx, GAME *game) {
    CLIP(npc_clip)->init_proc(actorx, game);
}

static void aNTT_actor_move(ACTOR *actorx, GAME *game) {
    NPC_TOTAKEKE_ACTOR *totakeke = (NPC_TOTAKEKE_ACTOR *)actorx;

    CLIP(npc_clip)->move_proc(actorx, game);
    if (totakeke->npc_class.draw.animation_id == aNPC_ANIM_ENSOU_E1) {
        totakeke->npc_class.draw.main_animation.keyframe.frame_control.mode = 1;
    }
}

static void aNTT_actor_draw(ACTOR *actorx, GAME *game) {
    NPC_TOTAKEKE_ACTOR *totakeke = (NPC_TOTAKEKE_ACTOR *)actorx;
    aNTT_event_save_c *save = (aNTT_event_save_c *)mEv_get_save_area(mEv_EVENT_KK_SLIDER, 0xa);
    GAME_PLAY* play = (GAME_PLAY*)game;
    
    CLIP(npc_clip)->draw_proc(actorx, game);
    if (save == NULL || (save->bitfield & 0x4000) == 0 || CLIP(mikanbox_clip) == NULL) {
        return;
    }
    CLIP(mikanbox_clip)->roll_draw_proc(play, totakeke->roll2_count, totakeke->_9a2);
}

#include "../src/actor/npc/ac_npc_totakeke_talk.c_inc"
#include "../src/actor/npc/ac_npc_totakeke_think.c_inc"
