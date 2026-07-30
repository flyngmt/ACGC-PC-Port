#ifndef AC_STRUCTURE_H
#define AC_STRUCTURE_H

#include "types.h"
#include "m_actor.h"
#include "m_actor_dlftbls.h"
#include "c_keyframe.h"
#include "m_play_h.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef TARGET_PC
#define aSTR_ACTOR_TBL_COUNT 32
#define aSTR_ACTOR_CLASS_SLOT_SIZE 0x400
#else
#define aSTR_ACTOR_TBL_COUNT 9
#endif
#define aSTR_OVERLAY_SIZE 0x2400

enum structure_type {
    aSTR_TYPE_HOUSE1,
    aSTR_TYPE_HOUSE2,
    aSTR_TYPE_HOUSE3,
    aSTR_TYPE_HOUSE4,
    aSTR_TYPE_HOUSE5,
    aSTR_TYPE_MYHOME,
    aSTR_TYPE_6,
    aSTR_TYPE_7,
    aSTR_TYPE_SHOP1,
    aSTR_TYPE_SHOP2,
    aSTR_TYPE_SHOP3,
    aSTR_TYPE_SHOP4,
    aSTR_TYPE_POST_OFFICE,
    aSTR_TYPE_STATION1,
    aSTR_TYPE_STATION2,
    aSTR_TYPE_STATION3,
    aSTR_TYPE_TRAIN0,
    aSTR_TYPE_TRAIN1,
    aSTR_TYPE_POLICE_BOX,
    aSTR_TYPE_FALLS,
    aSTR_TYPE_FALLSESW,
    aSTR_TYPE_RESERVE,
    aSTR_TYPE_SHRINE,
    aSTR_TYPE_BRSHOP,
    aSTR_TYPE_BUGGY,
    aSTR_TYPE_S_CAR,
    aSTR_TYPE_KAMAKURA, // also used for camping tent
    aSTR_TYPE_GOZA,
    aSTR_TYPE_RADIO,
    aSTR_TYPE_YATAI,
    aSTR_TYPE_TUKIMI,
    aSTR_TYPE_TUKIMI2,
    aSTR_TYPE_MIKUJI,
    aSTR_TYPE_COUNT,
    aSTR_TYPE_COUNT02,
    aSTR_TYPE_SPORTSFAIR_A,
    aSTR_TYPE_SPORTSFAIR_B,
    aSTR_TYPE_TURI,
    aSTR_TYPE_TURI2,
    aSTR_TYPE_KOINOBORI,
    aSTR_TYPE_DUMP,
    aSTR_TYPE_WINDMILL,
    aSTR_TYPE_LOTUS,
    aSTR_TYPE_MIKANBOX,
    aSTR_TYPE_DOUZOU,
    aSTR_TYPE_TOUDAI,
    aSTR_TYPE_GHOG,
    aSTR_TYPE_HTABLE,
    aSTR_TYPE_MUSEUM,
    aSTR_TYPE_BRIDGE_A,
    aSTR_TYPE_50,
    aSTR_TYPE_NEEDLEWORK_SHOP,
    aSTR_TYPE_FLAG,
    aSTR_TYPE_BOAT,
    aSTR_TYPE_COTTAGE_MY,
    aSTR_TYPE_COTTAGE_NPC,

    aSTR_TYPE_NUM
};

enum structure_palette {
    aSTR_PAL_HOUSE1_A,
    aSTR_PAL_HOUSE1_B,
    aSTR_PAL_HOUSE1_C,
    aSTR_PAL_HOUSE1_D,
    aSTR_PAL_HOUSE1_E,
    aSTR_PAL_HOUSE2_A,
    aSTR_PAL_HOUSE2_B,
    aSTR_PAL_HOUSE2_C,
    aSTR_PAL_HOUSE2_D,
    aSTR_PAL_HOUSE2_E,
    aSTR_PAL_HOUSE3_A,
    aSTR_PAL_HOUSE3_B,
    aSTR_PAL_HOUSE3_C,
    aSTR_PAL_HOUSE3_D,
    aSTR_PAL_HOUSE3_E,
    aSTR_PAL_HOUSE4_A,
    aSTR_PAL_HOUSE4_B,
    aSTR_PAL_HOUSE4_C,
    aSTR_PAL_HOUSE4_D,
    aSTR_PAL_HOUSE4_E,
    aSTR_PAL_HOUSE5_A,
    aSTR_PAL_HOUSE5_B,
    aSTR_PAL_HOUSE5_C,
    aSTR_PAL_HOUSE5_D,
    aSTR_PAL_HOUSE5_E,
    aSTR_PAL_MYHOME_A,
    aSTR_PAL_MYHOME_B,
    aSTR_PAL_MYHOME_C,
    aSTR_PAL_MYHOME_D,
    aSTR_PAL_MYHOME_E,
    aSTR_PAL_MYHOME_F,
    aSTR_PAL_MYHOME_G,
    aSTR_PAL_MYHOME_H,
    aSTR_PAL_MYHOME_I,
    aSTR_PAL_MYHOME_J,
    aSTR_PAL_MYHOME_K,
    aSTR_PAL_MYHOME_L,
    aSTR_PAL_SHOP1,
    aSTR_PAL_SHOP2,
    aSTR_PAL_SHOP3,
    aSTR_PAL_SHOP4,
    aSTR_PAL_POST_OFFICE,
    aSTR_PAL_STATION1_A,
    aSTR_PAL_STATION1_B,
    aSTR_PAL_STATION1_C,
    aSTR_PAL_STATION1_D,
    aSTR_PAL_STATION1_E,
    aSTR_PAL_STATION2_A,
    aSTR_PAL_STATION2_B,
    aSTR_PAL_STATION2_C,
    aSTR_PAL_STATION2_D,
    aSTR_PAL_STATION2_E,
    aSTR_PAL_STATION3_A,
    aSTR_PAL_STATION3_B,
    aSTR_PAL_STATION3_C,
    aSTR_PAL_STATION3_D,
    aSTR_PAL_STATION3_E,
    aSTR_PAL_TRAIN1_A1,
    aSTR_PAL_TRAIN1_A2,
    aSTR_PAL_POLICE_BOX,
    aSTR_PAL_FALLS,
    aSTR_PAL_FALLSESW,
    aSTR_PAL_RESERVE,
    aSTR_PAL_SHRINE,
    aSTR_PAL_BR_SHOP,
    aSTR_PAL_BUGGY,
    aSTR_PAL_S_CAR,
    aSTR_PAL_KAMAKURA,
    aSTR_PAL_GOZA,
    aSTR_PAL_RADIO,
    aSTR_PAL_YATAI,
    aSTR_PAL_TUKIMI,
    aSTR_PAL_TUKIMI2,
    aSTR_PAL_MIKUJI,
    aSTR_PAL_COUNT,
    aSTR_PAL_COUNT02,
    aSTR_PAL_KAGO_R,
    aSTR_PAL_KAGO_W,
    aSTR_PAL_TURI,
    aSTR_PAL_TURI2,
    aSTR_PAL_KOINOBORI_A,
    aSTR_PAL_DUMP,
    aSTR_PAL_WINDMILL_A,
    aSTR_PAL_WINDMILL_B,
    aSTR_PAL_WINDMILL_C,
    aSTR_PAL_WINDMILL_D,
    aSTR_PAL_WINDMILL_E,
    aSTR_PAL_01_LOTUS,
    aSTR_PAL_MIKANBOX,
    aSTR_PAL_DOUZOU_DAI,
    aSTR_PAL_TOUDAI,
    aSTR_PAL_MUSEUM,
    aSTR_PAL_BRIDGE_A,
    aSTR_PAL_TAILOR,
    aSTR_PAL_FLAG,
    aSTR_PAL_BOAT,
    aSTR_PAL_MYHOME_ISLAND,
    aSTR_PAL_HOUSE_I,

    aSTR_PAL_NUM
};

typedef struct actor_structure_control_s STRUCTURE_CONTROL_ACTOR;
typedef struct actor_structure_s STRUCTURE_ACTOR;

typedef STRUCTURE_ACTOR* (*aSTR_SETUP_ACTOR_PROC)(GAME*, mActor_name_t, s16, f32, f32);
typedef void (*aSTR_GET_OVERLAY_AREA_PROC)(ACTOR_DLFTBL*);
typedef void (*aSTR_FREE_OVERLAY_AREA_PROC)(ACTOR_DLFTBL*);
typedef STRUCTURE_ACTOR* (*aSTR_GET_ACTOR_AREA_PROC)();
typedef void (*aSTR_FREE_ACTOR_AREA_PROC)(STRUCTURE_ACTOR*);
typedef u16* (*aSTR_GET_PAL_SEGMENT_PROC)(s16);

typedef void (*aSTR_MOVE_PROC)(STRUCTURE_ACTOR*, GAME_PLAY*);

// sizeof(actor_structure_s) == 0x2DC
struct actor_structure_s {
    /* 0x000 */ ACTOR actor_class;
    /* 0x174 */ int keyframe_state;
    /* 0x178 */ cKF_SkeletonInfo_R_c keyframe;
    /* 0x1E8 */ int keyframe_saved_keyframe;
    /* 0x1EC */ s_xyz work_area[15];
    /* 0x246 */ s_xyz morph_area[15];
    /* 0x2A0 */ aSTR_MOVE_PROC action_proc;
    /* 0x2A4 */ int _2A4;
    /* 0x2A8 */ int structure_type; /* aSTR_TYPE_* */
    /* 0x2AC */ int structure_pal;  /* aSTR_PAL_* */
    /* 0x2B0 */ int request_type;
    /* 0x2B4 */ int action;

    /* general purpose members with unique usage between structure actors */
    /* 0x2B8 */ int arg0;
    /* 0x2BC */
    intptr_t arg1; /* Some structure actors use this slot as a native pointer. */
    /* 0x2C0 */ int arg2;
    /* 0x2C4 */
    intptr_t arg3; /* Some structure actors use this slot as a native pointer. */

    /* general purpose float members with unique usage between structure actors*/
    /* 0x2C8 */ f32 arg0_f;
    /* 0x2CC */ f32 arg1_f;
    /* 0x2D0 */ f32 arg2_f;
    /* 0x2D4 */ f32 arg3_f;

    /* 0x2D8 */ u32 season;
};

typedef struct actor_overlay_info_s {
    u8* overlay_p;
    int used;
} aSTR_Overlay_info_c;

typedef struct actor_structure_clip_s {
    aSTR_SETUP_ACTOR_PROC setup_actor_proc;
    aSTR_GET_OVERLAY_AREA_PROC get_overlay_area_proc;
    aSTR_FREE_OVERLAY_AREA_PROC free_overlay_area_proc;
    aSTR_GET_ACTOR_AREA_PROC get_actor_area_proc;
    aSTR_FREE_ACTOR_AREA_PROC free_actor_area_proc;

    STRUCTURE_ACTOR* structure_actor_tbl[aSTR_ACTOR_TBL_COUNT];
    int structure_actor_used_tbl[aSTR_ACTOR_TBL_COUNT];

    aSTR_Overlay_info_c overlay_area[aSTR_ACTOR_TBL_COUNT];

    aSTR_GET_PAL_SEGMENT_PROC get_pal_segment_proc;
} aSTR_Clip_c;

struct actor_structure_control_s {
    ACTOR actor_class;
    int _174;
    mActor_name_t str_door_name;
    u8 reset;
};

extern ACTOR_PROFILE Structure_Profile;

#ifdef __cplusplus
}
#endif

#endif
