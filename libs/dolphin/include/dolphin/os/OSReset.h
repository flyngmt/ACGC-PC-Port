#ifndef OSRESET_H
#define OSRESET_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define OS_RESETCODE_RESTART 0x80000000

#define OS_RESET_RESTART 0
#define OS_RESET_HOTRESET 1 /* Soft reset */
#define OS_RESET_SHUTDOWN 2

struct OSResetFunctionQueue {
	struct OSResetFunctionInfo* head;
	struct OSResetFunctionInfo* tail;
};

typedef BOOL (*OSResetFunction)(BOOL final);
typedef struct OSResetFunctionInfo OSResetFunctionInfo;

struct OSResetFunctionInfo {
  // public
  OSResetFunction func;
  u32 priority;

  // private
  OSResetFunctionInfo* next;
  OSResetFunctionInfo* prev;
};

u32 OSGetResetCode();
void OSResetSystem(int reset, u32 resetCode, BOOL forceMenu);
BOOL OSGetResetSwitchState();
void OSGetSaveRegion(void** start, void** end);
void OSRegisterResetFunction(OSResetFunctionInfo* info);

#ifdef __cplusplus
}
#endif

#endif
