#ifndef M_TIMEIN_OVL_H
#define M_TIMEIN_OVL_H

#include "types.h"
#include "m_timeIn_ovl_h.h"
#include "m_submenu_ovl.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mTI_MIN_YEAR 1
#ifdef TARGET_PC
#define mTI_MAX_YEAR 99
#else
#define mTI_MAX_YEAR 30
#endif

enum {
    mTI_IDX_HOUR,
    mTI_IDX_MIN,
    mTI_IDX_MONTH,
    mTI_IDX_DAY,
    mTI_IDX_YEAR,
    mTI_IDX_OK,

    mTI_IDX_NUM = mTI_IDX_OK
};

enum {
    mTI_OVL_OPEN_NORMAL,
    mTI_OVL_OPEN_INITIAL,

    mTI_OVL_OPEN_NUM
};

struct timeIn_ovl_s {
    u16 values[mTI_IDX_NUM];
    int sel_idx;
    u16 saved_min;
    u16 input_disabled_flag;
    lbRTC_time_c original_time;
    int init_flag;
#ifdef TARGET_PC
    f32 clock_step_accum;
#endif
};

extern void mTI_timeIn_ovl_set_proc(Submenu* submenu);
extern void mTI_timeIn_ovl_construct(Submenu* submenu);
extern void mTI_timeIn_ovl_destruct(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
