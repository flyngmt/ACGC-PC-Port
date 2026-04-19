#include "m_scene.h"

#include "m_player_lib.h"
#include "libultra/libultra.h"
#include "jsyswrap.h"
#include "m_play.h"
#include "m_common_data.h"
#include "m_npc.h"
#include "m_name_table.h"
#include "m_card.h"
#include "m_submenu.h"
#include "m_scene_ftr.h"

static void mSc_set_bank_status_after(Object_Bank_c* bank) {
    bank->bank_id = ABS(bank->bank_id);
    bank->ram_start = bank->dma_start;
    bank->state = 0;
}

static void mSc_clear_bank_status(Object_Bank_c* bank) {
    bank->bank_id = 0;
    bank->size = 0;
    bank->dma_start = NULL;
    bank->ram_start = NULL;
}

static void Object_Exchange_keep_new_Player(GAME_PLAY* play) {
    mPlib_Object_Exchange_keep_new_PlayerMdl(play);
    mPlib_Object_Exchange_keep_new_PlayerTex(play, 0, 0);
    mPlib_Object_Exchange_keep_new_PlayerPallet(play, 0, 0);
    mPlib_Object_Exchange_keep_new_PlayerTex(play, 1, 2);
    mPlib_Object_Exchange_keep_new_PlayerPallet(play, 1, 2);
    mPlib_Object_Exchange_keep_new_PlayerFaceTex(play);
    mPlib_Object_Exchange_keep_new_PlayerFacePallet(play, 1, 0);
    mPlib_Object_Exchange_keep_new_PlayerFacePallet(play, 2, 1);
}

extern char* mSc_secure_exchange_keep_bank(Object_Exchange_c* exchange, s16 bank_id, size_t size) {
    char* area = NULL;
    Object_Bank_c* bank = exchange->banks + exchange->bank_idx;

    if (exchange->bank_idx < mSc_OBJECT_BANK_NUM) {
        area = (char*)ALIGN_NEXT((uintptr_t)exchange->next_bank_ram_address + size, 32);

        if (area >= exchange->max_ram_address) {
            area = NULL;
        } else {
            bank->bank_id = bank_id;
            bank->ram_start = exchange->next_bank_ram_address;
            bank->dma_start = exchange->next_bank_ram_address;
            bank->rom_addr = 0;
            bank->size = size;
            bank->num_exist = 0;
            bank->state = 3;

            exchange->next_bank_ram_address = area;
            exchange->bank_idx++;
        }
    }

    return area;
}

extern void mSc_background_dmacopy_controller(Object_Bank_c* bank) {
    switch (bank->state) {
        case 1: {
            if (bank->_14 == 0) {
                osCreateMesgQueue(&bank->dma_controller_msg_queue, &bank->dma_controller_msg, 1);
                _JW_GetResourceAram(bank->rom_addr, (u8*)bank->dma_start, bank->size);
                DCStoreRangeNoSync(bank->dma_start, bank->size);
                bank->state = 0;
            }

            break;
        }

        case 2: {
            if (osRecvMesg(&bank->dma_controller_msg_queue, NULL, OS_MESSAGE_NOBLOCK) == FALSE) {
                mSc_set_bank_status_after(bank);
            }

            break;
        }
    }
}

extern void mSc_dmacopy_data_bank(Object_Exchange_c* exchange) {
    /* stubbed */
}

extern int mSc_bank_regist_check(Object_Exchange_c* exchange, s16 bank_id) {
    int res = -1;
    int i;

    for (i = 0; i < mSc_OBJECT_BANK_NUM; i++) {
        if (ABS(exchange->banks[i].bank_id) == bank_id) {
            res = i;

            break;
        }
    }

    return res;
}

extern void mSc_regist_initial_exchange_bank(GAME_PLAY* play) {
    play->object_exchange.selected_partition = 0;
    play->object_exchange.exchange_id = play->object_exchange.bank_idx;

    if (Common_Get(field_type) == mFI_FIELDTYPE2_FG) {
        u32 size;

        /* Split the remaining object exchange space into two equal portions */
        size = (size_t)(play->object_exchange.max_ram_address - play->object_exchange.next_bank_ram_address) / 2;
        play->object_exchange.start_address_save[0] = play->object_exchange.next_bank_ram_address;
        play->object_exchange.end_address_save[0] =
            (char*)ALIGN_NEXT((uintptr_t)play->object_exchange.next_bank_ram_address + size, 32);

        play->object_exchange.start_address_save[1] = play->object_exchange.end_address_save[0];
        play->object_exchange.end_address_save[1] = play->object_exchange.max_ram_address;

        /* Temporarily limit the maximum address to half the remaining free space */
        play->object_exchange.max_ram_address = play->object_exchange.end_address_save[0];
    } else {
        play->object_exchange.start_address_save[0] = play->object_exchange.next_bank_ram_address;
        play->object_exchange.end_address_save[0] = play->object_exchange.max_ram_address;

        play->object_exchange.start_address_save[1] = play->object_exchange.next_bank_ram_address;
        play->object_exchange.end_address_save[1] = play->object_exchange.max_ram_address;
    }

    play->object_exchange.exchange_id = play->object_exchange.bank_idx; /* leftover from DnM? */
}

static void mSc_dmacopy_all_exchange_bank_sub(Object_Bank_c* bank, Object_Exchange_c* exchange, int idx) {
    if (idx >= exchange->exchange_id) {
        char* area = (char*)ALIGN_NEXT((uintptr_t)exchange->next_bank_ram_address + bank->size, 32);

        if (area >= exchange->max_ram_address) {
            exchange->selected_partition = (exchange->selected_partition + 1) % 2;
            exchange->next_bank_ram_address = exchange->start_address_save[exchange->selected_partition];
            exchange->max_ram_address = exchange->end_address_save[exchange->selected_partition];

            area = (char*)ALIGN_NEXT((uintptr_t)exchange->next_bank_ram_address + bank->size, 32);
        }

        bank->dma_start = exchange->next_bank_ram_address;
        bank->part_id = exchange->selected_partition;
        exchange->next_bank_ram_address = area;
    }

    _JW_GetResourceAram(bank->rom_addr, (u8*)bank->dma_start, bank->size);
    DCStoreRangeNoSync(bank->dma_start, bank->size);
    mSc_set_bank_status_after(bank);
}

extern void mSc_dmacopy_all_exchange_bank(Object_Exchange_c* exchange) {
    Object_Bank_c* bank;
    int i;

    bank = exchange->banks + exchange->keep_id;
    exchange->next_bank_ram_address = exchange->start_address_save[exchange->selected_partition];

    for (i = exchange->keep_id; i < mSc_OBJECT_BANK_NUM; i++) {
        if (bank->bank_id != 0 && bank->state != 3) {
            if (bank->bank_id < 0) {
                mSc_dmacopy_all_exchange_bank_sub(bank, exchange, i);
            } else if (bank->num_exist != 0) {
                mSc_dmacopy_all_exchange_bank_sub(bank, exchange, i);
            } else if (i >= exchange->exchange_id) {
                mSc_clear_bank_status(bank);
            } else {
                bank->bank_id = 0;
            }
        }

        bank++;
    }

    if (Common_Get(clip).npc_clip != NULL) {
        Common_Get(clip).npc_clip->rebuild_dma_proc();
    }

    if (Common_Get(clip)._068 != NULL) {
        (*Common_Get(clip)._068)();
    }

    if (Common_Get(clip).shop_manekin_clip != NULL) {
        Common_Get(clip).shop_manekin_clip->manekin_dma_again_proc();
    }

    if (Common_Get(clip).shop_indoor_clip != NULL) {
        Common_Get(clip).shop_indoor_clip->indoor_dma_again_proc();
    }

    if (Common_Get(clip).my_room_clip != NULL) {
        Common_Get(clip).my_room_clip->redma_ftr_bank_proc();
    }

    if (Common_Get(clip).my_indoor_clip != NULL) {
        Common_Get(clip).my_indoor_clip->indoor_dma_again_proc();
    }

    if (Common_Get(clip).arrange_room_clip != NULL) {
        Common_Get(clip).arrange_room_clip->redma_proc();
    }

    if (Common_Get(clip).shop_umbrella_clip != NULL) {
        Common_Get(clip).shop_umbrella_clip->umbrella_dma_again_proc();
    }

    if (Common_Get(clip).ball_redma_proc != NULL) {
        (*Common_Get(clip).ball_redma_proc)();
    }
}

extern void mSc_data_bank_ct(GAME_PLAY* play, Object_Exchange_c* exchange) {
    char* exchange_arena;

    bzero(exchange, sizeof(Object_Exchange_c));

    exchange->keep_id = -1;
    exchange->exchange_id = -1;

    exchange_arena = (char*)THA_allocAlign(&play->game.tha, mSc_ARENA_SIZE, ~0x1F);
    exchange->next_bank_ram_address = exchange_arena;
    exchange->start_address_save[0] = exchange_arena;
    exchange->start_address_save[1] = exchange_arena;

    exchange_arena += mSc_ARENA_SIZE;
    exchange->max_ram_address = exchange_arena;
    exchange->end_address_save[0] = exchange_arena;
    exchange->end_address_save[1] = exchange_arena;
}

extern void mSc_decide_exchange_bank(Object_Exchange_c* exchange) {
    exchange->keep_id = exchange->bank_idx;
    exchange->_194C = exchange->next_bank_ram_address;
}

static void Scene_player_select(int scene_no, int npc_actor) {
    if (Save_Get(scene_no) == scene_no) {
        int met_villagers_bitfield = 0;
        int met_villagers_num = 0;
        mActor_name_t npc_id;
        Animal_c* animal = Save_Get(animals);
        Anmmem_c* memory;
        int i;
        int j;
        int selected;

        /* Track all villagers who have met a player from town before */
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
                memory = animal->memories;

                for (j = 0; j < ANIMAL_MEMORY_NUM; j++) {
                    if (memory->memory_player_id.land_id == Save_Get(land_info).id &&
                        mLd_CheckCmpLandName(memory->memory_player_id.land_name, Save_Get(land_info).name) == TRUE) {
                        met_villagers_bitfield |= (1 << i);
                        met_villagers_num++;

                        break;
                    }

                    memory++;
                }
            }

            animal++;
        }

        /* Roll a random villager if none have met a player in town before */
        if (met_villagers_num == 0) {
            do {
                selected = RANDOM(ANIMAL_NUM_MAX);
            } while (mNpc_CheckFreeAnimalPersonalID(&Save_Get(animals[selected]).id));

            npc_id = Save_Get(animals[selected]).id.npc_id;
            i = mNpc_SearchAnimalinfo(Save_Get(animals), npc_id, ANIMAL_NUM_MAX);
        } else {
            /* Pick a random villager which has met a player in town */

            selected = RANDOM(met_villagers_num);

            for (i = 0; i < ANIMAL_NUM_MAX; i++) {
                if ((met_villagers_bitfield & 1) != 0) {
                    if (selected == 0) {
                        break;
                    } else {
                        selected--;
                    }
                }

                met_villagers_bitfield >>= 1;
            }

            npc_id = Save_Get(animals[i]).id.npc_id;
        }

        if (scene_no == SCENE_PLAYERSELECT_2) {
            Common_Set(player_select_animal_no, i);
        }

        mNpc_RegistEventNpc(npc_actor, npc_id, npc_id, Save_Get(animals[i]).cloth);
    }
}

static void Scene_Proc_Player_Ptr(GAME_PLAY* play, Scene_Word_u* data);
static void Scene_Proc_Ctrl_Actor_Ptr(GAME_PLAY* play, Scene_Word_u* data);
static void Scene_Proc_Actor_Ptr(GAME_PLAY* play, Scene_Word_u* data);
static void Scene_Proc_Object_Exchange_Bank_Ptr(GAME_PLAY* play, Scene_Word_u* data);
static void Scene_Proc_Door_Data_Ptr(GAME_PLAY* play, Scene_Word_u* data);
static void Scene_Proc_Field_ct(GAME_PLAY* play, Scene_Word_u* data);
static void Scene_Proc_MyRoom_ct(GAME_PLAY* play, Scene_Word_u* data);
static void Scene_Proc_ArrangeRoom_ct(GAME_PLAY* play, Scene_Word_u* data);
static void Scene_Proc_ArrangeFurniture_ct(GAME_PLAY* play, Scene_Word_u* data);
static void Scene_Proc_Sound(GAME_PLAY* play, Scene_Word_u* data);

typedef void (*mSc_SCENE_WORD_PROC)(GAME_PLAY*, Scene_Word_u*);

extern void Scene_ct(GAME_PLAY* play, Scene_Word_u* scene_data) {
    static mSc_SCENE_WORD_PROC Scene_Proc[mSc_SCENE_DATA_TYPE_NUM] = {
        &Scene_Proc_Player_Ptr,
        &Scene_Proc_Ctrl_Actor_Ptr,
        &Scene_Proc_Actor_Ptr,
        &Scene_Proc_Object_Exchange_Bank_Ptr,
        &Scene_Proc_Door_Data_Ptr,
        &Scene_Proc_Field_ct,
        &Scene_Proc_MyRoom_ct,
        &Scene_Proc_ArrangeRoom_ct,
        &Scene_Proc_ArrangeFurniture_ct,
        &Scene_Proc_Sound,
        NULL,
    };

    /* Initialize all scene data */
    while (TRUE) {
        u32 type = scene_data->misc.type;

        if (type == mSc_SCENE_DATA_TYPE_END) {
            break;
        }

        if (type < mSc_SCENE_DATA_TYPE_NUM) {
            (*Scene_Proc[type])(play, scene_data);
        }

        scene_data++;
    }

    /* Setup player select actors */
    Scene_player_select(SCENE_PLAYERSELECT_2, SP_NPC_P_SEL2);     // load
    Scene_player_select(SCENE_PLAYERSELECT_SAVE, SP_NPC_RESTART); // save

    /* Select Rover or Blanca for visiting town scene */
    if (Save_Get(scene_no) == SCENE_START_DEMO3) {
        int rover_shown = FALSE;

        if (mLd_CheckCmpLand(Common_Get(now_private)->player_ID.land_name, Common_Get(now_private)->player_ID.land_id,
                             Common_Get(travel_persistent_data).land.name,
                             Common_Get(travel_persistent_data).land.id) == TRUE) {
            if (Common_Get(now_private)->state_flags & mPr_FLAG_MASK_CAT_SCHEDULED) {
                Common_Get(now_private)->state_flags &= ~mPr_FLAG_MASK_CAT_SCHEDULED;
                rover_shown = TRUE;
            } else if (fqrand() < 0.5f) {
                Common_Get(now_private)->state_flags |= mPr_FLAG_MASK_CAT_SCHEDULED; // Blanca is scheduled
            } else {
                Common_Get(now_private)->state_flags &= ~mPr_FLAG_MASK_CAT_SCHEDULED;
                rover_shown = TRUE;
            }
        } else {
            rover_shown = TRUE;
        }

        if (rover_shown == FALSE) {
            mActor_name_t blanca_cloth;

            mSP_SelectRandomItem_New(NULL, &blanca_cloth, 1, NULL, 0, mSP_KIND_CLOTH, mSP_LISTTYPE_ABC, FALSE);
            mNpc_RegistMaskNpc(SP_NPC_MASK_CAT2, SP_NPC_MASK_CAT2, blanca_cloth);
            Save_Get(mask_cat).cloth_no = (blanca_cloth >= ITM_CLOTH_START && blanca_cloth < ITM_CLOTH_END)
                                              ? (blanca_cloth - ITM_CLOTH_START)
                                              : EMPTY_NO;
        } else {
            mNpc_RegistMaskNpc(SP_NPC_MASK_CAT2, SP_NPC_GUIDE, EMPTY_NO); // Rover
        }
    }
}

static void Scene_Proc_Player_Ptr(GAME_PLAY* play, Scene_Word_u* scene_data) {
    static s16 angle_table[mSc_DIRECT_NUM] = {
        DEG2SHORT_ANGLE(0.0f),    /* 0x0000 */
        DEG2SHORT_ANGLE(45.0f),   /* 0x2000 */
        DEG2SHORT_ANGLE(90.0f),   /* 0x4000 */
        DEG2SHORT_ANGLE(135.0f),  /* 0x6000 */
        DEG2SHORT_ANGLE(-180.0f), /* 0x8000 */
        DEG2SHORT_ANGLE(-135.0f), /* 0xA000 */
        DEG2SHORT_ANGLE(-90.0f),  /* 0xC000 */
        DEG2SHORT_ANGLE(-45.0f)   /* 0xE000 */
    };

    Actor_data* data = scene_data->actor.data_p;

    play->player_data = data;

    /* Update player position & orientation based on the current door exit data */
    if (Common_Get(door_data).next_scene_id != 0) {
        mem_copy((u8*)&data->position, (u8*)&Common_Get(door_data).exit_position, sizeof(s_xyz));
        data->rotation.y = angle_table[Common_Get(door_data).exit_orientation];
    }

    data->arg = Common_Get(door_data).extra_data;
    Object_Exchange_keep_new_Player(play);
    mSM_Object_Exchange_keep_new_Menu(play);
}

static void Scene_Proc_Ctrl_Actor_Ptr(GAME_PLAY* play, Scene_Word_u* scene_data) {
    s16* data = scene_data->control_actor.ctrl_actor_profile_p;

    play->ctrl_actor_data_num = scene_data->control_actor.num_ctrl_actors;
    play->ctrl_actor_data = data;
}

static void Scene_Proc_Actor_Ptr(GAME_PLAY* play, Scene_Word_u* scene_data) {
    Actor_data* data_p = scene_data->actor.data_p;

    play->actor_data_num = scene_data->actor.num_actors;
    play->actor_data = data_p;
}

static void Scene_Proc_Object_Exchange_Bank_Ptr(GAME_PLAY* play, Scene_Word_u* scene_data) {
    play->obj_bank_data_num = scene_data->object_bank.num_banks;
    play->obj_bank_data = scene_data->object_bank.banks_p;
}

static void Scene_Proc_Door_Data_Ptr(GAME_PLAY* play, Scene_Word_u* scene_data) {
    Door_data_c* data_p = scene_data->door_data.door_data_p;

    play->door_info.num_doors = scene_data->door_data.num_doors;
    play->door_info.door_data_p = data_p;
}

extern void Door_info_ct(Door_info_c* door_info) {
    door_info->num_doors = 0;
}

static void Scene_Proc_Sound(GAME_PLAY* play, Scene_Word_u* scene_data) {
    // stubbed
}

static void set_item_info(GAME_PLAY* play, Scene_Word_Data_FieldCt_c* field_ct) {
    static s16 profile_table[4] = {
        mAc_PROFILE_BGITEM,
        mAc_PROFILE_DUMMY,
        mAc_PROFILE_BGPOLICEITEM,
        mAc_PROFILE_BGPOSTITEM,
    };

    int item_type = field_ct->item_type;

    if (item_type == 0) {
        Common_Set(bg_item_profile, Common_Get(time).bgitem_profile);
    } else {
        Common_Set(bg_item_profile, profile_table[item_type]);
    }

    Common_Set(bg_item_type, item_type);
}

static void Scene_Proc_Field_ct(GAME_PLAY* play, Scene_Word_u* scene_data) {
#ifdef TARGET_PC
    /* mSc_DATA_FIELDCT packs (bg_disp_size<<16 | room_type<<8 | draw_type) into misc.param3.
       On GC (big-endian), reading through field_ct struct gives correct values.
       On LE x86, the byte order is wrong. Extract from param3 directly. */
    u32 packed = scene_data->misc.param3;
    u16 bg_disp_size = (packed >> 16) & 0xFFFF;
    u8 room_type = (packed >> 8) & 0xFF;
    u8 draw_type = packed & 0xFF;
    u8 bg_num = scene_data->misc.param1;
    Scene_Word_Data_FieldCt_c fixed_ct;
    fixed_ct.type = scene_data->misc.type;
    fixed_ct.item_type = scene_data->misc.param0;
    fixed_ct.bg_num = bg_num;
    fixed_ct.bg_disp_size = bg_disp_size;
    fixed_ct.room_type = room_type;
    fixed_ct.draw_type = draw_type;
    mFM_SetFieldInitData(bg_num, bg_disp_size);
    set_item_info(play, &fixed_ct);
    Common_Set(field_draw_type, draw_type);
#else
    mFM_SetFieldInitData(scene_data->field_ct.bg_num, scene_data->field_ct.bg_disp_size);
    set_item_info(play, &scene_data->field_ct);
    Common_Set(field_draw_type, scene_data->field_ct.draw_type);
#endif
    Common_Set(game_started, FALSE);
    Common_Set(in_initial_block, TRUE);
    Common_Set(sunlight_flag, TRUE);
}

static void Scene_Proc_MyRoom_ct(GAME_PLAY* play, Scene_Word_u* scene_data) {
    mScn_ObtainMyRoomBank(play);
}

static void Scene_Proc_ArrangeRoom_ct(GAME_PLAY* play, Scene_Word_u* scene_data) {
    mScn_ObtainCarpetBank(play);
}

static void Scene_Proc_ArrangeFurniture_ct(GAME_PLAY* play, Scene_Word_u* scene_data) {
    Common_Get(clip).arrange_ftr_num = scene_data->arrange_ftr_ct.arrange_ftr_num;
}

extern int goto_other_scene(GAME_PLAY* play, Door_data_c* door_data, int update_player_mode) {
    PLAYER_ACTOR* player = get_player_actor_withoutCheck(play);
    int res = 0; // failed

    if (player != NULL) {
        if (play->fb_wipe_mode == WIPE_MODE_NONE) {
            play->fb_fade_type = FADE_TYPE_OUT;

            if (door_data->wipe_type == WIPE_TYPE_NORMAL) {
                play->fb_wipe_type = WIPE_TYPE_FADE_BLACK;
            } else {
                play->fb_wipe_type = door_data->wipe_type;
            }

            if (Common_Get(transition).wipe_type == 0xFF) {
                Common_Get(transition).wipe_type = play->fb_wipe_type;
            }

            Common_Set(door_data, *door_data);
            Common_Get(door_data).next_scene_id = door_data->next_scene_id + 1;
            play->next_scene_no = door_data->next_scene_id;

            if (update_player_mode) {
                mPlib_request_main_invade_type1((GAME*)play);
            }

            restore_fgdata_all(play);
            play->game.pad_initialized = FALSE;
            res = 1; // success
        } else {
            res = 2; // already changing scenes
        }
    }

    return res;
}

extern int goto_next_scene(GAME_PLAY* play, int next_idx, int update_player_mode) {
    int res = FALSE;

    if (play->door_info.num_doors != 0) {
        res = goto_other_scene(play, play->door_info.door_data_p + next_idx, update_player_mode);
    }

    return res;
}

extern int goto_emu_game(GAME* game, s16 famicom_rom_id) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    PLAYER_ACTOR* player = get_player_actor_withoutCheck(play);
    int res = FALSE;

    if (player != NULL) {
        Door_data_c* door_data;

        play->fb_fade_type = FADE_TYPE_OUT_START_EMU;
        play->fb_wipe_type = WIPE_TYPE_FADE_BLACK;
        res = TRUE;

        door_data = Common_GetPointer(famicom_emu_exit_door_data);
        door_data->next_scene_id = Save_Get(scene_no);
        door_data->exit_orientation = 0;
        door_data->exit_type = 0;
        door_data->extra_data = 0;
        door_data->exit_position.x = player->actor_class.world.position.x;
        door_data->exit_position.y = player->actor_class.world.position.y;
        door_data->exit_position.z = player->actor_class.world.position.z;
        door_data->door_actor_name = EMPTY_NO;
        Common_Set(current_famicom_rom, famicom_rom_id);
    }

    return res;
}

extern void return_emu_game(GAME* game) {
    mem_copy((u8*)Common_GetPointer(door_data), (u8*)Common_GetPointer(famicom_emu_exit_door_data),
             sizeof(Door_data_c)); // copy exit door data
    Common_Get(door_data).next_scene_id = Common_Get(famicom_emu_exit_door_data).next_scene_id + 1;
    game->pad_initialized = FALSE;
    game_goto_next_game_play(game);
    Save_Set(scene_no, Common_Get(famicom_emu_exit_door_data).next_scene_id);
}
