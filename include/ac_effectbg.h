#ifndef AC_EFFECTBG_H
#define AC_EFFECTBG_H

#include "types.h"
#include "m_actor.h"
#include "c_keyframe.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EffectBg_ENTRY_NUM 3
#define EffectBg_JOINT_NUM 4
#define EffectBg_JOINT_ALL 6

enum {
    EffectBG_EFFECT_SHAKE,
    EffectBG_EFFECT_CUT_LEFT,
    EffectBG_EFFECT_CUT_RIGHT,
    EffectBG_EFFECT_SHAKE_SMALL,
    EffectBG_EFFECT_SHAKE_LARGE,

    EffectBG_EFFECT_NUM,

    EffectBG_EFFECT_CUT_RIGHT_PALM = EffectBG_EFFECT_NUM,
    EffectBG_EFFECT_CUT_RIGHT_CEDAR,
    EffectBG_EFFECT_CUT_RIGHT_GOLD
};

enum {
    EffectBG_VARIANT_TREE_SMALL = -1,
    EffectBG_VARIANT_TREE_MED,
    EffectBG_VARIANT_TREE_LARGE,
    EffectBG_VARIANT_TREE_FULL,
    
    EffectBG_VARIANT_NUM,
    EffectBG_VARIANT_TREE_XMAS = EffectBG_VARIANT_NUM,
    EffectBG_VARIANT_PALM_SMALL,
    EffectBG_VARIANT_PALM_MED,
    EffectBG_VARIANT_PALM_LARGE,
    EffectBG_VARIANT_PALM_FULL,
    EffectBG_VARIANT_CEDAR_SMALL,
    EffectBG_VARIANT_CEDAR_MED,
    EffectBG_VARIANT_CEDAR_LARGE,
    EffectBG_VARIANT_CEDAR_FULL,
    EffectBG_VARIANT_CEDAR_XMAS,
    EffectBG_VARIANT_GOLD_SMALL,
    EffectBG_VARIANT_GOLD_MED,
    EffectBG_VARIANT_GOLD_LARGE,
    EffectBG_VARIANT_GOLD_FULL,

    EffectBG_VARIANT_ALL
};

typedef void (*EffectBG_MAKE_EFFECTBG_PROC)(GAME*, s16, s16, xyz_t*);

typedef struct effectbg_entry_s {
    cKF_SkeletonInfo_R_c keyframe;
    N64Mtx mtx[2][EffectBg_JOINT_ALL];
    xyz_t base_pos;
    xyz_t effect_pos;
    s_xyz work[EffectBg_JOINT_NUM];
    s_xyz morph[EffectBg_JOINT_NUM];
    s16 timer;
    s16 timer_max;
    s16 type;
    s16 variant;
    s16 add_angle;
    s16 leaf_angle;
    f32 timer_accum;
    u8 status;
    int block_ux;
    int block_uz;
} EffectBg_c;

typedef struct effectbg_actor_s EFFECTBG_ACTOR;

struct effectbg_actor_s {
    ACTOR actor_class;
    int _174;
    EffectBg_c effect[EffectBg_ENTRY_NUM];
    int _CE8;
    u16* tree_pal;
    u16* palm_pal;
    u16* palm_pal2;
    u16* gold_pal;
    int _CFC;
};

extern ACTOR_PROFILE Effectbg_Profile;

#ifdef __cplusplus
}
#endif

#endif
