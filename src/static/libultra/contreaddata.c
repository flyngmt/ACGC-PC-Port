#include "libultra/contreaddata.h"
#include "libultra/osContPad.h"

#include "libultra/controller.h"
#include "libultra/initialize.h"
#include "libultra/osMesg.h"
#include "libultra/libultra.h"
#include <dolphin/os.h>
#include "jsyswrap.h"
#include "m_nmibuf.h"

u8 __osResetKeyStep;
u8 __osResetSwitchPressed;

extern s32 osContStartReadData(OSMessageQueue* mq) {
    JW_JUTGamePad_read();
    osSendMesg(mq, (OSMessage)0, OS_MESG_NOBLOCK);
    return 0;
}

extern void osContGetReadData(OSContPad* pad) {
    OSContPadEx padEx[PAD_MAX_CONTROLLERS];
    u32 i;
    
    osContGetReadDataEx(padEx);
    for (i = 0; i < PAD_MAX_CONTROLLERS; i++) {
        bcopy(&padEx[i].pad, &pad[i], sizeof(OSContPad));
    }
}

extern void osContGetReadDataEx(OSContPadEx* pad) {
    static u16 last_button = 0;
    static u32 reset_t0 = 0;

    PADStatus padStatus[PAD_MAX_CONTROLLERS];
    int resetSwitchState;
    PADStatus* padStatus_p;
    int i;

    if (osShutdown) {
        OSTime time = osGetTime();

        if (
            (osIsEnableShutdown() && OSMicrosecondsToTicks((u64)3000000) + __osShutdownTime < time) ||
            (osIsDisableShutdown() && OSMicrosecondsToTicks((u64)30000000) + osGetDisableShutdownTime() < time)
        ) {
            osShutdownStart(OS_RESET_RESTART);
        }
    }

    JW_getPadStatus(padStatus);
    resetSwitchState = OSGetResetSwitchState();
    if ((__osResetSwitchPressed || resetSwitchState != OS_RESET_RESTART)) {
        if (resetSwitchState != OS_RESET_RESTART) {
            if (!__osResetSwitchPressed) {
                __osResetSwitchPressed = TRUE;
            }
        } else {
            JC_JUTGamePad_recalibrate(0xF0000000); // all controllers
            osShutdown = TRUE;
            __osShutdownTime = osGetTime();
        }
    } 

    if ((APPNMI_ZURUMODE3_GET() || APPNMI_HOTRESET_GET()) && (padStatus[0].err == 0) && (padStatus[0].button & (s16)0xE1EF) == 0 && (padStatus[0].button & (JUT_START | JUT_X | JUT_B)) == (JUT_START | JUT_X | JUT_B)) {
        u32 count = osGetCount();

        if (__osResetKeyStep == 0) {
            __osResetKeyStep = 1;
            reset_t0 = count;
            last_button = padStatus[0].button;
        } else if (__osResetKeyStep == 1) {
            if (padStatus[0].button != last_button) {
                __osResetKeyStep = 0;
            } else if (count - reset_t0 > OSMicrosecondsToTicks((u64)500000)) {
                u16 jut_input;
                
                __osResetKeyStep = 2;
                jut_input = padStatus[0].button & (JUT_Y | JUT_Z);
                if (jut_input == (JUT_Y | JUT_Z)) {
                    osShutdown = 5;
                } else if (jut_input == JUT_Z) {
                    osShutdown = 4;
                } else if (jut_input == JUT_Y) {
                    osShutdown = 3;
                } else {
                    osShutdown = 2;
                }

                if (osShutdown != 0) {
                    __osShutdownTime = osGetTime();
                }
            }
        }
    } else {
        __osResetKeyStep = 0;
    }

    for (i = 0; i < __osMaxControllers; i++, pad++) {
        PADStatus curPad = padStatus[i];

        if (curPad.err == PAD_ERR_TRANSFER) {
            pad->pad.error = 0;
        } else {
            switch (curPad.err) {
                case PAD_ERR_NO_CONTROLLER:
                    pad->pad.error = 8;
                    break;
                case PAD_ERR_NOT_READY:
                    pad->pad.error = 8;
                    break;
                case PAD_ERR_TRANSFER:
                    pad->pad.error = 4;
                    break;
                default:
                    pad->pad.error = 0;
                    break;
            }
        }
        
        if (pad->pad.error == 0) {
            u16 jut_button = curPad.button;
            u16 mask = jut_button & (JUT_START | JUT_X | JUT_B);
            u16 button = 0;

            if ((APPNMI_ZURUMODE3_GET() || APPNMI_HOTRESET_GET()) && mask == (JUT_START | JUT_X | JUT_B)) {
                bzero(pad, sizeof(OSContPadEx));
            } else {
                if (jut_button & JUT_DPAD_LEFT) {
                    button |= BUTTON_DLEFT;
                }

                if (jut_button & JUT_DPAD_RIGHT) {
                    button |= BUTTON_DRIGHT;
                }

                if (jut_button & JUT_DPAD_DOWN) {
                    button |= BUTTON_DDOWN;
                }

                if (jut_button & JUT_DPAD_UP) {
                    button |= BUTTON_DUP;
                }

                if (jut_button & JUT_Z) {
                    button |= BUTTON_Z;
                }

                if ((jut_button & JUT_R) != 0 || curPad.triggerRight) {
                    button |= BUTTON_R;
                }

                if ((jut_button & JUT_L) != 0 || curPad.triggerLeft) {
                    button |= BUTTON_L;
                }

                if (jut_button & JUT_A) {
                    button |= BUTTON_A;
                }

                if (jut_button & JUT_B) {
                    button |= BUTTON_B;
                }

                if (jut_button & JUT_X) {
                    button |= BUTTON_X;
                }

                if (jut_button & JUT_Y) {
                    button |= BUTTON_Y;
                }

                if (jut_button & JUT_START) {
                    button |= BUTTON_START;
                }

                if (curPad.substickX >= 29) {
                    button |= BUTTON_CRIGHT;
                }

                if (curPad.substickX <= -29) {
                    button |= BUTTON_CLEFT;
                }

                if (curPad.substickY >= 29) {
                    button |= BUTTON_CUP;
                }

                if (curPad.substickY <= -29) {
                    button |= BUTTON_CDOWN;
                }

                pad->pad.button = button;
                pad->pad.stick_x = curPad.stickX;
                pad->pad.stick_y = curPad.stickY;
                pad->substickX = curPad.substickX;
                pad->substickY = curPad.substickY;
                pad->triggerL = curPad.triggerLeft;
                pad->triggerR = curPad.triggerRight;
            }
        }
    }
}
