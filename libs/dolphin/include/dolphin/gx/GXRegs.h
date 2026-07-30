#ifndef _DOLPHIN_GXREGS
#define _DOLPHIN_GXREGS

#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif

extern u16 *__memReg;
extern u16 *__peReg;
extern u16 *__cpReg;
extern u32 *__piReg;

#define GX_GET_CP_REG(offset)  (*(volatile u16*)((__cpReg) + (offset)))
#define GX_SET_CP_REG(offset, value) ((*(volatile u16*)((__cpReg) + (offset))) = (value))

inline u32 __GXReadCPCounterU32(u32 regAddrL, u32 regAddrH)
{
	u32 ctrH0;
    u32 ctrH1;
    u32 ctrL;

	ctrH0 = GX_GET_CP_REG(regAddrH);
	while (TRUE) {
		ctrH1 = ctrH0;
		ctrL  = GX_GET_CP_REG(regAddrL);
		ctrH0 = GX_GET_CP_REG(regAddrH);

        if (ctrH0 == ctrH1) {
            break;
        }
	}

	return (ctrH0 << 16) | (ctrL);
}

#ifdef __cplusplus
}
#endif

#endif
