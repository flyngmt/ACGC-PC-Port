#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <macros.h>

#include "gx/__gx.h"

void GXSetTevOp(GXTevStageID id, GXTevMode mode)
{
    GXTevColorArg carg = GX_CC_RASC;
    GXTevAlphaArg aarg = GX_CA_RASA;

    CHECK_GXBEGIN(0x76, "GXSetTevOp");

    if (id != GX_TEVSTAGE0) {
        carg = GX_CC_CPREV;
        aarg = GX_CA_APREV;
    }

    switch (mode) {
    case GX_MODULATE:
        GXSetTevColorIn(id, GX_CC_ZERO, GX_CC_TEXC, carg, GX_CC_ZERO);
        GXSetTevAlphaIn(id, GX_CA_ZERO, GX_CA_TEXA, aarg, GX_CA_ZERO);
        break;
    case GX_DECAL:
        GXSetTevColorIn(id, carg, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
        GXSetTevAlphaIn(id, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, aarg);
        break;
    case GX_BLEND:
        GXSetTevColorIn(id, carg, GX_CC_ONE, GX_CC_TEXC, GX_CC_ZERO);
        GXSetTevAlphaIn(id, GX_CA_ZERO, GX_CA_TEXA, aarg, GX_CA_ZERO);
        break;
    case GX_REPLACE:
        GXSetTevColorIn(id, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
        GXSetTevAlphaIn(id, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
        break;
    case GX_PASSCLR:
        GXSetTevColorIn(id, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, carg);
        GXSetTevAlphaIn(id, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, aarg);
        break;
    default:
        ASSERTMSGLINE(0x93, 0, "GXSetTevOp: Invalid Tev Mode");
    }
    GXSetTevColorOp(id, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(id, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
}


void GXSetTevColorIn(GXTevStageID stage, GXTevColorArg a, GXTevColorArg b, GXTevColorArg c, GXTevColorArg d)
{
    u32 *pTevReg;

    CHECK_GXBEGIN(0xE9, "GXSetTevColorIn");
    ASSERTMSGLINE(0xEA, stage < 16, "GXSetTevColor: Invalid Tev Stage Index");
    ASSERTMSGLINE(0xEB, a <= 15, "GXSetTev*In: A/B/C/D argument out of range");
    ASSERTMSGLINE(0xEC, b <= 15, "GXSetTev*In: A/B/C/D argument out of range");
    ASSERTMSGLINE(0xED, c <= 15, "GXSetTev*In: A/B/C/D argument out of range");
    ASSERTMSGLINE(0xEE, d <= 15, "GXSetTev*In: A/B/C/D argument out of range");

    pTevReg = &gx->tevc[stage];
    SET_REG_FIELD(0xF1, *pTevReg, 4, 12, a);
    SET_REG_FIELD(0xF2, *pTevReg, 4,  8, b);
    SET_REG_FIELD(0xF3, *pTevReg, 4,  4, c);
    SET_REG_FIELD(0xF4, *pTevReg, 4,  0, d);

    GX_WRITE_RAS_REG(*pTevReg);
    gx->bpSentNot = GX_FALSE;
}

void GXSetTevAlphaIn(GXTevStageID stage, GXTevAlphaArg a, GXTevAlphaArg b, GXTevAlphaArg c, GXTevAlphaArg d)
{
    u32 *pTevReg;

    CHECK_GXBEGIN(0x10C, "GXSetTevAlphaIn");
    ASSERTMSGLINE(0x10D, stage < 16, "GXSetTevAlpha: Invalid Tev Stage Index");
    ASSERTMSGLINE(0x10E, a <= 7, "GXSetTev*In: A/B/C/D argument out of range");
    ASSERTMSGLINE(0x10F, b <= 7, "GXSetTev*In: A/B/C/D argument out of range");
    ASSERTMSGLINE(0x110, c <= 7, "GXSetTev*In: A/B/C/D argument out of range");
    ASSERTMSGLINE(0x111, d <= 7, "GXSetTev*In: A/B/C/D argument out of range");

    pTevReg = &gx->teva[stage];
    SET_REG_FIELD(0x114, *pTevReg, 3, 13, a);
    SET_REG_FIELD(0x115, *pTevReg, 3, 10, b);
    SET_REG_FIELD(0x116, *pTevReg, 3,  7, c);
    SET_REG_FIELD(0x117, *pTevReg, 3,  4, d);

    GX_WRITE_RAS_REG(*pTevReg);
    gx->bpSentNot = GX_FALSE;
}

void GXSetTevColorOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg)
{
    u32 *pTevReg;

    CHECK_GXBEGIN(0x132, "GXSetTevColorOp");
    ASSERTMSGLINE(0x133, stage < 16, "GXSetTevColor: Invalid Tev Stage Index");

    pTevReg = &gx->tevc[stage];
    SET_REG_FIELD(0x13B, *pTevReg, 1, 18, op & 1);
    if (op <= 1) {
        SET_REG_FIELD(0x13D, *pTevReg, 2, 20, scale);
        SET_REG_FIELD(0x13E, *pTevReg, 2, 16, bias);
    } else {
        SET_REG_FIELD(0x140, *pTevReg, 2, 20, (op >> 1) & 3);
        SET_REG_FIELD(0x141, *pTevReg, 2, 16, 3);
    }
    SET_REG_FIELD(0x144, *pTevReg, 1, 19, clamp & 0xFF);
    SET_REG_FIELD(0x145, *pTevReg, 2, 22, out_reg);

    GX_WRITE_RAS_REG(*pTevReg);
    gx->bpSentNot = GX_FALSE;
}

void GXSetTevAlphaOp(GXTevStageID stage, GXTevOp op, GXTevBias bias, GXTevScale scale, GXBool clamp, GXTevRegID out_reg)
{
    u32 *pTevReg;

    CHECK_GXBEGIN(0x15E, "GXSetTevAlphaOp");
    ASSERTMSGLINE(0x15F, stage < 16, "GXSetTevAlpha: Invalid Tev Stage Index");

    pTevReg = &gx->teva[stage];
    SET_REG_FIELD(0x167, *pTevReg, 1, 18, op & 1);
    if (op <= 1) {
        SET_REG_FIELD(0x169, *pTevReg, 2, 20, scale);
        SET_REG_FIELD(0x16A, *pTevReg, 2, 16, bias);
    } else {
        SET_REG_FIELD(0x16C, *pTevReg, 2, 20, (op >> 1) & 3);
        SET_REG_FIELD(0x16D, *pTevReg, 2, 16, 3);
    }
    SET_REG_FIELD(0x170, *pTevReg, 1, 19, clamp & 0xFF);
    SET_REG_FIELD(0x171, *pTevReg, 2, 22, out_reg);

    GX_WRITE_RAS_REG(*pTevReg);
    gx->bpSentNot = GX_FALSE;
}

void GXSetTevColor(GXTevRegID id, GXColor color)
{
    u32 regRA;
    u32 regBG;

    CHECK_GXBEGIN(0x186, "GXSetTevColor");

    regRA = 0;
    SET_REG_FIELD(0x189, regRA, 11,  0, color.r);
    SET_REG_FIELD(0x18A, regRA, 11, 12, color.a);
    SET_REG_FIELD(0x18B, regRA,  8, 24, 224 + id * 2);

    regBG = 0;
    SET_REG_FIELD(0x18E, regBG, 11,  0, color.b);
    SET_REG_FIELD(0x18F, regBG, 11, 12, color.g);
    SET_REG_FIELD(0x190, regBG,  8, 24, 225 + id * 2);

    GX_WRITE_RAS_REG(regRA);
    GX_WRITE_RAS_REG(regBG);
    GX_WRITE_RAS_REG(regBG);
    GX_WRITE_RAS_REG(regBG);
    gx->bpSentNot = GX_FALSE;
}

void GXSetTevColorS10(GXTevRegID id, GXColorS10 color)
{
    u32 regRA;
    u32 regBG;

    ASSERTMSGLINE(0x1AB, color.r >= -1024 && color.r < 1024, "GXSetTevColorS10: Color not in range -1024 to +1023");
    ASSERTMSGLINE(0x1AC, color.g >= -1024 && color.g < 1024, "GXSetTevColorS10: Color not in range -1024 to +1023");
    ASSERTMSGLINE(0x1AD, color.b >= -1024 && color.b < 1024, "GXSetTevColorS10: Color not in range -1024 to +1023");
    ASSERTMSGLINE(0x1AE, color.a >= -1024 && color.a < 1024, "GXSetTevColorS10: Color not in range -1024 to +1023");

    CHECK_GXBEGIN(0x1B0, "GXSetTevColorS10");

    regRA = 0;
    SET_REG_FIELD(0x1B3, regRA, 11,  0, color.r & 0x7FF);
    SET_REG_FIELD(0x1B4, regRA, 11, 12, color.a & 0x7FF);
    SET_REG_FIELD(0x1B5, regRA,  8, 24, 224 + id * 2);

    regBG = 0;
    SET_REG_FIELD(0x1B8, regBG, 11,  0, color.b & 0x7FF);
    SET_REG_FIELD(0x1B9, regBG, 11, 12, color.g & 0x7FF);
    SET_REG_FIELD(0x1BA, regBG,  8, 24, 225 + id * 2);

    GX_WRITE_RAS_REG(regRA);
    GX_WRITE_RAS_REG(regBG);
    GX_WRITE_RAS_REG(regBG);
    GX_WRITE_RAS_REG(regBG);
    gx->bpSentNot = GX_FALSE;
}

void GXSetTevKColor(GXTevKColorID id, GXColor color)
{
    u32 regRA;
    u32 regBG;

    CHECK_GXBEGIN(0x1E1, "GXSetTevKColor");

    regRA = 0;
    SET_REG_FIELD(0x1E4, regRA, 8,  0, color.r);
    SET_REG_FIELD(0x1E5, regRA, 8, 12, color.a);
    SET_REG_FIELD(0x1E6, regRA, 4, 20, 8);
    SET_REG_FIELD(0x1E7, regRA, 8, 24, 224 + id * 2);

    regBG = 0;
    SET_REG_FIELD(0x1EA, regBG, 8,  0, color.b);
    SET_REG_FIELD(0x1EB, regBG, 8, 12, color.g);
    SET_REG_FIELD(0x1EC, regBG, 4, 20, 8);
    SET_REG_FIELD(0x1ED, regBG, 8, 24, 225 + id * 2);

    GX_WRITE_RAS_REG(regRA);
    GX_WRITE_RAS_REG(regBG);
    gx->bpSentNot = GX_FALSE;
}

void GXSetTevKColorSel(GXTevStageID stage, GXTevKColorSel sel)
{
    u32 *Kreg;

    CHECK_GXBEGIN(0x208, "GXSetTevKColorSel");
    ASSERTMSGLINE(0x209, stage < 16, "GXSetTevKColor*: Invalid Tev Stage Index");

    Kreg = &gx->tevKsel[stage >> 1];
    if (stage & 1) {
        SET_REG_FIELD(0x20E, *Kreg, 5, 14, sel);
    } else {
        SET_REG_FIELD(0x210, *Kreg, 5, 4, sel);
    }

    GX_WRITE_RAS_REG(*Kreg);
    gx->bpSentNot = GX_FALSE;
}

void GXSetTevKAlphaSel(GXTevStageID stage, GXTevKAlphaSel sel)
{
    u32 *Kreg;

    CHECK_GXBEGIN(0x229, "GXSetTevKAlphaSel");
    ASSERTMSGLINE(0x22A, stage < 16, "GXSetTevKColor*: Invalid Tev Stage Index");

    Kreg = &gx->tevKsel[stage >> 1];
    if (stage & 1) {
        SET_REG_FIELD(0x22F, *Kreg, 5, 19, sel);
    } else {
        SET_REG_FIELD(0x231, *Kreg, 5, 9, sel);
    }

    GX_WRITE_RAS_REG(*Kreg);
    gx->bpSentNot = GX_FALSE;
}

void GXSetTevSwapMode(GXTevStageID stage, GXTevSwapSel ras_sel, GXTevSwapSel tex_sel)
{
    u32 *pTevReg;

    CHECK_GXBEGIN(0x24E, "GXSetTevSwapMode");
    ASSERTMSGLINE(0x24F, stage < 16, "GXSetTevSwapMode: Invalid Tev Stage Index");

    pTevReg = &gx->teva[stage];
    SET_REG_FIELD(0x252, *pTevReg, 2, 0, ras_sel);
    SET_REG_FIELD(0x253, *pTevReg, 2, 2, tex_sel);

    GX_WRITE_RAS_REG(*pTevReg);
    gx->bpSentNot = GX_FALSE;
}

void GXSetTevSwapModeTable(GXTevSwapSel table, GXTevColorChan red, GXTevColorChan green, GXTevColorChan blue, GXTevColorChan alpha)
{
    u32 *Kreg;
#if !DEBUG
    // not a real variable, but needed to match release
    int index = table * 2;
#endif

    CHECK_GXBEGIN(0x272, "GXSetTevSwapModeTable");
    ASSERTMSGLINE(0x273, table < 4, "GXSetTevSwapModeTable: Invalid Swap Selection Index");

#if DEBUG
    Kreg = &gx->tevKsel[table * 2];
#else
    Kreg = &gx->tevKsel[index];
#endif
    SET_REG_FIELD(0x276, *Kreg, 2, 0, red);
    SET_REG_FIELD(0x277, *Kreg, 2, 2, green);

    GX_WRITE_RAS_REG(*Kreg);

    Kreg = &gx->tevKsel[table * 2 + 1];
    SET_REG_FIELD(0x27B, *Kreg, 2, 0, blue);
    SET_REG_FIELD(0x27C, *Kreg, 2, 2, alpha);

    GX_WRITE_RAS_REG(*Kreg);
    gx->bpSentNot = GX_FALSE;
}

void GXSetTevClampMode(void)
{
    ASSERTMSGLINE(0x294, 0, "GXSetTevClampMode: not available on this hardware");
}

void GXSetAlphaCompare(GXCompare comp0, u8 ref0, GXAlphaOp op, GXCompare comp1, u8 ref1)
{
    u32 reg = 0;

    CHECK_GXBEGIN(0x2B6, "GXSetAlphaCompare");

    SET_REG_FIELD(0x2B8, reg, 8, 0, ref0);
    SET_REG_FIELD(0x2B9, reg, 8, 8, ref1);
    SET_REG_FIELD(0x2BA, reg, 3, 16, comp0);
    SET_REG_FIELD(0x2BB, reg, 3, 19, comp1);
    SET_REG_FIELD(0x2BC, reg, 2, 22, op);
    SET_REG_FIELD(0x2BD, reg, 8, 24, 0xF3);

    GX_WRITE_RAS_REG(reg);
    gx->bpSentNot = GX_FALSE;
}

void GXSetZTexture(GXZTexOp op, GXTexFmt fmt, u32 bias)
{
    u32 zenv0;
    u32 zenv1;
    u32 type;

    CHECK_GXBEGIN(0x2D5, "GXSetZTexture");

    zenv0 = 0;
    SET_REG_FIELD(0x2D8, zenv0, 24, 0, bias);
    SET_REG_FIELD(0x2D9, zenv0, 8, 24, 0xF4);

    zenv1 = 0;
    switch (fmt)
    {
    case GX_TF_Z8:
        type = 0;
        break;
    case GX_TF_Z16:
        type = 1;
        break;
    case GX_TF_Z24X8:
        type = 2;
        break;
    default:
        ASSERTMSGLINE(0x2E1, 0, "GXSetZTexture: Invalid z-texture format");
        type = 2;
        break;
    }
    SET_REG_FIELD(0x2E4, zenv1, 2, 0, type);
    SET_REG_FIELD(0x2E5, zenv1, 2, 2, op);
    SET_REG_FIELD(0x2E6, zenv1, 8, 24, 0xF5);

    GX_WRITE_RAS_REG(zenv0);
    GX_WRITE_RAS_REG(zenv1);
    gx->bpSentNot = GX_FALSE;
}

void GXSetTevOrder(GXTevStageID stage, GXTexCoordID coord, GXTexMapID map, GXChannelID color)
{
    u32 *ptref;
    u32 tmap;
    u32 tcoord;
    static int c2r[] = { 0, 1, 0, 1, 0, 1, 7, 5, 6 };

    CHECK_GXBEGIN(0x30B, "GXSetTevOrder");
    ASSERTMSGLINE(0x30C, stage < 16, "GXSetTevColor: Invalid Tev Stage Index");

    ptref = &gx->tref[stage / 2];
    gx->texmapId[stage] = map;

    tmap = map & ~0x100;
    tmap = (tmap >= GX_MAX_TEXMAP) ? GX_TEXMAP0 : tmap;

    if (coord >= GX_MAX_TEXCOORD) {
		tcoord     = GX_TEXCOORD0;
		gx->tevTcEnab = gx->tevTcEnab & ~(1 << stage);
	} else {
		tcoord     = coord;
		gx->tevTcEnab = gx->tevTcEnab | (1 << stage);
	}

    if (stage & 1) {
        SET_REG_FIELD(0x320, *ptref, 3, 12, tmap);
        SET_REG_FIELD(0x321, *ptref, 3, 15, tcoord);
        SET_REG_FIELD(0x323, *ptref, 3, 19, (color == GX_COLOR_NULL) ? 7 : c2r[color]);
        SET_REG_FIELD(0x325, *ptref, 1, 18, (map != GX_TEXMAP_NULL && !(map & 0x100)));
    } else {
        SET_REG_FIELD(0x328, *ptref, 3, 0, tmap);
        SET_REG_FIELD(0x329, *ptref, 3, 3, tcoord);
        SET_REG_FIELD(0x32B, *ptref, 3, 7, (color == GX_COLOR_NULL) ? 7 : c2r[color]);
        SET_REG_FIELD(0x32D, *ptref, 1, 6, (map != GX_TEXMAP_NULL && !(map & 0x100)));
    }

    GX_WRITE_RAS_REG(*ptref);
    gx->bpSentNot = GX_FALSE;
    gx->dirtyState |= 1;
}

void GXSetNumTevStages(u8 nStages)
{
    CHECK_GXBEGIN(0x33D, "GXSetNumTevStages");

    ASSERTMSGLINE(0x33F, nStages != 0 && nStages <= 16, "GXSetNumTevStages: Exceed max number of tex stages");
    SET_REG_FIELD(0x340, gx->genMode, 4, 10, nStages - 1);
    gx->dirtyState |= 4;
}
