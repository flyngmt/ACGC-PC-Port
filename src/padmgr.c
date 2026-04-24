#include "padmgr.h"

#include "libultra/libultra.h"
#include "m_debug.h"
#include "jsyswrap.h"

#ifdef TARGET_PC
#include "dolphin/pad.h"
#endif

static int frame = 0;
padmgr padmgr_class;
static padmgr* this = &padmgr_class;

extern OSMessageQueue* padmgr_LockSerialMesgQ(void) {
    OSMessageQueue* mq;

    osRecvMesg(&this->serial_mq, (OSMesg)&mq, OS_MESG_BLOCK);
    return mq;
}

extern void padmgr_UnlockSerialMesgQ(OSMessageQueue* mq) {
    osSendMesg(&this->serial_mq, (OSMesg)mq, OS_MESG_BLOCK);
}

static void padmgr_LockContData(void) {
    osRecvMesg(&this->controller_lock_mq, NULL, OS_MESG_BLOCK);
}

static void padmgr_UnlockContData(void) {
    osSendMesg(&this->controller_lock_mq, (OSMesg)NULL, OS_MESG_BLOCK);
}

static void padmgr_RumbleControl(void) {
    Motor_t* motor = this->rumble.motors;
    int i;

    for (i = 0; i < PAD_MAX_CONTROLLERS; i++) {
        if (this->device_type[i] == PADMGR_TYPE_CONTROLLER && this->rumble.cooldown_frames == 0) {
            if (motor->last_command != motor->now_command) {
                if (motor->now_command == PAD_MOTOR_STOP) {
                    motor->frames = 3;
                } else {
                    motor->frames = 0;
                }

                PADControlMotor(i, motor->now_command);
                motor->last_command = motor->now_command;
            } else {
                if (motor->frames != 0) {
                    motor->frames--;
                }

                if (motor->frames != 0) {
                    PADControlMotor(i, PAD_MOTOR_STOP);
                }
            }
        }

        motor++;
    }
}

static void padmgr_RumbleStop(void) {
    static u32 stop_command[PAD_MAX_CONTROLLERS] = { PAD_MOTOR_STOP, PAD_MOTOR_STOP, PAD_MOTOR_STOP, PAD_MOTOR_STOP };
    int i;

    PADControlAllMotors(stop_command);
    for (i = 0; i < PAD_MAX_CONTROLLERS; i++) {
        this->rumble.motors[i].last_command = PAD_MOTOR_STOP;
        this->rumble.motors[i].now_command = PAD_MOTOR_STOP;
        this->rumble.motors[i].frames = 0;
    }
}

extern void padmgr_force_stop_ON(void) {
    this->rumble.cooldown_frames = 4;
}

extern void padmgr_force_stop_OFF(void) {
    this->rumble.cooldown_frames = 0;
}

extern void padmgr_RumbleReset(void) {
    this->rumble.cooldown_frames = -3;
}

extern void padmgr_RumbleSet(int pad, int command) {
    this->rumble.motors[pad].now_command = command;
    if (command != PAD_MOTOR_RUMBLE) {
        this->rumble.rumble_frames = 240;
    }
}

static void padmgr_PakConnectCheck(void) {
    static int padno = 0;
    int i;

    for (i = 0; i < this->num_controllers; i++) {
        padno = (padno + 1) % this->num_controllers;
        if (this->device_type[padno] == PADMGR_TYPE_CONTROLLER) {
            if (this->pak_type[padno] != PADMGR_PAK_NONE) {
                u8 status = this->pad_status[padno].status;

                if ((status & CONT_CARD_PULL) != 0 || (status & CONT_CARD_ON) == 0) {
                    this->pak_type[padno] = PADMGR_PAK_NONE;
                }
            }

            if (this->pak_type[padno] == PADMGR_PAK_NONE && (this->pad_status[padno].status & CONT_CARD_ON) != 0) {
                this->pak_type[padno] = PADMGR_PAK_UNK;
            }
            break;
        }
    }
}

static void padmgr_HandleDoneReadPadMsg(void) {
    pad_t* pad = this->pads;
    OSContPad* cur_pad = this->cur_pads;
    int now;
    int trigger;
    int i;

    for (i = 0; i < this->num_controllers; i++) {
        pad->last = pad->now;
        if (this->device_type[i] == PADMGR_TYPE_CONTROLLER) {
            switch (cur_pad->errno) {
                case CONT_NO_ERROR:
                    pad->now = *cur_pad;
                    if (this->device_type[i] == PADMGR_TYPE_NONE) {
                        this->device_type[i] = PADMGR_TYPE_CONTROLLER;
                    }
                    break;
                case CONT_OVERRUN_ERROR:
                    pad->now = pad->last;
                    break;
                case CONT_NO_RESPONSE_ERROR:
                    pad->now.button = 0;
                    pad->now.stick_x = 0;
                    pad->now.stick_y = 0;
                    pad->now.errno = cur_pad->errno;
                    if (this->device_type[i] != PADMGR_TYPE_NONE) {
                        this->device_type[i] = PADMGR_TYPE_NONE;
                        this->pak_type[i] = PADMGR_PAK_NONE;
                    }
                    break;
            }
        } else {
            pad->now.button = 0;
            pad->now.stick_x = 0;
            pad->now.stick_y = 0;
            pad->now.errno = cur_pad->errno;
        }

        /* Update buttons */
        trigger = pad->last.button ^ pad->now.button;
        trigger |= GETREG(SREG, 16 + i);
        pad->on.button |= (u16)(trigger & pad->now.button);
        pad->off.button |= (u16)(trigger & pad->last.button);

        /* Update stick values */
        pad_correct_stick(pad);
        pad->on.stick_x += (s8)(pad->now.stick_x - pad->last.stick_x);
        pad->on.stick_y += (s8)(pad->now.stick_y - pad->last.stick_y);

        pad++;
        cur_pad++;
    }
}

static void padmgr_ConnectCheck(void) {
    int pattern = 0;
    int i;

    for (i = 0; i < this->num_controllers; i++) {
        if (this->pad_status[i].errno == CONT_NO_ERROR) {
            int masked_type = this->pad_status[i].type & CONT_TYPE_MASK;

            switch (masked_type) {
                case CONT_TYPE_NORMAL:
                    pattern |= 1 << i;
                    if (this->device_type[i] == PADMGR_TYPE_NONE) {
                        this->device_type[i] = PADMGR_TYPE_CONTROLLER;
                    }
                    break;
                case CONT_TYPE_MOUSE:
                    if (this->device_type[i] == PADMGR_TYPE_NONE) {
                        this->device_type[i] = PADMGR_TYPE_MOUSE;
                    }
                    break;
                case CONT_TYPE_VOICE:
                    if (this->device_type[i] == PADMGR_TYPE_NONE) {
                        this->device_type[i] = PADMGR_TYPE_VOICE_UNINTIALIZED;
                        this->pak_type[i] = PADMGR_PAK_NONE;
                    }
                    break;
                default:
                    if (this->device_type[i] == PADMGR_TYPE_NONE) {
                        this->device_type[i] = PADMGR_TYPE_UNK;
                    }
                    break;
            }
        } else {
            if (this->device_type[i] != PADMGR_TYPE_NONE) {
                if (this->device_type[i] == PADMGR_TYPE_CONTROLLER) {
                    this->pak_type[i] = PADMGR_PAK_NONE;
                }

                this->device_type[i] = PADMGR_TYPE_NONE;
            }
        }
    }

    this->pad_pattern = pattern;
}

static void padmgr_HandleRetraceMsg(void) {
    OSMessageQueue* serial_mq;

    serial_mq = padmgr_LockSerialMesgQ();
    osContStartReadData(serial_mq);

    if (this->callback != NULL) {
        (*this->callback)(this->callback_param);
    }

    osRecvMesg(serial_mq, NULL, OS_MESG_BLOCK);
    osContGetReadData(this->cur_pads);

    if (this->rumble.reset) {
        bzero(this->cur_pads, sizeof(this->cur_pads));
    }

    osContStartQuery(serial_mq);
    osRecvMesg(serial_mq, NULL, OS_MESG_BLOCK);
    osContGetQuery(this->pad_status);

    padmgr_UnlockSerialMesgQ(serial_mq);

    padmgr_ConnectCheck();
    padmgr_LockContData();
    padmgr_HandleDoneReadPadMsg();

    if (this->callback2 != NULL) {
        (*this->callback2)(this->callback2_param);
    }

    padmgr_UnlockContData();

    if (this->rumble.cooldown_frames != 0) {
        if (this->rumble.cooldown_frames > 1) {
            this->rumble.cooldown_frames--;
            padmgr_RumbleStop();
        } else if (this->rumble.cooldown_frames < 0) {
            this->rumble.cooldown_frames++;
            padmgr_RumbleStop();
        }
    } else if (this->rumble.rumble_frames == 0) {
        padmgr_RumbleStop();
    } else if (this->rumble.reset == FALSE) {
        padmgr_RumbleControl();
        this->rumble.rumble_frames--;
    }

    serial_mq = padmgr_LockSerialMesgQ();
    padmgr_PakConnectCheck();
    padmgr_UnlockSerialMesgQ(serial_mq);
    frame++;
}

static void padmgr_HandlePreNMIMsg(void) {
    this->rumble.reset = TRUE;
    padmgr_RumbleReset();
}

extern void padmgr_RequestPadData_NonLock(pad_t* pad, int flag) {
    int i;
    pad_t* padmgr_pad = this->pads;
    pad_t* pad_p = pad;
    int trigger;

    for (i = 0; i < this->num_controllers; i++) {
        if (flag) {
            /* Direct copy from padmgr */
            *pad_p = *padmgr_pad;
            padmgr_pad->on.button = 0;
            padmgr_pad->on.stick_x = 0;
            padmgr_pad->on.stick_y = 0;
            padmgr_pad->off.button = 0;
        } else {
            /* Only copy now from padmgr and update all other info from that */
            pad_p->last = pad_p->now;
            pad_p->now = padmgr_pad->now;
            trigger = pad_p->last.button ^ pad_p->now.button;
            pad_p->on.button = trigger & pad_p->now.button;
            pad_p->off.button = trigger & pad_p->last.button;
            pad_correct_stick(pad_p);
            pad_p->on.stick_x += (s8)(pad_p->now.stick_x - pad_p->last.stick_x);
            pad_p->on.stick_y += (s8)(pad_p->now.stick_y - pad_p->last.stick_y);
        }

        padmgr_pad++;
        pad_p++;
    }
}

#ifdef TARGET_PC
/* On PC, the padmgr thread doesn't run (osStartThread is a no-op).
   Poll input once per frame, then let all callers read the accumulated triggers.
   On GC, the padmgr thread polls asynchronously and accumulates triggers between reads.
   On PC, inline polling means a second call within the same frame sees no state change
   (XOR of same button state = 0), producing zero triggers. The once-per-frame guard
   is in padmgr_RequestPadData to skip redundant calls entirely. */
extern u32 pc_frame_counter; /* incremented in VIWaitForRetrace */

static void padmgr_UpdatePC(void) {
    PADStatus pad_status[MAXCONTROLLERS];
    int i;

    JW_JUTGamePad_read();
    PADRead(pad_status);

    /* Convert PADStatus (GC format) to OSContPad (N64 format).
       PADRead returns GC button masks; the game uses N64-style button constants.
       GC PAD bits:  A=0x0100 B=0x0200 X=0x0400 Y=0x0800 START=0x1000
                     Z=0x0010 R=0x0020 L=0x0040
                     DUp=0x0008 DDown=0x0004 DLeft=0x0001 DRight=0x0002
       N64 OSContPad: A=0x8000 B=0x4000 Z=0x2000 START=0x1000
                     L=0x0020 R=0x0010 X=0x0040 Y=0x0080
                     DUp=0x0800 DDown=0x0400 DLeft=0x0200 DRight=0x0100
                     CUp=0x0008 CDown=0x0004 CLeft=0x0002 CRight=0x0001 */
    for (i = 0; i < MAXCONTROLLERS; i++) {
        u16 gc = pad_status[i].button;
        u16 n64 = 0;
        if (gc & 0x0100) n64 |= 0x8000; /* A */
        if (gc & 0x0200) n64 |= 0x4000; /* B */
        if (gc & 0x0400) n64 |= 0x0040; /* X */
        if (gc & 0x0800) n64 |= 0x0080; /* Y */
        if (gc & 0x1000) n64 |= 0x1000; /* START */
        if (gc & 0x0010) n64 |= 0x2000; /* Z */
        if (gc & 0x0020) n64 |= 0x0010; /* R */
        if (gc & 0x0040) n64 |= 0x0020; /* L */
        if (gc & 0x0008) n64 |= 0x0800; /* D-Up */
        if (gc & 0x0004) n64 |= 0x0400; /* D-Down */
        if (gc & 0x0001) n64 |= 0x0200; /* D-Left */
        if (gc & 0x0002) n64 |= 0x0100; /* D-Right */
        if (pad_status[i].substickX >= 29)  n64 |= 0x0001; /* C-Right */
        if (pad_status[i].substickX <= -29) n64 |= 0x0002; /* C-Left */
        if (pad_status[i].substickY >= 29)  n64 |= 0x0008; /* C-Up */
        if (pad_status[i].substickY <= -29) n64 |= 0x0004; /* C-Down */
        this->cur_pads[i].button = n64;
        this->cur_pads[i].stick_x = pad_status[i].stickX;
        this->cur_pads[i].stick_y = pad_status[i].stickY;
        this->cur_pads[i].errno = 0; /* CONT_NO_ERROR */
    }

    {
        extern int g_pc_paused;
        extern int g_pc_pause_input_drain;
        int suppress = g_pc_paused;
        if (g_pc_pause_input_drain) {
            /* Only buttons gate the drain. Gamepad stick drift could keep
             * cur_pads[].stick_* non-zero indefinitely and lock the player
             * out. Buttons reliably go to 0 on release. */
            int any_button = 0;
            for (i = 0; i < MAXCONTROLLERS; i++) {
                if (this->cur_pads[i].button != 0) { any_button = 1; break; }
            }
            if (any_button) suppress = 1;
            else            g_pc_pause_input_drain = 0;
        }
        if (suppress) {
            for (i = 0; i < MAXCONTROLLERS; i++) {
                this->cur_pads[i].button = 0;
                this->cur_pads[i].stick_x = 0;
                this->cur_pads[i].stick_y = 0;
            }
        }
    }

    /* Always report PAD0 as connected (keyboard is always available) */
    this->device_type[0] = PADMGR_TYPE_CONTROLLER;

    /* Process cur_pads into pads (button triggers, stick deltas, etc.) */
    padmgr_HandleDoneReadPadMsg();
}
#endif

extern void padmgr_RequestPadData(pad_t* pad, int flag) {
    padmgr_LockContData();
#ifdef TARGET_PC
    /* On GC, the padmgr thread runs asynchronously and accumulates triggers between
       reads. padmgr_RequestPadData can be called multiple times per frame (e.g. from
       graph_main and play_main) and each call gets the accumulated triggers.
       On PC, we poll inline, so the second call would see no state change and overwrite
       the game's pads with zero triggers. Fix: only do the full poll+copy once per frame.
       Subsequent calls within the same frame are no-ops since game->pads already has
       the correct data from the first call. */
    {
        static u32 last_request_frame = 0xFFFFFFFF;
        if (last_request_frame == pc_frame_counter) {
            padmgr_UnlockContData();
            return;
        }
        last_request_frame = pc_frame_counter;
    }
    padmgr_UpdatePC();
#endif
    padmgr_RequestPadData_NonLock(pad, flag);
    padmgr_UnlockContData();
}

extern void padmgr_ClearPadData(pad_t* pad) {
    int i;

    for (i = 0; i < this->num_controllers; i++) {
        pad->last = pad->now;
        pad->now.button = 0;
        pad->now.stick_x = 0;
        pad->now.stick_y = 0;
        pad->on = pad->now;
        pad->off = pad->now;

        pad++;
    }
}

static void padmgr_MainProc(void* arg) {
    BOOL done = FALSE;
    int flags;

    while (done == FALSE) {
        VIWaitForRetrace();
        flags = PADMGR_FLAG_HANDLE_RETRACE;

        while (flags != 0) {
            if ((flags & PADMGR_FLAG_DONE) != 0) {
                flags &= ~PADMGR_FLAG_DONE;
                done = TRUE;
            } else if ((flags & PADMGR_FLAG_HANDLE_PRENMI) != 0) {
                flags &= ~PADMGR_FLAG_HANDLE_PRENMI;
                padmgr_HandlePreNMIMsg();
            } else if ((flags & PADMGR_FLAG_HANDLE_RETRACE) != 0) {
                flags &= ~PADMGR_FLAG_HANDLE_RETRACE;
                padmgr_HandleRetraceMsg();
            }
        }
    }
}

extern void padmgr_Init(OSMessageQueue* mq) {
    bzero(this, sizeof(padmgr));
    osCreateMesgQueue(&this->serial_mq, &this->_msg24, 1);
    padmgr_UnlockSerialMesgQ(mq);
    osCreateMesgQueue(&this->controller_lock_mq, &this->_msg28, 1);
    padmgr_UnlockContData();
    osContInit(mq, &this->pad_pattern, this->pad_status);
    this->num_controllers = MAXCONTROLLERS;
    osContSetCh(this->num_controllers);
}

extern void padmgr_Create(OSMessageQueue* serial_mq, OSId id, OSPri priority, void* stackend, size_t stack_size) {
    padmgr_Init(serial_mq);
    osCreateMesgQueue(&this->_msgQueue8C, this->_msgBuf2C, PADMSGBUFCNT);
    osCreateThread2(&this->thread, id, &padmgr_MainProc, this, stackend, stack_size, priority);
    osStartThread(&this->thread);
}

extern int padmgr_isConnectedController(int idx) {
    if (this->device_type[idx] == PADMGR_TYPE_CONTROLLER) {
        return TRUE;
    }

    return FALSE;
}
