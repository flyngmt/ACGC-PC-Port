#ifndef AC_MISIN_H
#define AC_MISIN_H

#include "types.h"
#include "m_actor.h"
#include "m_needlework.h"
#include "c_keyframe.h"
#include "ac_misin_clip.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct misin_actor_s MISIN_ACTOR;

#define aMSN_GetClip() ((aMSN_Clip_c*)Common_Get(clip).misin_clip)

typedef struct misin_dustcloth_s {
    s16 switch_flag;
    s16 frame;
    xyz_t pos;
    xyz_t target_pos;
    int target_idx;
    s16 target_angle_y;
    int moving_flag;
    mNW_original_design_c* original_p;
    u16* palette_p;
#ifdef TARGET_PC
    f32 logic_accum;
#endif
} aMSN_DustCloth_c;

typedef struct misin_misin_s {
    s16 status;
    f32 speed;
    xyz_t pos;
    f32 needle_y_counter;
    xyz_t needle_offset;
    s16 y_scroll;
    cKF_SkeletonInfo_R_c keyframe;
    s_xyz work[17];
    s_xyz morph[17];
    ATTRIBUTE_ALIGN(8) N64Mtx mtx[2][16];
} aMSN_Misin_c;

struct misin_actor_s {
    ACTOR actor_class;
    aMSN_DustCloth_c dustcloth;
    aMSN_Misin_c misin;
    aMSN_Clip_c clip;
};

extern ACTOR_PROFILE Misin_Profile;

#ifdef __cplusplus
}
#endif

#endif
