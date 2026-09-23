#ifndef M_HAND_OVL_H_H
#define M_HAND_OVL_H_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hand_ovl_s mHD_Ovl_c;

#ifdef MOUSE_INPUT
extern void mHD_mouse_pointer_get_offset(f32* x, f32* y);
#endif

#ifdef __cplusplus
}
#endif

#endif
