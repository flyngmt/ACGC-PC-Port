#include "ac_structure.h"

#include "m_play.h"
#include "m_name_table.h"
#include "m_malloc.h"
#include "m_common_data.h"

static void aSTR_actor_ct(ACTOR* actor, GAME* game);
static void aSTR_actor_dt(ACTOR* actor, GAME* game);
static void aSTR_actor_move(ACTOR* actor, GAME* game);

ACTOR_PROFILE Structure_Profile = { mAc_PROFILE_STRUCTURE,
                                    ACTOR_PART_CONTROL,
                                    ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
                                    EMPTY_NO,
                                    ACTOR_OBJ_BANK_KEEP,
                                    sizeof(STRUCTURE_CONTROL_ACTOR),

                                    &aSTR_actor_ct,
                                    &aSTR_actor_dt,
                                    &aSTR_actor_move,
                                    NONE_ACTOR_PROC,
                                    NULL };

static u8 aSTR_overlay[aSTR_ACTOR_TBL_COUNT][aSTR_OVERLAY_SIZE];
#ifdef TARGET_PC
/* Native pointer/alignment growth makes some derived structure actors larger
 * than STRUCTURE_ACTOR. Keep a fixed stride so one actor cannot clear the next. */

typedef union {
    u64 align;
    STRUCTURE_ACTOR actor;
    u8 bytes[aSTR_ACTOR_CLASS_SLOT_SIZE];
} aSTR_pc_actor_storage_c;

typedef char aSTR_pc_actor_slot_backing_too_small
    [(aSTR_ACTOR_CLASS_SLOT_SIZE >= sizeof(STRUCTURE_ACTOR)) ? 1 : -1];

static aSTR_pc_actor_storage_c aSTR_actor_cl[aSTR_ACTOR_TBL_COUNT];

static STRUCTURE_ACTOR* aSTR_pc_actor_slot(int idx) {
    return &aSTR_actor_cl[idx].actor;
}
#else
static STRUCTURE_ACTOR aSTR_actor_cl[aSTR_ACTOR_TBL_COUNT];
#define aSTR_pc_actor_slot(idx) (&aSTR_actor_cl[idx])
#endif

#include "../src/actor/ac_structure_clip.c_inc"

static void aSTR_actor_ct(ACTOR* actor, GAME* game) {
    STRUCTURE_CONTROL_ACTOR* structure = (STRUCTURE_CONTROL_ACTOR*)actor;

    aSTR_init_clip_area();
    structure->str_door_name = Common_Get(door_data).door_actor_name;
    structure->reset = Common_Get(door_data).exit_type;
}

static void aSTR_actor_dt(ACTOR* actor, GAME* game) {
    aSTR_free_clip_area();
}

static void aSTR_check_door_data(STRUCTURE_CONTROL_ACTOR* actor, GAME* game) {
    static int request[2] = { 4, 5 };

    GAME_PLAY* play = (GAME_PLAY*)game;

    if (ITEM_NAME_GET_TYPE(actor->str_door_name) == NAME_TYPE_STRUCT) {
        STRUCTURE_ACTOR* str_actor =
            (STRUCTURE_ACTOR*)Actor_info_fgName_search(&play->actor_info, actor->str_door_name, ACTOR_PART_ITEM);

        if (str_actor != NULL && str_actor->request_type == 0) {
            str_actor->request_type = request[actor->reset == TRUE];
            actor->str_door_name = EMPTY_NO;
        }
    } else {
        actor->str_door_name = EMPTY_NO;
    }
}

static void aSTR_actor_move(ACTOR* actor, GAME* game) {
    STRUCTURE_CONTROL_ACTOR* structure = (STRUCTURE_CONTROL_ACTOR*)actor;
    switch (mFI_GetFieldId()) {
        case mFI_FIELD_FG:
            aSTR_check_door_data(structure, game);
            break;
    }
}
