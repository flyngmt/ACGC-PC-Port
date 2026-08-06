#include "ac_mural.h"

#include "m_debug.h"
#include "m_name_table.h"
#include "m_player_lib.h"
#include "sys_matrix.h"

static void Mural_Actor_ct(ACTOR* actorx, GAME* game);
static void Mural_Actor_dt(ACTOR* actorx, GAME* game);
static void Mural_Actor_move(ACTOR* actorx, GAME* game);
static void Mural_Actor_draw(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Mural_Profile = {
    mAc_PROFILE_MURAL,
    ACTOR_PART_BG,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_MURAL,
    sizeof(MURAL_ACTOR),
    &Mural_Actor_ct,
    &Mural_Actor_dt,
    &Mural_Actor_move,
    &Mural_Actor_draw,
    NULL,
};

ATTRIBUTE_ALIGN(32) static u8 tex[aML_MURAL_NUM][(32 * 32) / 2];
ATTRIBUTE_ALIGN(32) static u16 pal[aML_MURAL_NUM][16];

static void Mural_Actor_ct(ACTOR* actorx, GAME* game) {
    MURAL_ACTOR* mural = (MURAL_ACTOR*)actorx;
    int i;

    for (i = 0; i < aML_MURAL_NUM; i++) {
        mural->mural[i].tex_p = tex[i];
        mural->mural[i].pal_p = pal[i];
        mPlib_Load_PlayerTexAndPallet(mural->mural[i].tex_p, mural->mural[i].pal_p, i);
        mural->mural[i].type = 0;
    }
}

static void Mural_Actor_dt(ACTOR* actorx, GAME* game) {
    // nothing
}

static void Mural_Actor_move(ACTOR* actorx, GAME* game) {
    MURAL_ACTOR* mural = (MURAL_ACTOR*)actorx;

    if (REGADDR(TAKREG, 10) == 0 || REGADDR(TAKREG, 10) == 1) {
        if (REGADDR(TAKREG, 12) >= 0 && REGADDR(TAKREG, 12) < 255) {
            if (REGADDR(TAKREG, 11) >= 0 && REGADDR(TAKREG, 11) < aML_MURAL_NUM) {
                mural->mural[REGADDR(TAKREG, 11)].type = REGADDR(TAKREG, 10);
                mPlib_Load_PlayerTexAndPallet(mural->mural[REGADDR(TAKREG, 11)].tex_p,
                                              mural->mural[REGADDR(TAKREG, 11)].pal_p, REGADDR(TAKREG, 12));
            }
        }
    }

    actorx->world.position.y = 140.0f;
}

extern Gfx obj_mural_model[];

static void Mural_Actor_draw(ACTOR* actorx, GAME* game) {
    MURAL_ACTOR* mural = (MURAL_ACTOR*)actorx;
    int y;
    int x;
    int i;

    i = 0;
    for (y = 0; y < aML_MURAL_Y_NUM; y++) {
        for (x = 0; x < aML_MURAL_X_NUM; x++, i++) {
            OPEN_DISP(game->graph);

            Matrix_translate(actorx->world.position.x + x * 24.0f, actorx->world.position.y - y * 24.0f,
                             actorx->world.position.z, MTX_LOAD);
            Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);

            /* Segment 8 holds the palette */
            gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, mural->mural[i].pal_p);

            /* Segment 9 holds the texture */
            gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_9, mural->mural[i].tex_p);

            gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(NEXT_POLY_OPA_DISP, obj_mural_model);

            CLOSE_DISP(game->graph);
        }
    }
}
