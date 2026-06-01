#include "m_field_make.h"

#include "m_island.h"
#include "m_name_table.h"
#include "m_common_data.h"
#include "m_room_type.h"
#include "m_scene_table.h"
#include "m_random_field.h"
#include "m_soncho.h"
#include "jsyswrap.h"
#include "m_malloc.h"
#include "libultra/libultra.h"
#include "m_bg_tex.h"
#include "m_house.h"
#include "m_bgm.h"
#ifdef TARGET_PC
#include "pc_bswap.h"
/* Byte-swap all u16 fields in FG data loaded from big-endian ARAM. */
static void mFM_ByteSwapFGData(mFM_fg_data_c* data, int count) {
    int ei, zi, xi;
    for (ei = 0; ei < count; ei++) {
        data[ei].fg_id = pc_bswap16(data[ei].fg_id);
        for (zi = 0; zi < UT_Z_NUM; zi++) {
            for (xi = 0; xi < UT_X_NUM; xi++) {
                data[ei].items[zi][xi] = pc_bswap16(data[ei].items[zi][xi]);
            }
        }
    }
}
#endif

// clang-format off
static mActor_name_t l_fg_outer_fill[UT_Z_NUM * UT_X_NUM] = {
    RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO,
    RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO,
    RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO,
    RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO,
    RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO,
    RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO,
    RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO,
    RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO,
    RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO,
    RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO,
    RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO,
    RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO,
    RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO,
    RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO,
    RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO,
    RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO, RSV_NO,
};
// clang-format on

// clang-format off
static mActor_name_t l_title_demo_fg[(BLOCK_Z_NUM - 2) * BLOCK_X_NUM] = {
    0x00CB, 0x00CB, 0x00CB, 0x00CB, 0x00CB, 0x00CB, 0x00CB,
    0x00CB, 0x00DD, 0x00AB, 0x00CC, 0x00E5, 0x002E, 0x00CB,
    0x00CB, 0x0174, 0x0030, 0x0069, 0x0088, 0x017C, 0x00CB,
    0x00CB, 0x0055, 0x0176, 0x0046, 0x0179, 0x0045, 0x00CB,
    0x00CB, 0x0175, 0x003F, 0x0029, 0x017A, 0x017D, 0x00CB,
    0x00CB, 0x006A, 0x00AC, 0x0178, 0x0068, 0x017E, 0x00CB,
    0x00CB, 0x0061, 0x0177, 0x0062, 0x017B, 0x0064, 0x00CB,
    0x00CB, 0x00CB, 0x00CB, 0x00CB, 0x00CB, 0x00CB, 0x00CB,
};
// clang-format on

typedef struct police_pos_s {
    int bx;
    int bz;
    int ut_x;
    int ut_z;
} mFM_police_pos_c;

static mFM_police_pos_c l_mfm_police_pos = { 0, 0, 0, 0 };

int l_bg_disp_num = 0;
int l_bg_disp_size = 0;
static u16 mFM_pal_area[11][16] ATTRIBUTE_ALIGN(32);
mFM_fdinfo_c* g_fdinfo;
static u8 l_block_type[BLOCK_TOTAL_NUM];
static int l_block_kind[BLOCK_TOTAL_NUM];

static void mFM_SortBGData(mFM_bg_data_c** sorted_data_p, mFM_bg_data_c* data, int count) {
    int i;
    mFM_bg_data_c** sorted_data_p_copy = sorted_data_p;

    for (i = 0; i < mFM_BG_ID_MAX; i++) {
        sorted_data_p_copy[0] = NULL;
        sorted_data_p_copy++;
    }

    for (i = 0; i < count; i++) {
        if (data->bg_id <= mFM_BG_ID_MAX) {
            sorted_data_p[data->bg_id] = data;
        }
        data++;
    }
}

static void mFM_SortFGData(mFM_fg_data_c** sorted_data_p, mFM_fg_data_c* data, int count, int list_size,
                           int name_start) {
    int i;
    mFM_fg_data_c** sorted_data_p_copy = sorted_data_p;

    for (i = 0; i < count; i++) {
        sorted_data_p_copy[0] = NULL;
        sorted_data_p_copy++;
    }

    for (i = 0; i < list_size; i++) {
        int fg_idx = data->fg_id - name_start;

        if (fg_idx < 0) {
            fg_idx = 0;
        }

        sorted_data_p[fg_idx] = data;
        data++;
    }
}

static void mFM_BgUtDataSet(mCoBG_Collision_u* collision, u8* keep, mCoBG_Collision_u* data) {
    int ut_x;
    int ut_z;

    for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
        for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
            collision[0] = data[0];
            keep[0] = data[0].data.center;

            collision++;
            data++;
            keep++;
        }
    }
}

static void mFM_FgUtDataSet(mActor_name_t* fg, mActor_name_t* data) {
    int ut_x;
    int ut_z;

// Aus version added NULL checks
#if VERSION >= VER_GAFU01_00
    if (fg == NULL) {
        return;
    }

    if (data == NULL) {
        return;
    }
#endif

    for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
        for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
            fg[0] = data[0];
            fg++;
            data++;
        }
    }
}

static void mFM_SetFgUtPtoSaveData(mFM_block_info_c* block_info, u8 bx_max, u8 bz_max, int* island_block_x) {
    int bz;
    int bx;

    for (bz = 0; bz < bz_max; bz++) {
        for (bx = 0; bx < bx_max; bx++) {
            if (bz > 0 && bz < (bz_max - 1) && bx > 0 && bx < (bx_max - 1)) {
                if (bx == island_block_x[0] && bz == mISL_BLOCK_Z) {
                    block_info->fg_info.items_p = Save_Get(island.fgblock[0][0]).items[0];
                } else if (bx == island_block_x[1] && bz == mISL_BLOCK_Z) {
                    block_info->fg_info.items_p = Save_Get(island.fgblock[0][1]).items[0];
                } else if (bz >= (bz_max - 3)) {
                    block_info->fg_info.items_p = l_fg_outer_fill;
                } else {
                    block_info->fg_info.items_p = Save_Get(fg[bz - 1][bx - 1]).items[0];
                }
            } else {
                block_info->fg_info.items_p = l_fg_outer_fill;
            }

            block_info++;
        }
    }
}

static void mFM_SetFgUtPtoHomeInfo(mFM_block_info_c* block_info, u8 bx_max, u8 bz_max, mActor_name_t house_no,
                                   int floor) {
    int bz;
    int bx;

    for (bz = 0; bz < bz_max; bz++) {
        for (bx = 0; bx < bx_max; bx++) {
            block_info->fg_info.items_p = Save_Get(homes[house_no]).floors[floor].layer_main.items[0];
            block_info++;
        }
    }
}

static void mFM_SetFgUtPtoCottageInfo(mFM_block_info_c* block_info, u8 bx_max, u8 bz_max) {
    int bz;
    int bx;

    for (bz = 0; bz < bz_max; bz++) {
        for (bx = 0; bx < bx_max; bx++) {
            block_info->fg_info.items_p = Save_Get(island).cottage.room.layer_main.items[0];
            block_info++;
        }
    }
}

static void mFM_ChangeFGName(mActor_name_t* fg_name_p, mActor_name_t fg_name, mActor_name_t field_name, int block) {
    mActor_name_t house_owner_name = Common_Get(house_owner_name);

    if (Save_Get(scene_no) == SCENE_COTTAGE_NPC) {
        fg_name_p[0] = Common_Get(island_npclist[0]).house_data.main_layer_id;
    } else if (field_name == mFI_FIELD_NPCROOM0 && ITEM_NAME_GET_TYPE(house_owner_name) == NAME_TYPE_NPC) {
        int npc_idx = mNpc_SearchAnimalinfo(Save_Get(animals), house_owner_name, ANIMAL_NUM_MAX);
        mNpc_NpcList_c* list = Common_GetPointer(npclist[npc_idx]);

        fg_name_p[0] = list->house_data.main_layer_id;
    } else if (mFI_CheckShopFieldName(field_name)) {
        fg_name_p[0] = mSP_GetNowShopFgNum();
    } else if (Save_Get(scene_no) == SCENE_FIELD_TOOL || Save_Get(scene_no) == SCENE_TITLE_DEMO) {
        fg_name_p[0] = l_title_demo_fg[block];
    } else {
        fg_name_p[0] = fg_name;
    }
}

static void mFM_ChangeBGName(mActor_name_t* bg_name_p, mActor_name_t bg_name, mActor_name_t field_name) {
    if (mFI_CheckShopFieldName(field_name)) {
        bg_name_p[0] = mSP_GetNowShopBgNum();
    } else if (mFI_GET_TYPE(field_name) == mFI_FIELD_PLAYER0_ROOM) {
        bg_name_p[0] = mRmTp_GetPlayerRoomCollisionIdx(field_name, bg_name);
    } else {
        bg_name_p[0] = bg_name;
    }
}

static void mFM_SetSoundSource(mFM_bg_sound_source_c* sound_source, mFM_bg_sound_source_data_c* data, int count, int bx,
                               int bz) {
    int i;

    for (i = 0; i != count; i++) {
        sound_source->kind = data->kind;
        sound_source->pos.x = data->ut_x * mFI_UT_WORLDSIZE_X_F;
        sound_source->pos.x += bx * mFI_BK_WORLDSIZE_X_F + mFI_UT_WORLDSIZE_HALF_X_F;
        sound_source->pos.y = 0.0f;
        sound_source->pos.z = data->ut_z * mFI_UT_WORLDSIZE_Z_F;
        sound_source->pos.z += bz * mFI_BK_WORLDSIZE_Z_F + mFI_UT_WORLDSIZE_HALF_Z_F;

        data++;
        sound_source++;
    }
}

static void mFM_SetBG(mFM_bg_info_c* bg_info, mFM_bg_data_c* bg_data, u16 height, u8 type, mActor_name_t bg_name,
                      int block_x, int block_z) {
    bg_info->bg_id.height = height;
    bg_info->bg_id.combination_type = bg_name;
    bg_info->opaque_gfx = bg_data->opaque_gfx;
    bg_info->translucent_gfx = bg_data->translucent_gfx;
    bg_info->animation = bg_data->animation;
    bg_info->animation_count = bg_data->animation_count;
    bg_info->rom_start_addr = bg_data->rom_start_addr;
    bg_info->rom_size = bg_data->rom_end_addr - bg_data->rom_start_addr;
    bg_info->block_type = type;
    bg_info->block_kind = mRF_Type2BlockInfo(type);

    mFM_SetSoundSource(bg_info->sound_source, bg_data->sound_source, mFM_SOUND_SOURCE_NUM, block_x, block_z);
    mFM_BgUtDataSet(bg_info->collision[0], bg_info->keep_h[0], bg_data->collision[0]);
}

static void mFM_SetFG(mFM_fg_info_c* fg_info, mFM_fg_data_c* data, mActor_name_t fg_name) {
    int scene;
    int i;

    fg_info->fg_id = fg_name;
    fg_info->move_actor_bit_data = 0;

    scene = Save_Get(scene_no);

    if (scene != SCENE_FG && scene != SCENE_MY_ROOM_S && scene != SCENE_MY_ROOM_M && scene != SCENE_MY_ROOM_L &&
        scene != SCENE_MY_ROOM_LL1 && scene != SCENE_MY_ROOM_LL2 && scene != SCENE_MY_ROOM_BASEMENT_S &&
        scene != SCENE_MY_ROOM_BASEMENT_M && scene != SCENE_MY_ROOM_BASEMENT_L && scene != SCENE_MY_ROOM_BASEMENT_LL1 &&
        scene != SCENE_COTTAGE_MY) {
        if (scene == SCENE_COTTAGE_NPC) {
            if (mNpc_GetIslandRoomFtrNum() > 0) {
                mFM_FgUtDataSet(fg_info->items_p, mNpc_GetIslandRoomP(Save_Get(island).animal.id.npc_id));
                mNpc_ChangeIslandRoom(fg_info->items_p);
            } else {
                mFM_FgUtDataSet(fg_info->items_p, data->items[0]);
            }

            if (fg_info != NULL && fg_info->items_p != NULL) {
                mActor_name_t* items_p = fg_info->items_p;

                items_p[(8 << 4) | 3] = EXIT_DOOR;
                items_p[(8 << 4) | 4] = EXIT_DOOR;
            }
        } else {
            mFM_FgUtDataSet(fg_info->items_p, data->items[0]);
        }
    }

    for (i = 0; i < mFM_HANIWA_STEP_NUM; i++) {
        fg_info->haniwa_step[i] = data->haniwa_step[i];
    }
}

static void mFM_SetFG2(mActor_name_t* items_p, mFM_fg_data_c** data, mActor_name_t field_name, int name_start) {
    mActor_name_t house_owner_name = Common_Get(house_owner_name);

    if (items_p != NULL && Save_Get(scene_no) == SCENE_COTTAGE_NPC) {
        int idx = mFM_FG2_ID_MAX;

        idx -= name_start;
        if (idx < 0) {
            idx = 0;
        }

        if (data[idx] != NULL) {
            mFM_FgUtDataSet(items_p, data[idx]->items[0]);
        }
    } else {
        if (items_p != NULL && field_name == mFI_FIELD_NPCROOM0 &&
            ITEM_NAME_GET_TYPE(house_owner_name) == NAME_TYPE_NPC) {
            int anm_idx = mNpc_SearchAnimalinfo(Save_Get(animals), house_owner_name, ANIMAL_NUM_MAX);
            mNpc_NpcList_c* npc_list = Common_GetPointer(npclist[anm_idx]);
            int secondary_idx = npc_list->house_data.secondary_layer_id - name_start;

            if (secondary_idx < 0) {
                secondary_idx = 0;
            }

            if (data[secondary_idx] != NULL) {
                mFM_FgUtDataSet(items_p, data[secondary_idx]->items[0]);
            }
        }
    }
}

static void mFM_BlockDataSet(mActor_name_t field_name, mFM_block_info_c* block_info,
                             mFM_combination_c* save_combi_table, mFM_bg_data_c** bg_data_list,
                             mFM_fg_data_c** fg_data_list, mFM_combo_info_c* data_combi_table, int bx_max, int bz_max,
                             int name_start) {
    mFM_combo_info_c* combi;
    mActor_name_t bg_name;
    mActor_name_t fg_name;
    int fg_idx;
    int i;
    int bx = 0;
    int bz = 0;
    int max = bz_max * bx_max;

    for (i = 0; i < max; i++) {
        combi = &data_combi_table[save_combi_table[0].combination_type];

        mFM_ChangeFGName(&fg_name, combi->fg_id, field_name, i);
        mFM_ChangeBGName(&bg_name, combi->bg_id, field_name);

        if (bg_name > mFM_BG_ID_MAX) {
            bg_name = 0;
        }

        if (fg_name > mFM_FG_ID_MAX) {
            fg_name = 0;
        }

        fg_idx = fg_name - name_start;
        if (fg_idx < 0) {
            fg_idx = 0;
        }

        if (bg_data_list[bg_name] != NULL && fg_data_list[fg_idx]) {
            mFM_SetBG(&block_info->bg_info, bg_data_list[bg_name], save_combi_table[0].height, combi->type, bg_name, bx,
                      bz);
            mFM_SetFG(&block_info->fg_info, fg_data_list[fg_idx], fg_name);
        }

        bx++;

        if (bx >= bx_max) {
            bx = 0;
            bz++;
        }

        block_info++;
        save_combi_table++;
    }
}

static void mFM_KeepPolicePos(int bx, int bz, int ut_x, int ut_z) {
    l_mfm_police_pos.bx = bx;
    l_mfm_police_pos.bz = bz;
    l_mfm_police_pos.ut_x = ut_x;
    l_mfm_police_pos.ut_z = ut_z;
}

extern void mFM_GetPolicePos(int* bx, int* bz, int* ut_x, int* ut_z) {
    *bx = l_mfm_police_pos.bx;
    *bz = l_mfm_police_pos.bz;
    *ut_x = l_mfm_police_pos.ut_x;
    *ut_z = l_mfm_police_pos.ut_z;
}

static void mFM_SetMoveActorInfo(mFM_block_info_c* block_info, int bx_max, int bz_max,
                                 mFM_move_actor_data_c* move_actor_data, u32 param_5, u32 param_6) {
    mFM_move_actor_data_c* move_ac_data_p = move_actor_data;

    if (block_info != NULL) {
        for (move_ac_data_p; move_ac_data_p != NULL && move_ac_data_p->name_id != RSV_NO; move_ac_data_p++) {
            int block = -1;
            int ut_x;
            int ut_z;

            ut_x = move_ac_data_p->ut_x;
            ut_z = move_ac_data_p->ut_z;

            if (move_ac_data_p->desired_block_kind == mRF_BLOCKKIND_NONE) {
                block = move_ac_data_p->block_x + move_ac_data_p->block_z * bx_max;
            } else {
                int bx;
                int bz;

                if (mFI_BlockKind2BkNum(&bx, &bz, move_ac_data_p->desired_block_kind) == TRUE) {
                    block = bx + bz * bx_max;

                    switch (move_ac_data_p->name_id) {
                        case SP_NPC_POLICE: {
                            mActor_name_t* items = block_info[block].fg_info.items_p;
                            int i;

                            for (i = 0; i < UT_TOTAL_NUM; i++) {
                                if (items[0] == POLICE_STATION) {
                                    ut_x = i % UT_X_NUM;
                                    ut_z = i / UT_Z_NUM;
                                    ut_x += 2;
                                    mFM_KeepPolicePos(bx, bz, ut_x, ut_z);

                                    break;
                                }

                                items++;
                            }

                            break;
                        }

                        case SP_NPC_SONCHO: {
                            if (mEv_CheckFirstJob() == FALSE ||
                                (mSC_check_ArbeitPlayer() && mSC_LightHouse_travel_check())) {
                                block = -1;
                            }

                            break;
                        }
                    }
                }
            }

            if (block != -1) {
                mFM_move_actor_c* move_actor = block_info[block].fg_info.move_actors;
                int free_idx = mFI_GetMoveActorListIdx(move_actor, mFM_MOVE_ACTOR_NUM, EMPTY_NO);

                if (free_idx != -1) {
                    move_actor[free_idx].name_id = move_ac_data_p->name_id;
                    move_actor[free_idx].ut_x = ut_x;
                    move_actor[free_idx].ut_z = ut_z;
                    move_actor[free_idx].npc_info_idx = move_ac_data_p->npc_info_idx;
                    move_actor[free_idx].arg = move_ac_data_p->arg;
                }
            }
        }
    }
}

static void mFM_SetCombiTable(mFM_combination_c* combi_table, mFM_combination_c* combi_id, u8 bx_max, u8 bz_max) {
    u8 bz;
    u8 bx;

    for (bz = 0; bz < bz_max; bz++) {
        for (bx = 0; bx < bx_max; bx++) {
            combi_table->combination_type = combi_id->combination_type;
            combi_table->height = combi_id->height;

            combi_table++;
            combi_id++;
        }
    }
}

static int mFM_SetBlockInfo(mFM_fdinfo_c* field_info, mFM_combination_c* combi_table) {
    mFM_bg_data_c** sorted_bg_data;
    mFM_fg_data_c** sorted_fg_data;
    mFM_combo_info_c* combi_info_p;
    mFM_bg_data_c* bg_data_p = data_bgd;
    mFM_fg_data_c* fg_data;
    size_t malloc_size;
    u32 aram_addr;
    int fg_count;
    int name_start;
    int file_id;
    u32 align_size;
    int fg_data_entries;
    u32 size;

    if (mFI_GET_TYPE(field_info->field_id) == mFI_FIELD_NPCROOM0) {
        malloc_size = mFM_FG_NPC_NUM * sizeof(mFM_fg_data_c*);
        fg_count = mFM_FG_NPC_NUM;
        name_start = mFM_FG_NPC_START;
        file_id = RESOURCE_FGNPCDATA;
    } else {
        malloc_size = mFM_FG_NUM * sizeof(mFM_fg_data_c*);
        fg_count = mFM_FG_NUM;
        name_start = mFM_FG_START;
        file_id = RESOURCE_FGDATA;
    }

    {
        size = JW_GetResSizeFileNo(file_id);
        align_size = ALIGN_NEXT(size, 32);
        fg_data = (mFM_fg_data_c*)zelda_malloc_align(align_size, 32);
        fg_data_entries = size / sizeof(mFM_fg_data_c);

        _JW_GetResourceAram(JW_GetAramAddress(file_id), (u8*)fg_data, align_size);

#ifdef TARGET_PC
        mFM_ByteSwapFGData(fg_data, fg_data_entries);
#endif

        combi_info_p = data_combi_table;
        sorted_bg_data = (mFM_bg_data_c**)zelda_malloc(mFM_BG_ID_MAX * sizeof(mFM_bg_data_c**));

        if (sorted_bg_data == NULL) {
            return FALSE;
        }

        mFM_SortBGData(sorted_bg_data, bg_data_p, data_bgd_number);
        sorted_fg_data = (mFM_fg_data_c**)zelda_malloc(malloc_size);

        if (sorted_fg_data == NULL) {
            return FALSE; /* @BUG - possible memory leak from the sorted_bg_data malloc */
        }

        mFM_SortFGData(sorted_fg_data, fg_data, fg_count, fg_data_entries, name_start);

        mFM_BlockDataSet(field_info->field_id, field_info->block_info, combi_table, sorted_bg_data, sorted_fg_data,
                         combi_info_p, field_info->block_x_max, field_info->block_z_max, name_start);

        mFM_SetFG2(field_info->fg2_p[0], sorted_fg_data, field_info->field_id, name_start);

        if (mFI_GET_TYPE(field_info->field_id) == mFI_FIELD_NPCROOM0) {
            mNpc_SetNpcFurnitureRandom(sorted_fg_data,
                                       name_start); // select a random furniture item from NPC base furniture layer
        }

// Aus version added NULL checks
#if VERSION >= VER_GAFU01_00
        if (sorted_bg_data != NULL) {
            zelda_free(sorted_bg_data);
        }

        if (sorted_fg_data != NULL) {
            zelda_free(sorted_fg_data);
        }

        if (fg_data != NULL) {
            zelda_free(fg_data);
        }
#else
        zelda_free(sorted_bg_data);
        zelda_free(sorted_fg_data);
        zelda_free(fg_data);
#endif
    }

    return 0;
}

static void mFM_set_pal_p(mFM_field_pal_c* pal) {
    if (pal != NULL) {
        bzero(mFM_pal_area, sizeof(mFM_pal_area));

        pal->earth_pal = mFM_pal_area[0];
        pal->cliff_pal = mFM_pal_area[1];
        pal->bush_pal = mFM_pal_area[2];
        pal->flower0_pal = mFM_pal_area[3];
        pal->flower1_pal = mFM_pal_area[4];
        pal->flower2_pal = mFM_pal_area[5];
        pal->grass_pal = mFM_pal_area[6];
        pal->tree_pal = mFM_pal_area[7];
        pal->cedar_tree_pal = mFM_pal_area[8];
        pal->palm_tree_pal = mFM_pal_area[9];
        pal->golden_tree_pal = mFM_pal_area[10];
    }
}

extern u16 mFM_obj_a_01_flower_pal[3 * 9][16];
extern u16 mFM_obj_01_zassou_pal[9][16];
extern u16 mFM_obj_tree_01_pal[14][16];
extern u16 mFM_obj_tree_01_pal_dol[14][16];
extern u16 mFM_obj_palm_01_pal[14][16];
extern u16 mFM_obj_gold_01_pal_dol[14][16];

static void mFM_SetFGPal(mFM_field_pal_c* pal, int term) {
    static int tree_pal_idx_table[mTM_TERM_NUM] = { 10, 12, 13, 0, 1, 2, 2, 3, 3, 4, 5, 6, 7, 8, 9, 10, 11, 10 };

    static int flower_pal_idx_table[mTM_TERM_NUM] = { 8, 8, 8, 0, 1, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 8, 8, 8 };

    int idx = flower_pal_idx_table[term];

    bcopy(mFM_obj_a_01_flower_pal[0 * 9 + idx], pal->flower0_pal, 16 * sizeof(u16));
    bcopy(mFM_obj_a_01_flower_pal[1 * 9 + idx], pal->flower1_pal, 16 * sizeof(u16));
    bcopy(mFM_obj_a_01_flower_pal[2 * 9 + idx], pal->flower2_pal, 16 * sizeof(u16));
    bcopy(mFM_obj_01_zassou_pal[idx], pal->grass_pal, 16 * sizeof(u16));
    bcopy(mFM_obj_tree_01_pal[tree_pal_idx_table[term]], pal->tree_pal, 16 * sizeof(u16));
    bcopy(mFM_obj_tree_01_pal_dol[tree_pal_idx_table[term]], pal->cedar_tree_pal, 16 * sizeof(u16));
    bcopy(mFM_obj_palm_01_pal[tree_pal_idx_table[term]], pal->palm_tree_pal, 16 * sizeof(u16));
    bcopy(mFM_obj_gold_01_pal_dol[tree_pal_idx_table[term]], pal->golden_tree_pal, 16 * sizeof(u16));
}

extern u16 mFM_earth_pal[mFM_FIELD_PAL_NUM][16];
extern u16 mFM_cliff_pal[mFM_FIELD_PAL_NUM][16];
extern u16 mFM_bush_pal[mFM_FIELD_PAL_NUM][16];
extern u16 mFM_rail_pal[mFM_FIELD_PAL_NUM][16];
extern u16 mFM_beach_pal[mFM_FIELD_PAL_NUM][16];

static void mFM_SetFieldPal(mFM_field_pal_c* pal) {
    static int field_pal_idx_table[mTM_TERM_NUM] = { 9, 10, 11, 0, 1, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 9, 9, 9 };

    u32 term = Common_Get(time.term_idx);
    int field_pal_idx;
    int i;
    u16* pal_src;

    if (term >= mTM_TERM_NUM) {
        term = mTM_TERM_0;
    }

    if (Save_Get(scene_no) == SCENE_MUSEUM_ROOM_INSECT) {
        term = mTM_TERM_4;
    }

    field_pal_idx = field_pal_idx_table[term];

    pal_src = mFM_earth_pal[field_pal_idx];
    for (i = 0; i < 16; i++) {
        pal->earth_pal[i] = pal_src[i];
    }

    pal_src = mFM_cliff_pal[field_pal_idx];
    for (i = 0; i < 16; i++) {
        pal->cliff_pal[i] = pal_src[i];
    }

    pal_src = mFM_bush_pal[field_pal_idx];
    for (i = 0; i < 16; i++) {
        pal->bush_pal[i] = pal_src[i];
    }

    mFM_SetFGPal(pal, term);
}

static void mFM_SetFgDepositP(mFM_block_info_c* block_info, mActor_name_t field_id, int bx_max, int bz_max,
                              int* island_x_blocks) {
    mFM_block_info_c* block_info_p;
    int total_block;
    int scene;
    u16* deposit_p;
    int bz;
    int bx;
    int fg_blocks;

    scene = Save_Get(scene_no);
    total_block = bx_max * bz_max;
    block_info_p = block_info;

    for (bz = 0; bz < total_block; bz++) {
        block_info[bz].fg_info.deposit_p = NULL;
    }

    if ((mFI_GET_TYPE(field_id) == mFI_FIELD_FG)) {
        fg_blocks = 0;

        if (scene == SCENE_FG) {
            for (bz = 0; bz < bz_max; bz++) {
                for (bx = 0; bx < bx_max; bx++) {
                    if (fg_blocks >= FG_BLOCK_TOTAL_NUM) {
                        break;
                    }

                    if (bx > 0 && bx < bx_max - 1 && bz > 0 && bz < bz_max - 3) {
                        block_info->fg_info.deposit_p = Save_GetPointer(deposit[fg_blocks++][0]);
                    }

                    block_info++;
                }
            }

            block_info = block_info_p + island_x_blocks[0] + bx_max * mISL_BLOCK_Z;

/* @BUG - they used the island Z acre location define here on accident lol */
#ifndef BUGFIXES
            for (bz = 0; bz < mISL_BLOCK_Z; bz++) {
#else
            for (bz = 0; bz < mISL_FG_BLOCK_X_NUM; bz++) {
#endif
                block_info->fg_info.deposit_p = Save_Get(island).deposit[bz];
                block_info++;
            }
        } else {
            for (bz = 0; bz < bz_max; bz++) {
                for (bx = 0; bx < bx_max; bx++) {
                    if (fg_blocks >= FG_BLOCK_TOTAL_NUM) {
                        break;
                    }

                    block_info->fg_info.deposit_p = Save_GetPointer(deposit[fg_blocks++][0]);
                    block_info++;
                }
            }
        }
    }
}

extern mFM_field_data_c data_fdd[SCENE_NUM];

static mFM_fdinfo_c* mFM_MakeField(u16 scene, u16 bg_max, u8 bg_num) {
    mFM_field_data_c* field_data;
    int island_x_blocks[2];
    int total_block;
    mFM_block_info_c* block_info;
    mFM_combination_c* combi;
    mFM_fdinfo_c* field_info = (mFM_fdinfo_c*)zelda_malloc(sizeof(mFM_fdinfo_c));
    int i;
    int j;
    mActor_name_t house_owner_id;
    int floor_no;

    if (field_info == NULL) {
        return NULL;
    }

    bzero(field_info, sizeof(mFM_fdinfo_c));
    field_data = &data_fdd[scene];
    field_info->block_x_max = field_data->block_x_max;
    field_info->block_z_max = field_data->block_z_max;
    field_info->bg_num = bg_num;
    field_info->bg_max = bg_max;
    field_info->fg2_p = (mActor_name_t**)zelda_malloc((mHm_LAYER_NUM - 1) * sizeof(mActor_name_t*));

    for (i = 0; i < 3; i++) {
        field_info->fg2_p[i] = NULL;
    }

    i = sizeof(mFM_block_info_c) * field_data->block_x_max * field_data->block_z_max;
    block_info = (mFM_block_info_c*)zelda_malloc(i);

    if (block_info == NULL) {
/* @BUG - field_info was not freed */
#ifdef BUGFIXES
        zelda_free(field_info);
#endif
        return NULL;
    }

    bzero(block_info, i);
    field_info->block_info = block_info;
    field_info->field_id = field_data->field_name;
    field_info->_04 = field_data->_94;
    field_info->update_fg = FALSE;
    field_info->born_item = FALSE;
    field_info->born_actor = FALSE;

    for (j = 0; j < mFM_VISIBLE_BLOCK_NUM; j++) {
        field_info->bg_draw_info[j].block_x = 0xFF;
        field_info->bg_draw_info[j].block_z = 0xFF;
        field_info->bg_draw_info[j].dma_loaded = FALSE;
        field_info->last_bg_idx[j] = -1;
    }

    if (Save_Get(scene_no) == SCENE_FG) {
        mFI_GetIslandBlockNumX(island_x_blocks);
    }

    if (Save_Get(scene_no) == SCENE_FG) {
        combi = Save_Get(combi_table[0]);
        mFM_SetFgUtPtoSaveData(field_info->block_info, field_info->block_x_max, field_info->block_z_max,
                               island_x_blocks);
    } else if (mSc_IS_SCENE_PLAYER_ROOM(Save_Get(scene_no))) {
        house_owner_id = Common_Get(house_owner_name);
        floor_no = mFI_GetNowPlayerHouseFloorNo();

        if (floor_no == -1) {
            floor_no = 0;
        }

        if (house_owner_id == RSV_NO) {
            house_owner_id = EMPTY_NO;
            Common_Set(house_owner_name, house_owner_id);
        }

        combi = field_data->combi;
        field_info->field_id = mFI_FIELD_PLAYER0_ROOM + house_owner_id;

        if (Save_Get(scene_no) == SCENE_COTTAGE_MY) {
            mFM_SetFgUtPtoCottageInfo(field_info->block_info, field_info->block_x_max, field_info->block_z_max);
        } else {
            mFM_SetFgUtPtoHomeInfo(field_info->block_info, field_info->block_x_max, field_info->block_z_max,
                                   house_owner_id, floor_no);
        }
    } else {
        mFM_block_info_c* block_info = field_info->block_info;
        int total_block = field_info->block_x_max * field_info->block_z_max;
        int k;
        combi = field_data->combi;

        for (k = total_block; k != 0; k--) {
            mActor_name_t* fg_p = (mActor_name_t*)zelda_malloc(UT_TOTAL_NUM * sizeof(mActor_name_t));

            // There could be a memory leak here due to previous allocated blocks, perhaps investigate later
            if (fg_p == NULL) {
                break;
            }

            bzero(fg_p, UT_TOTAL_NUM * sizeof(mActor_name_t));
            block_info->fg_info.items_p = fg_p;
            block_info++;
        }
    }

    if (mSc_IS_SCENE_PLAYER_ROOM(Save_Get(scene_no))) {
        mHm_lyr_c* layer;

        if (Save_Get(scene_no) == SCENE_COTTAGE_MY) {
            layer = &Save_Get(island).cottage.room.layer_main;
        } else {
            mActor_name_t house_owner_id = Common_Get(house_owner_name);
            floor_no = mFI_GetNowPlayerHouseFloorNo();

            if (floor_no == -1) {
                floor_no = 0;
            }

            layer = &Save_Get(homes[house_owner_id]).floors[floor_no].layer_main;
        }

        for (i = 1; i < mHm_LAYER_NUM; i++) {
            field_info->fg2_p[i - 1] = layer[i].items[0];
        }
    } else if (Save_Get(scene_no) == SCENE_NPC_HOUSE || Save_Get(scene_no) == SCENE_FIELD_TOOL_INSIDE) {
        field_info->fg2_p[0] = (mActor_name_t*)zelda_malloc(UT_TOTAL_NUM * sizeof(mActor_name_t));

        if (field_info->fg2_p[0] != NULL) {
            bzero(field_info->fg2_p[0], UT_TOTAL_NUM * sizeof(mActor_name_t));
        }
    }

    mFM_SetBlockInfo(field_info, combi);
    mFM_SetMoveActorInfo(field_info->block_info, field_info->block_x_max, field_info->block_z_max,
                         field_data->move_actor_data, field_data->_94, field_data->_98);

    for (i = 0; i < mFM_VISIBLE_BLOCK_NUM; i++) {
        field_info->bg_display_list_p[i] = NULL;
    }

    for (i = 0; i < field_info->bg_num; i++) {
        field_info->bg_display_list_p[i] = (u8*)zelda_malloc(field_info->bg_max);
        field_info->bg_display_list_p[i] = (u8*)(((uintptr_t)(field_info->bg_display_list_p[i]) + (16 - 1)) & ~(uintptr_t)(16 - 1));
    }

    mFM_set_pal_p(&field_info->field_palette);
    mFM_SetFieldPal(&field_info->field_palette);
    mFM_SetFgDepositP(field_info->block_info, field_info->field_id, field_info->block_x_max, field_info->block_z_max,
                      island_x_blocks);

    return field_info;
}

static mBGTex_obj_c l_bg_tex_common_dummy[27] = {
    { earth_tex_dummy, 0x800 },    { cliff_tex_dummy, 0x800 },   { bush_a_tex_dummy, 0x800 },
    { bush_b_tex_dummy, 0x400 },   { grass_tex_dummy, 0x200 },   { rail_tex_dummy, 0x800 },
    { station_tex_dummy, 0x800 },  { stone_tex_dummy, 0x800 },   { river_tex_dummy, 0x400 },
    { water_1_tex_dummy, 0x200 },  { water_2_tex_dummy, 0x200 }, { bridge_1_tex_dummy, 0x800 },
    { bridge_2_tex_dummy, 0x800 }, { tekkyo_tex_dummy, 0x800 },  { tunnel_tex_dummy, 0x800 },
    { beach_tex_dummy, 0x800 },    { bridge_1_pal_dummy, 0x20 }, { bridge_2_pal_dummy, 0x20 },
    { station_pal_dummy, 0x20 },   { beach1_tex_dummy2, 0x400 }, { beach2_tex_dummy2, 0x100 },
    { sand_tex_dummy, 0x400 },     { wave1_tex_dummy, 0x400 },   { wave2_tex_dummy, 0x800 },
    { wave3_tex_dummy, 0x400 },    { sprashA_tex_dummy, 0x200 }, { sprashC_tex_dummy, 0x200 },
};

static mBGTex_obj_c l_bg_pal_common_dummy[5] = { { earth_pal_dummy, 16 * sizeof(u16) },
                                                 { cliff_pal_dummy, 16 * sizeof(u16) },
                                                 { bush_pal_dummy, 16 * sizeof(u16) },
                                                 { rail_pal_dummy, 16 * sizeof(u16) },
                                                 { beach_pal_dummy2, 16 * sizeof(u16) } };

extern u8 mFM_grd_s_earth_tex[];
extern u8 mFM_grd_s_cliff_tex[];
extern u8 mFM_grd_s_bushA_tex[];
extern u8 mFM_grd_s_bushB_tex[];
extern u8 mFM_grd_s_grass_tex[];
extern u8 mFM_grd_s_rail_tex[];
extern u8 mFM_grd_s_station_tex[];
extern u8 mFM_grd_s_stone_tex[];
extern u8 mFM_grd_s_river_tex[];
extern u8 mFM_grd_water1_tex[];
extern u8 mFM_grd_water2_tex[];
extern u8 mFM_grd_s_bridge1_tex[];
extern u8 mFM_grd_s_bridge2_tex[];
extern u8 mFM_grd_s_tekkyo_tex[];
extern u8 mFM_grd_s_tunnel_tex[];
extern u8 mFM_grd_s_beach_tex[];
extern u16 mFM_grd_s_bridge1_pal[];
extern u16 mFM_grd_s_bridge2_pal[];
extern u16 mFM_grd_s_station1_pal[];
extern u8 mFM_grd_beachA_tex[];
extern u8 mFM_grd_beachB_tex[];
extern u8 mFM_grd_s_sand_tex[];
extern u8 mFM_grd_wave1_tex[];
extern u8 mFM_grd_wave2_tex[];
extern u8 mFM_grd_wave3_tex[];
extern u8 mFM_grd_sprashA_tex[];
extern u8 mFM_grd_sprashC_tex[];

static void* l_bg_tex_segment_rom_start_s_0[mFM_FIELD_TEX_NUM] = {
    mFM_grd_s_earth_tex, mFM_grd_s_cliff_tex,   mFM_grd_s_bushA_tex,   mFM_grd_s_bushB_tex,    mFM_grd_s_grass_tex,
    mFM_grd_s_rail_tex,  mFM_grd_s_station_tex, mFM_grd_s_stone_tex,   mFM_grd_s_river_tex,    mFM_grd_water1_tex,
    mFM_grd_water2_tex,  mFM_grd_s_bridge1_tex, mFM_grd_s_bridge2_tex, mFM_grd_s_tekkyo_tex,   mFM_grd_s_tunnel_tex,
    mFM_grd_s_beach_tex, mFM_grd_s_bridge1_pal, mFM_grd_s_bridge2_pal, mFM_grd_s_station1_pal, mFM_grd_beachA_tex,
    mFM_grd_beachB_tex,  mFM_grd_s_sand_tex,    mFM_grd_wave1_tex,     mFM_grd_wave2_tex,      mFM_grd_wave3_tex,
    mFM_grd_sprashA_tex, mFM_grd_sprashC_tex
};

extern u8 mFM_grd_s_earth_2_tex[];
extern u8 mFM_grd_s_cliff_2_tex[];
extern u8 mFM_grd_s_bushA_2_tex[];
extern u8 mFM_grd_s_bushB_2_tex[];
extern u8 mFM_grd_s_grass_2_tex[];
extern u8 mFM_grd_s_rail_2_tex[];
extern u8 mFM_grd_s_station_2_tex[];
extern u8 mFM_grd_s_stone_2_tex[];
extern u8 mFM_grd_s_river_2_tex[];
extern u8 mFM_grd_s_bridge1_2_tex[];
extern u8 mFM_grd_s_bridge2_2_tex[];
extern u8 mFM_grd_s_tekkyo_2_tex[];
extern u8 mFM_grd_s_tunnel_2_tex[];
extern u8 mFM_grd_s_sand_2_tex[];

static void* l_bg_tex_segment_rom_start_s_1[mFM_FIELD_TEX_NUM] = {
    mFM_grd_s_earth_2_tex,   mFM_grd_s_cliff_2_tex,  mFM_grd_s_bushA_2_tex,   mFM_grd_s_bushB_2_tex,
    mFM_grd_s_grass_2_tex,   mFM_grd_s_rail_2_tex,   mFM_grd_s_station_2_tex, mFM_grd_s_stone_2_tex,
    mFM_grd_s_river_2_tex,   mFM_grd_water1_tex,     mFM_grd_water2_tex,      mFM_grd_s_bridge1_2_tex,
    mFM_grd_s_bridge2_2_tex, mFM_grd_s_tekkyo_2_tex, mFM_grd_s_tunnel_2_tex,  mFM_grd_s_beach_tex,
    mFM_grd_s_bridge1_pal,   mFM_grd_s_bridge2_pal,  mFM_grd_s_station1_pal,  mFM_grd_beachA_tex,
    mFM_grd_beachB_tex,      mFM_grd_s_sand_2_tex,   mFM_grd_wave1_tex,       mFM_grd_wave2_tex,
    mFM_grd_wave3_tex,       mFM_grd_sprashA_tex,    mFM_grd_sprashC_tex
};

extern u8 mFM_grd_s_earth_3_tex[];
extern u8 mFM_grd_s_cliff_3_tex[];
extern u8 mFM_grd_s_bushA_3_tex[];
extern u8 mFM_grd_s_bushB_3_tex[];
extern u8 mFM_grd_s_grass_3_tex[];
extern u8 mFM_grd_s_rail_3_tex[];
extern u8 mFM_grd_s_station_3_tex[];
extern u8 mFM_grd_s_stone_3_tex[];
extern u8 mFM_grd_s_river_3_tex[];
extern u8 mFM_grd_s_bridge1_3_tex[];
extern u8 mFM_grd_s_bridge2_3_tex[];
extern u8 mFM_grd_s_tekkyo_3_tex[];
extern u8 mFM_grd_s_tunnel_3_tex[];
extern u8 mFM_grd_s_sand_3_tex[];

static void* l_bg_tex_segment_rom_start_s_2[mFM_FIELD_TEX_NUM] = {
    mFM_grd_s_earth_3_tex,   mFM_grd_s_cliff_3_tex,  mFM_grd_s_bushA_3_tex,   mFM_grd_s_bushB_3_tex,
    mFM_grd_s_grass_3_tex,   mFM_grd_s_rail_3_tex,   mFM_grd_s_station_3_tex, mFM_grd_s_stone_3_tex,
    mFM_grd_s_river_3_tex,   mFM_grd_water1_tex,     mFM_grd_water2_tex,      mFM_grd_s_bridge1_3_tex,
    mFM_grd_s_bridge2_3_tex, mFM_grd_s_tekkyo_3_tex, mFM_grd_s_tunnel_3_tex,  mFM_grd_s_beach_tex,
    mFM_grd_s_bridge1_pal,   mFM_grd_s_bridge2_pal,  mFM_grd_s_station1_pal,  mFM_grd_beachA_tex,
    mFM_grd_beachB_tex,      mFM_grd_s_sand_3_tex,   mFM_grd_wave1_tex,       mFM_grd_wave2_tex,
    mFM_grd_wave3_tex,       mFM_grd_sprashA_tex,    mFM_grd_sprashC_tex
};

static void** l_bg_tex_segment_table[mFM_BG_TEX_NUM] = { l_bg_tex_segment_rom_start_s_0, l_bg_tex_segment_rom_start_s_1,
                                                         l_bg_tex_segment_rom_start_s_2 };

extern u8 mFM_grd_w_earth_tex[];
extern u8 mFM_grd_w_cliff_tex[];
extern u8 mFM_grd_w_bushA_tex[];
extern u8 mFM_grd_w_bushB_tex[];
extern u8 mFM_grd_w_grass_tex[];
extern u8 mFM_grd_w_rail_tex[];
extern u8 mFM_grd_w_station_tex[];
extern u8 mFM_grd_w_stone_tex[];
extern u8 mFM_grd_w_river_tex[];
extern u8 mFM_grd_w_bridge1_tex[];
extern u8 mFM_grd_w_bridge2_tex[];
extern u8 mFM_grd_w_tekkyo_tex[];
extern u8 mFM_grd_w_sand_tex[];

static void* l_bg_tex_segment_rom_start_w_0[mFM_FIELD_TEX_NUM] = {
    mFM_grd_w_earth_tex, mFM_grd_w_cliff_tex,   mFM_grd_w_bushA_tex,   mFM_grd_w_bushB_tex,    mFM_grd_w_grass_tex,
    mFM_grd_w_rail_tex,  mFM_grd_w_station_tex, mFM_grd_w_stone_tex,   mFM_grd_w_river_tex,    mFM_grd_water1_tex,
    mFM_grd_water2_tex,  mFM_grd_w_bridge1_tex, mFM_grd_w_bridge2_tex, mFM_grd_w_tekkyo_tex,   mFM_grd_s_tunnel_tex,
    mFM_grd_s_beach_tex, mFM_grd_s_bridge1_pal, mFM_grd_s_bridge2_pal, mFM_grd_s_station1_pal, mFM_grd_beachA_tex,
    mFM_grd_beachB_tex,  mFM_grd_w_sand_tex,    mFM_grd_wave1_tex,     mFM_grd_wave2_tex,      mFM_grd_wave3_tex,
    mFM_grd_sprashA_tex, mFM_grd_sprashC_tex
};

extern u8 mFM_grd_w_earth_2_tex[];
extern u8 mFM_grd_w_cliff_2_tex[];
extern u8 mFM_grd_w_bushA_2_tex[];
extern u8 mFM_grd_w_bushB_2_tex[];
extern u8 mFM_grd_w_grass_2_tex[];
extern u8 mFM_grd_w_rail_2_tex[];
extern u8 mFM_grd_w_station_2_tex[];
extern u8 mFM_grd_w_stone_2_tex[];
extern u8 mFM_grd_w_river_2_tex[];
extern u8 mFM_grd_w_bridge1_2_tex[];
extern u8 mFM_grd_w_bridge2_2_tex[];
extern u8 mFM_grd_w_tekkyo_2_tex[];
extern u8 mFM_grd_w_tunnel_2_tex[];
extern u8 mFM_grd_w_sand_2_tex[];

static void* l_bg_tex_segment_rom_start_w_1[mFM_FIELD_TEX_NUM] = {
    mFM_grd_w_earth_2_tex,   mFM_grd_w_cliff_2_tex,  mFM_grd_w_bushA_2_tex,   mFM_grd_w_bushB_2_tex,
    mFM_grd_w_grass_2_tex,   mFM_grd_w_rail_2_tex,   mFM_grd_w_station_2_tex, mFM_grd_w_stone_2_tex,
    mFM_grd_w_river_2_tex,   mFM_grd_water1_tex,     mFM_grd_water2_tex,      mFM_grd_w_bridge1_2_tex,
    mFM_grd_w_bridge2_2_tex, mFM_grd_w_tekkyo_2_tex, mFM_grd_w_tunnel_2_tex,  mFM_grd_s_beach_tex,
    mFM_grd_s_bridge1_pal,   mFM_grd_s_bridge2_pal,  mFM_grd_s_station1_pal,  mFM_grd_beachA_tex,
    mFM_grd_beachB_tex,      mFM_grd_w_sand_2_tex,   mFM_grd_wave1_tex,       mFM_grd_wave2_tex,
    mFM_grd_wave3_tex,       mFM_grd_sprashA_tex,    mFM_grd_sprashC_tex
};

extern u8 mFM_grd_w_earth_3_tex[];
extern u8 mFM_grd_w_cliff_3_tex[];
extern u8 mFM_grd_w_bushA_3_tex[];
extern u8 mFM_grd_w_bushB_3_tex[];
extern u8 mFM_grd_w_grass_3_tex[];
extern u8 mFM_grd_w_rail_3_tex[];
extern u8 mFM_grd_w_station_3_tex[];
extern u8 mFM_grd_w_stone_3_tex[];
extern u8 mFM_grd_w_river_3_tex[];
extern u8 mFM_grd_w_bridge1_3_tex[];
extern u8 mFM_grd_w_bridge2_3_tex[];
extern u8 mFM_grd_w_tekkyo_3_tex[];
extern u8 mFM_grd_w_tunnel_3_tex[];
extern u8 mFM_grd_w_sand_3_tex[];

static void* l_bg_tex_segment_rom_start_w_2[mFM_FIELD_TEX_NUM] = {
    mFM_grd_w_earth_3_tex,   mFM_grd_w_cliff_3_tex,  mFM_grd_w_bushA_3_tex,   mFM_grd_w_bushB_3_tex,
    mFM_grd_w_grass_3_tex,   mFM_grd_w_rail_3_tex,   mFM_grd_w_station_3_tex, mFM_grd_w_stone_3_tex,
    mFM_grd_w_river_3_tex,   mFM_grd_water1_tex,     mFM_grd_water2_tex,      mFM_grd_w_bridge1_3_tex,
    mFM_grd_w_bridge2_3_tex, mFM_grd_w_tekkyo_3_tex, mFM_grd_w_tunnel_3_tex,  mFM_grd_s_beach_tex,
    mFM_grd_s_bridge1_pal,   mFM_grd_s_bridge2_pal,  mFM_grd_s_station1_pal,  mFM_grd_beachA_tex,
    mFM_grd_beachB_tex,      mFM_grd_w_sand_3_tex,   mFM_grd_wave1_tex,       mFM_grd_wave2_tex,
    mFM_grd_wave3_tex,       mFM_grd_sprashA_tex,    mFM_grd_sprashC_tex
};

static void** l_bg_w_tex_segment_table[mFM_BG_TEX_NUM] = { l_bg_tex_segment_rom_start_w_0,
                                                           l_bg_tex_segment_rom_start_w_1,
                                                           l_bg_tex_segment_rom_start_w_2 };

static u8* l_bg_pal_segment_rom_start[5] = { (u8*)mFM_earth_pal, (u8*)mFM_cliff_pal, (u8*)mFM_bush_pal,
                                             (u8*)mFM_rail_pal, (u8*)mFM_beach_pal };

static u8 l_water_permission[mFM_FIELD_TEX_NUM] = { TRUE,  TRUE,  TRUE, TRUE, TRUE,  TRUE,  TRUE,  TRUE, FALSE,
                                                    FALSE, FALSE, TRUE, TRUE, TRUE,  TRUE,  TRUE,  TRUE, TRUE,
                                                    TRUE,  TRUE,  TRUE, TRUE, FALSE, FALSE, FALSE, TRUE, TRUE };

static void mFM_LoadBGCommonMonthlyPal() {
    static int field_pal_idx_table[mTM_TERM_NUM] = { 9, 10, 11, 0, 1, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 9, 9, 9 };

    u32 term = Common_Get(time.term_idx);
    int idx;
    int i;

    if (term >= mTM_TERM_NUM) {
        term = mTM_TERM_0;
    }

    if (Save_Get(scene_no) == SCENE_MUSEUM_ROOM_INSECT) {
        term = mTM_TERM_4;
    }

    idx = field_pal_idx_table[term];

    for (i = 0; i < 5; i++) {
        bcopy(l_bg_pal_segment_rom_start[i] + ((l_bg_pal_common_dummy[i].size * idx) & ~1),
              l_bg_pal_common_dummy[i].data, l_bg_pal_common_dummy[i].size);
    }
}

extern void mFM_DecideBgTexIdx(u8* bg_tex_idx) {
    *bg_tex_idx = RANDOM(mFM_BG_TEX_NUM);
}

static void mFM_LoadBGCommonTex(int update_tex, u8 tex_idx) {
    void** bg_tex_tbl;
    u32 season = Common_Get(time.season);
    int i;

    if (season >= mTM_SEASON_NUM) {
        season = mTM_SEASON_SPRING;
    }

    if (Save_Get(scene_no) == SCENE_TITLE_DEMO) {
        mFM_DecideBgTexIdx(&tex_idx);
    }

    if (tex_idx >= mFM_BG_TEX_NUM) {
        tex_idx = mFM_BG_TEX_TRIANGLE;
    }

    if (Save_Get(scene_no) == SCENE_MUSEUM_ROOM_INSECT) {
        bg_tex_tbl = l_bg_tex_segment_table[tex_idx];
    } else if (season == mTM_SEASON_WINTER) {
        bg_tex_tbl = l_bg_w_tex_segment_table[tex_idx];
    } else {
        bg_tex_tbl = l_bg_tex_segment_table[tex_idx];
    }

    for (i = 0; i < mFM_FIELD_TEX_NUM; i++) {
        if (update_tex == TRUE || l_water_permission[i] == TRUE) {
            bcopy(bg_tex_tbl[i], l_bg_tex_common_dummy[i].data, l_bg_tex_common_dummy[i].size);
        }
    }

    mFM_LoadBGCommonMonthlyPal();
}

static void set_field_type() {
    int field_id = mFI_GetFieldId();
    int house_owner_id;
    u8 field_type;

    if (mLd_PlayerManKindCheck() == FALSE) {
        house_owner_id = mFI_FIELD_PLAYER0_ROOM + mHS_get_arrange_idx(Common_Get(player_no));
    } else {
        house_owner_id = RSV_NO;
    }

    if (field_id == mFI_FIELD_FG) {
        field_type = mFI_FIELDTYPE2_FG;
    } else if ((field_id == house_owner_id && mEv_CheckFirstIntro() == FALSE) ||
               Save_Get(scene_no) == SCENE_COTTAGE_MY) {
        field_type = mFI_FIELDTYPE2_PLAYER_ROOM;
    } else if (field_id == mFI_FIELD_NPCROOM0) {
        field_type = mFI_FIELDTYPE2_NPC_ROOM;
    } else {
        field_type = mFI_FIELDTYPE2_ROOM;
    }

    Common_Set(field_type, field_type);
}

static void mFM_PoorTreeBlock(mFM_block_info_c* block, int ut) {
    mCoBG_Collision_u* col = (mCoBG_Collision_u*)block->bg_info.collision;
    int i;

    for (i = ut; i < UT_TOTAL_NUM; i += UT_X_NUM) {
        mCoBG_Change2PoorAttr(col + i);
    }
}

static void mFM_PoorTree() {
    mFM_block_info_c* block = g_fdinfo->block_info;
    int bx_max;
    int bz_max;
    int block_total;
    int i;

    bx_max = g_fdinfo->block_x_max;
    bz_max = g_fdinfo->block_z_max - 3;
    block_total = bx_max * bz_max;

    if (mFI_GET_TYPE(g_fdinfo->field_id) == mFI_FIELD_FG && Save_Get(scene_no) == SCENE_FG) {
        for (i = bx_max; i < block_total; i += bx_max) {
            mFM_PoorTreeBlock(&block[i + 1], 0);
            mFM_PoorTreeBlock(&block[i + bx_max - 2], UT_X_NUM - 1);
        }
    }
}

static void mFM_PoorTreeUnderPlayerBlock() {
    mFM_fdinfo_c* field_info = g_fdinfo;
    mFM_block_info_c* block_info = field_info->block_info;
    int bx_max = field_info->block_x_max;

    if (field_info != NULL && mFI_GET_TYPE(field_info->field_id) == mFI_FIELD_FG && Save_Get(scene_no) == SCENE_FG) {
        mCoBG_Collision_u* col = &block_info[bx_max * 3 + 3].bg_info.collision[0][0];

        if (col != NULL) {
            mCoBG_Change2PoorAttr(col + 7);
            mCoBG_Change2PoorAttr(col + 8);
            mCoBG_Change2PoorAttr(col + (UT_X_NUM + 7));
            mCoBG_Change2PoorAttr(col + (UT_X_NUM + 8));
        }
    }
}

static void mFM_SetFruit_title_demo(int scene) {
    if (scene == SCENE_FIELD_TOOL || scene == SCENE_TITLE_DEMO) {
        mFI_BlockUtNumtoFGSet(TREE_APPLE_FRUIT, 5, 5, 14, 8);
    }
}

extern void mFM_SetFieldInitData(int bg_disp_num, int bg_disp_size) {
    l_bg_disp_num = bg_disp_num;
    l_bg_disp_size = bg_disp_size;
}

extern void mFM_FieldInit(GAME_PLAY* play) {
    int bg_disp_num = l_bg_disp_num;
    int bg_disp_size = l_bg_disp_size;
    int scene = Save_Get(scene_no);

    mFM_LoadBGCommonTex(TRUE, Save_Get(bg_tex_idx));
    if (bg_disp_num > mFM_VISIBLE_BLOCK_NUM) {
        bg_disp_num = mFM_VISIBLE_BLOCK_NUM;
    }

    g_fdinfo = mFM_MakeField(scene, bg_disp_size, bg_disp_num);
    mFI_InitMoveActorBitData();
    mFI_ClearColKeep();
    mFI_InitAreaInfo();
    mFI_InitRegisterBgInfo();
    set_field_type();
    mFM_PoorTree();

    if (Common_Get(field_type) == mFI_FIELDTYPE2_FG) {
        mRF_CheckBeastRoad();
    }

    mFM_PoorTreeUnderPlayerBlock();
    mAGrw_ChangeCedar2Tree();
    mAGrw_RenewalFgItem(Common_GetPointer(time.rtc_time));
    mAGrw_SetXmasTree();
    mFM_SetFruit_title_demo(Save_Get(scene_no));

    if (scene == SCENE_FG) {
        mNpc_SetNpcHomeYpos();
    }

    mNpc_SendRegisteredGoodbyMail();
    Common_Set(floor_idx, mRmTp_GetFloorIdx());
    Common_Set(make_npc2_actor, FALSE);

    if (play->fb_wipe_type == WIPE_TYPE_EVENT) {
        if (scene == SCENE_MUSEUM_ENTRANCE) {
            mBGMPsComp_museum_status(1);
        } else if (scene == SCENE_MUSEUM_ROOM_PAINTING) {
            mBGMPsComp_museum_status(2);
        } else if (scene == SCENE_MUSEUM_ROOM_FISH) {
            mBGMPsComp_museum_status(3);
        } else if (scene == SCENE_MUSEUM_ROOM_INSECT) {
            mBGMPsComp_museum_status(4);
        } else if (scene == SCENE_MUSEUM_ROOM_FOSSIL) {
            mBGMPsComp_museum_status(5);
        }
    } else if (mFI_GET_TYPE(g_fdinfo->field_id) == mFI_FIELD_PLAYER0_ROOM ||
               mFI_GET_TYPE(g_fdinfo->field_id) == mFI_FIELD_ROOM0 ||
               mFI_GET_TYPE(g_fdinfo->field_id) == mFI_FIELD_NPCROOM0) {
        if (scene == SCENE_MUSEUM_ENTRANCE) {
            mBGMPsComp_scene_mode(15);
            mBGMPsComp_museum_status(1);
        } else if (scene == SCENE_MUSEUM_ROOM_PAINTING) {
            mBGMPsComp_scene_mode(15);
            mBGMPsComp_museum_status(2);
        } else if (scene == SCENE_MUSEUM_ROOM_FISH) {
            mBGMPsComp_scene_mode(15);
            mBGMPsComp_museum_status(3);
        } else if (scene == SCENE_MUSEUM_ROOM_INSECT) {
            mBGMPsComp_scene_mode(15);
            mBGMPsComp_museum_status(4);
        } else if (scene == SCENE_MUSEUM_ROOM_FOSSIL) {
            mBGMPsComp_scene_mode(15);
            mBGMPsComp_museum_status(5);
        } else if (scene == SCENE_LIGHTHOUSE) {
            mBGMPsComp_scene_mode(16);
        } else {
            if (mEv_CheckFirstIntro() == TRUE) {
                mBGMPsComp_scene_mode(10);
            } else {
                mBGMPsComp_scene_mode(2);
            }
        }
    } else if (mFI_GET_TYPE(g_fdinfo->field_id) == mFI_FIELD_FG) {
        if (scene != SCENE_TITLE_DEMO) {
            if (mEv_CheckFirstIntro() == TRUE) {
                mBGMPsComp_scene_mode(9);
            } else if (mEv_CheckGateway() == TRUE) {
                mBGMPsComp_scene_mode(8);
            } else {
                mBGMPsComp_scene_mode(1);
            }
        }
    } else if (scene == SCENE_PLAYERSELECT || scene == SCENE_PLAYERSELECT_2 || scene == SCENE_PLAYERSELECT_3 ||
               scene == SCENE_PLAYERSELECT_SAVE) {
        mBGMPsComp_scene_mode(3);
    } else if (scene == SCENE_START_DEMO || scene == SCENE_START_DEMO2 || scene == SCENE_START_DEMO3) {
        mBGMPsComp_scene_mode(4);
    } else {
        mBGMPsComp_scene_mode(0);
    }
}

extern void mFM_Field_dt() {
    mFM_fdinfo_c* field_info = g_fdinfo;
    mFM_block_info_c* block_info;
    int max;
    int i;

    Common_Set(last_field_id, field_info->field_id);

    if (mFI_GET_TYPE(field_info->field_id) == mFI_FIELD_ROOM0 && mSc_IS_SCENE_MUSEUM_ROOM(Common_Get(last_scene_no)) &&
        !mSc_IS_SCENE_MUSEUM_ROOM(Save_Get(scene_no))) {
        mBGMPsComp_museum_status(0);
    }

    if (field_info->field_id != mFI_FIELD_FG && mFI_GET_TYPE(field_info->field_id) != mFI_FIELD_PLAYER0_ROOM) {
        if (mFI_GET_TYPE(field_info->field_id) == mFI_FIELD_NPCROOM0) {
            if (field_info->fg2_p[0] != NULL) {
                zelda_free(field_info->fg2_p[0]);
            }
        } else {
            block_info = field_info->block_info;
            max = field_info->block_x_max * field_info->block_z_max;

            for (i = max; i != 0; i--) {
// Aus version added NULL check
#if VERSION >= VER_GAFU01_00
                if (block_info->fg_info.items_p != NULL) {
                    zelda_free(block_info->fg_info.items_p);
                }
#else
                zelda_free(block_info->fg_info.items_p);
#endif
                block_info++;
            }
        }
    }

    // Aus version added NULL checks
#if VERSION >= VER_GAFU01_00
    if (field_info->fg2_p != NULL) {
        zelda_free(field_info->fg2_p);
    }
    if (field_info->block_info != NULL) {
        zelda_free(field_info->block_info);
    }

    for (i = 0; i < mFM_VISIBLE_BLOCK_NUM; i++) {
        if (field_info->bg_display_list_p[i] != NULL) {
            zelda_free(field_info->bg_display_list_p[i]);
        }
    }

    if (field_info != NULL) {
        zelda_free(field_info);
    }
#else
    zelda_free(field_info->fg2_p);
    zelda_free(field_info->block_info);

    for (i = 0; i < mFM_VISIBLE_BLOCK_NUM; i++) {
        zelda_free(field_info->bg_display_list_p[i]);
    }

    zelda_free(field_info);
#endif


    g_fdinfo = NULL;
    mFI_InitRegisterBgInfo();
}

static void mFM_SetBlockKind(u8* type_p, int* kind_p, mFM_combination_c* combi_p, mFM_combo_info_c* combi_info_p,
                             int count) {
    for (count; count != 0; count--) {
        int combi_type = combi_p[0].combination_type;

        type_p[0] = combi_info_p[combi_type].type;
        kind_p[0] = mRF_Type2BlockInfo(combi_info_p[combi_type].type);

        type_p++;
        kind_p++;
        combi_p++;
    }
}

extern void mFM_SetBlockKindLoadCombi() {
    mFM_SetBlockKind(g_block_type_p, g_block_kind_p, Save_Get(combi_table[0]), data_combi_table, BLOCK_TOTAL_NUM);
}

static void mFM_SetIslandFg(mFM_combo_info_c* combi_info_p, mFM_fg_data_c** sorted_fg_data, int* island_x_blocks) {
    int i;

    for (i = 0; i < mISL_FG_BLOCK_X_NUM; i++) {
        int fg_id = combi_info_p[Save_Get(combi_table[mISL_BLOCK_Z][island_x_blocks[0]]).combination_type].fg_id;
        if (sorted_fg_data[fg_id] == NULL) {
            break;
        }

        if (fg_id >= 0 && fg_id < mFM_FG_NUM) {
            mFM_FgUtDataSet(Save_Get(island).fgblock[0][i].items[0], sorted_fg_data[fg_id]->items[0]);
        }

        island_x_blocks++;
    }
}

static mFM_combination_c l_combiID[BLOCK_TOTAL_NUM] = {
    // clang-format off
    { BLOCK_COMBI_GRD_S_E4_1, 1 }, { BLOCK_COMBI_GRD_S_E1_1, 1 }, { BLOCK_COMBI_GRD_S_E1_1, 1 }, { BLOCK_COMBI_GRD_S_E1_1, 1 }, { BLOCK_COMBI_GRD_S_E1_R1_1, 1 }, { BLOCK_COMBI_GRD_S_E1_1, 1 }, { BLOCK_COMBI_GRD_S_E5_1, 1 },
    { BLOCK_COMBI_GRD_S_E2_T_1, 1 }, { BLOCK_COMBI_GRD_S_T_9, 1 }, { BLOCK_COMBI_GRD_S_T_SH_2, 1 }, { BLOCK_COMBI_GRD_S_T_ST1_3, 1 }, { BLOCK_COMBI_GRD_S_T_R1_4, 1 }, { BLOCK_COMBI_GRD_S_T_PO_3, 1 }, { BLOCK_COMBI_GRD_S_E3_T_1, 1 },
    { BLOCK_COMBI_GRD_S_E2_1, 1 }, { BLOCK_COMBI_GRD_S_F_5, 1 }, { BLOCK_COMBI_GRD_5, 1 },   { BLOCK_COMBI_GRD_S_F_MH_2, 1 }, { BLOCK_COMBI_GRD_S_R1_3, 1 },  { BLOCK_COMBI_GRD_S_F_1, 1 },  { BLOCK_COMBI_GRD_S_E3_1, 1 },
    { BLOCK_COMBI_GRD_S_E2_1, 1 }, { BLOCK_COMBI_GRD_S_C4_1, 0 },  { BLOCK_COMBI_GRD_S_C5_S_2, 0 }, { BLOCK_COMBI_GRD_S_R7_2, 1 },  { BLOCK_COMBI_GRD_S_R6_B_2, 1 }, { BLOCK_COMBI_GRD_S_C4_2, 0 }, { BLOCK_COMBI_GRD_S_E3_C1_1, 0 },
    { BLOCK_COMBI_GRD_S_E2_C1_1, 0 }, { BLOCK_COMBI_GRD_S_C2_1, 0 },  { BLOCK_COMBI_GRD_S_F_9, 0 }, { BLOCK_COMBI_GRD_S_R1_B_1, 0 },  { BLOCK_COMBI_GRD_S_F_10, 0 }, { BLOCK_COMBI_GRD_S_F_KO_3, 0 }, { BLOCK_COMBI_GRD_S_E3_1, 0 },
    { BLOCK_COMBI_GRD_S_E2_1, 0 }, { BLOCK_COMBI_GRD_S_F_3, 0 }, { BLOCK_COMBI_GRD_S_F_PK_1, 0 }, { BLOCK_COMBI_GRD_S_R1_P_1, 0 }, { BLOCK_COMBI_GRD_S_F_2, 0 },  { BLOCK_COMBI_GRD_S_F_6, 0 }, { BLOCK_COMBI_GRD_S_E3_1, 0 },
    { BLOCK_COMBI_GRD_S_F_9_1, 0 }, { BLOCK_COMBI_GRD_S_F_9_1, 0 }, { BLOCK_COMBI_GRD_S_F_9_1, 0 }, { BLOCK_COMBI_GRD_S_F_9_1, 0 }, { BLOCK_COMBI_GRD_S_F_9_1, 0 }, { BLOCK_COMBI_GRD_S_F_9_1, 0 }, { BLOCK_COMBI_GRD_S_F_9_1, 0 },
    { BLOCK_COMBI_GRD_S_F_9_1, 0 }, { BLOCK_COMBI_GRD_S_F_9_1, 0 }, { BLOCK_COMBI_GRD_S_F_9_1, 0 }, { BLOCK_COMBI_GRD_S_F_9_1, 0 }, { BLOCK_COMBI_GRD_S_F_9_1, 0 }, { BLOCK_COMBI_GRD_S_F_9_1, 0 }, { BLOCK_COMBI_GRD_S_F_9_1, 0 },
    { BLOCK_COMBI_GRD_S_F_9_1, 0 }, { BLOCK_COMBI_GRD_S_F_9_1, 0 }, { BLOCK_COMBI_GRD_S_F_9_1, 0 }, { BLOCK_COMBI_GRD_S_F_9_1, 0 }, { BLOCK_COMBI_GRD_S_F_9_1, 0 }, { BLOCK_COMBI_GRD_S_F_9_1, 0 }, { BLOCK_COMBI_GRD_S_F_9_1, 0 },
    { BLOCK_COMBI_GRD_S_F_9_1, 0 }, { BLOCK_COMBI_GRD_S_F_9_1, 0 }, { BLOCK_COMBI_GRD_S_F_9_1, 0 }, { BLOCK_COMBI_GRD_S_F_9_1, 0 }, { BLOCK_COMBI_GRD_S_F_9_1, 0 }, { BLOCK_COMBI_GRD_S_F_9_1, 0 }, { BLOCK_COMBI_GRD_S_F_9_1, 0 },
    // clang-format on
};

u8* g_block_type_p = l_block_type;
int* g_block_kind_p = l_block_kind;

extern void mFM_InitFgCombiSaveData(GAME* game) {
    GameAlloc* game_alloc_p = NULL;
    void* gamealloc_data_p;
    mFM_fg_data_c* fg_data_p;
    mFM_combo_info_c* combo_info_p;
    mFM_combination_c* combi_table;
    mFM_fg_data_c** sorted_fg_data_list;
    size_t fg_datasize;
    size_t fg_datasize_align;
    mFM_fg_c* fg_block;
    int fg_id;
    mFM_fg_c* fg_block_p;
    int fg_data_num;
    mFM_fg_data_c* src_data;
    int bz;
    int bx;
    int total_fg_block;

    combi_table = Save_Get(combi_table[0]);
    fg_block = Save_Get(fg[0]);
    
// Aus version initializes pointers to NULL for NULL checks
#if VERSION >= VER_GAFU01_00
    gamealloc_data_p = NULL;
    fg_data_p = NULL;
    total_fg_block = 0;
#else
    total_fg_block = 0;
#endif

    if (game != NULL) {
        game_alloc_p = &game->gamealloc;
    }

    combo_info_p = data_combi_table;
    mRF_MakeRandomField(l_combiID, combo_info_p, data_combi_table_number, game);
    mFM_SetBlockKind(g_block_type_p, g_block_kind_p, l_combiID, combo_info_p, BLOCK_TOTAL_NUM);
    mFM_SetCombiTable(combi_table, l_combiID, BLOCK_X_NUM, BLOCK_Z_NUM);
    fg_datasize = JW_GetResSizeFileNo(RESOURCE_FGDATA);
    fg_datasize_align = ALIGN_NEXT(fg_datasize, 32);

    if (game != NULL) {
        gamealloc_data_p = gamealloc_malloc(game_alloc_p, fg_datasize_align + 32);
// Aus version added NULL check
#if VERSION >= VER_GAFU01_00
        if (gamealloc_data_p != NULL) {
            fg_data_p = (mFM_fg_data_c*)(ALIGN_NEXT((uintptr_t)gamealloc_data_p, 32));
        }
#else
        fg_data_p = (mFM_fg_data_c*)(ALIGN_NEXT((uintptr_t)gamealloc_data_p, 32));
#endif
    } else {
        fg_data_p = (mFM_fg_data_c*)zelda_malloc_align(fg_datasize_align, 32);
    }

    fg_data_num = fg_datasize / sizeof(mFM_fg_data_c);
    _JW_GetResourceAram(JW_GetAramAddress(RESOURCE_FGDATA), (u8*)fg_data_p, fg_datasize_align);

#ifdef TARGET_PC
    mFM_ByteSwapFGData(fg_data_p, fg_data_num);
#endif

    if (game != NULL) {
        sorted_fg_data_list = (mFM_fg_data_c**)gamealloc_malloc(game_alloc_p, mFM_FG_NUM * sizeof(mFM_fg_data_c*));
    } else {
        sorted_fg_data_list = (mFM_fg_data_c**)zelda_malloc(mFM_FG_NUM * sizeof(mFM_fg_data_c*));
    }

    mFM_SortFGData(sorted_fg_data_list, fg_data_p, mFM_FG_NUM, fg_data_num, 0);

    fg_block_p = fg_block;
    for (bz = 0; bz < mISL_BLOCK_Z; bz++) {
        for (bx = 0; bx < BLOCK_X_NUM; bx++, combi_table++) {
            if (bz > 0 && bz < (BLOCK_Z_NUM - 3) && bx > 0 && bx < (BLOCK_X_NUM - 1)) {
                if (total_fg_block >= FG_BLOCK_TOTAL_NUM) {
                    break;
                }

                fg_id = combo_info_p[combi_table[0].combination_type].fg_id;
                if (fg_block_p == NULL) {
                    break;
                }

                src_data = sorted_fg_data_list[fg_id];
                if (src_data == NULL) {
                    break;
                }

                if (fg_id >= 0 && fg_id < mFM_FG_NUM) {
                    mFM_FgUtDataSet(fg_block_p->items[0], src_data->items[0]);
                }

                total_fg_block++;
                fg_block_p++;

                if (total_fg_block >= FG_BLOCK_TOTAL_NUM) {
                    break;
                }
            }
        }
    }

    {
        int island_x_blocks[2];

        mFI_GetIslandBlockNumX(island_x_blocks);
        mFM_SetIslandFg(combo_info_p, sorted_fg_data_list, island_x_blocks);
    }

// Aus version added NULL checks
#if VERSION >= VER_GAFU01_00
    if (game != NULL) {
        if (sorted_fg_data_list != NULL) {
            gamealloc_free(game_alloc_p, sorted_fg_data_list);
        }

        if (gamealloc_data_p != NULL) {
            gamealloc_free(game_alloc_p, gamealloc_data_p);
        }
    } else {
        if (sorted_fg_data_list != NULL) {
            zelda_free(sorted_fg_data_list);
        }

        if (fg_data_p != NULL) {
            zelda_free(fg_data_p);
        }
    }
#else
    if (game != NULL) {
        gamealloc_free(game_alloc_p, sorted_fg_data_list);
        gamealloc_free(game_alloc_p, gamealloc_data_p);
    } else {
        zelda_free(sorted_fg_data_list);
        zelda_free(fg_data_p);
    }
#endif
}

static int mFM_AddIdx(int* idx, int min, int max) {
    int res = FALSE;

    (*idx)++;

    if (*idx >= max) {
        *idx = min;
        res = TRUE;
    }

    return res;
}

static mActor_name_t mFM_GetNextReseve(int set, int set_idx, int river_idx, u32 block_kind, int force) {
    int group = set;
    int idx = set_idx;
    mActor_name_t reserve = SIGN00;

    if (force == FALSE && ((block_kind & mRF_BLOCKKIND_RIVER) == mRF_BLOCKKIND_RIVER)) {
        group = 0;
        idx = river_idx;
    }


    reserve += (mActor_name_t)(group * 3 + idx);
    return reserve;
}

static void mFM_RenewalReserveBlock(mActor_name_t* items, int* set, int* set_idx, int* river_idx, u32 block_kind) {
    int force = FALSE;
    int i;

    for (i = 0; i < UT_TOTAL_NUM; i++) {
        if (*items == SIGN00) {
            *items = mFM_GetNextReseve(*set, *set_idx, *river_idx, block_kind, force);

            if (force == FALSE && (block_kind & mRF_BLOCKKIND_RIVER) == mRF_BLOCKKIND_RIVER) {
                mFM_AddIdx(river_idx, 0, 3);
                force = TRUE;
            } else {
                if (mFM_AddIdx(set, 1, 7) == TRUE) {
                    mFM_AddIdx(set_idx, 0, 3);
                }
            }
        }

        items++;
    }
}

extern void mFM_RenewalReserve() {
    mFM_fg_c* fg_block = Save_Get(fg[1]);
    int set = 1;
    int set_idx = 0;
    int river_idx = 0;
    u32 block_kind;
    int block;

    int bx;
    int bz;

    for (bz = 1; bz < FG_BLOCK_Z_NUM; bz++) {
        for (bx = 0; bx < FG_BLOCK_X_NUM; bx++, fg_block++) {
            block_kind = g_block_kind_p[(bz + 1) * BLOCK_X_NUM + (bx + 1)];
// Aus adds NULL check on fg_block
#if VERSION >= VER_GAFU01_00
            if (fg_block == NULL) {
                continue;
            }
#endif
            mFM_RenewalReserveBlock(fg_block->items[0], &set, &set_idx, &river_idx, block_kind);
        }
    }
}

extern mActor_name_t mFM_GetReseveName(int bx, int bz) {
    mActor_name_t* items;
    mActor_name_t reserve_name = SIGN03;
    u32 block_kind;
    int reserve_bit_field = 0;
    u8 reserve_complete_sets_bit_field = 0;
    int free_signs;
    int set = 0;
    int reserve_noncomplete_sets = 0;
    int set_idx = 0;
    int i;

    if (bx > 0 && bx < (BLOCK_X_NUM - 1) && bz > 0 && bz < (BLOCK_Z_NUM - 3)) {
        block_kind = g_block_kind_p[(bz * BLOCK_X_NUM) + bx];
        items = Save_Get(fg[bz - 1][bx - 1]).items[0];

        for (i = 0; i < UT_TOTAL_NUM; i++) {
            if (mNT_IS_RESERVE(items[0])) {
                reserve_bit_field |= (1 << (items[0] - SIGN00));
            }

            items++;
        }

        for (i = 0; i < 7; i++) {
            u32 shift = i * 3;
            if (((reserve_bit_field >> shift) & 0b111) == 0b111) {
                reserve_complete_sets_bit_field |= (1 << i);
            }

            if (((reserve_bit_field >> (i * 3)) & 0b111) != 0b111) {
                reserve_noncomplete_sets++;
            }
        }

        /* Mark river set as unavailable */
        if ((block_kind & mRF_BLOCKKIND_RIVER) != mRF_BLOCKKIND_RIVER && ((reserve_complete_sets_bit_field & 1) == 0)) {
            reserve_complete_sets_bit_field |= 1;
            reserve_noncomplete_sets--;
        }

        /* Select one of the 7 sets of signs */
        {
            int selected_set = RANDOM(reserve_noncomplete_sets);

            for (i = 0; i < 7; i++) {
                if (((reserve_complete_sets_bit_field >> i) & 1) == 0) {
                    if (selected_set <= 0) {
                        set = i;
                        break;
                    } else {
                        selected_set--;
                    }
                }
            }
        }

        /* Count used signs in selected set */
        {
            int subset_start = set * 3;
            int idx;
            int j;
            int selected_idx;
            free_signs = 0;

            for (i = subset_start; i < subset_start + 3; i++) {
                if (((reserve_bit_field >> i) & 1) == 0) {
                    free_signs++;
                }
            }

            /* Select random free sign in set */
            selected_idx = RANDOM(free_signs);
            idx = 0;

            for (j = subset_start; j < subset_start + 3; j++) {
                if (((reserve_bit_field >> j) & 1) == 0) {
                    if (selected_idx <= 0) {
                        idx = j;
                        break;
                    } else {
                        selected_idx--;
                    }
                }
            }

            reserve_name = SIGN00 + idx;
        }
    }

    return reserve_name;
}

extern void mFM_toSummer() {
    mTM_set_season_com(7);

    if (g_fdinfo != NULL) {
        mFM_LoadBGCommonTex(FALSE, Save_Get(island).grass_tex_type);
        mFM_SetFieldPal(&g_fdinfo->field_palette);
    }
}

extern void mFM_returnSeason() {
    mTM_set_season();

    if (g_fdinfo != NULL) {
        mFM_LoadBGCommonTex(FALSE, Save_Get(bg_tex_idx));
        mFM_SetFieldPal(&g_fdinfo->field_palette);
    }
}

extern void mFM_RestoreIslandBG(int* island_x_blocks, int bx_num) {
    mFM_combination_c* combi_p;

    mFM_block_info_c* block_info;
    mFM_bg_data_c** sorted_bg_data;
    mFM_bg_data_c* bg_data_p = data_bgd;
    mFM_combo_info_c* combo_info_p = data_combi_table;

    if (mFI_CheckFieldData() && Save_Get(scene_no) == SCENE_FG) {
        block_info = mFI_GetBlockTopP();

        if (block_info != NULL) {
            int i;
            sorted_bg_data = (mFM_bg_data_c**)zelda_malloc(mFM_BG_ID_MAX * sizeof(mFM_bg_data_c*));

            if (sorted_bg_data != NULL) {
                mFM_SortBGData(sorted_bg_data, bg_data_p, data_bgd_number);
                combi_p = Save_Get(combi_table[mISL_BLOCK_Z] + island_x_blocks[0]);
                block_info += mFI_GetBlockNum(island_x_blocks[0], mISL_BLOCK_Z);

                for (i = 0; i < bx_num; i++) {
                    int bg_id = combo_info_p[combi_p[0].combination_type].bg_id;

                    if (bg_id <= mFM_BG_ID_MAX && sorted_bg_data[bg_id] != NULL) {
                        mFM_SetBG(&block_info->bg_info, sorted_bg_data[bg_id], combi_p->height,
                                  block_info->bg_info.block_type, bg_id, island_x_blocks[i], mISL_BLOCK_Z);
                    }

                    block_info++;
                    combi_p++;
                }

                if (sorted_bg_data != NULL) {
                    zelda_free(sorted_bg_data);
                }
            }
        }
    }
}

extern void mFM_SetIslandNpcRoomData(GAME* game, int malloc_flag) {
    GameAlloc* gamealloc = NULL;
    mFM_fg_data_c** sorted_fgnpc_data_list;

#if VERSION >= VER_GAFU01_00
    void* gamealloc_data_p = NULL;
#else
    void* gamealloc_data_p;
#endif
    mFM_fg_data_c* fgnpc_data_p;
    size_t fgnpc_size = JW_GetResSizeFileNo(RESOURCE_FGNPCDATA);
    size_t fgnpc_size_align = ALIGN_NEXT(fgnpc_size, 32);
    int fgnpc_data_num;

    if (game != NULL) {
        gamealloc = &game->gamealloc;
    }

    if (malloc_flag == TRUE) {
        fgnpc_data_p = (mFM_fg_data_c*)zelda_malloc_align(fgnpc_size_align, 32);
    } else if (game != NULL) {
        gamealloc_data_p = gamealloc_malloc(gamealloc, fgnpc_size_align + 32);
        fgnpc_data_p = (mFM_fg_data_c*)(ALIGN_NEXT((uintptr_t)gamealloc_data_p, 32));
    } else {
        fgnpc_data_p = (mFM_fg_data_c*)zelda_malloc_align(fgnpc_size_align, 32);
    }

    if (fgnpc_data_p != NULL) {
        fgnpc_data_num = fgnpc_size / sizeof(mFM_fg_data_c);
        _JW_GetResourceAram(JW_GetAramAddress(RESOURCE_FGNPCDATA), (u8*)fgnpc_data_p, fgnpc_size_align);

#ifdef TARGET_PC
        mFM_ByteSwapFGData(fgnpc_data_p, fgnpc_data_num);
#endif

        if (malloc_flag == TRUE) {
            sorted_fgnpc_data_list = (mFM_fg_data_c**)zelda_malloc(mFM_FG_NPC_NUM * sizeof(mFM_fg_data_c*));
        } else if (game != NULL) {
            sorted_fgnpc_data_list =
                (mFM_fg_data_c**)gamealloc_malloc(gamealloc, mFM_FG_NPC_NUM * sizeof(mFM_fg_data_c*));
        } else {
            sorted_fgnpc_data_list = (mFM_fg_data_c**)zelda_malloc(mFM_FG_NPC_NUM * sizeof(mFM_fg_data_c*));
        }

        if (sorted_fgnpc_data_list != NULL) {
            mFM_SortFGData(sorted_fgnpc_data_list, fgnpc_data_p, mFM_FG_NPC_NUM, fgnpc_data_num, mFM_FG_NPC_START);
            mNpc_IslandNpcRoomDataSet(sorted_fgnpc_data_list, mFM_FG_NPC_START);

            if (sorted_fgnpc_data_list != NULL) {
                if (malloc_flag == TRUE) {
                    zelda_free(sorted_fgnpc_data_list);
                } else if (game != NULL) {
                    gamealloc_free(gamealloc, sorted_fgnpc_data_list);
                } else {
                    zelda_free(sorted_fgnpc_data_list);
                }
            }
        }

#if VERSION >= VER_GAFU01_00
        if (fgnpc_data_p != NULL) {
            if (malloc_flag == TRUE || game == NULL) {
                zelda_free(fgnpc_data_p);
            }
        }

        if (gamealloc_data_p != NULL) {
            gamealloc_free(gamealloc, gamealloc_data_p);
        }
#else
        /* @BUG - memory leak if gamealloc malloc path is not taken above */
#ifndef BUGFIXES
        if (gamealloc_data_p != NULL) {
#else
        if (fgnpc_data_p != NULL) { // this is guaranteed to exist in all malloc paths
#endif
            if (malloc_flag == TRUE) {
                zelda_free(fgnpc_data_p);
            } else if (game != NULL) {
                gamealloc_free(gamealloc, gamealloc_data_p);
            } else {
                zelda_free(fgnpc_data_p);
            }
        }
#endif
    }
}
