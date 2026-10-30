/* Real SDK input driver bridge; needs libxenon-input.patch, NOT upstream ABI. */
#include "pad_state.h"
#include <input/input.h>
#include <usb/usbmain.h>
extern int ac_usb_controller_connected(unsigned int port);
int ac_pad_usb_poll(unsigned int port,ACPadState* state) {
    struct controller_data_s d;
    struct ACNativeInput sample;
    int connected,fresh;
    if(port>=4 || !state) return -1;
    usb_do_poll();
    connected=ac_usb_controller_connected(port);
    fresh=connected && get_controller_data(&d,(int)port);
    if(fresh) {
        sample.left_x=d.s1_x; sample.left_y=d.s1_y;
        sample.right_x=d.s2_x; sample.right_y=d.s2_y;
        sample.left_trigger=d.lt; sample.right_trigger=d.rt;
        /* Digital shoulder policy: RB=R, LB=Z, full triggers also L/R. */
        sample.buttons=(d.left?1:0)|(d.right?2:0)|(d.down?4:0)|(d.up?8:0)|
            (d.lb?16:0)|((d.rb||d.rt>=240)?32:0)|(d.lt>=240?64:0)|
            (d.a?256:0)|(d.b?512:0)|(d.x?1024:0)|(d.y?2048:0)|(d.start?4096:0);
    }
    ac_pad_update(state,connected,fresh,fresh?&sample:0);
    return connected;
}
