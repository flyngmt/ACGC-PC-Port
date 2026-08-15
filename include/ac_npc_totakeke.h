#ifndef AC_NPC_TOTAKEKE_H
#define AC_NPC_TOTAKEKE_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"
#include "m_item_name.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE Npc_Totakeke_Profile;

// @BUG - this should've been updated to mIN_ITEM_NAME_LEN
#ifndef BUGFIXES
#define aNTT_REQUEST_STR_LEN 10
#else
#define aNTT_REQUEST_STR_LEN mIN_ITEM_NAME_LEN
#endif

typedef struct npc_totakeke_s NPC_TOTAKEKE_ACTOR;

typedef struct npc_totakeke_think_data_s aNTT_think_data_c;
typedef struct npc_totakeke_event_save_s aNTT_event_save_c;
typedef struct npc_totakeke_event_common_s aNTT_event_common_c;

typedef void (*aNTT_PROC)(NPC_TOTAKEKE_ACTOR* totakeke, GAME_PLAY* play);

struct npc_totakeke_s {
    /* 0x000 */ NPC_ACTOR npc_class;
    /* 0x994 */ aNTT_PROC proc;
    /* 0x998 */ s16 roll2_count;
    /* 0x99a */ s16 roll4_count;
    /* 0x99c */ s16 show_timer;
    /* 0x99e */ u8 song;
    /* 0x99f */ u8 _99f;
    /* 0x9a0 */ u8 _9a0;
    /* 0x9a1 */ u8 _9a1;
    /* 0x9a2 */ u8 _9a2;
    /* 0x9a3 */ u8 talk;
    /* 0x9a4 */ u8 think;
    /* 0x9a5 */ u8 pre_roll_think;
    /* 0x9a6 */ u8 post_roll_think;
    /* 0x9a7 */ u8 melody_inst;
    /* 0x9a8 */ u8 think_proc_id;
    /* 0x9a9 */ u8 majin_flag;
    /* 0x9aa */ u8 _9aa;
    /* 0x9ab */ u8 _9ab;
#ifdef TARGET_PC
    /* 0x9ac */ f32 staffroll_logic_accum;
#endif
};

struct npc_totakeke_think_data_s {
    /* 0x00 */ u8 think_proc_id;
    /* 0x01 */ u8 think_init_idx;
    /* 0x02 */ u8 next_talk;
    /* 0x03 */ u8 talk;
    /* 0x04 */ u8 pre_roll_think;
};

#define aNTT_FLAG_HELLO (1 << 0)
#define aNTT_FLAG_1 (1 << 1)
#define aNTT_FLAG_2 (1 << 2)
#define aNTT_FLAG_3 (1 << 3)
#define aNTT_FLAG_AIRCHECK_RECEIVED (1 << 4)
#define aNTT_FLAG_5 (1 << 5)
#define aNTT_FLAG_6 (1 << 6)
#define aNTT_FLAG_7 (1 << 7)
#define aNTT_FLAG_SP_DELETE_MAJIN (1 << 13)
#define aNTT_FLAG_SP_ROLL_DRAW (1 << 14)
#define aNTT_FLAG_SP_ROLL_END (1 << 15)

struct npc_totakeke_event_save_s {
    /* 0x00 */ s16 _00;
    /* 0x01 */ u16 bitfield;
    /* 0x04 */ u8 request_str[mIN_ITEM_NAME_LEN];
    /* 0x14 */ u8 roll_flag;
    /* 0x15 */ u8 copyright_alpha;
};

struct npc_totakeke_event_common_s {
    /* 0x00 */ u16 foreigner_bitfield;
    /* 0x02 */ u16 _02;
    /* 0x04 */ u8 request_str;
    /* 0x05 */ u16 _05;
    /* 0x07 */ u8 _07;
    /* 0x08 */ u8 _08;
    /* 0x09 */ u8 _09;
    /* 0x0a */ u8 _0a;
    /* 0x0b */ u8 _0b;
    /* 0x0c */ u8 _0c;
    /* 0x0d */ u8 _0d;
    /* 0x0e */ u8 _0e;
    /* 0x0f */ u8 _0f;
};

enum aNTT_talk_proc {
    aNTT_TALK_NONE,
    aNTT_TALK_SELECT0,
    aNTT_TALK_SELECT1,
    aNTT_TALK_STOP_PLAYER,
    aNTT_TALK_SUBMENU,
    aNTT_TALK_SUBMENU2,
    aNTT_TALK_GIVE
};

enum aNTT_think_proc {
    aNTT_THINK_NONE,
    aNTT_THINK_WAIT,
    aNTT_THINK_ROLL,
    aNTT_THINK_ROLL1,
    aNTT_THINK_ROLL2,
    aNTT_THINK_ROLL4,
    aNTT_THINK_ROLL_END,
    aNTT_THINK_7,
    aNTT_THINK_8,
    aNTT_THINK_9,
    aNTT_THINK_GIVE_MERODY,
    aNTT_THINK_POCKETS_FULL,
    aNTT_THINK_GIVE_LATER,
};

#ifdef __cplusplus
}
#endif

#endif
