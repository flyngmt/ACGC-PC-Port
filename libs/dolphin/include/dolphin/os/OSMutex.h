#ifndef OS_MUTEX_H
#define OS_MUTEX_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "dolphin/os/OSThread.h"

struct OSMutex
{
    OSThreadQueue queue;
    OSThread *thread; // the current owner
    s32 count;        // lock count
    OSMutexLink link; // for OSThread.queueMutex
};

struct OSCond
{
    OSThreadQueue queue;
};

void OSInitMutex(OSMutex *mutex);
void OSLockMutex(OSMutex *mutex);
void OSUnlockMutex(OSMutex *mutex);
BOOL OSTryLockMutex(OSMutex *mutex);
void OSInitCond(OSCond *cond);
void OSWaitCond(OSCond *cond, OSMutex *mutex);
void OSSignalCond(OSCond *cond);

#ifdef __cplusplus
}
#endif

#endif // DOLPHIN_OSMUTEX_H
