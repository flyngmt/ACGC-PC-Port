#include "ac_arrange_room.h"
#include "m_common_data.h"
#include "m_malloc.h"
#include "m_rcp.h"
#include "sys_matrix.h"

static void aAR_Redma();

extern Gfx rom_myhome2_floor_model[];
extern Gfx rom_myhome2_wall_model[];
extern Gfx rom_myhome2_wall_modelT[];

static void Arrange_Room_Actor_ct(ACTOR* actor, GAME* game);
static void Arrange_Room_Actor_dt(ACTOR* actor, GAME* game);
static void Arrange_Room_Actor_move(ACTOR* actor, GAME* game);
static void Arrange_Room_Actor_draw(ACTOR* actor, GAME* game);


ACTOR_PROFILE Arrange_Room_Profile = {
    mAc_PROFILE_ARRANGE_ROOM,
    ACTOR_PART_FG,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    ETC_ARRANGE_ROOM,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(ARRANGE_ROOM_ACTOR),
    &Arrange_Room_Actor_ct,
    &Arrange_Room_Actor_dt,
    &Arrange_Room_Actor_move,
    &Arrange_Room_Actor_draw,
    NULL,
};

static void* aAR_SecureDmaRam(GAME* game, size_t size) { 
    zelda_malloc_align(size, 0x20); 
}

static void aAR_SetClip(ACTOR* actor, int flag) {
    ARRANGE_ROOM_ACTOR* arrange_room = (ARRANGE_ROOM_ACTOR*)actor;

    if (flag != FALSE) {
        arrange_room->clip.arrange_room_actor_p = arrange_room;
        arrange_room->clip.redma_proc = aAR_Redma;
        common_data.clip.arrange_room_clip = &arrange_room->clip;
    } else {
        common_data.clip.arrange_room_clip = NULL;
    }
}

static void Arrange_Room_Actor_ct(ACTOR* actor, GAME* game) {
    ARRANGE_ROOM_ACTOR* arrange_room = (ARRANGE_ROOM_ACTOR*)actor;
    s16 wall_floor_num;
    s16 wall_num;
    s16 floor_num;
    u8* segment;
    void* data_p;

    mNpc_RenewalNpcRoom(&wall_floor_num);
    actor->actor_specific = wall_floor_num;
    aAR_SetClip(actor, TRUE);
    wall_num = (wall_floor_num >> 8) & 0xFF;
    floor_num = (u8)(wall_floor_num);

    if (floor_num < 0) {
        floor_num = 0;
    } else if (floor_num > 0x42) {
        floor_num = 0x42;
    }

    if (wall_num < 0) {
        wall_num = 0;
    } else if (wall_num > 0x42) {
        wall_num = 0x42;
    }

    arrange_room->vram_segment = NULL;
    arrange_room->wall_data_p = NULL;
    arrange_room->wall_num = wall_num;
    arrange_room->floor_data_p = NULL;
    arrange_room->floor_num = floor_num;

    Common_Set(floor_idx, arrange_room->floor_num);

    data_p = aAR_SecureDmaRam(game, 0x1020);
    arrange_room->wall_data_p = data_p;

    if (data_p != NULL) {
        mRmTp_CopyWallData(arrange_room->wall_data_p, arrange_room->wall_num);
    }

    data_p = aAR_SecureDmaRam(game, 0x2020);
    arrange_room->floor_data_p = data_p;

    if (data_p != NULL) {
        mRmTp_CopyFloorData(arrange_room->floor_data_p, arrange_room->floor_num);
    }
}

static void Arrange_Room_Actor_dt(ACTOR* actor, GAME* game) {
    ARRANGE_ROOM_ACTOR* arrange_room = (ARRANGE_ROOM_ACTOR*)actor;

    aAR_SetClip(actor, FALSE);

    if (arrange_room->wall_data_p != NULL) {
        zelda_free(arrange_room->wall_data_p);
    }

    if (arrange_room->floor_data_p != NULL) {
        zelda_free(arrange_room->floor_data_p);
    }
}

static void aAR_DrawFloor(ACTOR* actor, GAME* game) {
    u8* ptr;
    ARRANGE_ROOM_ACTOR* arrange_room = (ARRANGE_ROOM_ACTOR*)actor;
    GRAPH* graph;

    ptr = arrange_room->floor_data_p;

    _texture_z_light_fog_prim(game->graph);

    graph = game->graph;

    Matrix_translate(0.0f, 0.0f, 0.0f, MTX_LOAD);
    Matrix_scale(0.0625f, 0.0625f, 0.0625f, MTX_MULT);

    OPEN_DISP(graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_C, ptr);
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, ptr + 0x20);
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_9, ptr + 0x820);
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_A, ptr + 0x1020);
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_B, ptr + 0x1820);
    gSPDisplayList(NEXT_POLY_OPA_DISP, rom_myhome2_floor_model);

    CLOSE_DISP(graph);
}

static void aAR_DrawWall(ACTOR* actor, GAME* game) {
    u8* ptr;
    ARRANGE_ROOM_ACTOR* arrange_room = (ARRANGE_ROOM_ACTOR*)actor;
    GRAPH* graph;

    ptr = arrange_room->wall_data_p;

    _texture_z_light_fog_prim(game->graph);

    graph = game->graph;

    Matrix_translate(0.0f, 0.0f, 0.0f, MTX_LOAD);
    Matrix_scale(0.0625f, 0.0625f, 0.0625f, MTX_MULT);

    OPEN_DISP(graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, ptr + 0x20);
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_9, ptr + 0x820);
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_A, ptr);

    gSPDisplayList(NEXT_POLY_OPA_DISP, rom_myhome2_wall_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, rom_myhome2_wall_modelT);

    CLOSE_DISP(graph);
}

static void Arrange_Room_Actor_draw(ACTOR* actor, GAME* game) {
    ARRANGE_ROOM_ACTOR* arrange_room = (ARRANGE_ROOM_ACTOR*)actor;
    GAME_PLAY* play = (GAME_PLAY*)game;

    Global_kankyo_set_room_prim(game);
    aAR_DrawFloor(&arrange_room->actor_class, &play->game);
    aAR_DrawWall(&arrange_room->actor_class, &play->game);
}

static void Arrange_Room_Actor_move(ACTOR* actor, GAME* game) {
    (void)actor; (void)game;
}

static void aAR_Redma() {
    aAR_Clip_c* clip = common_data.clip.arrange_room_clip;
    ARRANGE_ROOM_ACTOR* arrange_room = clip->arrange_room_actor_p;

    if (arrange_room != NULL) {
        mRmTp_CopyWallData(arrange_room->wall_data_p, arrange_room->wall_num);
        mRmTp_CopyFloorData(arrange_room->floor_data_p, arrange_room->floor_num);
    }
}
