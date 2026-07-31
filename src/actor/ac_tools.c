#include "ac_tools.h"

#include "m_common_data.h"
#include "libultra/libultra.h"
#include "m_scene.h"
#include "m_name_table.h"

static void aTOL_actor_ct(ACTOR* actor, GAME* play);
static void aTOL_actor_dt(ACTOR*, GAME*);
static void aTOL_init_clip_area(GAME* play);
static void aTOL_free_clip_area();

ACTOR_PROFILE Tools_Profile = {
    mAc_PROFILE_TOOLS,
    ACTOR_PART_CONTROL,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(ACTOR),
    aTOL_actor_ct,
    aTOL_actor_dt,
    NONE_ACTOR_PROC,
    NONE_ACTOR_PROC,
    NULL,
};

aTOL_Clip_c aTOL_clip;

static void aTOL_actor_ct(ACTOR* actor, GAME* game) {
    aTOL_init_clip_area(game);
}

static void aTOL_actor_dt(ACTOR* actor, GAME* game) {
    aTOL_free_clip_area();
}

static void aTOL_check_data_bank(int id, ACTOR* actor) {
    ACTOR* kill;
    aTOL_Clip_c* clip;

    if ((actor->part == ACTOR_PART_PLAYER) && (id <= 0x1F)) {

        clip = Common_Get(clip.tools_clip);

        if (clip->bank_id != -1) {

            kill = actor->child_actor;

            if ((kill != NULL) && (kill->data_bank_id == clip->bank_id)) {
                Actor_delete(kill);
            }
        }
    }
}

static ACTOR* aTOL_birth_proc(int kind, int mode, ACTOR* parent_actor, GAME* game, s16 arg, int* bank_id) {
    static s16 profile_table[] = {
        mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA,
        mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA,
        mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA,
        mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA,
        mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA,
        mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA,
        mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA,
        mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA,
        mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA,
        mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA, mAc_PROFILE_T_UMBRELLA,
        mAc_PROFILE_T_KEITAI,   mAc_PROFILE_T_UTIWA,    mAc_PROFILE_T_HANABI,   mAc_PROFILE_T_CRACKER,
        mAc_PROFILE_T_PISTOL,   mAc_PROFILE_T_FLAG,     mAc_PROFILE_T_TUMBLER,  mAc_PROFILE_T_NPCSAO,
        mAc_PROFILE_T_TAMA,     mAc_PROFILE_T_TAMA,     mAc_PROFILE_T_TAMA,     mAc_PROFILE_T_TAMA,
        mAc_PROFILE_T_ANRIUM1,  mAc_PROFILE_T_BAG1,     mAc_PROFILE_T_BAG2,     mAc_PROFILE_T_BISCUS1,
        mAc_PROFILE_T_BISCUS2,  mAc_PROFILE_T_BISCUS3,  mAc_PROFILE_T_BISCUS4,  mAc_PROFILE_T_HASU1,
        mAc_PROFILE_T_HAT1,     mAc_PROFILE_T_HAT2,     mAc_PROFILE_T_HAT3,     mAc_PROFILE_T_REI1,
        mAc_PROFILE_T_REI2,     mAc_PROFILE_T_ZINNIA1,  mAc_PROFILE_T_ZINNIA2,  mAc_PROFILE_T_COBRA1,
    };

    ACTOR* child;
    GAME_PLAY* play = (GAME_PLAY*)game;

    aTOL_check_data_bank(kind, parent_actor);
    child = Actor_info_make_child_actor(&play->actor_info, parent_actor, game, profile_table[kind], 0.0f, 0.0f,
                                                      0.0f, 0, 0, 0, -1, 0, arg, -1);

    if (child != NULL) {
        TOOLS_ACTOR* tool = (TOOLS_ACTOR*)child;

        tool->work0 = mode;
        tool->tool_name = kind;
    }

    if (bank_id != NULL) {
        *bank_id = -1;
    }

    return child;
}

static int aTOL_chg_request_mode_proc(ACTOR* actor, ACTOR* tool, int mode) {
    TOOLS_ACTOR* t_actor = (TOOLS_ACTOR*)tool;

    if (actor != tool->parent_actor) {
        return FALSE;
    }

    t_actor->work0 = mode;
    return TRUE;
}

static void aTOL_secure_pl_umbrella_bank_area(GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    Object_Exchange_c* exchange;
    int id;

    exchange = &play->object_exchange;
    id = exchange->bank_idx;

    if (mSc_secure_exchange_keep_bank(exchange, 0, 0xC00) != NULL) {
        Common_Set(clip.tools_clip->bank_id, id);
    } else {
        Common_Set(clip.tools_clip->bank_id, -1);
    }
}

static void aTOL_init_clip_area(GAME* game) {
    if (Common_Get(clip.tools_clip) == NULL) {
        Common_Set(clip.tools_clip, &aTOL_clip);
        bzero(&aTOL_clip, sizeof(aTOL_Clip_c));
        Common_Set(clip.tools_clip->aTOL_birth_proc, aTOL_birth_proc);
        Common_Set(clip.tools_clip->aTOL_chg_request_mode_proc, aTOL_chg_request_mode_proc);
        aTOL_secure_pl_umbrella_bank_area(game);
    }
}

static void aTOL_free_clip_area() {
    if (Common_Get(clip.tools_clip) != NULL) {
        Common_Set(clip.tools_clip, NULL);
    }
}
