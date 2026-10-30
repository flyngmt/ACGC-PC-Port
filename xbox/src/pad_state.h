#ifndef AC_PAD_STATE_H
#define AC_PAD_STATE_H
#include "native_backend.h"
/* Mapping policy, not a claim of native GameCube electrical calibration.
 * Call only on the USB polling core; disconnect is an actual driver event. */
typedef struct ACPadStatus {
    unsigned short button;
    signed char stick_x,stick_y,sub_x,sub_y;
    unsigned char left,right,a,b;
    signed char error;
} ACPadStatus;
typedef struct ACPadState {
    struct ACNativeInput cached;
    int connected,valid,recalibrate;
    int center[4];
} ACPadState;
void ac_pad_update(ACPadState*,int connected,int fresh,const struct ACNativeInput*);
void ac_pad_recalibrate(ACPadState*);
void ac_pad_status(const ACPadState*,ACPadStatus*);
int ac_pad_usb_poll(unsigned int,ACPadState*);
#endif
