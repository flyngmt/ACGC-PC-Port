#ifndef M_SCENE_H
#define M_SCENE_H

#include "types.h"
#include "m_actor.h"
#include "m_lib.h"
#include "famicom_emu.h"
#include "m_scene_table.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mSc_ARENA_SIZE 0xA000

enum {
    mSc_DIRECT_SOUTH,
    mSc_DIRECT_SOUTH_EAST,
    mSc_DIRECT_EAST,
    mSc_DIRECT_NORTH_EAST,
    mSc_DIRECT_NORTH,
    mSc_DIRECT_NORTH_WEST,
    mSc_DIRECT_WEST,
    mSc_DIRECT_SOUTH_WEST,

    mSc_DIRECT_NUM
};

enum {
    mSc_ITEM_TYPE_BGITEM,
    mSc_ITEM_TYPE_DUMMY,
    mSc_ITEM_TYPE_BGPOLICEITEM,
    mSc_ITEM_TYPE_BGPOSTITEM,

    mSc_ITEM_TYPE_NUM
};

enum {
    mSc_ROOM_TYPE_OUTDOORS,
    mSc_ROOM_TYPE_MY_ROOM,
    mSc_ROOM_TYPE_NPC_ROOM,
    mSc_ROOM_TYPE_MISC_ROOM,

    mSc_ROOM_TYPE_NUM
};

typedef struct door_data_s {
    /* 0x00 */ int next_scene_id;
    /* 0x04 */ u8 exit_orientation;
    /* 0x05 */ u8 exit_type; // 0 = normal, 1 = restart game?
    /* 0x06 */ u16 extra_data;
    /* 0x08 */ s_xyz exit_position;
    /* 0x0E */ mActor_name_t door_actor_name;
    /* 0x10 */ u8 wipe_type;
    /* 0x11 */ u8 pad[3]; // possibly necessary due to struct copy
} Door_data_c;

#define mSc_OBJECT_BANK_NUM 70
#define mSC_BANK_NONE 0xFF

typedef struct object_bank_s {
    s16 bank_id;
    char* ram_start;
    char* dma_start;
    u32 rom_addr;
    size_t size;
    u32 _14;
    int _18;
    int _1C;
    int _20;
    int _24;
    int _28;
    OSMessageQueue* msg_queue_p;
    OSMessage _30_msg;
    OSMessageQueue dma_controller_msg_queue;
    OSMessage dma_controller_msg;
    s16 num_exist;
    u8 part_id;
    u8 state;
} Object_Bank_c;

typedef struct object_exchange_s {
    Object_Bank_c banks[mSc_OBJECT_BANK_NUM];
    int bank_idx;
    int keep_id;
    int exchange_id;
    char* next_bank_ram_address;
    char* max_ram_address;
    char* start_address_save[2];
    char* end_address_save[2];
    char* _194C;
    int selected_partition;
    int _1954;
} Object_Exchange_c;

enum {
    mSc_SCENE_DATA_TYPE_PLAYER_PTR,
    mSc_SCENE_DATA_TYPE_CTRL_ACTOR_PTR,
    mSc_SCENE_DATA_TYPE_ACTOR_PTR,
    mSc_SCENE_DATA_TYPE_OBJECT_EXCHANGE_BANK_PTR,
    mSc_SCENE_DATA_TYPE_DOOR_DATA_PTR,
    mSc_SCENE_DATA_TYPE_FIELD_CT,
    mSc_SCENE_DATA_TYPE_MY_ROOM_CT,
    mSc_SCENE_DATA_TYPE_ARRANGE_ROOM_CT,
    mSc_SCENE_DATA_TYPE_ARRANGE_FURNITURE_CT,
    mSc_SCENE_DATA_TYPE_SOUND,
    mSc_SCENE_DATA_TYPE_END,

    mSc_SCENE_DATA_TYPE_NUM
};

typedef struct {
    /* 0x00 */ u8 type;
    /* 0x01 */ u8 num_actors;
    /* 0x04 */ Actor_data* data_p;
} Scene_Word_Data_Actor_c;

typedef struct {
    /* 0x00 */ u8 type;
    /* 0x01 */ u8 num_ctrl_actors;
    /* 0x04 */ s16* ctrl_actor_profile_p;
} Scene_Word_Data_Ctrl_Actor_c;

typedef struct {
    /* 0x00 */ u8 type;
    /* 0x01 */ u8 num_banks;
    /* 0x04 */ s16* banks_p;
} Scene_Word_Data_Object_Bank_c;

typedef struct {
    /* 0x00 */ u8 type;
    /* 0x01 */ u8 num_doors;
    /* 0x04 */ Door_data_c* door_data_p;
} Scene_Word_Data_Door_Data_c;

typedef struct {
    /* 0x00 */ u8 type;
    /* 0x01 */ u8 item_type;
    /* 0x02 */ u8 bg_num;
    /* 0x04 */ u16 bg_disp_size;
    /* 0x06 */ u8 room_type;
    /* 0x07 */ u8 draw_type;
} Scene_Word_Data_FieldCt_c;

typedef struct {
    /* 0x00 */ u8 type;
    /* 0x01 */ u8 arrange_ftr_num;
} Scene_Word_Data_ArrangeFurniture_ct_c;

typedef struct {
    /* 0x00 */ u8 type;
    /* 0x01 */ u8 param0;
    /* 0x02 */ u8 param1;
    /* 0x03 */ u8 param2;
    /* 0x04 */ u32 param3;
} Scene_Word_Data_Misc_c;

typedef union scene_word_u {
    Scene_Word_Data_Misc_c misc;   /* MY_ROOM_CT, ARRANGE_ROOM_CT, ARRANGE_FURNITURE_CT, SOUND */
    Scene_Word_Data_Actor_c actor; /* PLAYER_PTR, ACTOR_PTR */
    Scene_Word_Data_Ctrl_Actor_c control_actor;
    Scene_Word_Data_Object_Bank_c object_bank;
    Scene_Word_Data_Door_Data_c door_data;
    Scene_Word_Data_FieldCt_c field_ct;
    Scene_Word_Data_ArrangeFurniture_ct_c arrange_ftr_ct;
} Scene_Word_u;

#ifdef TARGET_PC
/* On PC (especially 64-bit), use the properly-typed union members
 * instead of casting pointers to u32 via the Misc_c layout */
#define mSc_DATA_PLAYER(actor_data_p)                               \
    { .actor = { mSc_SCENE_DATA_TYPE_PLAYER_PTR, 1, actor_data_p } }

#define mSc_DATA_CTRL_ACTORS(n_actors, ctrl_actor_list_p)           \
    { .control_actor = { mSc_SCENE_DATA_TYPE_CTRL_ACTOR_PTR, n_actors, ctrl_actor_list_p } }

#define mSc_DATA_ACTORS(n_actors, actor_data_p)                     \
    { .actor = { mSc_SCENE_DATA_TYPE_ACTOR_PTR, n_actors, actor_data_p } }

#define mSc_DATA_OBJ_BANK(n_banks, bank_list_p)                    \
    { .object_bank = { mSc_SCENE_DATA_TYPE_OBJECT_EXCHANGE_BANK_PTR, n_banks, bank_list_p } }

#define mSc_DATA_DOOR_DATA(n_doors, door_data_list_p)               \
    { .door_data = { mSc_SCENE_DATA_TYPE_DOOR_DATA_PTR, n_doors, door_data_list_p } }
#else
#define mSc_DATA_PLAYER(actor_data_p)                               \
    {                                                               \
        mSc_SCENE_DATA_TYPE_PLAYER_PTR, 1, 0, 0, (u32)actor_data_p, \
    }

#define mSc_DATA_CTRL_ACTORS(n_actors, ctrl_actor_list_p)                           \
    {                                                                               \
        mSc_SCENE_DATA_TYPE_CTRL_ACTOR_PTR, n_actors, 0, 0, (u32)ctrl_actor_list_p, \
    }

#define mSc_DATA_ACTORS(n_actors, actor_data_p)                           \
    {                                                                     \
        mSc_SCENE_DATA_TYPE_ACTOR_PTR, n_actors, 0, 0, (u32)actor_data_p, \
    }

#define mSc_DATA_OBJ_BANK(n_banks, bank_list_p)                                        \
    {                                                                                  \
        mSc_SCENE_DATA_TYPE_OBJECT_EXCHANGE_BANK_PTR, n_banks, 0, 0, (u32)bank_list_p, \
    }

#define mSc_DATA_DOOR_DATA(n_doors, door_data_list_p)                            \
    {                                                                            \
        mSc_SCENE_DATA_TYPE_DOOR_DATA_PTR, n_doors, 0, 0, (u32)door_data_list_p, \
    }
#endif

#define mSc_DATA_FIELDCT(item_type, bg_num, bg_disp_size, room_type, draw_type)                  \
    {                                                                                            \
        mSc_SCENE_DATA_TYPE_FIELD_CT,                                                            \
        item_type,                                                                               \
        bg_num,                                                                                  \
        0,                                                                                       \
        ((((u32)bg_disp_size & 0xFFFF) << 16) | ((room_type & 0xFF) << 8) | (draw_type & 0xFF)), \
    }

#define mSc_DATA_MY_ROOM_CT()                       \
    {                                               \
        mSc_SCENE_DATA_TYPE_MY_ROOM_CT, 0, 0, 0, 0, \
    }

#define mSc_DATA_ARRANGE_ROOM_CT()                       \
    {                                                    \
        mSc_SCENE_DATA_TYPE_ARRANGE_ROOM_CT, 0, 0, 0, 0, \
    }

#define mSc_DATA_ARRANGE_FTR(ftr_num)                               \
    {                                                               \
        mSc_SCENE_DATA_TYPE_ARRANGE_FURNITURE_CT, ftr_num, 0, 0, 0, \
    }

#define mSc_DATA_SOUND(p0, p1)                   \
    {                                            \
        mSc_SCENE_DATA_TYPE_SOUND, p0, p1, 0, 0, \
    }

#define mSc_DATA_END()                       \
    {                                        \
        mSc_SCENE_DATA_TYPE_END, 0, 0, 0, 0, \
    }

typedef struct door_info_s {
    /* 0x00 */ u8 num_doors;
    /* 0x04 */ Door_data_c* door_data_p;
} Door_info_c;

extern Scene_Word_u test01_info[];
extern Scene_Word_u test02_info[];
extern Scene_Word_u test03_info[];
extern Scene_Word_u water_test_info[];
extern Scene_Word_u test_step01_info[];
extern Scene_Word_u test04_info[];
extern Scene_Word_u npc_room01_info[];
extern Scene_Word_u test_fd_npc_land_info[];
extern Scene_Word_u field_tool_field_info[];
extern Scene_Word_u shop01_info[];
extern Scene_Word_u BG_TEST01_info[];
extern Scene_Word_u BG_TEST01_XLU_info[];
extern Scene_Word_u broker_shop_info[];
extern Scene_Word_u fg_tool_in_info[];
extern Scene_Word_u post_office_info[];
extern Scene_Word_u start_demo1_info[];
extern Scene_Word_u start_demo2_info[];
extern Scene_Word_u police_box_info[];
extern Scene_Word_u buggy_info[];
extern Scene_Word_u player_select_info[];
extern Scene_Word_u player_room_s_info[];
extern Scene_Word_u player_room_m_info[];
extern Scene_Word_u player_room_l_info[];
extern Scene_Word_u shop02_info[];
extern Scene_Word_u shop03_info[];
extern Scene_Word_u shop04_1f_info[];
extern Scene_Word_u test05_info[];
extern Scene_Word_u PLAYER_SELECT2_info[];
extern Scene_Word_u PLAYER_SELECT3_info[];
extern Scene_Word_u shop04_2f_info[];
extern Scene_Word_u event_notification_info[];
extern Scene_Word_u kamakura_info[];
extern Scene_Word_u field_tool_field_info[];
extern Scene_Word_u title_demo_info[];
extern Scene_Word_u PLAYER_SELECT4_info[];
extern Scene_Word_u museum_entrance_info[];
extern Scene_Word_u museum_picture_info[];
extern Scene_Word_u museum_fossil_info[];
extern Scene_Word_u museum_insect_info[];
extern Scene_Word_u museum_fish_info[];
extern Scene_Word_u player_room_ll1_info[];
extern Scene_Word_u player_room_ll2_info[];
extern Scene_Word_u p_room_bm_s_info[];
extern Scene_Word_u p_room_bm_m_info[];
extern Scene_Word_u p_room_bm_l_info[];
extern Scene_Word_u p_room_bm_ll1_info[];
extern Scene_Word_u NEEDLEWORK_info[];
extern Scene_Word_u player_room_island_info[];
extern Scene_Word_u npc_room_island_info[];
extern Scene_Word_u start_demo3_info[];
extern Scene_Word_u lighthouse_info[];
extern Scene_Word_u tent_info[];

extern char* mSc_secure_exchange_keep_bank(Object_Exchange_c* exchange, s16 bank_id, size_t size);
extern void mSc_background_dmacopy_controller(Object_Bank_c* bank);
extern void mSc_dmacopy_data_bank(Object_Exchange_c* exchange);
extern int mSc_bank_regist_check(Object_Exchange_c* exchange, s16 bank_id);
extern void mSc_regist_initial_exchange_bank(GAME_PLAY* play);
extern void mSc_dmacopy_all_exchange_bank(Object_Exchange_c* exchange);
extern void mSc_data_bank_ct(GAME_PLAY* play, Object_Exchange_c* exchange);
extern void mSc_decide_exchange_bank(Object_Exchange_c* exchange);
extern void Scene_ct(GAME_PLAY* play, Scene_Word_u* scene_data);
extern void Door_info_ct(Door_info_c* door_info);
extern int goto_other_scene(GAME_PLAY* play, Door_data_c* door_data, int update_player_mode);
extern int goto_next_scene(GAME_PLAY* play, int next_idx, int update_player_mode);
extern int goto_emu_game(GAME* game, s16 famicom_rom_id);
extern void return_emu_game(GAME* game);

#ifdef __cplusplus
}
#endif

#endif
