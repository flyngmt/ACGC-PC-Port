#include "ac_field_draw.h"

#include "audio.h"
#include "m_debug.h"
#include "m_field_info.h"
#include "m_player_lib.h"
#include "m_random_field.h"
#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"

static void Bg_Draw_Actor_ct(ACTOR* actorx, GAME* game);
static void Bg_Draw_Actor_dt(ACTOR* actorx, GAME* game);
static void Bg_Draw_Actor_move(ACTOR* actorx, GAME* game);
static void Bg_Draw_Actor_draw(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Field_Draw_Profile = {
    mAc_PROFILE_FIELD_DRAW,
    ACTOR_PART_FG,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(FIELD_DRAW_ACTOR),
    &Bg_Draw_Actor_ct,
    &Bg_Draw_Actor_dt,
    &Bg_Draw_Actor_move,
    &Bg_Draw_Actor_draw,
    NULL,
};

static void aFD_MakeMarinScrollInfo(ACTOR* actorx, GAME* game);

enum {
    aFD_SEARCH_FULL,
    aFD_SEARCH_CURRENT,
    aFD_SEARCH_ROW,

    aFD_SEARCH_NUM
};

typedef struct {
    int sound_source_no;
    int bx;
    int bz;
    f32 dist;
} aFD_ongen_info_c;

typedef struct {
    int sound_source_no;
    int bx;
    int bz;
} aFD_ongen_info2_c;

typedef struct {
    s16 offset_x;
    s16 offset_z;
} aFD_offset_c;

/*
  4 3 5
  1 0 2
  7 6 8
*/
static aFD_offset_c aFD_block_offset_table[] = {
    { 0, 0 },   // current
    { -1, 0 },  // left
    { 1, 0 },   // right
    { 0, -1 },  // top
    { -1, -1 }, // top-left
    { 1, -1 },  // top-right
    { 0, 1 },   // bot
    { -1, 1 },  // bot-left
    { 1, 1 },   // bot-right
};

static Gfx* aFD_MakeEnvSetDisplayList(u8 r, u8 g, u8 b, u8 a, GAME* game) {
    Gfx* gfx = GRAPH_ALLOC_TYPE(game->graph, Gfx, 2);

    if (gfx != NULL) {
        gDPSetEnvColor(gfx + 0, r, g, b, a);
        gSPEndDisplayList(gfx + 1);
        return gfx;
    }

    return NULL;
}

static int aFD_OperateWaterSound(xyz_t* center_pos, ACTOR* actorx, s16 ongen_type, u8 se_no, f32 ofs_x, f32 ofs_z,
                                 int search_type) {
    static aFD_ongen_info_c dist_info[9 * mFM_SOUND_SOURCE_NUM];
    static int ongen_block_count_table[aFD_SEARCH_NUM] = { 9, 1, 3 };
    int res = FALSE;
    int search_clamped = search_type >= 0 && search_type < aFD_SEARCH_NUM ? search_type : aFD_SEARCH_FULL;
    int ongen_block_count = ongen_block_count_table[search_clamped];
    int i;
    int j;
    int source_num = 0;
    aFD_ongen_info2_c ongen_info[2] = { { -1, 0, 0 }, { -1, 0, 0 } };
    int bx;
    int bz;
    int search_bx;
    int search_bz;
    f32 dx;
    f32 dz;

    if (mFI_Wpos2BlockNum(&bx, &bz, *center_pos)) {
        for (i = 0; i < ongen_block_count; i++) {
            int search_bx = bx + aFD_block_offset_table[i].offset_x;
            int search_bz = bz + aFD_block_offset_table[i].offset_z;
            mFM_bg_sound_source_c* source = mFI_GetSoundSourcePBlockNum(search_bx, search_bz);

            if (source != NULL) {
                for (j = 0; j < mFM_SOUND_SOURCE_NUM; j++) {
                    if (source->kind == ongen_type) {
                        aFD_ongen_info_c* info = &dist_info[source_num];
                        f32 dx = center_pos->x - source->pos.x;
                        f32 dz = center_pos->z - source->pos.z;

                        source_num++;
                        info->sound_source_no = j;
                        info->bx = search_bx;
                        info->bz = search_bz;
                        info->dist = SQ(dx) + SQ(dz);
                    }

                    source++;
                }
            }
        }

        if (source_num != 0) {
            int i;
            f32 closest_dist = 10000000.0f;
            int closest_idx = -1;

            /* Find the closest sound */
            for (i = 0; i < source_num; i++) {
                if (dist_info[i].dist < closest_dist) {
                    ongen_info[0].sound_source_no = dist_info[i].sound_source_no;
                    ongen_info[0].bx = dist_info[i].bx;
                    ongen_info[0].bz = dist_info[i].bz;

                    closest_idx = i;
                    closest_dist = dist_info[i].dist;
                }
            }

            /* Find the second closest sound (if any) */
            closest_dist = 10000000.0f;
            for (i = 0; i < source_num; i++) {
                if (i != closest_idx) {
                    if (dist_info[i].dist < closest_dist) {
                        ongen_info[1].sound_source_no = dist_info[i].sound_source_no;
                        ongen_info[1].bx = dist_info[i].bx;
                        ongen_info[1].bz = dist_info[i].bz;

                        closest_dist = dist_info[i].dist;
                    }
                }
            }

            /* Start playing the sounds */
            for (i = 0; i < ARRAY_COUNT(ongen_info); i++) {
                aFD_ongen_info2_c* info = &ongen_info[i];

                if (info->sound_source_no != -1) {
                    uintptr_t ongen_id = (uintptr_t)actorx + (mFI_GetBlockXMax() * info->bz + info->bx) * mFM_SOUND_SOURCE_NUM +
                                   info->sound_source_no;
                    mFM_bg_sound_source_c* source = mFI_GetSoundSourcePBlockNum(info->bx, info->bz);

                    if (source != NULL) {
                        xyz_t ongen_pos = source[info->sound_source_no].pos;

                        ongen_pos.x += ofs_x;
                        ongen_pos.z += ofs_z;
                        ongen_pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos(source[info->sound_source_no].pos, 0.0f) + 40.0f;
                        sAdo_OngenPos(ongen_id, se_no, &ongen_pos);
                        res = TRUE;
                    }
                }
            }
        }
    }

    return res;
}

static f32 aFD_position_offset = 0.0f;

static void aFD_SetActorPosition(ACTOR* actorx, GAME_PLAY* play) {
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR(play);

    actorx->world.position = player->actor_class.world.position;
    actorx->world.position.y += aFD_position_offset;
}

static void aFD_PrepareFieldDraw(ACTOR* actorx, GAME* game) {
    /*
      6 7 8
      3 4 5
      0 1 2
    */
    static aFD_offset_c draw_block_offset_table[] = {
        { -1, 1 },  // bot-left
        { 0, 1 },   // bot
        { 1, 1 },   // bot-right
        { -1, 0 },  // left
        { 0, 0 },   // current
        { 1, 0 },   // right
        { -1, -1 }, // top-left
        { 0, -1 },  // top
        { 1, -1 },  // top-right
    };

    GAME_PLAY* play = (GAME_PLAY*)game;
    FIELD_DRAW_ACTOR* field_draw = (FIELD_DRAW_ACTOR*)actorx;
    aFD_block_c* block = field_draw->block;
    mFM_field_draw_info_c* draw_info = mFI_BGDisplayListTop();
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR(play);
    int bx;
    int bz;
    int i;

    mFI_Wpos2BlockNum(&bx, &bz, player->actor_class.world.position);
    aFD_SetActorPosition(actorx, play);

    for (i = 0; i < aFD_BLOCK_DRAW_NUM; i++) {
        block->bx = bx + draw_block_offset_table[i].offset_x;
        block->bz = bz + draw_block_offset_table[i].offset_z;
        mFI_BkNum2WposXZ(&block->wpos.x, &block->wpos.z, block->bx, block->bz);
        block->wpos.y = mFI_BkNum2BaseHeight(block->bx, block->bz);
        block->exist = TRUE;
        block++;
    }

    aFD_MakeMarinScrollInfo(actorx, game);
}

static void aFD_SetPositionOffset(f32 ofs) {
    aFD_position_offset = ofs;
}

static void aFD_SetDefaultPositionOffset() {
    aFD_SetPositionOffset(1000.0f);
}

static void Bg_Draw_Actor_ct(ACTOR* actorx, GAME* game) {
    aFD_PrepareFieldDraw(actorx, game);
    aFD_SetDefaultPositionOffset();
}

static void Bg_Draw_Actor_dt(ACTOR* actorx, GAME* game) {
}

static void Bg_Draw_Actor_move(ACTOR* actorx, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR(play);
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    int bx;
    int bz;
    int pond_x;
    int pond_z;

    aFD_PrepareFieldDraw(actorx, game);

    if (mFI_Wpos2BlockNum(&bx, &bz, player->actor_class.world.position)) {
        if ((mFI_BkNum2BlockKind(bx, bz) & mRF_BLOCKKIND_MARINE) != 0) {
            aFD_OperateWaterSound(&player->actor_class.world.position, actorx, 2, 28, 0.0f, 175.0f, aFD_SEARCH_ROW);
        } else {
            aFD_OperateWaterSound(&player->actor_class.world.position, actorx, 1, 11, 0.0f, 0.0f, aFD_SEARCH_FULL);
        }

        if (mRF_SearchPond(&pond_x, &pond_z, bx, bz)) {
            xyz_t frog_se_pos;
            xyz_t pond_pos;

            /* Play the frog sound effect */
            if (rtc_time->month >= lbRTC_MAY && rtc_time->month <= lbRTC_AUGUST &&
                ((rtc_time->hour >= 18 && rtc_time->hour <= 21) || (rtc_time->hour >= 4 && rtc_time->hour <= 6))) {
                frog_se_pos.x = mFI_UNIT_BASE_SIZE_F + (f32)pond_x * mFI_UNIT_BASE_SIZE_F;
                frog_se_pos.y = 0.0f;
                frog_se_pos.z = mFI_UNIT_BASE_SIZE_F + (f32)pond_z * mFI_UNIT_BASE_SIZE_F;
                frog_se_pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos(frog_se_pos, 0.0f);
                sAdo_OngenPos((uintptr_t)&Bg_Draw_Actor_move, 0xA1, &frog_se_pos);
            }

            /* Pond sound effect */
            pond_pos.x = mFI_UNIT_BASE_SIZE_F * 0.5f + (f32)pond_x * mFI_UNIT_BASE_SIZE_F;
            pond_pos.y = 0.0f;
            pond_pos.z = mFI_UNIT_BASE_SIZE_F * 0.5f + (f32)pond_z * mFI_UNIT_BASE_SIZE_F;
            pond_pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos(pond_pos, 0.0f);
            sAdo_OngenPos((uintptr_t)&Bg_Draw_Actor_ct, 0x16, &pond_pos);
        }
    }

    if (GETREG(CRV, 39)) {
        int i;

        for (i = 0; i < 4; i++) {
            // ??
        }

        SETREG(CRV, 39, 0);
    }
}

/* Culling box which is aproximately 128:25 (5.12:1) on the xz plane */
/* NOTE: these vertices are only included because they are not used in any art asset */
static Vtx aFD_culling_vtx[] ATTRIBUTE_ALIGN(32) = {
    // clang-format off
    {     0,    0,     0,  0,  0, 0,  0, 0, 0, 0 },
    {     0,    0, 10240,  0,  0, 0,  0, 0, 0, 0 },
    { 10240,    0, 10240,  0,  0, 0,  0, 0, 0, 0 },
    { 10240,    0,     0,  0,  0, 0,  0, 0, 0, 0 },
    {     0, 2000,     0,  0,  0, 0,  0, 0, 0, 0 },
    {     0, 2000, 10240,  0,  0, 0,  0, 0, 0, 0 },
    { 10240, 2000, 10240,  0,  0, 0,  0, 0, 0, 0 },
    { 10240, 2000,     0,  0,  0, 0,  0, 0, 0, 0 },
    // clang-format on
};

static Gfx aFD_cull_set_gfx[] ATTRIBUTE_ALIGN(32) = {
    gsSPClearGeometryMode(G_FOG | G_LIGHTING),
    gsSPVertex(&aFD_culling_vtx[0], 8, 0),
    gsSPCullDisplayList(0, 7),
    gsSPSetGeometryMode(G_FOG | G_LIGHTING),
    gsSPEndDisplayList(),
};

static Gfx aFD_cull_set_model[] ATTRIBUTE_ALIGN(32) = {
    gsSPDisplayList(aFD_cull_set_gfx),
    gsSPDisplayList(SEGMENT_ADDR(G_MWO_SEGMENT_A, 0)), /* Dynamic segment 0x0A */
    gsSPEndDisplayList(),
};

static EVW_ANIME_SCROLL aFD_texture_scroll2_data[2] = { { 1, -1, 32, 32 }, { -1, -2, 32, 32 } };

static EVW_ANIME_DATA aFD_evw_data = { -4, EVW_ANIME_TYPE_SCROLL2, aFD_texture_scroll2_data };

static void aFD_SetRiverFlow(GAME_PLAY* play) {
    Evw_Anime_Set(play, &aFD_evw_data);
}

static void aFD_SetViewerData(EVW_ANIME_DATA* data, GAME_PLAY* play) {
    if (data != NULL) {
        Evw_Anime_Set(play, data);
    } else {
        aFD_SetRiverFlow(play);
    }
}

static int aFD_SetBeachColorOpaSegment(ACTOR* actorx, GAME* game, int bx, int bz) {
    FIELD_DRAW_ACTOR* field_draw = (FIELD_DRAW_ACTOR*)actorx;
    aFD_marin_info_c* marin_info = &field_draw->marin_info;

    if ((mFI_BkNum2BlockKind(bx, bz) & mRF_BLOCKKIND_MARINE) != 0) {
        Gfx* gfx = aFD_MakeEnvSetDisplayList(marin_info->beach_env_color.r, marin_info->beach_env_color.g,
                                             marin_info->beach_env_color.b, marin_info->beach_env_color.a, game);

        if (gfx == NULL) {
            return FALSE;
        }

        OPEN_DISP(game->graph);

        gSPSegment(NEXT_BG_OPA_DISP, G_MWO_SEGMENT_C, gfx);

        CLOSE_DISP(game->graph);
    }

    return TRUE;
}

static int aFD_SetMarinScrollXluSegment(ACTOR* actorx, GAME* game, int bx, int bz) {
    FIELD_DRAW_ACTOR* field_draw = (FIELD_DRAW_ACTOR*)actorx;
    aFD_marin_info_c* marin_info = &field_draw->marin_info;

    if ((mFI_BkNum2BlockKind(bx, bz) & mRF_BLOCKKIND_MARINE) != 0) {
        Gfx* gfx0 = two_tex_scroll_dolphin(game->graph, 0, 0, marin_info->tile0_scroll << 1, 32, 32, 1, 0,
                                           marin_info->tile1_scroll << 1, 32, 64);
        Gfx* gfx1 = two_tex_scroll_dolphin(game->graph, 0, 0, marin_info->tile0_scroll << 1, 32, 32, 1, 0,
                                           marin_info->tile1_scroll << 1, 32, 32);

        if (gfx0 == NULL || gfx1 == NULL) {
            return FALSE;
        }

        OPEN_DISP(game->graph);

        gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_B, gfx0);
        gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_D, gfx1);

        CLOSE_DISP(game->graph);
    }

    return TRUE;
}

static void aFD_DrawBg(Gfx* gfx, int exists, GAME* game) {
    if (gfx != NULL) {
        OPEN_DISP(game->graph);

        gSPSegment(NEXT_BG_OPA_DISP, G_MWO_SEGMENT_A, gfx); /* Bg display list is called in between culling microcode */
        gSPDisplayList(NEXT_BG_OPA_DISP, aFD_cull_set_model);

        CLOSE_DISP(game->graph);
    }
}

static void aFD_DrawXluBg(Gfx* gfx, int exists, GAME* game) {
    if (gfx != NULL) {
        OPEN_DISP(game->graph);

        if (mFI_GetFieldId() == mFI_FIELD_ROOM_BUGGY) {
            GAME_PLAY* play = (GAME_PLAY*)game;
            static xyz_t ball = { 160.0f, 70.0f, 180.0f }; // Katrina's crystal ball highlight

            Setpos_HiliteReflect_xlu_init(&ball, play);
        }

        gSPDisplayList(NEXT_POLY_XLU_DISP, gfx);

        CLOSE_DISP(game->graph);
    }
}

typedef void (*aFD_DRAW_PROC)(GAME* game);

static void aFD_DrawBlock(aFD_block_c* block, ACTOR* actorx, GAME* game) {
    static aFD_DRAW_PROC draw_proc[] = { (aFD_DRAW_PROC)&none_proc1, &Global_kankyo_set_room_prim,
                                         &Global_kankyo_set_room_prim, (aFD_DRAW_PROC)&none_proc1 };

    int block_type = mFI_BkNum2BlockType(block->bx, block->bz);
    s8 anime_frame_count;
    EVW_ANIME_DATA* anime_data;
    u32 exist = block->exist;
    Gfx* opa_gfx;
    Gfx* xlu_gfx;
    GAME_PLAY* play = (GAME_PLAY*)game;


    if (exist != FALSE) {
        opa_gfx = mFI_GetBGDisplayListRom(block->bx, block->bz);
        xlu_gfx = mFI_GetBGDisplayListRom_XLU(block->bx, block->bz);
        anime_data = mFI_GetBGTexAnimInfo(&anime_frame_count, block->bx, block->bz);

        Matrix_translate(block->wpos.x, block->wpos.y, block->wpos.z, MTX_LOAD);
        Matrix_scale(0.0625f, 0.0625f, 0.0625f, MTX_MULT);
        _texture_z_light_fog_prim_xlu(game->graph);
        _texture_z_light_fog_prim_bg(game->graph);

        OPEN_DISP(game->graph);

        gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPMatrix(NEXT_BG_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        CLOSE_DISP(game->graph);

        aFD_SetViewerData(anime_data, play);
        (*draw_proc[Common_Get(field_draw_type)])(game);

        if (aFD_SetBeachColorOpaSegment(actorx, game, block->bx, block->bz)) {
            u32 kind = mFI_BkNum2BlockKind(block->bx, block->bz);

            switch (GETREG(MYKREG, 77)) {
                case 0: {
                    // Draw all BG
                    aFD_DrawBg(opa_gfx, exist, game);
                    break;
                }

                case 1: {
                    // Do not draw BG unless we're in an island block
                    if ((kind & mRF_BLOCKKIND_ISLAND) == 0) {
                        aFD_DrawBg(opa_gfx, exist, game);
                    }

                    break;
                }

                case 2: {
                    // Do not draw BG at all
                    break;
                }

                default: {
                    // Draw all BG
                    aFD_DrawBg(opa_gfx, exist, game);
                    break;
                }
            }
        }

        if (aFD_SetMarinScrollXluSegment(actorx, game, block->bx, block->bz)) {
            if (GETREG(MYKREG, 77) != 3) {
                aFD_DrawXluBg(xlu_gfx, exist, game);
            }
        }
    }
}

static void aFD_MakeMarinScrollInfo(ACTOR* actorx, GAME* game) {
    FIELD_DRAW_ACTOR* field_draw = (FIELD_DRAW_ACTOR*)actorx;
    aFD_marin_info_c* marin_info = &field_draw->marin_info;
    GAME_PLAY* play = (GAME_PLAY*)game;

    int frame = play->game_frame % 300;
    f32 frame_f = (f32)frame;
    f32 wave_radian = (frame_f / 300.0f) * F_PI * 2.0f;
    f32 wave_cos = cosf_table(wave_radian);
    f32 beach_cos = cosf_table((wave_radian - 1.2f) + (f32)GETREG(MYKREG, 53) * 0.01f);

    marin_info->frame = frame;
    marin_info->tile0_scroll = (int)((f32)play->game_frame * -0.42666667f) - 7;
    marin_info->tile1_scroll = (int)(wave_cos * -32.0f - -32.0f);

    mCoBG_WaveCos2BgCheck(wave_cos);

    marin_info->beach_env_color.r = (u8)(int)(144.0f + ((beach_cos * -21.0f) + 21.0f));
    marin_info->beach_env_color.g = (u8)(int)(128.0f + ((beach_cos * -18.0f) + 18.0f));
    marin_info->beach_env_color.b = (u8)(int)(96.0f + ((beach_cos * -14.0f) + 14.0f));
    marin_info->beach_env_color.a = (u8)255;
}

static void Bg_Draw_Actor_draw(ACTOR* actorx, GAME* game) {
    FIELD_DRAW_ACTOR* field_draw = (FIELD_DRAW_ACTOR*)actorx;
    aFD_block_c* block = field_draw->block;
    int i;

    OPEN_DISP(game->graph);

    gDPSetTexEdgeAlpha(NEXT_BG_OPA_DISP, 144);
    gDPSetTexEdgeAlpha(NEXT_POLY_XLU_DISP, 144);
    gDPSetTextureAdjustMode(NEXT_BG_OPA_DISP, G_TA_DOLPHIN);
    gDPSetTextureAdjustMode(NEXT_POLY_XLU_DISP, G_TA_DOLPHIN);

    CLOSE_DISP(game->graph);

    for (i = 0; i < aFD_BLOCK_DRAW_NUM; i++) {
        aFD_DrawBlock(block, actorx, game);
        block++;
    }

    OPEN_DISP(game->graph);

    gDPSetTextureAdjustMode(NEXT_BG_OPA_DISP, G_TA_N64);
    gDPSetTextureAdjustMode(NEXT_POLY_XLU_DISP, G_TA_N64);

    CLOSE_DISP(game->graph);
}
