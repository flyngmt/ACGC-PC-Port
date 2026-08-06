#ifndef PC_TRACY_H
#define PC_TRACY_H

#ifdef TARGET_PC
#include <tracy/TracyC.h>
#else
#define TracyCZone(ctx, active)
#define TracyCZoneN(ctx, name, active)
#define TracyCZoneEnd(ctx)
#define TracyCZoneName(ctx, name, size)
#define TracyCFrameMark
#define TracyCFrameMarkStart(name)
#define TracyCFrameMarkEnd(name)
#endif

#endif
