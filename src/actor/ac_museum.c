#include "ac_museum.h"

#include "m_name_table.h"
#include "bg_item_h.h"
#include "m_common_data.h"
#include "m_house.h"
#include "m_player_lib.h"
#include "m_demo.h"
#include "ac_intro_demo.h"
#include "m_bgm.h"
#include "sys_matrix.h"
#include "m_rcp.h"
#include "libforest/gbi_extensions.h"

static void aMsm_actor_ct(ACTOR* actor, GAME* game);
static void aMsm_actor_init(ACTOR* actor, GAME* game);
static void aMsm_actor_draw(ACTOR* actor, GAME* game);

// clang-format off
ACTOR_PROFILE Museum_Profile = {
    mAc_PROFILE_MUSEUM,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET,
    MUSEUM,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(STRUCTURE_ACTOR),
    &aMsm_actor_ct,
    mActor_NONE_PROC1,
    &aMsm_actor_init,
    &aMsm_actor_draw,
    NULL
};
// clang-format on

// clang-format off
static u8 aMsm_shadow_vtx_fix_flg_table[] = {
    TRUE, FALSE, FALSE, TRUE,
    FALSE, TRUE, TRUE, FALSE
};
// clang-format on

extern Vtx obj_museum_shadow_v[];
extern Gfx obj_museum_shadowT_model[];

// clang-format off
static bIT_ShadowData_c aMsm_shadow_data = {
    8,
    aMsm_shadow_vtx_fix_flg_table,
    60.0f,
    obj_museum_shadow_v,
    obj_museum_shadowT_model
};
// clang-format on

// clang-format off
static Door_data_c aMsm_museum_enter_data = {
    SCENE_MUSEUM_ENTRANCE,
    mSc_DIRECT_NORTH,
    FALSE,
    0,
    {240,0,440},
    EMPTY_NO,
    1,
    {0,0,0},
};
// clang-format on

extern Gfx obj_s_museum_lightT_model[];
extern Gfx obj_s_museum_t1_model[];
extern Gfx obj_s_museum_t2_model[];
extern Gfx obj_s_museum_t3T_model[];
extern Gfx obj_s_museum_windowT_model[];

extern Gfx obj_w_museum_lightT_model[];
extern Gfx obj_w_museum_t1_model[];
extern Gfx obj_w_museum_t2_model[];
extern Gfx obj_w_museum_t3T_model[];
extern Gfx obj_w_museum_windowT_model[];

static void aMsm_set_bgOffset(STRUCTURE_ACTOR* kamakura);
static int aMsm_ctrl_light();

static void aMsm_actor_ct(ACTOR* actor, GAME* game) {
    STRUCTURE_ACTOR* museum;

    museum = (STRUCTURE_ACTOR*)actor;
    museum->season = Common_Get(time.season);

    aMsm_set_bgOffset(museum);

    actor->cull_width = 1000.0f;
    actor->cull_radius = 1600.0f;

    museum->arg0_f = aMsm_ctrl_light() ? 1.0f : 0.0f;
}

static void aMsm_set_bgOffset(STRUCTURE_ACTOR* museum) {
    // clang-format off
    static s_xz unit_offset[35] = {
        { -3, -2 },
        { -2, -2 },
        { -1, -2 },
        { 0, -2 },
        { 1, -2 },
        { 2, -2 },
        { 3, -2 },
        { -3, -1 },
        { -2, -1 },
        { -1, -1 },
        { 0, -1 },
        { 1, -1 },
        { 2, -1 },
        { 3, -1 },
        { -3, 0 },
        { -2, 0 },
        { -1, 0 },
        { 0, 0 },
        { 1, 0 },
        { 2, 0 },
        { 3, 0 },
        { -3, 1 },
        { -2, 1 },
        { -1, 1 },
        { 0, 1 },
        { 1, 1 },
        { 2, 1 },
        { 3, 1 },
        { -3, 2 },
        { -2, 2 },
        { -1, 2 },
        { 0, 2 },
        { 1, 2 },
        { 2, 2 },
        { 3, 2 }
    };
    // clang-format on

    static const mCoBG_OffsetTable_c rewrite_data = {mCoBG_ATTRIBUTE_NONE, 10, 10, 10, 10, 10, 0 };

    xyz_t pos = { 0.0f, 0.0f, 0.0f };
    int i;

    for (i = 0; i < 35; i++) {
        pos.x = museum->actor_class.world.position.x + ((mFI_UT_WORLDSIZE_X_F * (f32)unit_offset[i].x));
        pos.z = museum->actor_class.world.position.z + ((mFI_UT_WORLDSIZE_Z_F * (f32)unit_offset[i].z));

        mCoBG_SetPluss5PointOffset_file(pos, rewrite_data, __FILE__, 291);
    }
}

static void aMsm_rewrite_out_data(ACTOR* actor, GAME_PLAY* play) {
    Door_data_c* door_data;
    xyz_t pos;

    door_data = Common_GetPointer(structure_exit_door_data);
    if (play->fb_wipe_mode != WIPE_MODE_NONE) {
        return;
    }

    door_data->next_scene_id = Save_Get(scene_no);
    door_data->exit_orientation = mSc_DIRECT_SOUTH;
    door_data->exit_type = 0;
    door_data->extra_data = 3;

    pos.x = actor->home.position.x;
    pos.z = actor->home.position.z + 120.0f;
    pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(pos, 0.0f);

    door_data->exit_position.x = pos.x;
    door_data->exit_position.y = pos.y;
    door_data->exit_position.z = pos.z;

    door_data->door_actor_name = MUSEUM;

    door_data->wipe_type = WIPE_TYPE_TRIFORCE;

    mBGMPsComp_make_ps_wipe(0x2168);
}

static int aMsm_ctrl_light() {
    int now_sec = Common_Get(time.now_sec);
    return !(now_sec < (64800) && now_sec >= (21600));
}

static int aMsm_check_player(ACTOR* actor, GAME_PLAY* play) {
    PLAYER_ACTOR* player;
    int res;
    u16 y;
    f32 t;
    f32 xOffs;
    f32 zOffs;

    player = GET_PLAYER_ACTOR(play);
    res = 1;

    if (player == NULL) {
        return 0;
    }

    y = player->actor_class.shape_info.rotation.y;

    xOffs = actor->world.position.x;
    xOffs = SQ(player->actor_class.world.position.x - xOffs);

    zOffs = (actor->world.position.z + 100.0f);
    zOffs = SQ(player->actor_class.world.position.z - zOffs);

    t = (xOffs) + (zOffs);

    if ((y > DEG2SHORT_ANGLE2(135.0f)) && (y < DEG2SHORT_ANGLE2(225.0f)) && (t < 1100.0f)) { // 0x6000 && 0xA000
        res = 2;
    }

    return res;
}

static void aMsm_actor_move(ACTOR* actor, GAME* game) {
    STRUCTURE_ACTOR* museum;
    GAME_PLAY* play;
    f32 target;
    xyz_t pos;

    play = (GAME_PLAY*)game;
    museum = (STRUCTURE_ACTOR*)actor;

    target = aMsm_ctrl_light() ? 1.0f : 0.0f;
    chase_f(&museum->arg0_f, target, 0.019532442f * (f32)game->graph->dt_num_60fps_frames);

    if (museum == GET_PLAYER_ACTOR_NOW()->get_door_label_proc(gamePT)) {
        aMsm_rewrite_out_data(&museum->actor_class, play);
        goto_other_scene(play, &aMsm_museum_enter_data, 0);
        return;
    }

    if (aMsm_check_player(actor, play) != 2) {
        return;
    }

    pos.x = actor->world.position.x;
    pos.y = GET_PLAYER_ACTOR(play)->actor_class.world.position.y;
    pos.z = actor->world.position.z + 100.0f;
    mPlib_request_main_door_type1(game, &pos, -DEG2SHORT_ANGLE(180.0f), TRUE, actor); // 0x8000
}

static void aMsm_actor_init(ACTOR* actor, GAME* game) {
    xyz_t pos;

    pos = actor->home.position;
    mFI_SetFG_common(DUMMY_MUSEUM, pos, FALSE);
    aMsm_actor_move(actor, game);
    actor->mv_proc = aMsm_actor_move;
}

// clang-format off
static Gfx* aMsm_summer_disp_table[] = {
    obj_s_museum_lightT_model,
    obj_s_museum_t1_model,
    obj_s_museum_t2_model,
    obj_s_museum_t3T_model,
    obj_s_museum_windowT_model
};
// clang-format on

// clang-format off
static Gfx* aMsm_winter_disp_table[] = {
    obj_w_museum_lightT_model,
    obj_w_museum_t1_model,
    obj_w_museum_t2_model,
    obj_w_museum_t3T_model,
    obj_w_museum_windowT_model
};
// clang-format on

static void aMsm_actor_draw(ACTOR* actor, GAME* game) {
    static Gfx** disp_info[] = { aMsm_summer_disp_table, aMsm_winter_disp_table };

    STRUCTURE_ACTOR* museum;
    GRAPH* graph;
    N64Mtx* mtx;
    u16* pal;
    Gfx** disp;
    f32 color;
    int r1;
    int g1;
    int b1;
    int l2;
    int r2;
    int g2;
    int b2;

    museum = (STRUCTURE_ACTOR*)actor;
    graph = game->graph;
    pal = Common_Get(clip).structure_clip->get_pal_segment_proc(aSTR_PAL_MUSEUM);
    disp = disp_info[museum->season == mTM_SEASON_WINTER];

    _texture_z_light_fog_prim_xlu(graph);
    _texture_z_light_fog_prim_npc(graph);
    _texture_z_light_fog_prim_shadow(graph);

    OPEN_DISP(graph);
    {
        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPMatrix(NEXT_SHADOW_DISP, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, pal);
        gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_8, pal);
        gSPSegment(NEXT_SHADOW_DISP, G_MWO_SEGMENT_8, pal);

        gDPPipeSync(NEXT_POLY_OPA_DISP);

        color = museum->arg0_f;
        r1 = ((color * 255.0f) + 0.5f);
        g1 = ((color * 255.0f) + 0.5f);
        b1 = ((color * 150.0f) + 0.5f);
        gDPSetPrimColor(NEXT_POLY_OPA_DISP, 0, 0, r1, g1, b1, 255);
        gSPDisplayList(NEXT_POLY_OPA_DISP, disp[0]);
        gSPDisplayList(NEXT_POLY_OPA_DISP, disp[1]);
        gSPDisplayList(NEXT_POLY_OPA_DISP, disp[2]);
        gSPDisplayList(NEXT_POLY_OPA_DISP, disp[3]);

        gDPPipeSync(NEXT_POLY_XLU_DISP);

        if (museum->arg0_f > 0.0f) {
            r2 = 255;
            g2 = 255;
            b2 = 150;
            l2 = (museum->arg0_f * 120.0f) + 0.5f;
        } else {
            l2 = 0;
            r2 = 0;
            g2 = 0;
            b2 = 0;
        }

        gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, l2, r2, g2, b2, 0);
        gSPDisplayList(NEXT_POLY_XLU_DISP, disp[4]);
    }
    CLOSE_DISP(graph);

    (*Common_Get(clip).bg_item_clip->draw_shadow_proc)(game, &aMsm_shadow_data, TRUE);
}
