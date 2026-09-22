#ifndef M_HAND_OVL_H
#define M_HAND_OVL_H

#include "types.h"
#include "m_hand_ovl_h.h"
#include "m_submenu_ovl.h"
#include "c_keyframe.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    mHD_ACTION_SASU,
    mHD_ACTION_SIDE,
    mHD_ACTION_CLOSE,
    mHD_ACTION_CLOSE_KEEP,
    mHD_ACTION_OPEN,
    mHD_ACTION_CLOSE2,
    mHD_ACTION_SASU2,

    mHD_ACTION_NUM
};

enum {
    mHD_MOVE_NONE,
    mHD_MOVE_NORMAL,
    mHD_MOVE_SWITCH_LEFT,
    mHD_MOVE_SWITCH_RIGHT,

    mHD_MOVE_NUM
};

typedef void (*mHD_OVL_NOP_HAND_FUNC)(Submenu*);
typedef void (*mHD_OVL_SET_HAND_FUNC)(Submenu*);

typedef struct hand_info_s {
    int type;
    f32 pos[2];
    f32 ofs[2];
    s16 move_flag;
    s16 wait_timer;
    cKF_SkeletonInfo_R_c keyframe;
    int keyframe_state;
    s_xyz work[29];
    s_xyz morph[29];
    u8 _1E8[72];
    s16 act;
    s16 next_act;
    mActor_name_t item;
    Mail_c mail;
    u32 item_cond;
    u8 hold_tbl;
    u8 hold_idx;
    u8 ret_flag;
    u8 catch_pg;
    s16 haniwa_item_cond;
    u32 haniwa_item_price;
    f32 visual_pos[2]; // Visual position (so mouse follows smoothly)
} mHD_hand_info_c;

/* sizeof(struct hand_ovl_s) == 0x378 */
struct hand_ovl_s {
    mHD_hand_info_c info;
    mHD_OVL_NOP_HAND_FUNC nop_hand_func;
    mHD_OVL_SET_HAND_FUNC set_hand_func;
};

extern void mHD_hand_ovl_construct(Submenu* submenu);
extern void mHD_hand_ovl_destruct(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
