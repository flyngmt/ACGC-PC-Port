#include "m_tag_ovl.h"

#include "m_common_data.h"
#include "m_inventory_ovl.h"
#include "m_hand_ovl.h"
#include "m_cpmail_ovl.h"
#include "m_cporiginal_ovl.h"
#include "m_gba_ovl.h"
#include "m_needlework_ovl.h"
#include "m_catalog_ovl.h"
#include "m_font.h"
#include "_mem.h"
#include "m_lib.h"
#include "m_item_name.h"
#include "ac_my_room.h"
#include "m_needlework.h"
#include "m_haniwa_ovl.h"
#include "m_player_lib.h"
#include "m_warning_ovl.h"
#include "m_mailbox_ovl.h"
#include "m_music_ovl.h"
#include "m_mark_room.h"
#include "ac_set_ovl_insect.h"
#include "m_editor_ovl.h"
#include "m_editEndChk_ovl.h"
#include "sys_matrix.h"
#include "m_roll_lib.h"
#include "m_house.h"

static void mTG_mark_main_CLR(Submenu* submenu, const mSM_MenuInfo_c* menu_info);

enum {
    mTG_QSTR_TYPE_NONE,
    mTG_QSTR_TYPE_ITEM,
    mTG_QSTR_TYPE_MAIL,
    mTG_QSTR_TYPE_FROM_MUSEUM,
    mTG_QSTR_TYPE_TO_MUSEUM,
    mTG_QSTR_TYPE_XMAS_SNOWMAN_SPNPC,
    mTG_QSTR_TYPE_SHOP,
    mTG_QSTR_TYPE_MOTHER,
    mTG_QSTR_TYPE_ANGLER,
    mTG_QSTR_TYPE_OMIKUJI,
    mTG_QSTR_TYPE_POST_OFFICE,
    mTG_QSTR_TYPE_HAPPY_ROOM,

    mTG_QSTR_TYPE_NUM
};

static mTG_Ovl_c tag_ovl_data;

typedef struct tag_word_s {
    u8 str[mTG_TAG_STR_LEN];
    mSM_MOVE_PROC move_proc;
} mTG_tag_word_c;

typedef struct tag_data_s {
    mTG_tag_word_c** words; /* array of words for each line */
    int lines;              /* # of lines */
} mTG_tag_data_c;

typedef struct tag_table_data_s {
    s16 col_num;
    s16 row_num;
    s16* col_pos;
    s16* row_pos;
} mTG_tag_data_table_c;

/* columns */
static s16 mTG_item_col_pos[] = { -77, -53, -29, -5, 19 };
static s16 mTG_mail_col_pos[] = { 55, 79 };
static s16 mTG_money_col_pos[] = { 19 };
static s16 mTG_player_col_pos[] = { -59 };
static s16 mTG_bg_col_pos[] = { 19 };
static s16 mTG_mbox_col_pos[] = { -36, -12 };
static s16 mTG_haniwa_col_pos[] = { -35, -11, 13, 37 };
static s16 mTG_collect_col_pos[] = { -89, -65, -41, -17, 8, 32, 57, 81 };
static s16 mTG_wchange_col_pos[] = { 105 };
static s16 mTG_cpmail_col_pos[] = { -16, 8, 32, 56 };
static s16 mTG_cpmail_wc_col_pos[] = { 98 };
static s16 mTG_cpmail_ti_col_pos[] = { 24 };
static s16 mTG_cpedit_col_pos[] = { 20 };
static s16 mTG_cpedit_end_col_pos[] = { 20 };
static s16 mTG_catalog_col_pos[] = { 65 };
static s16 mTG_catalog_wc_col_pos[] = { 93 };
static s16 mTG_music_main_col_pos[] = { -100, -80, -60, -40, -20, 0, 20, 40, 60, 80, 100 };
static s16 mTG_needlework_col_pos[] = { -19, 19 };
static s16 mTG_cporiginal_col_pos[] = { 0, 32, 64 };
static s16 mTG_inventory_wc_org_col_pos[] = { -105 };
static s16 mTG_cporiginal_nw_col_pos[] = { -88, -56 };
static s16 mTG_cporiginal_wc_col_pos[] = { 102 };
static s16 mTG_cporiginal_ti_col_pos[] = { 32 };
static s16 mTG_gba_col_pos[] = { -97, -67, -37, -7 };
static s16 mTG_gba_nw_col_pos[] = { 48, 80 };
static s16 mTG_card_col_pos[] = { -45 };

/* rows */
static s16 mTG_item_line_pos[] = { -10, -34, -58 };
static s16 mTG_mail_line_pos[] = { 38, 14, -10, -34, -58 };
static s16 mTG_money_line_pos[] = { 18 };
static s16 mTG_player_line_pos[] = { 63 };
static s16 mTG_bg_line_pos[] = { -90 };
static s16 mTG_mbox_line_pos[] = { 39, 15, -9, -33, -57 };
static s16 mTG_haniwa_line_pos[] = { 46 };
static s16 mTG_collect_line_pos[] = { 42, 18, -6, -30, -54 };
static s16 mTG_wchange_line_pos[] = { 37, 0, -37 };
static s16 mTG_cpmail_wc_line_pos[] = { 50, 35, 20, 5, -10, -25, -40, -55 };
static s16 mTG_cpmail_ti_line_pos[] = { 71 };
static s16 mTG_cpedit_line_pos[] = { 50, 18, -14 };
static s16 mTG_cpedit_end_line_pos[] = { -49 };
static s16 mTG_catalog_line_pos[] = { 60, 42, 24, 6, -12, -30, -48 };
static s16 mTG_catalog_wc_line_pos[] = { 64, 48, 32, 16, 0, -16, -32, -48, -64 };
static s16 mTG_music_main_line_pos[] = { 25, 5, -15, -35, -55 };
static s16 mTG_needlework_line_pos[] = { 50, 16, -18, -52 };
static s16 mTG_cporiginal_line_pos[] = { 44, 15, -14, -43 };
static s16 mTG_inventory_wc_org_line_pos[] = { 0 };
static s16 mTG_cporiginal_nw_line_pos[] = { 45, 16, -13, -42 };
static s16 mTG_cporiginal_wc_line_pos[] = { 53, 40, 24, 10, -4, -18, -34, -47 };
static s16 mTG_cporiginal_ti_line_pos[] = { 74 };
static s16 mTG_gba_line_pos[] = { 6, -25 };
static s16 mTG_gba_nw_line_pos[] = { 40, 11, -18, -47 };
static s16 mTG_card_line_pos[] = { -10 };

/* Data table */
static mTG_tag_data_table_c mTG_table_data[] = {
    { 5, 3, mTG_item_col_pos, mTG_item_line_pos },                         /* mTG_TABLE_ITEM */
    { 2, 5, mTG_mail_col_pos, mTG_mail_line_pos },                         /* mTG_TABLE_MAIL */
    { 1, 1, mTG_money_col_pos, mTG_money_line_pos },                       /* mTG_TABLE_MONEY */
    { 1, 1, mTG_player_col_pos, mTG_player_line_pos },                     /* mTG_TABLE_PLAYER */
    { 1, 1, mTG_bg_col_pos, mTG_bg_line_pos },                             /* mTG_TABLE_BG */
    { 2, 5, mTG_mbox_col_pos, mTG_mbox_line_pos },                         /* mTG_TABLE_MBOX */
    { 4, 1, mTG_haniwa_col_pos, mTG_haniwa_line_pos },                     /* mTG_TABLE_HANIWA */
    { 8, 5, mTG_collect_col_pos, mTG_collect_line_pos },                   /* mTG_TABLE_COLLECT */
    { 1, 3, mTG_wchange_col_pos, mTG_wchange_line_pos },                   /* mTG_TABLE_WCHANGE */
    { 4, 5, mTG_cpmail_col_pos, mTG_mail_line_pos },                       /* mTG_TABLE_CPMAIL */
    { 1, 8, mTG_cpmail_wc_col_pos, mTG_cpmail_wc_line_pos },               /* mTG_TABLE_CPMAIL_WC */
    { 1, 1, mTG_cpmail_ti_col_pos, mTG_cpmail_ti_line_pos },               /* mTG_TABLE_CPMAIL_TI */
    { 1, 3, mTG_cpedit_col_pos, mTG_cpedit_line_pos },                     /* mTG_TABLE_CPEDIT */
    { 1, 1, mTG_cpedit_end_col_pos, mTG_cpedit_end_line_pos },             /* mTG_TABLE_CPEDIT_END */
    { 1, 7, mTG_catalog_col_pos, mTG_catalog_line_pos },                   /* mTG_TABLE_CATALOG */
    { 1, 9, mTG_catalog_wc_col_pos, mTG_catalog_wc_line_pos },             /* mTG_TABLE_CATALOG_WC */
    { 11, 5, mTG_music_main_col_pos, mTG_music_main_line_pos },            /* mTG_TABLE_MUSIC_MAIN */
    { 2, 4, mTG_needlework_col_pos, mTG_needlework_line_pos },             /* mTG_TABLE_NEEDLEWORK */
    { 3, 4, mTG_cporiginal_col_pos, mTG_cporiginal_line_pos },             /* mTG_TABLE_CPORIGINAL */
    { 1, 1, mTG_inventory_wc_org_col_pos, mTG_inventory_wc_org_line_pos }, /* mTG_TABLE_INVENTORY_WC_ORG */
    { 2, 4, mTG_cporiginal_nw_col_pos, mTG_cporiginal_nw_line_pos },       /* mTG_TABLE_CPORIGINAL_NW */
    { 1, 8, mTG_cporiginal_wc_col_pos, mTG_cporiginal_wc_line_pos },       /* mTG_TABLE_CPORIGINAL_WC */
    { 1, 1, mTG_cporiginal_ti_col_pos, mTG_cporiginal_ti_line_pos },       /* mTG_TABLE_CPORIGINAL_TI */
    { 4, 2, mTG_gba_col_pos, mTG_gba_line_pos },                           /* mTG_TABLE_GBA */
    { 2, 4, mTG_gba_nw_col_pos, mTG_gba_nw_line_pos },                     /* mTG_TABLE_GBA_NW */
    { 1, 1, mTG_card_col_pos, mTG_card_line_pos },                         /* mTG_TABLE_CARD */
    { 2, 4, mTG_gba_nw_col_pos, mTG_gba_nw_line_pos },                     /* mTG_TABLE_CARD_NW */
};

static u8 str_omikuji[7] = "fortune";
static u8 str_happy_room[7] = "the HRA";
static u8 postoffice_str[15] = "the post office";
static u8 mother_str[4] = "home";
static u8 str_otodokemono[12] = "Delivery for";
static u8 str_otegami[9] = "Letter to";
static u8 str_title0[5] = "to\xD3  ";
static u8 str_title1[5] = "from\xD3";
static u8 str_title2[5] = "'s   ";
static u8 str_title3[5] = "for\xD3 ";
static u8 str_title4[5] = "the\xD3 ";

static void mTG_present_open_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_nw_select_this_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_give_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_sell_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_sell_all_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_get_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_dump_mail_mark_exe_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_mailbox_change_mail_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_cpmail_change_mail_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_dump_mail_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_dump_item_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_send_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_rewrite_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_stick_select_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_carpet_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_cover_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_putin_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_music_listen_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_music_takeout_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_plant_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_field_put_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_room_put_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_put_all_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_dump_mail_mark_conf_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_next_open_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_next_open_needlework_sel_stick_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_next_open_needlework_sel_put_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_free_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_catch_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_password_item_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_write_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_priceset_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_present_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_show_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_cancel_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_read_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_take_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_m100_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_m1000_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_m10000_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_m30000_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_1catch_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_order_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_bury_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_release_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_fly_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_hukubukuro_open_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_cp_data_delete_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_nw_room_put_manekin_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_nw_stk_pat_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_tag_remove_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_nw_room_put_umbrella_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_nw_st_umbrella_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_nw_st_wear_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_change_original_proc(Submenu*, mSM_MenuInfo_c*);
static void mTG_drop_proc(Submenu*, mSM_MenuInfo_c*);

static mTG_tag_word_c mTG_tag_word_akeru = {
    "Open            ",
    &mTG_present_open_proc,
};

static mTG_tag_word_c mTG_tag_word_ageru = {
    "Give            ",
    &mTG_give_proc,
};

static mTG_tag_word_c mTG_tag_word_itadaku = {
    "Take it         ",
    &mTG_get_proc,
};

static mTG_tag_word_c mTG_tag_word_dump_item = {
    "Yes             ",
    &mTG_dump_item_proc,
};

static mTG_tag_word_c mTG_tag_word_field_sign = {
    "Erect           ",
    &mTG_field_put_proc,
};

static mTG_tag_word_c mTG_tag_word_dump_mail = {
    "Yes             ",
    &mTG_dump_mail_proc,
};

static mTG_tag_word_c mTG_tag_word_sell = {
    "Sell            ",
    &mTG_sell_proc,
};

static mTG_tag_word_c mTG_tag_word_sell_all = {
    "Sell All        ",
    &mTG_sell_all_proc,
};

static mTG_tag_word_c mTG_tag_word_okuru = {
    "Send            ",
    &mTG_send_proc,
};

static mTG_tag_word_c mTG_tag_word_kakinaosu = {
    "Rewrite         ",
    &mTG_rewrite_proc,
};

static mTG_tag_word_c mTG_tag_word_kabeniharu = {
    "Put on Wall     ",
    &mTG_cover_proc,
};

static mTG_tag_word_c mTG_tag_word_korewoireru = {
    "Put Away        ",
    &mTG_putin_proc,
};

static mTG_tag_word_c mTG_tag_word_zimenniueru = {
    "Plant           ",
    &mTG_plant_proc,
};

static mTG_tag_word_c mTG_tag_word_zimennioku = {
    "Drop            ",
    &mTG_field_put_proc,
};

static mTG_tag_word_c mTG_tag_word_suteru = {
    "Throw Away      ",
    &mTG_next_open_proc,
};

static mTG_tag_word_c mTG_tag_word_tada = {
    "Give Away       ",
    &mTG_free_proc,
};

static mTG_tag_word_c mTG_tag_word_tukamu = {
    "Grab            ",
    &mTG_catch_proc,
};

static mTG_tag_word_c mTG_tag_word_tegamiwokaku = {
    "Write Letter    ",
    &mTG_write_proc,
};

static mTG_tag_word_c mTG_tag_word_nedanwotukeru = {
    "Set Price       ",
    &mTG_priceset_proc,
};

static mTG_tag_word_c mTG_tag_word_present = {
    "Present         ",
    &mTG_present_proc,
};

static mTG_tag_word_c mTG_tag_word_miserudake = {
    "Display         ",
    &mTG_show_proc,
};

static mTG_tag_word_c mTG_tag_word_yameru = {
    "Quit            ",
    &mTG_cancel_proc,
};

static mTG_tag_word_c mTG_tag_word_heyanioku = {
    "Drop            ",
    &mTG_room_put_proc,
};

static mTG_tag_word_c mTG_tag_word_yukanisiku = {
    "Spread on Floor ",
    &mTG_carpet_proc,
};

static mTG_tag_word_c mTG_tag_word_yomu = {
    "Read            ",
    &mTG_read_proc,
};

static mTG_tag_word_c mTG_tag_word_watasu = {
    "Give            ",
    &mTG_take_proc,
};

static mTG_tag_word_c mTG_tag_word_100 = {
    "100             ",
    &mTG_m100_proc,
};

static mTG_tag_word_c mTG_tag_word_1000 = {
    "1000            ",
    &mTG_m1000_proc,
};

static mTG_tag_word_c mTG_tag_word_10000 = {
    "10000           ",
    &mTG_m10000_proc,
};

static mTG_tag_word_c mTG_tag_word_30000 = {
    "30000           ",
    &mTG_m30000_proc,
};

static mTG_tag_word_c mTG_tag_word_okane = {
    "Price\xD3:\xD3\xD3\xD3\xD3\xD3\xD3\xD3  ",
    NULL,
};

static mTG_tag_word_c mTG_tag_word_beru = {
    "Bells           ",
    NULL,
};

static mTG_tag_word_c mTG_tag_word_osameru = {
    "Give            ",
    &mTG_putin_proc,
};

static mTG_tag_word_c mTG_tag_word_zenbutukamu = {
    "Grab All        ",
    &mTG_catch_proc,
};

static mTG_tag_word_c mTG_tag_word_1maitukamu = {
    "Grab One        ",
    &mTG_1catch_proc,
};

static mTG_tag_word_c mTG_tag_word_1tamatukamu = {
    "Grab            ",
    &mTG_1catch_proc,
};

static mTG_tag_word_c mTG_tag_word_order = {
    "Order           ",
    &mTG_order_proc,
};

static mTG_tag_word_c mTG_tag_word_zimenniumeru = {
    "Bury            ",
    &mTG_bury_proc,
};

static mTG_tag_word_c mTG_tag_word_nigasu = {
    "Release         ",
    &mTG_release_proc,
};

static mTG_tag_word_c mTG_tag_word_fly = {
    "Let Go          ",
    &mTG_fly_proc,
};

static mTG_tag_word_c mTG_tag_word_akeru2 = {
    "Open            ",
    &mTG_hukubukuro_open_proc,
};

static mTG_tag_word_c mTG_tag_word_kesu = {
    "????            ",
    &mTG_next_open_proc,
};

static mTG_tag_word_c mTG_tag_word_hai = {
    "Yes             ",
    &mTG_cp_data_delete_proc,
};

static mTG_tag_word_c mTG_tag_word_iie = {
    "No              ",
    &mTG_cancel_proc,
};

static mTG_tag_word_c mTG_tag_word_dump_mail_mark_conf = {
    "Throw All Away  ",
    &mTG_dump_mail_mark_conf_proc,
};

static mTG_tag_word_c mTG_tag_word_dump_mail_mark_exe = {
    "Yes             ",
    &mTG_dump_mail_mark_exe_proc,
};

static mTG_tag_word_c mTG_tag_word_mailbox_change_mail = {
    "Copy All        ",
    &mTG_mailbox_change_mail_proc,
};

static mTG_tag_word_c mTG_tag_word_cpmail_change_mail = {
    "Swap            ",
    &mTG_cpmail_change_mail_proc,
};

static mTG_tag_word_c mTG_tag_word_music_listen = {
    "Listen          ",
    &mTG_music_listen_proc,
};

static mTG_tag_word_c mTG_tag_word_music_takeout = {
    "Take out        ",
    &mTG_music_takeout_proc,
};

static mTG_tag_word_c mTG_tag_word_music_takeout_all = {
    "Take out all    ",
    &mTG_music_takeout_proc,
};

static mTG_tag_word_c mTG_tag_word_hand_over_curator = {
    "Give            ",
    &mTG_give_proc,
};

static mTG_tag_word_c mTG_tag_word_nw_select_this = {
    "Use             ",
    &mTG_nw_select_this_proc,
};

static mTG_tag_word_c mTG_tag_word_nw_select_put = {
    "Drop            ",
    &mTG_nw_select_this_proc,
};

static mTG_tag_word_c mTG_tag_word_nw_select_change = {
    "Swap            ",
    &mTG_nw_select_this_proc,
};

static mTG_tag_word_c mTG_tag_word_nw_st_wear = {
    "Use on Clothes  ",
    &mTG_nw_st_wear_proc,
};

static mTG_tag_word_c mTG_tag_word_nw_st_umbrella = {
    "Use on Umbrella ",
    &mTG_nw_st_umbrella_proc,
};

static mTG_tag_word_c mTG_tag_word_nw_cover = {
    "Use on Walls    ",
    &mTG_stick_select_proc,
};

static mTG_tag_word_c mTG_tag_word_nw_carpet = {
    "Use on Floor    ",
    &mTG_stick_select_proc,
};

static mTG_tag_word_c mTG_tag_word_nw_catch = {
    "Grab            ",
    &mTG_catch_proc,
};

static mTG_tag_word_c mTG_tag_word_nw_mr_sel_stick = {
    "Use             ",
    &mTG_next_open_needlework_sel_stick_proc,
};

static mTG_tag_word_c mTG_tag_word_nw_or_sel_stick = {
    "Use             ",
    &mTG_next_open_needlework_sel_stick_proc,
};

static mTG_tag_word_c mTG_tag_word_nw_sel_put = {
    "Drop            ",
    &mTG_next_open_needlework_sel_put_proc,
};

static mTG_tag_word_c mTG_tag_word_nw_put_umbrella = {
    "Drop as Umbrella",
    &mTG_nw_room_put_umbrella_proc,
};

static mTG_tag_word_c mTG_tag_word_nw_put_wear = {
    "Drop as Clothes ",
    &mTG_nw_room_put_manekin_proc,
};

static mTG_tag_word_c mTG_tag_word_nw_stk_pat_nrml = {
    "Basic Paste     ",
    &mTG_nw_stk_pat_proc,
};

static mTG_tag_word_c mTG_tag_word_nw_stk_pat_turn = {
    "Mix it up       ",
    &mTG_nw_stk_pat_proc,
};

static mTG_tag_word_c mTG_tag_word_remove = {
    "Remove          ",
    &mTG_tag_remove_proc,
};

static mTG_tag_word_c mTG_tag_word_put_all = {
    "Drop All        ",
    &mTG_put_all_proc,
};

static mTG_tag_word_c mTG_tag_word_put_chk = {
    "That's Fine     ",
    &mTG_drop_proc,
};

static mTG_tag_word_c mTG_tag_word_never_mind = {
    "Never mind      ",
    &mTG_cancel_proc,
};

static mTG_tag_word_c mTG_tag_word_change_original = {
    "Swap            ",
    &mTG_change_original_proc,
};

static mTG_tag_word_c mTG_tag_word_password_item = {
    "Give            ",
    &mTG_password_item_proc,
};

static u8 mTG_tag_str_suteruno[13] = "Throw it out?";
static u8 mTG_tag_str_hontoni[6] = "??????";
static u8 mTG_tag_str_iidesuka[6] = "??????";
static u8 mTG_tag_str_put_chk1[11] = "You'll lose";
static u8 mTG_tag_str_put_chk2[12] = "that design.";

// clang-format off
static u8 mTG_catalog_str[][mCL_TAG_STR_SIZE] = {
    "Furniture ",
    "Wallpaper ",
    "Carpet    ",
    "Clothing  ",
    "Items     ",
    "Stationery",
    "Gyroids   ",
    "Fossils   ",
    "Music     ",
};
// clang-format on

static mTG_tag_word_c* mTG_field_default[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_zimennioku,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_field_default_bury[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_zimennioku,
    &mTG_tag_word_zimenniumeru,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_field_letter[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_tegamiwokaku,
    &mTG_tag_word_zimennioku,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_field_letter_bury[] = {
    &mTG_tag_word_tukamu,       &mTG_tag_word_tegamiwokaku, &mTG_tag_word_zimennioku,
    &mTG_tag_word_zimenniumeru, &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_field_sign[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_field_sign,
    &mTG_tag_word_suteru,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_field_balloon[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_fly,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_field_hukubukuro[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_akeru2,
    &mTG_tag_word_zimennioku,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_field_hukubukuro_bury[] = {
    &mTG_tag_word_tukamu,       &mTG_tag_word_akeru2, &mTG_tag_word_zimennioku,
    &mTG_tag_word_zimenniumeru, &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_field_release[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_nigasu,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_catch_item[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_field_plant[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_zimennioku,
    &mTG_tag_word_zimenniueru,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_field_plant_job[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_zimenniueru,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_present_item[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_akeru,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_room_default[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_heyanioku,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_room_wall[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_heyanioku,
    &mTG_tag_word_kabeniharu,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_room_carpet[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_heyanioku,
    &mTG_tag_word_yukanisiku,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_room_letter[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_tegamiwokaku,
    &mTG_tag_word_heyanioku,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_room_hukubukuro[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_akeru2,
    &mTG_tag_word_heyanioku,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_other_letter[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_tegamiwokaku,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_other_hukubukuro[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_akeru2,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_def_rmail[] = {
    &mTG_tag_word_yomu,
    &mTG_tag_word_tukamu,
    &mTG_tag_word_suteru,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_room_rmail[] = {
    &mTG_tag_word_yomu,
    &mTG_tag_word_tukamu,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_def_rmail_pre[] = {
    &mTG_tag_word_yomu,
    &mTG_tag_word_tukamu,
    &mTG_tag_word_present,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_def_smail[] = {
    &mTG_tag_word_kakinaosu,
    &mTG_tag_word_tukamu,
    &mTG_tag_word_suteru,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_room_smail[] = {
    &mTG_tag_word_kakinaosu,
    &mTG_tag_word_tukamu,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_def_smail_pre[] = {
    &mTG_tag_word_kakinaosu,
    &mTG_tag_word_tukamu,
    &mTG_tag_word_present,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_dump_mail[] = {
    &mTG_tag_word_dump_mail,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_dump_item[] = {
    &mTG_tag_word_dump_item,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_money_sack1[] = {
    &mTG_tag_word_100,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_money_sack2[] = {
    &mTG_tag_word_100,
    &mTG_tag_word_1000,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_money_sack3[] = {
    &mTG_tag_word_100,
    &mTG_tag_word_1000,
    &mTG_tag_word_10000,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_money_sack4[] = {
    &mTG_tag_word_100, &mTG_tag_word_1000, &mTG_tag_word_10000, &mTG_tag_word_30000, &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_quest_item[] = {
    &mTG_tag_word_watasu,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_sell_item[] = {
    &mTG_tag_word_sell,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_give_item[] = {
    &mTG_tag_word_ageru,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_send_mail[] = {
    &mTG_tag_word_okuru,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_field_ticket[] = {
    &mTG_tag_word_zenbutukamu,
    &mTG_tag_word_1maitukamu,
    &mTG_tag_word_zimennioku,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_field_ticket_bury[] = {
    &mTG_tag_word_zenbutukamu,  &mTG_tag_word_1maitukamu, &mTG_tag_word_zimennioku,
    &mTG_tag_word_zimenniumeru, &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_room_ticket[] = {
    &mTG_tag_word_zenbutukamu,
    &mTG_tag_word_1maitukamu,
    &mTG_tag_word_heyanioku,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_catch_ticket[] = {
    &mTG_tag_word_zenbutukamu,
    &mTG_tag_word_1maitukamu,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_putin_item[] = {
    &mTG_tag_word_korewoireru,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_shrine_item[] = {
    &mTG_tag_word_osameru,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_haniwa_item[] = {
    &mTG_tag_word_tukamu,     &mTG_tag_word_tada,   &mTG_tag_word_nedanwotukeru,
    &mTG_tag_word_miserudake, &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_haniwa_put_item[] = {
    &mTG_tag_word_tada,
    &mTG_tag_word_nedanwotukeru,
    &mTG_tag_word_miserudake,
};

static mTG_tag_word_c* mTG_haniwa_get_item[] = {
    &mTG_tag_word_itadaku,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_haniwa_price[] = {
    &mTG_tag_word_okane,
    &mTG_tag_word_beru,
};

static mTG_tag_word_c* mTG_order_item[] = {
    &mTG_tag_word_order,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_cp_delete[] = {
    &mTG_tag_word_yameru,
    &mTG_tag_word_kesu,
};

static mTG_tag_word_c* mTG_cp_delete2[] = {
    &mTG_tag_word_iie,
    &mTG_tag_word_hai,
};

static mTG_tag_word_c* mTG_field_mail_mark[] = {
    &mTG_tag_word_dump_mail_mark_conf,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_dump_mail_mark_conf[] = {
    &mTG_tag_word_dump_mail_mark_exe,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_field_mail_mark2[] = {
    &mTG_tag_word_mailbox_change_mail,
    &mTG_tag_word_dump_mail_mark_conf,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_cpack_mail_mark[] = {
    &mTG_tag_word_cpmail_change_mail,
    &mTG_tag_word_dump_mail_mark_conf,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_sell_all_item[] = {
    &mTG_tag_word_sell_all,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_music_select[] = {
    &mTG_tag_word_music_listen,
    &mTG_tag_word_music_takeout,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_music_select_many[] = {
    &mTG_tag_word_music_takeout_all,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_field_wisp[] = {
    &mTG_tag_word_zenbutukamu,
    &mTG_tag_word_1tamatukamu,
    &mTG_tag_word_nigasu,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_catch_wisp[] = {
    &mTG_tag_word_zenbutukamu,
    &mTG_tag_word_1tamatukamu,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_tag_hand_over_curator[] = {
    &mTG_tag_word_hand_over_curator,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_tag_nw_select[] = {
    &mTG_tag_word_nw_select_this,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_tag_nw_my_room[] = {
    &mTG_tag_word_nw_catch,
    &mTG_tag_word_nw_mr_sel_stick,
    &mTG_tag_word_nw_sel_put,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_tag_nw_ot_room[] = {
    &mTG_tag_word_nw_catch,
    &mTG_tag_word_nw_or_sel_stick,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_tag_nw_ug_room[] = {
    &mTG_tag_word_nw_catch,
    &mTG_tag_word_nw_mr_sel_stick,
    &mTG_tag_word_nw_sel_put,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_tag_nw_mr_sel_stick[] = {
    &mTG_tag_word_nw_st_wear, &mTG_tag_word_nw_st_umbrella, &mTG_tag_word_nw_cover,
    &mTG_tag_word_nw_carpet,  &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_tag_nw_sel_put[] = {
    &mTG_tag_word_nw_put_wear,
    &mTG_tag_word_nw_put_umbrella,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_tag_nw_or_sel_stick[] = {
    &mTG_tag_word_nw_st_wear,
    &mTG_tag_word_nw_st_umbrella,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_tag_nw_sel_stk_pattern[] = {
    &mTG_tag_word_nw_stk_pat_nrml,
    &mTG_tag_word_nw_stk_pat_turn,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_tag_remove[] = {
    &mTG_tag_word_remove,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_tag_put_all[] = {
    &mTG_tag_word_put_all,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_tag_put_chk[] = {
    &mTG_tag_word_put_chk,
    &mTG_tag_word_never_mind,
};

static mTG_tag_word_c* mTG_field_letters[] = {
    &mTG_tag_word_tukamu,     &mTG_tag_word_1maitukamu, &mTG_tag_word_tegamiwokaku,
    &mTG_tag_word_zimennioku, &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_field_letters_bury[] = {
    &mTG_tag_word_tukamu,     &mTG_tag_word_1maitukamu,   &mTG_tag_word_tegamiwokaku,
    &mTG_tag_word_zimennioku, &mTG_tag_word_zimenniumeru, &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_room_letters[] = {
    &mTG_tag_word_tukamu,    &mTG_tag_word_1maitukamu, &mTG_tag_word_tegamiwokaku,
    &mTG_tag_word_heyanioku, &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_other_letters[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_1maitukamu,
    &mTG_tag_word_tegamiwokaku,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_change_original[] = {
    &mTG_tag_word_change_original,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_taisou_card[] = {
    &mTG_tag_word_tukamu,
    &mTG_tag_word_suteru,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_tag_nw_select_change[] = {
    &mTG_tag_word_nw_select_change,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_tag_nw_select_put[] = {
    &mTG_tag_word_nw_select_put,
    &mTG_tag_word_yameru,
};

static mTG_tag_word_c* mTG_tag_password_item[] = {
    &mTG_tag_word_password_item,
    &mTG_tag_word_yameru,
};

static mTG_tag_data_c mTG_label_table[] = {
    { NULL, 0 },                                                             /* mTG_TYPE_NONE */
    { mTG_field_default, ARRAY_COUNT(mTG_field_default) },                   /* mTG_TYPE_FIELD_DEFAULT */
    { mTG_field_default_bury, ARRAY_COUNT(mTG_field_default_bury) },         /* mTG_TYPE_FIELD_DEFAULT_BURY */
    { mTG_field_letter, ARRAY_COUNT(mTG_field_letter) },                     /* mTG_TYPE_FIELD_LETTER */
    { mTG_field_letter_bury, ARRAY_COUNT(mTG_field_letter_bury) },           /* mTG_TYPE_FIELD_LETTER_BURY */
    { mTG_field_hukubukuro, ARRAY_COUNT(mTG_field_hukubukuro) },             /* mTG_TYPE_FIELD_HUKUBUKURO */
    { mTG_field_hukubukuro_bury, ARRAY_COUNT(mTG_field_hukubukuro_bury) },   /* mTG_TYPE_FIELD_HUKUBUKURO_BURY */
    { mTG_field_release, ARRAY_COUNT(mTG_field_release) },                   /* mTG_TYPE_FIELD_RELEASE */
    { mTG_catch_item, ARRAY_COUNT(mTG_catch_item) },                         /* mTG_TYPE_CATCH_ITEM */
    { mTG_field_plant, ARRAY_COUNT(mTG_field_plant) },                       /* mTG_TYPE_FIELD_PLANT */
    { mTG_field_plant_job, ARRAY_COUNT(mTG_field_plant_job) },               /* mTG_TYPE_FIELD_PLANT_JOB */
    { mTG_present_item, ARRAY_COUNT(mTG_present_item) },                     /* mTG_TYPE_PRESENT_ITEM */
    { mTG_room_default, ARRAY_COUNT(mTG_room_default) },                     /* mTG_TYPE_ROOM_DEFAULT */
    { mTG_room_wall, ARRAY_COUNT(mTG_room_wall) },                           /* mTG_TYPE_ROOM_WALL */
    { mTG_room_carpet, ARRAY_COUNT(mTG_room_carpet) },                       /* mTG_TYPE_ROOM_CARPET */
    { mTG_room_letter, ARRAY_COUNT(mTG_room_letter) },                       /* mTG_TYPE_ROOM_LETTER */
    { mTG_room_hukubukuro, ARRAY_COUNT(mTG_room_hukubukuro) },               /* mTG_TYPE_ROOM_HUKUBUKURO */
    { mTG_other_letter, ARRAY_COUNT(mTG_other_letter) },                     /* mTG_TYPE_OTHER_LETTER */
    { mTG_other_hukubukuro, ARRAY_COUNT(mTG_other_hukubukuro) },             /* mTG_TYPE_OTHER_HUKUBUKURO */
    { mTG_def_rmail, ARRAY_COUNT(mTG_def_rmail) },                           /* mTG_TYPE_DEF_RMAIL */
    { mTG_room_rmail, ARRAY_COUNT(mTG_room_rmail) },                         /* mTG_TYPE_ROOM_RMAIL */
    { mTG_def_rmail_pre, ARRAY_COUNT(mTG_def_rmail_pre) },                   /* mTG_TYPE_DEF_RMAIL_PRE */
    { mTG_def_smail, ARRAY_COUNT(mTG_def_smail) },                           /* mTG_TYPE_DEF_SMAIL */
    { mTG_room_smail, ARRAY_COUNT(mTG_room_smail) },                         /* mTG_TYPE_ROOM_SMAIL */
    { mTG_def_smail_pre, ARRAY_COUNT(mTG_def_smail_pre) },                   /* mTG_TYPE_DEF_SMAIL_PRE */
    { mTG_dump_mail, ARRAY_COUNT(mTG_dump_mail) },                           /* mTG_TYPE_DUMP_MAIL */
    { mTG_money_sack3, ARRAY_COUNT(mTG_money_sack3) },                       /* mTG_TYPE_MONEY_SACK */
    { mTG_quest_item, ARRAY_COUNT(mTG_quest_item) },                         /* mTG_TYPE_QUEST_ITEM */
    { mTG_sell_item, ARRAY_COUNT(mTG_sell_item) },                           /* mTG_TYPE_SELL_ITEM */
    { mTG_give_item, ARRAY_COUNT(mTG_give_item) },                           /* mTG_TYPE_GIVE_ITEM */
    { mTG_send_mail, ARRAY_COUNT(mTG_send_mail) },                           /* mTG_TYPE_SEND_MAIL */
    { mTG_field_ticket, ARRAY_COUNT(mTG_field_ticket) },                     /* mTG_TYPE_FIELD_TICKET */
    { mTG_field_ticket_bury, ARRAY_COUNT(mTG_field_ticket_bury) },           /* mTG_TYPE_FIELD_TICKET_BURY */
    { mTG_room_ticket, ARRAY_COUNT(mTG_room_ticket) },                       /* mTG_TYPE_ROOM_TICKET */
    { mTG_catch_ticket, ARRAY_COUNT(mTG_catch_ticket) },                     /* mTG_TYPE_CATCH_TICKET */
    { mTG_putin_item, ARRAY_COUNT(mTG_putin_item) },                         /* mTG_TYPE_PUTIN_ITEM */
    { mTG_shrine_item, ARRAY_COUNT(mTG_shrine_item) },                       /* mTG_TYPE_SHRINE_ITEM */
    { mTG_haniwa_item, ARRAY_COUNT(mTG_haniwa_item) },                       /* mTG_TYPE_HANIWA_ITEM */
    { mTG_haniwa_put_item, ARRAY_COUNT(mTG_haniwa_put_item) },               /* mTG_TYPE_HANIWA_PUT_ITEM */
    { mTG_haniwa_price, ARRAY_COUNT(mTG_haniwa_price) },                     /* mTG_TYPE_HANIWA_PRICE */
    { mTG_haniwa_get_item, ARRAY_COUNT(mTG_haniwa_get_item) },               /* mTG_TYPE_HANIWA_GET_ITEM */
    { mTG_order_item, ARRAY_COUNT(mTG_order_item) },                         /* mTG_TYPE_ORDER_ITEM */
    { mTG_cp_delete, ARRAY_COUNT(mTG_cp_delete) },                           /* mTG_TYPE_CP_DELETE */
    { mTG_cp_delete2, ARRAY_COUNT(mTG_cp_delete2) },                         /* mTG_TYPE_CP_DELETE2 */
    { mTG_field_mail_mark, ARRAY_COUNT(mTG_field_mail_mark) },               /* mTG_TYPE_FIELD_MAIL_MARK */
    { mTG_dump_mail_mark_conf, ARRAY_COUNT(mTG_dump_mail_mark_conf) },       /* mTG_TYPE_DUMP_MAIL_MARK_CONF */
    { mTG_field_mail_mark2, ARRAY_COUNT(mTG_field_mail_mark2) },             /* mTG_TYPE_FIELD_MAIL_MARK2 */
    { mTG_cpack_mail_mark, ARRAY_COUNT(mTG_cpack_mail_mark) },               /* mTG_TYPE_CPACK_MAIL_MARK */
    { mTG_sell_all_item, ARRAY_COUNT(mTG_sell_all_item) },                   /* mTG_TYPE_SELL_ALL_ITEM */
    { mTG_music_select, ARRAY_COUNT(mTG_music_select) },                     /* mTG_TYPE_MUSIC_SELECT */
    { mTG_music_select_many, ARRAY_COUNT(mTG_music_select_many) },           /* mTG_TYPE_MUSIC_SELECT_MANY */
    { mTG_field_wisp, ARRAY_COUNT(mTG_field_wisp) },                         /* mTG_TYPE_FIELD_WISP */
    { mTG_catch_wisp, ARRAY_COUNT(mTG_catch_wisp) },                         /* mTG_TYPE_CATCH_WISP */
    { mTG_tag_hand_over_curator, ARRAY_COUNT(mTG_tag_hand_over_curator) },   /* mTG_TYPE_TAG_HAND_OVER_CURATOR */
    { mTG_tag_nw_select, ARRAY_COUNT(mTG_tag_nw_select) },                   /* mTG_TYPE_TAG_NW_SELECT */
    { mTG_tag_nw_my_room, ARRAY_COUNT(mTG_tag_nw_my_room) },                 /* mTG_TYPE_TAG_NW_MY_ROOM */
    { mTG_tag_nw_ot_room, ARRAY_COUNT(mTG_tag_nw_ot_room) },                 /* mTG_TYPE_TAG_NW_OT_ROOM */
    { mTG_tag_nw_ug_room, ARRAY_COUNT(mTG_tag_nw_ug_room) },                 /* mTG_TYPE_TAG_NW_UG_ROOM */
    { mTG_tag_nw_mr_sel_stick, ARRAY_COUNT(mTG_tag_nw_mr_sel_stick) },       /* mTG_TYPE_TAG_NW_MR_SEL_STICK */
    { mTG_tag_nw_or_sel_stick, ARRAY_COUNT(mTG_tag_nw_or_sel_stick) },       /* mTG_TYPE_TAG_NW_OR_SEL_STICK */
    { mTG_tag_nw_sel_put, ARRAY_COUNT(mTG_tag_nw_sel_put) },                 /* mTG_TYPE_TAG_NW_SEL_PUT */
    { mTG_tag_nw_sel_stk_pattern, ARRAY_COUNT(mTG_tag_nw_sel_stk_pattern) }, /* mTG_TYPE_TAG_NW_SEL_STK_PATTERN */
    { mTG_tag_remove, ARRAY_COUNT(mTG_tag_remove) },                         /* mTG_TYPE_TAG_REMOVE */
    { mTG_tag_put_all, ARRAY_COUNT(mTG_tag_put_all) },                       /* mTG_TYPE_TAG_PUT_ALL */
    { mTG_tag_put_chk, ARRAY_COUNT(mTG_tag_put_chk) },                       /* mTG_TYPE_TAG_PUT_CHK */
    { mTG_field_letters, ARRAY_COUNT(mTG_field_letters) },                   /* mTG_TYPE_FIELD_LETTERS */
    { mTG_field_letters_bury, ARRAY_COUNT(mTG_field_letters_bury) },         /* mTG_TYPE_FIELD_LETTERS_BURY */
    { mTG_room_letters, ARRAY_COUNT(mTG_room_letters) },                     /* mTG_TYPE_ROOM_LETTERS */
    { mTG_other_letters, ARRAY_COUNT(mTG_other_letters) },                   /* mTG_TYPE_OTHER_LETTERS */
    { mTG_change_original, ARRAY_COUNT(mTG_change_original) },               /* mTG_TYPE_CHANGE_ORIGINAL */
    { mTG_taisou_card, ARRAY_COUNT(mTG_taisou_card) },                       /* mTG_TYPE_TAISOU_CARD */
    { mTG_dump_item, ARRAY_COUNT(mTG_dump_item) },                           /* mTG_TYPE_DUMP_ITEM */
    { mTG_field_sign, ARRAY_COUNT(mTG_field_sign) },                         /* mTG_TYPE_FIELD_SIGN */
    { mTG_field_balloon, ARRAY_COUNT(mTG_field_balloon) },                   /* mTG_TYPE_FIELD_BALLOON */
    { mTG_tag_nw_select_change, ARRAY_COUNT(mTG_tag_nw_select_change) },     /* mTG_TYPE_TAG_NW_SELECT_CHANGE */
    { mTG_tag_nw_select_put, ARRAY_COUNT(mTG_tag_nw_select_put) },           /* mTG_TYPE_TAG_NW_SELECT_PUT */
    { NULL, 0 },                                                             /* mTG_TYPE_76 */
    { mTG_tag_password_item, ARRAY_COUNT(mTG_tag_password_item) },           /* mTG_TYPE_TAG_PASSWORD_ITEM */
};

static void mTG_init_tag_data_item_win(Submenu*);

static int mTG_check_hand_condition(Submenu* submenu) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
    int res = FALSE;

    if (hand_ovl->info.item == EMPTY_NO && mMl_check_not_used_mail(&hand_ovl->info.mail) == TRUE) {
        res = TRUE;
    }

    return res;
}

static f32 mTG_set_hand_pos_offset(Submenu* submenu, int table) {
    f32 res = 0.0f;

    if (submenu->overlay->needlework_ovl != NULL) {
        int nw_type = submenu->overlay->menu_info[mSM_OVL_NEEDLEWORK].data0;

        if (nw_type == mNW_OPEN_DESIGN) {
            res = 21.0f;
        } else if (nw_type == mNW_OPEN_INV && table == mTG_TABLE_NEEDLEWORK) {
            res = 46.0f;
        }
    } else if (submenu->overlay->inventory_ovl != NULL) {
        if (submenu->overlay->menu_info[mSM_OVL_INVENTORY].data0 == mSM_IV_OPEN_CPMAIL && table == mTG_TABLE_MAIL) {
            res = -155.0f;
        }
    }

    return res;
}

static void mTG_set_hand_pos(Submenu* submenu, f32* pos, int table, int idx) {
    mTG_tag_data_table_c* data_p = &mTG_table_data[table];
    f32 ofs = mTG_set_hand_pos_offset(submenu, table);
    int col = idx % data_p->col_num;
    int row;
    f32 pos_x = data_p->col_pos[col];

    pos_x += ofs;
    pos[0] = pos_x;

    row = idx / data_p->col_num;
    pos[1] = data_p->row_pos[row];
}

static int mTG_get_tag_idx(Submenu* submenu, int type) {
    int idx = submenu->overlay->tag_ovl->sel_tag_idx;
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[idx];
    int i;

    for (i = idx; i >= 0; i--) {
        if (tag->type == type) {
            return i;
        }

        tag--;
    }

    return -1;
}

static int mTG_return_tag_init(Submenu* submenu, int ret_type, int type) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag;
    int ret_idx = mTG_get_tag_idx(submenu, ret_type);
    int i;

    if (ret_idx >= 0) {
        if (ret_idx == 0) {
            tag_ovl->ret_tag_idx = -1;
        } else {
            tag_ovl->ret_tag_idx = ret_idx;
        }

        if (type == mTG_RETURN_CLOSE) {
            tag = &tag_ovl->tags[tag_ovl->sel_tag_idx];

            for (i = tag_ovl->sel_tag_idx - tag_ovl->ret_tag_idx; i != 0; i--) {
                tag->base_pos[0] += tag->body_ofs[0];
                tag->base_pos[1] += tag->body_ofs[1];
                tag->body_ofs[0] = 0.0f;
                tag->body_ofs[1] = 0.0f;
                tag--;
            }
        }
    }

    return ret_idx;
}

static s16 mTG_get_item_name_wait_time(mTG_tag_c* tag) {
    s16 time;

    tag->scale = 0.0f;
    if (tag->table == mTG_TABLE_CATALOG_WC) {
        time = 16;
    } else {
        time = 20;
    }

    return time;
}

static void mTG_return_tag_func(Submenu* submenu, mTG_Ovl_c* tag_ovl, mTG_tag_c* tag) {
    mTG_tag_c* now_tag = tag;
    int count = 0;
    int tag_num = tag_ovl->sel_tag_idx - tag_ovl->ret_tag_idx;
    int i;

    for (i = tag_num; i != 0; i--) {
        now_tag->scale -= 0.125f;
        if (now_tag->scale <= 0.0f) {
            if (now_tag->type == mTG_TYPE_NONE) {
                tag_ovl->item_name_wait_time = mTG_get_item_name_wait_time(now_tag);
            }

            now_tag->scale = 0.0f;
            count++;
        }

        now_tag--;
    }

    if (count == tag_num) {
        if (tag_ovl->ret_tag_idx == -1) {
            tag_ovl->ret_tag_idx = 0;
        }

        tag_ovl->sel_tag_idx = tag_ovl->ret_tag_idx;
        if (tag_ovl->sel_tag_idx == 0) {
            mTG_init_tag_data_item_win(submenu);
        }
    }
}

static int mTG_quest_disp_up_check(mTG_tag_c* tag) {
    int res = FALSE;

    if ((tag->table == mTG_TABLE_ITEM && tag->tag_row == 0) || (tag->table == mTG_TABLE_MAIL && tag->tag_row == 2)) {
        res = TRUE;
    }

    return res;
}

static int mTG_quest_disp_low_check(mTG_tag_c* tag) {
    int res = FALSE;

    if ((tag->table == mTG_TABLE_MAIL && tag->tag_row == 1)) {
        res = TRUE;
    }

    return res;
}

typedef struct tag_win_arrow_ofs_s {
    f32 ofs[2];
    f32 scale[2];
} mTG_win_arrow_ofs_c;

typedef struct tag_win_data_s {
    f32 _00[2];
    f32 _08[2];
    f32 _10;
    f32 _14;
    f32 _18;
    f32 _1C[2];
    f32 _24[2];
    mTG_win_arrow_ofs_c* arrow_offset;
} mTG_win_data_c;

enum {
    mTG_WIN_TYPE_ITEM,
    mTG_WIN_TYPE_SELECT,
    mTG_WIN_TYPE_SELECT2,

    mTG_WIN_TYPE_NUM
};

static void mTG_set_tag_win_scale_p(mTG_tag_c* tag, int win_type, f32 x, f32 y) {
    static mTG_win_arrow_ofs_c tag_win_data_pix_arrow_offset_item = {
        { -3.5f, -3.5f },
        { -7.0f, 3.5f },
    };

    static mTG_win_arrow_ofs_c tag_win_data_pix_arrow_offset_quest = {
        { -1.0f, 21.0f },
        { -11.0f, 5.0f },
    };

    static mTG_win_arrow_ofs_c tag_win_data_pix_arrow_offset_quest_up = {
        { -13.0f, 4.0f },
        { -6.0f, 10.0f },
    };

    static mTG_win_arrow_ofs_c tag_win_data_pix_arrow_offset_quest_low = {
        { -13.0f, 56.0f },
        { -6.0f, -2.0f },
    };

    static mTG_win_arrow_ofs_c tag_win_data_pix_arrow_offset_select = {
        { 6.125f, 15.75f },
        { 0.875f, 26.25f },
    };

    static mTG_win_data_c tag_win_data_pix[] = {
        {
            { 0.2972973f, 0.8125f },
            { -64.75f, 14.0f },
            0.875f,
            21.0f,
            84.0f,
            { 8.75f, -4.375f },
            { 4.375f, -2.625f },
            &tag_win_data_pix_arrow_offset_item,
        },
        {
            { 0.5217391f, 0.88235295f },
            { -92.0f, 34.0f },
            1.0f,
            52.5f,
            67.5f,
            { 22.0f, -12.0f },
            { 10.0f, -4.0f },
            &tag_win_data_pix_arrow_offset_quest,
        },
        {
            { 0.5714286f, 0.43243244f },
            { -61.25f, 64.75f },
            0.875f,
            31.5f,
            42.0f,
            { 22.75f, -14.875f },
            { 5.25f, -15.75f },
            &tag_win_data_pix_arrow_offset_select,
        },
    };

    mTG_win_data_c* win_data = &tag_win_data_pix[win_type];
    mTG_win_arrow_ofs_c* arrow_data = win_data->arrow_offset;
    int i;

    tag->_04[0] = (x - win_data->_14) / win_data->_18;

    if (y != 0.0f) {
        tag->_04[1] = (y - 28.0f) / 42.0f;
    } else {
        tag->_04[1] = tag->_04[0];
    }

    if (win_type == mTG_WIN_TYPE_SELECT) {
        if (mTG_quest_disp_up_check(tag) == TRUE) {
            arrow_data = &tag_win_data_pix_arrow_offset_quest_up;
        } else if (mTG_quest_disp_low_check(tag) == TRUE) {
            arrow_data = &tag_win_data_pix_arrow_offset_quest_low;
        }
    }

    tag->_34 = win_data->_10;
    for (i = 0; i < 2; i++) {
        tag->body_scale[i] = win_data->_00[i] + tag->_04[i] * (1.0f - win_data->_00[i]);
        tag->arrow_scale[i] = 1.0f;
        tag->text_ofs[i] = win_data->_1C[i] + win_data->_24[i] * tag->_04[i] + win_data->_08[i] * tag->body_scale[i];
        tag->body_ofs[i] =
            (arrow_data->ofs[i] + arrow_data->scale[i] * tag->_04[i]) - win_data->_08[i] * tag->body_scale[i];
    }
}

static int mTG_get_table_idx(mTG_tag_c* tag) {
    int idx = tag->tag_col + tag->tag_row * mTG_table_data[tag->table].col_num;

    if (idx >= 0) {
        return idx;
    }

    return 0;
}

static int mTG_check_edge_right_item(mTG_tag_c* tag) {
    f32 edge;
    int res = FALSE;

    if (tag->str2_type == mTG_QSTR_TYPE_NONE) {
        edge = 64.75f;
    } else {
        edge = 92.0f;
    }

    if (tag->base_pos[0] + tag->body_ofs[0] + tag->body_scale[0] * edge <= 146.0f) {
        res = TRUE;
    }

    return res;
}

static void mTG_calc_right_edge_select(mTG_tag_c* tag, f32* right_edge) {
    f32 margin = tag->body_scale[0] * 122.5f * 0.5f;

    *right_edge = tag->base_pos[0] + tag->body_ofs[0] + margin;
}

static int mTG_check_edge_right_select(mTG_tag_c* tag, f32* right_edge) {
    f32 margin = tag->body_scale[0] * 122.5f * 0.5f;
    int res = FALSE;

    *right_edge = (tag->base_pos[0] + tag->body_ofs[0] + margin) - 134.0f;

    if (*right_edge <= 0.0f) {
        res = TRUE;
    }

    return res;
}

/* @unused @fabricated */
static int mTG_check_edge_left_select(mTG_tag_c* tag, f32* left_edge) {
    f32 margin = tag->body_scale[0] * 122.5f * 0.5f;
    int res = FALSE;

    *left_edge = (tag->base_pos[0] + tag->body_ofs[0] - margin) - -134.0f;

    if (*left_edge <= 0.0f) {
        res = TRUE;
    }

    return res;
}

static int mTG_check_edge_foot_select(mTG_tag_c* tag) {
    f32 margin = (tag->body_scale[1] * 129.5f) * 0.5f;
    f32 tmp;
    int res = FALSE;

    tmp = (tag->base_pos[1] + tag->body_ofs[1]) - margin;
    tag->flags &= ~mTG_TAG_FLAG_EDGE_FOOT_SELECT;
    if (tmp - 3.0f >= -120.0f) {
        tag->flags |= mTG_TAG_FLAG_EDGE_FOOT_SELECT;
        res = TRUE;
    }

    return res;
}

static int mTG_get_max_col_width_data(mTG_tag_word_c** tag_word, int lines) {
    int max_col_width = 0;
    int i;

    if (tag_word != NULL) {
        for (i = 0; i < lines; i++) {
            int len = mMl_strlen(tag_word[i]->str, mTG_TAG_STR_LEN, CHAR_SPACE);
            int width = mFont_GetStringWidth(tag_word[i]->str, len, TRUE);

            if (width > max_col_width) {
                max_col_width = width;
            }
        }
    }

    return max_col_width;
}

static void mTG_get_col_width_and_line_select(mTG_tag_c* tag, mTG_tag_data_c* tag_data, f32* max_width,
                                              f32* max_height) {
    *max_width = mTG_get_max_col_width_data(tag_data->words, tag_data->lines);

    switch (tag->type) {
        case mTG_TYPE_CP_DELETE2: {
            *max_height = (f32)(tag_data->lines + 2) * 16.0f;
            *max_width = mFont_GetStringWidth(mTG_tag_str_iidesuka, sizeof(mTG_tag_str_iidesuka), TRUE);
            break;
        }

        case mTG_TYPE_DUMP_MAIL:
        case mTG_TYPE_DUMP_MAIL_MARK_CONF:
        case mTG_TYPE_DUMP_ITEM: {
            f32 width;

            *max_height = (f32)(tag_data->lines + 1) * 16.0f;
            width = mFont_GetStringWidth(mTG_tag_str_suteruno, sizeof(mTG_tag_str_suteruno), TRUE);

            if (width > *max_width) {
                *max_width = width;
            }
            break;
        }

        case mTG_TYPE_TAG_PUT_CHK: {
            *max_width = mFont_GetStringWidth(mTG_tag_str_put_chk1, sizeof(mTG_tag_str_put_chk1), TRUE);
            *max_height = (f32)(tag_data->lines + 2) * 16.0f;
            break;
        }

        default: {
            *max_height = (f32)tag_data->lines * 16.0f;
            break;
        }
    }
}

static Mail_c* mTG_get_mail_pointer(Submenu* submenu, mHD_Ovl_c* hand_ovl) {
    mCM_Ovl_c* cpmail_ovl = submenu->overlay->cpmail_ovl;
    int table;
    int idx;
    int page;

    if (hand_ovl != NULL) {
        table = hand_ovl->info.hold_tbl;
        idx = hand_ovl->info.hold_idx;
        page = hand_ovl->info.catch_pg;
    } else {
        mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];

        table = tag->table;
        idx = mTG_get_table_idx(tag);

        if (cpmail_ovl != NULL) {
            page = cpmail_ovl->page_order[0];
        } else {
            page = 0;
        }
    }

    switch (table) {
        case mTG_TABLE_CPMAIL:
            return &cpmail_ovl->card_mail->mail[page][idx];
        case mTG_TABLE_MBOX:
            return &Common_Get(now_home)->mailbox[idx];
        default:
            return &Now_Private->mail[idx];
    }
}

static int mTG_strcat(u8* str0, u8* str1, int str0_max, int str1_max) {
    int str0_len = mMl_strlen(str0, str0_max, CHAR_SPACE);
    int str1_len = mMl_strlen(str1, str1_max, CHAR_SPACE);

    if ((str0_len + str1_len) > str0_max) {
        str1_len -= (str0_len + str1_len) - str0_max;
    }

    if (str1_len > 0) {
        memcpy(&str0[str0_len], str1, str1_len);
        str0_len += str1_len;
    }

    return str0_len;
}

static int mTG_strcpy(u8* dst, u8* src, int dst_max, int src_max) {
    int src_len;

    mem_clear(dst, dst_max, CHAR_SPACE);

    src_len = mMl_strlen(src, src_max, CHAR_SPACE);
    if (src_len < dst_max) {
        dst_max = src_len;
    }

    memcpy(dst, src, dst_max);
    return dst_max;
}

static int mTG_strcat_color(u8* str, u8* src, int str_max, int src_max, const rgba_t* color) {
    /* 0x7F 0x05 0x00 0x00 0x00 0x00 */
    static u8 font_color_base[] = { CHAR_CONTROL_CODE, mFont_CONT_CODE_SET_COLOR_CHAR, 0, 0, 0, 0 };
    int str_len = mMl_strlen(str, str_max, CHAR_SPACE);
    int src_len = mMl_strlen(src, src_max, CHAR_SPACE);

    if ((str_max - src_len) - str_len > 1) {
        int col_len = mTG_strcat(str, font_color_base, str_max, sizeof(font_color_base));

        if ((col_len + src_len) > str_max) {
            src_len -= (col_len + src_len) - str_max;
        }
        
        str[col_len - 4] = color->r;
        str[col_len - 3] = color->g;
        str[col_len - 2] = color->b;
        str[col_len - 1] = (u8)src_len;
        memcpy(str + col_len, src, src_len);
        str_len = col_len + src_len;
    }

    return str_len;
}

typedef struct tag_str_info_s {
    u8 str[mTG_TAG_SEL_STRING_LEN];
    int str_len;
    int color_idx;
} mTG_str_info_c;

enum {
    mTG_MAIL_TYPE_NONE,
    mTG_MAIL_TYPE_FROM,
    mTG_MAIL_TYPE_FROM_THE,
    mTG_MAIL_TYPE_FROM2,
    mTG_MAIL_TYPE_FROM_S,
    mTG_MAIL_TYPE_FROM3,

    mTG_MAIL_TYPE_NUM
};

enum {
    mTG_MAIL_NAME_COLOR_RED,
    mTG_MAIL_NAME_COLOR_VIOLET,
    mTG_MAIL_NAME_COLOR_GREEN,
    mTG_MAIL_NAME_COLOR_PURPLE,
    mTG_MAIL_NAME_COLOR_INDIGO,
    mTG_MAIL_NAME_COLOR_PINK,
    mTG_MAIL_NAME_COLOR_BLACK,

    mTG_MAIL_NAME_COLOR_NUM
};

static int mTG_init_tag_data_item_win_sub_mail_item_mail(mTG_tag_c* tag, mTG_str_info_c* str_infos, Mail_c* mail) {
    int type = mTG_MAIL_TYPE_FROM;

    mTG_strcpy(str_infos[1].str, mail->header.sender.personalID.player_name, mTG_TAG_SEL_STRING_LEN, PLAYER_NAME_LEN);
    str_infos[1].str_len = PLAYER_NAME_LEN;

    if (mail->header.recipient.type == mMl_NAME_TYPE_MUSEUM) {
        str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_VIOLET;
        tag->str2_type = mTG_QSTR_TYPE_TO_MUSEUM;
        type = mTG_MAIL_TYPE_FROM_THE;
    } else if (mail->header.sender.type == mMl_NAME_TYPE_MUSEUM) {
        str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_GREEN;
        tag->str2_type = mTG_QSTR_TYPE_FROM_MUSEUM;
        type = mTG_MAIL_TYPE_FROM2;
    } else {
        str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_VIOLET;
        tag->str2_type = mTG_QSTR_TYPE_MAIL;
    }

    return type;
}

static int mTG_init_tag_data_item_win_sub_mail_item_xmas(mTG_tag_c* tag, mTG_str_info_c* str_infos, Mail_c* mail) {
    mTG_strcpy(str_infos[1].str, mNpc_GetNpcWorldNameP(SP_NPC_SANTA), mTG_TAG_SEL_STRING_LEN, PLAYER_NAME_LEN);
    str_infos[1].str_len = PLAYER_NAME_LEN;
    str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_PURPLE;
    tag->str2_type = mTG_QSTR_TYPE_XMAS_SNOWMAN_SPNPC;

    return mTG_MAIL_TYPE_FROM;
}

static int mTG_init_tag_data_item_win_sub_mail_item_tanukiti(mTG_tag_c* tag, mTG_str_info_c* str_infos, Mail_c* mail) {
    mTG_strcpy(str_infos[1].str, mNpc_GetNpcWorldNameP(SP_NPC_SHOP_MASTER), mTG_TAG_SEL_STRING_LEN, PLAYER_NAME_LEN);
    str_infos[1].str_len = PLAYER_NAME_LEN;
    str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_INDIGO;
    tag->str2_type = mTG_QSTR_TYPE_SHOP;

    return mTG_MAIL_TYPE_FROM;
}

static int mTG_init_tag_data_item_win_sub_mail_item_tunekiti(mTG_tag_c* tag, mTG_str_info_c* str_infos, Mail_c* mail) {
    mTG_strcpy(str_infos[1].str, mNpc_GetNpcWorldNameP(SP_NPC_BROKER), mTG_TAG_SEL_STRING_LEN, PLAYER_NAME_LEN);
    str_infos[1].str_len = PLAYER_NAME_LEN;
    str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_INDIGO;
    tag->str2_type = mTG_QSTR_TYPE_SHOP;

    return mTG_MAIL_TYPE_FROM;
}

static int mTG_init_tag_data_item_win_sub_mail_item_mother(mTG_tag_c* tag, mTG_str_info_c* str_infos, Mail_c* mail) {
    mTG_strcpy(str_infos[1].str, mother_str, mTG_TAG_SEL_STRING_LEN, sizeof(mother_str));
    str_infos[1].str_len = sizeof(mother_str);
    str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_INDIGO;
    tag->str2_type = mTG_QSTR_TYPE_MOTHER;

    return mTG_MAIL_TYPE_FROM2;
}

static int mTG_init_tag_data_item_win_sub_mail_item_omikuji(mTG_tag_c* tag, mTG_str_info_c* str_infos, Mail_c* mail) {
    mTG_strcpy(str_infos[1].str, mNpc_GetNpcWorldNameP(SP_NPC_EV_MIKO), mTG_TAG_SEL_STRING_LEN, PLAYER_NAME_LEN);
    str_infos[1].str_len = PLAYER_NAME_LEN;
    str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_INDIGO;
    tag->str2_type = mTG_QSTR_TYPE_OMIKUJI;

    return mTG_MAIL_TYPE_FROM_S;
}

static int mTG_init_tag_data_item_win_sub_mail_item_happy(mTG_tag_c* tag, mTG_str_info_c* str_infos, Mail_c* mail) {
    mTG_strcpy(str_infos[1].str, str_happy_room, mTG_TAG_SEL_STRING_LEN, sizeof(str_happy_room));
    str_infos[1].str_len = sizeof(str_happy_room);
    str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_GREEN;
    tag->str2_type = mTG_QSTR_TYPE_HAPPY_ROOM;

    return mTG_MAIL_TYPE_FROM;
}

static int mTG_init_tag_data_item_win_sub_mail_item_snowman(mTG_tag_c* tag, mTG_str_info_c* str_infos, Mail_c* mail) {
    mTG_strcpy(str_infos[1].str, mNpc_GetNpcWorldNameP(ETC_SNOWMAN_BALL_A), mTG_TAG_SEL_STRING_LEN, PLAYER_NAME_LEN);
    str_infos[1].str_len = PLAYER_NAME_LEN;
    str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_PURPLE;
    tag->str2_type = mTG_QSTR_TYPE_XMAS_SNOWMAN_SPNPC;

    return mTG_MAIL_TYPE_FROM;
}

static int mTG_init_tag_data_item_win_sub_mail_item_angler(mTG_tag_c* tag, mTG_str_info_c* str_infos, Mail_c* mail) {
    mTG_strcpy(str_infos[1].str, mNpc_GetNpcWorldNameP(SP_NPC_ANGLER), mTG_TAG_SEL_STRING_LEN, PLAYER_NAME_LEN);
    str_infos[1].str_len = PLAYER_NAME_LEN;
    str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_PURPLE;
    tag->str2_type = mTG_QSTR_TYPE_ANGLER;

    return mTG_MAIL_TYPE_FROM;
}

static int mTG_init_tag_data_item_win_sub_mail_item_postoffice(mTG_tag_c* tag, mTG_str_info_c* str_infos,
                                                               Mail_c* mail) {
    mTG_strcpy(str_infos[1].str, postoffice_str, mTG_TAG_SEL_STRING_LEN, sizeof(postoffice_str));
    str_infos[1].str_len = sizeof(postoffice_str);
    str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_GREEN;
    tag->str2_type = mTG_QSTR_TYPE_POST_OFFICE;

    return mTG_MAIL_TYPE_FROM2;
}

static int mTG_init_tag_data_item_win_sub_mail_item_sp_npc(mTG_tag_c* tag, mTG_str_info_c* str_infos, Mail_c* mail) {
    mTG_strcpy(str_infos[1].str, mail->header.sender.personalID.player_name, mTG_TAG_SEL_STRING_LEN, PLAYER_NAME_LEN);
    str_infos[1].str_len = PLAYER_NAME_LEN;
    str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_PURPLE;
    tag->str2_type = mTG_QSTR_TYPE_XMAS_SNOWMAN_SPNPC;

    return mTG_MAIL_TYPE_FROM;
}

// clang-format off
static rgba_t str_color[] = {
    { 205,  40,  40, 255 },
    { 100,  65, 195, 255 },
    {  60, 150,  65, 255 },
    { 165,  30, 255, 255 },
    {  60,  50, 155, 255 },
    { 225,  30, 220, 255 },
    {   0,   0,   0, 255 },
};
// clang-format on

static void mTG_init_tag_data_item_win_sub_mail_item_set_string(mTG_tag_c* tag, mTG_str_info_c* str_infos, int type) {
    switch (type) {
        case mTG_MAIL_TYPE_FROM: {
            mTG_strcat_color(tag->str0, str_infos[0].str, mTG_TAG_SEL_STRING_LEN, str_infos[0].str_len,
                             &str_color[str_infos[0].color_idx]);
            mTG_strcat(tag->str1, str_title1, mTG_TAG_SEL_STRING_LEN, sizeof(str_title1));
            mTG_strcat_color(tag->str1, str_infos[1].str, mTG_TAG_SEL_STRING_LEN, str_infos[1].str_len,
                             &str_color[str_infos[1].color_idx]);

            break;
        }

        case mTG_MAIL_TYPE_FROM_THE: {
            mTG_strcat(tag->str0, str_title4, mTG_TAG_SEL_STRING_LEN, sizeof(str_title4));
            mTG_strcat_color(tag->str0, str_infos[0].str, mTG_TAG_SEL_STRING_LEN, str_infos[0].str_len,
                             &str_color[str_infos[0].color_idx]);
            mTG_strcat(tag->str1, str_title1, mTG_TAG_SEL_STRING_LEN, sizeof(str_title1));
            mTG_strcat_color(tag->str1, str_infos[1].str, mTG_TAG_SEL_STRING_LEN, str_infos[1].str_len,
                             &str_color[str_infos[1].color_idx]);

            break;
        }

        case mTG_MAIL_TYPE_FROM2: {
            mTG_strcat_color(tag->str0, str_infos[0].str, mTG_TAG_SEL_STRING_LEN, str_infos[0].str_len,
                             &str_color[str_infos[0].color_idx]);
            mTG_strcat(tag->str1, str_title1, mTG_TAG_SEL_STRING_LEN, sizeof(str_title1));
            mTG_strcat_color(tag->str1, str_infos[1].str, mTG_TAG_SEL_STRING_LEN, str_infos[1].str_len,
                             &str_color[str_infos[1].color_idx]);

            break;
        }

        case mTG_MAIL_TYPE_FROM_S: {
            mTG_strcat_color(tag->str0, str_infos[0].str, mTG_TAG_SEL_STRING_LEN, str_infos[0].str_len,
                             &str_color[str_infos[0].color_idx]);
            mTG_strcat(tag->str0, str_title2, mTG_TAG_SEL_STRING_LEN, sizeof(str_title2));
            mTG_strcat(tag->str1, str_title1, mTG_TAG_SEL_STRING_LEN, sizeof(str_title1));
            mTG_strcat_color(tag->str1, str_infos[1].str, mTG_TAG_SEL_STRING_LEN, str_infos[1].str_len,
                             &str_color[str_infos[1].color_idx]);

            break;
        }

        case mTG_MAIL_TYPE_FROM3: {
            mTG_strcat_color(tag->str0, str_infos[0].str, mTG_TAG_SEL_STRING_LEN, str_infos[0].str_len,
                             &str_color[str_infos[0].color_idx]);
            mTG_strcat(tag->str1, str_title1, mTG_TAG_SEL_STRING_LEN, sizeof(str_title1));
            mTG_strcat_color(tag->str1, str_infos[1].str, mTG_TAG_SEL_STRING_LEN, str_infos[1].str_len,
                             &str_color[str_infos[1].color_idx]);

            break;
        }
    }
}

typedef int (*mTG_ITEM_WIN_SUB_MAIL_ITEM_PROC)(mTG_tag_c*, mTG_str_info_c*, Mail_c*);

static void mTG_init_tag_data_item_win_sub_mail_item(Submenu* submenu, mTG_tag_c* tag, Mail_c* mail,
                                                     mActor_name_t itemNo, int itemCond, int idx) {
    static mTG_ITEM_WIN_SUB_MAIL_ITEM_PROC proc[] = {
        &mTG_init_tag_data_item_win_sub_mail_item_mail,       &mTG_init_tag_data_item_win_sub_mail_item_xmas,
        &mTG_init_tag_data_item_win_sub_mail_item_tanukiti,   &mTG_init_tag_data_item_win_sub_mail_item_tunekiti,
        &mTG_init_tag_data_item_win_sub_mail_item_mother,     &mTG_init_tag_data_item_win_sub_mail_item_omikuji,
        &mTG_init_tag_data_item_win_sub_mail_item_happy,      &mTG_init_tag_data_item_win_sub_mail_item_tanukiti,
        &mTG_init_tag_data_item_win_sub_mail_item_snowman,    &mTG_init_tag_data_item_win_sub_mail_item_angler,
        &mTG_init_tag_data_item_win_sub_mail_item_postoffice, &mTG_init_tag_data_item_win_sub_mail_item_sp_npc,
    };
    static u8 present_str[7] = "Present";

    f32 scale = 0.875f;
    int win_type = mTG_WIN_TYPE_ITEM;
    int mail_type = mTG_MAIL_TYPE_NONE;
    mTG_str_info_c str_infos[3];
    int i;

    mem_clear(str_infos[0].str, mTG_TAG_SEL_STRING_LEN, CHAR_SPACE);
    mem_clear(str_infos[1].str, mTG_TAG_SEL_STRING_LEN, CHAR_SPACE);
    mem_clear(str_infos[2].str, mTG_TAG_SEL_STRING_LEN, CHAR_SPACE);

    if (itemNo == EMPTY_NO) {
        scale = 0.75f;
        win_type = mTG_WIN_TYPE_SELECT;
        mTG_strcpy(str_infos[0].str, mail->header.recipient.personalID.player_name, mTG_TAG_SEL_STRING_LEN,
                   PLAYER_NAME_LEN);
        str_infos[0].str_len = PLAYER_NAME_LEN;

        if (mail->content.mail_type == mMl_TYPE_MAIL && mail->header.recipient.type == mMl_NAME_TYPE_MUSEUM) {
            str_infos[0].color_idx = mTG_MAIL_NAME_COLOR_GREEN;
        } else {
            str_infos[0].color_idx = mTG_MAIL_NAME_COLOR_RED;
        }

        mail_type = (*proc[mail->content.mail_type])(tag, str_infos, mail);
    } else if (tag->table == mTG_TABLE_ITEM) {
        tag->str2_type = mTG_QSTR_TYPE_NONE;
        win_type = mTG_WIN_TYPE_SELECT;

        /* Show quest item info */
        if ((itemCond & mPr_ITEM_COND_QUEST)) {
            u8 str0[mTG_TAG_SEL_STRING_LEN];
            u8 str1[mTG_TAG_SEL_STRING_LEN];

            mem_clear(str0, mTG_TAG_SEL_STRING_LEN, CHAR_SPACE);
            mem_clear(str1, mTG_TAG_SEL_STRING_LEN, CHAR_SPACE);

            if (mQst_GetToFromName(str0, str1, idx) == TRUE) {
                mTG_strcpy(str_infos[0].str, str0, mTG_TAG_SEL_STRING_LEN, mTG_TAG_SEL_STRING_LEN);
                str_infos[0].str_len = mTG_TAG_SEL_STRING_LEN;
                str_infos[0].color_idx = mTG_MAIL_NAME_COLOR_RED;

                mTG_strcpy(str_infos[1].str, str1, mTG_TAG_SEL_STRING_LEN, mTG_TAG_SEL_STRING_LEN);
                str_infos[1].str_len = mTG_TAG_SEL_STRING_LEN;
                str_infos[1].color_idx = mTG_MAIL_NAME_COLOR_VIOLET;

                scale = 0.75f;
                mail_type = mTG_MAIL_TYPE_FROM3;
                tag->str2_type = mTG_QSTR_TYPE_ITEM;
            }
        }
    } else {
        tag->str2_type = mTG_QSTR_TYPE_NONE;
    }

    if (tag->str2_type == mTG_QSTR_TYPE_NONE) {
        if (itemCond == mPr_ITEM_COND_PRESENT) {
            mem_copy(tag->str0, present_str, sizeof(present_str));
        } else if (itemNo >= ITM_MY_ORG_UMBRELLA0 && itemNo <= ITM_MY_ORG_UMBRELLA7) {
            mem_copy(tag->str0, Now_Private->my_org[(itemNo - ITM_MY_ORG_UMBRELLA0) & 7].name,
                     mNW_ORIGINAL_DESIGN_NAME_LEN);
        } else {
            mIN_copy_name_str(tag->str0, itemNo);
        }

        win_type = mTG_WIN_TYPE_ITEM;
    }

    if (tag->str2_type != mTG_QSTR_TYPE_NONE) {
        if (tag->str2_type == mTG_QSTR_TYPE_ITEM) {
            mTG_strcpy(tag->str2, str_otodokemono, mTG_TAG_SEL_STRING_LEN, sizeof(str_otodokemono));
        } else if (tag->str2_type == mTG_QSTR_TYPE_OMIKUJI) {
            mTG_strcpy(tag->str2, str_omikuji, mTG_TAG_SEL_STRING_LEN, sizeof(str_omikuji));
        } else {
            mTG_strcpy(tag->str2, str_otegami, mTG_TAG_SEL_STRING_LEN, sizeof(str_otegami));
        }
    }

    mTG_init_tag_data_item_win_sub_mail_item_set_string(tag, str_infos, mail_type);

    {
        int str0_len = mMl_strlen(tag->str0, mTG_TAG_SEL_STRING_LEN, CHAR_SPACE);
        int str1_len = mMl_strlen(tag->str1, mTG_TAG_SEL_STRING_LEN, CHAR_SPACE);
        int str2_len = mMl_strlen(tag->str2, mTG_TAG_SEL_STRING_LEN, CHAR_SPACE);
        f32 width = mFont_GetStringWidth2(tag->str0, str0_len, TRUE);
        f32 str1_width = mFont_GetStringWidth2(tag->str1, str1_len, TRUE);
        f32 str2_width = mFont_GetStringWidth2(tag->str2, str2_len, TRUE);

        if (str1_width > width) {
            width = str1_width;
        }

        if (str2_width > width) {
            width = str2_width;
        }

        width *= scale;
        mTG_set_tag_win_scale_p(tag, win_type, width, 0.0f);
    }

    if (win_type == mTG_WIN_TYPE_SELECT && mTG_quest_disp_up_check(tag) == FALSE &&
        mTG_quest_disp_low_check(tag) == FALSE) {
        tag->body_ofs[1] += 8.0f;
    }

    if (mTG_check_edge_right_item(tag) == TRUE) {
        tag->arrow_dir = 1;
    } else {
        tag->body_ofs[0] *= -1.0f;
        tag->arrow_dir = 2;
    }

    submenu->overlay->tag_ovl->item_name_wait_time = mTG_get_item_name_wait_time(tag);
}

static void mTG_init_tag_data_set_base_pos(mTG_tag_c* tag) {
    switch (tag->table) {
        case mTG_TABLE_NEEDLEWORK:
            tag->base_pos[0] += -3.0f;
            tag->base_pos[1] += -7.0f;
            break;
        case mTG_TABLE_CPORIGINAL:
        case mTG_TABLE_CPORIGINAL_NW:
        case mTG_TABLE_GBA:
        case mTG_TABLE_GBA_NW:
        case mTG_TABLE_CARD:
            tag->base_pos[0] += -2.0f;
            tag->base_pos[1] += -5.0f;
            break;
        case mTG_TABLE_CATALOG_WC:
            tag->base_pos[0] += -8.75f;
            break;
        case mTG_TABLE_CPMAIL_WC:
            tag->base_pos[0] += -8.75f;
            break;
    }
}

static void mTG_init_tag_data_set_itemNo(mActor_name_t* itemNo, Mail_c** mail_pp, int* itemCond, Submenu* submenu,
                                         int idx) {
    switch (submenu->overlay->tag_ovl->tags[0].table) {
        case mTG_TABLE_ITEM:
            *itemNo = Now_Private->inventory.pockets[idx];
            *itemCond = mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, idx);
            break;
        case mTG_TABLE_PLAYER:
            *itemNo = Now_Private->equipment;
            break;
        case mTG_TABLE_HANIWA:
            *itemNo = Save_Get(homes[submenu->overlay->menu_info[mSM_OVL_HANIWA].data1]).haniwa.items[idx].item;
            break;
        case mTG_TABLE_COLLECT: {
            mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;

            *itemNo = inv_ovl->set_collect_itemNo_proc(idx, inv_ovl->page_order[0]);
            break;
        }
        case mTG_TABLE_MAIL:
        case mTG_TABLE_MBOX:
        case mTG_TABLE_CPMAIL:
            *mail_pp = mTG_get_mail_pointer(submenu, NULL);
            break;
        default:
            *itemNo = EMPTY_NO;
            break;
    }
}

static void mTG_init_tag_data_catalog_win(Submenu* submenu, int idx) {
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int len;
    f32 width;

    mem_copy(tag->str0, mTG_catalog_str[idx], mCL_TAG_STR_SIZE);
    len = mMl_strlen(tag->str0, mTG_TAG_STR_LEN, CHAR_SPACE);
    width = mFont_GetStringWidth(tag->str0, len, TRUE);
    mTG_set_tag_win_scale_p(tag, mTG_WIN_TYPE_ITEM, width * 0.875f, 0.0f);
    tag->body_ofs[0] *= -1.0f;
    tag->arrow_dir = 2;
    submenu->overlay->tag_ovl->item_name_wait_time = mTG_get_item_name_wait_time(tag);
}

static void mTG_init_tag_data_cpmail_wc_win(Submenu* submenu, int folder_idx) {
    mCM_Ovl_c* cpmail_ovl = submenu->overlay->cpmail_ovl;
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int len;

    mem_copy(tag->str0, cpmail_ovl->card_mail->folder_names[folder_idx], mCD_KEEP_MAIL_FOLDER_NAME_LEN);
    len = mMl_strlen(tag->str0, mCD_KEEP_MAIL_FOLDER_NAME_LEN, CHAR_SPACE);

    if (len <= 0 || cpmail_ovl->page_order[0] == tag->tag_row) {
        tag->arrow_dir = 0;
        tag->str2_type = mTG_QSTR_TYPE_NONE;
    } else {
        f32 width = mFont_GetStringWidth(tag->str0, len, TRUE);

        mTG_set_tag_win_scale_p(tag, mTG_WIN_TYPE_ITEM, width * 0.875f, 0.0f);
        tag->str2_type = mTG_QSTR_TYPE_NONE;
        tag->body_ofs[0] *= -1.0f;
        tag->arrow_dir = 2;
        submenu->overlay->tag_ovl->item_name_wait_time = mTG_get_item_name_wait_time(tag);
    }
}

static void mTG_init_tag_data_cporiginal_wc_win(Submenu* submenu) {
    mCO_Ovl_c* cporiginal_ovl = submenu->overlay->cporiginal_ovl;
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int len;

    mem_copy(tag->str0, mCO_get_folder_name(submenu, tag->tag_row), mCO_FOLDER_NAME_LEN);
    len = mMl_strlen(tag->str0, mCO_FOLDER_NAME_LEN, CHAR_SPACE);

    if (len <= 0 || mCO_top_folder(submenu) == tag->tag_row) {
        tag->arrow_dir = 0;
        tag->str2_type = mTG_QSTR_TYPE_NONE;
    } else {
        f32 width = mFont_GetStringWidth(tag->str0, len, TRUE);

        mTG_set_tag_win_scale_p(tag, mTG_WIN_TYPE_ITEM, width * 0.875f, 0.0f);
        tag->str2_type = mTG_QSTR_TYPE_NONE;
        tag->body_ofs[0] *= -1.0f;
        tag->arrow_dir = 2;
        submenu->overlay->tag_ovl->item_name_wait_time = mTG_get_item_name_wait_time(tag);
    }
}

static void mTG_init_tag_data_needlework_win(Submenu* submenu, int idx) {
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int len;

    tag->str2_type = mTG_QSTR_TYPE_NONE;
    if (tag->table == mTG_TABLE_CPORIGINAL) {
        int hide = mCO_check_hide_flg(submenu, mCO_top_folder(submenu), idx);

        if (hide) {
            tag->arrow_dir = 0;
            return;
        }
    } else {
        int hide = mNW_check_hide_flg(submenu, idx);

        if (hide) {
            tag->arrow_dir = 0;
            return;
        }
    }

    switch (tag->table) {
        case mTG_TABLE_CPORIGINAL:
            mem_copy(tag->str0, mCO_get_image_name(submenu, mCO_top_folder(submenu), idx),
                     mNW_ORIGINAL_DESIGN_NAME_LEN);
            break;
        case mTG_TABLE_GBA:
        case mTG_TABLE_CARD:
            mem_copy(tag->str0, mGB_get_image_name(submenu, idx), mNW_ORIGINAL_DESIGN_NAME_LEN);
            break;
        default:
            mem_copy(tag->str0, mNW_get_image_name(submenu, idx), mNW_ORIGINAL_DESIGN_NAME_LEN);
            break;
    }

    len = mMl_strlen(tag->str0, mNW_ORIGINAL_DESIGN_NAME_LEN, CHAR_SPACE);
    if (len <= 0) {
        tag->arrow_dir = 0;
    } else {
        f32 width = mFont_GetStringWidth(tag->str0, len, TRUE);

        mTG_set_tag_win_scale_p(tag, mTG_WIN_TYPE_ITEM, width * 0.875f, 0.0f);
        switch (tag->table) {
            case mTG_TABLE_CPORIGINAL:
            case mTG_TABLE_CPORIGINAL_NW:
            case mTG_TABLE_GBA:
            case mTG_TABLE_CARD:
                if (mTG_check_edge_right_item(tag) == TRUE) {
                    tag->arrow_dir = 1;
                } else {
                    tag->body_ofs[0] *= -1.0f;
                    tag->arrow_dir = 2;
                }
                break;
            default:
                tag->body_ofs[0] *= -1.0f;
                tag->arrow_dir = 2;
                break;
        }

        submenu->overlay->tag_ovl->item_name_wait_time = mTG_get_item_name_wait_time(tag);
    }
}

static void mTG_init_tag_data_item_win(Submenu* submenu) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[0];
    mActor_name_t itemNo = EMPTY_NO;
    Mail_c* mail = NULL;
    int itemCond = mPr_ITEM_COND_NORMAL;
    int idx = mTG_get_table_idx(tag);

    tag_ovl->sel_tag_idx = 0;
    mTG_set_hand_pos(submenu, tag->base_pos, tag->table, idx);
    mTG_init_tag_data_set_base_pos(tag);
    mem_clear(tag->str0, mTG_TAG_SEL_STRING_LEN, CHAR_SPACE);
    mem_clear(tag->str1, mTG_TAG_SEL_STRING_LEN, CHAR_SPACE);
    mem_clear(tag->str2, mTG_TAG_SEL_STRING_LEN, CHAR_SPACE);
    mTG_init_tag_data_set_itemNo(&itemNo, &mail, &itemCond, submenu, idx);

    if (itemNo != EMPTY_NO || (mail != NULL && mMl_check_not_used_mail(mail) == FALSE)) {
        mTG_init_tag_data_item_win_sub_mail_item(submenu, tag, mail, itemNo, itemCond, idx);
    } else {
        if (tag->table == mTG_TABLE_CATALOG_WC) {
            mTG_init_tag_data_catalog_win(submenu, idx);
        } else if (tag->table == mTG_TABLE_CPMAIL_WC) {
            mTG_init_tag_data_cpmail_wc_win(submenu, idx);
        } else if (tag->table == mTG_TABLE_CPORIGINAL_WC) {
            mTG_init_tag_data_cporiginal_wc_win(submenu);
        } else if (tag->table == mTG_TABLE_CPORIGINAL_NW || tag->table == mTG_TABLE_NEEDLEWORK ||
                   tag->table == mTG_TABLE_CPORIGINAL || tag->table == mTG_TABLE_GBA_NW ||
                   tag->table == mTG_TABLE_CARD || tag->table == mTG_TABLE_CARD_NW || tag->table == mTG_TABLE_GBA) {
            mTG_init_tag_data_needlework_win(submenu, idx);
        } else {
            tag->arrow_dir = 0;
        }
    }
}

static void mTG_init_tag_data_select_win_only(mTG_tag_c* tag, mTG_tag_data_c* data) {
    static f32 other_arrow_min_offset[][2] = {
        { 6.125f, 15.75f },
        { -4.375f, 15.75f },
        { 4.375f, -15.75f },
        { -6.125f, -15.75f },
    };

    static f32 other_arrow_offset_dis[][2] = {
        { 0.875f, 26.25f },
        { 0.875f, 26.25f },
        { -0.875f, -26.25f },
        { -0.875f, -26.25f },
    };

    f32 dist_right;
    f32 max_width;
    f32 max_height;
    int edge_right;
    int edge_foot;
    f32* min_ofs_p;
    f32* ofs_dis_p;
    int idx;
    f32 dir_x;
    f32 dir_y;

    mTG_get_col_width_and_line_select(tag, data, &max_width, &max_height);
    mTG_set_tag_win_scale_p(tag, mTG_WIN_TYPE_SELECT2, max_width * 0.875f, max_height * 0.875f);
    edge_right = mTG_check_edge_right_select(tag, &dist_right);
    edge_foot = mTG_check_edge_foot_select(tag);

    if (edge_right) {
        tag->arrow_dir = 1;
        dir_x = 1.0f;
        if (edge_foot) {
            idx = 0;
            dir_y = -1.0f;
        } else {
            idx = 2;
            dir_y = 1.0f;
        }
    } else {
        tag->arrow_dir = 2;
        dir_x = -1.0f;
        if (edge_foot) {
            idx = 1;
            dir_y = -1.0f;
        } else {
            idx = 3;
            dir_y = 1.0f;
        }
    }

    min_ofs_p = other_arrow_min_offset[idx];
    ofs_dis_p = other_arrow_offset_dis[idx];

    tag->body_ofs[0] = min_ofs_p[0] + ofs_dis_p[0] * tag->_04[0] + tag->body_scale[0] * 61.25f * dir_x;
    tag->body_ofs[1] = min_ofs_p[1] + ofs_dis_p[1] * tag->_04[1] + (tag->body_scale[1] * 64.75f - 6.0f) * dir_y;
}

typedef struct add_item_data_s {
    f32 down_min[2][2];
    f32 down_ofs[2][2];

    f32 up_min[2][2];
    f32 up_ofs[2][2];
} mTG_add_item_data_c;

static void mTG_init_tag_data_select_win_after_item(mTG_tag_c* tag, mTG_tag_c* item_tag, mTG_tag_data_c* tag_data) {
    // clang-format off
    static mTG_add_item_data_c tag_add_item_data[] = {
        {
            { {  27.125f,  1.750f }, {  54.250f,  1.750f } }, /* down_min */
            { {  27.125f, -1.750f }, {  54.250f, -1.750f } }, /* down_ofs */

            { { -29.750f,  6.125f }, { -28.875f,  8.750f } }, /* up_min */
            { { -29.750f, -6.125f }, { -28.875f, -8.750f } }, /* up_ofs */
        },
        {
            { {  52.500f,  4.375f }, {  39.375f,  0.000f } },
            { {  52.500f, -4.375f }, {  39.375f,  0.000f } },
            
            { { -27.125f,  7.000f }, { -28.000f,  8.750f } },
            { { -27.125f, -7.000f }, { -28.000f, -8.750f } },
        },
    };
    // clang-format on

    int left_flag;
    mTG_add_item_data_c* data_p;
    f32 scale_x;
    f32 scale_y;
    f32 dist_right;
    f32 max_width;
    f32 max_height;
    int tmp;
    int idx;

    mTG_get_col_width_and_line_select(tag, tag_data, &max_width, &max_height);
    mTG_set_tag_win_scale_p(tag, mTG_WIN_TYPE_SELECT2, max_width * 0.875f, max_height * 0.875f);

    left_flag = FALSE;
    if (item_tag->body_ofs[0] < 0.0f) {
        left_flag = TRUE;
    }

    if (item_tag->str2_type != mTG_QSTR_TYPE_NONE) {
        scale_x = 184.0f;
        scale_y = 68.0f;
        data_p = &tag_add_item_data[1];
    } else {
        scale_x = 129.5f;
        scale_y = 28.0f;
        data_p = &tag_add_item_data[0];
    }

    tag->base_pos[1] += data_p->down_min[0][1] + (item_tag->body_ofs[1] - item_tag->body_scale[1] * scale_y * 0.5f) +
                        item_tag->_04[1] * data_p->down_min[1][1];
    tag->body_ofs[1] = (data_p->up_min[0][1] + tag->_04[1] * data_p->up_min[1][1]) - tag->body_scale[1] * 129.5f * 0.5f;

    tag->base_pos[0] += item_tag->body_ofs[0] - item_tag->body_scale[0] * scale_x * 0.5f;
    tag->body_ofs[0] = tag->body_scale[0] * 122.5f * 0.5f;

    tmp = mTG_check_edge_foot_select(tag);
    if (tmp && item_tag->table == mTG_TABLE_ITEM && item_tag->tag_row == 1 && mTG_label_table[tag->type].lines == 2) {
        tmp = FALSE;
    }

    if (tmp) {
        tag->base_pos[0] += data_p->down_min[0][0] + item_tag->_04[0] * data_p->down_min[1][0];
        tag->body_ofs[0] += data_p->up_min[0][0] + tag->_04[0] * data_p->up_min[1][0];
        mTG_calc_right_edge_select(tag, &dist_right);

        idx = 0;
        if (dist_right >= 131.0f) {
            if (dist_right >= 167.0f) {
                idx = 2;
            } else {
                idx = 1;
            }
        }

        if (idx == 2 || left_flag) {
            f32 xofs;

            tag->base_pos[0] =
                (item_tag->base_pos[0] + item_tag->body_ofs[0] + item_tag->body_scale[0] * scale_x * 0.5f) -
                (data_p->down_min[0][0] + item_tag->_04[0] * data_p->down_min[1][0]);
            tag->body_ofs[0] =
                -(tag->body_scale[0] * 122.5f * 0.5f) - (data_p->up_min[0][0] + tag->_04[0] * data_p->up_min[1][0]);
            xofs = (tag->base_pos[0] + tag->body_ofs[0] - tag->body_scale[0] * 122.5f * 0.5f) - -134.0f;

            if (xofs < 0.0f) {
                tag->body_ofs[0] -= xofs;
            }
        } else if (idx == 1) {
            tag->base_pos[0] -= (dist_right - 131.0f);
        }
    } else {
        f32 yofs;

        tag->base_pos[1] = item_tag->base_pos[1] + item_tag->body_ofs[1] + item_tag->body_scale[1] * scale_y * 0.5f +
                           data_p->down_ofs[0][1] + item_tag->_04[1] * data_p->down_ofs[1][1];
        tag->body_ofs[1] =
            (tag->body_scale[1] * 129.5f * 0.5f) + (data_p->up_ofs[0][1] + tag->_04[1] * data_p->up_ofs[1][1]);
        yofs = (tag->base_pos[1] + tag->body_ofs[1] + tag->body_scale[1] * 129.5f * 0.5f);

        if (yofs > 120.0f) {
            tag->base_pos[1] -= yofs - 120.0f;
        }

        tag->base_pos[0] += data_p->down_ofs[0][0] + item_tag->_04[0] * data_p->down_ofs[1][0];
        tag->body_ofs[0] += data_p->up_ofs[0][0] + tag->_04[0] * data_p->up_ofs[1][0];

        mTG_calc_right_edge_select(tag, &dist_right);

        idx = 0;
        if (dist_right >= 131.0f) {
            if (dist_right >= 167.0f) {
                idx = 2;
            } else {
                idx = 1;
            }
        }

        if (idx == 2 || left_flag) {
            f32 xofs;

            tag->base_pos[0] =
                (item_tag->base_pos[0] + item_tag->body_ofs[0] + item_tag->body_scale[0] * scale_x * 0.5f) -
                (data_p->down_ofs[0][0] + item_tag->_04[0] * data_p->down_ofs[1][0]);
            tag->body_ofs[0] =
                -(tag->body_scale[0] * 122.5f * 0.5f) - (data_p->up_ofs[0][0] + tag->_04[0] * data_p->up_ofs[1][0]);
            xofs = (tag->base_pos[0] + tag->body_ofs[0] - tag->body_scale[0] * 122.5f * 0.5f) - -134.0f;

            if (xofs < 0.0f) {
                tag->body_ofs[0] -= xofs;
            }
        } else if (idx == 1) {
            tag->base_pos[0] -= (dist_right - 131.0f);
        }
    }

    tag->arrow_dir = 0;
}

static void mTG_init_tag_data_select_win_after_select(mTG_tag_c* tag, mTG_tag_c* parent_tag, mTG_tag_data_c* tag_data) {
    f32 dist_right;
    f32 line;
    f32 col;
    f32 pos;

    mTG_get_col_width_and_line_select(tag, tag_data, &col, &line);
    mTG_set_tag_win_scale_p(tag, mTG_WIN_TYPE_SELECT2, col * 0.875f, line * 0.875f);
    tag->arrow_dir = 0;
    pos = tag->base_pos[1];

    tag->base_pos[0] += tag->_04[0] * -0.875f + -0.875f;
    tag->base_pos[1] += tag->_04[1] * 8.75f + 6.125f;
    tag->base_pos[1] -= 7.0f;
    tag->body_ofs[0] = tag->body_scale[0] * 61.25f;
    tag->body_ofs[1] = tag->body_scale[1] * -64.75f;

    if (mTG_check_edge_right_select(tag, &dist_right) == FALSE) {
        tag->body_ofs[0] -= dist_right;
    }

    if (mTG_check_edge_foot_select(tag) == FALSE) {
        f32 tmp;

        tag->body_ofs[1] *= -1.0f;
        tag->base_pos[1] = pos - (tag->_04[1] * 8.75f + 6.125f);
        tag->base_pos[1] += 7.0f;

        tmp = tag->body_scale[1] * 129.5f * 0.5f + (tag->base_pos[1] + tag->body_ofs[1]);
        if (tmp > 120.0f) {
            tag->base_pos[1] -= tmp - 120.0f;
        }
    }
}

static void mTG_init_tag_data(Submenu* submenu, int table, int type, f32 base_x, f32 base_y, int idx_x, int idx_y) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_data_c* tag_data = &mTG_label_table[type];
    mTG_tag_c* tag = &tag_ovl->tags[tag_ovl->sel_tag_idx];
    mTG_tag_c* item_tag = &tag_ovl->tags[0];
    mTG_tag_c* parent_tag;

    if (tag_ovl->sel_tag_idx > 0) {
        parent_tag = &tag_ovl->tags[tag_ovl->sel_tag_idx - 1];
    } else {
        parent_tag = NULL;
    }

    tag->type = type;
    tag->table = table;
    tag->tag_col = idx_x;
    tag->tag_row = idx_y;
    tag->scale = 0.0f;

    if (tag_ovl->sel_tag_idx == 0) {
        mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
        int table_idx = mTG_get_table_idx(item_tag);

        hand_ovl->info.type = 1;
        mTG_init_tag_data_item_win(submenu);
        mTG_set_hand_pos(submenu, hand_ovl->info.pos, item_tag->table, table_idx);
    } else {
        tag->base_pos[0] = base_x;
        tag->base_pos[1] = base_y;

        if (tag_ovl->sel_tag_idx == 1) {
            if (item_tag->arrow_dir != 0) {
                mTG_init_tag_data_select_win_after_item(tag, item_tag, tag_data);
            } else {
                mTG_init_tag_data_select_win_only(tag, tag_data);
            }
        } else {
            mTG_init_tag_data_select_win_after_select(tag, parent_tag, tag_data);
        }
    }
}

static void mTG_chg_tag_func(Submenu* submenu, int table, int type, int idx, f32 base_x, f32 base_y) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_data_table_c* data_table = &mTG_table_data[table];
    int idx_x;
    int idx_y;

    idx_y = idx / data_table->col_num;
    idx_x = idx - (idx_y * data_table->col_num);

    if (tag_ovl->sel_tag_idx < 3) {
        tag_ovl->sel_tag_idx++;
        tag_ovl->ret_tag_idx = tag_ovl->sel_tag_idx;
        mTG_init_tag_data(submenu, table, type, base_x, base_y, idx_x, idx_y);
    }
}

static void mTG_chg_tag_func2(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag, int type) {
    // clang-format off
    mTG_chg_tag_func(
        submenu,
        tag->table,
        type,
        0,
        tag->base_pos[0] + menu_info->position[0] + (tag->body_ofs[0] + tag->text_ofs[0] + -3.5f),
        tag->base_pos[1] + menu_info->position[1] + ((tag->body_ofs[1] + tag->text_ofs[1] - tag->tag_row * 16.0f) - 8.0f) * 0.875f
    );
    // clang-format on
}

static int mTG_check_item_on_mail(mActor_name_t item, int cond) {
    int res = TRUE;

    if (cond != mPr_ITEM_COND_NORMAL ||
        ((item >= ITM_EXCERCISE_CARD00 && item <= ITM_EXCERCISE_CARD12) || item == ITM_KNIFE_AND_FORK)) {
        res = FALSE;
    } else if (ITEM_IS_ITEM1(item)) {
        int cat = ITEM_NAME_GET_CAT(item);

        if (cat == ITEM1_CAT_KABU || cat == ITEM1_CAT_FISH || cat == ITEM1_CAT_INSECT) {
            res = FALSE;
        }
    }

    return res;
}

static int mTG_check_put_unit(xyz_t* pos_p) {
    GAME_PLAY* play = (GAME_PLAY*)gamePT;
    int ux;
    int uz;
    int res = TRUE;

    mFI_Wpos2UtNum(&ux, &uz, *pos_p);

    if (mRlib_snowman_ball_unit_check_from_pos(play, pos_p)) {
        res = FALSE;
    } else if (mCoBG_CheckAcceptDesignSign(pos_p) == FALSE) {
        res = FALSE;
    } else {
        mCoBG_Collision_u* col = mFI_UtNum2UtCol(ux, uz);

        if (mCoBG_GetHoleNumber_ClData(col) > 0) {
            res = FALSE;
        }
    }

    return res;
}

static int mTG_put_place_check(xyz_t* pos_p, int plant_flag, int unit_flag) {
    int res = TRUE;

    if (unit_flag) {
        res = mTG_check_put_unit(pos_p);
    }

    if (res == TRUE) {
        if (plant_flag) {
            if (mCoBG_CheckPlant(*pos_p) == -1) {
                res = FALSE;
            }
        } else {
            res = mCoBG_CheckPlace(*pos_p);
        }
    }

    return res;
}

static void mTG_check_direction_put_pos(int* dir_p) {
    if (*dir_p < 0) {
        (*dir_p) += 8;
    } else if (*dir_p >= 8) {
        (*dir_p) -= 8;
    }
}

static int mTG_check_wall_put_pos(const xyz_t* start_pos_p, const xyz_t* end_pos_p) {
    mCoBG_Check_c bg_check;
    int res = FALSE;

    bg_check.result.hit_wall = 0;
    bg_check.result.hit_attribute_wall = 0;

    mCoBG_VirtualBGCheck(NULL, &bg_check, start_pos_p, end_pos_p, 0, FALSE, TRUE, 10.0f, -20.0f, 1, 1, 0);
    if (bg_check.result.hit_wall != 0 || bg_check.result.hit_attribute_wall != 0) {
        res = TRUE;
    }

    return res;
}

static int mTG_check_pos_slope(xyz_t* pos_p) {
    // clang-format off
    static f32 offset_pos[][2] = {
        {                  0.0f,  mFI_UT_WORLDSIZE_Z_F },
        {  mFI_UT_WORLDSIZE_X_F,  mFI_UT_WORLDSIZE_Z_F },
        {  mFI_UT_WORLDSIZE_X_F,                  0.0f },
        {  mFI_UT_WORLDSIZE_X_F, -mFI_UT_WORLDSIZE_Z_F },
        {                  0.0f, -mFI_UT_WORLDSIZE_Z_F },
        { -mFI_UT_WORLDSIZE_X_F, -mFI_UT_WORLDSIZE_Z_F },
        { -mFI_UT_WORLDSIZE_X_F,                  0.0f },
        { -mFI_UT_WORLDSIZE_X_F,  mFI_UT_WORLDSIZE_Z_F },
    };
    // clang-format on

    int res = TRUE;
    int i;

    for (i = 0; i < 8; i++) {
        xyz_t pos;
        mCoBG_Collision_u* col;

        pos.x = pos_p->x + offset_pos[i][0];
        pos.z = pos_p->z + offset_pos[i][1];
        pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(pos, 0.0f);

        col = mFI_GetUnitCol(pos);
        if (mCoBG_GetHoleNumber_ClData(col) > 0 || pos_p->y != pos.y) {
            res = FALSE;
            break;
        }
    }

    return res;
}

// clang-format off
#define mTG_SEARCH_BAD_ITEM(item) ( \
    (item) == TREE_S0 || \
    (item) == TREE_S1 || \
    (item) == TREE_S2 || \
    (item) == TREE || \
    (item) == TREE_1000BELLS_S0 || \
    (item) == TREE_1000BELLS_S1 || \
    (item) == TREE_1000BELLS_S2 || \
    (item) == TREE_1000BELLS || \
    (item) == TREE_10000BELLS_S0 || \
    (item) == TREE_10000BELLS_S1 || \
    (item) == TREE_10000BELLS_S2 || \
    (item) == TREE_10000BELLS || \
    (item) == TREE_30000BELLS_S0 || \
    (item) == TREE_30000BELLS_S1 || \
    (item) == TREE_30000BELLS_S2 || \
    (item) == TREE_30000BELLS || \
    (item) == TREE_100BELLS_S0 || \
    (item) == TREE_100BELLS_S1 || \
    (item) == TREE_100BELLS_S2 || \
    (item) == TREE_100BELLS || \
    (item) == CEDAR_TREE_S0 || \
    (item) == CEDAR_TREE_S1 || \
    (item) == CEDAR_TREE_S2 || \
    (item) == CEDAR_TREE || \
    (item) == GOLD_TREE_S0 || \
    (item) == GOLD_TREE_S1 || \
    (item) == GOLD_TREE_S2 || \
    (item) == GOLD_TREE || \
    (item) == GOLD_TREE_SHOVEL || \
    (item) == TREE_APPLE_S0 || \
    (item) == TREE_APPLE_S1 || \
    (item) == TREE_APPLE_S2 || \
    (item) == TREE_APPLE_NOFRUIT_0 || \
    (item) == TREE_APPLE_NOFRUIT_1 || \
    (item) == TREE_APPLE_NOFRUIT_2 || \
    (item) == TREE_APPLE_FRUIT || \
    (item) == TREE_ORANGE_S0 || \
    (item) == TREE_ORANGE_S1 || \
    (item) == TREE_ORANGE_S2 || \
    (item) == TREE_ORANGE_NOFRUIT_0 || \
    (item) == TREE_ORANGE_NOFRUIT_1 || \
    (item) == TREE_ORANGE_NOFRUIT_2 || \
    (item) == TREE_ORANGE_FRUIT || \
    (item) == TREE_PEACH_S0 || \
    (item) == TREE_PEACH_S1 || \
    (item) == TREE_PEACH_S2 || \
    (item) == TREE_PEACH_NOFRUIT_0 || \
    (item) == TREE_PEACH_NOFRUIT_1 || \
    (item) == TREE_PEACH_NOFRUIT_2 || \
    (item) == TREE_PEACH_FRUIT || \
    (item) == TREE_PEAR_S0 || \
    (item) == TREE_PEAR_S1 || \
    (item) == TREE_PEAR_S2 || \
    (item) == TREE_PEAR_NOFRUIT_0 || \
    (item) == TREE_PEAR_NOFRUIT_1 || \
    (item) == TREE_PEAR_NOFRUIT_2 || \
    (item) == TREE_PEAR_FRUIT || \
    (item) == TREE_CHERRY_S0 || \
    (item) == TREE_CHERRY_S1 || \
    (item) == TREE_CHERRY_S2 || \
    (item) == TREE_CHERRY_NOFRUIT_0 || \
    (item) == TREE_CHERRY_NOFRUIT_1 || \
    (item) == TREE_CHERRY_NOFRUIT_2 || \
    (item) == TREE_CHERRY_FRUIT || \
    (item) == TREE_PALM_S0 || \
    (item) == TREE_PALM_S1 || \
    (item) == TREE_PALM_S2 || \
    (item) == TREE_PALM_NOFRUIT_0 || \
    (item) == TREE_PALM_NOFRUIT_1 || \
    (item) == TREE_PALM_NOFRUIT_2 || \
    (item) == TREE_PALM_FRUIT || \
    (item) == TREE_BEES || \
    (item) == TREE_FTR || \
    (item) == TREE_LIGHTS || \
    (item) == TREE_PRESENT || \
    (item) == TREE_BELLS || \
    (item) == CEDAR_TREE_BELLS || \
    (item) == CEDAR_TREE_FTR || \
    (item) == CEDAR_TREE_BEES || \
    (item) == GOLD_TREE_BELLS || \
    (item) == GOLD_TREE_FTR || \
    (item) == GOLD_TREE_BEES || \
    (item) == CEDAR_TREE_LIGHTS || \
    ITEM_IS_HOLE((item)) || \
    (item) == HOLE_SHINE || \
    IS_ITEM_TREE_STUMP((item)) \
)
// clang-format on

static int mTG_search_put_pos2(ACTOR* player_actor, xyz_t* pos_tbl, int plant_flag, int param_4, int num_pos,
                               int param_6, int unit_flag, int param_8) {
    // clang-format off
    static f32 offset_pos[][2] = {
        {                  0.0f,  mFI_UT_WORLDSIZE_Z_F },
        {  mFI_UT_WORLDSIZE_X_F,  mFI_UT_WORLDSIZE_Z_F },
        {  mFI_UT_WORLDSIZE_X_F,                  0.0f },
        {  mFI_UT_WORLDSIZE_X_F, -mFI_UT_WORLDSIZE_Z_F },
        {                  0.0f, -mFI_UT_WORLDSIZE_Z_F },
        { -mFI_UT_WORLDSIZE_X_F, -mFI_UT_WORLDSIZE_Z_F },
        { -mFI_UT_WORLDSIZE_X_F,                  0.0f },
        { -mFI_UT_WORLDSIZE_X_F,  mFI_UT_WORLDSIZE_Z_F },
    };
    // clang-format on
    xyz_t pos;
    xyz_t center_pos;
    xyz_t pos2;
    xyz_t start_pos;
    int unit;
    int next_unit;
    mActor_name_t* fg_p;
    s16 player_angle_y;
    int max;
    int i;
    int count;

    pos2.x = player_actor->world.position.x;
    pos2.z = player_actor->world.position.z;
    pos2.y = player_actor->world.position.y;
    count = 0;

    mFI_Wpos2UtCenterWpos(&center_pos, pos2);
    center_pos.y = mCoBG_Wpos2BgUtCenterHeight_AddColumn(center_pos);
    fg_p = mFI_GetUnitFG(center_pos);

    if (param_6 == 0 && param_4 == 0 && fg_p != NULL && *fg_p == EMPTY_NO &&
        mTG_put_place_check(&center_pos, plant_flag, unit_flag)) {
        xyz_t_move(pos_tbl, &center_pos);
        pos_tbl++;
        count = 1;
    }

    player_angle_y = player_actor->shape_info.rotation.y;

    if (player_angle_y > DEG2SHORT_ANGLE2(157.5f) || player_angle_y <= DEG2SHORT_ANGLE2(-157.5f)) {
        unit = 4;
    } else if (player_angle_y > DEG2SHORT_ANGLE2(112.5f)) {
        unit = 3;
    } else if (player_angle_y > DEG2SHORT_ANGLE2(67.5f)) {
        unit = 2;
    } else if (player_angle_y > DEG2SHORT_ANGLE2(22.5f)) {
        unit = 1;
    } else if (player_angle_y > DEG2SHORT_ANGLE2(-22.5f)) {
        unit = 0;
    } else if (player_angle_y > DEG2SHORT_ANGLE2(-67.5f)) {
        unit = 7;
    } else if (player_angle_y > DEG2SHORT_ANGLE2(-112.5f)) {
        unit = 6;
    } else {
        unit = 5;
    }

    max = param_8 ? 5 : 8;
    for (i = 0; i < max && count < num_pos; i++) {
        mActor_name_t* fg_p;

        if (i & 1) {
            unit += i;
        } else {
            unit -= i;
        }

        mTG_check_direction_put_pos(&unit);
        pos.x = center_pos.x + offset_pos[unit][0];
        pos.z = center_pos.z + offset_pos[unit][1];
        pos.y = mCoBG_Wpos2BgUtCenterHeight_AddColumn(pos);

        fg_p = mFI_GetUnitFG(pos);
        if (fg_p != NULL && *fg_p == EMPTY_NO && mTG_put_place_check(&pos, plant_flag, unit_flag) &&
            (unit_flag == FALSE || (unit_flag != FALSE && mTG_check_pos_slope(&pos)))) {
            start_pos = player_actor->world.position;
            start_pos.y -= 20.0f;

            if ((unit & 1)) {
                mActor_name_t* fg_p;

                next_unit = unit + 1;
                mTG_check_direction_put_pos(&next_unit);

                pos2.x = center_pos.x + offset_pos[next_unit][0];
                pos2.z = center_pos.z + offset_pos[next_unit][1];
                pos2.y = mCoBG_Wpos2BgUtCenterHeight_AddColumn(pos2);

                fg_p = mFI_GetUnitFG(pos2);
                if (fg_p != NULL && !mTG_SEARCH_BAD_ITEM(*fg_p) && mTG_check_wall_put_pos(&start_pos, &pos2) == FALSE &&
                    mTG_check_wall_put_pos(&pos2, &pos) == FALSE) {
                    xyz_t_move(pos_tbl, &pos);
                    count++;
                    pos_tbl++;
                } else {
                    next_unit = unit - 1;
                    mTG_check_direction_put_pos(&next_unit);

                    pos2.x = center_pos.x + offset_pos[next_unit][0];
                    pos2.z = center_pos.z + offset_pos[next_unit][1];
                    pos2.y = mCoBG_Wpos2BgUtCenterHeight_AddColumn(pos2);

                    fg_p = mFI_GetUnitFG(pos2);
                    if (fg_p != NULL && !mTG_SEARCH_BAD_ITEM(*fg_p) &&
                        mTG_check_wall_put_pos(&start_pos, &pos2) == FALSE &&
                        mTG_check_wall_put_pos(&pos2, &pos) == FALSE) {
                        xyz_t_move(pos_tbl, &pos);
                        count++;
                        pos_tbl++;
                    }
                }
            } else {
                if (mTG_check_wall_put_pos(&start_pos, &pos) == FALSE) {
                    xyz_t_move(pos_tbl, &pos);
                    count++;
                    pos_tbl++;
                }
            }
        }
    }

    return count;
}

static int mTG_search_put_pos(ACTOR* player_actor, xyz_t* pos_tbl, int plant_flag, int param_4, int param_5,
                              int unit_flag, int param_7) {
    return mTG_search_put_pos2(player_actor, pos_tbl, plant_flag, param_4, 1, param_5, unit_flag, param_7);
}

static void mTG_open_warning_window(Submenu* submenu, mSM_MenuInfo_c* menu_info, int type) {
    mSM_open_submenu(submenu, mSM_OVL_WARNING, type, 0);
    menu_info->proc_status = mSM_OVL_PROC_WAIT;
    menu_info->next_proc_status = mSM_OVL_PROC_WAIT;
    mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
    sAdo_SysTrgStart(MONO(NA_SE_3));
}

static int mTG_common_throw_put_field(GAME_PLAY* play, mActor_name_t item, xyz_t* pos_p, s16 layer) {
    int res = FALSE;

    if (item == ITM_SIGNBOARD) {
        res = aSIGN_set_white_sign(&play->game, pos_p);
    } else {
        int ux;
        int uz;

        if (mFI_Wpos2UtNum(&ux, &uz, *pos_p) && Common_Get(clip).bg_item_clip != NULL &&
            Common_Get(clip).bg_item_clip->player_drop_entry_proc != NULL) {
            res = Common_Get(clip).bg_item_clip->player_drop_entry_proc(&play->game, item, ux, uz, layer);
        }
    }

    return res;
}

static int mTG_common_throw_put_room(GAME_PLAY* play, mActor_name_t item, xyz_t* pos_p, int layer, int delay_timer) {
    int ux;
    int uz;
    int res = FALSE;

    if (mFI_Wpos2UtNum(&ux, &uz, *pos_p) && Common_Get(clip).shop_goods_clip != NULL &&
        Common_Get(clip).shop_goods_clip->player_drop_entry_proc != NULL) {
        res = Common_Get(clip).shop_goods_clip->player_drop_entry_proc(&play->game, item, ux, uz, layer, delay_timer);
    }

    return res;
}

static void mTG_close_window(Submenu* submenu, mSM_MenuInfo_c* menu_info, int se_flag) {
    submenu->overlay->move_chg_base_proc(menu_info, mSM_OVL_PROC_MOVE);
    if (se_flag) {
        sAdo_SysTrgStart(NA_SE_31);
    }
}

static void mTG_open_board_init(Submenu* submenu, mSM_MenuInfo_c* menu_info, int mail_idx, int type, int item_idx) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* item_tag = &tag_ovl->tags[0];
    Mail_c* mail;

    if (mail_idx == -1) {
        mail = mTG_get_mail_pointer(submenu, NULL);
    } else {
        mail = &Now_Private->mail[mail_idx];
    }

    tag_ovl->sel_tag_idx = 0;
    tag_ovl->ret_tag_idx = 0;
    tag_ovl->item_name_wait_time = mTG_get_item_name_wait_time(item_tag);

    mSM_open_submenu_new(submenu, mSM_OVL_BOARD, type, item_idx, mail);

    menu_info->proc_status = mSM_OVL_PROC_MOVE;
    menu_info->next_proc_status = mSM_OVL_PROC_WAIT;
    menu_info->move_drt = mSM_MOVE_OUT_LEFT;
    sAdo_SysTrgStart(NA_SE_5F);
}

static void mTG_set_catch_se(Submenu* submenu) {
    if (submenu->overlay->tag_ovl->sel_tag_idx == 0) {
        sAdo_SysTrgStart(NA_SE_33);
    } else {
        sAdo_SysTrgStart(NA_SE_33);
    }
}

static void mTG_catch_item_from_table(Submenu* submenu, Mail_c* mail, mActor_name_t* item, int item_cond, int table,
                                      int table_idx) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;

    if (table == mTG_TABLE_PLAYER) {
        hand_ovl->info.wait_timer = 16;
        submenu->overlay->segment.change_player_main_anime_idx = mIV_ANIM_CATCH;
    } else if (table == mTG_TABLE_NEEDLEWORK || table == mTG_TABLE_CPORIGINAL_NW) {
        hand_ovl->info.next_act = mHD_ACTION_CLOSE;
        hand_ovl->info.hold_tbl = table;
        hand_ovl->info.hold_idx = table_idx;
        hand_ovl->info.item = *item;
        hand_ovl->info.item_cond = item_cond;
        *item = EMPTY_NO;
        mNW_on_hide_flg(submenu, table_idx);
    } else if (table == mTG_TABLE_CPORIGINAL) {
        int top = mCO_top_folder(submenu);

        hand_ovl->info.next_act = mHD_ACTION_CLOSE;
        hand_ovl->info.hold_tbl = table;
        hand_ovl->info.hold_idx = table_idx;
        hand_ovl->info.item = *item;
        hand_ovl->info.item_cond = item_cond;
        hand_ovl->info.catch_pg = top;
        *item = EMPTY_NO;
        mCO_on_hide_flg(submenu, top, table_idx);
    } else {
        hand_ovl->info.next_act = mHD_ACTION_CLOSE;
        hand_ovl->info.hold_tbl = table;
        hand_ovl->info.hold_idx = table_idx;

        if (table == mTG_TABLE_CPMAIL) {
            hand_ovl->info.catch_pg = submenu->overlay->cpmail_ovl->page_order[0];
        } else {
            hand_ovl->info.catch_pg = 0;
        }

        if (mail != NULL) {
            mMl_copy_mail(&hand_ovl->info.mail, mail);
            mMl_clear_mail(mail);
        } else {
            hand_ovl->info.item = *item;
            hand_ovl->info.item_cond = item_cond;

            if (table == mTG_TABLE_ITEM) {
                mPr_SetPossessionItem(Now_Private, table_idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);
            } else {
                *item = EMPTY_NO;
            }
        }
    }

    mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
    mTG_set_catch_se(submenu);
}

static int mTG_itemNo_to_amount(mActor_name_t itemNo) {
    switch (itemNo) {
        case ITM_MONEY_1000:
            return 1000;
        case ITM_MONEY_10000:
            return 10000;
        case ITM_MONEY_30000:
            return 30000;
        case ITM_MONEY_100:
            return 100;
        default:
            return 0;
    }
}

static int mTG_make_money_sack(Submenu* submenu, mSM_MenuInfo_c* menu_info, mActor_name_t item) {
    u32* money_p = &Now_Private->inventory.wallet;
    int amount = mTG_itemNo_to_amount(item);
    int res = FALSE;

    if ((int)*money_p >= amount) {
        mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;

        *money_p -= amount;
        hand_ovl->info.next_act = mHD_ACTION_CLOSE;
        hand_ovl->info.item = item;
        hand_ovl->info.item_cond = mPr_ITEM_COND_NORMAL;
        hand_ovl->info.wait_timer = 42;
        hand_ovl->info.hold_tbl = mTG_TABLE_MONEY;
        hand_ovl->info.hold_idx = 0;
        hand_ovl->info.catch_pg = 0;
        mTG_mark_main_CLR(submenu, menu_info);
        mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
        submenu->overlay->inventory_ovl->disp_money_chg_step = -(amount / 42);
        sAdo_SysTrgStart(MONO(NA_SE_52));
        res = TRUE;
    }

    return res;
}

static int mTG_drop_furniture(GAME_PLAY* play, mActor_name_t item) {
    int idx = -1;

    if (aMR_CLIP != NULL) {
        GAME* game = (GAME*)play;
        int sq_ofs;
        int layer;
        int ux;
        int uz;
        u16 rot;
        u16 ftrIdx = mRmTp_FtrItemNo2FtrIdx(item);

        idx = aMR_CLIP->judge_breed_new_ftr_proc(game, ftrIdx, &ux, &uz, &rot, &sq_ofs, &layer);
        if (idx >= 0) {
            aMR_CLIP->reserve_ftr_proc(game, ftrIdx, idx, ux, uz, rot, sq_ofs, layer);
        }
    }

    return idx;
}

static int mTG_nw_drop_furniture(GAME_PLAY* play, int type, int image_no) {
    GAME* game = (GAME*)play;
    int idx = aMR_JUDGE_MAX_FTR;
    int sq_ofs;
    int layer;
    int ux;
    int uz;
    u16 rot;

    switch (type) {
        case mNW_TYPE_MANEKIN:
            idx = aMR_CLIP->judge_breed_new_ftr_proc(game, FTR_MYFMANEKIN0 + (image_no & 7), &ux, &uz, &rot, &sq_ofs, &layer);
            break;
        case mNW_TYPE_UMBRELLA:
            idx = aMR_CLIP->judge_breed_new_ftr_proc(game, FTR_MYFUMBRELLA0 + (image_no & 7), &ux, &uz, &rot, &sq_ofs, &layer);
            break;
    }

    if (idx >= 0) {
        switch (type) {
            case mNW_TYPE_MANEKIN:
                aMR_CLIP->reserve_ftr_proc(game, FTR_MYFMANEKIN0 + (image_no & 7), idx, ux, uz, rot, sq_ofs, layer);
                break;
            case mNW_TYPE_UMBRELLA:
                aMR_CLIP->reserve_ftr_proc(game, FTR_MYFUMBRELLA0 + (image_no & 7), idx, ux, uz, rot, sq_ofs, layer);
                break;
        }
    }

    return idx;
}

static int mTG_get_unit_front_player(xyz_t* pos_p, const xyz_t* player_pos, s16 angle_y) {
    int dir;
    static f32 offset_pos[][2] = {
        // clang-format off
        {                  0.0f,  mFI_UT_WORLDSIZE_Z_F },
        {  mFI_UT_WORLDSIZE_X_F,  mFI_UT_WORLDSIZE_Z_F },
        {  mFI_UT_WORLDSIZE_X_F,                  0.0f },
        {  mFI_UT_WORLDSIZE_X_F, -mFI_UT_WORLDSIZE_Z_F },
        {                  0.0f, -mFI_UT_WORLDSIZE_Z_F },
        { -mFI_UT_WORLDSIZE_X_F, -mFI_UT_WORLDSIZE_Z_F },
        { -mFI_UT_WORLDSIZE_X_F,                  0.0f },
        { -mFI_UT_WORLDSIZE_X_F,  mFI_UT_WORLDSIZE_Z_F },
        // clang-format on
    };

    if (angle_y > DEG2SHORT_ANGLE2(157.5f) || angle_y <= DEG2SHORT_ANGLE2(-157.5f)) {
        dir = 4;
    } else if (angle_y > DEG2SHORT_ANGLE2(112.5f)) {
        dir = 3;
    } else if (angle_y > DEG2SHORT_ANGLE2(67.5f)) {
        dir = 2;
    } else if (angle_y > DEG2SHORT_ANGLE2(22.5f)) {
        dir = 1;
    } else if (angle_y > DEG2SHORT_ANGLE2(-22.5f)) {
        dir = 0;
    } else if (angle_y > DEG2SHORT_ANGLE2(-67.5f)) {
        dir = 7;
    } else if (angle_y > DEG2SHORT_ANGLE2(-112.5f)) {
        dir = 6;
    } else {
        dir = 5;
    }

    pos_p->x = player_pos->x + offset_pos[dir][0];
    pos_p->y = player_pos->y;
    pos_p->z = player_pos->z + offset_pos[dir][1];
}

static int mTG_check_free_2nd_layer(const xyz_t* pos_p) {
    int bx;
    int bz;
    int ux;
    int uz;
    mActor_name_t* fg_p;
    int res = FALSE;

    if (mFI_Wpos2BlockNum(&bx, &bz, *pos_p) && mFI_Wpos2UtNum_inBlock(&ux, &uz, *pos_p)) {
        fg_p = mFI_BkNum2UtFGTop_layer(bx, bz, mCoBG_LAYER1);
        if (fg_p != NULL && fg_p[ux + uz * UT_X_NUM] == EMPTY_NO) {
            res = TRUE;
        }
    }

    return res;
}

static void mTG_set_trade_cond(Submenu* submenu, mSM_MenuInfo_c* menu_info, s16 cond, u32 arg) {
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];

    Save_Get(homes[menu_info->data1]).haniwa.items[tag->tag_col].exchange_type = cond;
    Save_Get(homes[menu_info->data1]).haniwa.items[tag->tag_col].extra_data = arg;
    mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
    sAdo_SysTrgStart(NA_SE_33);
    submenu->overlay->haniwa_ovl->set_interrupt_message_proc(submenu, tag, mHW_MSG_KASIKO);
}

static void mTG_present_open_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    int table_idx;

    table_idx = mTG_get_table_idx(&submenu->overlay->tag_ovl->tags[0]);
    mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_KEEP);
    sAdo_SysTrgStart(NA_SE_436);
    mPr_SetItemCollectBit(Now_Private->inventory.pockets[table_idx]);
    submenu->overlay->inventory_ovl->item_scale_type[table_idx] = 5;
    submenu->overlay->inventory_ovl->remove_timer = 48;
}

static void mTG_nw_select_this_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    int table_idx;
    Submenu_Item_c* item_p;

    table_idx = mTG_get_table_idx(&submenu->overlay->tag_ovl->tags[0]);
    item_p = submenu->item_p;
    item_p->item = RSV_NO;
    item_p->slot_no = table_idx;
    submenu->selected_item_num = 1;
    mTG_close_window(submenu, menu_info, TRUE);
}

static void mTG_give_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    int table_idx;
    Submenu_Item_c* item_p;
    int category;

    table_idx = mTG_get_table_idx(&submenu->overlay->tag_ovl->tags[0]);
    item_p = submenu->item_p;
    item_p->item = Now_Private->inventory.pockets[table_idx];
    item_p->slot_no = table_idx;
    submenu->selected_item_num = 1;

    category = ITEM_NAME_GET_CAT(item_p->item);
    if (menu_info->data1 == 2) {
        submenu->after_mode = aHOI_REQUEST_GET_PULL_WAIT;
    } else if (menu_info->data1 == 1) {
        submenu->after_mode = aHOI_REQUEST_PUTAWAY;
    } else if (ITEM_NAME_GET_TYPE(item_p->item) == NAME_TYPE_ITEM1 &&
               (category == ITEM1_CAT_FRUIT || category == ITEM1_CAT_FISH)) {
        submenu->after_mode = aHOI_REQUEST_EAT;
    } else {
        submenu->after_mode = aHOI_REQUEST_PUTAWAY;
    }

    mPlib_request_main_give_from_submenu(item_p->item, submenu->after_mode,
                                         mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, item_p->slot_no) & 1,
                                         FALSE);
    mTG_close_window(submenu, menu_info, TRUE);
}

static void mTG_sell_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[0];
    int table_idx = mTG_get_table_idx(tag);
    Submenu_Item_c* item_p = submenu->item_p;

    if (mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, table_idx) == mPr_ITEM_COND_QUEST) {
        mTG_open_warning_window(submenu, menu_info, mWR_WARNING_SELL_QUEST_ITEM);
    } else {
        item_p->item = Now_Private->inventory.pockets[table_idx];
        item_p->slot_no = table_idx;
        submenu->selected_item_num = 1;
        mTG_close_window(submenu, menu_info, TRUE);
    }
}

static void mTG_sell_all_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mIV_Ovl_c* inventory_ovl;
    int table_idx;
    Submenu_Item_c* item_p;
    int count;
    int i;

    inventory_ovl = submenu->overlay->inventory_ovl;
    table_idx = mTG_get_table_idx(&submenu->overlay->tag_ovl->tags[0]);

    if (mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, table_idx) == mPr_ITEM_COND_QUEST) {
        mTG_open_warning_window(submenu, menu_info, mWR_WARNING_SELL_QUEST_ITEM);
    } else {
        item_p = submenu->item_p;
        count = 0;

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++, item_p++) {
            item_p->item = EMPTY_NO;
            item_p->slot_no = 0;
        }

        item_p = submenu->item_p;
        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if ((inventory_ovl->item_mark_bitfield & (1 << i)) != 0) {
                count++;
                item_p->item = Now_Private->inventory.pockets[i];
                item_p->slot_no = i;
                item_p++;
            }
        }

        submenu->selected_item_num = count;
        mTG_close_window(submenu, menu_info, TRUE);
    }
}

static void mTG_get_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    static mActor_name_t mTG_money_name[] = { ITM_MONEY_100, ITM_MONEY_1000, ITM_MONEY_10000, ITM_MONEY_30000 };
    static u32 mTG_money_amount[] = { 100, 1000, 10000, 30000 };
    int money;
    mActor_name_t* item_p2;
    int k;
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int idx = mPr_GetPossessionItemIdxWithCond(Now_Private, EMPTY_NO, mPr_ITEM_COND_NORMAL);
    mHW_Ovl_c* haniwa_ovl;
    Haniwa_Item_c* haniwa_item_p;
    mActor_name_t* item_p;
    int changed_money;
    int keep_money;
    int i;
    int j;
    mIV_Ovl_c* inventory_ovl;
    mActor_name_t* money_name_p;
    u32* money_amount_p;
    int change_money;

    if (idx == -1) {
        haniwa_ovl = submenu->overlay->haniwa_ovl;

        haniwa_ovl->msg_interrupt_idx = 6;
        haniwa_ovl->table_idx = tag->table;
        haniwa_ovl->sub_idx = tag->tag_col;
        haniwa_ovl->msg_time = 120;
        mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
        sAdo_SysTrgStart(MONO(NA_SE_3));
    } else {
        haniwa_item_p = &Save_Get(homes[menu_info->data1]).haniwa.items[tag->tag_col];
        item_p = Now_Private->inventory.pockets;

        money = Now_Private->inventory.wallet;
        changed_money = money;
        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++, item_p++) {
            if (mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, i) == mPr_ITEM_COND_NORMAL) {
                changed_money += mTG_itemNo_to_amount(*item_p);
            }
        }

        changed_money -= haniwa_item_p->extra_data;
        if (changed_money < 0) {
            submenu->overlay->haniwa_ovl->set_interrupt_message_proc(submenu, tag, mHW_MSG_OKANE);
            mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
            sAdo_SysTrgStart(MONO(NA_SE_3));
        } else {
            inventory_ovl = submenu->overlay->inventory_ovl;
            money_name_p = mTG_money_name;
            money_amount_p = mTG_money_amount;

            keep_money = money - haniwa_item_p->extra_data;
            for (j = 0; j < ARRAY_COUNT(mTG_money_name) && keep_money < 0; j++, money_name_p++, money_amount_p++) {
                item_p2 = Now_Private->inventory.pockets;
                for (k = 0; k < mPr_POCKETS_SLOT_COUNT; k++, item_p2++) {
                    if (mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, k) == mPr_ITEM_COND_NORMAL &&
                        *item_p2 == *money_name_p) {
                        keep_money += *money_amount_p;
                        mPr_SetPossessionItem(Now_Private, k, EMPTY_NO, mPr_ITEM_COND_NORMAL);

                        if (keep_money >= 0) {
                            break;
                        }
                    }
                }
            }

            Now_Private->inventory.wallet = keep_money;
            mPr_SetPossessionItem(Now_Private, idx, haniwa_item_p->item, mPr_ITEM_COND_NORMAL);
            submenu->overlay->haniwa_ovl->set_interrupt_message_proc(submenu, tag, mHW_MSG_MAIDO);
            mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
            Save_Get(homes[menu_info->data1]).haniwa.bells += haniwa_item_p->extra_data;
            haniwa_item_p->item = EMPTY_NO;

            if (haniwa_item_p->exchange_type == mHm_HANIWA_TRADE_0) {
                sAdo_SysTrgStart(NA_SE_5F);
            } else {
                change_money = (int)keep_money - (int)money;

                if (ABS(change_money) < 42) {
                    sAdo_SysTrgStart(MONO(NA_SE_REGISTER));
                    inventory_ovl->disp_money = keep_money;
                } else {
                    sAdo_SysTrgStart(MONO(NA_SE_52));
                    submenu->overlay->hand_ovl->info.wait_timer = 42;
                    inventory_ovl->disp_money_chg_step = change_money / 42;

                    if (ABS(inventory_ovl->disp_money_chg_step) % 5 == 0) {
                        if (inventory_ovl->disp_money_chg_step > 0) {
                            inventory_ovl->disp_money_chg_step--;
                        } else {
                            inventory_ovl->disp_money_chg_step++;
                        }
                    }
                }
            }
        }
    }
}

static void mTG_dump_mail_mark_exe_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    mMB_Ovl_c* mailbox_ovl = submenu->overlay->mailbox_ovl;
    mCM_Ovl_c* cpmail_ovl = submenu->overlay->cpmail_ovl;
    int delete_flag;
    int i;

    if (menu_info->menu_type == mSM_OVL_MAILBOX) {
        int i;

        mailbox_ovl->mark_flag = FALSE;
        for (i = 0; i < HOME_MAILBOX_SIZE; i++) {
            Mail_c* mail = &Common_Get(now_home)->mailbox[i];

            // clear selected mail if it has a present or is from the player (sending)
            if (mail->present != EMPTY_NO ||
                (mail->content.font != mMl_FONT_RECV_READ && mail->content.font != mMl_FONT_RECV_PLAYER_PRESENT_READ)) {
                mailbox_ovl->mark_bitfield &= ~(1 << i);
            }
        }

        if (mailbox_ovl->mark_bitfield != 0) {
            mailbox_ovl->mark_flag = TRUE;
        }
    } else if (menu_info->menu_type == mSM_OVL_CPMAIL) {
        int page = cpmail_ovl->page_order[0];
        int i;

        for (i = 0; i < mCD_KEEP_MAIL_COUNT; i++) {
            Mail_c* mail = &cpmail_ovl->card_mail->mail[page][i];

            // clear selected mail if it has a present or is from the player (sending)
            if (mail->present != EMPTY_NO ||
                (mail->content.font != mMl_FONT_RECV_READ && mail->content.font != mMl_FONT_RECV_PLAYER_PRESENT_READ)) {
                cpmail_ovl->mark_bitfield &= ~(1 << i);
            }
        }

        cpmail_ovl->mark_flag = FALSE;
        if (cpmail_ovl->mark_bitfield != 0) {
            cpmail_ovl->mark_flag = TRUE;
        }
    }

    for (i = 0; i < mPr_INVENTORY_MAIL_COUNT; i++) {
        Mail_c* mail = &Now_Private->mail[i];

        // clear selected mail if it has a present or is from the player (sending)
        if (mail->present != EMPTY_NO ||
            (mail->content.font != mMl_FONT_RECV_READ && mail->content.font != mMl_FONT_RECV_PLAYER_PRESENT_READ)) {
            inv_ovl->mail_mark_bitfield2 &= ~(1 << i);
        }
    }

    inv_ovl->mail_mark_flag = FALSE;
    if (inv_ovl->mail_mark_bitfield2 != 0) {
        inv_ovl->mail_mark_flag = TRUE;
    }

    delete_flag = FALSE;
    if (inv_ovl->mail_mark_flag == TRUE) {
        delete_flag = TRUE;
    } else if (menu_info->menu_type == mSM_OVL_MAILBOX) {
        if (mailbox_ovl->mark_flag == TRUE) {
            delete_flag = TRUE;
        }
    } else if (menu_info->menu_type == mSM_OVL_CPMAIL) {
        if (cpmail_ovl->mark_flag == TRUE) {
            delete_flag = TRUE;
        }
    }

    if (delete_flag) {
        inv_ovl->remove_timer = 24;
        sAdo_SysTrgStart(NA_SE_435);
    } else {
        sAdo_SysTrgStart(MONO(NA_SE_A));
    }

    mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
}

static void mTG_mailbox_change_mail_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mMB_Ovl_c* mailbox_ovl = submenu->overlay->mailbox_ovl;
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    int idx = mMl_chk_mail_free_space(Now_Private->mail, mPr_INVENTORY_MAIL_COUNT);

    inv_ovl->mail_mark_bitfield2 = 0;
    if (idx != -1) {
        mailbox_ovl->mark_flag = 2;
        sAdo_SysTrgStart(NA_SE_MENU_EXIT);
    } else {
        mailbox_ovl->mark_bitfield = 0;
        sAdo_SysTrgStart(MONO(NA_SE_A));
    }

    mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
}

static void mTG_cpmail_change_mail_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mCM_Ovl_c* cpmail_ovl = submenu->overlay->cpmail_ovl;
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    int inv_free_cnt;
    int inv_mark_cnt;
    int cpmail_mark_cnt;
    int cpmail_free_cnt;
    int inv_cnt;
    int cpmail_cnt;
    int page;
    int i;

    inv_mark_cnt = 0;
    for (i = 0; i < mPr_INVENTORY_MAIL_COUNT; i++) {
        if ((inv_ovl->mail_mark_bitfield2 & (1 << i)) != 0) {
            inv_mark_cnt++;
        }
    }

    cpmail_mark_cnt = 0;
    for (i = 0; i < mCD_KEEP_MAIL_COUNT; i++) {
        if ((cpmail_ovl->mark_bitfield & (1 << i)) != 0) {
            cpmail_mark_cnt++;
        }
    }

    inv_free_cnt = 0;
    for (i = 0; i < mPr_INVENTORY_MAIL_COUNT; i++) {
        if (mMl_check_not_used_mail(&Now_Private->mail[i])) {
            inv_free_cnt++;
        }
    }

    cpmail_free_cnt = 0;
    page = cpmail_ovl->page_order[0];
    for (i = 0; i < mCD_KEEP_MAIL_COUNT; i++) {
        if (mMl_check_not_used_mail(&cpmail_ovl->card_mail->mail[page][i]) == TRUE) {
            cpmail_free_cnt++;
        }
    }

    inv_cnt = 0;
    cpmail_cnt = 0;
    if (inv_mark_cnt > cpmail_mark_cnt && (inv_mark_cnt - cpmail_mark_cnt) > cpmail_free_cnt) {
        inv_cnt = (inv_mark_cnt - cpmail_mark_cnt) - cpmail_free_cnt;
    } else if (cpmail_mark_cnt > inv_mark_cnt && (cpmail_mark_cnt - inv_mark_cnt) > inv_free_cnt) {
        cpmail_cnt = (cpmail_mark_cnt - inv_mark_cnt) - inv_free_cnt;
    }

    if (inv_cnt == inv_mark_cnt && cpmail_cnt == cpmail_mark_cnt) {
        cpmail_ovl->mark_bitfield = 0;
        inv_ovl->mail_mark_bitfield2 = 0;
        sAdo_SysTrgStart(MONO(NA_SE_A));
    } else {
        int i;
        int cnt;
        if (inv_cnt > 0) {
            for (cnt = 0, i = 0; cnt < inv_cnt && i < mPr_INVENTORY_MAIL_COUNT; i++) {
                if ((inv_ovl->mail_mark_bitfield2 & (1 << i)) != 0) {
                    inv_ovl->mail_mark_bitfield2 &= ~(1 << i);
                    cnt++;
                }
            }
        }

        if (cpmail_cnt > 0) {
            for (cnt = 0, i = 0; cnt < cpmail_cnt && i < mCD_KEEP_MAIL_COUNT; i++) {
                if ((cpmail_ovl->mark_bitfield & (1 << i)) != 0) {
                    cpmail_ovl->mark_bitfield &= ~(1 << i);
                    cnt++;
                }
            }
        }

        inv_ovl->mail_mark_flag = 2;
        cpmail_ovl->mark_flag = 2;
        sAdo_SysTrgStart(NA_SE_MENU_EXIT);
    }

    mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
}

static void mTG_dump_mail_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;

    inv_ovl->remove_timer = 24;
    mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
    sAdo_SysTrgStart(NA_SE_435);
}

static void mTG_dump_item_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;

    inv_ovl->remove_timer = 12;
    inv_ovl->item_scale_type[idx] = mIV_ITEM_SCALE_TYPE_SHRINK;
    mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
    sAdo_SysTrgStart(NA_SE_435);
}

static void mTG_send_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);
    Mail_c* mail = &Now_Private->mail[idx];
    Submenu_Item_c* item_p = submenu->item_p;

    mail->content.font = mMl_FONT_RECV;
    mMl_copy_mail(&submenu->mail, mail);
    mMl_clear_mail(mail);
    item_p->slot_no = idx;
    item_p->item = ITM_QST_LETTER;
    submenu->selected_item_num = 1;
    submenu->after_mode = aHOI_REQUEST_PUTAWAY;
    mPlib_request_main_give_from_submenu(item_p->item, submenu->after_mode, FALSE, TRUE);
    mTG_close_window(submenu, menu_info, TRUE);
}

static void mTG_rewrite_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_open_board_init(submenu, menu_info, -1, mSM_BD_OPEN_REWRITE, -1);
}

static void mTG_stick_select_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[tag_ovl->sel_tag_idx];

    mTG_chg_tag_func2(submenu, menu_info, tag, mTG_TYPE_TAG_NW_SEL_STK_PATTERN);
    sAdo_SysTrgStart(NA_SE_33);
}

static void mTG_nw_carpet_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);
    int changed_flag = TRUE;
    int change_org_flag = FALSE;
    int img_no;

    if (tag_ovl->tags[3].tag_row == 1) {
        change_org_flag = TRUE;
    }

    if (mRmTp_CheckFloorIsMyOriginalInThisScene()) {
        if (change_org_flag) {
            img_no = mNW_get_image_no(submenu, idx) & 7;
            CLIP(my_indoor_clip)->floor_idx_2_change_floor_proc(FLOOR_MY_ORIG_START + img_no, TRUE);
        } else {
            img_no = mNW_get_image_no(submenu, idx) & 7;
            CLIP(my_indoor_clip)->floor_idx_2_change_floor_proc(FLOOR_MY_ORIG_START + img_no, FALSE);
        }
    } else {
        int free_idx = mPr_GetPossessionItemIdx(Now_Private, EMPTY_NO);

        if (free_idx >= 0) {
            mActor_name_t* item_p = &Now_Private->inventory.pockets[free_idx];

            if (change_org_flag) {
                img_no = mNW_get_image_no(submenu, idx) & 7;
                *item_p = CLIP(my_indoor_clip)->floor_idx_2_change_floor_proc(FLOOR_MY_ORIG_START + img_no, TRUE);
            } else {
                img_no = mNW_get_image_no(submenu, idx) & 7;
                *item_p = CLIP(my_indoor_clip)->floor_idx_2_change_floor_proc(FLOOR_MY_ORIG_START + img_no, FALSE);
            }
        } else {
            mTG_open_warning_window(submenu, menu_info, mWR_WARNING_ORIGINAL);
            changed_flag = FALSE;
        }
    }

    if (changed_flag) {
        if (inv_ovl != NULL) {
            inv_ovl->original_flag = TRUE;
        }

        mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
        mTG_close_window(submenu, menu_info, FALSE);
    }
}

static void mTG_carpet_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);

    if (CLIP(my_indoor_clip) != NULL) {
        mActor_name_t* item_p = &Now_Private->inventory.pockets[idx];

        if (mRmTp_CheckFloorIsMyOriginalInThisScene()) {
            CLIP(my_indoor_clip)->change_carpet_proc(*item_p);
            *item_p = EMPTY_NO;
        } else {
            mActor_name_t item;

            item = CLIP(my_indoor_clip)->change_carpet_proc(*item_p);
            *item_p = item;
        }

        mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
        mTG_close_window(submenu, menu_info, FALSE);
    }
}

static void mTG_nw_cover_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);
    int changed_flag = TRUE;
    int change_org_flag = FALSE;
    int img_no;

    if (tag_ovl->tags[3].tag_row == 1) {
        change_org_flag = TRUE;
    }

    if (mRmTp_CheckWallIsMyOriginalInThisScene()) {
        if (change_org_flag) {
            img_no = mNW_get_image_no(submenu, idx) & 7;
            CLIP(my_indoor_clip)->wall_idx_2_change_wall_proc(WALL_MY_ORIG_START + img_no, TRUE);
        } else {
            img_no = mNW_get_image_no(submenu, idx) & 7;
            CLIP(my_indoor_clip)->wall_idx_2_change_wall_proc(WALL_MY_ORIG_START + img_no, FALSE);
        }
    } else {
        int free_idx = mPr_GetPossessionItemIdx(Now_Private, EMPTY_NO);

        if (free_idx >= 0) {
            mActor_name_t* item_p = &Now_Private->inventory.pockets[free_idx];

            if (change_org_flag) {
                img_no = mNW_get_image_no(submenu, idx) & 7;
                *item_p = CLIP(my_indoor_clip)->wall_idx_2_change_wall_proc(WALL_MY_ORIG_START + img_no, TRUE);
            } else {
                img_no = mNW_get_image_no(submenu, idx) & 7;
                *item_p = CLIP(my_indoor_clip)->wall_idx_2_change_wall_proc(WALL_MY_ORIG_START + img_no, FALSE);
            }
        } else {
            mTG_open_warning_window(submenu, menu_info, mWR_WARNING_ORIGINAL);
            changed_flag = FALSE;
        }
    }

    if (changed_flag) {
        if (inv_ovl != NULL) {
            inv_ovl->original_flag = TRUE;
        }

        mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
        mTG_close_window(submenu, menu_info, FALSE);
    }
}

static void mTG_cover_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);

    if (CLIP(my_indoor_clip) != NULL) {
        mActor_name_t* item_p = &Now_Private->inventory.pockets[idx];

        if (mRmTp_CheckWallIsMyOriginalInThisScene()) {
            CLIP(my_indoor_clip)->change_wall_proc(*item_p);
            *item_p = EMPTY_NO;
        } else {
            mActor_name_t item;

            item = CLIP(my_indoor_clip)->change_wall_proc(*item_p);
            *item_p = item;
        }

        mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
        mTG_close_window(submenu, menu_info, FALSE);
    }
}

static void mTG_putin_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);
    Submenu_Item_c* item_p = submenu->item_p;

    item_p->item = Now_Private->inventory.pockets[idx];
    item_p->slot_no = idx;
    submenu->selected_item_num = 1;

    if (menu_info->data0 == 10) {
        if (ChkRoomMusicBox((u32)(item_p->item - ITM_MINIDISK_START))) {
            item_p->item = EMPTY_NO;
            mTG_open_warning_window(submenu, menu_info, mWR_WARNING_MUSIC2);
        } else {
            SetRoomMusicBox((u32)(item_p->item - ITM_MINIDISK_START));
            mPr_SetPossessionItem(Now_Private, idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);
            mTG_close_window(submenu, menu_info, TRUE);
        }
    } else {
        if (menu_info->data0 != 11) {
            mPr_SetPossessionItem(Now_Private, idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);
        }

        mTG_close_window(submenu, menu_info, TRUE);
    }
}

static void mTG_music_listen_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);
    Submenu_Item_c* item_p = submenu->item_p;

    item_p->item = ITM_MINIDISK_START + idx;
    item_p->slot_no = idx;
    submenu->selected_item_num = 1;
    mTG_close_window(submenu, menu_info, TRUE);
}

static void mTG_music_takeout_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);
    mMU_Ovl_c* music_ovl = submenu->overlay->music_ovl;
    u32 mark_cnt = 0;
    int free_idx;
    int i;

    for (i = 0; i < MINIDISK_NUM; i++) {
        if (ChkMusicBox(music_ovl->mark_flg, i)) {
            mark_cnt++;
        }
    }

    if (mark_cnt == 0 || ChkMusicBox(music_ovl->mark_flg, idx) == FALSE) {
        if (mPr_GetPossessionItemSum(Now_Private, EMPTY_NO) >= 1) {
            free_idx = mPr_GetPossessionItemIdx(Now_Private, EMPTY_NO);

            if (free_idx >= 0) {
                ClrRoomMusicBox(idx);
                mPr_SetPossessionItem(Now_Private, free_idx, ITM_MINIDISK_START + idx, mPr_ITEM_COND_NORMAL);
            }

            mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
            mTG_close_window(submenu, menu_info, TRUE);
        } else {
            mTG_open_warning_window(submenu, menu_info, mWR_WARNING_MUSIC);
        }
    } else {
        if (mPr_GetPossessionItemSum(Now_Private, EMPTY_NO) >= 1) {
            for (i = 0; i < MINIDISK_NUM; i++) {
                if (ChkMusicBox(music_ovl->mark_flg, i)) {
                    free_idx = mPr_GetPossessionItemIdx(Now_Private, EMPTY_NO);

                    if (free_idx >= 0) {
                        ClrRoomMusicBox(i);
                        mPr_SetPossessionItem(Now_Private, free_idx, ITM_MINIDISK_START + i, mPr_ITEM_COND_NORMAL);
                    }
                }
            }

            mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
            mTG_close_window(submenu, menu_info, TRUE);
        } else {
            mTG_open_warning_window(submenu, menu_info, mWR_WARNING_MUSIC);
        }
    }
}

static void mTG_island_check_plant_plant(mActor_name_t item) {
    if (item == ITM_SAPLING || item == ITM_CEDAR_SAPLING) {
        mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_PLANT_TREE);
    } else if (ITEM_IS_FLOWER_BAG(item)) {
        mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_PLANT_FLOWER);
    }
}

static void mTG_island_check_fruit_plant(mActor_name_t item) {
    switch (item) {
        case ITM_FOOD_APPLE:
            mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_PLANT_APPLE_TREE);
            mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_PLANT_TREE);
            break;
        case ITM_FOOD_CHERRY:
            mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_PLANT_CHERRY_TREE);
            mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_PLANT_TREE);
            break;
        case ITM_FOOD_PEAR:
            mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_PLANT_PEAR_TREE);
            mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_PLANT_TREE);
            break;
        case ITM_FOOD_PEACH:
            mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_PLANT_PEACH_TREE);
            mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_PLANT_TREE);
            break;
        case ITM_FOOD_ORANGE:
            mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_PLANT_ORANGE_TREE);
            mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_PLANT_TREE);
            break;
        case ITM_FOOD_COCONUT:
            mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_PLANT_COCONUT_TREE);
            mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_PLANT_TREE);
            break;
    }
}

static void mTG_island_check_fruit_eat(mActor_name_t item) {
    if (item == ITM_FOOD_COCONUT) {
        mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_EAT_COCONUT);
    }
}

static void mTG_plant_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    GAME_PLAY* play = (GAME_PLAY*)gamePT;
    ACTOR* player = GET_PLAYER_ACTOR_ACTOR(play);
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);
    mActor_name_t plant_item;
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    xyz_t pos;

    plant_item = Now_Private->inventory.pockets[idx];

    if (((Now_Private->equipment >= ITM_SHOVEL && Now_Private->equipment <= ITM_SHOVEL) ||
         (Now_Private->equipment >= ITM_GOLDEN_SHOVEL && Now_Private->equipment <= ITM_GOLDEN_SHOVEL)) &&
        inv_ovl->shovel_flag == TRUE) {
        mTG_island_check_plant_plant(plant_item);
        mTG_island_check_fruit_plant(plant_item);
        mPlib_request_main_putin_scoop_from_submenu(&inv_ovl->shovel_pos, Now_Private->inventory.pockets[idx], FALSE);
        mPr_SetPossessionItem(Now_Private, idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);
        mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
        mTG_close_window(submenu, menu_info, TRUE);
        return;
    } else {
        if (mTG_search_put_pos(player, &pos, TRUE, plant_item == ITM_SIGNBOARD, plant_item == ITM_SIGNBOARD, FALSE,
                               FALSE)) {
            mActor_name_t item = Now_Private->inventory.pockets[idx];
            mActor_name_t throw_item;

            mTG_island_check_plant_plant(item);
            if (item == ITM_SAPLING) {
                throw_item = TREE_SAPLING;
            } else if (item == ITM_CEDAR_SAPLING) {
                throw_item = CEDAR_TREE_SAPLING;
            } else {
                throw_item = FLOWER_PANSIES0 + (item - ITM_WHITE_PANSY_BAG);
            }

            if (mTG_common_throw_put_field(play, throw_item, &pos, mCoBG_LAYER0)) {
                mPr_SetPossessionItem(Now_Private, idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);
                pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(pos, 0.0f);
                sAdo_OngenTrgStart(NA_SE_2A, &pos);
                mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
                mTG_close_window(submenu, menu_info, FALSE);
                return;
            }
        }
    }

    mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_PLANT);
}

static int mTG_check_island_famicom(mActor_name_t item) {
    int res = TRUE;

    if (mFI_CheckInIsland() &&
        (mSP_SearchItemCategoryPriority(item, mSP_KIND_FURNITURE, mSP_LISTTYPE_HOMEPAGE, NULL) ||
         mSP_SearchItemCategoryPriority(item, mSP_KIND_FURNITURE, mSP_LISTTYPE_SPECIALPRESENT, NULL))) {
        res = FALSE;
    }

    return res;
}

static void mTG_field_put_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    GAME_PLAY* play = (GAME_PLAY*)gamePT;
    ACTOR* player = GET_PLAYER_ACTOR_ACTOR(play);
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);
    mActor_name_t put_item = Now_Private->inventory.pockets[idx];
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    xyz_t pos;

    if (inv_ovl->item_mark_bitfield != 0 && (inv_ovl->item_mark_bitfield & (1 << idx)) != 0) {
        int i;
        int put_cnt = 0;
        int bad_famicom_cnt = 0;

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if ((inv_ovl->item_mark_bitfield & (1 << i)) != 0) {
                mActor_name_t item = Now_Private->inventory.pockets[i];

                if (mTG_check_island_famicom(item)) {
                    if (mTG_search_put_pos(player, &pos, item == ITM_SIGNBOARD, FALSE, item == ITM_SIGNBOARD,
                                           item == ITM_SIGNBOARD, item == ITM_SIGNBOARD) &&
                        mTG_common_throw_put_field(play, item, &pos, put_cnt)) {
                        mPr_SetPossessionItem(Now_Private, i, EMPTY_NO, mPr_ITEM_COND_NORMAL);
                        put_cnt++;
                    }
                } else {
                    bad_famicom_cnt++;
                }
            }
        }

        if (put_cnt != 0) {
            mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
            mTG_close_window(submenu, menu_info, FALSE);
        } else if (bad_famicom_cnt != 0) {
            mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_FAMI);
        } else {
            mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_ITEM);
        }

        inv_ovl->item_mark_bitfield = 0;
    } else {
        if (put_item == ITM_SIGNBOARD && (mFI_CheckInIsland() || mLd_PlayerManKindCheck())) {
            if (mFI_CheckInIsland()) {
                mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_SIGN_ISLAND);
            } else {
                mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_SIGN_OTHER);
            }
        } else if ((mSP_SearchItemCategoryPriority(put_item, mSP_KIND_FURNITURE, mSP_LISTTYPE_HOMEPAGE, NULL) ||
                    mSP_SearchItemCategoryPriority(put_item, mSP_KIND_FURNITURE, mSP_LISTTYPE_SPECIALPRESENT, NULL)) &&
                   mFI_CheckInIsland()) {
            mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_FAMI);
        } else {
            if (mTG_search_put_pos(player, &pos, put_item == ITM_SIGNBOARD, FALSE, put_item == ITM_SIGNBOARD,
                                   put_item == ITM_SIGNBOARD, put_item == ITM_SIGNBOARD) &&
                mTG_common_throw_put_field(play, put_item, &pos, mCoBG_LAYER0)) {
                if (menu_info->data0 == 13) {
                    mPr_SetPossessionItem(Now_Private, idx, (mActor_name_t)menu_info->data1, mPr_ITEM_COND_NORMAL);
                    mPlib_request_main_wait_from_submenu();
                } else {
                    mPr_SetPossessionItem(Now_Private, idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);
                }

                mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
                mTG_close_window(submenu, menu_info, FALSE);
            } else {
                if (put_item == ITM_SIGNBOARD) {
                    mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_SIGN);
                } else {
                    mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_ITEM);
                }
            }
        }
    }
}

static void mTG_room_put_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    GAME_PLAY* play = (GAME_PLAY*)gamePT;
    ACTOR* player = GET_PLAYER_ACTOR_ACTOR(play);
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int idx;
    mActor_name_t put_item;
    mIV_Ovl_c* inv_ovl;
    int ftrID;
    xyz_t pos;
    xyz_t ut_pos;
    int ux;
    int uz;

    idx = mTG_get_table_idx(tag);
    put_item = mRmTp_Item1ItemNo2FtrItemNo_AtPlayerRoom(Now_Private->inventory.pockets[idx], TRUE);
    inv_ovl = submenu->overlay->inventory_ovl;

    switch (ITEM_NAME_GET_TYPE(put_item)) {
        case NAME_TYPE_FTR0:
        case NAME_TYPE_FTR1:
            if (!mFI_CheckInIsland() ||
                !(mSP_SearchItemCategoryPriority(put_item, mSP_KIND_FURNITURE, mSP_LISTTYPE_HOMEPAGE, NULL) ||
                  mSP_SearchItemCategoryPriority(put_item, mSP_KIND_FURNITURE, mSP_LISTTYPE_SPECIALPRESENT, NULL))) {
                ftrID = mTG_drop_furniture(play, put_item);
                if (ftrID >= 0) {
                    mPr_SetPossessionItem(Now_Private, idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);
                    mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
                    mTG_close_window(submenu, menu_info, FALSE);
                    mMkRm_ReportChangePlayerRoom();
                } else {
                    if (ftrID == -1) {
                        mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_MAX_FURNITURE);
                    } else {
                        mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_FURNITURE);
                    }
                }
            } else {
                mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_FAMI);
            }
            break;
        case NAME_TYPE_ITEM1:
            xyz_t_move(&pos, &player->world.position);
            if (inv_ovl->item_mark_bitfield != 0 && (inv_ovl->item_mark_bitfield & (1 << idx)) != 0) {
                int i;
                int cnt = 0;

                for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
                    if ((inv_ovl->item_mark_bitfield & (1 << i)) != 0) {
                        mActor_name_t item =
                            mRmTp_Item1ItemNo2FtrItemNo_AtPlayerRoom(Now_Private->inventory.pockets[i], TRUE);

                        if (mTG_search_put_pos(player, &pos, FALSE, FALSE, cnt, FALSE, FALSE) &&
                            mTG_common_throw_put_room(play, item, &pos, mCoBG_LAYER0, cnt)) {
                            mPr_SetPossessionItem(Now_Private, i, EMPTY_NO, mPr_ITEM_COND_NORMAL);
                            cnt++;
                        }
                    }
                }

                if (cnt > 0) {
                    mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
                    mMkRm_ReportChangePlayerRoom();
                    mTG_close_window(submenu, menu_info, FALSE);
                } else {
                    mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_ITEM);
                }
            } else {
                if (aMR_CLIP != NULL) {
                    mTG_get_unit_front_player(&ut_pos, &pos, player->shape_info.rotation.y);
                    if (mTG_check_free_2nd_layer(&ut_pos)) {
                        if (mFI_Wpos2UtNum(&ux, &uz, ut_pos) && aMR_CLIP->judge_place_2nd_layer_proc(ux, uz) &&
                            mTG_common_throw_put_room(play, put_item, &ut_pos, mCoBG_LAYER1, 0)) {
                            mPr_SetPossessionItem(Now_Private, idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);
                            mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
                            mTG_close_window(submenu, menu_info, FALSE);
                            mMkRm_ReportChangePlayerRoom();
                            return;
                        }
                    }
                }

                if (mTG_search_put_pos(player, &pos, FALSE, FALSE, 0, FALSE, FALSE) &&
                    mTG_common_throw_put_room(play, put_item, &pos, mCoBG_LAYER0, 0)) {
                    mPr_SetPossessionItem(Now_Private, idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);
                    mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
                    mMkRm_ReportChangePlayerRoom();
                    mTG_close_window(submenu, menu_info, FALSE);
                } else {
                    mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_ITEM);
                }
            }
            break;
    }
}

static void mTG_put_all_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    switch (Common_Get(field_type)) {
        case mFI_FIELDTYPE2_FG:
            mTG_field_put_proc(submenu, menu_info);
            break;
        case mFI_FIELDTYPE2_PLAYER_ROOM:
            mTG_room_put_proc(submenu, menu_info);
            break;
        case mFI_FIELDTYPE2_NPC_ROOM:
            break;
        case mFI_FIELDTYPE2_ROOM:
            break;
        default:
            break;
    }
}

static void mTG_dump_mail_mark_conf_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[tag_ovl->sel_tag_idx];

    mTG_chg_tag_func2(submenu, menu_info, tag, mTG_TYPE_DUMP_MAIL_MARK_CONF);
    sAdo_SysTrgStart(NA_SE_33);
}

static void mTG_next_open_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[tag_ovl->sel_tag_idx];
    int next_type;

    if (tag->type == mTG_TYPE_CP_DELETE) {
        next_type = mTG_TYPE_CP_DELETE2;
    } else if (tag->type == mTG_TYPE_TAISOU_CARD || tag->type == mTG_TYPE_FIELD_SIGN) {
        next_type = mTG_TYPE_DUMP_ITEM;
    } else {
        next_type = mTG_TYPE_DUMP_MAIL;
    }

    mTG_chg_tag_func2(submenu, menu_info, tag, next_type);
    sAdo_SysTrgStart(NA_SE_33);
}

static void mTG_next_open_needlework_sel_stick_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[tag_ovl->sel_tag_idx];
    int next_type;

    /* @BUG - if Save::field_type is out of the normal enum value range then next_type will be undefined */
    switch (Common_Get(field_type)) {
        case mFI_FIELDTYPE2_PLAYER_ROOM:
            if (Save_Get(scene_no) == SCENE_COTTAGE_MY || mSc_IS_SCENE_BASEMENT(Save_Get(scene_no))) {
                next_type = mTG_TYPE_TAG_NW_OR_SEL_STICK;
            } else {
                next_type = mTG_TYPE_TAG_NW_MR_SEL_STICK;
            }
            break;
        case mFI_FIELDTYPE2_FG:
        case mFI_FIELDTYPE2_NPC_ROOM:
        case mFI_FIELDTYPE2_ROOM:
#ifdef BUGFIXES
        default:
#endif
            next_type = mTG_TYPE_TAG_NW_OR_SEL_STICK;
            break;
    }

    mTG_chg_tag_func2(submenu, menu_info, tag, next_type);
    sAdo_SysTrgStart(NA_SE_33);
}

static void mTG_next_open_needlework_sel_put_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[tag_ovl->sel_tag_idx];

    mTG_chg_tag_func2(submenu, menu_info, tag, mTG_TYPE_TAG_NW_SEL_PUT);
    sAdo_SysTrgStart(NA_SE_33);
}

static void mTG_free_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_set_trade_cond(submenu, menu_info, mHm_HANIWA_TRADE_0, 0);
}

static void mTG_catch_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[0];
    mTG_tag_c* cur_tag = &tag_ovl->tags[tag_ovl->sel_tag_idx];
    int idx = 0;
    int item_cond = mPr_ITEM_COND_NORMAL;
    mActor_name_t* item_p = NULL;
    Mail_c* mail_p = NULL;

    if (cur_tag->table == mTG_TABLE_ITEM) {
        idx = mTG_get_table_idx(tag);
        item_p = &Now_Private->inventory.pockets[idx];
        item_cond = mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, idx);
        if (*item_p != EMPTY_NO) {
            mQst_CheckGrabItem(*item_p, idx);
        }
    } else if (cur_tag->table == mTG_TABLE_MAIL || cur_tag->table == mTG_TABLE_MBOX ||
               cur_tag->table == mTG_TABLE_CPMAIL) {
        idx = mTG_get_table_idx(tag);
        mail_p = mTG_get_mail_pointer(submenu, NULL);

        if (mMl_check_not_used_mail(mail_p) == TRUE) {
            return;
        }

        if (submenu->overlay->tag_ovl->sel_tag_idx == 0 && menu_info->menu_type != mSM_OVL_MAILBOX &&
            menu_info->menu_type != mSM_OVL_CPMAIL) {
            item_p = &mail_p->present;
            if (*item_p != EMPTY_NO) {
                if (mMl_check_set_present_myself(mail_p)) {
                    item_cond = mPr_ITEM_COND_NORMAL;
                    mail_p = NULL;
                } else if (mPr_GetPossessionItemIdx(Now_Private, EMPTY_NO) != -1) {
                    item_cond = mPr_ITEM_COND_PRESENT;
                    mail_p = NULL;
                } else {
                    item_p = NULL;
                }
            } else {
                item_p = NULL;
            }
        }
    } else {
        mActor_name_t item;

        switch (cur_tag->table) {
            case mTG_TABLE_HANIWA:
                idx = tag->tag_col;
                item_p = &Save_Get(homes[menu_info->data1]).haniwa.items[idx].item;
                break;
            case mTG_TABLE_PLAYER:
                item_p = &Now_Private->equipment;
                break;
            case mTG_TABLE_MONEY:
                mTG_make_money_sack(submenu, menu_info, ITM_MONEY_100);
                return;
            case mTG_TABLE_NEEDLEWORK:
            case mTG_TABLE_CPORIGINAL_NW:
                idx = mTG_get_table_idx(tag);
                item_p = &item;
                item = RSV_NW_ORIGINAL0 + idx;
                break;
            case mTG_TABLE_CPORIGINAL:
                idx = mTG_get_table_idx(tag);
                item = RSV_CPORIGINAL_FLD0_00 + mCO_top_folder(submenu) * mCO_ORIGINAL_NUM + idx;
                item_p = &item;
                break;
            case mTG_TABLE_GBA:
            case mTG_TABLE_CARD:
                idx = mTG_get_table_idx(tag);
                item_p = &item;
                item = RSV_GBAORIGINAL0 + idx;
                break;
        }
    }

    if (mail_p != NULL || (item_p != NULL && *item_p != EMPTY_NO)) {
        mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;

        mTG_mark_main_CLR(submenu, menu_info);
        if (cur_tag->table == mTG_TABLE_HANIWA) {
            hand_ovl->info.haniwa_item_cond = Save_Get(homes[menu_info->data1]).haniwa.items[idx].exchange_type;
            hand_ovl->info.haniwa_item_price = Save_Get(homes[menu_info->data1]).haniwa.items[idx].extra_data;
        } else {
            hand_ovl->info.haniwa_item_cond = mPr_ITEM_COND_PRESENT;
            hand_ovl->info.haniwa_item_price = 0;
        }

        mTG_catch_item_from_table(submenu, mail_p, item_p, item_cond, cur_tag->table, idx);
        mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
    }
}

static int mTG_mail_check(Mail_c* mail) {
    int flags = 0;

    if (mail->present != EMPTY_NO) {
        flags |= mTG_MAIL_FLAG_PRESENT;
    }

    if (!mMl_check_send_mail(mail)) {
        flags |= mTG_MAIL_FLAG_RECV;
    }

    return flags;
}

static void mTG_password_item_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);
    Submenu_Item_c* item_p = submenu->item_p;

    if (mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, idx) == mPr_ITEM_COND_QUEST) {
        mTG_open_warning_window(submenu, menu_info, mWR_WARNING_SELL_QUEST_ITEM);
    } else {
        item_p->item = Now_Private->inventory.pockets[idx];
        item_p->slot_no = idx;
        submenu->selected_item_num = 1;
        mTG_close_window(submenu, menu_info, TRUE);
    }
}

static int mTG_mark_enable_check(int menu_type, int param, int table, u8 field_type) {
    int res = mTG_MARK_TYPE_NONE;

    switch (menu_type) {
        case mSM_OVL_INVENTORY:
            switch (param) {
                case mSM_IV_OPEN_NORMAL:
                    switch (table) {
                        case mTG_TABLE_ITEM:
                            switch (field_type) {
                                case mFI_FIELDTYPE2_FG:
                                    res = mTG_MARK_TYPE_INV_FG_ITEM;
                                    break;
                                case mFI_FIELDTYPE2_PLAYER_ROOM:
                                    res = mTG_MARK_TYPE_INV_PLAYERROOM_ITEM;
                                    break;
                                default:
                                    res = mTG_MARK_TYPE_INV_OTHERROOM_ITEM;
                                    break;
                            }
                            break;
                        case mTG_TABLE_MAIL:
                            if (field_type == mFI_FIELDTYPE2_FG) {
                                res = mTG_MARK_TYPE_INV_FG_MAIL;
                            }
                            break;
                    }
                    break;
                case mSM_IV_OPEN_MAILBOX:
                    res = mTG_MARK_TYPE_INV_MAILBOX;
                    break;
                case mSM_IV_OPEN_SELL:
                    if (table == mTG_TABLE_ITEM) {
                        res = mTG_MARK_TYPE_INV_SELL_ITEM;
                    }
                    break;
            }
            break;
        case mSM_OVL_MAILBOX:
            res = mTG_MARK_TYPE_MAILBOX;
            break;
        case mSM_OVL_CPMAIL:
            switch (table) {
                case mTG_TABLE_CPMAIL:
                    res = mTG_MARK_TYPE_CPMAIL_CPMAIL;
                    break;
                case mTG_TABLE_MAIL:
                    res = mTG_MARK_TYPE_CPMAIL_MAIL;
                    break;
            }
            break;
        case mSM_OVL_MUSIC:
            res = mTG_MARK_TYPE_MUSIC;
            break;
        case mSM_OVL_NEEDLEWORK:
            // scrapped?
            break;
        case mSM_OVL_CPORIGINAL:
            // scrapped?
            break;
    }

    return res;
}

typedef union tag_mark_field_u {
    u16 field16;
    u32 field32;
    u32 music_box[2];
    u8 u8array[8];
} mTG_mark_field_u;

static int mTG_mark_main_sub(Submenu* submenu, int menu_type, int param, int table, int table_idx, Mail_c* mail,
                             int mode, mTG_mark_field_u** mark_bitfield_p, int* max_mark_count,
                             mTG_mark_field_u* updated_mark_bitfield) {
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    mMB_Ovl_c* mailbox_ovl = submenu->overlay->mailbox_ovl;
    mCM_Ovl_c* cpmail_ovl = submenu->overlay->cpmail_ovl;
    mMU_Ovl_c* music_ovl = submenu->overlay->music_ovl;
    mNW_Ovl_c* needlework_ovl = submenu->overlay->needlework_ovl;
    mCO_Ovl_c* cporiginal_ovl = submenu->overlay->cporiginal_ovl;
    int mark_type;

    mark_type = mTG_mark_enable_check(menu_type, param, table, Common_Get(field_type));
    switch (mark_type) {
        case mTG_MARK_TYPE_NONE:
            return FALSE;
        case mTG_MARK_TYPE_INV_FG_ITEM:
        case mTG_MARK_TYPE_INV_PLAYERROOM_ITEM: {
            mActor_name_t item = Now_Private->inventory.pockets[table_idx];
            u32 cond = mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, table_idx);
            int type;
            int category;

            category = ITEM_NAME_GET_CAT(item);
            type = ITEM_NAME_GET_TYPE(item);
            *(u16**)mark_bitfield_p = &inv_ovl->item_mark_bitfield;
            updated_mark_bitfield->field16 = 1 << table_idx;
            *max_mark_count = mPr_POCKETS_SLOT_COUNT;

            if ((mode == mTG_MARK_CHK || mode == mTG_MARK_OFF || mode == mTG_MARK_CLR) ||
                (item != EMPTY_NO && cond == mPr_ITEM_COND_NORMAL && !ITEM_IS_EXERCISE_CARD(item) &&
                 item != ITM_KNIFE_AND_FORK && !ITEM_IS_BALLOON(item) &&
                 (type != NAME_TYPE_ITEM1 || (category != ITEM1_CAT_FISH && category != ITEM1_CAT_INSECT)) &&
                 (mark_type != mTG_MARK_TYPE_INV_FG_ITEM ||
                  (mark_type == mTG_MARK_TYPE_INV_FG_ITEM && item != ITM_SIGNBOARD)) &&
                 (mark_type != mTG_MARK_TYPE_INV_PLAYERROOM_ITEM ||
                  ((mark_type == mTG_MARK_TYPE_INV_PLAYERROOM_ITEM && type != NAME_TYPE_FTR0 &&
                    type != NAME_TYPE_FTR1) &&
                   (!ITEM_IS_UMBRELLA2(item) && !ITEM_IS_CLOTH(item)))) &&
                 (mEv_CheckFirstJob() == FALSE || mark_type == mTG_MARK_TYPE_INV_PLAYERROOM_ITEM ||
                  type != NAME_TYPE_ITEM1 || category != ITEM1_CAT_PLANT))) {
                return TRUE;
            }
            return FALSE;
        }
        case mTG_MARK_TYPE_INV_OTHERROOM_ITEM:
            return FALSE;
        case mTG_MARK_TYPE_INV_SELL_ITEM: {
            mActor_name_t item = Now_Private->inventory.pockets[table_idx];

            *(u16**)mark_bitfield_p = &inv_ovl->item_mark_bitfield;
            updated_mark_bitfield->field16 = 1 << table_idx;
            *max_mark_count = mPr_POCKETS_SLOT_COUNT;

            if ((mode == mTG_MARK_CHK || mode == mTG_MARK_OFF || mode == mTG_MARK_CLR) ||
                (item != EMPTY_NO && !ITEM_IS_EXERCISE_CARD(item) && item != ITM_KNIFE_AND_FORK &&
                 (ITEM_NAME_GET_TYPE(item) != NAME_TYPE_ITEM1 || (ITEM_NAME_GET_CAT(item) != ITEM1_CAT_MONEY)) &&
                 (Common_Get(time.rtc_time).weekday != lbRTC_SUNDAY ||
                  (ITEM_NAME_GET_TYPE(item) != NAME_TYPE_ITEM1 || (ITEM_NAME_GET_CAT(item) != ITEM1_CAT_KABU))))) {
                return TRUE;
            }
            return FALSE;
        }
        case mTG_MARK_TYPE_INV_FG_MAIL:
        case mTG_MARK_TYPE_INV_MAILBOX:
        case mTG_MARK_TYPE_CPMAIL_MAIL:
        case mTG_MARK_TYPE_MAILBOX:
        case mTG_MARK_TYPE_CPMAIL_CPMAIL: {
            if (table == mTG_TABLE_MAIL) {
                *(u16**)mark_bitfield_p = &inv_ovl->mail_mark_bitfield2;
                updated_mark_bitfield->field16 = 1 << table_idx;
                *max_mark_count = mPr_INVENTORY_MAIL_COUNT;

                if (mode != mTG_MARK_CHK && mode != mTG_MARK_OFF && mode != mTG_MARK_CLR) {
                    if (mMl_check_not_used_mail(mail) == TRUE) {
                        return FALSE;
                    }

                    if (menu_type == mSM_OVL_MAILBOX) {
                        if (mail->present != EMPTY_NO ||
                            (mail->content.font != mMl_FONT_RECV_READ &&
                             mail->content.font != mMl_FONT_RECV_PLAYER_PRESENT_READ) ||
                            (mTG_mail_check(mail) & mTG_MAIL_FLAG_RECV) != mTG_MAIL_FLAG_RECV) {
                            return FALSE;
                        }
                    } else if (menu_type == mSM_OVL_CPMAIL) {
                        if ((mTG_mail_check(mail) & mTG_MAIL_FLAG_RECV) != mTG_MAIL_FLAG_RECV) {
                            return FALSE;
                        }
                    } else {
                        if ((mail->content.font != mMl_FONT_RECV_READ &&
                             mail->content.font != mMl_FONT_RECV_PLAYER_PRESENT_READ) ||
                            (mTG_mail_check(mail) & mTG_MAIL_FLAG_RECV) != mTG_MAIL_FLAG_RECV ||
                            (mTG_mail_check(mail) & mTG_MAIL_FLAG_PRESENT) == mTG_MAIL_FLAG_PRESENT) {
                            return FALSE;
                        }
                    }
                }

                return TRUE;
            } else if (table == mTG_TABLE_MBOX) {
                *(u16**)mark_bitfield_p = &mailbox_ovl->mark_bitfield;
                updated_mark_bitfield->field16 = 1 << table_idx;
                *max_mark_count = HOME_MAILBOX_SIZE;

                if ((mode != mTG_MARK_CHK || mode != mTG_MARK_OFF || mode != mTG_MARK_CLR)) {
                    if (mMl_check_not_used_mail(mail) == TRUE ||
                        (mTG_mail_check(mail) & mTG_MAIL_FLAG_RECV) != mTG_MAIL_FLAG_RECV) {
                        return FALSE;
                    }
                    return TRUE;
                }
            } else if (table == mTG_TABLE_CPMAIL) {
                if ((mode != mTG_MARK_CHK || mode != mTG_MARK_OFF || mode != mTG_MARK_CLR)) {
                    if (mMl_check_not_used_mail(mail) == TRUE ||
                        (mTG_mail_check(mail) & mTG_MAIL_FLAG_RECV) != mTG_MAIL_FLAG_RECV) {
                        return FALSE;
                    }
                }

                *(u32**)mark_bitfield_p = &cpmail_ovl->mark_bitfield;
                updated_mark_bitfield->field32 = 1 << table_idx;
                *max_mark_count = mCD_KEEP_MAIL_COUNT;
            } else {
                return FALSE;
            }
            break;
        }
        case mTG_MARK_TYPE_MUSIC: {
            *(u32**)mark_bitfield_p = music_ovl->mark_flg;
            updated_mark_bitfield->music_box[(table_idx / 32)] = 1 << ((u32)table_idx - (table_idx / 32) * 32);
            // SetMusicBox(updated_mark_bitfield->music_box, table_idx);
            *max_mark_count = MINIDISK_NUM;

            if ((mode != mTG_MARK_CHK || mode != mTG_MARK_OFF || mode != mTG_MARK_CLR)) {
                if (!ChkRoomMusicBox(table_idx)) {
                    return FALSE;
                }
            }
            break;
        }
        case mTG_MARK_TYPE_NEEDLEWORK_ORIGINAL:
            *(u16**)mark_bitfield_p = &needlework_ovl->mark_flg;
            updated_mark_bitfield->field16 = 1 << table_idx;
            *max_mark_count = mPr_ORIGINAL_DESIGN_COUNT;

            if (mode == mTG_MARK_CHK || mode == mTG_MARK_OFF || mode == mTG_MARK_CLR) {
                if (mNW_check_hide_flg(submenu, table_idx)) {
                    return FALSE;
                }
            }
            break;
        case mTG_MARK_TYPE_CPORIGINAL_ORIGINAL:
            *(u16**)mark_bitfield_p = &cporiginal_ovl->mark_flg;
            updated_mark_bitfield->field16 = 1 << table_idx;
            *max_mark_count = mCO_ORIGINAL_NUM;

            if (mode == mTG_MARK_CHK || mode == mTG_MARK_OFF || mode == mTG_MARK_CLR) {
                if (mCO_check_hide_flg(submenu, mCO_top_folder(submenu), table_idx)) {
                    return FALSE;
                }
            }
            break;
    }

    return TRUE;
}

static int mTG_bit_chk(u8* flags, u8* masks, int count) {
    int res = 0;
    int i;

    for (i = 0; i < count; i++, flags++, masks++) {
        res |= *flags & *masks;
    }

    return res;
}

static void mTG_bit_on(u8* flags, u8* bits, int count) {
    int i;

    for (i = 0; i < count; i++, flags++, bits++) {
        *flags |= *bits;
    }
}

static void mTG_bit_off(u8* flags, u8* bits, int count) {
    int i;

    for (i = 0; i < count; i++, flags++, bits++) {
        *flags &= ~*bits;
    }
}

static void mTG_bit_rvs(u8* flags, u8* bits, int count) {
    int i;

    for (i = 0; i < count; i++, flags++, bits++) {
        *flags ^= *bits;
    }
}

static void mTG_bit_clr(u8* flags, u8* bits, int count) {
    int i;

    for (i = 0; i < count; i++, flags++) {
        *flags = 0;
    }
}

static int mTG_bit_chk_all0(u8* flags, u8* bits, int count) {
    int res = 0;
    int i;

    for (i = 0; i < count; i++, flags++) {
        res |= *flags == 0;
    }

    return res;
}

extern int mTG_mark_mainX(Submenu* submenu, const mSM_MenuInfo_c* menu_info, int table, int table_idx, int mode,
                          int* chk_result) {
    int mark_res = FALSE;
    mTG_mark_field_u set_flags;
    mTG_mark_field_u* current_flags_p;
    int max_flag_count;
    int menu_type;
    int param;
    int chk_res = FALSE;
    int i;

    for (i = 0; i < 8; i++) {
        set_flags.u8array[i] = 0;
    }

    mark_res = mTG_mark_main_sub(submenu, menu_info->menu_type, menu_info->data0, table, table_idx, mTG_get_mail_pointer(submenu, NULL), mode,
                                 &current_flags_p, &max_flag_count, &set_flags);
    if (mark_res) {
        int byte_count = ((max_flag_count + 15) / 16) * 2;

        switch (mode) {
            case mTG_MARK_CHK:
                chk_res = mTG_bit_chk(current_flags_p->u8array, set_flags.u8array, byte_count);
                break;
            case mTG_MARK_ON:
                mTG_bit_on(current_flags_p->u8array, set_flags.u8array, byte_count);
                break;
            case mTG_MARK_OFF:
                mTG_bit_off(current_flags_p->u8array, set_flags.u8array, byte_count);
                break;
            case mTG_MARK_RVS:
                mTG_bit_rvs(current_flags_p->u8array, set_flags.u8array, byte_count);
                break;
            case mTG_MARK_CLR:
                mTG_bit_clr(current_flags_p->u8array, set_flags.u8array, byte_count);
                break;
            case mTG_MARK_CHK_ALL0:
                chk_res = mTG_bit_chk_all0(current_flags_p->u8array, set_flags.u8array, byte_count);
                break;
        }

        if (mode != mTG_MARK_CHK) {
            mTG_mark_mainX(submenu, menu_info, table, table_idx, mTG_MARK_CHK, &chk_res);
        }
    }

    if (chk_result != NULL) {
        *chk_result = chk_res;
    }

    return mark_res;
}

static void mTG_mark_main_CLR(Submenu* submenu, const mSM_MenuInfo_c* menu_info) {
    switch (menu_info->menu_type) {
        case mSM_OVL_INVENTORY:
            mTG_mark_mainX(submenu, menu_info, mTG_TABLE_ITEM, 0, mTG_MARK_CLR, NULL);
            mTG_mark_mainX(submenu, menu_info, mTG_TABLE_MAIL, 0, mTG_MARK_CLR, NULL);
            break;
        case mSM_OVL_MAILBOX:
            mTG_mark_mainX(submenu, menu_info, mTG_TABLE_MAIL, 0, mTG_MARK_CLR, NULL);
            mTG_mark_mainX(submenu, menu_info, mTG_TABLE_MBOX, 0, mTG_MARK_CLR, NULL);
            break;
        case mSM_OVL_CPMAIL:
            mTG_mark_mainX(submenu, menu_info, mTG_TABLE_MAIL, 0, mTG_MARK_CLR, NULL);
            mTG_mark_mainX(submenu, menu_info, mTG_TABLE_CPMAIL, 0, mTG_MARK_CLR, NULL);
            break;
        case mSM_OVL_CPORIGINAL:
            mTG_mark_mainX(submenu, menu_info, mTG_TABLE_CPORIGINAL_NW, 0, mTG_MARK_CLR, NULL);
            mTG_mark_mainX(submenu, menu_info, mTG_TABLE_CPORIGINAL, 0, mTG_MARK_CLR, NULL);
            break;
    }
}

extern int mTG_mark_main(Submenu* submenu, mSM_MenuInfo_c* menu_info, int mode, int* chk_result) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);

    return mTG_mark_mainX(submenu, menu_info, tag->table, idx, mode, chk_result);
}

static void mTG_write_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);
    int mail_idx = mMl_chk_mail_free_space(Now_Private->mail, mPr_INVENTORY_MAIL_COUNT);

    if (mail_idx >= 0) {
        mTG_open_board_init(submenu, menu_info, mail_idx, mSM_BD_OPEN_WRITE, idx);
    } else {
        mTG_open_warning_window(submenu, menu_info, mWR_WARNING_WRITE);
    }
}

static void mTG_priceset_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[0];
    mTG_tag_c* sel_tag = &tag_ovl->tags[tag_ovl->sel_tag_idx];

    mTG_chg_tag_func2(submenu, menu_info, sel_tag, mTG_TYPE_HANIWA_PRICE);
    submenu->overlay->haniwa_ovl->price = Save_Get(homes[menu_info->data1]).haniwa.items[tag->tag_col].extra_data;
    sAdo_SysTrgStart(NA_SE_33);
}

static void mTG_present_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);
    Mail_c* mail = &Now_Private->mail[idx];
    int present_myself = mMl_check_set_present_myself(mail);

    if (present_myself == FALSE && mPr_GetPossessionItemIdx(Now_Private, EMPTY_NO) == -1) {
        mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PR_LEAVE);
    } else {
        mTG_catch_item_from_table(submenu, NULL, &mail->present,
                                  present_myself ? mPr_ITEM_COND_NORMAL : mPr_ITEM_COND_PRESENT, mTG_TABLE_MAIL, idx);
    }
}

static void mTG_show_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_set_trade_cond(submenu, menu_info, mHm_HANIWA_TRADE_1, 0);
}

static void mTG_cancel_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    if (menu_info->menu_type == mSM_OVL_INVENTORY) {
        mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;

        if (menu_info->data0 == mSM_IV_OPEN_QUEST) {
            mTG_close_window(submenu, menu_info, TRUE);
        } else {
            if (inv_ovl != NULL) {
                inv_ovl->mail_mark_flag = 0;
            }

            mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_KEEP);
            sAdo_SysTrgStart(MONO(NA_SE_3));
        }
    } else {
        mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_KEEP);
        sAdo_SysTrgStart(MONO(NA_SE_3));
    }
}

static void mTG_read_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    Mail_c* mail;

    mTG_open_board_init(submenu, menu_info, -1, mSM_BD_OPEN_READ, -1);
    mail = mTG_get_mail_pointer(submenu, NULL);
    if (mail->content.font == mMl_FONT_RECV_PLAYER_PRESENT) {
        mail->content.font = mMl_FONT_RECV_PLAYER_PRESENT_READ;
    } else if (mail->content.font == mMl_FONT_RECV) {
        mail->content.font = mMl_FONT_RECV_READ;
    }

    mPr_SetItemCollectBit(ITM_PAPER_START + mail->content.paper_type);
}

static void mTG_take_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    Submenu_Item_c* item_p = submenu->item_p;
    int idx;

    if (menu_info->data0 == 4) {
        idx = menu_info->data1;
    } else {
        idx = mTG_get_table_idx(&submenu->overlay->tag_ovl->tags[0]);
    }

    item_p->item = Now_Private->inventory.pockets[idx];
    item_p->slot_no = idx;
    submenu->selected_item_num = 1;

    mPr_SetPossessionItem(Now_Private, idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);

    if (menu_info->data0 == 4) {
        if (menu_info->data3 == 1) {
            submenu->after_mode = aHOI_REQUEST_PUTAWAY;
        } else if (ITEM_NAME_GET_TYPE(item_p->item) == NAME_TYPE_ITEM1) {
            int category = ITEM_NAME_GET_CAT(item_p->item);

            if (category == ITEM1_CAT_FRUIT || category == ITEM1_CAT_FISH) {
                submenu->after_mode = aHOI_REQUEST_EAT;
            } else if (category == ITEM1_CAT_CLOTH) {
                submenu->after_mode = aHOI_REQUEST_GET_PULL_WAIT;
            } else {
                submenu->after_mode = aHOI_REQUEST_PUTAWAY;
            }
        } else {
            submenu->after_mode = aHOI_REQUEST_PUTAWAY;
        }
    } else if (menu_info->data3 == 2) {
        submenu->after_mode = aHOI_REQUEST_GET_PULL_WAIT;
    } else {
        submenu->after_mode = aHOI_REQUEST_PUTAWAY;
    }

    mPlib_request_main_give_from_submenu(
        item_p->item, submenu->after_mode,
        mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, item_p->slot_no) & mPr_ITEM_COND_PRESENT, FALSE);
    mTG_close_window(submenu, menu_info, TRUE);
}

static void mTG_m100_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_make_money_sack(submenu, menu_info, ITM_MONEY_100);
}

static void mTG_m1000_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_make_money_sack(submenu, menu_info, ITM_MONEY_1000);
}

static void mTG_m10000_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_make_money_sack(submenu, menu_info, ITM_MONEY_10000);
}

static void mTG_m30000_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_make_money_sack(submenu, menu_info, ITM_MONEY_30000);
}

static void mTG_1catch_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);
    mActor_name_t item = Now_Private->inventory.pockets[idx];

    mTG_mark_main_CLR(submenu, menu_info);
    if (ITEM_IS_WISP(item)) {
        hand_ovl->info.next_act = mHD_ACTION_CLOSE;
        hand_ovl->info.item = ITM_SPIRIT0;
        hand_ovl->info.item_cond = mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, idx);
        hand_ovl->info.hold_tbl = mTG_TABLE_ITEM;
        hand_ovl->info.hold_idx = idx;
        hand_ovl->info.catch_pg = 0;
        Now_Private->inventory.pockets[idx] = item - 1;
    } else if (ITEM_IS_PAPER(item)) {
        int paper_idx = item - ITM_PAPER_START;
        int paper_item = ITM_PAPER_START + PAPER2TYPE(paper_idx);

        hand_ovl->info.next_act = mHD_ACTION_CLOSE;
        hand_ovl->info.item = paper_item;
        hand_ovl->info.item_cond = mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, idx);
        hand_ovl->info.hold_tbl = mTG_TABLE_ITEM;
        hand_ovl->info.hold_idx = idx;
        hand_ovl->info.catch_pg = 0;
        Now_Private->inventory.pockets[idx] = paper_item + (PAPER2STACK(paper_idx) - 1) * PAPER_UNIQUE_NUM;
    } else {
        hand_ovl->info.next_act = mHD_ACTION_CLOSE;
        hand_ovl->info.item = ITM_TICKET_START | (item & (0xF << 3));
        hand_ovl->info.item_cond = mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, idx);
        hand_ovl->info.hold_tbl = mTG_TABLE_ITEM;
        hand_ovl->info.hold_idx = idx;
        hand_ovl->info.catch_pg = 0;
        Now_Private->inventory.pockets[idx] = item - 1;
    }

    mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
    mTG_init_tag_data_item_win(submenu);
    sAdo_SysTrgStart(NA_SE_33);
}

static void mTG_order_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mCL_Ovl_c* catalog_ovl = submenu->overlay->catalog_ovl;
    Submenu_Item_c* item_p = submenu->item_p;
    mCL_Menu_c* menu_p = &catalog_ovl->menu_data[catalog_ovl->page_order[0]];

    item_p->item = mRmTp_FtrItemNo2Item1ItemNo(menu_p->item_list[menu_p->top_idx + menu_p->y_idx], TRUE);
    submenu->selected_item_num = 1;
    if (catalog_ovl->item_data[catalog_ovl->item_data_idx].price == 0) {
        item_p->slot_no = 0;
    } else {
        item_p->slot_no = 1;
    }

    mTG_close_window(submenu, menu_info, TRUE);
}

static void mTG_bury_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);
    mActor_name_t item = Now_Private->inventory.pockets[idx];

    mTG_island_check_plant_plant(item);
    mTG_island_check_fruit_plant(item);

    if (!mFI_CheckInIsland() ||
        (!mSP_SearchItemCategoryPriority(item, mSP_KIND_FURNITURE, mSP_LISTTYPE_HOMEPAGE, NULL) &&
         !mSP_SearchItemCategoryPriority(item, mSP_KIND_FURNITURE, mSP_LISTTYPE_SPECIALPRESENT, NULL))) {
        mPlib_request_main_putin_scoop_from_submenu(&inv_ovl->shovel_pos, item, FALSE);
        mPr_SetPossessionItem(Now_Private, idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);
        mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
        mTG_close_window(submenu, menu_info, TRUE);
    } else {
        mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_FAMI);
    }
}

static void mTG_insect_release_sub(mActor_name_t item, int gold_scoop) {
    if (ITEM_IS_WISP(item)) {
        mPlib_request_main_release_creature_insect_from_submenu(aINS_INSECT_TYPE_SPIRIT, gold_scoop);
    } else {
        mPlib_request_main_release_creature_insect_from_submenu(ITEM_IS_INSECT(item) ? item - ITM_INSECT_START : 0,
                                                                gold_scoop);
    }
}

static void mTG_insect_release_demo_gold_scoop(mActor_name_t item) {
    mTG_insect_release_sub(item, TRUE);
}

static void mTG_insect_release(mActor_name_t item) {
    mTG_insect_release_sub(item, FALSE);
}

static void mTG_release_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    int idx = mTG_get_table_idx(&submenu->overlay->tag_ovl->tags[0]);
    mActor_name_t item = Now_Private->inventory.pockets[idx];
    GAME_PLAY* play = (GAME_PLAY*)gamePT;
    ACTOR* player = GET_PLAYER_ACTOR_ACTOR(play);
    s16 angle_y;
    Submenu_Item_c* item_p = submenu->item_p;

    item_p->slot_no = idx;
    item_p->item = item;
    submenu->selected_item_num = 1;

    if (menu_info->data0 == 13) {
        mPr_SetPossessionItem(Now_Private, idx, (mActor_name_t)menu_info->data1, mPr_ITEM_COND_NORMAL);
        angle_y = (s16)menu_info->data3;
    } else {
        mPr_SetPossessionItem(Now_Private, idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);
        angle_y = player->shape_info.rotation.y;
    }

    mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
    mTG_close_window(submenu, menu_info, TRUE);

    if (ITEM_NAME_GET_CAT(item) == ITEM1_CAT_FISH) {
        xyz_t_move(&submenu->water_pos, &submenu->overlay->inventory_ovl->release_pos);
        mPlib_request_main_release_creature_gyoei_from_submenu(angle_y, item, FALSE);
    } else if (ITEM_IS_WISP(item)) {
        int wisp_count = ITEM_IS_WISP(item) ? 1 + (item - ITM_SPIRIT0) : 0;

        if (wisp_count >= 2) {
            mPr_SetPossessionItem(Now_Private, idx, ITM_SPIRIT0 + (wisp_count - 2), mPr_ITEM_COND_NORMAL);
        } else {
            mPr_SetPossessionItem(Now_Private, idx, EMPTY_NO,
                                  mPr_ITEM_COND_NORMAL); // @cleanup - we already cleared the item before
        }
        mTG_insect_release(ITM_SPIRIT0);
    } else {
        mTG_insect_release(item);
    }
}

static void mTG_fly_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    int idx = mTG_get_table_idx(&submenu->overlay->tag_ovl->tags[0]);
    mActor_name_t item = Now_Private->inventory.pockets[idx];
    // @cleanup - copy-paste leftovers, we don't need player or angle
    GAME_PLAY* play = (GAME_PLAY*)gamePT;
    ACTOR* player = GET_PLAYER_ACTOR_ACTOR(play);
    s16 angle_y;
    Submenu_Item_c* item_p = submenu->item_p;

    item_p->slot_no = idx;
    item_p->item = item;
    submenu->selected_item_num = 1;

    if (menu_info->data0 == 13) {
        mPr_SetPossessionItem(Now_Private, idx, (mActor_name_t)menu_info->data1, mPr_ITEM_COND_NORMAL);
        angle_y = (s16)menu_info->data3;
    } else {
        mPr_SetPossessionItem(Now_Private, idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);
        angle_y = player->shape_info.rotation.y;
    }

    mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
    mTG_close_window(submenu, menu_info, TRUE);

    mPlib_request_main_release_creature_balloon_from_submenu(item, FALSE);
}

static void mTG_exchange_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    GAME_PLAY* play = (GAME_PLAY*)gamePT;
    ACTOR* player = GET_PLAYER_ACTOR_ACTOR(play);
    int sfx = NA_SE_31;

    if (!mTG_check_hand_condition(submenu)) {
        mActor_name_t item = (mActor_name_t)submenu->overlay->hand_ovl->info.item;
        int demo_gold_scoop = FALSE;
        int type = ITEM_NAME_GET_TYPE(item);
        int category = ITEM_NAME_GET_CAT(item);

        mTG_mark_main(submenu, menu_info, mTG_MARK_OFF, NULL);
        if (submenu->overlay->hand_ovl->info.item_cond == mPr_ITEM_COND_PRESENT) {
            switch (item) {
                case ITM_GOLDEN_NET:
                    item = ITM_GOLDEN_NET_PRESENT;
                    break;
                case ITM_GOLDEN_AXE:
                    item = ITM_GOLDEN_AXE_PRESENT;
                    break;
                case ITM_GOLDEN_SHOVEL:
                    item = ITM_GOLDEN_SHOVEL_PRESENT;
                    break;
                case ITM_GOLDEN_ROD:
                    item = ITM_GOLDEN_ROD_PRESENT;
                    break;
                default:
                    item = ITM_PRESENT;
                    break;
            }
        }

        if (mPlib_Check_golden_item_get_demo_end(mPlayer_GOLDEN_ITEM_TYPE_SHOVEL) == FALSE &&
            ITEM_IS_GOLD_SCOOP(menu_info->data1) && !ITEM_IS_GOLD_SCOOP(item)) {
            demo_gold_scoop = TRUE;
        }

        if (type == NAME_TYPE_ITEM1 && category == ITEM1_CAT_FISH) {
            mPlib_request_main_release_creature_gyoei_from_submenu((s16)menu_info->data3, item, demo_gold_scoop);
        } else if (type == NAME_TYPE_ITEM1 && category == ITEM1_CAT_INSECT) {
            if (demo_gold_scoop) {
                mTG_insect_release_demo_gold_scoop(item);
            } else {
                mTG_insect_release(item);
            }
        } else if (ITEM_IS_BALLOON(item)) {
            mPlib_request_main_release_creature_balloon_from_submenu(item, demo_gold_scoop);
        } else {
            xyz_t pos;

            if (!mFI_CheckInIsland() ||
                (!mSP_SearchItemCategoryPriority(item, mSP_KIND_FURNITURE, mSP_LISTTYPE_HOMEPAGE, NULL) &&
                 !mSP_SearchItemCategoryPriority(item, mSP_KIND_FURNITURE, mSP_LISTTYPE_SPECIALPRESENT, NULL))) {
                if (mTG_search_put_pos(player, &pos, item == ITM_SIGNBOARD, 0, item == ITM_SIGNBOARD, FALSE,
                                       item == ITM_SIGNBOARD) &&
                    mTG_common_throw_put_field(play, item, &pos, mCoBG_LAYER0)) {
                    if (demo_gold_scoop) {
                        mPlib_request_main_demo_get_golden_item_from_submenu();
                    } else {
                        mPlib_request_main_wait_from_submenu();
                        sfx = -1;
                        mPlib_request_main_wait_from_submenu();
                    }
                } else {
                    if (menu_info->data2 != NULL &&
                        (ITEM_IS_SCOOP(Now_Private->equipment) || ITEM_IS_GOLD_SCOOP(Now_Private->equipment))) {
                        mTG_island_check_plant_plant(item);
                        mTG_island_check_fruit_plant(item);
                        mPlib_request_main_putin_scoop_from_submenu((xyz_t*)menu_info->data2, item, demo_gold_scoop);
                    } else if (item == ITM_SIGNBOARD) {
                        mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_SIGN);
                        return;
                    } else {
                        mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_ITEM);
                        return;
                    }
                }
            } else {
                mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_FAMI);
                return;
            }
        }
    } else {
        int demo_gold_scoop = FALSE;

        if (mPlib_Check_golden_item_get_demo_end(mPlayer_GOLDEN_ITEM_TYPE_SHOVEL) == FALSE &&
            ITEM_IS_GOLD_SCOOP(menu_info->data1)) {
            demo_gold_scoop = TRUE;
        }

        if (demo_gold_scoop) {
            mPlib_request_main_demo_get_golden_item_from_submenu();
        } else {
            mPlib_request_main_wait_from_submenu();
        }
    }

    submenu->overlay->move_chg_base_proc(menu_info, mSM_MOVE_OUT_RIGHT);
    if (sfx >= 0) {
        sAdo_SysTrgStart(sfx);
    }
}

static void mTG_hukubukuro_open_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    int free_idx[3];
    mActor_name_t items[3];
    int idx;
    int i;
    int j;
    int count;
    mActor_name_t* item_p;
    mIV_Ovl_c* inv_ovl;
    mActor_name_t huku_item;
    int rng;
    int pinwheel_flag;
    int rng1;
    int rng2;

    item_p = Now_Private->inventory.pockets;
    count = 0;
    idx = mTG_get_table_idx(&submenu->overlay->tag_ovl->tags[0]);
    for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++, item_p++) {
        if (*item_p == EMPTY_NO) {
            free_idx[count] = i;
            count++;
            if (count == 3) {
                break;
            }
        }
    }

    if (count != 3) {
        mTG_open_warning_window(submenu, menu_info, mWR_WARNING_HUKUBUKURO_OPEN);
    } else {
        inv_ovl = submenu->overlay->inventory_ovl;
        huku_item = Now_Private->inventory.pockets[idx];
        inv_ovl->remove_timer = 70;
        inv_ovl->item_scale_type[idx] = mIV_ITEM_SCALE_TYPE_SHRINK;

        if (huku_item == ITM_HUKUBUKURO_BAG) {
            // Nook sale day grab bag
            pinwheel_flag = FALSE;
            rng = RANDOM(3) % 3; // @cleanup - why do we modulo 3 when we're already bound to three?

            for (i = 0; i < 3; i++) {
                if (i == rng && fqrand() <= 0.5f) {
                    pinwheel_flag = TRUE;
                }

                if (pinwheel_flag) {
                    int rng2 = RANDOM(8.0f) % 8; // @cleanup - again, why are we taking the modulus here?

                    pinwheel_flag = FALSE;
                    items[i] = ITM_YELLOW_PINWHEEL + rng2;
                } else {
                    int category;
                    f32 rngf = fqrand();

                    /* Equal 25% chance of the following */
                    if (rngf < 0.25f) {
                        category = mSP_KIND_CLOTH;
                    } else if (rngf < 0.5f) {
                        category = mSP_KIND_CARPET;
                    } else if (rngf < 0.75f) {
                        category = mSP_KIND_WALLPAPER;
                    } else {
                        category = mSP_KIND_FURNITURE;
                    }

                    mSP_SelectRandomItem_New(NULL, &items[i], 1, items, i, category, mSP_LISTTYPE_RARE, FALSE);
                }
            }
        } else {
            items[0] = ITM_MINIDISK35; // K.K. Love Song
            rng1 = RANDOM(mSP_GC_FAMICOM_TABLE_CNT) %
                   mSP_GC_FAMICOM_TABLE_CNT; // @cleanup - again with the unnecessary modulus
            rng2 = RANDOM(mSP_GC_FAMICOM_TABLE_CNT - 1) %
                   (mSP_GC_FAMICOM_TABLE_CNT - 1); // @cleanup - tired of repeating myself
            if (rng2 >= rng1) {
                rng2++; // ensure we don't land on the same famicom twice
            }

            items[1] = mSP_gc_famicom_table[rng1];
            items[2] = mSP_gc_famicom_table[rng2];
        }

        /* Give items */
        for (j = 0; j < 3; j++) {
            mPr_SetPossessionItem(Now_Private, free_idx[j], items[j], mPr_ITEM_COND_NORMAL);
            inv_ovl->item_scale_type[free_idx[j]] = mIV_ITEM_SCALE_TYPE_GROW + j;
        }

        mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
        sAdo_SysTrgStart(NA_SE_MENU_EXIT);
    }
}

static void mTG_cp_data_delete_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    // @stubbed - only used in N64 version for controller pak management
}

static void mTG_nw_room_put_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info, int type) {
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    GAME_PLAY* play = (GAME_PLAY*)gamePT;
    // @cleanup - we don't need the player here
    ACTOR* player = GET_PLAYER_ACTOR_ACTOR(play);
    int idx = mTG_get_table_idx(&submenu->overlay->tag_ovl->tags[0]);
    int res = mTG_nw_drop_furniture(play, type, mNW_get_image_no(submenu, idx));

    if (res >= 0) {
        if (inv_ovl != NULL) {
            inv_ovl->original_flag = TRUE;
        }

        mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
        mTG_close_window(submenu, menu_info, FALSE);
        mMkRm_ReportChangePlayerRoom();
    } else if (res == aMR_JUDGE_MAX_FTR) {
        mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_MAX_FURNITURE);
    } else {
        mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PUT_FURNITURE);
    }
}

static void mTG_nw_room_put_manekin_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_nw_room_put_proc(submenu, menu_info, mNW_TYPE_MANEKIN);
}

static void mTG_nw_stk_pat_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[2];

    switch (tag->tag_row) {
        case 2:
            mTG_nw_cover_proc(submenu, menu_info);
            break;
        case 3:
            mTG_nw_carpet_proc(submenu, menu_info);
            break;
    }
}

static void mTG_tag_remove_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];

    if (tag->table == mTG_TABLE_PLAYER) {
        mTG_catch_proc(submenu, menu_info);
    }
}

static void mTG_nw_room_put_umbrella_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_nw_room_put_proc(submenu, menu_info, mNW_TYPE_UMBRELLA);
}

static void mTG_nw_st_umbrella_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int idx = mTG_get_table_idx(tag);

    if (mPr_GetPossessionItemIdx(Now_Private, EMPTY_NO) >= 0 ||
        (ITEM_IS_MYUMBRELLA_TOOL(Now_Private->equipment) || Now_Private->equipment == EMPTY_NO)) {
        hand_ovl->info.next_act = mHD_ACTION_SASU2;
        hand_ovl->info.item = ITM_MY_ORG_UMBRELLA0 + mNW_get_image_no(submenu, idx);
        hand_ovl->info.hold_tbl = mTG_TABLE_NUM;

        mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
        submenu->overlay->segment.change_player_main_anime_idx = mIV_ANIM_CATCH;
        hand_ovl->info.wait_timer = 14;
        sAdo_SysTrgStart(NA_SE_5E);
    } else {
        mTG_open_warning_window(submenu, menu_info, mWR_WARNING_ORIGINAL);
    }
}

static void mTG_nw_st_wear_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;

    if (mPr_GetPossessionItemIdx(Now_Private, EMPTY_NO) >= 0 || ITEM_IS_RSVCLOTH(Now_Private->cloth.item)) {
        hand_ovl->info.next_act = mHD_ACTION_SASU2;
        hand_ovl->info.item = RSV_CLOTH;
        hand_ovl->info.hold_tbl = mTG_TABLE_NUM;

        mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
        submenu->overlay->segment.change_player_main_anime_idx = mIV_ANIM_CHANGE;
        sAdo_SysTrgStart(NA_SE_WEAR);
    } else {
        mTG_open_warning_window(submenu, menu_info, mWR_WARNING_ORIGINAL);
    }
}

static void mTG_change_original_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mNW_Ovl_c* needlework_ovl = submenu->overlay->needlework_ovl;
    mCO_Ovl_c* cporiginal_ovl = submenu->overlay->cporiginal_ovl;
    int needlework_mark_num;
    int needlework_clear_num;
    int cporiginal_mark_num;
    int cporiginal_clear_num;
    int i;

    needlework_mark_num = 0;
    for (i = 0; i < mPr_ORIGINAL_DESIGN_COUNT; i++) {
        if (mNW_check_mark_flg(submenu, i)) {
            needlework_mark_num++;
        }
    }

    cporiginal_mark_num = 0;
    for (i = 0; i < mCO_ORIGINAL_NUM; i++) {
        if (mCO_check_mark_flg(submenu, i)) {
            cporiginal_mark_num++;
        }
    }

    needlework_clear_num = 0;
    cporiginal_clear_num = 0;

    if (needlework_mark_num > cporiginal_mark_num) {
        needlework_clear_num = needlework_mark_num - cporiginal_mark_num;
    }

    if (!(needlework_mark_num > cporiginal_mark_num)) {
        cporiginal_clear_num = cporiginal_mark_num - needlework_mark_num;
    }

    if (needlework_mark_num == 0 || cporiginal_mark_num == 0) {
        needlework_ovl->mark_flg = 0;
        cporiginal_ovl->mark_flg = 0;
        sAdo_SysTrgStart(MONO(NA_SE_A));
    } else {
        mTG_Ovl_c* tag_ovl;
        int n;

        if (needlework_clear_num > 0) {
            n = 0;
            for (i = mPr_ORIGINAL_DESIGN_COUNT - 1; n < needlework_clear_num && i >= 0; i--) {
                if (mNW_check_mark_flg(submenu, i)) {
                    needlework_ovl->mark_flg &= ~(1 << i);
                    n++;
                }
            }
        }

        if (cporiginal_clear_num > 0) {
            n = 0;
            for (i = mCO_ORIGINAL_NUM - 1; n < cporiginal_clear_num && i >= 0; i--) {
                if (mCO_check_mark_flg(submenu, i)) {
                    cporiginal_ovl->mark_flg &= ~(1 << i);
                    n++;
                }
            }
        }

        tag_ovl = submenu->overlay->tag_ovl;
        tag_ovl->original_mark.mark_flg[mTG_ORG_TYPE_NW] = needlework_ovl->mark_flg;
        tag_ovl->original_mark.mark_flg[mTG_ORG_TYPE_CO] = cporiginal_ovl->mark_flg;
        tag_ovl->original_mark.mark_max[mTG_ORG_TYPE_NW] = mPr_ORIGINAL_DESIGN_COUNT;
        tag_ovl->original_mark.mark_max[mTG_ORG_TYPE_CO] = mCO_ORIGINAL_NUM;
        tag_ovl->original_mark.mark_mode = mTG_CHANGE_ORIGINAL_MARK_DECIDE;

        sAdo_SysTrgStart(NA_SE_MENU_EXIT);

        needlework_ovl->mark_flg = 0;
        cporiginal_ovl->mark_flg = 0;
    }

    mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
}

static void mTG_mv_priceSet(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    static int add_data[] = { 10000, 1000, 100, 10, 1 };
    u32 trigger = submenu->overlay->menu_control.trigger;
    int price = submenu->overlay->haniwa_ovl->price;

    if ((trigger & (BUTTON_B | BUTTON_START | BUTTON_Y)) != 0) {
        mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
        mTG_tag_c* last_tag = &tag_ovl->tags[tag_ovl->sel_tag_idx - 1];

        mTG_return_tag_init(submenu, last_tag->type, mTG_RETURN_KEEP);
        sAdo_SysTrgStart(MONO(NA_SE_3));
    } else if ((trigger & BUTTON_A) != 0) {
        if (price == 0) {
            mTG_set_trade_cond(submenu, menu_info, mHm_HANIWA_TRADE_0, 0);
        } else {
            mTG_set_trade_cond(submenu, menu_info, mHm_HANIWA_TRADE_2, price);
        }
    } else if ((trigger & (BUTTON_CUP | BUTTON_CDOWN)) != 0) {
        if ((trigger & BUTTON_CDOWN) != 0) {
            price -= add_data[tag->tag_col];
            if (price < 0) {
                price = 0;
            } else {
                sAdo_SysTrgStart(NA_SE_426);
            }
        } else {
            price += add_data[tag->tag_col];
            if (price > 99999) {
                price = 99999;
            } else {
                sAdo_SysTrgStart(NA_SE_426);
            }
        }

        submenu->overlay->haniwa_ovl->price = price;
    } else if ((trigger & (BUTTON_CLEFT | BUTTON_CRIGHT)) != 0) {
        if ((trigger & BUTTON_CLEFT) != 0) {
            if (tag->tag_col > 0) {
                tag->tag_col--;
                sAdo_SysTrgStart(NA_SE_CURSOL);
            }
        } else {
            if (tag->tag_col < 4) {
                tag->tag_col++;
                sAdo_SysTrgStart(NA_SE_CURSOL);
            }
        }
    }
}

static void mTG_change_mail(Mail_c* mail_a, Mail_c* mail_b) {
    Mail_c tmp_mail;

    mMl_copy_mail(&tmp_mail, mail_a);
    mMl_copy_mail(mail_a, mail_b);
    mMl_copy_mail(mail_b, &tmp_mail);
}

static void mTG_change_mail2(s16 field_a, Mail_c* mail_a, s16 field_b, Mail_c* mail_b) {
    if (field_a != mTG_MARK_IDX_UNSET && field_b != mTG_MARK_IDX_UNSET) {
        mTG_change_mail(mail_a, mail_b);
    }
}

static void mTG_change_mail3(s16 idx0, s16 idx1, Mail_c* mail0, Mail_c* mail1, s16 idx2, s16 idx3, Mail_c* mail2,
                             Mail_c* mail3) {
    if (idx0 < idx1) {
        if (idx2 < idx3) {
            mTG_change_mail2(idx0, mail0, idx2, mail2);
        } else {
            mTG_change_mail2(idx0, mail0, idx3, mail3);
            mTG_change_mail2(idx0, mail0, idx2, mail2);
        }
    } else {
        if (idx2 < idx3) {
            mTG_change_mail2(idx1, mail1, idx2, mail2);
            mTG_change_mail2(idx0, mail0, idx2, mail2);
        } else {
            mTG_change_mail2(idx1, mail1, idx2, mail2);
            mTG_change_mail2(idx0, mail0, idx3, mail3);
        }
    }
}

static f32 mIV_get_win_posY(Submenu* submenu, mSM_MenuInfo_c* menu_info, int page_idx) {
    if (page_idx == submenu->overlay->inventory_ovl->next_page_id) {
        return menu_info->position[1];
    } else {
        return -menu_info->position[1];
    }
}

static void mTG_cpack_change_mail_mark_move(Submenu* submenu, mIV_Ovl_c* inv_ovl, mCM_Ovl_c* cpmail_ovl, int mark_idx) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_cpmail_mark_c* cpmail_mark = &tag_ovl->cpmail_mark[mark_idx];

    if ((cpmail_mark->_4A & 3) == 3) {
        int i;

        tag_ovl->_2F4[0]._00 = 0;
        tag_ovl->_2F4[1]._00 = 0;
        // clang-format off
        mTG_change_mail3(
            cpmail_mark->idx_tbl[0], cpmail_mark->idx_tbl[1], cpmail_mark->mail_tbl[0], cpmail_mark->mail_tbl[1],
            cpmail_mark->idx_tbl[2], cpmail_mark->idx_tbl[3], cpmail_mark->mail_tbl[2], cpmail_mark->mail_tbl[3]
        );
        // clang-format on

        if (cpmail_mark->idx_tbl[0] != mTG_MARK_IDX_UNSET) {
            inv_ovl->mail_mark_bitfield &= ~(1 << cpmail_mark->idx_tbl[0]);
        }

        if (cpmail_mark->idx_tbl[1] != mTG_MARK_IDX_UNSET) {
            inv_ovl->mail_mark_bitfield &= ~(1 << cpmail_mark->idx_tbl[1]);
        }

        if (cpmail_mark->idx_tbl[2] != mTG_MARK_IDX_UNSET) {
            cpmail_ovl->mark_bitfield2 &= ~(1 << cpmail_mark->idx_tbl[2]);
        }

        if (cpmail_mark->idx_tbl[3] != mTG_MARK_IDX_UNSET) {
            cpmail_ovl->mark_bitfield2 &= ~(1 << cpmail_mark->idx_tbl[3]);
        }

        // Clear primary bitfields
        if (cpmail_mark->idx_tbl[0] != mTG_MARK_IDX_UNSET) {
            inv_ovl->mail_mark_bitfield2 &= ~(1 << cpmail_mark->idx_tbl[0]);
        }

        if (cpmail_mark->idx_tbl[2] != mTG_MARK_IDX_UNSET) {
            cpmail_ovl->mark_bitfield &= ~(1 << cpmail_mark->idx_tbl[2]);
        }

        for (i = 0; i < 4; i++) {
            cpmail_mark->idx_tbl[i] = mTG_MARK_IDX_UNSET;
            cpmail_mark->mail_tbl[i] = NULL;
        }

        sAdo_SysTrgStart(NA_SE_446);
        cpmail_mark->mode = mTG_CHANGE_MAIL_MARK_DECIDE;
        mTG_init_tag_data_item_win(submenu);
    } else {
        mTG_cpmail_mark_pos_c* pos_p;
        int i;

        add_calc(&tag_ovl->_370, 1.0f, 1.0f - sqrtf(0.5f), 0.175f, 0.005f);
        for (i = 0; i < 2; i++) {
            pos_p = &tag_ovl->_2F4[i];

            if ((cpmail_mark->_4A & (1 << i)) != 0) {
                pos_p->_00 = 0;
            } else {
                f32 x0;
                f32 y0;
                f32 y1;
                f32 x1;
                f32 tmp;

                x0 = cpmail_mark->_20[i][0];
                y0 = cpmail_mark->_20[i][1];
                x1 = cpmail_mark->_30[i][0];
                y1 = cpmail_mark->_30[i][1];
                tmp = tag_ovl->_370;

                if (1.0f - tmp <= 0.00999999f) {
                    pos_p->pos[0] = x1;
                    pos_p->pos[1] = y1;
                    cpmail_mark->_4A |= (1 << i);
                } else {
                    pos_p->pos[0] = x0 + (x1 - x0) * tmp;
                    pos_p->pos[1] = y0 + (y1 - y0) * tag_ovl->_370;
                    pos_p->_00 = cpmail_mark->_00[i];
                }
            }
        }

        mTG_init_tag_data_item_win(submenu);
    }
}

static void mTG_cpack_change_mail_mark_decide(Submenu* submenu, mIV_Ovl_c* inv_ovl, mCM_Ovl_c* cpmail_ovl,
                                              int mark_idx) {
    static int table_no[] = { mTG_TABLE_MAIL, mTG_TABLE_CPMAIL };
    int k;
    int j;
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    s16 inv_move_idx;
    s16 cpmail_move_idx;
    s16 inv_free_idx;
    s16 cpmail_free_idx;
    Mail_c* inv_mail;
    Mail_c* cpmail_mail;
    int cpmail_top_page = cpmail_ovl->page_order[0];
    s16 i;
    Mail_c* inv_move_mail;
    Mail_c* cpmail_move_mail;
    Mail_c* inv_free_mail;
    Mail_c* cpmail_free_mail;
    mTG_cpmail_mark_c* cpmail_mark; // = &tag_ovl->cpmail_mark[mark_idx];
    s16 mail_idx1[2];
    s16 mail_idx0[2];
    Mail_c* mail_tbl1[2];
    Mail_c* mail_tbl0[2];
    mSM_MenuInfo_c* inv_menu;
    mSM_MenuInfo_c* cpmail_menu;

    inv_mail = Now_Private->mail;
    inv_move_idx = -1;
    inv_free_idx = -1;
    inv_move_mail = NULL;
    inv_free_mail = NULL;
    for (i = 0; i < mPr_INVENTORY_MAIL_COUNT; i++, inv_mail++) {
        if (inv_move_idx < 0 && (inv_ovl->mail_mark_bitfield2 & (1 << i)) != 0) {
            inv_move_idx = i;
            inv_move_mail = inv_mail;
        } else if (inv_free_idx < 0 && mMl_check_not_used_mail(inv_mail)) {
            inv_free_idx = i;
            inv_free_mail = inv_mail;
        }

        if (inv_move_idx >= 0 && inv_free_idx >= 0) {
            break;
        }
    }

    cpmail_mail = cpmail_ovl->card_mail->mail[cpmail_top_page];
    cpmail_move_idx = -1;
    cpmail_free_idx = -1;
    cpmail_move_mail = NULL;
    cpmail_free_mail = NULL;
    for (i = 0; i < mCD_KEEP_MAIL_COUNT; i++, cpmail_mail++) {
        if (cpmail_move_idx < 0 && (cpmail_ovl->mark_bitfield & (1 << i)) != 0) {
            cpmail_move_mail = cpmail_mail;
            cpmail_move_idx = i;
        } else if (cpmail_free_idx < 0 && mMl_check_not_used_mail(cpmail_mail)) {
            cpmail_free_mail = cpmail_mail;
            cpmail_free_idx = i;
        }

        if (cpmail_free_idx >= 0 && cpmail_move_idx >= 0) {
            break;
        }
    }

    if (inv_move_idx < 0) {
        cpmail_free_idx = -1;
        cpmail_free_mail = NULL;
    }

    if (cpmail_move_idx < 0) {
        inv_free_idx = -1;
        inv_free_mail = NULL;
    }

    for (j = 0; j < 2; j++) {
        mail_idx1[j] = mTG_MARK_IDX_UNSET;
        mail_idx0[j] = mTG_MARK_IDX_UNSET;
        mail_tbl1[j] = NULL;
        mail_tbl0[j] = NULL;
    }

    if (inv_move_idx < 0) {
        inv_move_idx = mTG_MARK_IDX_UNSET;
        inv_move_mail = NULL;
    }

    mail_idx1[0] = inv_move_idx;
    mail_idx0[1] = inv_move_idx;
    mail_tbl1[0] = inv_move_mail;
    mail_tbl0[1] = inv_move_mail;

    if (inv_free_idx >= 0) {
        if (inv_free_idx < inv_move_idx) {
            mail_idx0[1] = inv_free_idx;
            mail_tbl0[1] = inv_free_mail;
        } else {
            inv_free_idx = mTG_MARK_IDX_UNSET;
            inv_free_mail = NULL;
        }
    } else {
        inv_free_idx = mTG_MARK_IDX_UNSET;
        inv_free_mail = NULL;
    }

    if (cpmail_move_idx < 0) {
        cpmail_move_idx = mTG_MARK_IDX_UNSET;
        cpmail_move_mail = NULL;
    }

    mail_idx1[1] = cpmail_move_idx;
    mail_idx0[0] = cpmail_move_idx;
    mail_tbl1[1] = cpmail_move_mail;
    mail_tbl0[0] = cpmail_move_mail;

    if (cpmail_free_idx >= 0) {
        if (cpmail_free_idx < cpmail_move_idx) {
            mail_idx0[0] = cpmail_free_idx;
            mail_tbl0[0] = cpmail_free_mail;
        } else {
            cpmail_free_idx = mTG_MARK_IDX_UNSET;
            cpmail_free_mail = NULL;
        }
    } else {
        cpmail_free_idx = mTG_MARK_IDX_UNSET;
        cpmail_free_mail = NULL;
    }

    cpmail_mark = &tag_ovl->cpmail_mark[mark_idx];

    cpmail_mark->mail_tbl[0] = inv_move_mail;
    cpmail_mark->mail_tbl[1] = inv_free_mail;
    cpmail_mark->mail_tbl[2] = cpmail_move_mail;
    cpmail_mark->mail_tbl[3] = cpmail_free_mail;

    cpmail_mark->idx_tbl[0] = inv_move_idx;
    cpmail_mark->idx_tbl[1] = inv_free_idx;
    cpmail_mark->idx_tbl[2] = cpmail_move_idx;
    cpmail_mark->idx_tbl[3] = cpmail_free_idx;
    
    tag_ovl->_370 = 0.0f;
    cpmail_mark->_4A = 0b11; // 3
    cpmail_mark->mode = mTG_CHANGE_MAIL_MARK_MOVE;
    
    inv_menu = &submenu->overlay->menu_info[mSM_OVL_INVENTORY];
    cpmail_menu = &submenu->overlay->menu_info[mSM_OVL_CPMAIL];

    for (k = 0; k < 2; k++) {
        if (mail_idx1[k] != mTG_MARK_IDX_UNSET) {
            cpmail_mark->_00[k] = mail_tbl1[k];
            cpmail_mark->_00[2 + k] = mail_tbl0[k];
            mTG_set_hand_pos(submenu, cpmail_mark->_20[k], table_no[k], mail_idx1[k]);
            mTG_set_hand_pos(submenu, cpmail_mark->_30[k], table_no[1 - k], mail_idx0[k]);

            switch (k) {
                case 0: {
                    cpmail_mark->_20[k][0] += inv_menu->position[0];
                    cpmail_mark->_20[k][1] += mIV_get_win_posY(submenu, inv_menu, 1);
                    cpmail_mark->_30[k][0] += cpmail_menu->position[0];
                    cpmail_mark->_30[k][1] += mIV_get_win_posY(submenu, cpmail_menu, 1);
                    break;
                }
                case 1: {
                    cpmail_mark->_20[k][0] += cpmail_menu->position[0];
                    cpmail_mark->_20[k][1] += mIV_get_win_posY(submenu, cpmail_menu, 1);
                    cpmail_mark->_30[k][0] += inv_menu->position[0];
                    cpmail_mark->_30[k][1] += mIV_get_win_posY(submenu, inv_menu, 1);
                    break;
                }
            }

            switch (k) {
                case 0:
                    inv_ovl->mail_mark_bitfield |= (1 << inv_move_idx);
                    break;
                case 1:
                    cpmail_ovl->mark_bitfield2 |= (1 << cpmail_move_idx);
            }

            cpmail_mark->_4A &= ~(1 << k);
        }
    }

    mTG_init_tag_data_item_win(submenu);
}

static int mTG_cpack_change_mail_mark_main(Submenu* submenu, mIV_Ovl_c* inv_ovl, mCM_Ovl_c* cpmail_ovl) {
    switch (submenu->overlay->tag_ovl->cpmail_mark[0].mode) {
        case mTG_CHANGE_MAIL_MARK_DECIDE:
            mTG_cpack_change_mail_mark_decide(submenu, inv_ovl, cpmail_ovl, 0);
        // fallthrough
        case mTG_CHANGE_MAIL_MARK_MOVE:
            mTG_cpack_change_mail_mark_move(submenu, inv_ovl, cpmail_ovl, 0);
            break;
    }

    return TRUE;
}

static int mTG_trans_mail_mark(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    mMB_Ovl_c* mailbox_ovl = submenu->overlay->mailbox_ovl;
    Mail_c* src;

    mailbox_ovl->_03++;
    if (mailbox_ovl->_03 % 3 == 0) {
        int dst_idx = mMl_chk_mail_free_space(Now_Private->mail, mPr_INVENTORY_MAIL_COUNT);

        if (dst_idx != -1) {
            int src_idx = 0;
            int i;

            for (i = mMB_MAIL_COUNT - 1; i >= 0; i--) {
                if ((mailbox_ovl->mark_bitfield & (1 << i)) != 0) {
                    src_idx = i;
                    break;
                }
            }

            src = &Common_Get(now_home)->mailbox[src_idx];
            mMl_copy_mail(&Now_Private->mail[dst_idx], src);
            mMl_clear_mail(src);
            tag->tag_col = src_idx % 2;
            tag->tag_row = src_idx / 2;
            mTG_set_hand_pos(submenu, tag->base_pos, tag->table, src_idx);
            sAdo_SysTrgStart(NA_SE_446);
            mailbox_ovl->mark_bitfield &= ~(1 << src_idx);
            mTG_init_tag_data_item_win(submenu);
            return TRUE;
        } else {
            mailbox_ovl->mark_flag = 0;
            mailbox_ovl->mark_bitfield = 0;
            return TRUE;
        }
    }

    return mailbox_ovl->open_flag == TRUE;
}

static int mTG_trans_mail(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    mMB_Ovl_c* mailbox_ovl = submenu->overlay->mailbox_ovl;
    Mail_c* src;

    mailbox_ovl->_03++;
    if (mailbox_ovl->_03 % 3 == 0) {
        int dst_idx = mMl_chk_mail_free_space(Now_Private->mail, mPr_INVENTORY_MAIL_COUNT);

        if (dst_idx != -1) {
            int src_idx = submenu->overlay->mailbox_ovl->get_last_mail_idx_proc();

            src = &Common_Get(now_home)->mailbox[src_idx];
            mMl_copy_mail(&Now_Private->mail[dst_idx], src);
            mMl_clear_mail(src);
            src_idx = submenu->overlay->mailbox_ovl->get_last_mail_idx_proc();
            tag->tag_col = src_idx % 2;
            tag->tag_row = src_idx / 2;
            mTG_set_hand_pos(submenu, tag->base_pos, tag->table, src_idx);
            sAdo_SysTrgStart(NA_SE_446);
            mTG_init_tag_data_item_win(submenu);
            return TRUE;
        }

        if (mailbox_ovl->open_flag == TRUE) {
            mTG_open_warning_window(submenu, menu_info, mWR_WARNING_MAILBOX);
            return TRUE;
        }
    }

    if (mailbox_ovl->open_flag == TRUE) {
        return TRUE;
    }

    return FALSE;
}

static int mTG_check_trans_mail(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    int res = FALSE;

    if (mMl_count_use_mail_space(Common_Get(now_home)->mailbox, HOME_MAILBOX_SIZE) != 0) {
        res = mTG_trans_mail(submenu, menu_info, tag);
    } else {
        submenu->overlay->mailbox_ovl->open_flag = FALSE;
    }

    return res;
}

static int mTG_check_trans_mail_mark(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    mMB_Ovl_c* mailbox_ovl = submenu->overlay->mailbox_ovl;
    int res = FALSE;

    if (mailbox_ovl->mark_bitfield != 0) {
        res = mTG_trans_mail_mark(submenu, menu_info, tag);
    } else {
        mailbox_ovl->open_flag = FALSE;
        mailbox_ovl->mark_bitfield = 0;
        mailbox_ovl->mark_flag = 0;
    }

    return res;
}

static int mTG_cpack_change_mail_mark(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    mCM_Ovl_c* cpmail_ovl = submenu->overlay->cpmail_ovl;
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    int res = FALSE;

    cpmail_ovl->_BBC++;
    if (inv_ovl->mail_mark_bitfield2 != 0 || cpmail_ovl->mark_bitfield != 0) {
        res = mTG_cpack_change_mail_mark_main(submenu, inv_ovl, cpmail_ovl);
    } else {
        inv_ovl->mail_mark_flag = 0;
        cpmail_ovl->mark_flag = 0;
    }

    return res;
}

static int mTG_move_cursol_in_cpedit(Submenu* submenu, mTG_tag_c* tag, u32 trigger) {
    return FALSE;
}

static int mTG_move_cursol_in_catalog(Submenu* submenu, mTG_tag_c* tag, u32 trigger) {
    mCL_Ovl_c* catalog_ovl = submenu->overlay->catalog_ovl;
    u32 btns = getButton() | getTrigger();
    mCL_Menu_c* catalog_menu = &catalog_ovl->menu_data[catalog_ovl->page_order[0]];
    int target = catalog_menu->top_idx + tag->tag_row;
    u32 masked_btns = btns & (BUTTON_CLEFT | BUTTON_CRIGHT | BUTTON_CDOWN | BUTTON_CUP);
    int new_target;
    int idx;

    if ((masked_btns & BUTTON_CLEFT) != 0) {
        if (catalog_menu->top_idx != 0 || tag->tag_row != 0) {
            catalog_menu->top_idx = 0;
            tag->tag_row = 0;
            catalog_ovl->change_flag = TRUE;
        }
    } else if ((masked_btns & BUTTON_CRIGHT) != 0) {
        s16 target = catalog_menu->item_count;
        int new_top_idx;
        int new_row;

        if (target > 0) {
            if (target < mCL_MENU_PAGE_SIZE) {
                new_top_idx = 0;
                new_row = target - 1;
            } else {
                new_top_idx = catalog_menu->item_count - mCL_MENU_PAGE_SIZE;
                new_row = mCL_MENU_PAGE_SIZE - 1;
            }

            if (catalog_menu->top_idx != new_top_idx || tag->tag_row != new_row) {
                catalog_menu->top_idx = new_top_idx;
                tag->tag_row = new_row;
                catalog_ovl->change_flag = TRUE;
            }
        }
    } else if ((trigger & BUTTON_CDOWN) != 0) {
        if ((masked_btns & BUTTON_CDOWN) != 0) {
            idx = catalog_menu->item_count - mCL_MENU_PAGE_SIZE;
            if ((catalog_menu->top_idx + mCL_MENU_PAGE_SIZE) <= idx) {
                catalog_menu->top_idx = catalog_menu->top_idx + mCL_MENU_PAGE_SIZE;
                catalog_ovl->change_flag = TRUE;
            } else if (target < catalog_menu->item_count - 1) {
                catalog_menu->top_idx = idx;
                if (catalog_menu->top_idx < 0) {
                    catalog_menu->top_idx = 0;
                }
                tag->tag_row = (catalog_menu->item_count - catalog_menu->top_idx) - 1;
                catalog_ovl->change_flag = TRUE;
            }
        } else {
            if (target < (catalog_menu->item_count - 1)) {
                if (tag->tag_row < 5 || (target == (catalog_menu->item_count - 2) && tag->tag_row < 6)) {
                    tag->tag_row++;
                } else {
                    catalog_menu->top_idx++;
                }

                catalog_ovl->change_flag = TRUE;
            }
        }
    } else if ((trigger & BUTTON_CUP) != 0) {
        if ((masked_btns & BUTTON_CUP) != 0) {
            if ((catalog_menu->top_idx - mCL_MENU_PAGE_SIZE) >= 0) {
                catalog_menu->top_idx -= mCL_MENU_PAGE_SIZE;
                catalog_ovl->change_flag = TRUE;
            } else if (target > 0) {
                catalog_menu->top_idx = 0;
                tag->tag_row = 0;
                catalog_ovl->change_flag = TRUE;
            }
        } else {
            if (target > 0) {
                if (tag->tag_row > 1 || (target == 1 && tag->tag_row > 0)) {
                    tag->tag_row--;
                } else {
                    catalog_menu->top_idx--;
                }

                catalog_ovl->change_flag = TRUE;
            }
        }
    }

    return catalog_ovl->change_flag;
}

static int mTG_move_cursol_base_left(mTG_tag_c* tag) {
    int res;

    if (tag->tag_col > 0) {
        tag->tag_col--;
        res = TRUE;
    } else {
        res = FALSE;
    }

    return res;
}

static int mTG_move_cursol_base_right(mTG_tag_c* tag) {
    int res;

    if (tag->tag_col < (mTG_table_data[tag->table].col_num - 1)) {
        tag->tag_col++;
        res = TRUE;
    } else {
        res = FALSE;
    }

    return res;
}

static int mTG_move_cursol_base_upper(mTG_tag_c* tag) {
    int res;

    if (tag->tag_row > 0) {
        tag->tag_row--;
        res = TRUE;
    } else {
        res = FALSE;
    }

    return res;
}

static int mTG_move_cursol_base_lower(mTG_tag_c* tag) {
    int res;

    if (tag->tag_row < (mTG_table_data[tag->table].row_num - 1)) {
        tag->tag_row++;
        res = TRUE;
    } else {
        res = FALSE;
    }

    return res;
}

static int mTG_move_check_hand_item_on_player(mActor_name_t item) {
    int category = ITEM_NAME_GET_CAT(item);

    return (ITEM_NAME_GET_TYPE(item) == NAME_TYPE_ITEM1 &&
            (category == ITEM1_CAT_CLOTH || category == ITEM1_CAT_FRUIT || category == ITEM1_CAT_TOOL ||
             (category == ITEM1_CAT_KABU && item != ITM_KABU_SPOILED)));
}

static int mTG_move_check_hand_item(Submenu* submenu, int table) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;

    if (hand_ovl->info.item == EMPTY_NO) {
        if (table != mTG_TABLE_BG) {
            return TRUE;
        }
    } else if (hand_ovl->info.item_cond != mPr_ITEM_COND_NORMAL || ITEM_IS_FTR(hand_ovl->info.item)) {
        if (table == mTG_TABLE_ITEM || table == mTG_TABLE_MAIL) {
            return TRUE;
        }
    } else {
        int category = ITEM_NAME_GET_CAT(hand_ovl->info.item);

        if (table == mTG_TABLE_MONEY) {
            if (category == ITEM1_CAT_MONEY) {
                return TRUE;
            }
        } else if (table == mTG_TABLE_BG) {
            if (category == ITEM1_CAT_CLOTH) {
                return TRUE;
            }
        } else if (table == mTG_TABLE_PLAYER) {
            if (mTG_move_check_hand_item_on_player(hand_ovl->info.item)) {
                return TRUE;
            }
        } else {
            return TRUE;
        }
    }

    return FALSE;
}

static int mTG_move_cursol_between_table_inventory_left(Submenu* submenu, mTG_tag_c* tag) {
    if (tag->table == mTG_TABLE_MAIL) {
        if (mMl_check_not_used_mail(&submenu->overlay->hand_ovl->info.mail) == TRUE) {
            if (tag->tag_row < 2 && mTG_move_check_hand_item(submenu, mTG_TABLE_MONEY)) {
                tag->table = mTG_TABLE_MONEY;
                tag->tag_row = 0;
                return TRUE;
            } else {
                tag->table = mTG_TABLE_ITEM;
                tag->tag_col = 4;
                tag->tag_row -= 2;
                if (tag->tag_row < 0) {
                    tag->tag_row = 0;
                }

                return TRUE;
            }
        }
    } else if (tag->table == mTG_TABLE_WCHANGE) {
        if (submenu->overlay->inventory_ovl->page_order[0] != mIV_PAGE_INVENTORY) {
            tag->table = mTG_TABLE_COLLECT;
            tag->tag_col = 7;
            if (tag->tag_row == 1) {
                tag->tag_row = 2;
            } else if (tag->tag_row == 2) {
                tag->tag_row = 4;
            }
        } else {
            tag->table = mTG_TABLE_MAIL;
            tag->tag_col = 1;
            if (tag->tag_row == 0) {
                tag->tag_row = 0;
            } else if (tag->tag_row == 1) {
                tag->tag_row = 2;
            } else {
                tag->tag_row = 3;
            }
        }

        return TRUE;
    } else if (tag->table == mTG_TABLE_MONEY) {
        if (mTG_move_check_hand_item(submenu, mTG_TABLE_PLAYER)) {
            tag->table = mTG_TABLE_PLAYER;
            return TRUE;
        }
    } else if (tag->table == mTG_TABLE_ITEM) {
        if (mTG_check_hand_condition(submenu) == TRUE) {
            tag->table = mTG_TABLE_INVENTORY_WC_ORG;
            tag->tag_row = 0;
            return TRUE;
        }
    } else if (tag->table == mTG_TABLE_PLAYER) {
        if (mTG_check_hand_condition(submenu) == TRUE) {
            tag->table = mTG_TABLE_INVENTORY_WC_ORG;
            return TRUE;
        }
    } else if (tag->table == mTG_TABLE_COLLECT) {
        submenu->overlay->hand_ovl->info.move_flag = mHD_MOVE_SWITCH_LEFT;
        tag->table = mTG_TABLE_WCHANGE;
        if (tag->tag_row == 1) {
            tag->tag_row = 0;
        } else if (tag->tag_row == 2) {
            tag->tag_row = 1;
        } else if (tag->tag_row == 3 || tag->tag_row == 4) {
            tag->tag_row = 2;
        }

        return TRUE;
    } else if (tag->table == mTG_TABLE_INVENTORY_WC_ORG) {
        tag->table = mTG_TABLE_WCHANGE;
        tag->tag_row = 1;
        submenu->overlay->hand_ovl->info.move_flag = mHD_MOVE_SWITCH_LEFT;
        return TRUE;
    }

    return FALSE;
}

static int mTG_move_cursol_between_table_inventory_right(Submenu* submenu, mTG_tag_c* tag) {
    if (tag->table == mTG_TABLE_MONEY) {
        tag->table = mTG_TABLE_MAIL;
        tag->tag_row = 1;
        return TRUE;
    } else if (tag->table == mTG_TABLE_ITEM) {
        if (mTG_move_check_hand_item(submenu, mTG_TABLE_MAIL)) {
            tag->table = mTG_TABLE_MAIL;
            tag->tag_col = 0;
            tag->tag_row += 2;
            return TRUE;
        }
    } else if (tag->table == mTG_TABLE_MAIL) {
        if (mTG_check_hand_condition(submenu) == TRUE) {
            tag->table = mTG_TABLE_WCHANGE;
            tag->tag_col = 0;
            tag->tag_row = (tag->tag_row + 1) >> 1;
            return TRUE;
        }
    } else if (tag->table == mTG_TABLE_COLLECT) {
        tag->table = mTG_TABLE_WCHANGE;
        tag->tag_col = 0;
        if (tag->tag_row > 2) {
            tag->tag_row = 2;
        } else if (tag->tag_row == 1) {
            tag->tag_row = 0;
        } else if (tag->tag_row == 2) {
            tag->tag_row = 1;
        }

        return TRUE;
    } else if (tag->table == mTG_TABLE_PLAYER) {
        if (mTG_move_check_hand_item(submenu, mTG_TABLE_MONEY)) {
            tag->table = mTG_TABLE_MONEY;
            return TRUE;
        }
    } else if (tag->table == mTG_TABLE_WCHANGE) {
        if (submenu->overlay->inventory_ovl->page_order[0] != mIV_PAGE_INVENTORY) {
            tag->table = mTG_TABLE_COLLECT;
            if (tag->tag_row == 1) {
                tag->tag_row = 2;
            } else if (tag->tag_row == 2) {
                tag->tag_row = 4;
            }
        } else {
            tag->table = mTG_TABLE_INVENTORY_WC_ORG;
            tag->tag_row = 0;
        }

        submenu->overlay->hand_ovl->info.move_flag = mHD_MOVE_SWITCH_RIGHT;
        return TRUE;
    } else if (tag->table == mTG_TABLE_INVENTORY_WC_ORG) {
        tag->table = mTG_TABLE_ITEM;
        tag->tag_row = 0;
        return TRUE;
    }

    return FALSE;
}

static int mTG_move_cursol_between_table_inventory_upper(Submenu* submenu, mTG_tag_c* tag) {
    if (tag->table == mTG_TABLE_BG) {
        tag->table = mTG_TABLE_ITEM;
        tag->tag_col = 4;
        tag->tag_row = 2;
        return TRUE;
    } else if (tag->table == mTG_TABLE_ITEM) {
        mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
        int category = ITEM_NAME_GET_CAT(hand_ovl->info.item);

        if (ITEM_NAME_GET_TYPE(hand_ovl->info.item) == NAME_TYPE_ITEM1 &&
            hand_ovl->info.item_cond == mPr_ITEM_COND_NORMAL) {
            if (category == ITEM1_CAT_MONEY) {
                tag->table = mTG_TABLE_MONEY;
                tag->tag_col = 0;
                tag->tag_row = 0;
                return TRUE;
            } else if (mTG_move_check_hand_item_on_player(hand_ovl->info.item)) {
                tag->table = mTG_TABLE_PLAYER;
                tag->tag_col = 0;
                tag->tag_row = 0;
                return TRUE;
            }
        }

        if (tag->tag_col < 2) {
            if (mTG_move_check_hand_item(submenu, mTG_TABLE_PLAYER)) {
                tag->table = mTG_TABLE_PLAYER;
                tag->tag_col = 0;
                tag->tag_row = 0;
                return TRUE;
            }
        } else {
            if (mTG_move_check_hand_item(submenu, mTG_TABLE_MONEY)) {
                tag->table = mTG_TABLE_MONEY;
                tag->tag_col = 0;
                tag->tag_row = 0;
                return TRUE;
            }
        }
    } else if (tag->table == mTG_TABLE_MONEY) {
        if (mTG_move_check_hand_item(submenu, mTG_TABLE_PLAYER)) {
            tag->table = mTG_TABLE_PLAYER;
            return TRUE;
        }
    }

    return FALSE;
}

static int mTG_move_cursol_between_table_inventory_lower(Submenu* submenu, mTG_tag_c* tag) {
    if (tag->table == mTG_TABLE_ITEM) {
        if (tag->tag_col == 4) {
            if (mTG_move_check_hand_item(submenu, mTG_TABLE_BG)) {
                tag->table = mTG_TABLE_BG;
                tag->tag_col = 0;
                tag->tag_row = 0;
                return TRUE;
            }
        }
    } else if (tag->table == mTG_TABLE_MONEY) {
        tag->table = mTG_TABLE_ITEM;
        tag->tag_col = 4;
        return TRUE;
    } else if (tag->table == mTG_TABLE_PLAYER) {
        tag->table = mTG_TABLE_ITEM;
        return TRUE;
    }

    return FALSE;
}

static int mTG_move_cursol_between_table_cpmail(Submenu* submenu, mTG_tag_c* tag, u32 trigger) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;

    if ((trigger & BUTTON_CLEFT) != 0) {
        if (tag->table == mTG_TABLE_CPMAIL_TI || tag->table == mTG_TABLE_CPMAIL) {
            tag->tag_col = 1;
            tag->table = mTG_TABLE_MAIL;
            return TRUE;
        } else if (tag->table == mTG_TABLE_CPMAIL_WC) {
            tag->table = mTG_TABLE_CPMAIL;
            tag->tag_col = 3;

            if (tag->tag_row < 2) {
                tag->tag_row = 0;
            } else if (tag->tag_row < 4) {
                tag->tag_row = 1;
            } else if (tag->tag_row < 6) {
                tag->tag_row = 2;
            } else if (tag->tag_row < 7) {
                tag->tag_row = 3;
            } else {
                tag->tag_row = 4;
            }

            if (!mTG_check_hand_condition(submenu)) {
                hand_ovl->info.next_act = mHD_ACTION_CLOSE2;
            }

            return TRUE;
        }
    } else if ((trigger & BUTTON_CDOWN) != 0) {
        if (tag->table == mTG_TABLE_CPMAIL_TI) {
            tag->table = mTG_TABLE_CPMAIL;
            tag->tag_row = 0;
            tag->tag_col = 0;
            return TRUE;
        }
    } else if ((trigger & BUTTON_CUP) != 0) {
        if (mMl_check_not_used_mail(&hand_ovl->info.mail) == TRUE) {
            if (tag->table != mTG_TABLE_CPMAIL_TI) {
                tag->table = mTG_TABLE_CPMAIL_TI;
                tag->tag_col = 0;
                tag->tag_row = 0;
                return TRUE;
            }
        }
    } else if ((trigger & BUTTON_CRIGHT) != 0) {
        if (tag->table == mTG_TABLE_MAIL) {
            tag->table = mTG_TABLE_CPMAIL;
            tag->tag_col = 0;
            return TRUE;
        } else if (tag->table == mTG_TABLE_CPMAIL_TI) {
            tag->table = mTG_TABLE_CPMAIL_WC;
            return TRUE;
        } else if (tag->table == mTG_TABLE_CPMAIL) {
            tag->table = mTG_TABLE_CPMAIL_WC;
            tag->tag_col = 0;
            if (tag->tag_row == 0) {
                tag->tag_row = 1;
            } else if (tag->tag_row == 1) {
                tag->tag_row = 3;
            } else if (tag->tag_row == 2) {
                tag->tag_row = 4;
            } else if (tag->tag_row == 3) {
                tag->tag_row = 6;
            } else {
                tag->tag_row = 7;
            }

            if (!mTG_check_hand_condition(submenu)) {
                hand_ovl->info.next_act = mHD_ACTION_OPEN;
            }

            return TRUE;
        }
    }

    return FALSE;
}

static int mTG_move_cursol_between_table_music(Submenu* submenu, mTG_tag_c* tag, u32 trigger) {
    return FALSE;
}

static int mTG_move_cursol_between_table_haniwa(mTG_tag_c* tag, u32 trigger) {
    int res = FALSE;

    if ((trigger & BUTTON_CDOWN) != 0 && tag->table == mTG_TABLE_HANIWA) {
        if (tag->tag_col == 3) {
            tag->tag_col = 4;
        } else {
            tag->tag_col += 2;
        }

        tag->table = mTG_TABLE_ITEM;
        res = TRUE;
    } else if ((trigger & BUTTON_CUP) != 0 && tag->table == mTG_TABLE_ITEM) {
        tag->table = mTG_TABLE_HANIWA;
        if (tag->tag_col < 2) {
            tag->tag_col = 0;
        } else {
            tag->tag_col -= 2;
        }

        tag->tag_row = 0;
        res = TRUE;
    }
    return res;
}

static int mTG_move_cursol_between_table_mailbox(Submenu* submenu, mTG_tag_c* tag, u32 trigger) {
    int res = FALSE;

    if ((trigger & BUTTON_CLEFT) != 0 && tag->table == mTG_TABLE_MAIL) {
        if (mTG_check_hand_condition(submenu)) {
            tag->table = mTG_TABLE_MBOX;
            tag->tag_col = 1;
            res = TRUE;
        }
    } else if ((trigger & BUTTON_CRIGHT) != 0 && tag->table == mTG_TABLE_MBOX) {
        tag->table = mTG_TABLE_MAIL;
        tag->tag_col = 0;
        res = TRUE;
    }
    return res;
}

static int mTG_move_cursol_between_table_catalog(Submenu* submenu, mTG_tag_c* tag, u32 trigger) {
    int res = FALSE;

    if ((trigger & BUTTON_CLEFT) != 0) {
        mCL_Ovl_c* catalog_ovl = submenu->overlay->catalog_ovl;
        mCL_Menu_c* catalog_menu = &catalog_ovl->menu_data[catalog_ovl->page_order[0]];

        if (tag->table == mTG_TABLE_CATALOG_WC) {
            if (tag->tag_row >= 4) {
                tag->tag_row--;
            }

            if (catalog_menu->item_count == 0) {
                tag->tag_row = 0;
            } else if (catalog_menu->item_count <= tag->tag_row) {
                tag->tag_row = catalog_menu->item_count - 1;
            } else if (tag->tag_row >= (mCL_MENU_PAGE_SIZE - 1)) {
                tag->tag_row = (mCL_MENU_PAGE_SIZE - 1);
            }

            tag->table = mTG_TABLE_CATALOG;
            catalog_ovl->change_flag = TRUE;
            res = TRUE;
        }
    } else if ((trigger & BUTTON_CRIGHT) != 0) {
        if (tag->table == mTG_TABLE_CATALOG) {
            tag->table = mTG_TABLE_CATALOG_WC;
            if (tag->tag_row >= 3) {
                tag->tag_row++;
            }
            res = TRUE;
        }
    }
    return res;
}

static int mTG_move_cursol_between_table_cporiginal(Submenu* submenu, mTG_tag_c* tag, u32 trigger) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
    int res = FALSE;

    if ((trigger & BUTTON_CLEFT) != 0) {
        if (tag->table == mTG_TABLE_CPORIGINAL_TI || tag->table == mTG_TABLE_CPORIGINAL) {
            tag->tag_col = 1;
            tag->table = mTG_TABLE_CPORIGINAL_NW;
            res = TRUE;
        } else if (tag->table == mTG_TABLE_CPORIGINAL_WC) {
            tag->table = mTG_TABLE_CPORIGINAL;
            tag->tag_col = 2;

            if (tag->tag_row < 2) {
                tag->tag_row = 0;
            } else if (tag->tag_row < 4) {
                tag->tag_row = 1;
            } else if (tag->tag_row < 6) {
                tag->tag_row = 2;
            } else {
                tag->tag_row = 3;
            }

            if (!mTG_check_hand_condition(submenu)) {
                hand_ovl->info.next_act = mHD_ACTION_CLOSE2;
            }

            res = TRUE;
        }
    } else if ((trigger & BUTTON_CDOWN) != 0) {
        if (tag->table == mTG_TABLE_CPORIGINAL_TI) {
            tag->table = mTG_TABLE_CPORIGINAL;
            tag->tag_row = 0;
            tag->tag_col = 0;
            res = TRUE;
        }
    } else if ((trigger & BUTTON_CUP) != 0) {
        if (mTG_check_hand_condition(submenu)) {
            if (tag->table != mTG_TABLE_CPORIGINAL_TI) {
                tag->table = mTG_TABLE_CPORIGINAL_TI;
                tag->tag_col = 0;
                tag->tag_row = 0;
                res = TRUE;
            }
        }
    } else if ((trigger & BUTTON_CRIGHT) != 0) {
        if (tag->table == mTG_TABLE_CPORIGINAL_NW) {
            tag->table = mTG_TABLE_CPORIGINAL;
            tag->tag_col = 0;
            res = TRUE;
        } else if (tag->table == mTG_TABLE_CPORIGINAL_TI) {
            tag->table = mTG_TABLE_CPORIGINAL_WC;
            res = TRUE;
        } else if (tag->table == mTG_TABLE_CPORIGINAL) {
            tag->table = mTG_TABLE_CPORIGINAL_WC;
            tag->tag_col = 0;
            if (tag->tag_row == 0) {
                tag->tag_row = 0;
            } else if (tag->tag_row == 1) {
                tag->tag_row = 2;
            } else if (tag->tag_row == 2) {
                tag->tag_row = 4;
            } else {
                tag->tag_row = 6;
            }

            if (!mTG_check_hand_condition(submenu)) {
                hand_ovl->info.next_act = mHD_ACTION_OPEN;
            }

            res = TRUE;
        }
    }

    return res;
}

static int mTG_move_cursol_between_table_gba(Submenu* submenu, mTG_tag_c* tag, u32 trigger) {
    int res = FALSE;

    if ((trigger & BUTTON_CLEFT) != 0) {
        if (tag->table == mTG_TABLE_GBA_NW) {
            tag->tag_col = 3;
            if (tag->tag_row == 0 || tag->tag_row == 1) {
                tag->tag_row = 0;
            } else {
                tag->tag_row = 1;
            }
            tag->table = mTG_TABLE_GBA;
            res = TRUE;
        }
    } else if ((trigger & BUTTON_CRIGHT) != 0) {
        if (tag->table == mTG_TABLE_GBA) {
            tag->tag_col = 0;
            if (tag->tag_row == 0) {
                tag->tag_row = 1;
            } else if (tag->tag_row == 1) {
                tag->tag_row = 2;
            }
            tag->table = mTG_TABLE_GBA_NW;
            res = TRUE;
        }
    }
    return res;
}

static int mTG_move_cursol_between_table_card(Submenu* submenu, mTG_tag_c* tag, u32 trigger) {
    int res = FALSE;

    if ((trigger & BUTTON_CLEFT) != 0) {
        if (tag->table == mTG_TABLE_CARD_NW) {
            tag->tag_col = 0;
            tag->tag_row = 0;
            tag->table = mTG_TABLE_CARD;
            res = TRUE;
        }
    } else if ((trigger & BUTTON_CRIGHT) != 0) {
        if (tag->table == mTG_TABLE_CARD) {
            tag->tag_col = 0;
            tag->tag_row = 1;
            tag->table = mTG_TABLE_CARD_NW;
            res = TRUE;
        }
    }
    return res;
}

static int mTG_move_cursol_between_table_inventory(Submenu* submenu, mTG_tag_c* tag, mSM_MenuInfo_c* menu_info,
                                                   u32 trigger) {
    int res = FALSE;

    if ((menu_info->menu_type == mSM_OVL_INVENTORY &&
         (menu_info->data0 == mSM_IV_OPEN_NORMAL || menu_info->data0 == mSM_IV_OPEN_EXCHANGE)) ||
        (menu_info->menu_type == mSM_OVL_NEEDLEWORK && menu_info->data0 == mNW_OPEN_INV)) {
        if ((trigger & BUTTON_CLEFT) != 0) {
            res = mTG_move_cursol_between_table_inventory_left(submenu, tag);
        } else if ((trigger & BUTTON_CDOWN) != 0) {
            res = mTG_move_cursol_between_table_inventory_lower(submenu, tag);
        } else if ((trigger & BUTTON_CUP) != 0) {
            res = mTG_move_cursol_between_table_inventory_upper(submenu, tag);
        } else {
            res = mTG_move_cursol_between_table_inventory_right(submenu, tag);
        }
    }

    return res;
}

static int mTG_move_cursol_base(Submenu* submenu, mTG_tag_c* tag, mSM_MenuInfo_c* menu_info) {
    u32 trigger = submenu->overlay->menu_control.trigger;
    int res = FALSE;

    if ((trigger & (BUTTON_CLEFT | BUTTON_CDOWN | BUTTON_CUP | BUTTON_CRIGHT)) != 0 ||
        (tag->table == mTG_TABLE_CATALOG &&
         (trigger & (BUTTON_DLEFT | BUTTON_DDOWN | BUTTON_DUP | BUTTON_DRIGHT | BUTTON_CLEFT | BUTTON_CDOWN |
                     BUTTON_CUP | BUTTON_CRIGHT)) != 0)) {
        if (tag->table == mTG_TABLE_CPEDIT) {
            res = mTG_move_cursol_in_cpedit(submenu, tag, trigger);
        } else if (tag->table == mTG_TABLE_CATALOG) {
            res = mTG_move_cursol_in_catalog(submenu, tag, trigger);
        } else {
            if ((trigger & BUTTON_CLEFT) != 0) {
                res = mTG_move_cursol_base_left(tag);
            } else if ((trigger & BUTTON_CDOWN) != 0) {
                res = mTG_move_cursol_base_lower(tag);
            } else if ((trigger & BUTTON_CUP) != 0) {
                res = mTG_move_cursol_base_upper(tag);
            } else {
                res = mTG_move_cursol_base_right(tag);
            }
        }

        if (res == FALSE) {
            /* Process movement between tables */
            if (menu_info->menu_type == mSM_OVL_CPMAIL) {
                res = mTG_move_cursol_between_table_cpmail(submenu, tag, trigger);
            } else if (menu_info->menu_type == mSM_OVL_HANIWA) {
                res = mTG_move_cursol_between_table_haniwa(tag, trigger);
            } else if (menu_info->menu_type == mSM_OVL_MAILBOX) {
                res = mTG_move_cursol_between_table_mailbox(submenu, tag, trigger);
            } else if (menu_info->menu_type == mSM_OVL_CATALOG) {
                res = mTG_move_cursol_between_table_catalog(submenu, tag, trigger);
            } else if (menu_info->menu_type == mSM_OVL_MUSIC) {
                res = mTG_move_cursol_between_table_music(submenu, tag, trigger);
            } else if (menu_info->menu_type == mSM_OVL_CPORIGINAL) {
                res = mTG_move_cursol_between_table_cporiginal(submenu, tag, trigger);
            } else if (menu_info->menu_type == mSM_OVL_GBA) {
                switch (menu_info->data0) {
                    case 3:
                        res = mTG_move_cursol_between_table_gba(submenu, tag, trigger);
                        break;
                    case 4:
                        res = mTG_move_cursol_between_table_card(submenu, tag, trigger);
                        break;
                }
            } else {
                res = mTG_move_cursol_between_table_inventory(submenu, tag, menu_info, trigger);
            }
        }
    }

    return res;
}

static int mTG_select_tag_decide_item_normal(Submenu* submenu, mActor_name_t item, int idx) {
    static int tag_type_field[] = {
        mTG_TYPE_FIELD_LETTER,     // ITEM1_CAT_PAPER
        mTG_TYPE_FIELD_DEFAULT,    // ITEM1_CAT_MONEY
        mTG_TYPE_FIELD_DEFAULT,    // ITEM1_CAT_TOOL
        mTG_TYPE_CATCH_ITEM,       // ITEM1_CAT_FISH
        mTG_TYPE_FIELD_DEFAULT,    // ITEM1_CAT_CLOTH
        mTG_TYPE_FIELD_DEFAULT,    // ITEM1_CAT_ETC
        mTG_TYPE_FIELD_DEFAULT,    // ITEM1_CAT_CARPET
        mTG_TYPE_FIELD_DEFAULT,    // ITEM1_CAT_WALL
        mTG_TYPE_FIELD_DEFAULT,    // ITEM1_CAT_FRUIT
        mTG_TYPE_FIELD_PLANT,      // ITEM1_CAT_PLANT
        mTG_TYPE_FIELD_DEFAULT,    // ITEM1_CAT_MINIDISK
        mTG_TYPE_FIELD_DEFAULT,    // ITEM1_CAT_DUMMY
        mTG_TYPE_FIELD_TICKET,     // ITEM1_CAT_TICKET
        mTG_TYPE_FIELD_RELEASE,    // ITEM1_CAT_INSECT
        mTG_TYPE_FIELD_HUKUBUKURO, // ITEM1_CAT_HUKUBUKURO
        mTG_TYPE_FIELD_DEFAULT,    // ITEM1_CAT_KABU
    };
    static int tag_type_my_room[] = {
        mTG_TYPE_ROOM_LETTER,  // ITEM1_CAT_PAPER
        mTG_TYPE_ROOM_DEFAULT, // ITEM1_CAT_MONEY
        mTG_TYPE_ROOM_DEFAULT, // ITEM1_CAT_TOOL
        mTG_TYPE_ROOM_DEFAULT, // ITEM1_CAT_FISH
        mTG_TYPE_ROOM_DEFAULT, // ITEM1_CAT_CLOTH
        mTG_TYPE_ROOM_DEFAULT, // ITEM1_CAT_ETC
        mTG_TYPE_ROOM_CARPET,  // ITEM1_CAT_CARPET
        mTG_TYPE_ROOM_WALL,    // ITEM1_CAT_WALL
        mTG_TYPE_ROOM_DEFAULT, // ITEM1_CAT_FRUIT
        mTG_TYPE_ROOM_DEFAULT, // ITEM1_CAT_PLANT
        mTG_TYPE_ROOM_DEFAULT, // ITEM1_CAT_MINIDISK
        mTG_TYPE_ROOM_DEFAULT, // ITEM1_CAT_DUMMY
        mTG_TYPE_ROOM_TICKET,  // ITEM1_CAT_TICKET
        mTG_TYPE_ROOM_DEFAULT, // ITEM1_CAT_INSECT
        mTG_TYPE_ROOM_DEFAULT, // ITEM1_CAT_HUKUBUKURO
        mTG_TYPE_ROOM_DEFAULT, // ITEM1_CAT_KABU
    };
    static int tag_type_other_room[] = {
        mTG_TYPE_OTHER_LETTER,     // ITEM1_CAT_PAPER
        mTG_TYPE_CATCH_ITEM,       // ITEM1_CAT_MONEY
        mTG_TYPE_CATCH_ITEM,       // ITEM1_CAT_TOOL
        mTG_TYPE_CATCH_ITEM,       // ITEM1_CAT_FISH
        mTG_TYPE_CATCH_ITEM,       // ITEM1_CAT_CLOTH
        mTG_TYPE_CATCH_ITEM,       // ITEM1_CAT_ETC
        mTG_TYPE_CATCH_ITEM,       // ITEM1_CAT_CARPET
        mTG_TYPE_CATCH_ITEM,       // ITEM1_CAT_WALL
        mTG_TYPE_CATCH_ITEM,       // ITEM1_CAT_FRUIT
        mTG_TYPE_CATCH_ITEM,       // ITEM1_CAT_PLANT
        mTG_TYPE_CATCH_ITEM,       // ITEM1_CAT_MINIDISK
        mTG_TYPE_CATCH_ITEM,       // ITEM1_CAT_DUMMY
        mTG_TYPE_CATCH_TICKET,     // ITEM1_CAT_TICKET
        mTG_TYPE_CATCH_ITEM,       // ITEM1_CAT_INSECT
        mTG_TYPE_OTHER_HUKUBUKURO, // ITEM1_CAT_HUKUBUKURO
        mTG_TYPE_CATCH_ITEM,       // ITEM1_CAT_KABU
    };
    static int* tag_type[] = {
        tag_type_field,
        tag_type_my_room,
        tag_type_other_room,
        tag_type_other_room,
    };
    static int tag_type_wisp_many[] = {
        mTG_TYPE_FIELD_RELEASE,
        mTG_TYPE_CATCH_ITEM,
        mTG_TYPE_CATCH_ITEM,
        mTG_TYPE_CATCH_ITEM,
    };
    static int tag_type_wisp_one[] = {
        mTG_TYPE_FIELD_RELEASE,
        mTG_TYPE_CATCH_ITEM,
        mTG_TYPE_CATCH_ITEM,
        mTG_TYPE_CATCH_ITEM,
    };
    static int tag_type_letters[] = {
        mTG_TYPE_FIELD_LETTERS,
        mTG_TYPE_ROOM_LETTERS,
        mTG_TYPE_OTHER_LETTERS,
        mTG_TYPE_OTHER_LETTERS,
    };

    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    u32 item_cond = mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, idx);
    int type = ITEM_NAME_GET_TYPE(item);
    int category = ITEM_NAME_GET_CAT(item);
    int ret_tag_type;

    if (inv_ovl->item_mark_bitfield != 0 && (inv_ovl->item_mark_bitfield & (1 << idx)) != 0) {
        ret_tag_type = mTG_TYPE_TAG_PUT_ALL;
    } else if ((item_cond & mPr_ITEM_COND_PRESENT) != 0) {
        ret_tag_type = mTG_TYPE_PRESENT_ITEM;
    } else if ((item_cond & mPr_ITEM_COND_QUEST) != 0) {
        ret_tag_type = mTG_TYPE_CATCH_ITEM;
    } else if (item == ITM_SIGNBOARD && Common_Get(field_type) == mFI_FIELDTYPE2_FG) {
        ret_tag_type = mTG_TYPE_FIELD_SIGN;
    } else if (ITEM_IS_EXERCISE_CARD(item) || item == ITM_KNIFE_AND_FORK) {
        ret_tag_type = mTG_TYPE_TAISOU_CARD;
    } else if (type == NAME_TYPE_FTR0 || type == NAME_TYPE_FTR1) {
        ret_tag_type = tag_type[Common_Get(field_type)][ITEM1_CAT_CLOTH];
    } else if (ITEM_IS_WISP(item)) {
        int wisp_cnt = ITEM_IS_WISP(item) ? (1 + (item - ITM_SPIRIT0)) : 0;

        if (wisp_cnt > 1) {
            ret_tag_type = tag_type_wisp_many[Common_Get(field_type)];
        } else {
            ret_tag_type = tag_type_wisp_one[Common_Get(field_type)];
        }
    } else if (ITEM_IS_PAPER(item)) {
        int paper_idx = item - ITM_PAPER_START;
        int paper_stack = PAPER2STACK(paper_idx);

        if (paper_stack == 0) {
            ret_tag_type = tag_type[Common_Get(field_type)][ITEM1_CAT_PAPER];
            category = ITEM1_CAT_PAPER; // @cleanup - why are we doing this?
        } else {
            ret_tag_type = tag_type_letters[Common_Get(field_type)];
        }
    } else if (ITEM_IS_BALLOON(item)) {
        if (Common_Get(field_type) == mFI_FIELDTYPE2_FG) {
            ret_tag_type = mTG_TYPE_FIELD_BALLOON;
        } else if (Common_Get(field_type) == mFI_FIELDTYPE2_PLAYER_ROOM) {
            ret_tag_type = mTG_TYPE_ROOM_DEFAULT;
        } else {
            ret_tag_type = mTG_TYPE_CATCH_ITEM;
        }
    } else {
        if (category == ITEM1_CAT_TICKET && (item & 7) == 0) {
            category = ITEM1_CAT_ETC;
        }

        ret_tag_type = tag_type[Common_Get(field_type)][category];

        /* Don't allow wallpaper & carpet options in the player basement */
        if (Common_Get(field_type) == mFI_FIELDTYPE2_PLAYER_ROOM) {
            if (mSc_IS_SCENE_BASEMENT(Save_Get(scene_no)) &&
            /* @BUG - developers missed a | for || here */
#ifndef BUGFIXES
                (category == ITEM1_CAT_CARPET | category == ITEM1_CAT_WALL)) {
#else
                (category == ITEM1_CAT_CARPET || category == ITEM1_CAT_WALL)) {
#endif
                ret_tag_type = mTG_TYPE_ROOM_DEFAULT;
            }
        }
    }

    if (inv_ovl != NULL) {
        if (type == NAME_TYPE_ITEM1 && category == ITEM1_CAT_FISH && inv_ovl->release_flag == TRUE) {
            ret_tag_type = mTG_TYPE_FIELD_RELEASE;
        } else if ((ITEM_IS_SCOOP(Now_Private->equipment) || ITEM_IS_GOLD_SCOOP(Now_Private->equipment)) &&
                   inv_ovl->shovel_flag == TRUE && item != ITM_SIGNBOARD &&
                   (type != NAME_TYPE_ITEM1 || category != ITEM1_CAT_INSECT)) {
            if (ret_tag_type == mTG_TYPE_FIELD_DEFAULT) {
                ret_tag_type = mTG_TYPE_FIELD_DEFAULT_BURY;
            } else if (ret_tag_type == mTG_TYPE_FIELD_LETTER) {
                ret_tag_type = mTG_TYPE_FIELD_LETTER_BURY;
            } else if (ret_tag_type == mTG_TYPE_FIELD_LETTERS) {
                ret_tag_type = mTG_TYPE_FIELD_LETTERS_BURY;
            } else if (ret_tag_type == mTG_TYPE_FIELD_HUKUBUKURO) {
                ret_tag_type = mTG_TYPE_FIELD_HUKUBUKURO_BURY;
            } else if (ret_tag_type == mTG_TYPE_FIELD_TICKET) {
                ret_tag_type = mTG_TYPE_FIELD_TICKET_BURY;
            }
        }
    }

    if (mEv_CheckFirstJob()) {
        if (ret_tag_type == mTG_TYPE_FIELD_PLANT) {
            ret_tag_type = mTG_TYPE_FIELD_PLANT_JOB;
        }
    }

    return ret_tag_type;
}

static int mTG_select_tag_decide_item(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    int idx = mTG_get_table_idx(tag);
    mActor_name_t item = Now_Private->inventory.pockets[idx];
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    int ret_tag_type = mTG_TYPE_NONE;

    if (item != EMPTY_NO) {
        if (menu_info->menu_type == mSM_OVL_INVENTORY) {
            switch (menu_info->data0) {
                case mSM_IV_OPEN_NORMAL:
                    return mTG_select_tag_decide_item_normal(submenu, item, idx);
                case mSM_IV_OPEN_SELL:
                    if (inv_ovl->item_mark_bitfield != 0 && (inv_ovl->item_mark_bitfield & (1 << idx)) != 0) {
                        ret_tag_type = mTG_TYPE_SELL_ALL_ITEM;
                    } else {
                        ret_tag_type = mTG_TYPE_SELL_ITEM;
                    }
                    break;
                case mSM_IV_OPEN_GIVE:
                    ret_tag_type = mTG_TYPE_GIVE_ITEM;
                    break;
                case mSM_IV_OPEN_TAKE:
                    ret_tag_type = mTG_TYPE_QUEST_ITEM;
                    break;
                case mSM_IV_OPEN_SHRINE:
                    ret_tag_type = mTG_TYPE_SHRINE_ITEM;
                    break;
                case mSM_IV_OPEN_PUTIN_FTR:
                case mSM_IV_OPEN_MINIDISK:
                    ret_tag_type = mTG_TYPE_PUTIN_ITEM;
                    break;
                case mSM_IV_OPEN_CURATOR:
                    ret_tag_type = mTG_TYPE_TAG_HAND_OVER_CURATOR;
                    break;
                case mSM_IV_OPEN_PASSWORD:
                    ret_tag_type = mTG_TYPE_TAG_PASSWORD_ITEM;
                    break;
                default:
                    break;
            }
        } else {
            ret_tag_type = mTG_TYPE_CATCH_ITEM;
        }
    }

    return ret_tag_type;
}

static int mTG_select_tag_decide_mail(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    static int mail_next_type[] = {
        mTG_TYPE_DEF_SMAIL,
        mTG_TYPE_DEF_SMAIL_PRE,
        mTG_TYPE_DEF_RMAIL,
        mTG_TYPE_DEF_RMAIL_PRE,
    };
    Mail_c* mail = mTG_get_mail_pointer(submenu, NULL);
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    int ret_tag_type = mTG_TYPE_NONE;

    if (tag->table == mTG_TABLE_MAIL && inv_ovl->mail_mark_bitfield2 != 0) {
        int idx = mTG_get_table_idx(&submenu->overlay->tag_ovl->tags[0]);

        if ((inv_ovl->mail_mark_bitfield2 & (1 << idx)) != 0) {
            switch (menu_info->menu_type) {
                case mSM_OVL_MAILBOX:
                    ret_tag_type = mTG_TYPE_FIELD_MAIL_MARK;
                    break;
                case mSM_OVL_CPMAIL:
                    ret_tag_type = mTG_TYPE_CPACK_MAIL_MARK;
                    break;
                default:
                    ret_tag_type = mTG_TYPE_FIELD_MAIL_MARK;
                    break;
            }
        }
    }

    if (menu_info->menu_type == mSM_OVL_MAILBOX && tag->table == mTG_TABLE_MBOX) {
        mMB_Ovl_c* mailbox_ovl = submenu->overlay->mailbox_ovl;

        if (mailbox_ovl != NULL) {
            int idx = mTG_get_table_idx(&submenu->overlay->tag_ovl->tags[0]);

            if ((mailbox_ovl->mark_bitfield & (1 << idx)) != 0) {
                ret_tag_type = mTG_TYPE_FIELD_MAIL_MARK2;
            }
        }
    }

    if (menu_info->menu_type == mSM_OVL_CPMAIL && tag->table == mTG_TABLE_CPMAIL) {
        mCM_Ovl_c* cpmail_ovl = submenu->overlay->cpmail_ovl;

        if (cpmail_ovl != NULL) {
            int idx = mTG_get_table_idx(&submenu->overlay->tag_ovl->tags[0]);

            if ((cpmail_ovl->mark_bitfield & (1 << idx)) != 0) {
                ret_tag_type = mTG_TYPE_CPACK_MAIL_MARK;
            }
        }
    }

    if (ret_tag_type != mTG_TYPE_NONE) {
        return ret_tag_type;
    }

    if (mMl_check_not_used_mail(mail) != TRUE) {
        if (menu_info->menu_type == mSM_OVL_CPMAIL) {
            if (mail->content.font == mMl_FONT_RECV_PLAYER_PRESENT || mail->content.font == mMl_FONT_RECV) {
                return mTG_TYPE_ROOM_RMAIL;
            } else {
                return mTG_TYPE_DEF_RMAIL;
            }
        }

        if (menu_info->menu_type == mSM_OVL_MAILBOX) {
            if (mail->content.font == mMl_FONT_RECV_PLAYER_PRESENT || mail->content.font == mMl_FONT_RECV ||
                mail->present != EMPTY_NO) {
                return mTG_TYPE_ROOM_RMAIL;
            } else {
                return mTG_TYPE_DEF_RMAIL;
            }
        }

        /* mSM_OVL_INVENTORY */
        if (menu_info->data0 == mSM_IV_OPEN_SEND_MAIL) {
            if (mMl_check_send_mail(mail)) {
                return mTG_TYPE_SEND_MAIL;
            }
        } else {
            int mail_flags = 0;
            int ret;

            if (mail->present != EMPTY_NO) {
                mail_flags |= mTG_MAIL_FLAG_PRESENT;
            }

            if (!mMl_check_send_mail(mail)) {
                mail_flags |= mTG_MAIL_FLAG_RECV;
            }

            ret = mail_next_type[mail_flags];
            if (Common_Get(field_type) != mFI_FIELDTYPE2_FG || mail->content.font == mMl_FONT_RECV_PLAYER_PRESENT ||
                mail->content.font == mMl_FONT_RECV) {
                if (ret == mTG_TYPE_DEF_SMAIL) {
                    ret = mTG_TYPE_ROOM_SMAIL;
                } else if (ret == mTG_TYPE_DEF_RMAIL) {
                    ret = mTG_TYPE_ROOM_RMAIL;
                }
            }

            return ret;
        }
    }

    return mTG_TYPE_NONE;
}

static int mTG_select_tag_decide_money(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    int ret_tag_type = mTG_TYPE_MONEY_SACK;
    u32 money = Now_Private->inventory.wallet;
    mTG_tag_data_c* tag_data_p = &mTG_label_table[mTG_TYPE_MONEY_SACK];

    if (money >= 30000) {
        tag_data_p->words = mTG_money_sack4;
        tag_data_p->lines = ARRAY_COUNT(mTG_money_sack4);
    } else if (money >= 10000) {
        tag_data_p->words = mTG_money_sack3;
        tag_data_p->lines = ARRAY_COUNT(mTG_money_sack3);
    } else if (money >= 1000) {
        tag_data_p->words = mTG_money_sack2;
        tag_data_p->lines = ARRAY_COUNT(mTG_money_sack2);
    } else if (money >= 100) {
        tag_data_p->words = mTG_money_sack1;
        tag_data_p->lines = ARRAY_COUNT(mTG_money_sack1);
    } else {
        ret_tag_type = mTG_TYPE_NONE;
    }

    return ret_tag_type;
}

static int mTG_select_tag_decide_player(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    mActor_name_t item = Now_Private->equipment;
    int ret_tag_type = mTG_TYPE_NONE;

    if (item != EMPTY_NO) {
        if (ITEM_IS_MYUMBRELLA_TOOL(item)) {
            ret_tag_type = mTG_TYPE_TAG_REMOVE;
        } else {
            ret_tag_type = mTG_TYPE_CATCH_ITEM;
        }
    }

    return ret_tag_type;
}

static int mTG_select_tag_decide_bg(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    return mTG_TYPE_NONE;
}

static int mTG_select_tag_decide_haniwa(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    mActor_name_t item = Save_Get(homes[menu_info->data1]).haniwa.items[tag->tag_col].item;
    int ret_tag_type = mTG_TYPE_NONE;

    if (item != EMPTY_NO) {
        if (menu_info->data0 == 0) {
            ret_tag_type = mTG_TYPE_HANIWA_ITEM;
        } else if (Save_Get(homes[menu_info->data1]).haniwa.items[tag->tag_col].exchange_type != mHm_HANIWA_TRADE_1) {
            ret_tag_type = mTG_TYPE_HANIWA_GET_ITEM;
        }
    }

    return ret_tag_type;
}

static int mTG_select_tag_decide_collect(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    submenu->overlay->tag_ovl->item_name_wait_time = 0;
    return mTG_TYPE_NONE;
}

static int mTG_select_tag_decide_wchange(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;

    if (inv_ovl->page_order[0] != tag->tag_row) {
        mTG_mark_main_CLR(submenu, menu_info);
        inv_ovl->next_page_id = tag->tag_row;
        inv_ovl->page_move_timer = 40;
        submenu->overlay->hand_ovl->nop_hand_func(submenu);
        sAdo_SysTrgStart(NA_SE_41C);
    }

    return mTG_TYPE_NONE;
}

static int mTG_select_tag_decide_cpmail_wchange(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    mCM_Ovl_c* cpmail_ovl = submenu->overlay->cpmail_ovl;

    if (cpmail_ovl->page_order[0] != tag->tag_row) {
        cpmail_ovl->next_page_id = tag->tag_row;
        cpmail_ovl->page_move_timer = 40;
        submenu->overlay->hand_ovl->nop_hand_func(submenu);
        sAdo_SysTrgStart(NA_SE_41C);
        cpmail_ovl->mark_bitfield = 0;
    }

    return mTG_TYPE_NONE;
}

static int mTG_select_tag_decide_cpmail_title(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    mCM_Ovl_c* cpmail_ovl = submenu->overlay->cpmail_ovl;

    mSM_open_submenu_new2(submenu, mSM_OVL_EDITOR, mED_TYPE_CP_TITLE, mCD_KEEP_MAIL_FOLDER_NAME_LEN,
                          &cpmail_ovl->card_mail->folder_names[cpmail_ovl->page_order[0]], mCM_FOLDER_NAME_MAX_WIDTH);
    menu_info->proc_status = mSM_OVL_PROC_WAIT;
    submenu->overlay->hand_ovl->nop_hand_func(submenu);

    return mTG_TYPE_NONE;
}

static int mTG_select_tag_decide_catalog(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    mCL_Ovl_c* catalog_ovl = submenu->overlay->catalog_ovl;
    mCL_Menu_c* catalog_menu = &catalog_ovl->menu_data[catalog_ovl->page_order[0]];
    int idx = catalog_menu->top_idx + tag->tag_row;
    int ret_tag_type = mTG_TYPE_NONE;

    if (catalog_menu->item_list[idx] != EMPTY_NO) {
        ret_tag_type = mTG_TYPE_ORDER_ITEM;
    }

    return ret_tag_type;
}

static int mTG_select_tag_decide_catalog_wchange(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    mCL_Ovl_c* catalog_ovl = submenu->overlay->catalog_ovl;

    if (catalog_ovl->page_order[0] != tag->tag_row) {
        mCL_Menu_c* catalog_menu;

        catalog_ovl->page_no = tag->tag_row;
        catalog_ovl->page_timer = 40;

        catalog_menu = &catalog_ovl->menu_data[tag->tag_row];
        catalog_menu->top_idx = 0;
        catalog_menu->y_idx = 0;
        submenu->overlay->hand_ovl->nop_hand_func(submenu);
        sAdo_SysTrgStart(NA_SE_41C);
        submenu->overlay->tag_ovl->item_name_wait_time = mTG_get_item_name_wait_time(tag);
    }

    return mTG_TYPE_NONE;
}

static int mTG_select_tag_decide_music_main(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    mMU_Ovl_c* music_ovl = submenu->overlay->music_ovl;
    int idx = mTG_get_table_idx(&submenu->overlay->tag_ovl->tags[0]);
    int ret_tag_type = mTG_TYPE_NONE;

    if (ChkRoomMusicBox(idx)) {
        int i;
        int n = 0;

        for (i = 0; i < MINIDISK_NUM; i++) {
            if (ChkMusicBox(music_ovl->mark_flg, i)) {
                n++;
            }
        }

        if (n >= 1 && ChkMusicBox(music_ovl->mark_flg, idx)) {
            ret_tag_type = mTG_TYPE_MUSIC_SELECT_MANY;
        } else {
            ret_tag_type = mTG_TYPE_MUSIC_SELECT;
        }
    }

    return ret_tag_type;
}

static int mTG_select_tag_decide_needlework(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    int idx = mTG_get_table_idx(&submenu->overlay->tag_ovl->tags[0]); // @cleanup - unused

    switch (menu_info->data0) {
        case 1:
            if (Common_Get(field_type) == mFI_FIELDTYPE2_PLAYER_ROOM && Save_Get(scene_no) != SCENE_COTTAGE_MY) {
                if (mSc_IS_SCENE_BASEMENT(Save_Get(scene_no))) {
                    return mTG_TYPE_TAG_NW_UG_ROOM;
                } else {
                    return mTG_TYPE_TAG_NW_MY_ROOM;
                }
            } else {
                return mTG_TYPE_TAG_NW_OT_ROOM;
            }
            break;
        case 0:
        default:
            switch (menu_info->data3) {
                case 0:
                default:
                    return mTG_TYPE_TAG_NW_SELECT;
                case 1:
                    return mTG_TYPE_TAG_NW_SELECT_CHANGE;
                case 2:
                    return mTG_TYPE_TAG_NW_SELECT_PUT;
            }
            break;
    }
}

static int mTG_select_tag_decide_inv_wc_org(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;

    mTG_mark_main_CLR(submenu, menu_info);
    inv_ovl->original_flag = FALSE;
    inv_ovl->wc_flag = TRUE;
    mSM_open_submenu_new(submenu, mSM_OVL_NEEDLEWORK, mNW_OPEN_INV, 0, NULL);
    menu_info->proc_status = mSM_OVL_PROC_WAIT;
    menu_info->next_proc_status = mSM_OVL_PROC_WAIT;
    submenu->overlay->hand_ovl->nop_hand_func(submenu);
    sAdo_SysTrgStart(NA_SE_MENU_EXIT);

    return mTG_TYPE_NONE;
}

static int mTG_select_tag_decide_cporiginal(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    mCO_Ovl_c* cporiginal_ovl = submenu->overlay->cporiginal_ovl;
    int idx = mTG_get_table_idx(&submenu->overlay->tag_ovl->tags[0]);

    if ((cporiginal_ovl->mark_flg & (1 << idx)) != 0) {
        return mTG_TYPE_CHANGE_ORIGINAL;
    } else {
        return mTG_TYPE_CATCH_ITEM;
    }
}

static int mTG_select_tag_decide_cporiginal_nw(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    mNW_Ovl_c* needlework_ovl = submenu->overlay->needlework_ovl;
    int idx = mTG_get_table_idx(&submenu->overlay->tag_ovl->tags[0]);

    if ((needlework_ovl->mark_flg & (1 << idx)) != 0) {
        return mTG_TYPE_CHANGE_ORIGINAL;
    } else {
        return mTG_TYPE_CATCH_ITEM;
    }
}

static int mTG_select_tag_decide_cporiginal_wc(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    if (tag->tag_row != mCO_top_folder(submenu)) {
        mCO_change_up_folder(submenu, tag->tag_row);
        submenu->overlay->hand_ovl->nop_hand_func(submenu);
        sAdo_SysTrgStart(NA_SE_41C);
        mCO_clear_mark_flg(submenu);
    }

    return mTG_TYPE_NONE;
}

static int mTG_select_tag_decide_cporiginal_ti(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    u8* folder_name;

    folder_name = mCO_get_folder_name(submenu, mCO_top_folder(submenu));
    mSM_open_submenu_new2(submenu, mSM_OVL_EDITOR, mED_TYPE_CP_TITLE, mCO_FOLDER_NAME_LEN, folder_name,
                          mCO_FOLDER_NAME_MAX_WIDTH);
    menu_info->proc_status = mSM_OVL_PROC_WAIT;
    return mTG_TYPE_NONE;
}

static int mTG_select_tag_decide_gba_nw(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    int ret_tag_type = mTG_TYPE_NONE;

    if (!mTG_check_hand_condition(submenu)) {
        if ((tag_ovl->nw_gba_flags & 0x4) != 0) {
            tag->arrow_dir = 0;
            tag_ovl->nw_gba_flags &= ~0x4;
            ret_tag_type = mTG_TYPE_TAG_PUT_CHK;
        } else {
            tag_ovl->nw_gba_flags |= 0x1;
        }
    } else {
        sAdo_SysTrgStart(MONO(NA_SE_A));
    }

    return ret_tag_type;
}

static void mTG_hand_drop_item(Submenu* submenu, mTG_tag_c* tag) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
    int table;
    int category;

    if (hand_ovl->info.act == mHD_ACTION_CLOSE_KEEP) {
        hand_ovl->info.next_act = mHD_ACTION_OPEN;
        mTG_init_tag_data_item_win(submenu);
        if (hand_ovl->info.ret_flag == TRUE) {
            table = hand_ovl->info.hold_tbl;
        } else {
            table = tag->table;
        }

        if (table == mTG_TABLE_PLAYER) {
            category = ITEM_NAME_GET_CAT(hand_ovl->info.item);
            switch (category) {
                case ITEM1_CAT_TOOL:
                    submenu->overlay->segment.change_player_main_anime_idx = mIV_ANIM_CATCH;
                    sAdo_SysTrgStart(NA_SE_5E);
                    break;
                case ITEM1_CAT_CLOTH:
                    submenu->overlay->segment.change_player_main_anime_idx = mIV_ANIM_CHANGE;
                    sAdo_SysTrgStart(NA_SE_WEAR);
                    break;
                case ITEM1_CAT_FRUIT:
                case ITEM1_CAT_KABU:
                    mTG_island_check_fruit_eat(hand_ovl->info.item);
                    submenu->overlay->segment.change_player_main_anime_idx = mIV_ANIM_EAT;
                    break;
            }
        } else if (table == mTG_TABLE_NEEDLEWORK) {
            mNW_clear_mark_flg(submenu);
        }
    } else if (hand_ovl->info.act == mHD_ACTION_SASU) {
        hand_ovl->info.act = mHD_ACTION_OPEN;
        hand_ovl->info.next_act = mHD_ACTION_OPEN;
    }
}

static void mTG_drop_item(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
    Mail_c* mail;
    u32 amount;
    u32 money;
    int idx;

    switch (tag->table) {
        case mTG_TABLE_MAIL:
        case mTG_TABLE_MBOX:
        case mTG_TABLE_CPMAIL:
            mail = mTG_get_mail_pointer(submenu, NULL);
            if (mMl_check_not_used_mail(&hand_ovl->info.mail) != TRUE) {
                mTG_hand_drop_item(submenu, tag);
            } else if (mMl_check_not_used_mail(mail) != TRUE && hand_ovl->info.item != EMPTY_NO) {
                if (mTG_check_item_on_mail(hand_ovl->info.item, hand_ovl->info.item_cond)) {
                    if (!mMl_check_set_present_myself(mail) && mail->present != EMPTY_NO &&
                        mPr_GetPossessionItemIdx(Now_Private, EMPTY_NO) == -1) {
                        mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PR_LEAVE);
                        mTG_init_tag_data_item_win(submenu);
                    } else if ((menu_info->menu_type == mSM_OVL_INVENTORY &&
                                menu_info->data0 == mSM_IV_OPEN_EXCHANGE) &&
                               ((hand_ovl->info.item == ITM_SIGNBOARD && mail->present != EMPTY_NO) ||
                                mail->present == ITM_SIGNBOARD)) {
                        sAdo_SysTrgStart(MONO(NA_SE_A));
                    } else {
                        mTG_hand_drop_item(submenu, tag);
                    }
                } else {
                    if (hand_ovl->info.item_cond == mPr_ITEM_COND_QUEST) {
                        mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PR_QUEST);
                    } else if (hand_ovl->info.item_cond == mPr_ITEM_COND_PRESENT) {
                        mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PRESENT_MAIL);
                    } else if (ITEM_IS_EXERCISE_CARD(hand_ovl->info.item)) {
                        mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PR_CARD);
                    } else if (hand_ovl->info.item == ITM_KNIFE_AND_FORK) {
                        mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PR_FORK);
                    } else {
                        mTG_open_warning_window(submenu, menu_info, mWR_WARNING_PR_FOOD);
                    }

                    mTG_init_tag_data_item_win(submenu);
                }
            }
            break;
        case mTG_TABLE_MONEY:
            amount = mTG_itemNo_to_amount(hand_ovl->info.item);
            money = Now_Private->inventory.wallet;

            if (money + amount <= mPr_WALLET_MAX) {
                hand_ovl->info.next_act = mHD_ACTION_OPEN;
            } else {
                mTG_open_warning_window(submenu, menu_info, mWR_WARNING_MONEY);
            }
            break;
        case mTG_TABLE_GBA:
        case mTG_TABLE_CARD:
            idx = mTG_get_table_idx(tag);
            if (idx != hand_ovl->info.hold_idx) {
                sAdo_SysTrgStart(MONO(NA_SE_A));
            } else {
                mTG_hand_drop_item(submenu, tag);
            }
            break;
        default:
            mTG_hand_drop_item(submenu, tag);
            break;
    }
}

static void mTG_drop_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[tag_ovl->sel_tag_idx];

    mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_CLOSE);
    mTG_drop_item(submenu, menu_info, tag);
}

static void mTG_hand_return_item(Submenu* submenu, mTG_tag_c* tag) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
    mActor_name_t item = hand_ovl->info.item;
    mActor_name_t dst_item;
    Mail_c* mail;

    switch (hand_ovl->info.hold_tbl) {
        case mTG_TABLE_ITEM:
            dst_item = Now_Private->inventory.pockets[(u8)hand_ovl->info.hold_idx];

            if (dst_item == EMPTY_NO) {
                hand_ovl->info.ret_flag = TRUE;
            } else if (hand_ovl->info.item_cond == mPr_ITEM_COND_NORMAL &&
                       mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, hand_ovl->info.hold_idx) ==
                           mPr_ITEM_COND_NORMAL) {
                if (ITEM_NAME_GET_TYPE(item) == NAME_TYPE_ITEM1 && ITEM_NAME_GET_CAT(item) == ITEM1_CAT_TICKET &&
                    ITEM_NAME_GET_TYPE(dst_item) == NAME_TYPE_ITEM1 &&
                    ITEM_NAME_GET_CAT(dst_item) == ITEM1_CAT_TICKET && TICKET_MONTH(item) == TICKET_MONTH(dst_item) &&
                    (TICKET_COUNT(item) + TICKET_COUNT(dst_item)) <= TICKET_STACK_MAX) {
                    hand_ovl->info.ret_flag = TRUE;
                } else if (ITEM_IS_WISP(item) && ITEM_IS_WISP(dst_item) &&
                           (WISP_COUNT(dst_item) + WISP_COUNT(item)) <= WISP_STACK_MAX) {
                    hand_ovl->info.ret_flag = TRUE;
                } else if (ITEM_IS_PAPER(item) && ITEM_IS_PAPER(dst_item) &&
                           (PAPER2TYPE(item - ITM_PAPER_START) == PAPER2TYPE(dst_item - ITM_PAPER_START)) &&
                           ((1 + PAPER2STACK(dst_item - ITM_PAPER_START)) +
                            (1 + PAPER2STACK(item - ITM_PAPER_START))) <= PAPER_STACK_MAX) {
                    hand_ovl->info.ret_flag = TRUE;
                }
            }
            break;
        case mTG_TABLE_NEEDLEWORK:
        case mTG_TABLE_CPORIGINAL:
        case mTG_TABLE_CPORIGINAL_NW:
        case mTG_TABLE_GBA:
        case mTG_TABLE_GBA_NW:
        case mTG_TABLE_CARD:
        case mTG_TABLE_CARD_NW:
            hand_ovl->info.ret_flag = TRUE;
            break;
        case mTG_TABLE_MAIL:
        case mTG_TABLE_MBOX:
        case mTG_TABLE_CPMAIL:
            mail = mTG_get_mail_pointer(submenu, hand_ovl);
            if (mMl_check_not_used_mail(mail) != TRUE) {
                if (item != EMPTY_NO && mTG_check_item_on_mail(item, hand_ovl->info.item_cond)) {
                    hand_ovl->info.ret_flag = TRUE;
                }
            } else {
                if (mMl_check_not_used_mail(&hand_ovl->info.mail) != TRUE) {
                    hand_ovl->info.ret_flag = TRUE;
                }
            }
            break;
        case mTG_TABLE_MONEY:
            if (ITEM_NAME_GET_TYPE(item) == NAME_TYPE_ITEM1 && ITEM_NAME_GET_CAT(item) == ITEM1_CAT_MONEY &&
                hand_ovl->info.item_cond == mPr_ITEM_COND_NORMAL &&
                Now_Private->inventory.wallet + mTG_itemNo_to_amount(item) <= mPr_WALLET_MAX) {
                hand_ovl->info.ret_flag = TRUE;
            }
            break;
        case mTG_TABLE_PLAYER:
            if (ITEM_NAME_GET_TYPE(item) == NAME_TYPE_ITEM1 && ITEM_NAME_GET_CAT(item) == ITEM1_CAT_TOOL &&
                hand_ovl->info.item_cond == mPr_ITEM_COND_NORMAL) {
                hand_ovl->info.ret_flag = TRUE;
            }
            break;
        case mTG_TABLE_HANIWA:
            hand_ovl->info.ret_flag = TRUE;
            break;
    }

    if (hand_ovl->info.ret_flag == FALSE && item != EMPTY_NO) {
        int i;

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if (Now_Private->inventory.pockets[i] == EMPTY_NO) {
                hand_ovl->info.hold_idx = i;
                hand_ovl->info.hold_tbl = mTG_TABLE_ITEM;
                hand_ovl->info.ret_flag = TRUE;
                hand_ovl->info.catch_pg = 0;
                break;
            }
        }
    }

    if (hand_ovl->info.ret_flag == TRUE) {
        mTG_hand_drop_item(submenu, tag);
    }
}

static int mTG_check_move_proc(Submenu* submenu, mTG_tag_c* tag) {
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    int idx;
    int res = TRUE;

    if (inv_ovl != NULL) {
        switch (tag->table) {
            case mTG_TABLE_ITEM:
                idx = mTG_get_table_idx(tag);
                if (mNT_check_unknown(Now_Private->inventory.pockets[idx]) == TRUE) {
                    res = FALSE;
                } else if ((inv_ovl->selectable_item_bitfield &
                            (1 << (tag->tag_col + tag->tag_row * mIV_ITEM_COLUMNS))) == 0) {
                    res = FALSE;
                }
                break;
            case mTG_TABLE_MAIL:
                if ((inv_ovl->selectable_mail_bitfield & (1 << (tag->tag_col + tag->tag_row * mIV_MAIL_COLUMNS))) ==
                    0) {
                    res = FALSE;
                }
                break;
        }
    }

    return res;
}

static void mTG_mark_proc(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    int chk_result;
    int chk_rvs_result;

    if (mTG_check_hand_condition(submenu) && mTG_check_move_proc(submenu, tag) &&
        mTG_mark_main(submenu, menu_info, mTG_MARK_CHK, &chk_result)) {
        if (mTG_mark_main(submenu, menu_info, mTG_MARK_RVS, &chk_rvs_result)) {
            if (chk_result != chk_rvs_result) {
                if (chk_result == FALSE) {
                    if (menu_info->menu_type == mSM_OVL_INVENTORY && menu_info->data0 == mSM_IV_OPEN_NORMAL) {
                        mTG_tag_c* main_tag = &tag_ovl->tags[0];

                        /* Deselect the opposite inventory table's selected items */
                        if (main_tag->table == mTG_TABLE_ITEM) {
                            mTG_mark_mainX(submenu, menu_info, mTG_TABLE_MAIL, 0, mTG_MARK_CLR, NULL);
                        } else if (main_tag->table == mTG_TABLE_MAIL) {
                            mTG_mark_mainX(submenu, menu_info, mTG_TABLE_ITEM, 0, mTG_MARK_CLR, NULL);
                        }
                    }

                    sAdo_SysTrgStart(NA_SE_45E);
                } else {
                    sAdo_SysTrgStart(NA_SE_45F);
                }
            }
        } else {
            sAdo_SysTrgStart(MONO(NA_SE_A));
        }
    } else {
        sAdo_SysTrgStart(MONO(NA_SE_A));
    }
}

static void mTG_move_cancel(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    int move_dir;
    int sfx;

    if (menu_info->menu_type == mSM_OVL_INVENTORY && menu_info->data0 == mSM_IV_OPEN_EXCHANGE) {
        mTG_exchange_proc(submenu, menu_info);
        return;
    }

    if (mTG_check_hand_condition(submenu)) {
        switch (menu_info->menu_type) {
            case mSM_OVL_CPMAIL:
            case mSM_OVL_CPORIGINAL:
            case mSM_OVL_GBA:
                menu_info->proc_status = mSM_OVL_PROC_WAIT;
                mSM_open_submenu(submenu, mSM_OVL_EDITENDCHK, mEE_TYPE_CPACK, 0);
                sAdo_SysTrgStart(NA_SE_5F);
                return;
        }

        sfx = NA_SE_31;
        switch (menu_info->menu_type) {
            case mSM_OVL_INVENTORY:
            case mSM_OVL_CATALOG:
                move_dir = mSM_MOVE_OUT_RIGHT;
                break;
            case mSM_OVL_NEEDLEWORK:
                move_dir = mSM_MOVE_OUT_RIGHT;
                if (menu_info->data0 == mNW_OPEN_CPORIGINAL) {
                    move_dir = -1;
                }
                break;
            case mSM_OVL_MAILBOX:
                move_dir = mSM_MOVE_OUT_LEFT;
                sfx = SE_SINGLETON(NA_SE_ZOOMDOWN_SHORT);
                break;
            default:
                move_dir = mSM_MOVE_OUT_LEFT;
                break;
        }

        if (move_dir != -1) {
            submenu->overlay->move_chg_base_proc(menu_info, move_dir);
        }

        if (sfx >= 0) {
            sAdo_SysTrgStart(sfx);
        }
    } else {
        mTG_hand_return_item(submenu, tag);
    }
}

typedef int (*mTG_DECIDE_PROC)(Submenu*, mSM_MenuInfo_c*, mTG_tag_c*);

static void mTG_move_decide(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    static mTG_DECIDE_PROC decide_proc[] = {
        &mTG_select_tag_decide_item,
        &mTG_select_tag_decide_mail,
        &mTG_select_tag_decide_money,
        &mTG_select_tag_decide_player,
        &mTG_select_tag_decide_bg,
        &mTG_select_tag_decide_mail,
        &mTG_select_tag_decide_haniwa,
        &mTG_select_tag_decide_collect,
        &mTG_select_tag_decide_wchange,
        &mTG_select_tag_decide_mail,
        &mTG_select_tag_decide_cpmail_wchange,
        &mTG_select_tag_decide_cpmail_title,
        (mTG_DECIDE_PROC)NULL,
        (mTG_DECIDE_PROC)NULL,
        &mTG_select_tag_decide_catalog,
        &mTG_select_tag_decide_catalog_wchange,
        &mTG_select_tag_decide_music_main,
        &mTG_select_tag_decide_needlework,
        &mTG_select_tag_decide_cporiginal,
        &mTG_select_tag_decide_inv_wc_org,
        &mTG_select_tag_decide_cporiginal_nw,
        &mTG_select_tag_decide_cporiginal_wc,
        &mTG_select_tag_decide_cporiginal_ti,
        &mTG_select_tag_decide_cporiginal_nw,
        &mTG_select_tag_decide_gba_nw,
        &mTG_select_tag_decide_cporiginal_nw,
        &mTG_select_tag_decide_gba_nw,
    };

    if (!mTG_check_move_proc(submenu, tag)) {
        sAdo_SysTrgStart(MONO(NA_SE_A));
        return;
    }

    if (mTG_check_hand_condition(submenu) == TRUE || tag->table == mTG_TABLE_CPMAIL_WC ||
        tag->table == mTG_TABLE_CPORIGINAL_WC || tag->table == mTG_TABLE_CARD_NW || tag->table == mTG_TABLE_GBA_NW) {
        int tag_type = (*decide_proc[tag->table])(submenu, menu_info, tag);

        if (menu_info->menu_type == mSM_OVL_INVENTORY && tag_type != mTG_TYPE_NONE) {
            mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;

            switch (tag->table) {
                case mTG_TABLE_ITEM:
                    if ((inv_ovl->item_mark_bitfield & (1 << mTG_get_table_idx(tag))) == 0) {
                        inv_ovl->item_mark_bitfield = 0;
                    }
                    inv_ovl->mail_mark_bitfield2 = 0;
                    break;
                case mTG_TABLE_MAIL:
                    if ((inv_ovl->mail_mark_bitfield2 & (1 << mTG_get_table_idx(tag))) == 0) {
                        inv_ovl->mail_mark_bitfield2 = 0;
                    }
                    inv_ovl->item_mark_bitfield = 0;
                    break;
                default:
                    inv_ovl->item_mark_bitfield = 0;
                    inv_ovl->mail_mark_bitfield2 = 0;
                    break;
            }
        }

        if (tag_type != mTG_TYPE_NONE) {
            submenu->overlay->tag_ovl->item_name_wait_time = 0;
            mTG_chg_tag_func(submenu, tag->table, tag_type, 0, tag->base_pos[0], tag->base_pos[1]);
            sAdo_SysTrgStart(NA_SE_32);
        }
    } else {
        mTG_drop_item(submenu, menu_info, tag);
    }
}

static void mTG_move_catch(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    if (
        // clang-format off
        (menu_info->menu_type == mSM_OVL_INVENTORY && (menu_info->data0 == mSM_IV_OPEN_NORMAL || menu_info->data0 == mSM_IV_OPEN_EXCHANGE)) ||
        (menu_info->menu_type == mSM_OVL_HANIWA && (menu_info->data0 == 0)) ||
        (menu_info->menu_type == mSM_OVL_CPMAIL && (tag->table != mTG_TABLE_CPMAIL_WC)) ||
        (menu_info->menu_type == mSM_OVL_MAILBOX) ||
        (menu_info->menu_type == mSM_OVL_NEEDLEWORK && (menu_info->data0 != mNW_OPEN_DESIGN)) ||
        (menu_info->menu_type == mSM_OVL_CPORIGINAL && (tag->table == mTG_TABLE_CPORIGINAL_NW || tag->table == mTG_TABLE_CPORIGINAL)) ||
        (menu_info->menu_type == mSM_OVL_GBA && (tag->table == mTG_TABLE_GBA || tag->table == mTG_TABLE_CARD))
        // clang-format on
    ) {
        if (mTG_check_move_proc(submenu, tag)) {
            if (mTG_check_hand_condition(submenu) == TRUE) {
                mTG_catch_proc(submenu, menu_info);
            } else {
                mTG_drop_item(submenu, menu_info, tag);
            }
        } else {
            sAdo_SysTrgStart(MONO(NA_SE_A));
        }
    }
}

static void mTG_move_change(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    int row;

    if (menu_info->menu_type == mSM_OVL_INVENTORY && menu_info->data0 == mSM_IV_OPEN_NORMAL &&
        mTG_check_hand_condition(submenu) == TRUE) {
        mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
        int idx_y;

        if (inv_ovl->page_order[0] == mIV_PAGE_INVENTORY) {
            idx_y = 0;
        } else if (inv_ovl->page_order[0] == mIV_PAGE_FISH_COLLECTION) {
            idx_y = 2;
        } else {
            idx_y = 1;
        }

        mTG_init_tag_data(submenu, mTG_TABLE_WCHANGE, mTG_TYPE_NONE, 0.0f, 0.0f, 0, idx_y);
        mTG_select_tag_decide_wchange(submenu, menu_info, tag);
    } else if (menu_info->menu_type == mSM_OVL_CATALOG && mTG_check_hand_condition(submenu) == TRUE) {
        tag->tag_row = (submenu->overlay->catalog_ovl->page_order[0] + 1) % mCL_MENU_NUM;
        mTG_select_tag_decide_catalog_wchange(submenu, menu_info, tag);
        mTG_init_tag_data(submenu, mTG_TABLE_CATALOG, mTG_TYPE_NONE, 0.0f, 0.0f, 0, 0);
    } else if (menu_info->menu_type == mSM_OVL_CPMAIL) {
        row = tag->tag_row;
        tag->tag_row = (submenu->overlay->cpmail_ovl->page_order[0] + 1) % mCD_KEEP_MAIL_PAGE_COUNT;
        mTG_select_tag_decide_cpmail_wchange(submenu, menu_info, tag);
        tag->tag_row = row;
    } else if (menu_info->menu_type == mSM_OVL_CPORIGINAL) {
        row = tag->tag_row;
        tag->tag_row = (mCO_top_folder(submenu) + 1) % mCO_PAGE_NUM;
        mTG_select_tag_decide_cporiginal_wc(submenu, menu_info, tag);
        tag->tag_row = row;
    }
}

static void mTG_move_move(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;

    if (hand_ovl->info.act == mHD_ACTION_CLOSE_KEEP || hand_ovl->info.act == mHD_ACTION_SASU) {
        if (mTG_move_cursol_base(submenu, tag, menu_info)) {
            mTG_init_tag_data_item_win(submenu);
            sAdo_SysTrgStart(NA_SE_CURSOL);
        }
    }
}

static void mTG_move_base(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    u32 trigger = submenu->overlay->menu_control.trigger;

    if (trigger & (BUTTON_B | BUTTON_START | BUTTON_Y)) {
        mTG_move_cancel(submenu, menu_info, tag);
    } else if (trigger & BUTTON_A) {
        mTG_move_decide(submenu, menu_info, tag);
    } else if (trigger & BUTTON_L) {
        mTG_move_catch(submenu, menu_info, tag);
    } else if (trigger & BUTTON_R) {
        mTG_move_change(submenu, menu_info, tag);
    } else if (trigger & BUTTON_X) {
        mTG_mark_proc(submenu, menu_info, tag);
    } else {
        mTG_move_move(submenu, menu_info, tag);
    }
}

static void mTG_move_base_mailbox(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    mMB_Ovl_c* mailbox_ovl = submenu->overlay->mailbox_ovl;

    if (mailbox_ovl->mark_flag == 2) {
        mTG_check_trans_mail_mark(submenu, menu_info, tag);
        mailbox_ovl->display_flag = TRUE;
    } else if (mailbox_ovl->open_flag == TRUE && mTG_check_trans_mail(submenu, menu_info, tag)) {
        mailbox_ovl->display_flag = TRUE;
    } else {
        mTG_move_base(submenu, menu_info, tag);
        mailbox_ovl->display_flag = FALSE;
    }
}

static void mTG_move_cpmail(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    mCM_Ovl_c* cmpmail_ovl = submenu->overlay->cpmail_ovl;

    if (cmpmail_ovl->mark_flag == 2) {
        mTG_cpack_change_mail_mark(submenu, menu_info, tag);
    } else {
        mTG_move_base(submenu, menu_info, tag);
    }
}

static void mTG_change_original_mark_move(Submenu* submenu, mNW_Ovl_c* nw_ovl, mCO_Ovl_c* co_ovl, int mark_idx) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_cporiginal_mark_c* mark_p = &tag_ovl->original_mark.mark[mark_idx];
    int i;

    add_calc(&tag_ovl->original_mark.move_percent, 1.0f, 1.0f - sqrtf(0.5f), 0.175f, 0.005f);
    if (tag_ovl->original_mark.move_percent >= 0.99f) {
        for (i = 0; i < 2; i++) {
            mTG_cporiginal_mark_entry_c* entry_p = &tag_ovl->original_entries[i];

            entry_p->pos[0] = mark_p->_10[i][0];
            entry_p->pos[1] = mark_p->_10[i][1];
            entry_p->item = EMPTY_NO;
        }

        mCO_swap_image(submenu, RSV_NW_ORIGINAL0 + mark_p->idx[mTG_ORG_TYPE_NW],
                       RSV_CPORIGINAL_FLD0_00 + mCO_top_folder(submenu) * mCO_ORIGINAL_NUM +
                           mark_p->idx[mTG_ORG_TYPE_CO]);
        mCO_clear_hide_flg(submenu);
        mNW_clear_hide_flg(submenu);
        tag_ovl->original_mark.mark_flg[mTG_ORG_TYPE_NW] &= ~(1 << mark_p->idx[mTG_ORG_TYPE_NW]);
        tag_ovl->original_mark.mark_flg[mTG_ORG_TYPE_CO] &= ~(1 << mark_p->idx[mTG_ORG_TYPE_CO]);
        sAdo_SysTrgStart(NA_SE_446);
        tag_ovl->original_mark.mark_mode = mTG_CHANGE_ORIGINAL_MARK_DECIDE;
    } else {
        for (i = 0; i < 2; i++) {
            mTG_cporiginal_mark_entry_c* entry_p = &tag_ovl->original_entries[i];
            f32 x0 = mark_p->_00[i][0];
            f32 x1 = mark_p->_10[i][0];
            f32 y0 = mark_p->_00[i][1];
            f32 y1 = mark_p->_10[i][1];

            entry_p->pos[0] = x0 + (x1 - x0) * tag_ovl->original_mark.move_percent;
            entry_p->pos[1] = y0 + (y1 - y0) * tag_ovl->original_mark.move_percent;
        }
    }

    mTG_init_tag_data_item_win(submenu);
}

static void mTG_change_original_mark_decide(Submenu* submenu, mNW_Ovl_c* nw_ovl, mCO_Ovl_c* co_ovl, int mark_idx) {
    static int table_no[] = { mTG_TABLE_CPORIGINAL_NW, mTG_TABLE_CPORIGINAL };
    int k;
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_mark_original_c* original_mark_p = &tag_ovl->original_mark;
    s16 idx1[mTG_ORG_TYPE_NUM];
    s16 idx0[mTG_ORG_TYPE_NUM];
    s16 mark_max;
    int i;
    int j;
    int cp_org_top = co_ovl->page_order[0];
    mTG_cporiginal_mark_entry_c* entry_p;
    mTG_cporiginal_mark_c* mark_p = &tag_ovl->original_mark.mark[mark_idx];

    for (i = 0; i < mTG_ORG_TYPE_NUM; i++) {
        idx1[i] = -1;
        mark_max = original_mark_p->mark_max[i];
        for (j = 0; j < mark_max; j++) {
            if ((original_mark_p->mark_flg[i] & (1 << j)) != 0) {
                mark_p->idx[i] = j;
                idx1[i] = j;
                idx0[1 - i] = j;
                break;
            }
        }
    }

    if (idx1[mTG_ORG_TYPE_NW] < 0 && idx1[mTG_ORG_TYPE_CO] < 0) {
        original_mark_p->mark_mode = mTG_CHANGE_ORIGINAL_MARK_NONE;
    } else {
        original_mark_p->move_percent = 0.0f;
        original_mark_p->mark_mode = mTG_CHANGE_ORIGINAL_MARK_MOVE;
        for (k = 0; k < mTG_ORG_TYPE_NUM; k++) {
            entry_p = &tag_ovl->original_entries[k];

            mTG_set_hand_pos(submenu, mark_p->_00[k], table_no[k], idx1[k]);
            mTG_set_hand_pos(submenu, mark_p->_10[k], table_no[1 - k], idx0[k]);

            switch (k) {
                case mTG_ORG_TYPE_NW:
                    entry_p->item = RSV_NW_ORIGINAL0 + idx1[k];
                    mNW_on_hide_flg(submenu, idx1[k]);
                    mNW_clear_mark_flg(submenu);
                    break;
                case mTG_ORG_TYPE_CO:
                    entry_p->item = RSV_CPORIGINAL_FLD0_00 + mCO_top_folder(submenu) * mCO_ORIGINAL_NUM + idx1[k];
                    mCO_on_hide_flg(submenu, cp_org_top, idx1[k]);
                    mCO_clear_mark_flg(submenu);
                    break;
            }

            mTG_change_original_mark_move(submenu, nw_ovl, co_ovl, mark_idx);
        }

        mTG_init_tag_data_item_win(submenu);
    }
}

static int mTG_change_cporiginal_mark_main(Submenu* submenu, mNW_Ovl_c* nw_ovl, mCO_Ovl_c* co_ovl) {
    switch (submenu->overlay->tag_ovl->original_mark.mark_mode) {
        case mTG_CHANGE_ORIGINAL_MARK_DECIDE:
            mTG_change_original_mark_decide(submenu, nw_ovl, co_ovl, 0);
            break;
        case mTG_CHANGE_ORIGINAL_MARK_MOVE:
            mTG_change_original_mark_move(submenu, nw_ovl, co_ovl, 0);
            break;
    }

    return TRUE;
}

static void mTG_change_cporiginal_mark(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    mTG_change_cporiginal_mark_main(submenu, submenu->overlay->needlework_ovl, submenu->overlay->cporiginal_ovl);
}

static void mTG_move_base_cporiginal(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    if (submenu->overlay->tag_ovl->original_mark.mark_mode != mTG_CHANGE_ORIGINAL_MARK_NONE) {
        mTG_change_cporiginal_mark(submenu, menu_info, tag);
    } else {
        mTG_move_base(submenu, menu_info, tag);
    }
}

static void mTG_move_delete(Submenu* submenu, mTG_tag_c* tag) {
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;

    inv_ovl->remove_timer--;
    if (inv_ovl->remove_timer == 0) {
        int idx = mTG_get_table_idx(tag);

        if (tag->table == mTG_TABLE_ITEM) {
            u32 cond = mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, idx);

            if ((cond & mPr_ITEM_COND_PRESENT) != 0) {
                Now_Private->inventory.item_conditions =
                    mPr_SET_ITEM_COND(Now_Private->inventory.item_conditions, (u32)idx, mPr_ITEM_COND_NORMAL);
                inv_ovl->item_scale_type[idx] = mIV_ITEM_SCALE_TYPE_NONE;
            } else {
                mActor_name_t item = Now_Private->inventory.pockets[idx];

                if (ITEM_IS_EXERCISE_CARD(item) || item == ITM_KNIFE_AND_FORK) {
                    mPr_SetPossessionItem(Now_Private, (u32)idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);
                    inv_ovl->item_scale_type[idx] = mIV_ITEM_SCALE_TYPE_NONE;
                } else {
                    u8* scale_p = inv_ovl->item_scale_type;
                    int i;

                    mPr_SetPossessionItem(Now_Private, (u32)idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);
                    for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++, scale_p++) {
                        *scale_p = mIV_ITEM_SCALE_TYPE_NONE;
                    }
                }
            }

            mTG_init_tag_data_item_win(submenu);
        } else {
            mMB_Ovl_c* mailbox_ovl;
            mCM_Ovl_c* cpmail_ovl;

            mailbox_ovl = submenu->overlay->mailbox_ovl;
            cpmail_ovl = submenu->overlay->cpmail_ovl;

            if (inv_ovl->mail_mark_flag == 0 &&
                ((mailbox_ovl != NULL && mailbox_ovl->mark_flag == 0) || mailbox_ovl == NULL) &&
                ((cpmail_ovl != NULL && cpmail_ovl->mark_flag == 0) || cpmail_ovl == NULL)) {
                mMl_clear_mail(mTG_get_mail_pointer(submenu, NULL));
            } else {
                if (inv_ovl->mail_mark_flag == 1) {
                    int i;

                    for (i = 0; i < mPr_INVENTORY_MAIL_COUNT; i++) {
                        if (mMl_check_not_used_mail(&Now_Private->mail[i]) != TRUE &&
                            (inv_ovl->mail_mark_bitfield2 & (1 << i)) != 0) {
                            mMl_clear_mail(&Now_Private->mail[i]);
                            inv_ovl->mail_mark_bitfield2 &= ~(1 << i);
                        }
                    }

                    inv_ovl->mail_mark_flag = 0;
                    inv_ovl->mail_mark_bitfield2 = 0;
                }

                if (mailbox_ovl != NULL) {
                    if (mailbox_ovl->mark_flag == 1) {
                        int i;

                        for (i = 0; i < mMB_MAIL_COUNT; i++) {
                            if ((mailbox_ovl->mark_bitfield & (1 << i)) != 0) {
                                mMl_clear_mail(&Common_Get(now_home)->mailbox[i]);
                            }
                        }

                        mailbox_ovl->mark_flag = 0;
                        mailbox_ovl->mark_bitfield = 0;
                    }
                }

                if (cpmail_ovl != NULL) {
                    if (cpmail_ovl->mark_flag == 1) {
                        int i;
                        int page = cpmail_ovl->page_order[0];

                        for (i = 0; i < mCD_KEEP_MAIL_COUNT; i++) {
                            if ((cpmail_ovl->mark_bitfield & (1 << i)) != 0) {
                                mMl_clear_mail(&cpmail_ovl->card_mail->mail[page][i]);
                            }
                        }

                        cpmail_ovl->mark_bitfield = 0;
                        cpmail_ovl->mark_flag = 0;
                    }
                }
            }
        }

        mTG_init_tag_data_item_win(submenu);
    }
}

static void mTG_select_tag_base(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    u32 trigger = submenu->overlay->menu_control.trigger;

    if (trigger & (BUTTON_B | BUTTON_START | BUTTON_Y)) {
        if (menu_info->menu_type == mSM_OVL_INVENTORY && menu_info->data0 == mSM_IV_OPEN_QUEST) {
            mTG_close_window(submenu, menu_info, TRUE);
        } else {
            mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
            mTG_tag_c* last_tag = &tag_ovl->tags[tag_ovl->sel_tag_idx - 1];

            mTG_return_tag_init(submenu, last_tag->type, mTG_RETURN_KEEP);
            sAdo_SysTrgStart(MONO(NA_SE_3));
        }
    } else if (trigger & (BUTTON_A)) {
        mTG_label_table[tag->type].words[tag->tag_row]->move_proc(submenu, menu_info);
    } else {
        int max = mTG_label_table[tag->type].lines - 1;

        if (trigger & (BUTTON_CDOWN | BUTTON_CUP)) {
            if (trigger & (BUTTON_CDOWN)) {
                if (tag->tag_row < max) {
                    tag->tag_row++;
                    sAdo_SysTrgStart(NA_SE_CURSOL);
                }
            } else {
                if (tag->tag_row > 0) {
                    tag->tag_row--;
                    sAdo_SysTrgStart(NA_SE_CURSOL);
                }
            }
        }
    }
}

static int mTG_normal_move(Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_Ovl_c* tag_ovl, mTG_tag_c* tag,
                           mIV_Ovl_c* inv_ovl) {
    if (menu_info->menu_type == mSM_OVL_INVENTORY && menu_info->data0 == mSM_IV_OPEN_EXCHANGE &&
        mTG_check_hand_condition(submenu)) {
        mTG_exchange_proc(submenu, menu_info);
        return TRUE;
    }

    if (tag_ovl->sel_tag_idx > tag_ovl->ret_tag_idx) {
        mTG_return_tag_func(submenu, tag_ovl, tag);
    } else if (menu_info->menu_type != submenu->current_menu_type) {
        return TRUE;
    } else if (tag->type == mTG_TYPE_NONE) {
        if (inv_ovl != NULL && inv_ovl->remove_timer > 0) {
            mTG_move_delete(submenu, tag);
        } else {
            if (tag_ovl->item_name_wait_time > 0) {
                tag_ovl->item_name_wait_time--;
            } else {
                tag->scale += 0.125f;
                if (tag->scale > 1.0f) {
                    tag->scale = 1.0f;
                }
            }

            if (menu_info->menu_type == mSM_OVL_MAILBOX) {
                mTG_move_base_mailbox(submenu, menu_info, tag);
            } else if (menu_info->menu_type == mSM_OVL_CPMAIL) {
                mTG_move_cpmail(submenu, menu_info, tag);
            } else if (menu_info->menu_type == mSM_OVL_CPORIGINAL) {
                mTG_move_base_cporiginal(submenu, menu_info, tag);
            } else {
                mTG_move_base(submenu, menu_info, tag);
            }
        }
    } else if (tag->scale >= 1.0f) {
        if (tag->type == mTG_TYPE_HANIWA_PRICE) {
            mTG_mv_priceSet(submenu, menu_info, tag);
        } else {
            mTG_select_tag_base(submenu, menu_info, tag);
        }
    } else {
        mTG_tag_c* main_tag = &tag_ovl->tags[0];

        if (tag_ovl->sel_tag_idx == 1 && main_tag->arrow_dir != 0 && main_tag->scale < 1.0f) {
            main_tag->scale += 0.125f;
            if (main_tag->scale > 1.0f) {
                main_tag->scale = 1.0f;
            }

            submenu->overlay->menu_control.hand_move_func(submenu);
            return TRUE;
        }

        if (tag_ovl->sel_tag_idx == 1 && main_tag->arrow_dir != 0) {
            tag->scale += 0.185f;
        } else {
            tag->scale += 0.125f;
        }

        if (tag->scale > 1.0f) {
            tag->scale = 1.0f;
        }
    }

    return FALSE;
}

#ifdef MOUSE_INPUT
typedef struct tag_table_mouse_data_s {
    s16* col_mouse_pos;      // X positions for mouse selection (if NULL, use default col_pos)
    s16* line_mouse_pos;     // Y positions for mouse selection (if NULL, use default row_pos)
    s16* col_mouse_hitbox;   // Half-width hitbox per column (if NULL, use default 10.0f)
    s16* line_mouse_hitbox;  // Half-height hitbox per row (if NULL, use default 10.0f)
} mTG_table_mouse_data_c;

// mTG_TABLE_MONEY
static s16 mTG_money_col_mouse_pos[] = { 0 };
static s16 mTG_money_line_mouse_pos[] = { 11 };
static s16 mTG_item_col_hitbox[] = { 20 };
static s16 mTG_item_line_hitbox[] = { 5 };

// mTG_TABLE_PLAYER
static s16 mTG_player_col_mouse_pos[] = { -78 };
static s16 mTG_player_line_mouse_pos[] = { 45 };
static s16 mTG_player_col_hitbox[] = { 22 };
static s16 mTG_player_line_hitbox[] = { 20 };

// mTG_TABLE_CPMAIL_TI
static s16 mTG_cpmail_ti_col_hitbox[] = { 58 };

// mTG_TABLE_CATALOG
static s16 mTG_catalog_col_mouse_pos[] = { 10 };
static s16 mTG_catalog_col_hitbox[] = { 55 };

// mTG_TABLE_NEEDLEWORK
static s16 mTG_needlework_col_hitbox[] = { 15, 15 };
static s16 mTG_needlework_line_hitbox[] = { 15, 15, 15, 15 };

// mTG_TABLE_CPORIGINAL_TI
static s16 mTG_cporiginal_ti_col_hitbox[] = { 58 };

// Table mouse data array
static mTG_table_mouse_data_c mTG_table_mouse_data[] = {
    { NULL, NULL, NULL, NULL }, // mTG_TABLE_ITEM (default)
    { NULL, NULL, NULL, NULL }, // mTG_TABLE_MAIL (default)
    { mTG_money_col_mouse_pos, mTG_money_line_mouse_pos, mTG_item_col_hitbox, mTG_item_line_hitbox }, // mTG_TABLE_MONEY
    { mTG_player_col_mouse_pos, mTG_player_line_mouse_pos, mTG_player_col_hitbox, mTG_player_line_hitbox }, // mTG_TABLE_PLAYER
    { NULL, NULL, NULL, NULL }, // mTG_TABLE_BG (default)
    { NULL, NULL, NULL, NULL }, // mTG_TABLE_MBOX (default)
    { NULL, NULL, NULL, NULL }, // mTG_TABLE_HANIWA (default)
    { NULL, NULL, NULL, NULL }, // mTG_TABLE_COLLECT (default)
    { NULL, NULL, NULL, NULL }, // mTG_TABLE_WCHANGE (default)
    { NULL, NULL, NULL, NULL }, // mTG_TABLE_CPMAIL (default)
    { NULL, NULL, NULL, NULL }, // mTG_TABLE_CPMAIL_WC (default)
    { NULL, NULL, mTG_cpmail_ti_col_hitbox, NULL }, // mTG_TABLE_CPMAIL_TI
    { NULL, NULL, NULL, NULL }, // mTG_TABLE_CPEDIT (stub)
    { NULL, NULL, NULL, NULL }, // mTG_TABLE_CPEDIT_END (stub)
    { mTG_catalog_col_mouse_pos, NULL, mTG_catalog_col_hitbox, NULL }, // mTG_TABLE_CATALOG
    { NULL, NULL, NULL, NULL }, // mTG_TABLE_CATALOG_WC (default)
    { NULL, NULL, NULL, NULL }, // mTG_TABLE_MUSIC_MAIN (default)
    { NULL, NULL, mTG_needlework_col_hitbox, mTG_needlework_line_hitbox }, // mTG_TABLE_NEEDLEWORK
    { NULL, NULL, NULL, NULL }, // mTG_TABLE_CPORIGINAL (default)
    { NULL, NULL, NULL, NULL }, // mTG_TABLE_INVENTORY_WC_ORG (default)
    { NULL, NULL, NULL, NULL }, // mTG_TABLE_CPORIGINAL_NW (default)
    { NULL, NULL, NULL, NULL }, // mTG_TABLE_CPORIGINAL_WC (default)
    { NULL, NULL, mTG_cporiginal_ti_col_hitbox, NULL }, // mTG_TABLE_CPORIGINAL_TI
    { NULL, NULL, NULL, NULL }, // mTG_TABLE_GBA (stub)
    { NULL, NULL, NULL, NULL }, // mTG_TABLE_GBA_NW (stub)
    { NULL, NULL, NULL, NULL }, // mTG_TABLE_CARD (stub)
    { NULL, NULL, NULL, NULL }, // mTG_TABLE_CARD_NW (stub)
};

static void mTG_get_mouse_slot_pos(Submenu* submenu, f32* pos, int table, int idx, mTG_table_mouse_data_c* mouse_data) {
    mTG_tag_data_table_c* data_p = &mTG_table_data[table];
    int col = idx % data_p->col_num;
    int row = idx / data_p->col_num;
    f32 pos_x;
    f32 pos_y;
    
    // Use mouse-specific X position if available, otherwise use default
    if (mouse_data->col_mouse_pos != NULL) {
        pos_x = mouse_data->col_mouse_pos[col];
    } else {
        pos_x = data_p->col_pos[col];
    }
    
    // Use mouse-specific Y position if available, otherwise use default
    if (mouse_data->line_mouse_pos != NULL) {
        pos_y = mouse_data->line_mouse_pos[row];
    } else {
        pos_y = data_p->row_pos[row];
    }
    
    f32 ofs = mTG_set_hand_pos_offset(submenu, table);
    pos[0] = pos_x + ofs;
    pos[1] = pos_y;
}

static void mTG_mouse_move_func(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[tag_ovl->sel_tag_idx];

    /* Setup mouse logic */
    s32 mouse_x, mouse_y;
    pc_mouse_get_native_position(&mouse_x, &mouse_y);
    f32 logical_mouse_x = mouse_x * 0.5;
    f32 logical_mouse_y = mouse_y * 0.5;

    u32 mouse_pressed = pc_mouse_button_pressed();
    s32 mouse_wheel = pc_mouse_scroll_wheel();
    s32 mouse_moved = pc_mouse_moved();

    /* Controller and mouse active checks */
    if (submenu->overlay->menu_control.trigger) {
        tag_ovl->mouse_active = 0;
    }
    if (mouse_moved || mouse_pressed || mouse_wheel != 0) {
        tag_ovl->mouse_active = 1;
    }

    tag_ovl->mouse_x = logical_mouse_x;
    tag_ovl->mouse_y = logical_mouse_y;

    if (!tag_ovl->mouse_active) {
        return;
    }

    /* Mouse scroll wheel logic */
    if (mouse_wheel != 0 && tag_ovl->sel_tag_idx == 0) {
        if (tag_ovl->hovered_table == mTG_TABLE_CATALOG) {
            mCL_Ovl_c* catalog_ovl = submenu->overlay->catalog_ovl;
            mCL_Menu_c* catalog_menu = &catalog_ovl->menu_data[catalog_ovl->page_order[0]];

            if (mouse_wheel > 0) {  // Scroll up
                if (catalog_menu->top_idx != 0) {
                    catalog_menu->top_idx--;
                    catalog_ovl->change_flag = TRUE;
                    sAdo_SysTrgStart(NA_SE_CURSOL);
                }
            } else {  // Scroll down
                if (catalog_menu->top_idx + mCL_MENU_PAGE_SIZE < catalog_menu->item_count) {
                    catalog_menu->top_idx++;
                    catalog_ovl->change_flag = TRUE;
                    sAdo_SysTrgStart(NA_SE_CURSOL);
                }
            }
        }
    }

    /* Mouse movement logic */
    if (mouse_moved) {
        if (tag_ovl->sel_tag_idx == 0) {
            f32 hand_x = (logical_mouse_x - 160.0f);
            f32 hand_y = (120.0f - logical_mouse_y);

            int hit_table = -1;
            int hit_col = -1;
            int hit_row = -1;

            int tables_to_check[7];
            int num_tables = 0;

            // Determine which tables are active based on menu type
            switch (menu_info->menu_type) {
                case mSM_OVL_INVENTORY: // Pause inventory
                    switch (menu_info->data0) {
                        case mSM_IV_OPEN_NORMAL:
                            if (submenu->overlay->inventory_ovl->page_order[0] == mIV_PAGE_INVENTORY) { // Main page inventory
                                if (mTG_move_check_hand_item(submenu, mTG_TABLE_ITEM)) { // Items
                                    tables_to_check[num_tables++] = mTG_TABLE_ITEM;
                                }
                                if (mTG_move_check_hand_item(submenu, mTG_TABLE_MAIL)) { // Letters
                                    tables_to_check[num_tables++] = mTG_TABLE_MAIL;
                                }
                                if (mTG_move_check_hand_item(submenu, mTG_TABLE_MONEY)) { // Bells
                                    tables_to_check[num_tables++] = mTG_TABLE_MONEY;
                                }
                                if (mTG_move_check_hand_item(submenu, mTG_TABLE_PLAYER)) { // Player
                                    tables_to_check[num_tables++] = mTG_TABLE_PLAYER;
                                }
                                if (mTG_move_check_hand_item(submenu, mTG_TABLE_BG)) { // Background color change
                                    tables_to_check[num_tables++] = mTG_TABLE_BG;
                                }
                                if (mTG_check_hand_condition(submenu)) { // Right labels (Fish, Inventory, Bugs)
                                    tables_to_check[num_tables++] = mTG_TABLE_WCHANGE;
                                }
                                if (mTG_check_hand_condition(submenu)) { // Left label (Pattern clothes)
                                    tables_to_check[num_tables++] = mTG_TABLE_INVENTORY_WC_ORG;
                                }
                            } else { // collection page (fish/bugs)
                                tables_to_check[num_tables++] = mTG_TABLE_COLLECT;  // Fish/Bugs
                                tables_to_check[num_tables++] = mTG_TABLE_WCHANGE;
                            }
                            break;
                        case mSM_IV_OPEN_SEND_MAIL:
                            tables_to_check[num_tables++] = mTG_TABLE_MAIL;
                            break;
                        default:
                            tables_to_check[num_tables++] = mTG_TABLE_ITEM;
                            break;
                    }
                    break;
                case mSM_OVL_HANIWA: // Gyroid storage
                    tables_to_check[num_tables++] = mTG_TABLE_HANIWA; // Gyroid top items
                    tables_to_check[num_tables++] = mTG_TABLE_ITEM;
                    break;
                case mSM_OVL_CATALOG: // Tom Nook shop catalog
                    tables_to_check[num_tables++] = mTG_TABLE_CATALOG;    // Catalog list
                    tables_to_check[num_tables++] = mTG_TABLE_CATALOG_WC; // Right label (Catalog tabs)
                    break;
                case mSM_OVL_MAILBOX: // Mailbox
                    tables_to_check[num_tables++] = mTG_TABLE_MBOX;  // Mailbox list
                    tables_to_check[num_tables++] = mTG_TABLE_MAIL;  
                    break;
                case mSM_OVL_CPMAIL: // Post office save letter
                    tables_to_check[num_tables++] = mTG_TABLE_MAIL;
                    tables_to_check[num_tables++] = mTG_TABLE_CPMAIL;    // Letters saved
                    tables_to_check[num_tables++] = mTG_TABLE_CPMAIL_TI; // Letter menu title
                    tables_to_check[num_tables++] = mTG_TABLE_CPMAIL_WC; // Right label (Letter color tag)
                    break;
                case mSM_OVL_NEEDLEWORK: // Pattern menu
                    tables_to_check[num_tables++] = mTG_TABLE_NEEDLEWORK;  // Pattern labels
                    break;
                case mSM_OVL_MUSIC: // Music box menu
                    tables_to_check[num_tables++] = mTG_TABLE_MUSIC_MAIN;  // Music box list
                    break;
                case mSM_OVL_CPORIGINAL: // Save pattern menu
                    tables_to_check[num_tables++] = mTG_TABLE_CPORIGINAL;    // Patterns saved
                    tables_to_check[num_tables++] = mTG_TABLE_CPORIGINAL_NW; // Left label (patterns created)
                    tables_to_check[num_tables++] = mTG_TABLE_CPORIGINAL_WC; // Right label (pattern color tag)
                    tables_to_check[num_tables++] = mTG_TABLE_CPORIGINAL_TI; // Pattern menu title
                    break;
                case mSM_OVL_CPEDIT:  // N64 controller pak menu
                    // This submenu is stubbed in GC, just here for convenience
                    tables_to_check[num_tables++] = mTG_TABLE_CPEDIT;
                    tables_to_check[num_tables++] = mTG_TABLE_CPEDIT_END;
                    break;
                case mSM_OVL_GBA:  // GBA menu
                    // Port doesn't support gba connectivity but again, convenience
                    switch (menu_info->data0) {
                        case 3:
                            tables_to_check[num_tables++] = mTG_TABLE_GBA;
                            tables_to_check[num_tables++] = mTG_TABLE_GBA_NW;
                            break;
                        case 4:
                            tables_to_check[num_tables++] = mTG_TABLE_CARD;
                            tables_to_check[num_tables++] = mTG_TABLE_CARD_NW;
                            break;
                    }
                    break;
                default:
                    // Just check the current table
                    tables_to_check[num_tables++] = tag->table; 
                    break;
            }

            for (int t = 0; t < num_tables; t++) {
                int table = tables_to_check[t];
                mTG_tag_data_table_c* data_p = &mTG_table_data[table];
                mTG_table_mouse_data_c* mouse_data = &mTG_table_mouse_data[table];
            
                for (int row = 0; row < data_p->row_num; row++) {
                    for (int col = 0; col < data_p->col_num; col++) {
                        f32 slot_pos[2];
                        mTG_get_mouse_slot_pos(submenu, slot_pos, table, row * data_p->col_num + col, mouse_data);
                    
                        // Get hitbox sizes, default to 10, commonly used for item cells
                        f32 x_hitbox = 10.0f;
                        f32 y_hitbox = 10.0f;
                    
                        if (mouse_data->col_mouse_hitbox != NULL) {
                            x_hitbox = mouse_data->col_mouse_hitbox[col];
                        }
                        if (mouse_data->line_mouse_hitbox != NULL) {
                            y_hitbox = mouse_data->line_mouse_hitbox[row];
                        }
                    
                        // Rectangular hitbox check
                        f32 dx = hand_x - slot_pos[0];
                        f32 dy = hand_y - slot_pos[1];
                    
                        if (fabsf(dx) <= x_hitbox && fabsf(dy) <= y_hitbox) {
                            hit_table = table;
                            hit_col = col;
                            hit_row = row;
                        }
                    }
                }
            }

            if (hit_table >= 0) {
                tag_ovl->hovered_table = hit_table;
                tag_ovl->hovered_col = hit_col;
                tag_ovl->hovered_row = hit_row;
                tag_ovl->hovered_idx = hit_row * mTG_table_data[hit_table].col_num + hit_col;
            } else {
                tag_ovl->hovered_table = -1;
                tag_ovl->hovered_col = -1;
                tag_ovl->hovered_row = -1;
                tag_ovl->hovered_idx = -1;
            }

            // Update cursor if we found a close slot and it's different from current
            if (hit_table >= 0 && (hit_table != tag->table || 
                hit_col != tag->tag_col || hit_row != tag->tag_row)) {

                // Update the main tag to the hovered position
                tag->table = hit_table;
                tag->tag_col = hit_col;
                tag->tag_row = hit_row;

                if (hit_table == mTG_TABLE_CATALOG) {
                    mCL_Ovl_c* catalog_ovl = submenu->overlay->catalog_ovl;
                    catalog_ovl->change_flag = TRUE;
                }

                // Update hand position using the mouse position
                int idx = hit_row * mTG_table_data[hit_table].col_num + hit_col;
                mTG_set_hand_pos(submenu, tag->base_pos, hit_table, idx);

                // Re-initialize the item window
                mTG_init_tag_data_item_win(submenu);
                sAdo_SysTrgStart(NA_SE_CURSOL);
            }
        } else {
            // We're in a selection submenu - handle mouse over the options
            mTG_tag_c* submenu_tag = &tag_ovl->tags[tag_ovl->sel_tag_idx];
            mTG_tag_data_c* tag_data = &mTG_label_table[submenu_tag->type];

            f32 scale = submenu_tag->scale;
            f32 scale_rate = scale * 0.875f;

            // Calculate the screen-space anchor for the text list
            f32 tag_screen_x = 160.0f + (submenu_tag->base_pos[0] + menu_info->position[0] + 
                scale * (submenu_tag->body_ofs[0] + submenu_tag->text_ofs[0]));
            f32 tag_screen_y = 120.0f - (submenu_tag->base_pos[1] + menu_info->position[1] + 
                scale * (submenu_tag->body_ofs[1] + submenu_tag->text_ofs[1]));

            int hovered_option = -1;
            f32 option_height = 16.0f * scale_rate; 

            for (int i = 0; i < tag_data->lines; i++) {
                // Set top and bottom option hitbox
                f32 option_top = tag_screen_y + (i * option_height);
                f32 option_bottom = option_top + option_height;

                // Set horizontal - adjust width based on highlighted text 
                int len = mMl_strlen(tag_data->words[i]->str, mTG_TAG_STR_LEN, CHAR_SPACE);
                f32 option_width = mFont_GetStringWidth(tag_data->words[i]->str, len, TRUE) * scale_rate;

                // Check if mouse_x/y (scaled/translated) falls within this rect
                if ((tag_ovl->mouse_x >= tag_screen_x && tag_ovl->mouse_x <= (tag_screen_x + option_width)) &&
                    (tag_ovl->mouse_y >= option_top && tag_ovl->mouse_y <= option_bottom)) {
                    hovered_option = i;
                    break;
                }
                
            }

            // Update cursor if hovering over a different option
            if (hovered_option >= 0 && hovered_option != submenu_tag->tag_row) {
                submenu_tag->tag_row = hovered_option;
                sAdo_SysTrgStart(NA_SE_CURSOL);
            }

            tag_ovl->hovered_option = hovered_option;
        }
    }

    /* Mouse click logic */
    if (tag_ovl->sel_tag_idx == 0) {
        if (tag_ovl->hovered_table >= 0) {
            if (mouse_pressed & (1 << 0)) { // Left click
                u32 old_trigger = submenu->overlay->menu_control.trigger;
                submenu->overlay->menu_control.trigger = BUTTON_A;
                mTG_move_decide(submenu, menu_info, tag);
                submenu->overlay->menu_control.trigger = old_trigger;
            }
        }

        if (mouse_pressed & (1 << 2)) { // Right click
            u32 old_trigger = submenu->overlay->menu_control.trigger;
            submenu->overlay->menu_control.trigger = BUTTON_B;
            mTG_move_cancel(submenu, menu_info, tag);
            submenu->overlay->menu_control.trigger = old_trigger;
        }
    } else {
        if (tag_ovl->hovered_option >= 0) {
            if (mouse_pressed & (1 << 0)) { // Left click
                u32 old_trigger = submenu->overlay->menu_control.trigger;
                submenu->overlay->menu_control.trigger = BUTTON_A;

                mTG_tag_c* submenu_tag = &tag_ovl->tags[tag_ovl->sel_tag_idx];
                mTG_label_table[submenu_tag->type].words[tag_ovl->hovered_option]->move_proc(submenu, menu_info);

                submenu->overlay->menu_control.trigger = old_trigger;
            }
        }

        if (mouse_pressed & (1 << 2)) { // Right click
            u32 old_trigger = submenu->overlay->menu_control.trigger;
            submenu->overlay->menu_control.trigger = BUTTON_B;

            if (menu_info->menu_type == mSM_OVL_INVENTORY && menu_info->data0 == mSM_IV_OPEN_QUEST) {
                mTG_close_window(submenu, menu_info, TRUE);
            } else {
                mTG_tag_c* last_tag = &tag_ovl->tags[tag_ovl->sel_tag_idx - 1];

                mTG_return_tag_init(submenu, last_tag->type, mTG_RETURN_KEEP);
                sAdo_SysTrgStart(MONO(NA_SE_3));
            }

            submenu->overlay->menu_control.trigger = old_trigger;
        }
    }
}
#endif

static void mTG_move_func(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    mTG_tag_c* tag = &tag_ovl->tags[tag_ovl->sel_tag_idx];
    mHD_Ovl_c* hand_ovl = submenu->overlay->hand_ovl;
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;

#ifdef MOUSE_INPUT
    mTG_mouse_move_func(submenu, menu_info);
#endif

    if (tag_ovl->sel_tag_idx < 0 || tag_ovl->sel_tag_idx >= mTG_TAG_NUM) {
        return;
    }

    if (hand_ovl->info.wait_timer > 0 && inv_ovl != NULL) {
        hand_ovl->info.wait_timer--;
        if (tag_ovl->sel_tag_idx > tag_ovl->ret_tag_idx) {
            mTG_return_tag_func(submenu, tag_ovl, tag);
        }

        if (hand_ovl->info.wait_timer == 0) {
            if (tag->table == mTG_TABLE_PLAYER) {
                if (!ITEM_IS_MYUMBRELLA_TOOL(Now_Private->equipment)) {
                    hand_ovl->info.next_act = mHD_ACTION_CLOSE;
                    hand_ovl->info.item = Now_Private->equipment;
                    hand_ovl->info.item_cond = mPr_ITEM_COND_NORMAL;
                    hand_ovl->info.hold_tbl = mTG_TABLE_PLAYER;
                    hand_ovl->info.hold_idx = 0;
                }

                Now_Private->equipment = EMPTY_NO;
                mTG_init_tag_data_item_win(submenu);
                submenu->overlay->segment.change_player_main_anime_idx = mIV_ANIM_WALK;
            } else {
                inv_ovl->disp_money = Now_Private->inventory.wallet;
                inv_ovl->disp_money_chg_step = 0;

                if (menu_info->menu_type == mSM_OVL_HANIWA) {
                    sAdo_SysTrgStart(MONO(NA_SE_REGISTER));
                }

                if (menu_info->menu_type == mSM_OVL_INVENTORY && menu_info->data0 == mSM_IV_OPEN_EXCHANGE &&
                    mTG_check_hand_condition(submenu)) {
                    mTG_exchange_proc(submenu, menu_info);
                    return;
                }

                mTG_init_tag_data_item_win(submenu);
            }
        } else if (inv_ovl->disp_money != Now_Private->inventory.wallet) {
            inv_ovl->disp_money += inv_ovl->disp_money_chg_step;
        }
    } else if (hand_ovl->info.move_flag == FALSE && hand_ovl->info.act != mHD_ACTION_CLOSE &&
               hand_ovl->info.act != mHD_ACTION_CLOSE2 && hand_ovl->info.act != mHD_ACTION_OPEN) {
        if (tag_ovl->nw_gba_flags & 0x1) {
            mTG_return_tag_init(submenu, mTG_TYPE_NONE, mTG_RETURN_KEEP);
            tag_ovl->nw_gba_flags &= ~0x1;
            tag_ovl->nw_gba_flags |= 0x2;
        } else if (tag_ovl->nw_gba_flags & 0x2) {
            if (tag_ovl->sel_tag_idx > tag_ovl->ret_tag_idx) {
                mTG_return_tag_func(submenu, tag_ovl, tag);
            } else {
                tag_ovl->nw_gba_flags &= ~0x2;
                tag_ovl->nw_gba_flags |= 0x4;
                mTG_move_decide(submenu, menu_info, tag);
            }
        } else if (submenu->overlay->segment.player_anime_timer <= 0) {
            if (mTG_normal_move(submenu, menu_info, tag_ovl, tag, inv_ovl)) {
                return;
            }
        } else if (tag->table == mTG_TABLE_NEEDLEWORK && tag_ovl->sel_tag_idx > tag_ovl->ret_tag_idx) {
            mTG_return_tag_func(submenu, tag_ovl, tag);
        }
    } else if (tag_ovl->sel_tag_idx > tag_ovl->ret_tag_idx) {
        mTG_return_tag_func(submenu, tag_ovl, tag);
    }

    submenu->overlay->menu_control.hand_move_func(submenu);
    if ((submenu->menu_type == mSM_OVL_NEEDLEWORK || submenu->menu_type == mSM_OVL_CPORIGINAL ||
         submenu->menu_type == mSM_OVL_GBA) &&
        hand_ovl->info.item != EMPTY_NO) {
        if (submenu->menu_type == mSM_OVL_GBA && (tag->table == mTG_TABLE_GBA_NW || tag->table == mTG_TABLE_CARD_NW) &&
            tag_ovl->sel_tag_idx == 1 && tag_ovl->tags[tag_ovl->sel_tag_idx].type == mTG_TYPE_TAG_PUT_CHK) {
            tag_ovl->nw_gba_flags &= ~0x8;
        } else {
            tag_ovl->nw_gba_flags |= 0x8;
        }
    } else {
        tag_ovl->nw_gba_flags &= ~0x8;
    }
}

enum {
    mTG_TAG_COLOR_NORMAL,
    mTG_TAG_COLOR_CPEDIT,
    mTG_TAG_COLOR_CATALOG,
    mTG_TAG_COLOR_MUSIC,

    mTG_TAG_COLOR_NUM
};

// clang-format off
static rgba_t mTG_select_col_type_on[] = {
    { 120,  35, 255, 255 },
    {  70,  70, 100, 255 },
    { 135,  20, 225, 255 },
    { 255, 215,  50, 255 },
};
// clang-format on

// clang-format off
static rgba_t mTG_select_col_type_off[] = {
    { 140, 150, 190, 255 },
    { 130, 130, 150, 255 },
    { 145, 135, 195, 255 },
    { 115, 110,  70, 255 },
};
// clang-format on

static int mTG_get_special_color(mSM_MenuInfo_c* menu_info, mTG_tag_c* tag) {
    int color = mTG_TAG_COLOR_NORMAL;

    if (menu_info->menu_type == mSM_OVL_CATALOG) {
        color = mTG_TAG_COLOR_CATALOG;
    } else if (menu_info->menu_type == mSM_OVL_MUSIC) {
        color = mTG_TAG_COLOR_MUSIC;
    }

    return color;
}

typedef struct {
    Gfx* frame;
    Gfx* frame_shadow;
    Gfx* left_arrow;
    Gfx* right_arrow;
} mTG_disp_data_c;

extern Gfx sen_itemw_wakuT_model[];
extern Gfx sen_itemw_kage_model[];
extern Gfx sen_itemw_yajirushi_model[];
extern Gfx sen_itemw_yajirushi2T_model[];

extern Gfx sen_qitem_wakuT_model[];
extern Gfx sen_qitem_kage_model[];
extern Gfx sen_qitem_yajirushiT_model[];
extern Gfx sen_qitem_yajirushi2T_model[];
extern Gfx sen_qitem_yajirushi3_model[];
extern Gfx sen_qitem_yajirushi4T_model[];
extern Gfx sen_qitem_yajirushi5_model[];
extern Gfx sen_qitem_yajirushi6T_model[];

extern Gfx sen_win_wakuT_model[];
extern Gfx sen_win_kageT_model[];
extern Gfx sen_win_yajirushiT_model[];
extern Gfx sen_win_yajirushi2T_model[];

extern Gfx sen_item2_DL_mode[];
extern Gfx sen_win_cursor_model[];

static void mTG_set_win_field(GRAPH* graph, Submenu* submenu, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag, f32 pos_x,
                              f32 pos_y, int win_type, int draw_no) {
    // clang-format off
    static rgba_t p_col_table[][4] = {
        {
            { 255, 245, 140, 255 },
            { 190, 235, 245, 255 },
            { 205, 245, 255, 255 },
            { 215, 255, 255, 255 },
        },
        {
            { 255, 245, 140, 255 },
            { 205, 195, 255, 255 },
            { 215, 205, 255, 255 },
            { 215, 205, 255, 255 },
        },
        {
            { 255, 195, 255, 255 },
            { 215, 215, 255, 255 },
            { 215, 215, 255, 255 },
            { 215, 215, 255, 255 },
        },
        {
            {  20,  20,  20, 255 },
            {  20,  20,  20, 255 },
            {  20,  20,  20, 255 },
            {  20,  20,  20, 255 },
        },
    };
    // clang-format on

    // clang-format off
    static rgba_t e_col_table[][4] = {
        {
            { 215, 165,  60, 255 },
            { 120, 120, 200, 255 },
            { 110, 110, 200, 255 },
            { 110, 110, 200, 255 },
        },
        {
            { 215, 165,  60, 255 },
            { 110, 110, 140, 255 },
            { 110, 110, 140, 255 },
            { 110, 110, 140, 255 },
        },
        {
            { 195,  65, 110, 255 },
            { 150,  75, 250, 255 },
            { 150,  75, 250, 255 },
            { 150,  75, 250, 255 },
        },
        {
            {  20, 225, 225, 255 },
            {  20, 225, 225, 255 },
            {  20, 225, 225, 255 },
            {  20, 225, 225, 255 },
        },
    };
    // clang-format on

    // clang-format off
    static rgba_t wc_cporiginal_color_e[] = {
        { 105,  80,  70, 255 },
        {  60,  50,  35, 255 },
        {  75,  55,  45, 255 },
        {  75,  55,  45, 255 },
        {  65,  45,  15, 255 },
        {  65,  55,  25, 255 },
        {  65,  45,  30, 255 },
        {  65,  55,  50, 255 },
    };
    // clang-format on

    // clang-format off
    static rgba_t wc_cporiginal_color_p[] = {
        { 255, 245, 160, 255 },
        { 255, 215, 150, 255 },
        { 245, 195, 130, 255 },
        { 225, 175, 110, 255 },
        { 205, 155,  90, 255 },
        { 185, 135,  70, 255 },
        { 165, 115,  50, 255 },
        { 155,  95,  40, 255 },
    };
    // clang-format on

    // clang-format off
    static rgba_t wc_cpmail_color_e[] = {
        { 255, 125,  35, 255 },
        {  50, 120, 190, 255 },
        { 110,  75,  90, 255 },
        {  70, 130,  90, 255 },
        { 135,  80,  60, 255 },
        {  90,  80, 150, 255 },
        { 130,  90,  90, 255 },
        {  90, 145, 100, 255 },
    };
    // clang-format on

    // clang-format off
    static rgba_t wc_cpmail_color_p[] = {
        { 255, 215,  40, 255 },
        {  60, 255, 255, 255 },
        { 255, 110, 255, 255 },
        {  75, 225, 165, 255 },
        { 255, 155, 110, 255 },
        { 185, 165, 255, 255 },
        { 255, 125, 150, 255 },
        { 155, 255,  90, 255 },
    };
    // clang-format on

    // clang-format off
    static mTG_disp_data_c tag_disp_data[mTG_WIN_NUM] = {
        { sen_itemw_wakuT_model, sen_itemw_kage_model, sen_itemw_yajirushi_model, sen_itemw_yajirushi2T_model },
        { sen_qitem_wakuT_model, sen_qitem_kage_model, sen_qitem_yajirushiT_model, sen_qitem_yajirushi2T_model },
        { sen_win_wakuT_model, sen_win_kageT_model, sen_win_yajirushiT_model, sen_win_yajirushi2T_model },
    };
    // clang-format on

    static mTG_disp_data_c quest_up_disp = {
        sen_qitem_wakuT_model,
        sen_qitem_kage_model,
        sen_qitem_yajirushi3_model,
        sen_qitem_yajirushi4T_model,
    };

    static mTG_disp_data_c quest_low_disp = {
        sen_qitem_wakuT_model,
        sen_qitem_kage_model,
        sen_qitem_yajirushi5_model,
        sen_qitem_yajirushi6T_model,
    };

    static mTG_disp_data_c sel_low_disp = {
        sen_win_wakuT_model,
        sen_win_kageT_model,
        sen_win_yajirushiT_model,
        sen_win_yajirushi2T_model,
    };

    // clang-format off
    static rgba_t cursol_color[] = {
        { 215,  30, 215, 255 },
        { 235,  60,  60, 255 },
        { 255,   0, 255, 255 },
        {   0, 255, 255, 255 },
    };
    // clang-format on

    mTG_Ovl_c* tag_ovl;
    mTG_disp_data_c* disp_data_p;
    mTG_tag_data_c* tag_data_p;
    rgba_t* color_p;
    int special_color;

    tag_ovl = submenu->overlay->tag_ovl;
    tag_data_p = &mTG_label_table[tag->type];
    special_color = mTG_get_special_color(menu_info, tag);
    disp_data_p = &tag_disp_data[win_type];

    if (win_type == mTG_WIN_QITEM) {
        if (mTG_quest_disp_up_check(tag) == TRUE) {
            disp_data_p = &quest_up_disp;
        } else if (mTG_quest_disp_low_check(tag) == TRUE) {
            disp_data_p = &quest_low_disp;
        }
    } else if (win_type == mTG_WIN_SELECT && (tag->flags & mTG_TAG_FLAG_EDGE_FOOT_SELECT) == 0 &&
               tag_ovl->sel_tag_idx == 1) {
        disp_data_p = &sel_low_disp;
    }

    /* Setup tag DL env */
    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(tag->base_pos[0] + pos_x, tag->base_pos[1] + pos_y, 140.0f, MTX_MULT);
    Matrix_scale(tag->scale, tag->scale, 1.0f, MTX_MULT);

    OPEN_POLY_OPA_DISP(graph);
    gSPDisplayList(POLY_OPA_DISP++, sen_item2_DL_mode);
    gDPSetAlphaCompare(POLY_OPA_DISP++, G_AC_THRESHOLD);
    gDPSetBlendColor(POLY_OPA_DISP++, 255, 255, 255, 40);

    /* Draw window shadow */
    Matrix_push();
    Matrix_translate(tag->body_ofs[0], tag->body_ofs[1], 0.0f, MTX_MULT);
    Matrix_scale(tag->body_scale[0] * tag->_34, tag->body_scale[1] * tag->_34, 1.0f, MTX_MULT);
    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, disp_data_p->frame_shadow);
    Matrix_pull();

    /* Draw arrow */
    if (tag->arrow_dir != 0) {
        Matrix_push();
        Matrix_scale(tag->arrow_scale[0], tag->arrow_scale[1], 1.0f, MTX_MULT);
        gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        if (tag->table == mTG_TABLE_CPORIGINAL_WC) {
            color_p = &wc_cporiginal_color_e[tag->tag_row];
        } else if (tag->table == mTG_TABLE_CPMAIL_WC) {
            color_p = &wc_cpmail_color_e[tag->tag_row];
        } else {
            color_p = &e_col_table[special_color][draw_no];
        }

        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, color_p->r, color_p->g, color_p->b, 255);

        if (tag->arrow_dir == 1) {
            gSPDisplayList(POLY_OPA_DISP++, disp_data_p->left_arrow);
        } else {
            gSPDisplayList(POLY_OPA_DISP++, disp_data_p->right_arrow);
        }

        Matrix_pull();
    }

    if (tag->table == mTG_TABLE_CPORIGINAL_WC) {
        color_p = &wc_cporiginal_color_p[tag->tag_row];
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 128, color_p->r, color_p->g, color_p->b, 255);
        color_p = &wc_cporiginal_color_e[tag->tag_row];
        gDPSetEnvColor(POLY_OPA_DISP++, color_p->r, color_p->g, color_p->b, 150);
    } else if (tag->table == mTG_TABLE_CPMAIL_WC) {
        color_p = &wc_cpmail_color_p[tag->tag_row];
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 128, color_p->r, color_p->g, color_p->b, 255);
        color_p = &wc_cpmail_color_e[tag->tag_row];
        gDPSetEnvColor(POLY_OPA_DISP++, color_p->r, color_p->g, color_p->b, 150);
    } else {
        color_p = &p_col_table[special_color][draw_no];
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 128, color_p->r, color_p->g, color_p->b, 255);
        color_p = &e_col_table[special_color][draw_no];
        gDPSetEnvColor(POLY_OPA_DISP++, color_p->r, color_p->g, color_p->b, 150);
    }

    /* Draw window */
    Matrix_push();
    Matrix_translate(tag->body_ofs[0], tag->body_ofs[1], 0.0f, MTX_MULT);
    Matrix_scale(tag->body_scale[0] * tag->_34, tag->body_scale[1] * tag->_34, 1.0f, MTX_MULT);
    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, disp_data_p->frame);
    Matrix_pull();

    if (tag_data_p->words != NULL && tag->type != mTG_TYPE_HANIWA_PRICE) {
        f32 cursor_ofs;
        f32 x;
        f32 y;

        if (tag->type == mTG_TYPE_CP_DELETE2) {
            cursor_ofs = (f32)(2 + tag->tag_row);
        } else if (tag->type == mTG_TYPE_DUMP_MAIL || tag->type == mTG_TYPE_DUMP_ITEM ||
                   tag->type == mTG_TYPE_DUMP_MAIL_MARK_CONF) {
            cursor_ofs = (f32)(1 + tag->tag_row);
        } else if (tag->type == mTG_TYPE_TAG_PUT_CHK) {
            cursor_ofs = (f32)(2 + tag->tag_row);
        } else {
            cursor_ofs = (f32)tag->tag_row;
        }

        x = tag->text_ofs[0] + (tag->_34 * -4.0f + tag->body_ofs[0]);
        y = (tag->text_ofs[1] + (tag->_34 * -8.0f + tag->body_ofs[1])) - cursor_ofs * 16.0f * tag->_34;
        Matrix_translate(x, y, 0.0f, MTX_MULT);
        gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        color_p = &cursol_color[special_color];
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, color_p->r, color_p->g, color_p->b, 255);
        gSPDisplayList(POLY_OPA_DISP++, sen_win_cursor_model);
    }

    /* Cleanup */
    gDPSetAlphaCompare(POLY_OPA_DISP++, G_AC_NONE);
    gDPSetBlendColor(POLY_OPA_DISP++, 255, 255, 255, 8);

    CLOSE_POLY_OPA_DISP(graph);
}

static void mTG_price_draw(Submenu* submenu, GAME* game, f32 pos_x, f32 pos_y, f32 scale, f32 ofs_x, f32 ofs_y,
                           mTG_tag_c* tag) {
    static int sel_col[] = { 255, 20, 20 };
    static int not_sel_col[] = { 155, 50, 95 };
    u8 price_str[6];
    u32 price = submenu->overlay->haniwa_ovl->price;
    int col = tag->tag_col;
    int* color_p;
    mTG_tag_data_c* tag_data_p = &mTG_label_table[tag->type];
    mTG_tag_word_c** words_p = tag_data_p->words;
    mTG_tag_word_c* word_p;
    int i;

    // clang-format off
    mFont_SetLineStrings(
        game,
        words_p[0]->str, mTG_TAG_STR_LEN,
        pos_x, pos_y,
        mTG_select_col_type_on[0].r, mTG_select_col_type_on[0].g, mTG_select_col_type_on[0].b, 255,
        FALSE,
        TRUE,
        scale, scale,
        mFont_MODE_POLY
    );
    // clang-format on

    mFont_UnintToString(price_str, sizeof(price_str), price, sizeof(price_str) - 1, FALSE, TRUE, TRUE);

    pos_x += 7.0f * scale;
    pos_y += ofs_y;

    // clang-format off
    mFont_SetLineStrings(
        game,
        /* @BUG - this should definitely be words_p[1]->str, only works since the second item is sequential in data */
#ifndef BUGFIXES
        words_p[0][1].str, mTG_TAG_STR_LEN,
#else
        words_p[1]->str, mTG_TAG_STR_LEN,
#endif
        pos_x + scale * (5 + mFont_GetStringWidth(price_str, sizeof(price_str), TRUE)), pos_y,
        mTG_select_col_type_on[0].r, mTG_select_col_type_on[0].g, mTG_select_col_type_on[0].b, 255,
        FALSE,
        TRUE,
        scale, scale,
        mFont_MODE_POLY
    );
    // clang-format on

    /* Skip comma */
    if (col >= 2) {
        col++;
    }

    for (i = 0; i < (int)sizeof(price_str); i++) {
        if (i == col) {
            color_p = sel_col;
        } else if (i == 2) {
            color_p = not_sel_col;
        } else {
            color_p = not_sel_col;
        }

        // clang-format off
        mFont_SetLineStrings(
            game,
            &price_str[i], 1,
            pos_x, pos_y,
            color_p[0], color_p[1], color_p[2], 255,
            FALSE,
            TRUE,
            scale, scale,
            mFont_MODE_POLY
        );
        // clang-format on

        pos_x += scale * (f32)mFont_GetStringWidth(&price_str[i], 1, TRUE);
    }
}

static void mTG_set_questItemInfo_sub(GAME* game, u8* str, int max_len, f32 x, f32 y, f32 scale) {
    int len = mMl_strlen(str, max_len, CHAR_SPACE);

    // clang-format off
    mFont_SetLineStrings(
        game,
        str, len,
        x, y,
        90, 60, 50, 255,
        FALSE,
        TRUE,
        scale, scale,
        mFont_MODE_POLY
    );
    // clang-format on
}

static void mTG_set_questItemInfo(GAME* game, mTG_tag_c* tag, f32 pos_x, f32 pos_y, f32 scale, f32 ofs_x, f32 ofs_y) {
    static int draw_turn_normal[] = { mTG_STR2, mTG_STR0, mTG_STR1 };
    static int draw_turn_omikuji[] = { mTG_STR0, mTG_STR2, mTG_STR1 };
    u8* str_p;
    int len;
    int* draw_turn_p = tag->str2_type == mTG_QSTR_TYPE_OMIKUJI ? draw_turn_omikuji : draw_turn_normal;
    int i;

    for (i = 0; i < mTG_STR_NUM; i++, draw_turn_p++) {
        switch (*draw_turn_p) {
            case mTG_STR0:
                str_p = tag->str0;
                len = mTG_TAG_SEL_STRING_LEN;
                break;
            case mTG_STR1:
                str_p = tag->str1;
                len = mTG_TAG_SEL_STRING_LEN;
                break;
            case mTG_STR2:
                str_p = tag->str2;
                len = mTG_TAG_SEL_STRING_LEN;
                break;
        }

        mTG_set_questItemInfo_sub(game, str_p, len, pos_x, pos_y, scale);
        pos_y += ofs_y;
    }
}

static void mTG_set_select(GAME* game, mSM_MenuInfo_c* menu_info, mTG_tag_c* tag, mTG_tag_word_c** words_p, int n_words,
                           f32 pos_x, f32 pos_y, f32 scale, f32 ofs) {
    rgba_t* color_p;
    int special_color;
    int i;

    special_color = mTG_get_special_color(menu_info, tag);
    for (i = 0; i < n_words; i++) {
        if (i == tag->tag_row) {
            color_p = &mTG_select_col_type_on[special_color];
        } else {
            color_p = &mTG_select_col_type_off[special_color];
        }

        // clang-format off
        mFont_SetLineStrings(
            game,
            words_p[0]->str, mTG_TAG_STR_LEN,
            pos_x, pos_y,
            color_p->r, color_p->g, color_p->b, 255,
            FALSE,
            TRUE,
            scale, scale,
            mFont_MODE_POLY
        );
        // clang-format on

        words_p++;
        pos_y += ofs;
    }
}

static void mTG_set_character(Submenu* submenu, mSM_MenuInfo_c* menu_info, GAME* game, GRAPH* graph, mTG_tag_c* tag,
                              f32 base_x, f32 base_y) {
    f32 scale = tag->scale;
    f32 scale_rate = scale * 0.875f;

    if (!F32_IS_ZERO(tag->scale)) {
        f32 pos_x = 160.0f + (tag->base_pos[0] + base_x + scale * (tag->body_ofs[0] + tag->text_ofs[0]));
        f32 pos_y = 120.0f - (tag->base_pos[1] + base_y + scale * (tag->body_ofs[1] + tag->text_ofs[1]));
        mTG_tag_data_c* tag_data_p = &mTG_label_table[tag->type];

        submenu->overlay->set_char_matrix_proc(graph);
        if (tag->type == mTG_TYPE_CP_DELETE2) {
            // clang-format off
            mFont_SetLineStrings(
                game,
                mTG_tag_str_hontoni, sizeof(mTG_tag_str_hontoni),
                pos_x, pos_y,
                140, 60, 255, 255,
                FALSE,
                TRUE,
                scale_rate, scale_rate,
                mFont_MODE_POLY
            );
            // clang-format on
            pos_y += 16.0f * scale_rate;

            // clang-format off
            mFont_SetLineStrings(
                game,
                mTG_tag_str_iidesuka, sizeof(mTG_tag_str_iidesuka),
                pos_x, pos_y,
                140, 60, 255, 255,
                FALSE,
                TRUE,
                scale_rate, scale_rate,
                mFont_MODE_POLY
            );
            // clang-format on
            pos_y += 16.0f * scale_rate;
        } else if (tag->type == mTG_TYPE_DUMP_MAIL || tag->type == mTG_TYPE_DUMP_ITEM ||
                   tag->type == mTG_TYPE_DUMP_MAIL_MARK_CONF) {
            // clang-format off
            mFont_SetLineStrings(
                game,
                mTG_tag_str_suteruno, sizeof(mTG_tag_str_suteruno),
                pos_x, pos_y,
                220, 30, 220, 255,
                FALSE,
                TRUE,
                scale_rate, scale_rate,
                mFont_MODE_POLY
            );
            // clang-format on
            pos_y += 16.0f * scale_rate;
        } else if (tag->type == mTG_TYPE_TAG_PUT_CHK) {
            // clang-format off
            mFont_SetLineStrings(
                game,
                mTG_tag_str_put_chk1, sizeof(mTG_tag_str_put_chk1),
                pos_x, pos_y,
                220, 30, 220, 255,
                FALSE,
                TRUE,
                scale_rate, scale_rate,
                mFont_MODE_POLY
            );
            // clang-format on
            pos_y += 16.0f * scale_rate;

            // clang-format off
            mFont_SetLineStrings(
                game,
                mTG_tag_str_put_chk2, sizeof(mTG_tag_str_put_chk2),
                pos_x, pos_y,
                220, 30, 220, 255,
                FALSE,
                TRUE,
                scale_rate, scale_rate,
                mFont_MODE_POLY
            );
            // clang-format on
            pos_y += 16.0f * scale_rate;
        }

        if (tag->type == mTG_TYPE_HANIWA_PRICE) {
            mTG_price_draw(submenu, game, pos_x, pos_y, scale_rate, 12.0f * scale_rate, 16.0f * scale_rate, tag);
        } else {
            mTG_set_select(game, menu_info, tag, tag_data_p->words, tag_data_p->lines, pos_x, pos_y, scale_rate,
                           16.0f * scale_rate);
        }
    }
}

static void mTG_set_character_item(Submenu* submenu, GAME* game, GRAPH* graph, mTG_tag_c* tag, f32 base_x, f32 base_y) {
    static rgba_t item_name_color[] = {
        { 90, 60, 50, 255 },
        { 40, 30, 30, 255 },
    };
    static rgba_t wc_cporiginal_color_char[] = {
        { 80, 50, 50, 255 }, { 80, 50, 50, 255 }, { 80, 50, 50, 255 }, { 70, 50, 50, 255 },
        { 70, 50, 50, 255 }, { 60, 40, 40, 255 }, { 60, 40, 40, 255 }, { 50, 30, 30, 255 },
    };
    static rgba_t wc_cpmail_color_char[] = {
        { 70, 40, 20, 255 }, { 20, 60, 90, 255 }, { 60, 30, 70, 255 }, { 10, 70, 50, 255 },
        { 70, 50, 20, 255 }, { 60, 50, 70, 255 }, { 70, 20, 30, 255 }, { 50, 70, 10, 255 },
    };
    f32 scale_rate = tag->scale;

    if (!F32_IS_ZERO(scale_rate)) {
        f32 pos_x;
        f32 pos_y;
        rgba_t* color_p;

        if (tag->table == mTG_TABLE_CATALOG_WC) {
            color_p = &item_name_color[1];
        } else if (tag->table == mTG_TABLE_CPORIGINAL_WC) {
            color_p = &wc_cporiginal_color_char[tag->tag_row];
        } else if (tag->table == mTG_TABLE_CPMAIL_WC) {
            color_p = &wc_cpmail_color_char[tag->tag_row];
        } else {
            color_p = &item_name_color[0];
        }

        pos_x = 160.0f + (tag->base_pos[0] + base_x + scale_rate * (tag->body_ofs[0] + tag->text_ofs[0]));
        pos_y = 120.0f - (tag->base_pos[1] + base_y + scale_rate * (tag->body_ofs[1] + tag->text_ofs[1]));

        submenu->overlay->set_char_matrix_proc(graph);

        // clang-format off
        mFont_SetLineStrings(
            game,
            tag->str0, mTG_TAG_STR_LEN,
            pos_x, pos_y,
            color_p->r, color_p->g, color_p->b, 255,
            FALSE,
            TRUE,
            scale_rate * 0.875f, scale_rate * 0.875f,
            mFont_MODE_POLY
        );
        // clang-format on
    }
}

static void mTG_set_character_q_item(Submenu* submenu, GAME* game, GRAPH* graph, mTG_tag_c* tag, f32 base_x,
                                     f32 base_y) {
    f32 scale_rate = tag->scale;

    if (!F32_IS_ZERO(scale_rate)) {
        f32 pos_x;
        f32 pos_y;

        pos_x = 160.0f + (tag->base_pos[0] + base_x + scale_rate * (tag->body_ofs[0] + tag->text_ofs[0]));
        pos_y = 120.0f - (tag->base_pos[1] + base_y + scale_rate * (tag->body_ofs[1] + tag->text_ofs[1]));

        submenu->overlay->set_char_matrix_proc(graph);
        scale_rate *= 0.75f;
        mTG_set_questItemInfo(game, tag, pos_x, pos_y, scale_rate, 12.0f * scale_rate, 16.0f * scale_rate);
    }
}

static void mTG_set_dl(Submenu* submenu, mSM_MenuInfo_c* menu_info, GRAPH* graph, GAME* game, mTG_tag_c* tag,
                       f32 base_x, f32 base_y, int draw_no) {
    if (tag->type == mTG_TYPE_NONE) {
        if (tag->arrow_dir != 0) {
            if (tag->str2_type != mTG_QSTR_TYPE_NONE) {
                mTG_set_win_field(graph, submenu, menu_info, tag, base_x, base_y, mTG_WIN_QITEM, 0);
                mTG_set_character_q_item(submenu, game, graph, tag, base_x, base_y);
            } else {
                mTG_set_win_field(graph, submenu, menu_info, tag, base_x, base_y, mTG_WIN_ITEM, 0);
                mTG_set_character_item(submenu, game, graph, tag, base_x, base_y);
            }
        }
    } else {
        mTG_set_win_field(graph, submenu, menu_info, tag, base_x, base_y, mTG_WIN_SELECT, draw_no);
        mTG_set_character(submenu, menu_info, game, graph, tag, base_x, base_y);
    }
}

extern Gfx inv_item_shadow_mode[];
extern Gfx inv_item_mode[];

static void mTG_draw_mail(Submenu* submenu, GRAPH* graph, Mail_c* mail, f32 x, f32 y) {
    OPEN_POLY_OPA_DISP(graph);
    gSPDisplayList(POLY_OPA_DISP++, inv_item_shadow_mode);
    CLOSE_POLY_OPA_DISP(graph);
    submenu->overlay->draw_mail_proc(graph, x + 4.0f, y - 4.0f, 1.0f, mail, TRUE, TRUE, FALSE);

    OPEN_POLY_OPA_DISP(graph);
    gSPDisplayList(POLY_OPA_DISP++, inv_item_mode);
    CLOSE_POLY_OPA_DISP(graph);
    submenu->overlay->draw_mail_proc(graph, x, y, 1.0f, mail, TRUE, FALSE, FALSE);
}

static void mTG_single_draw_mail(Submenu* submenu, GRAPH* graph, mTG_Ovl_c* tag_ovl) {
    Mail_c* mail;
    int i;
    mTG_cpmail_mark_pos_c* mark_pos = tag_ovl->_2F4;

    for (i = 0; i < 4; i++) {
        f32 x = mark_pos->pos[0];
        f32 y = mark_pos->pos[1];

        mail = mark_pos->_00;
        if (mail != NULL && mMl_check_not_used_mail(mail) == FALSE) {
            mTG_draw_mail(submenu, graph, mail, x, y);
        }

        mark_pos++;
    }
}

static void mTG_single_draw_original(Submenu* submenu, GRAPH* graph, mTG_Ovl_c* tag_ovl) {
    mActor_name_t item;
    int i;
    mTG_cporiginal_mark_entry_c* entry_p = tag_ovl->original_entries;

    for (i = 0; i < mTG_ORG_TYPE_NUM; i++) {
        f32 x = entry_p->pos[0];
        f32 y = entry_p->pos[1];

        item = entry_p->item;
        if (item != EMPTY_NO) {
            mSM_draw_original(submenu, graph, x, y, 1.0f, item, FALSE);
        }

        entry_p++;
    }
}

static void mTG_draw_func(Submenu* submenu, GAME* game, int menu_type) {
    if (submenu->menu_type == menu_type) {
        GRAPH* graph = game->graph;
        Submenu_Overlay_c* overlay_p = submenu->overlay;
        mTG_Ovl_c* tag_ovl = overlay_p->tag_ovl;
        mTG_tag_c* tag;
        mSM_MenuInfo_c* menu_info = &overlay_p->menu_info[menu_type];
        int i;
        int max;

        if (menu_info->proc_status != mSM_OVL_PROC_MOVE && menu_info->proc_status != mSM_OVL_PROC_END) {
            mTG_single_draw_mail(submenu, graph, tag_ovl);
            mTG_single_draw_original(submenu, graph, tag_ovl);

            if ((tag_ovl->nw_gba_flags & 0x8) == 0) {
                submenu->overlay->menu_control.hand_draw_func(submenu, game);
            }

            max = overlay_p->tag_ovl->sel_tag_idx + 1;
            tag = overlay_p->tag_ovl->tags;
            for (i = 0; i < max; i++, tag++) {
                mTG_set_dl(submenu, menu_info, graph, game, tag, menu_info->position[0], menu_info->position[1], i);
            }

            if ((tag_ovl->nw_gba_flags & 0x8) != 0) {
                submenu->overlay->menu_control.hand_draw_func(submenu, game);
            }
        }
    }
}

extern void mTG_tag_ovl_construct(Submenu* submenu) {
    Submenu_Overlay_c* overlay_p = submenu->overlay;
    mSM_Control_c* menu_control = &overlay_p->menu_control;
    mTG_Ovl_c* tag_ovl_p;
    mTG_tag_c* tag;
    int i;

    if (submenu->overlay->tag_ovl == NULL) {
        mem_clear((u8*)&tag_ovl_data, sizeof(tag_ovl_data), 0);
        menu_control->tag_move_func = &mTG_move_func;
        menu_control->tag_draw_func = &mTG_draw_func;

        tag_ovl_p = &tag_ovl_data;
        overlay_p->tag_ovl = tag_ovl_p;

        submenu->overlay->tag_ovl->set_hand_pos_proc = &mTG_set_hand_pos;
        submenu->overlay->tag_ovl->init_tag_data_item_win_proc = &mTG_init_tag_data_item_win;
        submenu->overlay->tag_ovl->chg_tag_func_proc = &mTG_chg_tag_func;
        submenu->overlay->tag_ovl->get_table_idx_proc = &mTG_get_table_idx;
        submenu->overlay->tag_ovl->get_mail_pointer_proc = &mTG_get_mail_pointer;
        submenu->overlay->tag_ovl->exchange_proc = &mTG_exchange_proc;

        tag = tag_ovl_p->tags;
        for (i = 0; i < mTG_TAG_NUM; i++, tag++) {
            tag->type = mTG_TYPE_NONE;
        }

        tag_ovl_p->sel_tag_idx = -1;
        tag_ovl_p->ret_tag_idx = -1;
#ifdef MOUSE_INPUT
        tag_ovl_p->mouse_active = 0;
        tag_ovl_p->mouse_x = 160;
        tag_ovl_p->mouse_y = 120;
        tag_ovl_p->hovered_table = -1;
        tag_ovl_p->hovered_idx = -1;
        tag_ovl_p->hovered_col = -1;
        tag_ovl_p->hovered_row = -1;
#endif
    }
}

extern void mTG_tag_ovl_destruct(Submenu* submenu) {
    submenu->overlay->tag_ovl = NULL;
}
