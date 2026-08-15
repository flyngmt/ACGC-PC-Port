#ifndef M_COMMON_DATA_H
#define M_COMMON_DATA_H

#include "m_mail.h"
#include "types.h"
#include "m_actor_type.h"
#include "m_land_h.h"
#include "lb_rtc.h"
#include "m_flashrom.h"
#include "m_home_h.h"
#include "m_private.h"
#include "m_npc.h"
#include "m_field_make.h"
#include "m_notice.h"
#include "m_shop.h"
#include "m_kabu_manager.h"
#include "m_post_office.h"
#include "m_police_box.h"
#include "m_snowman.h"
#include "m_config.h"
#include "m_island.h"
#include "m_needlework.h"
#include "m_museum_display.h"
#include "m_lib.h"
#include "m_field_assessment.h"
#include "m_mushroom.h"
#include "m_clip.h"
#include "m_event.h"
#include "m_scene.h"
#include "m_npc_walk.h"
#include "m_mask_cat.h"
#include "m_npc_schedule_h.h"
#include "m_all_grow.h"
#include "m_fishrecord.h"
#include "m_card.h"
#include "m_demo.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SCHEDULE_NUM ANIMAL_NUM_MAX + mISL_ISLANDER_NUM

typedef struct time_s {
    u32 season;
    u32 term_idx;
    s16 bgitem_profile;
    s16 bgitem_bank;
    int now_sec;
    lbRTC_time_c rtc_time;
    s16 rad_min;  /* clock hand radial position for mins */
    s16 rad_hour; /* clock hand radial position for hours */
    u8 time_signal;
    u8 under_sec;
    u8 disp;
    u8 rtc_crashed;
    int rtc_enabled;
    int add_sec;
    int add_idx;
} Time_c;

/* sizeof(PlusBridge_c) == 8 */
typedef struct bridge_s {
    /* 0x00 */ u8 block_x;
    /* 0x01 */ u8 block_z;
    /* 0x02 */ struct {
        u8 exists : 1;
        u8 pending : 1;
        u8 pad : 6;
    };
    /* 0x04 */ lbRTC_ymd_c build_date;
} PlusBridge_c;

typedef struct lighthouse_s {
    lbRTC_ymd_c renew_time;
    u8 days_switched_on;
    u8 players_quest_started;
    u8 players_completed;
} LightHouse_c;

typedef struct Save_s {
    /* 0x000000 */ mFRm_chk_t save_check; /* save information */
    /* 0x000014 */ int scene_no;          /* current 'scene' id */
    /* 0x000018 */ u8 now_npc_max;        /* current number of villagers living in town (see (Add/Sub)NowNpcMax) */
    /* 0x000019 */ u8
        remove_animal_idx; /* index of the villager which is scheduled to leave town, 0xFF when none selected */
    /* 0x00001A */ u16
        copy_protect; /* 'unique' value between [1, 65520] used for copy protection (see mCD_get_land_copyProtect) */
    /* 0x00001C */ u8 pad_1C[4];
    /* 0x000020 */ Private_c private_data[PLAYER_NUM];                   /* player data */
    /* 0x009120 */ mLd_land_info_c land_info;                            /* town name & id */
    /* 0x00912C */ mNtc_board_post_c noticeboard[mNtc_BOARD_POST_COUNT]; /* noticeboard posts */
    /* 0x009CE4 */ u8 pad_9CE4[4];
    /* 0x009CE8 */ mHm_hs_c homes[PLAYER_NUM];                              /* player house data */
    /* 0x0137A8 */ mFM_fg_c fg[FG_BLOCK_Z_NUM][FG_BLOCK_X_NUM];             /* fg items (fg = foreground?) */
    /* 0x0173A8 */ mFM_combination_c combi_table[BLOCK_Z_NUM][BLOCK_X_NUM]; /* acre 'combination' data */
    /* 0x017438 */ Animal_c animals[ANIMAL_NUM_MAX];                        /* villagers in town */
    /* 0x020330 */ AnmPersonalID_c last_removed_animal_id;                  /* ID of last villager who left town */
    /* 0x020340 */ Shop_c shop;                                             /* Nook's shop */
    /* 0x020480 */ Kabu_price_c kabu_price_schedule;                        /* Stalk Market info */
    /* 0x020498 */ mEv_event_save_c event_save_data;
    /* 0x020554 */ mEv_save_common_data_c event_save_common;
    /* 0x020688 */ mActor_name_t fruit;  /* town fruit type */
    /* 0x02068A */ u8 house_arrangement; /* 2 bits for each player for the # of house they own */
    /* 0x02068B */ u8 num_statues;       /* number of statues built for players who have paid off their debts */
    /* 0x02068C */ lbRTC_time_c all_grow_renew_time; /* renewal time for fg items handled by mAgrw_RenewalFgItem_ovl */
    /* 0x020694 */ PostOffice_c post_office;         /* post office data */
    /* 0x020ED0 */ PoliceBox_c police_box;           /* police station lost & found */
    /* 0x020EF8 */ mSN_snowman_save_c snowmen;       /* saved snowmen data */
    /* 0x020F08 */ u64 melody;                       /* town tune, each nibble is a note (16 notes) */
    /* 0x020F10 */ Config_c config;                  /* saved config for sound mode, voice mode, and vibration */
    /* 0x020F14 */ lbRTC_ymd_c renew_time;           /* next renew date */
    /* 0x020F18 */ u8 station_type;                  /* train station type */
    /* 0x020F19 */ u8 weather;                       /* upper nibble is intensity, lower nibble is type */
    /* 0x020F1A */ u8 save_exist;        /* unsure, set in mCD_SaveHome_bg_set_data (1) & mCD_SaveHome_bg (bss) */
    /* 0x020F1B */ u8 npc_force_go_home; /* when set to 1, forces the 'm_go_home' code to activate */
    /* 0x020F1C */ u16 deposit[FG_BLOCK_X_NUM * FG_BLOCK_Z_NUM]
                              [UT_Z_NUM];       /* flags for which items are buried around town */
    /* 0x0212DC */ lbRTC_time_c last_grow_time; /* last time that a new villager moved into town */
    /* 0x0212E4 */ mPr_mother_mail_info_c
        mother_mail[PLAYER_NUM];              /* info on when mom sent player letters and what event was sent */
    /* 0x02131C */ mMsr_time_c mushroom_time; /* last time mushroom season info was updated */
    /* 0x021322 */ lbRTC_ymd_c _021322;
    /* 0x021326 */ u16 _021326[20];
    /* 0x02134E */ u8 npc_used_tbl[32];
    /* 0x02136E */ lbRTC_time_c _02136E;
    /* 0x021376 */ u8 cheated_flag;
    /* 0x021377 */ u8 _021377[7];
    /* 0x02137E */ lbRTC_time_c treasure_buried_time;  /* last time treasure was actually buried */
    /* 0x021386 */ lbRTC_time_c treasure_checked_time; /* last time check to bury treasure was executed */
    /* 0x02138E */ u8 saved_rom_debug;                 /* flag to set save to 'debug rom' mode */
    /* 0x02138F */ u8 snowman_year;                    /* year last snowman was built */
    /* 0x021390 */ u8 snowman_month;                   /* month last snowman was built */
    /* 0x021391 */ u8 snowman_day;                     /* day last snowman was built */
    /* 0x021392 */ u8 snowman_hour;                    /* hour last snowman was built */
    /* 0x021393 */ u8 haniwa_scheduled;                /* when set, gyroids will be spwaned */
    /* 0x021394 */ u8 dust_flag; /* set by field assessment for too much 'dust' (garbage) around town, causes immediate
                                    fail of town ranking */
    /* 0x021395 */ u8 clear_grass; /* set by Wisp, removes all weeds */
    /* 0x021396 */ u8 _021396[2];
    /* 0x021398 */ s16 event_year;
    /* 0x02139A */ u8 unused_2139C[6];
    /* 0x0213A0 */ u8 keep_house_size[PLAYER_NUM]; /* saved flags for house sizes */
    /* 0x0213A4 */ lbRTC_ymd_c force_remove_date;  /* last time the NPC force remove timer was updated */
    /* 0x0213A8 */ mMmd_info_c museum_display;     /* museum display bits */
    /* 0x0213E7 */ u8 _tmp6[0x213F0 - 0x213E7];
    /* 0x0213F0 */ PlusBridge_c bridge;         /* additional bridge info */
    /* 0x021400 */ mNW_needlework_c needlework; /* Able Sisters' designs */
    /* 0x022500 */ u8 _tmp7[0x22528 - 0x22500];
    /* 0x022528 */ OSTime time_delta; /* time delta against GC RTC */
    /* 0x022540 */ Island_c island;   /* island data */
    /* 0x023E40 */ mAGrw_AllGrow_c allgrow_ss_pos_info;
    /* 0x023E68 */ mFR_record_c fishRecord[mFR_RECORD_NUM];
    /* 0x023F20 */ MaskCat_c mask_cat;
    /* 0x024160 */ Anmret_c return_animal;  /* information about villager which moved back in to your town after moving
                                               to someone else's town */
    /* 0x02416C */ LightHouse_c LightHouse; /* info for tracking the light house quest */
    /* 0x024174 */ u8 insect_term;          /* current insect term idx */
    /* 0x024175 */ u8 insect_term_transition_offset; /* days offset from end of term to begin transition */
    /* 0x024176 */ u8 gyoei_term;                    /* current fish term idx */
    /* 0x024177 */ u8 gyoei_term_transition_offset;  /* days offset from end of term to begin transition */
    /* 0x024178 */ mFAs_GoodField_c good_field;      /* field assessment last info */
    /* 0x024184 */ u8 bg_tex_idx;                    /* Grass type */
    /* 0x024185 */ lbRTC_month_t rainbow_month;
    /* 0x024186 */ lbRTC_day_t rainbow_day;
    /* 0x024187 */ u8 rainbow_reserved;
    /* 0x024188 */ u8 _24188;
    /* 0x024189 */ u8 first_present;
    /* 0x02418A */ u8 town_day;
    /* 0x02418B */ u8 _2418B[0x24198 - 0x2418B];
    /* 0x024198 */ OSTime travel_hard_time;
    /* 0x0241A0 */ lbRTC_time_c saved_auto_nwrite_time; /* save data notice time used for fishing tourney results? */
    /* 0x0241A8 */ u8 _241A8[0x242A0 - 0x241A8];
} Save_t;

typedef union save_u {
    Save_t save;
    u8 __force_sector_align[mCD_ALIGN_SECTORSIZE(sizeof(Save_t))]; /* memcard sector-size aligned */
} Save;

typedef struct transition_s {
    u8 _00; // only set in Global_kankyo_ct?
    u8 fade_rate;
    u8 wipe_rate;
    u8 wipe_type;
} Transition_c;

/* sizeof(common_data_t) == 0x2DC00 */
typedef struct common_data_s {
    /* 0x000000 */ Save save;
    /* 0x026000 */ u8 game_started;
    /* 0x026001 */ u8 field_type;
    /* 0x026002 */ u8 field_draw_type;
    /* 0x026003 */ u8 player_no;
    /* 0x026004 */ int last_scene_no;
    /* 0x026008 */ int player_data_mode;
    /* 0x02600C */ Clip_c clip;
    /* 0x026110 */ Time_c time;
    /* 0x02613C */ Private_c* now_private;
    /* 0x026140 */ mHm_hs_c* now_home;
    /* 0x026144 */ u8 map_flag;
    /* 0x026145 */ u8 fish_location;
    /* 0x026146 */ u8 npc_is_summercamper;
    /* 0x026147 */ u8 player_select_animal_no;
    /* 0x026148 */ u8 _26148[0x2614C - 0x26148];
    /* 0x02614C */ Transition_c transition;
    /* 0x026150 */ s16 bg_item_type;
    /* 0x026152 */ s16 bg_item_profile;
    /* 0x026154 */ u8 _26154[0x26164 - 0x26154];
    /* 0x026164 */ mNpc_NpcList_c npclist[ANIMAL_NUM_MAX + 1];
    /* 0x0264E4 */ mNpc_NpcList_c island_npclist[1]; // TODO: define for island npc count
    /* 0x02651C */ mActor_name_t house_owner_name;
    /* 0x02651E */ mActor_name_t last_field_id;
    /* 0x026520 */ u8 in_initial_block; /* when TRUE, the player is in acre they exited a building. FALSE otherwise. */
    /* 0x026521 */ u8 submenu_disabled; /* when set, submenus cannot be accessed from start button */
    /* 0x026522 */ u8 sunlight_flag;
    /* 0x026523 */ u8 train_flag;
    /* 0x026522 */ Mail_c unused_mail_26522; //u8 _26524[0x26668 - 0x26524];
    /* 0x02664E */ mActor_name_t _2664E;
    /* 0x026650 */ mActor_name_t _26650;
    /* 0x026652 */ Mail_nm_c unused_mail_name_26652;
    /* 0x026668 */ mActor_name_t npc_chg_cloth;
    /* 0x02666A */ u16 _pad_2666A; // weather data is probably a struct aligned to 4 bytes
    /* 0x02666C */ s16 weather;
    /* 0x02666E */ s16 weather_intensity;
    /* 0x026670 */ lbRTC_time_c weather_time;
    /* 0x026678 */ s_xyz wind;
    /* 0x026680 */ f32 wind_speed;
    /* 0x026684 */ mEv_event_common_u special_event_common;
    /* 0x02669C */ mQst_not_saved_c quest;
    /* 0x0266A4 */ int scene_from_title_demo; /* next scene to be loaded when title demo finishes */
    /* 0x0266A8 */ mNPS_schedule_c npc_schedule[SCHEDULE_NUM];
    /* 0x0267A8 */ mNpc_walk_c npc_walk;
    /* 0x026838 */ mNpc_EventNpc_c event_npc[mNpc_EVENT_NPC_NUM];
    /* 0x026878 */ mNpc_MaskNpc_c mask_npc[mNpc_MASK_NPC_NUM];
    /* 0x028528 */ int snowman_msg_id;
    /* 0x02852C */ s16 money_power;
    /* 0x02852E */ s16 goods_power;
    /* 0x028530 */ Door_data_c door_data;                /* misc door data */
    /* 0x028544 */ Door_data_c structure_exit_door_data; /* door data for when exiting a building */
    /* 0x028558 */ mDemo_Request_c start_demo_request;
    /* 0x028568 */ Door_data_c event_door_data;
    /* 0x02857C */ Door_data_c famicom_emu_exit_door_data;
    /* 0x028590 */ u8 remove_cut_tree_info_bitfield; /* resets the cut tree states for trees in a visible acre */
    /* 0x028591 */ s8 floor_idx;
    /* 0x028592 */ s16 demo_profiles[2]; /* demo_profiles[0] is for demo_clip, demo_profiles[1] is for demo_clip2 */
    /* 0x028596 */ u16 copy_protect;
    /* 0x028598 */ int event_keep_flags[4];
    /* 0x0285A8 */ u8 _285A8[0x0285BD - 0x0285A8];
    /* 0x0285BD */ s8 player_warp_request;
    /* 0x0285BE */ s8 player_actor_exists;
    /* 0x0285BF */ s8 complete_payment_type;
    /* 0x0285C0 */ s8 player_decoy_flag;
    /* 0x0285C1 */ s8 axe_damage;
    /* 0x0285C2 */ u8 make_npc2_actor;
    /* 0x0285C4 */ s16 event_id;
    /* 0x0285C6 */ u8 event_title_flags;
    /* 0x0285C7 */ u8 event_title_fade_in_progress;
    /* 0x0285C8 */ mEv_common_data_c event_common;
    /* 0x0287F8 */ s8 current_famicom_rom;
    /* 0x0287F9 */ s8 famicom_287F9;
    /* 0x0287FA */ u8 _287FA[0x28838 - 0x0287FA];
    /* 0x028838 */ s8 player_bee_swell_flag;
    /* 0x028839 */ s8 player_bee_chase_flag;
    /* 0x02883A */ s8 goki_shocked_flag;
    /* 0x02883B */ u8 time_changed_flag;
    /* 0x02883C */ s8 unable_wade;
    /* 0x02883D */ s8 fail_emu_flag;
    /* 0x02883E */ u8 train_coming_flag;        /* state tracker for when train is going to spawn/has spawned */
    /* 0x02883F */ u8 train_exists_flag;        /* state tracker for when train exists */
    /* 0x028840 */ u8 train_control_state;      /* current train state */
    /* 0x028841 */ u8 train_last_control_state; /* previous train state */
    /* 0x028842 */ u8 train_signal;
    /* 0x028843 */ u8 train_day;
    /* 0x028844 */ u8 train_action;
    /* 0x028845 */ u8 train_timer;
    /* 0x028848 */ u32 train_start_timer;
    /* 0x02884C */ f32 train_speed;
    /* 0x028850 */ xyz_t train_position;
    /* 0x02885C */ f32 unused_02885C;
    /* 0x028860 */ f32 unused_028860;
    /* 0x028864 */ u16 unused_028864;
    /* 0x028866 */ u16 unused_028866;
    /* 0x028868 */ u8 reset_flag;
    /* 0x028869 */ u8 reset_type;
    /* 0x02886A */ u8 force_mail_delivery_flag;
    /* 0x02886B */ u8 post_girl_npc_type;
    /* 0x02886C */ xyz_t ball_pos;
    /* 0x028878 */ u8 ball_type;
    /* 0x028879 */ u8 auto_nwrite_count;
    /* 0x02887A */ lbRTC_year_t auto_nwrite_year;
    /* 0x02887C */ u8 save_error_type;        /* set to one of the mFRm_ERROR_* states when save is invalid */
    /* 0x02887D */ u8 train_approaching_flag; /* set when the train is coming */
    /* 0x02887E */ u8 buried_treasure_flag;   /* when set, treasure cannot be buried */
    /* 0x02887F */ u8 spnpc_first_talk_flags;
    /* 0x028880 */ u8 needlework_first_talk_flags;
    /* 0x028882 */ u16 event_notification_active;
    /* 0x028884 */ lbRTC_time_c newly_set_time; /* time set by player in time adjust menu */
    /* 0x02888C */ lbRTC_time_c old_time;       /* time before being changed by the player */
    /* 0x028894 */ s16 balloon_state;           /* balloon's current state */
    /* 0x028896 */ s16 balloon_last_spawn_min;  /* last minute the balloon was spawned */
    /* 0x028898 */ f32 balloon_spawn_percent;   /* chance that a balloon will spawn */
    /* 0x02889C */ int tanuki_shop_status;      /* adjusted based on any current events happening to Nook's shop */
    /* 0x0288A0 */ u8 pad_connected;            /* is gamepad 0 connected? */
    /* 0x0288A1 */ u8 unk288A1;
    /* 0x0288A2 */ s16 current_sound_effect;
    /* 0x0288A4 */ u8 _288a4[0x0288C0 - 0x0288A4];
    /* 0x0288C0 */ Island_c transfer_island; /* used when transferring islands with the GBA */
    /* 0x02A1C0 */ Island_agb_c agb_island;  /* converted island data sent over to the GBA */
    /* 0x02DB40 */ u8 auto_nwrite_set; /* when true, saved nwrite time will be utilized. Seems to be used to keep same
                                          date for fishing tourney stuff. */
    /* 0x02DB42 */ u16 select_last_select_no;
    /* 0x02DB44 */ u16 select_last_top_no;
    /* 0x02DB46 */ mCD_persistent_data_c travel_persistent_data; /* used for checking if travelling back to town */
    /* 0x02DBA2 */ s16 island_weather;
    /* 0x02DBA4 */ s16 island_weather_intensity;
    /* 0x02DBA6 */
#ifdef TARGET_PC
    u16 sunburn_time; /* Village exposure exceeds S16_MAX. */
#else
    s16 sunburn_time;
#endif
    /* 0x02DBA8 */ u8 memcard_slot;
    /* 0X02DBAC */ int my_room_message_control_flags;
    /* 0x02DBB0 */ s16 can_look_goki_count;
    /* 0x02DBB4 */ f32 rainbow_opacity; /* current opacity of rainbow (0.0f - 1.0f) */
    /* 0x02DBB8 */ u32 event_flags[mEv_EVENT_TYPE_NUM];
    /* 0x02DBD4 */ const xyz_t* pluss_bridge_pos; /* position of extra bridge */
    /* 0x02DBD8 */ lbRTC_time_c auto_nwrite_time; /* cached notice time used for fishing tourney results? */
    /* 0x02DBE0 */ u8 rhythym_updated;
    /* 0x02DBE1 */ u8 _2dbe1;
    /* 0x02DBE2 */ u8 hem_visible;             /* controls farley's visiblilty during cutscene? */
    /* 0x02DBE4 */ u8* carde_program_p;        /* pointer to current e-Reader program data */
    /* 0x02DBE8 */ size_t carde_program_size;  /* size of current e-Reader program data */
    /* 0x02DBEC */ int unk_nook_present_count; /* something possibly to do withhanding over password present? */
    /* 0x02DBF0 */ u8 pad[16];
} common_data_t;

extern common_data_t common_data;

#define Common_Get(name) (common_data.name)
#define Common_GetPointer(name) (&common_data.name)
#define Common_Set(name, value) (common_data.name = (value))

#define Save_Get(name) (Common_Get(save.save.name))
#define Save_GetPointer(name) (Common_GetPointer(save.save.name))
#define Save_Set(name, value) (Common_Set(save.save.name, value))

/* Useful for returning fg item data as a pointer to mActor_name_t */
#define Save_GetFG() Save_Get(fg[0][0].items[0])

#define Player_Palette_Get(idx) (Common_Get(now_private->my_org[idx].palette))
#define Player_Design_Get(idx) (Common_GetPointer(now_private->my_org[idx].design))

#define Now_Private (Common_Get(now_private))

#define Able_Sisters_Palette_Get(idx) (Save_Get(needlework.original_design[idx].palette))
#define Able_Sisters_Design_Get(idx) (Save_GetPointer(needlework.original_design[idx].design))
#define Able_Sisters_Cloth_Palette_Get(idx) (Able_Sisters_Palette_Get(idx))
#define Able_Sisters_Cloth_Design_Get(idx) (Able_Sisters_Design_Get(idx))
#define Able_Sisters_Umbrella_Palette_Get(idx) (Able_Sisters_Palette_Get(idx + mNW_CLOTH_DESIGN_NUM))
#define Able_Sisters_Umbrella_Design_Get(idx) (Able_Sisters_Design_Get(idx + mNW_CLOTH_DESIGN_NUM))

#define Get_Villager(idx) (Save_Get(animals[idx]))

#define Get_Island() (Save_Get(island))
#define Get_Island_Villager() (Get_Island().animal)

#define GetRoomMusicBox() (Save_Get(scene_no) == SCENE_COTTAGE_MY \
                             ? Save_Get(island).cottage.music_box \
                             : Save_Get(homes[mHS_get_arrange_idx(Common_Get(player_no))]).music_box)
#define ChkMusicBox(box, n) (((box)[((n) / 32) & 1] >> ((n) & 31)) & 1)
#define SetMusicBox(box, n) ((box)[((n) / 32) & 1] |= (1 << ((n) & 31)))
#define ClrMusicBox(box, n) ((box)[((n) / 32) & 1] &= ~(u32)(1 << ((n) & 31)))
#define ChkRoomMusicBox(n) ChkMusicBox(GetRoomMusicBox(), n)
#define SetRoomMusicBox(n) SetMusicBox(GetRoomMusicBox(), n)
#define ClrRoomMusicBox(n) ClrMusicBox(GetRoomMusicBox(), n)

#define NowPrivate_GetItemCond(i) mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, i)

#define CLIP(n) (Common_Get(clip).n)
#define aMR_CLIP (Common_Get(clip).my_room_clip)

extern void common_data_reinit();
extern void common_data_init();
extern void common_data_clear();

//clang-format on

#ifdef __cplusplus
}
#endif

#endif
