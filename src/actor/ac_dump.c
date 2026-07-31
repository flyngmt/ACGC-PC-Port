#include "ac_dump.h"

#include "m_name_table.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "m_player_lib.h"
#include "m_common_data.h"

extern Gfx dump_s_DL_model[];
extern Gfx dump_w_DL_model[];

extern Vtx obj_dump_shadow_v[];
extern Gfx obj_dump_shadowT_model[];

static void aDUM_actor_ct(ACTOR* actor, GAME* game);
static void aDUM_actor_dt(ACTOR* actor, GAME* game);
static void aDUM_actor_init(ACTOR* actor, GAME* game);
static void aDUM_actor_draw(ACTOR* actor, GAME* game);

ACTOR_PROFILE Dump_Profile = {
    mAc_PROFILE_DUMP,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET | ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    DUMP,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(DUMP_ACTOR),
    aDUM_actor_ct,
    aDUM_actor_dt,
    aDUM_actor_init,
    aDUM_actor_draw,
    NULL,
};

u8 aDUM_shadow_vtx_fix_flg_table[] = {
    1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1,
    1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1,
};

bIT_ShadowData_c aDUM_shadow_data = {
    48, aDUM_shadow_vtx_fix_flg_table, 60.0f, obj_dump_shadow_v, obj_dump_shadowT_model,
};

static void aDUM_set_bgOffset(DUMP_ACTOR*, int);
static void aDUM_setup_action(DUMP_ACTOR*, int);

static void aDUM_actor_ct(ACTOR* actor, GAME* game) {
    DUMP_ACTOR* dump = (DUMP_ACTOR*)actor;

    dump->season = Common_Get(time.season);
    aDUM_set_bgOffset(dump, 1);
    aDUM_setup_action(dump, 0);
    actor->world.position.x -= 40.0f;
}

static void aDUM_actor_dt(ACTOR* actor, GAME* game) {

    actor->world.position.x += 40.0f;
}

static void aDUM_set_bgOffset_sub(DUMP_ACTOR* dump, int x, int z, s16 mode) {
    static int flag_tbl[6][6] = {
        1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
    };
    xyz_t pos;

    pos.x = dump->actor_class.home.position.x - (x * 40);
    pos.y = dump->actor_class.home.position.y;
    pos.z = dump->actor_class.home.position.z - (z * 40);

    if (flag_tbl[z][x] != 0) {
        mCoBG_SetPlussOffset(pos, mode, 100);
    }
}

static void aDUM_set_bgOffset(DUMP_ACTOR* dump, int s) {
    s16 mode = s ? 4 : 4;
    int i;
    for (i = 0; i < 6; i++) {
        aDUM_set_bgOffset_sub(dump, 0, i, mode);
        aDUM_set_bgOffset_sub(dump, 1, i, mode);
        aDUM_set_bgOffset_sub(dump, 2, i, mode);
        aDUM_set_bgOffset_sub(dump, 3, i, mode);
        aDUM_set_bgOffset_sub(dump, 4, i, mode);
        aDUM_set_bgOffset_sub(dump, 5, i, mode);
    }
}

static void aDUM_set_talk_info(ACTOR* actor) {
    rgba_t color;

    mDemo_Set_msg_num(MSG_4970);
    mDemo_Set_talk_display_name(0);
    mDemo_Set_camera(1);
    mPlib_Set_able_hand_all_item_in_demo(1);
    mDemo_Set_ListenAble();

    color.r = 185;
    color.g = 60;
    color.b = 40;
    color.a = 255;
    mDemo_Set_talk_window_color(&color);
}

static void aDUM_wait(DUMP_ACTOR* dump, GAME_PLAY* play) {
    ACTOR* actor = &dump->actor_class;

    PLAYER_ACTOR* player = get_player_actor_withoutCheck(play);
    xyz_t pos;

    xyz_t_move(&pos, &actor->world.position);

    if ((mDemo_Check(mDemo_TYPE_TALK, actor) != TRUE) && (player != NULL) && (mDemo_Get_talk_actor() == NULL)) {

        if (player->actor_class.world.position.z >= pos.z) {

            if (ABS(actor->player_angle_y) < DEG2SHORT_ANGLE2(45.0f)) {
                mDemo_Request(mDemo_TYPE_TALK, actor, aDUM_set_talk_info);
            }
        }
    }
}

static void aDUM_setup_action(DUMP_ACTOR* dump, int action) {
    static DUMP_PROC process[] = { aDUM_wait };

    dump->proc = process[action];
    dump->current_action = action;
}

static void aDUM_actor_move(ACTOR* actor, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    DUMP_ACTOR* dump = (DUMP_ACTOR*)actor;

    dump->proc(dump, play);
}

static void aDUM_actor_init(ACTOR* actor, GAME* game) {
    DUMP_ACTOR* dump = (DUMP_ACTOR*)actor;

    mFI_SetFG_common(DUMMY_DUMP, actor->home.position, FALSE);
    aDUM_actor_move(actor, game);
    actor->mv_proc = aDUM_actor_move;
}

static void aDUM_actor_draw(ACTOR* actor, GAME* game) {
    static Gfx* model[] = { dump_s_DL_model, dump_w_DL_model };
    DUMP_ACTOR* dump = (DUMP_ACTOR*)actor;

    GRAPH* graph = game->graph;
    u16* pal;
    int type;
    Gfx* gfx;
    N64Mtx* cur;

    type = dump->season == mTM_SEASON_WINTER;
    pal = Common_Get(clip.structure_clip)->get_pal_segment_proc(aSTR_PAL_DUMP);

    _texture_z_light_fog_prim_npc(graph);

    OPEN_DISP(graph);

    gfx = NOW_POLY_OPA_DISP;
    gSPSegment(gfx++, 0x8, pal);

    Matrix_translate(-6000.0f, 0.0f,-10000.0f, MTX_MULT);

    cur = _Matrix_to_Mtx_new(graph);

    if (cur != NULL) {
        gSPMatrix(gfx++, cur, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfx++, model[type]);
        SET_POLY_OPA_DISP(gfx);
    }

    (*Common_Get(clip).bg_item_clip->draw_shadow_proc)(game, &aDUM_shadow_data, FALSE);

    CLOSE_DISP(graph);
}
