#include "libultra/libultra.h"
#include "libultra/osContPad.h"
#include "libultra/osMesg.h"
#include "libultra/controller.h"
#include "dolphin/pad.h"
#include "libjsys/jsyswrapper.h"

u8 __osMaxControllers;
int __osContinitialized;

s32 osContInit(OSMessageQueue* mq, u8* p, OSContStatus* s){

    if (__osContinitialized != 0){
        return 0;
    }
    __osContinitialized = 1;
    __osMaxControllers = 4;

    __osContGetInitData(p,s);
    return 0;
}

void __osContGetInitData(u8* p, OSContStatus* s){
    PADStatus npad;
    int i;
    u8 success;
    
    for (i = 0, success = 0; i < __osMaxControllers; i++, s++){
        npad = JC_JUTGamePad_getPadStatus(i);

        if (npad.err == -3) {
            s->error = 0;
        }
        else {
            switch(npad.err){
                case -1:
                s->error = 8;
                break;
                case -2:
                s->error = 8;
                break;
                case -3:
                s->error = 4;
                break;
                default:
                s->error = 0;
                break;
            }
        }
    
        if(s->error == 0){
            s->type = 5;
            s->status = 1;
            success |= 1 << i;
        }
    }

    *p = success;
}
