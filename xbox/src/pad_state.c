#include "pad_state.h"
#include <string.h>
static signed char axis(int raw,int center) {
    int value=(raw-center)*127/32767;
    if(value>127) value=127;
    if(value< -127) value= -127;
    return (signed char)value;
}
void ac_pad_update(ACPadState* state,int connected,int fresh,const struct ACNativeInput* sample) {
    if(!connected) { memset(state,0,sizeof(*state)); return; }
    if(!state->connected) { memset(state,0,sizeof(*state)); state->connected=1; }
    if(fresh && sample) {
        state->cached=*sample; state->valid=1;
        if(state->recalibrate) {
            state->center[0]=sample->left_x; state->center[1]=sample->left_y;
            state->center[2]=sample->right_x; state->center[3]=sample->right_y;
            state->recalibrate=0;
        }
    }
}
void ac_pad_recalibrate(ACPadState* state) {
    if(state->connected) { state->recalibrate=1; state->valid=0; }
}
void ac_pad_status(const ACPadState* state,ACPadStatus* out) {
    memset(out,0,sizeof(*out));
    out->error=!state->connected ? -1 : !state->valid ? -2 : 0;
    if(out->error) return;
    out->button=state->cached.buttons;
    out->stick_x=axis(state->cached.left_x,state->center[0]);
    out->stick_y=axis(state->cached.left_y,state->center[1]);
    out->sub_x=axis(state->cached.right_x,state->center[2]);
    out->sub_y=axis(state->cached.right_y,state->center[3]);
    out->left=state->cached.left_trigger; out->right=state->cached.right_trigger;
    out->a=(out->button&256) ? 255 : 0; out->b=(out->button&512) ? 255 : 0;
}
