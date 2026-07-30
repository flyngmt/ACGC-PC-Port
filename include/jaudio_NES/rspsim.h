#ifndef RSPSIM_H
#define RSPSIM_H

#include "types.h"

#define RSPSIM_MODE_INIT 0
#define RSPSIM_MODE_MOVE 1

#ifdef __cplusplus
extern "C" {
#endif

extern s32 RspStart(void* pTaskCmds, s32 allTasks);
extern void RspStart2(void* pTaskCmds, s32 allTasks, s32 mode);

#ifdef __cplusplus
}
#endif

#endif
