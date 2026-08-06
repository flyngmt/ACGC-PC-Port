#include "ac_train_window.h"
#include "m_common_data.h"
#include "m_debug.h"
#include "m_name_table.h"
#include "evw_anime.h"
#include "m_rcp.h"
#include "m_play.h"
#include "sys_matrix.h"

// clang-format off
ATTRIBUTE_ALIGN(32) static u16 aTrainWindow_tree_pal_table[15][16] = {
    {
        0x0724,0xA443,
        0xBCA4,0xDD25,
        0xF5E7,0xF209,
        0xFECD,0x0545,
        0x9885,0xA0C5,
        0xAD05,0xBD66,
        0xCDE8,0xD2FA,
        0xE77C,0xF3BE
    },
    {
        0x0724,0xA443,
        0xBCA4,0xDD25,
        0xF5E7,0xF209,
        0xFECD,0x0655,
        0x98C5,0xA105,
        0xB165,0xC1E6,
        0xD268,0xD2FA,
        0xE77C,0xF3BE
    },
    {
        0x0724,0xA443,
        0xBCA4,0xDD25,
        0xF5E7,0xF209,
        0xFECD,0x0464,
        0x90C3,0x9504,
        0xA184,0xAA05,
        0xB287,0xD2FA,
        0xE77C,0xF3BE
    },
    {
        0x0724,0xA443,
        0xBCA4,0xDD25,
        0xF5E7,0xF209,
        0xFECD,0x0164,
        0x80E5,0x8145,
        0x89A4,0x9A60,
        0xB300,0xD380,
        0xEFE8,0x8000
    },
    {
        0x0724,0xA443,
        0xBCA4,0xDD25,
        0xF5E7,0xF209,
        0xFECD,0x0C37,
        0xB086,0xC8A7,
        0xE0C7,0xF109,
        0xF98C,0xFE10,
        0xFF18,0x8000
    },
    {
        0x0724,0xA443,
        0xBCA4,0xDD25,
        0xF5E7,0xF209,
        0xFECD,0x0066,
        0x80C9,0x8127,
        0x8186,0x8202,
        0x82C1,0x9380,
        0xCBE8,0x8000
    },
    {
        0x0724,0xA443,
        0xBCA4,0xDD25,
        0xF5E7,0xF209,
        0xFECD,0x0058,
        0x80C9,0x80E8,
        0x8148,0x81C8,
        0x8268,0x9326,
        0xC3EB,0x8000
    },
    {
        0x0724,0xA443,
        0xBCA4,0xDD25,
        0xF5E7,0xF209,
        0xFECD,0x0353,
        0x8CC2,0x9102,
        0x9963,0xA5C4,
        0xB242,0xC6E4,
        0xDB88,0x8000
    },
    {
        0x0724,0xA443,
        0xBCA4,0xDD25,
        0xF5E7,0xF209,
        0xFECD,0x0564,
        0x90C5,0x9924,
        0xA984,0xBA03,
        0xD2A3,0xE304,
        0xEF6A,0x8000
    },
    {
        0x0724,0xA443,
        0xBCA4,0xDD25,
        0xF5E7,0xF209,
        0xFECD,0x0842,
        0xA463,0xB4A2,
        0xC502,0xD961,
        0xE9E1,0xF682,
        0xFF26,0x8000
    },
    {
        0x0724,0xA443,
        0xBCA4,0xDD25,
        0xF5E7,0xF209,
        0xFECD,0x0814,
        0xB024,0xC044,
        0xCC85,0xE0C6,
        0xF128,0xFE0B,
        0xFEEB,0x8000
    },
    {
        0x0724,0xA443,
        0xBCA4,0xDD25,
        0xF5E7,0xF209,
        0xFECD,0x0734,
        0xA484,0xAC83,
        0xBCC4,0xD503,
        0xE985,0xF629,
        0xFF0E,0x8000
    },
    {
        0x0724,0xA443,
        0xBCA4,0xDD25,
        0xF5E7,0xF209,
        0xFECD,0x0635,
        0xA085,0xA8C5,
        0xB505,0xC566,
        0xD5E8,0xEE8A,
        0xFF2C,0x8000
    },
    {
        0x0724,0xA443,
        0xBCA4,0xDD25,
        0xF5E7,0xF209,
        0xFECD,0x0545,
        0x9885,0xA0C5,
        0xAD05,0xBD66,
        0xCDE8,0xD2FA,
        0xE77C,0xF3BE
    },
    {
        0x0724,0xA443,
        0xBCA4,0xDD25,
        0xF5E7,0xF209,
        0xFECD,0x0545,
        0x9885,0xA0C5,
        0xAD05,0xBD66,
        0xCDE8,0xD2FA,
        0xE77C,0xF3BE
    },
};
// clang-format on

static EVW_ANIME_SCROLL aTrainWindow_out_cloud = { 0, -2, 64, 64 };

static EVW_ANIME_DATA aTrainWindow_evw_anime_data = { -2, EVW_ANIME_TYPE_SCROLL1, &aTrainWindow_out_cloud };

static void Train_Window_Actor_ct(ACTOR*, GAME*);
static void Train_Window_Actor_dt(ACTOR*, GAME*);
static void Train_Window_Actor_move(ACTOR*, GAME*);
static void Train_Window_Actor_draw(ACTOR*, GAME*);

ACTOR_PROFILE Train_Window_Profile = {
    mAc_PROFILE_TRAIN_WINDOW,
    ACTOR_PART_ITEM,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    ETC_TRAIN_WINDOW,
    ACTOR_OBJ_BANK_TRAINWINDOW,
    sizeof(TRAIN_WINDOW_ACTOR),
    &Train_Window_Actor_ct,
    &Train_Window_Actor_dt,
    &Train_Window_Actor_move,
    &Train_Window_Actor_draw,
    NULL,
};

static int aTrainWindow_NoDraw(ACTOR*, GAME*);
static int aTrainWindow_DrawGoneOutTunnel(ACTOR*, GAME*);
static int aTrainWindow_DrawInTunnel(ACTOR*, GAME*);

extern Gfx rom_train_out_tunnel_model[];
extern Gfx rom_train_out_bgsky_model[];
extern Gfx rom_train_out_bgcloud_modelT[];
extern Gfx rom_train_out_bgtree_modelT[];
extern Gfx rom_train_out_shineglass_modelT[];

static int aTrainWindow_GetTreePalletIdx() {
    static u8 till_data[15][2] = {
        { 0x02, 0x03 }, { 0x02, 0x11 }, { 0x02, 0x18 }, { 0x04, 0x03 }, { 0x04, 0x08 },
        { 0x07, 0x16 }, { 0x09, 0x0F }, { 0x0A, 0x05 }, { 0x0A, 0x17 }, { 0x0B, 0x07 },
        { 0x0B, 0x0E }, { 0x0B, 0x1C }, { 0x0C, 0x0A }, { 0x0C, 0x11 }, { 0x0C, 0x1F },
    };

    int i;
    lbRTC_month_t month = Common_Get(time.rtc_time.month);
    lbRTC_day_t day = Common_Get(time.rtc_time.day);

    for (i = 0; i < 15; i++) {
        if (month < till_data[i][0]) {
            return i;
        }

        if (month == till_data[i][0] && day <= till_data[i][1]) {
            return i;
        }
    }

    return 0;
}

static void Train_Window_Actor_ct(ACTOR* actor, GAME* game) {
    TRAIN_WINDOW_ACTOR* window = (TRAIN_WINDOW_ACTOR*)actor;

    switch (Save_Get(scene_no)) {
        case SCENE_START_DEMO:
        case SCENE_START_DEMO3:
            window->draw_type = &aTrainWindow_NoDraw;
            window->Single_Scrollx = 0;
            window->Single_Scrolly = 0;
            window->Two_Scrollx1 = 0;
            window->Two_Scrolly1 = 0;
            window->Two_Scrollx2 = 0;
            window->Two_Scrolly2 = 0;
            window->scroll_speed = 0.07f;
            window->tree_scroll_subtexels = 0;
            break;

        case SCENE_START_DEMO2:
            window->draw_type = &aTrainWindow_DrawGoneOutTunnel;
            window->Single_Scrollx = 1000;
            window->Single_Scrolly = 0;
            window->Two_Scrollx1 = 1000;
            window->Two_Scrolly1 = 0;
            window->Two_Scrollx2 = 0;
            window->Two_Scrolly2 = 0;
            window->scroll_speed = 1.0f;
            window->tree_scroll_subtexels = 0;
            break;
    }
    window->pallete_id = aTrainWindow_GetTreePalletIdx();
    window->current_pallete = aTrainWindow_tree_pal_table[window->pallete_id];
    window->TreeScrollx = 500;
    window->TreeScrolly = 0;
    window->pos.x = 0;
    window->pos.y = 0;
    window->pos.z = 0;
    window->xlu_alpha = 254.0f;
}

static void Train_Window_Actor_dt(ACTOR* actor, GAME* game) {
}

static u8 aTW_GetNowAlpha() {

    if ((Common_Get(time.now_sec) >= 14400) && (Common_Get(time.now_sec) < 72000)) {
        if (Common_Get(time.now_sec) < 43200) {
            return 255.0f * ((f32)(Common_Get(time.now_sec) - 14400) / 28800.0f);
        }
        return 255.0f * (1.0f - ((f32)(Common_Get(time.now_sec) - 43200) / 28800.0f));
    } else if (Common_Get(time.now_sec) < 14400) {
        return 200.0f * (1.0f - (0.5f + ((f32)Common_Get(time.now_sec) / 28800.0f)));
    } else {
        return 200.0f * ((f32)Common_Get(time.now_sec - 72000) / 28800.0f);
    }
}

static void Train_Window_Actor_move(ACTOR* actor, GAME* game) {
    TRAIN_WINDOW_ACTOR* window = (TRAIN_WINDOW_ACTOR*)actor;

    f32 alpha;

#ifdef TARGET_PC
    {
        /* PC frame pacing can run this actor faster than 60 Hz; keep texture scroll in 60 Hz units. */
        const int step = (int)((5.0f * (f32)game->graph->dt_num_60fps_frames * 256.0f) + 0.5f);

        window->tree_scroll_subtexels += step;
        window->TreeScrollx += window->tree_scroll_subtexels >> 8;
        window->tree_scroll_subtexels &= 0xFF;
    }
#else
    window->TreeScrollx += 5;
#endif
    add_calc(&window->xlu_alpha, aTW_GetNowAlpha(), window->scroll_speed, 50.0f, 1.0f);
    if ((Common_Get(time.now_sec) < 14400) || (Common_Get(time.now_sec) >= 72000)) {
        alpha = 0.0f;
    } else if (Common_Get(time.now_sec) >= 43200) {
        alpha = 160.0f + (-160.0f * ((f32)(Common_Get(time.now_sec) - 43200) / 28800.0f));
    } else {
        alpha = 160.0f * ((f32)(Common_Get(time.now_sec) - 14400) / 28800.0f);
    }
    add_calc(&window->lod_factor, alpha, 0.3f, 50.0f, 1.0f);
}

static int aTrainWindow_OperateScrollLimit(int a, int b, int c) {
    b >>= 1;
    if (b != 0) {
        if (b > 0) {
            if (a + b > c) {
                return c;
            }
            return a + b;
        }
        if (b >= 0) {
            return a;
        }
        if (a + b < c) {
            return c;
        }
        return a + b;
    }
    return a;
}

static Gfx* aTrainWindow_TileScroll(u32* x, u32* y, int xamt, int yamt, int xend, int yend, int width, int height,
                                    GRAPH** graph) {

    *x = aTrainWindow_OperateScrollLimit(*x, xamt, xend);
    *y = aTrainWindow_OperateScrollLimit(*y, yamt, yend);

    return tex_scroll2(*graph, *x, *y, width, height);
}

static Gfx* aTrainWindow_TileScroll2(u32* x1, u32* y1, int x1amt, int y1amt, int x1end, int y1end, int width1,
                                     int height1, u32* x2, u32* y2, int x2amt, int y2amt, int x2end, int y2end,
                                     int width2, int height2, GRAPH** graph) {

    *x1 = aTrainWindow_OperateScrollLimit(*x1, x1amt, x1end);
    *y1 = aTrainWindow_OperateScrollLimit(*y1, y1amt, y1end);
    *x2 = aTrainWindow_OperateScrollLimit(*x2, x2amt, x2end);
    *y2 = aTrainWindow_OperateScrollLimit(*y2, y2amt, y2end);

    return two_tex_scroll(*graph, 0, *x1, *y1, width1, height1, 1, *x2, *y2, width2, height2);
}

static int aTrainWindow_DrawGoneOutTunnel(ACTOR* actor, GAME* game) {
    TRAIN_WINDOW_ACTOR* window = (TRAIN_WINDOW_ACTOR*)actor;

    GRAPH** graph = &game->graph;
    Gfx* ssc;
    Gfx* tsc;

    ssc = aTrainWindow_TileScroll(&window->Single_Scrollx, &window->Single_Scrolly, 0, 0, 1000, 0, 64, 32, graph);
    tsc = aTrainWindow_TileScroll2(&window->Two_Scrollx1, &window->Two_Scrolly1, 0, 0, 1000, 0, 64, 8,
                                   &window->Two_Scrollx2, &window->Two_Scrolly2, 0, 0, 0, 0, 16, 16, graph);

    if ((ssc == NULL) || (tsc == NULL)) {
        return 0;
    } else {
        OPEN_DISP(*graph);

        gSPSegment(NOW_POLY_OPA_DISP++, 11, ssc);
        gSPSegment(NOW_POLY_XLU_DISP++, 11, ssc);

        gSPSegment(NOW_POLY_OPA_DISP++, 12, tsc);
        gSPSegment(NOW_POLY_XLU_DISP++, 12, tsc);

        CLOSE_DISP(*graph);

        return 1;
    }
}

static int aTrainWindow_DrawGoingOutTunnel(ACTOR* actor, GAME* game) {
    TRAIN_WINDOW_ACTOR* window = (TRAIN_WINDOW_ACTOR*)actor;

    Gfx* tsc;
    Gfx* ssc;
    GRAPH** graph = &game->graph;

    ssc = aTrainWindow_TileScroll(&window->Single_Scrollx, &window->Single_Scrolly, 30, 0, 1000, 0, 64, 32, graph);
    tsc = aTrainWindow_TileScroll2(&window->Two_Scrollx1, &window->Two_Scrolly1, 30, 0, 1000, 0, 64, 8,
                                   &window->Two_Scrollx2, &window->Two_Scrolly2, 0, 0, 0, 0, 16, 16, graph);

    if ((ssc == NULL) || (tsc == NULL)) {
        return 0;
    } else {
        OPEN_DISP(*graph);

        gSPSegment(NOW_POLY_OPA_DISP++, 11, ssc);
        gSPSegment(NOW_POLY_XLU_DISP++, 11, ssc);

        gSPSegment(NOW_POLY_OPA_DISP++, 12, tsc);
        gSPSegment(NOW_POLY_XLU_DISP++, 12, tsc);

        CLOSE_DISP(*graph);

        if (((int)window->Single_Scrollx == 1000) && ((int)window->Two_Scrollx1 == 1000)) {
            window->draw_type = aTrainWindow_DrawGoneOutTunnel;
            window->pallete_id = aTrainWindow_GetTreePalletIdx();
            window->current_pallete = aTrainWindow_tree_pal_table[window->pallete_id];
        }

        return 1;
    }
}

static int aTrainWindow_NoDraw(ACTOR* actor, GAME* game) {
    TRAIN_WINDOW_ACTOR* window = (TRAIN_WINDOW_ACTOR*)actor;
    window->draw_type = aTrainWindow_DrawInTunnel;
    return 0;
}

static int aTrainWindow_DrawInTunnel(ACTOR* actor, GAME* game) {
    TRAIN_WINDOW_ACTOR* window = (TRAIN_WINDOW_ACTOR*)actor;

    Gfx* tsc;
    Gfx* ssc;
    GRAPH** graph = &game->graph;

    ssc = aTrainWindow_TileScroll(&window->Single_Scrollx, &window->Single_Scrolly, 0, 0, 1000, 0, 64, 32, graph);
    tsc = aTrainWindow_TileScroll2(&window->Two_Scrollx1, &window->Two_Scrolly1, 0, 0, 1000, 0, 64, 8,
                                   &window->Two_Scrollx2, &window->Two_Scrolly2, 0, 0, 0, 0, 16, 16, graph);

    if ((ssc == NULL) || (tsc == NULL)) {
        return 0;
    } else {
        OPEN_DISP(*graph);

        gSPSegment(NOW_POLY_OPA_DISP++, 11, ssc);
        gSPSegment(NOW_POLY_XLU_DISP++, 11, ssc);

        gSPSegment(NOW_POLY_OPA_DISP++, 12, tsc);
        gSPSegment(NOW_POLY_XLU_DISP++, 12, tsc);

        CLOSE_DISP(*graph);

        if (Common_Get(sunlight_flag) != 0) {
            window->pallete_id = aTrainWindow_GetTreePalletIdx();
            window->current_pallete = aTrainWindow_tree_pal_table[window->pallete_id];
            window->draw_type = aTrainWindow_DrawGoingOutTunnel;
        }
        return 1;
    }
}

static void aTrainWindow_SetLightPrimColorDetail(GAME* game, u32 r, u32 g, u32 b, int l, int poly_a, int xlu_a) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    int i;
    int current_color;
    u8 color[3];
    GRAPH* graph;

    for (i = 0; i < 3; i++) {
        current_color = play->global_light.ambientColor[i] + play->kankyo.base_light.sun_color[i];
        switch (i) {
            case 0:
                current_color += r;
                break;
            case 1:
                current_color += g;
                break;
            case 2:
                current_color += b;
                break;
        }
        if (current_color < 0) {
            current_color = 0;
        } else if (current_color >= 256) {
            current_color = 255;
        }
        color[i] = current_color;
    }

    if (l < 0) {
        l = 0;
    } else if (l > 255) {
        l = 255;
    }
    if (poly_a < 0) {
        poly_a = 0;
    } else if (poly_a > 255) {
        poly_a = 255;
    }
    if (xlu_a < 0) {
        xlu_a = 0;
    } else if (xlu_a > 255) {
        xlu_a = 255;
    }

    graph = play->game.graph;

    OPEN_DISP(graph);
    gDPSetPrimColor(NOW_POLY_OPA_DISP++, 0, l, color[0], color[1], color[2], poly_a);
    gDPSetPrimColor(NOW_POLY_XLU_DISP++, 0, l, color[0], color[1], color[2], xlu_a);
    CLOSE_DISP(graph);
}

static void aTrainWindow_SetTreeTextureScroll(ACTOR* actor, GAME* game) {
    TRAIN_WINDOW_ACTOR* window = (TRAIN_WINDOW_ACTOR*)actor;
    Gfx* tree;

    GRAPH** graph = &game->graph;

    tree = tex_scroll2(*graph, window->TreeScrollx, window->TreeScrolly, 128, 32);

    OPEN_DISP(*graph);

    gSPSegment(NOW_POLY_OPA_DISP++, 8, tree);
    gSPSegment(NOW_POLY_XLU_DISP++, 8, tree);

    CLOSE_DISP(*graph);
}

static void Train_Window_Actor_draw(ACTOR* actor, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    TRAIN_WINDOW_ACTOR* window = (TRAIN_WINDOW_ACTOR*)actor;

    GRAPH* graph = game->graph;
    Matrix_translate(0.0f, 0.0f, 0.0f, MTX_LOAD);
    Matrix_scale(0.05f, 0.05f, 0.05f, MTX_MULT);

    OPEN_DISP(graph);

    gSPMatrix(NOW_POLY_OPA_DISP++, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPMatrix(NOW_POLY_XLU_DISP++, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    _texture_z_light_fog_prim(game->graph);
    _texture_z_light_fog_prim_xlu(game->graph);

    if (window->draw_type(actor, game) != 0) {
        aTrainWindow_SetLightPrimColorDetail(game, 0, 0, 0, 127, 255, (u8)window->xlu_alpha);
        gSPSegment(NOW_POLY_XLU_DISP++, 10, window->current_pallete);
        Evw_Anime_Set(play, &aTrainWindow_evw_anime_data);
        aTrainWindow_SetLightPrimColorDetail(game, 0, 0, 0, 43, 255, window->xlu_alpha);
        gSPDisplayList(NOW_POLY_OPA_DISP++, rom_train_out_tunnel_model);
        aTrainWindow_SetLightPrimColorDetail(game, 0, 0, 0, 127, 255, window->xlu_alpha);
        gSPDisplayList(NOW_POLY_OPA_DISP++, rom_train_out_bgsky_model);
        aTrainWindow_SetLightPrimColorDetail(game, 0, 0, 0, 127, 255, window->xlu_alpha);
        gSPDisplayList(NOW_POLY_XLU_DISP++, rom_train_out_bgcloud_modelT);
        aTrainWindow_SetTreeTextureScroll(actor, game);
        aTrainWindow_SetLightPrimColorDetail(
            game, GETREG(CRV, CRV_DEBUG_RED_VALUE) - 80, GETREG(CRV, CRV_DEBUG_GREEN_VALUE) - 70,
            GETREG(CRV, CRV_DEBUG_BLUE_VALUE) - 160, GETREG(CRV, CRV_DEBUG_LOD_VALUE) + 27, 255, window->xlu_alpha);
        gSPDisplayList(NOW_POLY_XLU_DISP++, rom_train_out_bgtree_modelT);
        aTrainWindow_SetLightPrimColorDetail(game, 0, 0, 0, window->lod_factor, 255, window->xlu_alpha);
        gSPDisplayList(NOW_POLY_XLU_DISP++, rom_train_out_shineglass_modelT);
    }
    CLOSE_DISP(graph);
}
