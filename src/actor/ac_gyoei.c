#include "ac_gyoei.h"

#include "m_common_data.h"
#include "m_actor_shadow.h"
#include "libultra/libultra.h"
#include "m_malloc.h"
#include "sys_matrix.h"
#include "m_skin_matrix.h"
#include "m_rcp.h"
#include "m_player_lib.h"

static void aGYO_actor_ct(ACTOR* actorx, GAME* game);
static void aGYO_actor_dt(ACTOR* actorx, GAME* game);
static void aGYO_actor_move(ACTOR* actorx, GAME* game);
static void aGYO_actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Gyoei_Profile = {
    mAc_PROFILE_GYOEI,
    ACTOR_PART_CONTROL,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(GYOEI_ACTOR),
    &aGYO_actor_ct,
    &aGYO_actor_dt,
    &aGYO_actor_move,
    &aGYO_actor_draw,
    NULL,
};
// clang-format on

static int aGYO_init_dma_and_clip_area(void);
static void aGYO_free_clip_area(void);

static ACTOR* aGYO_ctrlActor = NULL;

typedef struct gyoei_overlay_s {
    ATTRIBUTE_ALIGN(8) u8 buf[0x3C00];
} aGYO_overlay_c;

static aGYO_overlay_c aGYO_overlay[aGYO_MAX_GYOEI];

static void aGYO_actor_ct(ACTOR* actorx, GAME* game) {
    GYOEI_ACTOR* gyoei = (GYOEI_ACTOR*)actorx;
    int i;
    aGYO_CTRL_ACTOR* ctrl = gyoei->ctrl;

    for (i = 0; i < aGYO_MAX_GYOEI; i++) {
        ctrl->exist = FALSE;
        ctrl->overlay_p = aGYO_overlay[i].buf;
        ctrl++;
    }

    for (i = 0; i < aGYO_EXIST_MAX; i++) {
        gyoei->exist[i] = FALSE;
        gyoei->segment_type[i] = -1;
    }

    gyoei->logic_accum = 0.0f;

    aGYO_ctrlActor = (ACTOR*)gyoei;
    aGYO_init_dma_and_clip_area();
}

static void aGYO_actor_dt(ACTOR* actorx, GAME* game) {
    GYOEI_ACTOR* gyoei = (GYOEI_ACTOR*)actorx;
    int i;
    aGYO_CTRL_ACTOR* ctrl = gyoei->ctrl;

    for (i = 0; i < aGYO_MAX_GYOEI; i++) {
        if (ctrl->overlay_p != NULL) {
            ctrl->overlay_p = NULL;
        }

        ctrl++;
    }

    aGYO_free_clip_area();
}

#include "../src/actor/ac_gyoei_model.c_inc"

static mActor_proc aGYO_program_dlftbl[] = {
    &aGTT_actor_init,
    &aGKK_actor_init,
};

#include "../src/actor/ac_gyoei_clip.c_inc"
#include "../src/actor/ac_gyoei_move.c_inc"
#include "../src/actor/ac_gyoei_data.c_inc"
#include "../src/actor/ac_gyoei_draw.c_inc"
