#ifndef M_SUBMENU_H
#define M_SUBMENU_H

#include "types.h"
#include "m_actor_type.h"
#include "m_submenu_ovl_h.h"
#include "game_h.h"
#include "m_mail.h"
#include "m_private.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct submenu_s Submenu;

typedef intptr_t mSM_param3_t;

#define mSM_MAP_BUTTON BUTTON_X
#define mSM_INV_BUTTON_0 BUTTON_START
#define mSM_INV_BUTTON_1 BUTTON_Y

enum {
    mSM_MODE_IDLE,
    mSM_MODE_PRERENDER_INIT,
    mSM_MODE_PRERENDER_WAIT,
    mSM_MODE_PRERENDER_DONE,
    mSM_MODE_OTHER,

    mSM_MODE_NUM
};

enum {
    mSM_PROCESS_WAIT,
    mSM_PROCESS_PREWAIT,
    mSM_PROCESS_LINKWAIT,
    mSM_PROCESS_PLAY,
    mSM_PROCESS_END,

    mSM_PROCESS_NUM
};

enum {
    mSM_DLF_SUBMENU_OVL,
    mSM_DLF_PLAYER_ACTOR,

    mSM_DLF_NUM
};

enum {
    mSM_MOVE_OUT_RIGHT,
    mSM_MOVE_IN_RIGHT,

    mSM_MOVE_OUT_LEFT,
    mSM_MOVE_IN_LEFT,

    mSM_MOVE_OUT_TOP,
    mSM_MOVE_IN_TOP,

    mSM_MOVE_OUT_BOTTOM,
    mSM_MOVE_IN_BOTTOM,

    mSM_MOVE_NUM
};

enum submenu_overlay {
    mSM_OVL_NONE,

    mSM_OVL_INVENTORY,
    mSM_OVL_HBOARD,
    mSM_OVL_TIMEIN,
    mSM_OVL_LEDIT,
    mSM_OVL_MAP,
    mSM_OVL_NOTICE,
    mSM_OVL_REPAY,
    mSM_OVL_MSCORE,
    mSM_OVL_BIRTHDAY,
    mSM_OVL_EDITOR,
    mSM_OVL_MAILBOX,
    mSM_OVL_BOARD,
    mSM_OVL_ADDRESS,
    mSM_OVL_HANIWA,
    mSM_OVL_EDITENDCHK,
    mSM_OVL_WARNING,
    mSM_OVL_CPMAIL,
    mSM_OVL_CPWARNING,
    mSM_OVL_CPEDIT,
    mSM_OVL_CATALOG,
    mSM_OVL_MUSIC,
    mSM_OVL_BANK,
    mSM_OVL_NEEDLEWORK,
    mSM_OVL_CPORIGINAL,
    mSM_OVL_DESIGN,
    mSM_OVL_GBA,
    mSM_OVL_DIARY,
    mSM_OVL_CALENDAR,
    mSM_OVL_PASSWORDMAKE,
    mSM_OVL_PASSWORDCHK,

    mSM_OVL_NUM
};

enum {
    mSM_IV_OPEN_NORMAL,
    mSM_IV_OPEN_MAILBOX,
    mSM_IV_OPEN_HANIWA_ENTRUST,
    mSM_IV_OPEN_HANIWA_TAKE,
    mSM_IV_OPEN_QUEST,
    mSM_IV_OPEN_SELL,
    mSM_IV_OPEN_GIVE,
    mSM_IV_OPEN_SEND_MAIL,
    mSM_IV_OPEN_TAKE,
    mSM_IV_OPEN_PUTIN_FTR,
    mSM_IV_OPEN_MINIDISK,
    mSM_IV_OPEN_SHRINE,
    mSM_IV_OPEN_12,
    mSM_IV_OPEN_EXCHANGE,
    mSM_IV_OPEN_CPMAIL,
    mSM_IV_OPEN_CURATOR,
    mSM_IV_OPEN_PASSWORD,

    mSM_IV_OPEN_NUM
};

enum {
    mSM_IV_ITEM_NORMAL,
    mSM_IV_ITEM_PUT_AWAY,
    mSM_IV_ITEM_WAIT,

    mSM_IV_ITEM_NUM
};

enum {
    mSM_HANIWA_OPEN_ENTRUST,
    mSM_HANIWA_OPEN_TAKE,

    mSM_HANIWA_OPEN_NUM
};

enum {
    mSM_BD_OPEN_WRITE,
    mSM_BD_OPEN_READ,
    mSM_BD_OPEN_REWRITE,
    mSM_BD_OPEN_WRITE_ISLAND,
    mSM_BD_OPEN_READ_ISLAND,

    mSM_BD_OPEN_NUM
};

#define mSM_CHECK_OPEN_MAP() (chkTrigger(mSM_MAP_BUTTON) && Common_Get(map_flag) == TRUE)

typedef struct submenu_item_s {
    mActor_name_t item;
    u8 slot_no;
} Submenu_Item_c;

typedef struct submenu_dlftbl {
    void* _00;
    int _04;
    int _08;
    int _0C;
    int _10;
    int _14;
    const char* name;
} mSM_dlftbl_c;

typedef void (*SUBMENU_PROC)(Submenu*);
typedef void (*SUBMENU_GAME_PROC)(Submenu*, GAME*);

/* sizeof (struct submenu_s) == 0x1B8 */
struct submenu_s {
    /* 0x000 */ int mode;
    /* 0x004 */ int menu_type;
    /* 0x008 */ int current_menu_type;

    /* 0x00C */ int process_status;

    /* 0x010 */ int param0;
    /* 0x014 */ int param1;
    /* 0x018 */ void* param2;
    /* 0x01C */ mSM_param3_t param3;

    /* 0x020 */ int wait_timer;

    /* 0x024 */ char* overlay_address;
    /* 0x028 */ char* next_overlay_address;
    /* 0x02C */ Submenu_Overlay_c* overlay;
    /* 0x030 */ SUBMENU_PROC move_proc;
    /* 0x034 */ SUBMENU_GAME_PROC draw_proc;

    /* 0x038 */ Mail_c mail;   /* selected mail */
    /* 0x162 */ u8 open_flag;  // only set to 0 or 1, checked at least once in aQMgr_actor_move_talk_sub_hand_item_wait
    /* 0x163 */ u8 after_mode; /* relates to code which runs after the submenu process */
    /* 0x164 */ u8 unk_164;    // only set to 0 in mSM_move_LINKWait in AC
    /* 0x165 */ u8 start_refuse;       /* when set to TRUE, the START button input will be ignored */
    /* 0x166 */ u8 start_refuse_timer; /* timer for when to disable the start button ignore flag */
    /* 0x168 */ xyz_t water_pos;       /* calculated to the nearest water position to the player for releasing fish */
    /* 0x174 */ Submenu_Item_c*
        item_p;               /* pointer to a 'Submenu_Item_c' array, seemingly only points to Submenu::items */
    /* 0x178 */ s16 item_num; /* number of items in the item array */
    /* 0x17A */ s16 selected_item_num; /* number of selected items in the item array */
    /* 0x17C */ Submenu_Item_c
        items[mPr_POCKETS_SLOT_COUNT]; /* item buffer, entries are only set when an item is selected by the player */
};

extern int mSM_COLLECT_INSECT_GET(int idx);
extern void mSM_COLLECT_INSECT_SET(int idx);
extern int mSM_CHECK_ALL_INSECT_GET();
extern int mSM_CHECK_LAST_INSECT_GET(int idx);
extern int mSM_COLLECT_FISH_GET(int idx);
extern void mSM_COLLECT_FISH_SET(int idx);
extern int mSM_CHECK_ALL_FISH_GET();
extern int mSM_CHECK_LAST_FISH_GET(int idx);
extern int SubmenuArea_IsPlayer();
extern void* mSM_ovlptr_dllcnv(void* proc, Submenu* submenu, int dlf_idx);
extern void mSM_submenu_ovlptr_init(GAME_PLAY* play);
extern void mSM_submenu_ovlptr_cleanup(Submenu* submenu);
extern void load_player(Submenu* submenu);
extern void mSM_submenu_ct(Submenu* submenu);
extern void mSM_submenu_dt(Submenu* submenu);
extern void mSM_open_submenu(Submenu* submenu, int type, int arg0, int arg1);
extern void mSM_open_submenu_new(Submenu* submenu, int type, int arg0, int arg1, void* arg2);
extern void mSM_open_submenu_new2(Submenu* submenu, int type, int arg0, int arg1, void* arg2, mSM_param3_t arg3);
extern void mSM_submenu_ctrl(GAME_PLAY* play);
extern void mSM_submenu_move(Submenu* submenu);
extern void mSM_submenu_draw(Submenu* submenu, GAME* game);
extern int mSM_check_open_inventory_itemlist(int type, int param_2);
extern void mSM_Object_Exchange_keep_new_Menu(GAME_PLAY* play);
extern u8* mSM_Get_ground_tex_p(GAME_PLAY* play);
extern u16* mSM_Get_ground_pallet_p(GAME_PLAY* play);

#ifdef __cplusplus
}
#endif

#endif
