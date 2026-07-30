#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <macros.h>

#include "gx/__gx.h"

#define CHECK_ATTRPTR(line, attrPtr) ASSERTMSGLINE(line, (attrPtr) != NULL, "GXSetVtxDescv: attrPtr is NULL")
#define CHECK_ATTRNAME(line, attr)   ASSERTMSGLINE(line, (attr) >= GX_VA_PNMTXIDX && (attr) < GX_VA_MAX_ATTR, "GXSetVtxDesc: Invalid vertex attribute name")
#define CHECK_ATTRNAME2(line, attr)  ASSERTMSGLINE(line, (attr) >= GX_VA_POS && (attr) <= GX_VA_MAX_ATTR, "GXSetVtxAttrFmt: Invalid vertex attribute name")
#define CHECK_ATTRNAME3(line, attr)  ASSERTMSGLINE(line, (attr) >= GX_VA_POS && (attr) <= GX_LIGHT_ARRAY, "GXSetArray: Invalid vertex attribute name")
#define CHECK_ATTRTYPE(line, type)   ASSERTMSGLINE(line, (type) >= GX_NONE && (type) <= GX_INDEX16, "GXSetVtxDesc: Invalid vertex attribute type")
#define CHECK_VTXFMT(line, vtxfmt)   ASSERTMSGLINE(line, (vtxfmt) < GX_MAX_VTXFMT, "GXSetVtxAttrFmt: Format Index is out of range")
#define CHECK_FRAC(line, frac)       ASSERTMSGLINE(line, (frac) < 32, "GXSetVtxAttrFmt: Frac value is >= 32")
#define CHECK_LISTPTR(line, list)    ASSERTMSGLINE(line, (list) != NULL, "GXSetVtxAttrFmt: list pointer is NULL")

static void __GXXfVtxSpecs(void)
{
    u32 nCols = 0;
    u32 nNrm;
    u32 nTex;
    u32 reg;

    nCols = GET_REG_FIELD(gx->vcdLo, 2, 13) ? 1 : 0;
    nCols += GET_REG_FIELD(gx->vcdLo, 2, 15) ? 1 : 0;
    nNrm = gx->hasBiNrms ? 2 : gx->hasNrms ? 1 : 0;
    nTex = 0;
    nTex += GET_REG_FIELD(gx->vcdHi, 2, 0) ? 1 : 0;
    nTex += GET_REG_FIELD(gx->vcdHi, 2, 2) ? 1 : 0;
    nTex += GET_REG_FIELD(gx->vcdHi, 2, 4) ? 1 : 0;
    nTex += GET_REG_FIELD(gx->vcdHi, 2, 6) ? 1 : 0;
    nTex += GET_REG_FIELD(gx->vcdHi, 2, 8) ? 1 : 0;
    nTex += GET_REG_FIELD(gx->vcdHi, 2, 10) ? 1 : 0;
    nTex += GET_REG_FIELD(gx->vcdHi, 2, 12) ? 1 : 0;
    nTex += GET_REG_FIELD(gx->vcdHi, 2, 14) ? 1 : 0;
    reg = (nCols) | (nNrm << 2) | (nTex << 4);
    GX_WRITE_XF_REG(8, reg);
    gx->bpSentNot = 1;
}

static inline void SETVCDATTR(GXAttr Attr, GXAttrType Type)
{
    switch (Attr) {
    case GX_VA_PNMTXIDX:   SET_REG_FIELD(0xAE, gx->vcdLo, 1, 0, Type); break;
    case GX_VA_TEX0MTXIDX: SET_REG_FIELD(0xAF, gx->vcdLo, 1, 1, Type); break;
    case GX_VA_TEX1MTXIDX: SET_REG_FIELD(0xB0, gx->vcdLo, 1, 2, Type); break;
    case GX_VA_TEX2MTXIDX: SET_REG_FIELD(0xB1, gx->vcdLo, 1, 3, Type); break;
    case GX_VA_TEX3MTXIDX: SET_REG_FIELD(0xB2, gx->vcdLo, 1, 4, Type); break;
    case GX_VA_TEX4MTXIDX: SET_REG_FIELD(0xB3, gx->vcdLo, 1, 5, Type); break;
    case GX_VA_TEX5MTXIDX: SET_REG_FIELD(0xB4, gx->vcdLo, 1, 6, Type); break;
    case GX_VA_TEX6MTXIDX: SET_REG_FIELD(0xB5, gx->vcdLo, 1, 7, Type); break;
    case GX_VA_TEX7MTXIDX: SET_REG_FIELD(0xB6, gx->vcdLo, 1, 8, Type); break;
    case GX_VA_POS:        SET_REG_FIELD(0xB7, gx->vcdLo, 2, 9, Type); break;
    case GX_VA_NRM:
        if (Type != GX_NONE) {
            gx->hasNrms = GX_TRUE;
            gx->hasBiNrms = GX_FALSE;
            gx->nrmType = Type;
        } else {
            gx->hasNrms = GX_FALSE;
        }
        break;
    case GX_VA_NBT:
        if (Type != GX_NONE) {
            gx->hasBiNrms = GX_TRUE;
            gx->hasNrms = GX_FALSE;
            gx->nrmType = Type;
        } else {
            gx->hasBiNrms = GX_FALSE;
        }
        break;
    case GX_VA_CLR0: SET_REG_FIELD(0xD0, gx->vcdLo, 2, 13, Type); break;
    case GX_VA_CLR1: SET_REG_FIELD(0xD1, gx->vcdLo, 2, 15, Type); break;
    case GX_VA_TEX0: SET_REG_FIELD(0xD2, gx->vcdHi, 2, 0, Type); break;
    case GX_VA_TEX1: SET_REG_FIELD(0xD3, gx->vcdHi, 2, 2, Type); break;
    case GX_VA_TEX2: SET_REG_FIELD(0xD4, gx->vcdHi, 2, 4, Type); break;
    case GX_VA_TEX3: SET_REG_FIELD(0xD5, gx->vcdHi, 2, 6, Type); break;
    case GX_VA_TEX4: SET_REG_FIELD(0xD6, gx->vcdHi, 2, 8, Type); break;
    case GX_VA_TEX5: SET_REG_FIELD(0xD7, gx->vcdHi, 2, 10, Type); break;
    case GX_VA_TEX6: SET_REG_FIELD(0xD8, gx->vcdHi, 2, 12, Type); break;
    case GX_VA_TEX7: SET_REG_FIELD(0xD9, gx->vcdHi, 2, 14, Type); break;
    }
}

void GXSetVtxDesc(GXAttr attr, GXAttrType type)
{
    CHECK_GXBEGIN(226, "GXSetVtxDesc");
    CHECK_ATTRNAME(229, attr);
    CHECK_ATTRTYPE(231, type);

    SETVCDATTR(attr, type);
    if (gx->hasNrms || gx->hasBiNrms) {
        SET_REG_FIELD(0xED, gx->vcdLo, 2, 11, gx->nrmType);
    } else {
        SET_REG_FIELD(0x00, gx->vcdLo, 2, 11, 0);
    }
    gx->dirtyState |= 8;
}

void GXSetVtxDescv(const GXVtxDescList *attrPtr)
{
    CHECK_GXBEGIN(267, "GXSetVtxDescv");
    CHECK_ATTRPTR(268, attrPtr);
    while (attrPtr->attr != 0xFF) {
        CHECK_ATTRNAME(273, attrPtr->attr);
        CHECK_ATTRTYPE(276, attrPtr->type);
        SETVCDATTR(attrPtr->attr, attrPtr->type);
        attrPtr++;
    }
    if (gx->hasNrms || gx->hasBiNrms) {
        SET_REG_FIELD(285, gx->vcdLo, 2, 11, gx->nrmType);
    } else {
        SET_REG_FIELD(285, gx->vcdLo, 2, 11, 0);
    }
    gx->dirtyState |= 8;
}

void __GXSetVCD(void)
{
    GX_WRITE_SOME_REG4(8, 0x50, gx->vcdLo, -12);
    GX_WRITE_SOME_REG4(8, 0x60, gx->vcdHi, -12);
    __GXXfVtxSpecs();
}

void __GXCalculateVLim(void) {
    static u8 tbl1[] = { 0, 4, 1, 2 };
    static u8 tbl2[] = { 0, 8, 1, 2 };
    static u8 tbl3[] = { 0, 12, 1, 2 };
    unsigned long vlm;
    s32 b;
    unsigned long vl;
    unsigned long vh;

    if (gx->vNum != 0) {
        vl = gx->vcdLo;
        vh = gx->vcdHi;
        vlm  = GET_REG_FIELD(vl, 1, 0);
        vlm += (u8)GET_REG_FIELD(vl, 1, 1);
        vlm += (u8)GET_REG_FIELD(vl, 1, 2);
        vlm += (u8)GET_REG_FIELD(vl, 1, 3);
        vlm += (u8)GET_REG_FIELD(vl, 1, 4);
        vlm += (u8)GET_REG_FIELD(vl, 1, 5);
        vlm += (u8)GET_REG_FIELD(vl, 1, 6);
        vlm += (u8)GET_REG_FIELD(vl, 1, 7);
        vlm += (u8)GET_REG_FIELD(vl, 1, 8);
        
        vlm += tbl3[(u8)GET_REG_FIELD(vl, 2, 9)];
        b = gx->vatA[GX_VTXFMT0];
	    b = (b & 0x200) >> 9;
        vlm += tbl3[(u8)GET_REG_FIELD(vl, 2, 11)] * (b == GX_NRM_NBT ? 3 : 1);
        vlm += tbl1[(u8)GET_REG_FIELD(vl, 2, 13)];
        vlm += tbl1[(u8)GET_REG_FIELD(vl, 2, 15)];

        vlm += tbl2[(u8)GET_REG_FIELD(vh, 2, 0)];
        vlm += tbl2[(u8)GET_REG_FIELD(vh, 2, 2)];
        vlm += tbl2[(u8)GET_REG_FIELD(vh, 2, 4)];
        vlm += tbl2[(u8)GET_REG_FIELD(vh, 2, 6)];
        vlm += tbl2[(u8)GET_REG_FIELD(vh, 2, 8)];
        vlm += tbl2[(u8)GET_REG_FIELD(vh, 2, 10)];
        vlm += tbl2[(u8)GET_REG_FIELD(vh, 2, 12)];
        vlm += tbl2[(u8)GET_REG_FIELD(vh, 2, 14)];
        gx->vLim = vlm;
    }
}

void GXGetVtxDesc(GXAttr attr, GXAttrType *type)
{
    u32 cpType;

    CHECK_GXBEGIN(411, "GXGetVtxDesc");
    CHECK_ATTRNAME(413, attr);

    switch (attr) {
    case GX_VA_PNMTXIDX:   cpType = GET_REG_FIELD(gx->vcdLo, 1, 0); break;
    case GX_VA_TEX0MTXIDX: cpType = GET_REG_FIELD(gx->vcdLo, 1, 1); break;
    case GX_VA_TEX1MTXIDX: cpType = GET_REG_FIELD(gx->vcdLo, 1, 2); break;
    case GX_VA_TEX2MTXIDX: cpType = GET_REG_FIELD(gx->vcdLo, 1, 3); break;
    case GX_VA_TEX3MTXIDX: cpType = GET_REG_FIELD(gx->vcdLo, 1, 4); break;
    case GX_VA_TEX4MTXIDX: cpType = GET_REG_FIELD(gx->vcdLo, 1, 5); break;
    case GX_VA_TEX5MTXIDX: cpType = GET_REG_FIELD(gx->vcdLo, 1, 6); break;
    case GX_VA_TEX6MTXIDX: cpType = GET_REG_FIELD(gx->vcdLo, 1, 7); break;
    case GX_VA_TEX7MTXIDX: cpType = GET_REG_FIELD(gx->vcdLo, 1, 8); break;
    case GX_VA_POS:        cpType = GET_REG_FIELD(gx->vcdLo, 2, 9); break;
    case GX_VA_NRM:        cpType = gx->hasNrms ? GET_REG_FIELD(gx->vcdLo, 2, 11) : 0; break;
    case GX_VA_NBT:        cpType = gx->hasBiNrms ? GET_REG_FIELD(gx->vcdLo, 2, 11) : 0; break;
    case GX_VA_CLR0:       cpType = GET_REG_FIELD(gx->vcdLo, 2, 13); break;
    case GX_VA_CLR1:       cpType = GET_REG_FIELD(gx->vcdLo, 2, 15); break;
    case GX_VA_TEX0:       cpType = GET_REG_FIELD(gx->vcdHi, 2, 0);  break;
    case GX_VA_TEX1:       cpType = GET_REG_FIELD(gx->vcdHi, 2, 2);  break;
    case GX_VA_TEX2:       cpType = GET_REG_FIELD(gx->vcdHi, 2, 4);  break;
    case GX_VA_TEX3:       cpType = GET_REG_FIELD(gx->vcdHi, 2, 6);  break;
    case GX_VA_TEX4:       cpType = GET_REG_FIELD(gx->vcdHi, 2, 8);  break;
    case GX_VA_TEX5:       cpType = GET_REG_FIELD(gx->vcdHi, 2, 10); break;
    case GX_VA_TEX6:       cpType = GET_REG_FIELD(gx->vcdHi, 2, 12); break;
    case GX_VA_TEX7:       cpType = GET_REG_FIELD(gx->vcdHi, 2, 14); break;
    default: cpType = 0; break;
    }
    *type = cpType;
}

void GXGetVtxDescv(GXVtxDescList *vcd)
{
    GXAttr attr;

    CHECK_GXBEGIN(464, "GXGetVtxDescv");
    CHECK_ATTRPTR(466, vcd);
    for (attr = 0; attr < GX_VA_MAX_ATTR; attr++) {
        vcd[attr].attr = attr;
        GXGetVtxDesc(attr, &vcd[attr].type);
    }
    vcd[attr].attr = 0xFF;
}

void GXClearVtxDesc(void)
{
    CHECK_GXBEGIN(489, "GXClearVtxDesc");
    gx->vcdLo = 0;
    SET_REG_FIELD(0x00, gx->vcdLo, 2, 9, 1);
    gx->vcdHi = 0;
    gx->hasNrms = 0;
    gx->hasBiNrms = 0;
    gx->dirtyState |= 8;
}

static inline void SETVAT(u32 *va, u32 *vb, u32 *vc, GXAttr attr, GXCompCnt cnt, GXCompType type, u8 shft)
{
    switch (attr) {
    case GX_VA_POS:
        SET_REG_FIELD(533, *va, 1, 0, cnt);
        SET_REG_FIELD(534, *va, 3, 1, type);
        SET_REG_FIELD(535, *va, 5, 4, shft);
        break;
    case GX_VA_NRM:
    case GX_VA_NBT:
        SET_REG_FIELD(543, *va, 3, 10, type);
        if (cnt == GX_NRM_NBT3) {
            SET_REG_FIELD(0, *va, 1, 9, 1);
            SET_REG_FIELD(0, *va, 1, 31, 1);
        } else {
            SET_REG_FIELD(549, *va, 1, 9, cnt);
            SET_REG_FIELD(50, *va, 1, 31, 0);
        }
        break;
    case GX_VA_CLR0:
        SET_REG_FIELD(555, *va, 1, 13, cnt);
        SET_REG_FIELD(556, *va, 3, 14, type);
        break;
    case GX_VA_CLR1:
        SET_REG_FIELD(559, *va, 1, 0x11, cnt);
        SET_REG_FIELD(560, *va, 3, 18, type);
        break;
    case GX_VA_TEX0:
        SET_REG_FIELD(563, *va, 1, 0x15, cnt);
        SET_REG_FIELD(564, *va, 3, 0x16, type);
        SET_REG_FIELD(565, *va, 5, 0x19, shft);
        break;
    case GX_VA_TEX1:
        SET_REG_FIELD(568, *vb, 1, 0, cnt);
        SET_REG_FIELD(569, *vb, 3, 1, type);
        SET_REG_FIELD(570, *vb, 5, 4, shft);
        break;
    case GX_VA_TEX2:
        SET_REG_FIELD(573, *vb, 1, 9, cnt);
        SET_REG_FIELD(574, *vb, 3, 10, type);
        SET_REG_FIELD(575, *vb, 5, 13, shft);
        break;
    case GX_VA_TEX3:
        SET_REG_FIELD(578, *vb, 1, 18, cnt);
        SET_REG_FIELD(579, *vb, 3, 19, type);
        SET_REG_FIELD(580, *vb, 5, 22, shft);
        break;
    case GX_VA_TEX4:
        SET_REG_FIELD(583, *vb, 1, 27, cnt);
        SET_REG_FIELD(584, *vb, 3, 28, type);
        SET_REG_FIELD(585, *vc, 5, 0, shft);
        break;
    case GX_VA_TEX5:
        SET_REG_FIELD(588, *vc, 1, 5, cnt);
        SET_REG_FIELD(589, *vc, 3, 6, type);
        SET_REG_FIELD(590, *vc, 5, 9, shft);
        break;
    case GX_VA_TEX6:
        SET_REG_FIELD(593, *vc, 1, 14, cnt);
        SET_REG_FIELD(594, *vc, 3, 15, type);
        SET_REG_FIELD(595, *vc, 5, 18, shft);
        break;
    case GX_VA_TEX7:
        SET_REG_FIELD(598, *vc, 1, 23, cnt);
        SET_REG_FIELD(599, *vc, 3, 24, type);
        SET_REG_FIELD(600, *vc, 5, 27, shft);
        break;
    }
}

void GXSetVtxAttrFmt(GXVtxFmt vtxfmt, GXAttr attr, GXCompCnt cnt, GXCompType type, u8 frac)
{
    u32 *va;
    u32 *vb;
    u32 *vc;

    CHECK_GXBEGIN(616, "GXSetVtxAttrFmt");
    CHECK_VTXFMT(617, vtxfmt);
    CHECK_ATTRNAME2(619, attr);
    CHECK_FRAC(620, frac);
    va = &gx->vatA[vtxfmt];
    vb = &gx->vatB[vtxfmt];
    vc = &gx->vatC[vtxfmt];
    SETVAT(va, vb, vc, attr, cnt, type, frac);
    gx->dirtyState |= 0x10;
    gx->dirtyVAT |= (u8)(1 << (u8)vtxfmt);
}

void GXSetVtxAttrFmtv(GXVtxFmt vtxfmt, const GXVtxAttrFmtList *list)
{
    u32 *va;
    u32 *vb;
    u32 *vc;

    CHECK_GXBEGIN(657, "GXSetVtxAttrFmtv");
    CHECK_LISTPTR(658, list);
    CHECK_VTXFMT(659, vtxfmt);
    va = &gx->vatA[vtxfmt];
    vb = &gx->vatB[vtxfmt];
    vc = &gx->vatC[vtxfmt];
    while (list->attr != GX_VA_NULL) {
        CHECK_ATTRNAME2(668, list->attr);
        CHECK_FRAC(669, list->frac);
        SETVAT(va, vb, vc, list->attr, list->cnt, list->type, list->frac);
        list++;
    }
    gx->dirtyState |= 0x10;
    gx->dirtyVAT |= (u8)(1 << (u8)vtxfmt);
}

void __GXSetVAT(void)
{
    u8 i;

    for (i = 0; i < 8; i++) {
        if (gx->dirtyVAT & (1 << (u8)i)) {
            GX_WRITE_SOME_REG4(8, i | 0x70, gx->vatA[i], i - 12);
            GX_WRITE_SOME_REG4(8, i | 0x80, gx->vatB[i], i - 12);
            GX_WRITE_SOME_REG4(8, i | 0x90, gx->vatC[i], i - 12);
        }
    }
    gx->dirtyVAT = 0;
}

void GXGetVtxAttrFmt(GXVtxFmt fmt, GXAttr attr, GXCompCnt *cnt, GXCompType *type, u8 *frac)
{
    u32 *va;
    u32 *vb;
    u32 *vc;

    CHECK_GXBEGIN(741, "GXGetVtxAttrFmt");
    CHECK_VTXFMT(742, fmt);
    va = &gx->vatA[fmt];
    vb = &gx->vatB[fmt];
    vc = &gx->vatC[fmt];
    switch (attr) {
    case GX_VA_POS:
        *cnt  = GET_REG_FIELD(*va, 1, 0);
        *type = GET_REG_FIELD(*va, 3, 1);
        *frac = (u8)(*va >> 4) & 0x1F;  // GET_REG_FIELD(*va, 5, 4)
        return;
    case GX_VA_NRM:
    case GX_VA_NBT:
        *cnt = GET_REG_FIELD(*va, 1, 9);
        if (*cnt == GX_TEX_ST && (u8)(*va >> 0x1F) != 0) {
            *cnt = GX_NRM_NBT3;
        }
        *type = GET_REG_FIELD(*va, 3, 10);
        *frac = 0;
        return;
    case GX_VA_CLR0:
        *cnt  = GET_REG_FIELD(*va, 1, 13);
        *type = GET_REG_FIELD(*va, 3, 14);
        *frac = 0;
        return;
    case GX_VA_CLR1:
        *cnt  = GET_REG_FIELD(*va, 1, 17);
        *type = GET_REG_FIELD(*va, 3, 18);
        *frac = 0;
        return;
    case GX_VA_TEX0:
        *cnt  = GET_REG_FIELD(*va, 1, 21);
        *type = GET_REG_FIELD(*va, 3, 22);
        *frac = (u8)(*va >> 0x19U) & 0x1F;
        return;
    case GX_VA_TEX1:
        *cnt  = GET_REG_FIELD(*vb, 1, 0);
        *type = GET_REG_FIELD(*vb, 3, 1);
        *frac = (u8)(*vb >> 4U) & 0x1F;
        return;
    case GX_VA_TEX2:
        *cnt  = GET_REG_FIELD(*vb, 1, 9);
        *type = GET_REG_FIELD(*vb, 3, 10);
        *frac = (u8)(*vb >> 0xDU) & 0x1F;
        return;
    case GX_VA_TEX3:
        *cnt  = GET_REG_FIELD(*vb, 1, 18);
        *type = GET_REG_FIELD(*vb, 3, 19);
        *frac = (u8)(*vb >> 0x16U) & 0x1F;
        return;
    case GX_VA_TEX4:
        *cnt  = GET_REG_FIELD(*vb, 1, 27);
        *type = GET_REG_FIELD(*vb, 3, 28);
        *frac = GET_REG_FIELD(*vc, 5, 0);
        return;
    case GX_VA_TEX5:
        *cnt = GET_REG_FIELD(*vc, 1, 5);
        *type = GET_REG_FIELD(*vc, 3, 6);
        *frac = (u8)(*vc >> 9U) & 0x1F;
        return;
    case GX_VA_TEX6:
        *cnt = GET_REG_FIELD(*vc, 1, 14);
        *type = GET_REG_FIELD(*vc, 3, 15);
        *frac = (u8)(*vc >> 0x12) & 0x1F;
        return;
    case GX_VA_TEX7:
        *cnt  = GET_REG_FIELD(*vc, 1, 23);
        *type = GET_REG_FIELD(*vc, 3, 24);
        *frac = (int)(*vc >> 0x1BU);
        return;
    default:
        *cnt = GX_TEX_ST;
        *type = GX_RGB565;
        *frac = 0;
        return;
    }
}

void GXGetVtxAttrFmtv(GXVtxFmt fmt, GXVtxAttrFmtList *vat)
{
    GXAttr attr;

    CHECK_GXBEGIN(838, "GXGetVtxAttrFmtv");
    CHECK_LISTPTR(839, vat);
    CHECK_VTXFMT(840, fmt);
    for (attr = GX_VA_POS; attr < GX_VA_MAX_ATTR; attr++) {
        vat->attr = attr;
        GXGetVtxAttrFmt(fmt, attr, &vat->cnt, &vat->type, &vat->frac);
        vat++;
    }
    vat->attr = GX_VA_NULL;
}

void GXSetArray(GXAttr attr, const void *base_ptr, u8 stride)
{
    GXAttr cpAttr;
    unsigned long phyAddr;

    attr;  // needed to match

    CHECK_GXBEGIN(869, "GXSetArray");
    if (attr == GX_VA_NBT) {
        attr = GX_VA_NRM;
    }
    CHECK_ATTRNAME3(872, attr);
    cpAttr = attr - GX_VA_POS;
    phyAddr = (u32)base_ptr & 0x3FFFFFFF;
    GX_WRITE_SOME_REG2(8, cpAttr | 0xA0, phyAddr, cpAttr - 12);
    GX_WRITE_SOME_REG3(8, cpAttr | 0xB0, stride, cpAttr - 12);
}

void GXInvalidateVtxCache(void)
{
    CHECK_GXBEGIN(894, "GXInvalidateVtxCache");
    GX_WRITE_U8(0x48);
}

void GXSetTexCoordGen2(GXTexCoordID dst_coord, GXTexGenType func, GXTexGenSrc src_param, u32 mtx, GXBool normalize, u32 pt_texmtx)
{
    u32 reg = 0;
    u32 row;
    u32 bumprow;  // unused
    u32 form;
    GXAttr mtxIdAttr;

    CHECK_GXBEGIN(936, "GXSetTexCoordGen");
    ASSERTMSGLINE(937, dst_coord < 8, "GXSetTexCoordGen: Invalid coordinate Id");
    form = 0;
    row = 5;
    switch (src_param) {
    case GX_TG_POS:     row = 0; form = 1; break;
    case GX_TG_NRM:     row = 1; form = 1; break;
    case GX_TG_BINRM:   row = 3; form = 1; break;
    case GX_TG_TANGENT: row = 4; form = 1; break;
    case GX_TG_COLOR0:  row = 2; break;
    case GX_TG_COLOR1:  row = 2; break;
    case GX_TG_TEX0:    row = 5; break;
    case GX_TG_TEX1:    row = 6; break;
    case GX_TG_TEX2:    row = 7; break;
    case GX_TG_TEX3:    row = 8; break;
    case GX_TG_TEX4:    row = 9; break;
    case GX_TG_TEX5:    row = 10; break;
    case GX_TG_TEX6:    row = 11; break;
    case GX_TG_TEX7:    row = 12; break;
    case GX_TG_TEXCOORD0: bumprow; break;
    case GX_TG_TEXCOORD1: bumprow; break;
    case GX_TG_TEXCOORD2: bumprow; break;
    case GX_TG_TEXCOORD3: bumprow; break;
    case GX_TG_TEXCOORD4: bumprow; break;
    case GX_TG_TEXCOORD5: bumprow; break;
    case GX_TG_TEXCOORD6: bumprow; break;
    default:
        ASSERTMSGLINE(965, 0, "GXSetTexCoordGen: Invalid source parameter");
        break;
    }
    switch (func)
    {
    case GX_TG_MTX2x4:
        SET_REG_FIELD(974, reg, 1, 1, 0);
        SET_REG_FIELD(975, reg, 1, 2, form);
        SET_REG_FIELD(976, reg, 3, 4, 0);
        SET_REG_FIELD(977, reg, 5, 7, row);
        break;
    case GX_TG_MTX3x4:
        SET_REG_FIELD(981, reg, 1, 1, 1);
        SET_REG_FIELD(982, reg, 1, 2, form);
        SET_REG_FIELD(983, reg, 3, 4, 0);
        SET_REG_FIELD(984, reg, 5, 7, row);
        break;
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
        ASSERTMSGLINE(997, src_param >= 12 && src_param <= 18, "GXSetTexCoordGen:  Bump source texture value is invalid");
        SET_REG_FIELD(998, reg, 1, 1, 0);
        SET_REG_FIELD(999, reg, 1, 2, form);
        SET_REG_FIELD(1000, reg, 3, 4, 1);
        SET_REG_FIELD(1001, reg, 5, 7, row);
        SET_REG_FIELD(1002, reg, 3, 12, src_param - 12);
        SET_REG_FIELD(1003, reg, 3, 15, func - 2);
        break;
    case GX_TG_SRTG:
        SET_REG_FIELD(1007, reg, 1, 1, 0);
        SET_REG_FIELD(1008, reg, 1, 2, form);
        if (src_param == GX_TG_COLOR0) {
            SET_REG_FIELD(0, reg, 3, 4, 2);
        } else {
            SET_REG_FIELD(0, reg, 3, 4, 3);
        }
        SET_REG_FIELD(0, reg, 5, 7, 2);
        break;
    default:
        ASSERTMSGLINE(1019, 0, "GXSetTexCoordGen:  Invalid function");
        break;
    }
    GX_WRITE_XF_REG(dst_coord + 0x40, reg);
    reg = 0;
    SET_REG_FIELD(1038, reg, 6, 0, pt_texmtx - 64);
    SET_REG_FIELD(1039, reg, 1, 8, normalize);
    GX_WRITE_XF_REG(dst_coord + 0x50, reg);
    switch (dst_coord) {
    case GX_TEXCOORD0: SET_REG_FIELD(1048, gx->matIdxA, 6, 6, mtx);  break;
    case GX_TEXCOORD1: SET_REG_FIELD(1049, gx->matIdxA, 6, 12, mtx); break;
    case GX_TEXCOORD2: SET_REG_FIELD(1050, gx->matIdxA, 6, 18, mtx); break;
    case GX_TEXCOORD3: SET_REG_FIELD(1051, gx->matIdxA, 6, 24, mtx); break;
    case GX_TEXCOORD4: SET_REG_FIELD(1052, gx->matIdxB, 6, 0, mtx);  break;
    case GX_TEXCOORD5: SET_REG_FIELD(1053, gx->matIdxB, 6, 6, mtx);  break;
    case GX_TEXCOORD6: SET_REG_FIELD(1054, gx->matIdxB, 6, 12, mtx); break;
    default:           SET_REG_FIELD(1055, gx->matIdxB, 6, 18, mtx); break;
    }
    mtxIdAttr = dst_coord + 1;
    __GXSetMatrixIndex(mtxIdAttr);
}

void GXSetNumTexGens(u8 nTexGens)
{
    CHECK_GXBEGIN(1073, "GXSetNumTexGens");
    SET_REG_FIELD(1075, gx->genMode, 4, 0, nTexGens);
    GX_WRITE_XF_REG(0x3F, nTexGens);
    gx->dirtyState |= 4;
}
