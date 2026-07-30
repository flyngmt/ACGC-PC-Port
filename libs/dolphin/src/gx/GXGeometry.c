#include <stddef.h>
#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <macros.h>

#include "gx/__gx.h"

void __GXSetDirtyState(void)
{
    if (gx->dirtyState & 1) {
        __GXSetSUTexRegs();
    }
    if (gx->dirtyState & 2) {
        __GXUpdateBPMask();
    }
    if (gx->dirtyState & 4) {
        __GXSetGenMode();
    }
    if (gx->dirtyState & 8) {
        __GXSetVCD();
    }
    if (gx->dirtyState & 0x10) {
        __GXSetVAT();
    }
    if (gx->dirtyState & (0x10 | 8)) {
        __GXCalculateVLim();
    }
    gx->dirtyState = 0;
}

void GXBegin(GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts)
{
    ASSERTMSGLINE(346, vtxfmt < GX_MAX_VTXFMT,   "GXBegin: Format Index is out of range");
    ASSERTMSGLINE(347, !__GXinBegin, "GXBegin: called inside another GXBegin/GXEnd");

    if (gx->dirtyState != 0) {
        __GXSetDirtyState();
    }
#if DEBUG
    if (!gx->inDispList) {
        __GXVerifyState(vtxfmt);
    }
    __GXinBegin = 1;
#endif
    if (*(u32 *)&gx->vNumNot == 0) {  // checks both vNumNot and bpSentNot
        __GXSendFlushPrim();
    }
    GX_WRITE_U8(vtxfmt | type);
    GX_WRITE_U16(nverts);
}

void __GXSendFlushPrim(void)
{
    u32 i;
    u32 numD = gx->vNum * gx->vLim;

    GX_WRITE_U8(0x98);
    GX_WRITE_U16(gx->vNum);
    for (i = 0; i < numD; i += 4) {
        GX_WRITE_U32(0);
    }
    gx->bpSentNot = GX_TRUE;
}

void GXSetLineWidth(u8 width, GXTexOffset texOffsets)
{
    CHECK_GXBEGIN(427, "GXSetLineWidth");
    SET_REG_FIELD(428, gx->lpSize, 8, 0, width);
    SET_REG_FIELD(429, gx->lpSize, 3, 16, texOffsets);
    GX_WRITE_RAS_REG(gx->lpSize);
    gx->bpSentNot = GX_FALSE;
}

void GXGetLineWidth(u8 *width, GXTexOffset *texOffsets)
{
    ASSERTMSGLINE(450, width != NULL && texOffsets != NULL, "GXGet*: invalid null pointer");

    *width      = GET_REG_FIELD(gx->lpSize, 8, 0);
    *texOffsets = GET_REG_FIELD(gx->lpSize, 3, 16);
}

void GXSetPointSize(u8 pointSize, GXTexOffset texOffsets)
{
    CHECK_GXBEGIN(471, "GXSetPointSize");
    SET_REG_FIELD(472, gx->lpSize, 8, 8, pointSize);
    SET_REG_FIELD(473, gx->lpSize, 3, 19, texOffsets);
    GX_WRITE_RAS_REG(gx->lpSize);
    gx->bpSentNot = GX_FALSE;
}

void GXGetPointSize(u8 *pointSize, GXTexOffset *texOffsets)
{
    ASSERTMSGLINE(494, pointSize != NULL && texOffsets != NULL, "GXGet*: invalid null pointer");

    *pointSize  = (int)GET_REG_FIELD(gx->lpSize, 8, 8);
    *texOffsets = GET_REG_FIELD(gx->lpSize, 3, 19);
}

void GXEnableTexOffsets(GXTexCoordID coord, u8 line_enable, u8 point_enable)
{
    CHECK_GXBEGIN(516, "GXEnableTexOffsets");

    ASSERTMSGLINE(518, coord < 8, "GXEnableTexOffsets: Invalid coordinate Id");

    SET_REG_FIELD(520, gx->suTs0[coord], 1, 18, line_enable);
    SET_REG_FIELD(521, gx->suTs0[coord], 1, 19, point_enable);
    GX_WRITE_RAS_REG(gx->suTs0[coord]);
    gx->bpSentNot = GX_FALSE;
}

void GXSetCullMode(GXCullMode mode)
{
    GXCullMode hwMode;

    CHECK_GXBEGIN(544, "GXSetCullMode");
    switch (mode) {
    case GX_CULL_FRONT: hwMode = GX_CULL_BACK;  break;
    case GX_CULL_BACK:  hwMode = GX_CULL_FRONT; break;
    default:            hwMode = mode;          break;
    }
    SET_REG_FIELD(552, gx->genMode, 2, 14, hwMode);
    gx->dirtyState |= 4;
}

void GXGetCullMode(GXCullMode *mode)
{
    GXCullMode hwMode = GET_REG_FIELD(gx->genMode, 2, 14);

    switch (hwMode) {
    case GX_CULL_FRONT: *mode = GX_CULL_BACK;  break;
    case GX_CULL_BACK:  *mode = GX_CULL_FRONT; break;
    default:            *mode = hwMode;        break;
    }
}

void GXSetCoPlanar(GXBool enable)
{
    u32 reg;

    CHECK_GXBEGIN(589, "GXSetCoPlanar");

    SET_REG_FIELD(591, gx->genMode, 1, 19, enable);
    reg = 0xFE080000;
    GX_WRITE_RAS_REG(reg);
    GX_WRITE_RAS_REG(gx->genMode);
}

void __GXSetGenMode(void)
{
    GX_WRITE_RAS_REG(gx->genMode);
    gx->bpSentNot = GX_FALSE;
}
