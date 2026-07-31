#include "ac_tent.h"
#include "bg_item_h.h"
#include "m_player_lib.h"
#include "m_collision_bg.h"
#include "m_field_info.h"
#include "sys_matrix.h"
#include "m_common_data.h"
#include "m_bgm.h"
#include "m_rcp.h"

static void aTnt_actor_ct(ACTOR* actor, GAME* game);
static void aTnt_actor_dt(ACTOR* actor, GAME* game);
static void aTnt_actor_init(ACTOR* actor, GAME* game);
static void aTnt_actor_draw(ACTOR* actor, GAME* game);

ACTOR_PROFILE Tent_Profile = {
    mAc_PROFILE_TENT, ACTOR_PART_ITEM, ACTOR_STATE_TA_SET, TENT, ACTOR_OBJ_BANK_KEEP, sizeof(TENT_ACTOR), aTnt_actor_ct,
    aTnt_actor_dt,    aTnt_actor_init, aTnt_actor_draw,    NULL,
};

extern Vtx obj_s_tent_shadow_v[];
extern Gfx obj_s_tent_shadow_modelT[];

u8 aTnt_shadow_vtx_fix_flg_table[] = {
    FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,  TRUE, FALSE, TRUE,  TRUE,  FALSE, FALSE, TRUE,
    TRUE,  FALSE, FALSE, TRUE,  TRUE,  FALSE, FALSE, TRUE, TRUE,  FALSE, FALSE, TRUE,  TRUE,  FALSE,
};

bIT_ShadowData_c aTnt_shadow_data = {
    28, aTnt_shadow_vtx_fix_flg_table, 60.0f, obj_s_tent_shadow_v, obj_s_tent_shadow_modelT,
};

Door_data_c aTnt_tent_enter_data = {
    SCENE_TENT, 4, FALSE, 0, { 120, 0, 220 }, EMPTY_NO, 1, { 0, 0, 0 },
};

static void aTnt_ChangeFg(ACTOR* actor, int type);
static void aTnt_SetupAction(ACTOR* actor, int type);
static void aTnt_SetBgOffset(ACTOR* actor, int offset);
static int aTnt_ControlLight(ACTOR* actor);

static void aTnt_actor_ct(ACTOR* actor, GAME* game) {
    TENT_ACTOR* tent = (TENT_ACTOR*)actor;
    f32 t;

    aTnt_ChangeFg(actor, 1);
    aTnt_SetupAction(actor, 0);
    aTnt_SetBgOffset(actor, 1);

    if (aTnt_ControlLight(actor) != 0) {
        t = 1.0f;
    } else {
        t = 0.0f;
    }

    tent->structure_class.arg0_f = t;
}

static void aTnt_actor_dt(ACTOR* actor, GAME* game) {
    aTnt_ChangeFg(actor, 0);
}

static void aTnt_ChangeFg(ACTOR* actor, int type) {
    xyz_t pos = actor->world.position;
    mActor_name_t* name;

    pos.z += 80.0f;

    if (type == 0) {
        mFI_SetFG_common(0, pos, 1);
        return;
    }

    name = mFI_GetUnitFG(pos);
    if (name != NULL) {
        if (mSN_ClearSnowman(name) == 0) {
            int dug = FALSE;

            if ((((*name >= BURIED_PITFALL_HOLE_START) && (*name <= BURIED_PITFALL_HOLE_END)) ||
                 (*name == SHINE_SPOT))) {
                dug = TRUE;
            }

            if (dug == TRUE) {
                mPB_keep_item(bg_item_fg_sub_dig2take_conv(*name));
                mFI_SetFG_common(RSV_NO, pos, 1);
                mFI_Wpos2DepositOFF(pos);
            } else {
                mFI_Wpos2DepositOFF(pos);
                mPB_keep_item(*name);
                mFI_SetFG_common(RSV_NO, pos, 1);
            }
        } else {
            mFI_SetFG_common(RSV_NO, pos, 1);
        }
    }
}

static void aTnt_SetBgOffset(ACTOR* actor, int type) {
    static mCoBG_OffsetTable_c height_table_ct[] = {
        { 100, 3, 1, 1, 7, 7, 0 }, { 100, 10, 10, 10, 10, 10, 0 }, { 100, 3, 7, 7, 1, 1, 0 },
        { 100, 3, 1, 1, 7, 7, 0 }, { 100, 10, 10, 10, 10, 10, 0 }, { 100, 3, 7, 7, 1, 1, 0 },
        { 100, 3, 3, 3, 3, 3, 0 }, { 100, 10, 10, 10, 10, 10, 0 }, { 100, 3, 3, 3, 3, 3, 0 },
    };
    static mCoBG_OffsetTable_c* height_table[] = { height_table_ct, height_table_ct };
    mCoBG_OffsetTable_c* tbl = height_table[type];
    int j;
    int i;

    for (i = -1; i <= 1; i++) {
        for (j = -1; j <= 1; j++) {
            xyz_t pos = actor->world.position;
            pos.x += 40.0f * j;
            pos.z += 40.0f * i;

            mCoBG_SetPluss5PointOffset_file(pos, tbl[0], __FILE__, 286);
            tbl++;
        }
    }
}

static void aTnt_rewrite_out_data(ACTOR* actor, GAME_PLAY* play) {
    Door_data_c* door_data = Common_GetPointer(structure_exit_door_data);

    if (play->fb_wipe_mode == WIPE_MODE_NONE) {
        xyz_t pos;

        door_data->next_scene_id = Save_Get(scene_no);
        door_data->exit_orientation = 0;
        door_data->exit_type = 0;
        door_data->extra_data = 3;

        pos.x = actor->world.position.x;
        pos.z = actor->world.position.z + 86.0f;
        pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(pos, 0.0f);

        door_data->exit_position.x = pos.x;
        door_data->exit_position.y = pos.y;
        door_data->exit_position.z = pos.z;

        door_data->door_actor_name = TENT;

        door_data->wipe_type = WIPE_TYPE_TRIFORCE;
        mBGMPsComp_make_ps_wipe(0x2168);
    }
}

static int aTnt_check_player(ACTOR* actor, GAME_PLAY* play) {
    u16 y;
    f32 xOffs;
    f32 zOffs;
    f32 t;
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR(play);

    if (player != NULL) {
        y = player->actor_class.shape_info.rotation.y;
        xOffs = SQ(player->actor_class.world.position.x - actor->world.position.x);
        zOffs = SQ(player->actor_class.world.position.z - (actor->world.position.z + 40.0f));
        t = (xOffs) + (zOffs);

        if ((y > 0x6000) && (y < 0xA000) && (t < 1600.0f)) {
            return 1;
        }
    }
    return 0;
}

static void aTnt_wait(STRUCTURE_ACTOR* actor, GAME_PLAY* play) {
    xyz_t pos;

    if (actor == GET_PLAYER_ACTOR_NOW()->get_door_label_proc(gamePT)) {
        aTnt_rewrite_out_data(&actor->actor_class, play);
        goto_other_scene(play, &aTnt_tent_enter_data, 1);
    } else if (aTnt_check_player(&actor->actor_class, play) != 0) {
        pos.x = actor->actor_class.world.position.x;
        pos.y = GET_PLAYER_ACTOR(play)->actor_class.world.position.y;
        pos.z = 68.0f + actor->actor_class.world.position.z;
        mPlib_request_main_door_type1(&play->game, &pos, -0x8000, 1, &actor->actor_class);
    }
}

static void aTnt_SetupAction(ACTOR* actor, int type) {
    static aSTR_MOVE_PROC process[] = {
        aTnt_wait,
    };
    TENT_ACTOR* tent = (TENT_ACTOR*)actor;

    tent->structure_class.action_proc = process[type];
    tent->structure_class.action = type;
}

static int aTnt_ControlLight(ACTOR* actor) {
    if (Common_Get(time.now_sec) >= 18000 && Common_Get(time.now_sec) < 64800) {
        return 0;
    }
    return 1;
}

static void aTnt_actor_move(ACTOR* actor, GAME* game) {
    STRUCTURE_ACTOR* tent = (STRUCTURE_ACTOR*)actor;
    GAME_PLAY* play = (GAME_PLAY*)game;

    PLAYER_ACTOR* player = GET_PLAYER_ACTOR(play);
    int bx1;
    int bz1;
    int bx2;
    int bz2;

    if ((mFI_Wpos2BlockNum(&bx1, &bz1, actor->world.position) != 0) &&
        (mFI_Wpos2BlockNum(&bx2, &bz2, actor->world.position) != 0) && ((bx1 != bx2) || (bz1 != bz2)) &&
        (mDemo_Check(mDemo_TYPE_SCROLL, &player->actor_class) == FALSE) &&
        (mDemo_Check(mDemo_TYPE_SCROLL2, &player->actor_class) == FALSE) &&
        (mDemo_Check(mDemo_TYPE_SCROLL3, &player->actor_class) == FALSE)) {
        Actor_delete(actor);
    } else {
        f32 window;

        tent->action_proc(tent, play);

        window = (aTnt_ControlLight(actor) != 0) ? 1.0f : 0.0f;
        chase_f(&tent->arg0_f, window, 0.019532442f * (f32)game->graph->dt_num_60fps_frames);
    }
}

static void aTnt_actor_init(ACTOR* actor, GAME* game) {
    mFI_SetFG_common(DUMMY_TENT, actor->home.position, 0);
    aTnt_actor_move(actor, game);
    actor->mv_proc = aTnt_actor_move;
}

static Gfx* aTnt_MakeWindowPrimDisplayList(ACTOR* actor, GAME* game) {
    TENT_ACTOR* tent = (TENT_ACTOR*)actor;

    GRAPH* graph = game->graph;
    Gfx* gfx = GRAPH_ALLOC_TYPE(graph, Gfx, 2);
    f32 tent_color = tent->structure_class.arg0_f;

    OPEN_DISP(graph);

    gDPSetPrimColor(&gfx[0], 0, 255, (int)(tent_color * 255.0f), (int)(tent_color * 255.0f), (int)(tent_color * 150.0f),
                    255);
    gSPEndDisplayList(&gfx[1]);

    CLOSE_DISP(graph);

    return gfx;
}

extern Gfx obj_s_tent_model[];

static void aTnt_actor_draw(ACTOR* actor, GAME* game) {
    N64Mtx* m = _Matrix_to_Mtx_new(game->graph);
    Gfx* gfx = aTnt_MakeWindowPrimDisplayList(actor, game);

    if (gfx != NULL) {
        _texture_z_light_fog_prim_npc(game->graph);
        _texture_z_light_fog_prim_shadow(game->graph);

        OPEN_DISP(game->graph);

        gSPMatrix(NEXT_POLY_OPA_DISP, m, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(NEXT_POLY_OPA_DISP, 8, gfx);

        gSPDisplayList(NEXT_POLY_OPA_DISP, obj_s_tent_model);

        (*Common_Get(clip).bg_item_clip->draw_shadow_proc)(game, &aTnt_shadow_data, FALSE);

        CLOSE_DISP(game->graph);
    }
}
