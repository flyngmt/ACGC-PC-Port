/* This file is fabriacted. These structs are in a unified file in N64 SDK. */

#ifndef OS_CONT_PAD
#define OS_CONT_PAD

#include "types.h"
#include "libultra/os_pfs.h"
#include "dolphin/os/OSMessage.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAXCONTROLLERS 4

/* controller errors */
#define CONT_NO_ERROR 0
#define CONT_NO_RESPONSE_ERROR 0x8
#define CONT_OVERRUN_ERROR 0x4
#define CONT_RANGE_ERROR -1

/* Controller type */
#define CONT_NONE 0x0000
#define CONT_ABSOLUTE 0x0001
#define CONT_RELATIVE 0x0002
#define CONT_JOYPORT 0x0004
#define CONT_EEPROM 0x8000
#define CONT_EEP16K 0x4000
#define CONT_TYPE_MASK 0x1f07
#define CONT_TYPE_NORMAL 0x0005
#define CONT_TYPE_MOUSE 0x0002
#define CONT_TYPE_VOICE 0x0100

/* Controller status */

#define CONT_CARD_ON 0x01
#define CONT_CARD_PULL 0x02
#define CONT_ADDR_CRC_ER 0x04
#define CONT_EEPROM_BUSY 0x80

/* Controller error number */

#define CONT_ERR_NO_CONTROLLER PFS_ERR_NOPACK /* 1 */
#define CONT_ERR_CONTRFAIL CONT_OVERRUN_ERROR /* 4 */
#define CONT_ERR_INVALID PFS_ERR_INVALID      /* 5 */
#define CONT_ERR_DEVICE PFS_ERR_DEVICE        /* 11 */
#define CONT_ERR_NOT_READY 12
#define CONT_ERR_VOICE_MEMORY 13
#define CONT_ERR_VOICE_WORD 14
#define CONT_ERR_VOICE_NO_RESPONSE 15

#ifdef TARGET_PC
/* 'errno' is a macro on POSIX (from <errno.h>). Permanently undefine it so
 * the struct field named 'errno' works. Game code never uses C errno. */
#ifdef errno
#undef errno
#endif
typedef struct {
    u16 type;
    u8 status;
    u8 errno;
} OSContStatus;

typedef struct {
    /* 0x00 */ u16 button;
    /* 0x02 */ s8 stick_x;
    /* 0x03 */ s8 stick_y;
    /* 0x04 */ u8 errno;
} OSContPad;
#else

typedef struct {
    u16 type;
    u8 status;
    u8 errno;
} OSContStatus;

/* sizeof(OSContPad) == 6 */
typedef struct {
    /* 0x00 */ u16 button;
    /* 0x02 */ s8 stick_x;
    /* 0x03 */ s8 stick_y;
    /* 0x04 */ u8 errno;
} OSContPad;

#endif

typedef struct {
    OSContPad pad;
    s8 substickX;
    s8 substickY;
    u8 triggerR;
    u8 triggerL;
} OSContPadEx;

extern s32 osContInit(OSMessageQueue* mq, u8* pattern_p, OSContStatus* status);
extern s32 osContStartQuery(OSMessageQueue* mq);
extern s32 osContStartReadData(OSMessageQueue* mq);
extern void osContGetQuery(OSContStatus* status);
extern s32 osContSetCh(u8 num_controllers);
extern void osContGetReadData(OSContPad* pad);
extern void osContGetReadDataEx(OSContPadEx* pad);

#ifdef __cplusplus
}
#endif

#endif
