#ifndef _DOLPHIN_OS_OSMESSAGE_H
#define _DOLPHIN_OS_OSMESSAGE_H

#include "types.h"
#include "dolphin/os/OSUtil.h"
#include "dolphin/os/OSThread.h"

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

///////// MESSAGE TYPES //////////
typedef struct OSMessageQueue OSMessageQueue;

// Useful typedef for messages.
typedef void* OSMessage;

// Struct for managing the message queue.
struct OSMessageQueue {
	OSThreadQueue queueSend;    // _00
	OSThreadQueue queueReceive; // _08
	OSMessage* msgArray;        // _10, array of messages.
	int msgCount;               // _14, array limit size.
	int firstIndex;             // _18, first message index in array.
	int usedCount;              // _1C, actual number of used messages.
};

// Defines for message flags for sending/receiving.
#define OS_MESSAGE_NOBLOCK (0)
#define OS_MESSAGE_BLOCK   (1)

typedef enum {
	OS_MSG_PERSISTENT = (1 << 0),
} OSMessageFlags;

//////////////////////////////////

/////// MESSAGE FUNCTIONS ////////
// Functions for handling messages.
void OSInitMessageQueue(OSMessageQueue* queue, OSMessage* msgArray, int msgCount);
BOOL OSSendMessage(OSMessageQueue* queue, OSMessage msg, int flags);
BOOL OSJamMessage(OSMessageQueue* queue, OSMessage msg, int flags);
BOOL OSReceiveMessage(OSMessageQueue* queue, OSMessage* msgPtr, int flags);

//////////////////////////////////

#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif
