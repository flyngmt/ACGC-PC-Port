#include "ac_kamakura_indoor.h"

#include "m_name_table.h"
#include "sys_matrix.h"
#include "m_rcp.h"
#include "m_play.h"
#include "audio.h"
#include "m_common_data.h"

static void Kamakura_Indoor_Actor_ct(ACTOR* actorx, GAME* game);
static void Kamakura_Indoor_Actor_dt(ACTOR* actorx, GAME* game);
static void Kamakura_Indoor_Actor_move(ACTOR* actorx, GAME* game);
static void Kamakura_Indoor_Actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Kamakura_Indoor_Profile = {
    mAc_PROFILE_KAMAKURA_INDOOR,
    ACTOR_PART_FG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KAMAKURA_INDOOR,
    sizeof(KAMAKURA_INDOOR_ACTOR),
    &Kamakura_Indoor_Actor_ct,
    &Kamakura_Indoor_Actor_dt,
    &Kamakura_Indoor_Actor_move,
    &Kamakura_Indoor_Actor_draw,
    NULL,
};
// clang-format on

static mCoBG_bg_size_c aKI_mochi_collision_info = { 25.0f, 25.0f, 25.0f, 25.0f };

static void Kamakura_Indoor_Actor_ct(ACTOR* actorx, GAME* game) {
    static xyz_t mochi_pos = { 160.0f, 40.0f, 160.0f };
    KAMAKURA_INDOOR_ACTOR* k_indoor = (KAMAKURA_INDOOR_ACTOR*)actorx;
    
    k_indoor->mochi.pos = mochi_pos;
    k_indoor->mochi.old_pos = mochi_pos;
    k_indoor->mochi.angle_y = 0;
    k_indoor->mochi.move_bg_idx = mCoBG_RegistMoveBg(&k_indoor->mochi.bg_regist, &k_indoor->mochi.pos, &k_indoor->mochi.old_pos, &k_indoor->mochi.angle_y, 35.0f, &aKI_mochi_collision_info, NULL, NULL, NULL, mCoBG_FTR_TYPE_NUM, mCoBG_ATTRIBUTE_STONE, 100.0f);
}

static void Kamakura_Indoor_Actor_dt(ACTOR* actorx, GAME* game) {
    KAMAKURA_INDOOR_ACTOR* k_indoor = (KAMAKURA_INDOOR_ACTOR*)actorx;

    mCoBG_CrossOffMoveBg(k_indoor->mochi.move_bg_idx);
}

extern Gfx rom_kamakura_ring_modelT[];

static void aKI_DrawKamakuraIndoorCandleRing(KAMAKURA_INDOOR_ACTOR* k_indoor, GAME* game) {
    static xyz_t candle_ring_pos[] = { { 142.0f, 106.0f, 38.0f }, { 178.0f, 106.0f, 38.0f } };
    GAME_PLAY* play = (GAME_PLAY*)game;
    f32 scale;
    int i;
    
    _texture_z_light_fog_prim_xlu(game->graph);
    Global_kankyo_set_room_prim(game);
    for (i = 0; i < aKI_CANDLE_NUM; i++) {
        Mtx* mtx = GRAPH_ALLOC_TYPE(game->graph, Mtx, 1);
        
        scale = k_indoor->candle_ring[i].scale * 0.0001f;

        OPEN_DISP(game->graph);

        gDPPipeSync(NEXT_POLY_XLU_DISP);
        suMtxMakeTS(mtx, scale, scale, scale, candle_ring_pos[i].x, candle_ring_pos[i].y, candle_ring_pos[i].z);
        gSPMatrix(NEXT_POLY_XLU_DISP, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPMatrix(NEXT_POLY_XLU_DISP, play->billboard_mtx_p, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW);
        gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, k_indoor->candle_ring[i].color.r, k_indoor->candle_ring[i].color.g, k_indoor->candle_ring[i].color.b, k_indoor->candle_ring[i].color.a);
        gSPDisplayList(NEXT_POLY_XLU_DISP, rom_kamakura_ring_modelT);

        CLOSE_DISP(game->graph);
    }
}

static Gfx* aKI_MakePrimEnvColorXluDisp(u8 r, u8 g, u8 b, u8 a, u8 f, u8 env_r, u8 env_g, u8 env_b, u8 env_a, GAME* game) {
    Gfx* gfx = GRAPH_ALLOC_TYPE(game->graph, Gfx, 4);

    if (gfx != NULL) {
        gDPPipeSync(&gfx[0]);
        gDPSetPrimColor(&gfx[1], 0, f, r, g, b, a);
        gDPSetEnvColor(&gfx[2], env_r, env_g, env_b, env_a);
        gSPEndDisplayList(&gfx[3]);
        return gfx;
    } else {
        return NULL;
    }
}

extern u8 rom_kamakura_a1[];
extern u8 rom_kamakura_a2_rgb_ci4[];

static u8* rom_kamakura_evw_anime_4_tex_table[] = { rom_kamakura_a1, rom_kamakura_a2_rgb_ci4 };

extern Gfx rom_kamakura_model[];
extern Gfx rom_kamakura_modelT[];

static void aKI_DrawKamakuraIndoorBG(KAMAKURA_INDOOR_ACTOR* k_indoor, GAME* game) {
    Gfx* gfx0 = aKI_MakePrimEnvColorXluDisp(k_indoor->candle_fire[0].color.r, k_indoor->candle_fire[0].color.g, k_indoor->candle_fire[0].color.b, k_indoor->candle_fire[0].color.a, 128, 255, 50, 0, 255, game);
    Gfx* gfx1 = aKI_MakePrimEnvColorXluDisp(k_indoor->candle_fire[1].color.r, k_indoor->candle_fire[1].color.g, k_indoor->candle_fire[1].color.b, k_indoor->candle_fire[1].color.a, 128, 255, 50, 0, 255, game);
    Gfx* scroll_gfx;

    if (gfx0 == NULL || gfx1 == NULL) {
        return;
    }
    
    _texture_z_light_fog_prim(game->graph);
    _texture_z_light_fog_prim_xlu(game->graph);
    Global_kankyo_set_room_prim(game);
    
    OPEN_DISP(game->graph);

    Matrix_translate(0.0f, 0.0f, 0.0f, MTX_LOAD);
    Matrix_scale(0.0625f, 0.0625f, 0.0625f, MTX_MULT);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NEXT_POLY_XLU_DISP, ANIME_2_TXT_SEG, k_indoor->candle_fire[0].tex_p);
    gSPSegment(NEXT_POLY_XLU_DISP, ANIME_1_TXT_SEG, gfx0);
    gSPSegment(NEXT_POLY_XLU_DISP, ANIME_3_TXT_SEG, k_indoor->candle_fire[1].tex_p);
    gSPSegment(NEXT_POLY_XLU_DISP, ANIME_5_TXT_SEG, gfx1);
    gSPSegment(NEXT_POLY_OPA_DISP, ANIME_4_TXT_SEG, rom_kamakura_evw_anime_4_tex_table[(game->frame_counter / 6) & 1]);
    scroll_gfx = two_tex_scroll_dolphin(game->graph, 0, -game->frame_counter, 0, 32, 16, 1, -game->frame_counter * -1, -(-game->frame_counter * 2), 32, 16);
    gSPSegment(NEXT_POLY_XLU_DISP, ANIME_6_TXT_SEG, scroll_gfx);
    gSPDisplayList(NEXT_POLY_OPA_DISP, rom_kamakura_model);
    gSPDisplayList(NEXT_POLY_XLU_DISP, rom_kamakura_modelT);

    CLOSE_DISP(game->graph);
}

static void Kamakura_Indoor_Actor_draw(ACTOR* actorx, GAME* game) {
    KAMAKURA_INDOOR_ACTOR* k_indoor = (KAMAKURA_INDOOR_ACTOR*)actorx;

    aKI_DrawKamakuraIndoorBG(k_indoor, game);
    aKI_DrawKamakuraIndoorCandleRing(k_indoor, game);
}

// @unused - only used in DnM and DnM+, necessary for float ordering
static f32 aKI_MakeSinPointSquare(void) {
    f32 f = cos_s(1);
    s16 t = RAD2SHORT_ANGLE2(f);
    f32 a = t;
    a += (3.14f);
    return a;
}

static f32 aKI_MakeSinPointHalf(s16 start_frame, f32 start, s16 end_frame, f32 end, s16 now_frame) {
    if (start_frame > end_frame || start_frame == end_frame) {
        return start;
    }

    if (now_frame <= start_frame) {
        return start;
    }

    if (now_frame >= end_frame) {
        return end;
    } else {
        f32 sf = (f32)start_frame;
        f32 ef = (f32)end_frame;
        f32 m = ef - sf;
        f32 midpoint = (start + end) * 0.5f;
        f32 nf = (f32)now_frame;
        f32 halfpoint = ABS(end - midpoint);
        f32 percent = ((nf - sf) * 3.14f) / m;

        if (start >= end) {
            return midpoint + cos_s(RAD2SHORT_ANGLE2(percent)) * halfpoint;
        } else {
            return midpoint + cos_s(RAD2SHORT_ANGLE2(percent)) * -halfpoint;
        }
    }
}

typedef struct candle_color_data_s {
    s16 frame;
    f32 scale;
    f32 g;
    f32 a;
} aKI_candle_color_data_c;

typedef struct candle_ring_data_s {
    aKI_candle_color_data_c start_col;
    aKI_candle_color_data_c end_col;
} aKI_candle_ring_data_c;

static aKI_candle_ring_data_c aKI_candle_ring_anime_data[] = {
    { { 0, 95.0f, 230.0f, 100.0f }, { 9, 105.0f, 250.0f, 60.0f } },
    { { 0, 95.0f, 230.0f, 100.0f }, { 9, 105.0f, 250.0f, 60.0f } },
    { { 0, 95.0f, 230.0f, 100.0f }, { 9, 105.0f, 250.0f, 60.0f } },
    { { 0, 95.0f, 230.0f, 100.0f }, { 9, 105.0f, 250.0f, 60.0f } },
    { { 0, 95.0f, 230.0f, 100.0f }, { 9, 105.0f, 250.0f, 60.0f } },
    { { 0, 95.0f, 230.0f, 100.0f }, { 9, 105.0f, 250.0f, 60.0f } },
    { { 0, 95.0f, 230.0f, 100.0f }, { 9, 105.0f, 250.0f, 60.0f } },
    { { 0, 95.0f, 230.0f, 100.0f }, { 9, 105.0f, 250.0f, 60.0f } },
    { { 0, 95.0f, 230.0f, 100.0f }, { 9, 105.0f, 250.0f, 60.0f } },
    { { 0, 95.0f, 230.0f, 100.0f }, { 9, 105.0f, 250.0f, 60.0f } },
    { { 9, 105.0f, 250.0f, 60.0f }, { 17, 100.0f, 230.0f, 80.0f } },
    { { 9, 105.0f, 250.0f, 60.0f }, { 17, 100.0f, 230.0f, 80.0f } },
    { { 9, 105.0f, 250.0f, 60.0f }, { 17, 100.0f, 230.0f, 80.0f } },
    { { 9, 105.0f, 250.0f, 60.0f }, { 17, 100.0f, 230.0f, 80.0f } },
    { { 9, 105.0f, 250.0f, 60.0f }, { 17, 100.0f, 230.0f, 80.0f } },
    { { 9, 105.0f, 250.0f, 60.0f }, { 17, 100.0f, 230.0f, 80.0f } },
    { { 9, 105.0f, 250.0f, 60.0f }, { 17, 100.0f, 230.0f, 80.0f } },
    { { 9, 105.0f, 250.0f, 60.0f }, { 17, 100.0f, 230.0f, 80.0f } },
    { { 17, 100.0f, 230.0f, 80.0f }, { 25, 105.0f, 210.0f, 50.0f } },
    { { 17, 100.0f, 230.0f, 80.0f }, { 25, 105.0f, 210.0f, 50.0f } },
    { { 17, 100.0f, 230.0f, 80.0f }, { 25, 105.0f, 210.0f, 50.0f } },
    { { 17, 100.0f, 230.0f, 80.0f }, { 25, 105.0f, 210.0f, 50.0f } },
    { { 17, 100.0f, 230.0f, 80.0f }, { 25, 105.0f, 210.0f, 50.0f } },
    { { 17, 100.0f, 230.0f, 80.0f }, { 25, 105.0f, 210.0f, 50.0f } },
    { { 17, 100.0f, 230.0f, 80.0f }, { 25, 105.0f, 210.0f, 50.0f } },
    { { 17, 100.0f, 230.0f, 80.0f }, { 25, 105.0f, 210.0f, 50.0f } },
    { { 25, 105.0f, 210.0f, 50.0f }, { 33, 95.0f, 230.0f, 100.0f } },
    { { 25, 105.0f, 210.0f, 50.0f }, { 33, 95.0f, 230.0f, 100.0f } },
    { { 25, 105.0f, 210.0f, 50.0f }, { 33, 95.0f, 230.0f, 100.0f } },
    { { 25, 105.0f, 210.0f, 50.0f }, { 33, 95.0f, 230.0f, 100.0f } },
    { { 25, 105.0f, 210.0f, 50.0f }, { 33, 95.0f, 230.0f, 100.0f } },
    { { 25, 105.0f, 210.0f, 50.0f }, { 33, 95.0f, 230.0f, 100.0f } },
    { { 25, 105.0f, 210.0f, 50.0f }, { 33, 95.0f, 230.0f, 100.0f } },
    { { 25, 105.0f, 210.0f, 50.0f }, { 33, 95.0f, 230.0f, 100.0f } },
};

typedef struct mochi_anim_s {
    s16 frame;
    xyz_t scale;
    f32 ofs_y;
} aKI_mochi_anim_c;

typedef struct mochi_anim_data_s {
    int type;
    aKI_mochi_anim_c start;
    aKI_mochi_anim_c end;
} aKI_mochi_anim_data_c;

static aKI_mochi_anim_data_c aKI_mochi_anime_data[] = {
    { 2, { 0, { 70.0f, 40.0f, 70.0f}, -9.0f }, { 240, { 70.0f, 40.0f, 70.0f }, -9.0f } },
    { 0, { 240, { 70.0f, 40.0f, 70.0f}, -9.0f }, { 380, { 85.0f, 75.0f, 85.0f }, -4.5 } },
    { 2, { 380, { 85.0f, 75.0f, 85.0f}, -4.5 }, { 420, { 85.0f, 75.0f, 85.0f }, -4.5 } },
    { 0, { 420, { 85.0f, 75.0f, 85.0f}, -4.5 }, { 600, { 100.0f, 100.0f, 100.0f }, 0.0f } },
    { 2, { 600, { 100.0f, 100.0f, 100.0f}, 0.0f }, { 760, { 100.0f, 100.0f, 100.0f }, 0.0f } },
    { 1, { 760, { 100.0f, 100.0f, 100.0f}, 0.0f }, { 810, { 70.0f, 40.0f, 70.0f }, -9.0f } },
    { 2, { 810, { 70.0f, 40.0f, 70.0f}, -9.0f }, { 970, { 70.0f, 40.0f, 70.0f }, -9.0f } },
    { 0, { 970, { 70.0f, 40.0f, 70.0f}, -9.0f }, { 1210, { 100.0f, 100.0f, 100.0f }, 0.0f } },
    { 2, { 1210, { 100.0f, 100.0f, 100.0f}, 0.0f }, { 1330, { 100.0f, 100.0f, 100.0f }, 0.0f } },
    { 1, { 1330, { 100.0f, 100.0f, 100.0f}, 0.0f }, { 1400, { 70.0f, 40.0f, 70.0f }, -9.0f } },
};

// clang-format off
static rgba_t aKI_candle_fire_rgba_data[] = {
    { 255, 220,   0, 180 },
    { 255, 220,   0, 180 },
    { 255, 225,   0, 165 },
    { 255, 225,   0, 165 },
    { 255, 230,   0, 150 },
    { 255, 230,   0, 150 },
    { 255, 225,   0, 165 },
    { 255, 225,   0, 165 },
    { 255, 220,   0, 180 },
    { 255, 220,   0, 180 },
    { 255, 215,   0, 202 },
    { 255, 215,   0, 202 },
    { 255, 210,   0, 225 },
    { 255, 210,   0, 225 },
    { 255, 215,   0, 235 },
    { 255, 215,   0, 235 },
    { 255, 220,   0, 245 },
    { 255, 220,   0, 245 },
    { 255, 225,   0, 222 },
    { 255, 225,   0, 222 },
    { 255, 230,   0, 200 },
    { 255, 230,   0, 200 },
    { 255, 210,   0, 190 },
    { 255, 210,   0, 190 },
};
// clang-format on

extern u8 rom_kamakura_fire1_rgb_i4[];
extern u8 rom_kamakura_fire2_rgb_i4[];
extern u8 rom_kamakura_fire3_rgb_i4[];

// clang-format off
static u8* aKI_candle_fire_anime_data[] = {
    rom_kamakura_fire2_rgb_i4,
    rom_kamakura_fire2_rgb_i4,
    rom_kamakura_fire2_rgb_i4,
    rom_kamakura_fire2_rgb_i4,
    rom_kamakura_fire1_rgb_i4,
    rom_kamakura_fire1_rgb_i4,
    rom_kamakura_fire1_rgb_i4,
    rom_kamakura_fire1_rgb_i4,
    rom_kamakura_fire2_rgb_i4,
    rom_kamakura_fire2_rgb_i4,
    rom_kamakura_fire2_rgb_i4,
    rom_kamakura_fire2_rgb_i4,
    rom_kamakura_fire3_rgb_i4,
    rom_kamakura_fire3_rgb_i4,
    rom_kamakura_fire3_rgb_i4,
    rom_kamakura_fire3_rgb_i4,
    rom_kamakura_fire2_rgb_i4,
    rom_kamakura_fire2_rgb_i4,
    rom_kamakura_fire2_rgb_i4,
    rom_kamakura_fire2_rgb_i4,
    rom_kamakura_fire1_rgb_i4,
    rom_kamakura_fire1_rgb_i4,
    rom_kamakura_fire1_rgb_i4,
    rom_kamakura_fire1_rgb_i4,
};
// clang-format on

static void Kamakura_Indoor_Actor_move(ACTOR* actorx, GAME* game) {
    KAMAKURA_INDOOR_ACTOR* k_indoor = (KAMAKURA_INDOOR_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;
    aKI_candle_ring_c* ring_p = k_indoor->candle_ring;
    aKI_candle_fire_c* fire_p = k_indoor->candle_fire;
    u32 counter = game->frame_counter;
    static u32 candle_ring_late_frame[] = { 0, 7 };
    static u32 candle_fire_late_frame[] = { 0, 6 };
    int i;
    s16 timer;

    sAdo_OngenPos((uintptr_t)actorx, NA_SE_KOKORO_TOGURU, &k_indoor->mochi.pos);
    if ((play->game_frame & 7) == 0) {
        xyz_t soba_yuge_pos = k_indoor->mochi.pos;

        soba_yuge_pos.y += 42.0f;
        eEC_CLIP->effect_make_proc(eEC_EFFECT_SOBA_YUGE, soba_yuge_pos, 1, 0, game, RSV_NO, 14, 1);
    }

    for (i = 0; i < aKI_CANDLE_NUM; i++) {
        s16 type;

        type = (counter - candle_ring_late_frame[i & 1]) % 34;
        ring_p->color.r = 255;
        ring_p->color.g = ABS(aKI_MakeSinPointHalf(aKI_candle_ring_anime_data[type].start_col.frame, aKI_candle_ring_anime_data[type].start_col.g, aKI_candle_ring_anime_data[type].end_col.frame, aKI_candle_ring_anime_data[type].end_col.g, type));
        ring_p->color.b = 0;
        ring_p->color.a = ABS(aKI_MakeSinPointHalf(aKI_candle_ring_anime_data[type].start_col.frame, aKI_candle_ring_anime_data[type].start_col.a, aKI_candle_ring_anime_data[type].end_col.frame, aKI_candle_ring_anime_data[type].end_col.a, type));
        ring_p->scale = aKI_MakeSinPointHalf(aKI_candle_ring_anime_data[type].start_col.frame, aKI_candle_ring_anime_data[type].start_col.scale, aKI_candle_ring_anime_data[type].end_col.frame, aKI_candle_ring_anime_data[type].end_col.scale, type);
        ring_p++;
        
        type = (counter - candle_fire_late_frame[i & 1]) % 24;
        fire_p->tex_p = aKI_candle_fire_anime_data[type];
        fire_p->color = aKI_candle_fire_rgba_data[type];
        fire_p++;
    }
}
