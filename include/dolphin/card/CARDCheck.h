#ifndef _DOLPHIN_CARDCHECK_H_
#define _DOLPHIN_CARDCHECK_H_

s32 CARDCheckAsync(s32 chan, CARDCallback callback);
#ifndef TARGET_PC
long CARDCheck(long chan);
#endif

#endif // _DOLPHIN_CARDCHECK_H_
