#include "m_rcp.h"

#include "gfxalloc.h"
#include "libu64/u64types.h"
#include "jsyswrap.h"
#include "m_font.h"

#define G_CC_POLY_Z_LIGHT_PRIM PRIMITIVE, 0, SHADE, 0, 0, 0, 0, PRIMITIVE
#define G_CC_MODULATEIDECALA_PRIM2 PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED
#define G_CC_PRIMLERP 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0

static Gfx z_gsCPModeSet_Data[15][6] = {
    {
        gsDPPipeSync(),
        gsSPTexture(65535, 65535, 0, 0, G_OFF),
        gsDPSetCombineMode(G_CC_POLY_Z_LIGHT_PRIM, G_CC_POLY_Z_LIGHT_PRIM),
        gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                             G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                         G_AC_NONE | G_ZS_PIXEL | G_RM_AA_ZB_XLU_SURF | G_RM_AA_ZB_XLU_SURF2),
        gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
        gsSPEndDisplayList(),
    },
    {
        gsDPPipeSync(),
        gsSPTexture(65535, 65535, 0, 0, G_ON),
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                             G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                         G_AC_THRESHOLD | G_ZS_PIXEL | G_RM_ZB_CLD_SURF | G_RM_ZB_CLD_SURF2),
        gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),
        gsSPEndDisplayList(),
    },
    {
        gsDPPipeSync(),
        gsSPTexture(65535, 65535, 0, 0, G_ON),
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIA_PRIM2),
        gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                             G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                         G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_OPA_SURF2),
        gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
        gsSPEndDisplayList(),
    },
    {
        gsDPPipeSync(),
        gsSPTexture(65535, 65535, 0, 0, G_ON),
        gsDPSetCombineMode(G_CC_MODULATEI_PRIM, G_CC_MODULATEI_PRIM),
        gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                             G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                         G_AC_NONE | G_ZS_PIXEL | G_RM_AA_ZB_OPA_SURF | G_RM_AA_ZB_OPA_SURF2),
        gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
        gsSPEndDisplayList(),
    },
    {
        gsDPPipeSync(),
        gsSPTexture(65535, 65535, 0, 0, G_ON),
        gsDPSetCombineMode(G_CC_MODULATEIDECALA_PRIM, G_CC_MODULATEIDECALA_PRIM),
        gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 | G_TL_TILE |
                             G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                         G_AC_THRESHOLD | G_ZS_PIXEL | G_RM_AA_TEX_EDGE | G_RM_AA_TEX_EDGE2),
        gsSPLoadGeometryMode(G_SHADE | G_SHADING_SMOOTH),
        gsSPEndDisplayList(),
    },
    {
        gsDPPipeSync(),
        gsSPTexture(65535, 65535, 0, 0, G_OFF),
        gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
        gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                             G_TD_CLAMP | G_TP_NONE | G_CYC_FILL | G_PM_NPRIMITIVE,
                         G_AC_THRESHOLD | G_ZS_PIXEL | G_RM_NOOP | G_RM_NOOP2),
        gsSPLoadGeometryMode(G_SHADE | G_SHADING_SMOOTH),
        gsSPEndDisplayList(),
    },
    {
        gsDPPipeSync(),
        gsSPTexture(65535, 65535, 0, 0, G_ON),
        gsDPSetCombineMode(G_CC_MODULATEI_PRIM, G_CC_MODULATEI_PRIM),
        gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                             G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                         G_AC_NONE | G_ZS_PIXEL | G_RM_ZB_XLU_SURF | G_RM_ZB_XLU_SURF2),
        gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH),
        gsSPEndDisplayList(),
    },
    {
        gsDPPipeSync(),
        gsSPTexture(65535, 65535, 0, 0, G_OFF),
        gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PRIMITIVE),
        gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                             G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                         G_AC_THRESHOLD | G_ZS_PIXEL | G_RM_CLD_SURF | G_RM_CLD_SURF2),
        gsSPLoadGeometryMode(G_SHADING_SMOOTH),
        gsSPEndDisplayList(),
    },
    {
        gsDPPipeSync(),
        gsSPTexture(65535, 65535, 0, 0, G_ON),
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM),
        gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                             G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                         G_AC_THRESHOLD | G_ZS_PIXEL | G_RM_CLD_SURF | G_RM_CLD_SURF2),
        gsSPLoadGeometryMode(G_SHADE | G_SHADING_SMOOTH),
        gsSPEndDisplayList(),
    },
    {
        gsDPPipeSync(),
        gsSPTexture(65535, 65535, 0, 0, G_ON),
        gsDPSetCombineMode(G_CC_MODULATEIA_PRIM, G_CC_PASS2),
        gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                             G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                         G_AC_NONE | G_ZS_PIXEL | G_RM_PASS | G_RM_ZB_CLD_SURF2),
        gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
        gsSPEndDisplayList(),
    },
    {
        gsDPPipeSync(),
        gsSPTexture(65535, 65535, 0, 0, G_ON),
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA_PRIM2),
        gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 |
                             G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                         G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_TEX_EDGE2),
        gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
        gsSPEndDisplayList(),
    },
    {
        gsDPPipeSync(),
        gsSPTexture(65535, 65535, 0, 0, G_ON),
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA_PRIM2),
        gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 |
                             G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                         G_AC_NONE | G_ZS_PIXEL | AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_FULL | ZMODE_OPA |
                             CVG_X_ALPHA | ALPHA_CVG_SEL | G_RM_FOG_SHADE_A |
                             GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)),
        gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
        gsSPEndDisplayList(),
    },
    {
        gsDPPipeSync(),
        gsSPTexture(65535, 65535, 0, 0, G_ON),
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA_PRIM2),
        gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 |
                             G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                         G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_TEX_EDGE2),
        gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
        gsSPEndDisplayList(),
    },
    {
        gsDPPipeSync(),
        gsSPTexture(65535, 65535, 0, 0, G_ON),
        gsDPSetCombineMode(G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA_PRIM2),
        gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_RGBA16 |
                             G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                         G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_CLD_SURF2),
        gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
        gsSPEndDisplayList(),
    },
    {
        gsDPPipeSync(),
        gsSPTexture(65535, 65535, 0, 0, G_ON),
        gsDPSetCombineMode(G_CC_PRIMLERP, G_CC_PASS2),
        gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                             G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                         G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_ZB_OVL_SURF2),
        gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH),
        gsSPEndDisplayList(),
    }
};

Gfx RSP_RDP_clear_data[12] = {
    gsDPPipeSync(),
    gsSPTexture(65535, 65535, 0, 0, G_OFF),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_FILL | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_NOOP | G_RM_NOOP2),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 640, 480),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x08),
    gsSPClipRatio(FRUSTRATIO_2),
    gsSPEndDisplayList(),
};

int fbdemo_mode;

extern void gfx_set_fog_position(Gfx** gfxp, int near, int far) {
    Gfx* gfx;

    if (near == far) {
        gfx = (*gfxp)++;
        gSPFogPosition(gfx++, 0, 10000000);
        return;
    }
    gfx = (*gfxp)++;
    gSPFogPosition(gfx++, near, far);
}

extern Gfx* gfx_set_fog_nosync(Gfx* gfx, int r, int g, int b, int a, int near, int far) {
    gDPSetFogColor(gfx++, r, g, b, a);
    gfx_set_fog_position(&gfx, near, far);

    return gfx;
}

extern void texture_z_light_prim_xlu_disp(GRAPH* graph) {
    OPEN_DISP(graph);

    gSPDisplayList(NOW_POLY_XLU_DISP++, z_gsCPModeSet_Data[2]);

    CLOSE_DISP(graph);
}

extern void _texture_z_light_fog_prim_bg(GRAPH* graph) {
    OPEN_DISP(graph);

    gSPDisplayList(NOW_BG_OPA_DISP++, z_gsCPModeSet_Data[2]);

    CLOSE_DISP(graph);
}

extern void _texture_z_light_fog_prim(GRAPH* graph) {
    OPEN_DISP(graph);

    gSPDisplayList(NOW_POLY_OPA_DISP++, z_gsCPModeSet_Data[2]);

    CLOSE_DISP(graph);
}

extern void _texture_z_light_fog_prim_shadow(GRAPH* graph) {
    OPEN_DISP(graph);

    gSPDisplayList(NOW_SHADOW_DISP++, z_gsCPModeSet_Data[2]);

    CLOSE_DISP(graph);
}

extern void _texture_z_light_fog_prim_xlu(GRAPH* graph) {
    OPEN_DISP(graph);

    gSPDisplayList(NOW_POLY_XLU_DISP++, z_gsCPModeSet_Data[2]);

    CLOSE_DISP(graph);
}

extern void _texture_z_light_fog_prim_light(GRAPH* graph) {
    OPEN_DISP(graph);

    gSPDisplayList(NOW_LIGHT_DISP++, z_gsCPModeSet_Data[2]);

    CLOSE_DISP(graph);
}

extern void _texture_z_light_fog_prim_npc(GRAPH* graph) {
    OPEN_DISP(graph);

    gSPDisplayList(NOW_POLY_OPA_DISP++, z_gsCPModeSet_Data[10]);
    gDPPipeSync(NOW_POLY_OPA_DISP++);
    gDPSetPrimColor(NOW_POLY_OPA_DISP++, 0, 128, 255, 255, 255, 255);

    CLOSE_DISP(graph);
}

extern Gfx* texture_z_light_fog_prim_bb_pal_opa(Gfx* gfx) {
    gSPDisplayList(gfx++, z_gsCPModeSet_Data[12]);
    gDPSetPrimColor(gfx++, 0, 128, 255, 255, 255, 255);

    return gfx;
}

extern Gfx* texture_z_light_fog_prim_bb_pal_xlu(Gfx* gfx) {
    gSPDisplayList(gfx++, z_gsCPModeSet_Data[13]);
    gDPSetPrimColor(gfx++, 0, 128, 255, 255, 255, 255);

    return gfx;
}

extern Gfx* texture_z_fog_lod_alpha_shadow(Gfx* gfx) {
    gSPDisplayList(gfx++, z_gsCPModeSet_Data[14]);

    return gfx;
}

extern Gfx* gfx_rect_moji(Gfx* gfx) {
    gSPDisplayList(gfx++, z_gsCPModeSet_Data[4]);

    return gfx;
}

extern void rect_moji(GRAPH* graph) {
    OPEN_DISP(graph);

    gSPDisplayList(NOW_POLY_OPA_DISP++, z_gsCPModeSet_Data[4]);

    CLOSE_DISP(graph);
}

extern void polygon_z_light_prim(GRAPH* graph) {
    OPEN_DISP(graph);

    gSPDisplayList(NOW_POLY_XLU_DISP++, z_gsCPModeSet_Data[0]);

    CLOSE_DISP(graph);
}

extern void softsprite_prim(GRAPH* graph) {
    OPEN_DISP(graph);

    gSPDisplayList(NOW_POLY_XLU_DISP++, z_gsCPModeSet_Data[6]);

    CLOSE_DISP(graph);
}

extern Gfx* gfx_softsprite_prim_xlu(Gfx* gfx) {
    gSPDisplayList(gfx++, z_gsCPModeSet_Data[8]);
    gDPSetColorDither(gfx++, G_CD_DISABLE);

    return gfx++;
}

extern Gfx* gfx_tex_scroll2(Gfx** gfxpp, int x, int y, int width, int height) {
    Gfx* dl = gfxalloc(gfxpp, 3 * sizeof(Gfx));

    gDPTileSync(dl);
    gDPSetTileSize(dl + 1, G_TX_RENDERTILE, x, y, x + ((width - 1) << 2), y + ((height - 1) << 2));
    gSPEndDisplayList(dl + 2);
    return dl;
}

extern Gfx* tex_scroll2(GRAPH* graph, u32 x, u32 y, int width, int height) {
    Gfx* dl = GRAPH_ALLOC_TYPE(graph, Gfx, 3);
    if (dl != NULL) {
        gDPTileSync(dl);
        gDPSetTileSize(dl + 1, G_TX_RENDERTILE, x & 0x7FF, y & 0x7FF, ((x & 0x7FF) + ((width - 1) << 2)),
                       ((y & 0x7FF) + ((height - 1) << 2)));
        gSPEndDisplayList(dl + 2);
    }

    return dl;
}

extern Gfx* tex_scroll2_dolphin(GRAPH* graph, int x, int y, int width, int height) {
    Gfx* dl = GRAPH_ALLOC_TYPE(graph, Gfx, 2);

    if (dl != NULL) {
        gDPSetTileSize_Dolphin(dl, 0, x << 1, y << 1, width, height);
        gSPEndDisplayList(dl + 1);
    }

    return dl;
}

extern Gfx* two_tex_scroll(GRAPH* graph, int tile1, int x1, int y1, int width1, int height1, int tile2, int x2, int y2,
                           int width2, int height2) {
    Gfx* dl = GRAPH_ALLOC_TYPE(graph, Gfx, 5);

    if (dl != NULL) {
        gDPTileSync(dl);
        gDPSetTileSize(dl + 1, tile1, x1 & 0x7FF, y1 & 0x7FF, (x1 & 0x7FF) + ((width1 - 1) << 2),
                       (y1 & 0x7FF) + ((height1 - 1) << 2));
        gDPTileSync(dl + 2);
        gDPSetTileSize(dl + 3, tile2, x2 & 0x7FF, y2 & 0x7FF, (x2 & 0x7FF) + ((width2 - 1) << 2),
                       (y2 & 0x7FF) + ((height2 - 1) << 2));
        gSPEndDisplayList(dl + 4);
    }

    return dl;
}

extern Gfx* two_tex_scroll_dolphin(GRAPH* graph, int tile1, int x1, int y1, int width1, int height1, int tile2, int x2,
                                   int y2, int width2, int height2) {
    Gfx* dl = GRAPH_ALLOC_TYPE(graph, Gfx, 3);

    if (dl != NULL) {
        gDPSetTileSize_Dolphin(dl, tile1, x1 << 1, y1 << 1, width1, height1);
        gDPSetTileSize_Dolphin(dl + 1, tile2, x2 << 1, y2 << 1, width2, height2);
        gSPEndDisplayList(dl + 2);
    }

    return dl;
}

// @BUG - we don't need to clear the screen by drawing a full screen quad with the clear color,
// as JW_setClearColor handles that for us.
#if defined(BUGFIXES) || defined(TARGET_PC)
extern void DisplayList_initialize(GRAPH* graph, u8 clear_r, u8 clear_g, u8 clear_b, GAME* game) {
    OPEN_DISP(graph);

    gSPDisplayList(NOW_POLY_OPA_DISP++, RSP_RDP_clear_data);
    gSPDisplayList(NOW_POLY_XLU_DISP++, RSP_RDP_clear_data);
    gSPDisplayList(NOW_OVERLAY_DISP++, RSP_RDP_clear_data);
    gSPDisplayList(NOW_FONT_DISP++, RSP_RDP_clear_data);
    gSPDisplayList(NOW_BG_OPA_DISP++, RSP_RDP_clear_data);
    gSPDisplayList(NOW_BG_XLU_DISP++, z_gsCPModeSet_Data[2]);
    gSPDisplayList(NOW_SHADOW_DISP++, z_gsCPModeSet_Data[2]);
    gSPDisplayList(NOW_LIGHT_DISP++, z_gsCPModeSet_Data[2]);

    gDPSetScissor(NOW_POLY_OPA_DISP++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    gDPSetScissor(NOW_POLY_XLU_DISP++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    gDPSetScissor(NOW_OVERLAY_DISP++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    gDPSetScissor(NOW_FONT_DISP++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    gDPSetScissor(NOW_SHADOW_DISP++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    gDPSetScissor(NOW_LIGHT_DISP++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    gDPSetScissor(NOW_BG_OPA_DISP++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    gDPSetScissor(NOW_BG_XLU_DISP++, G_SC_NON_INTERLACE, 0, 0, 640, 480);

    CLOSE_DISP(graph);

    JW_setClearColor(clear_r, clear_g, clear_b);
    mFont_Main_start(graph);
}
#else
extern void DisplayList_initialize(GRAPH* graph, u8 clear_r, u8 clear_g, u8 clear_b, GAME* game) {
    OPEN_DISP(graph);

    gSPDisplayList(NOW_POLY_OPA_DISP++, RSP_RDP_clear_data);
    gSPDisplayList(NOW_POLY_XLU_DISP++, RSP_RDP_clear_data);
    gSPDisplayList(NOW_OVERLAY_DISP++, RSP_RDP_clear_data);
    gSPDisplayList(NOW_FONT_DISP++, RSP_RDP_clear_data);
    gSPDisplayList(NOW_BG_OPA_DISP++, RSP_RDP_clear_data);
    gSPDisplayList(NOW_BG_XLU_DISP++, z_gsCPModeSet_Data[2]);
    gSPDisplayList(NOW_SHADOW_DISP++, z_gsCPModeSet_Data[2]);
    gSPDisplayList(NOW_LIGHT_DISP++, z_gsCPModeSet_Data[2]);

    gDPSetScissor(NOW_POLY_OPA_DISP++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    gDPSetScissor(NOW_POLY_XLU_DISP++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    gDPSetScissor(NOW_OVERLAY_DISP++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    gDPSetScissor(NOW_FONT_DISP++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    gDPSetScissor(NOW_SHADOW_DISP++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    gDPSetScissor(NOW_LIGHT_DISP++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    gDPSetScissor(NOW_BG_OPA_DISP++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    gDPSetScissor(NOW_BG_XLU_DISP++, G_SC_NON_INTERLACE, 0, 0, 640, 480);

    if (((game == NULL) || (fbdemo_mode < 2)) && (JW_setClearColor(clear_r, clear_g, clear_b))) {
        gDPSetCycleType(NOW_POLY_OPA_DISP++, G_CYC_FILL);
        gDPSetRenderMode(NOW_POLY_OPA_DISP++, G_RM_NOOP, G_RM_NOOP2);
        gDPSetFillColor(NOW_POLY_OPA_DISP++, (GPACK_RGBA5551(clear_r, clear_g, clear_b, 1) << 16) |
                                                 GPACK_RGBA5551(clear_r, clear_g, clear_b, 1));
        gDPFillRectangle(NOW_POLY_OPA_DISP++, 0, 0, 639, 479);
        gDPPipeSync(NOW_POLY_OPA_DISP++);
    }

    CLOSE_DISP(graph);

    mFont_Main_start(graph);
}
#endif

extern void fade_rgba8888_draw(Gfx** gfxp, u32 alpha) {
    static Gfx fade_gfx[6] = {
        gsDPPipeSync(),
        gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                             G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_1PRIMITIVE,
                         G_AC_NONE | G_ZS_PIXEL | G_RM_CLD_SURF | G_RM_CLD_SURF2),
        gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PRIMITIVE),
        gsDPFillRectangle(0, 0, 640, 480),
        gsDPPipeSync(),
        gsSPEndDisplayList(),
    };

    static Gfx fill_gfx[5] = {
        gsDPPipeSync(),
        gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                             G_TD_CLAMP | G_TP_NONE | G_CYC_FILL | G_PM_1PRIMITIVE,
                         G_AC_NONE | G_ZS_PIXEL | G_RM_NOOP | G_RM_NOOP2),
        gsDPFillRectangle(0, 0, 639, 479),
        gsDPPipeSync(),
        gsSPEndDisplayList(),
    };

    Gfx* gfx;

    if ((alpha & 0xFF) == 255) {
        u32 r = ((alpha >> 16) & 0xF800);
        u32 g = ((alpha >> 13) & 0x7FFC0);
        u32 b = (alpha >> 10) & 0x7FFFFF;
        u32 c = ((r | g | b | 1));
        u32 f = c | ((c & 0xFFFF) << 16);

        gfx = *gfxp;
        gDPSetFillColor(gfx, f);
        gSPDisplayList(gfx + 1, fill_gfx);
        *gfxp = gfx + 2;
    } else if ((alpha & 0xFF) != 0) {
        gfx = *gfxp;
        gDPSetColor(gfx, G_SETPRIMCOLOR, alpha);
        gSPDisplayList(gfx + 1, fade_gfx);
        *gfxp = gfx + 2;
    }
}

extern void fade_black_draw(Gfx** gfx, u32 alpha) {
    fade_rgba8888_draw(gfx, alpha);
}

extern Gfx* gfx_gDPFillRectangle1(Gfx* gfx, u32 ulx, u32 uly, u32 lrx, u32 lry) {
    gDPFillRectangle(gfx++, ulx << 1, uly << 1, lrx << 1, lry << 1);
    return gfx;
}

extern Gfx* gfx_gDPFillRectangleF(Gfx* gfx, u32 ulx, u32 uly, u32 lrx, u32 lry) {
    gDPFillRectangle(gfx++, ulx << 1, uly << 1, (lrx << 1) - 1, (lry << 1) - 1);
    return gfx;
}

extern Gfx* gfx_gSPTextureRectangle1(Gfx* gfx, int xl, int yl, int xh, int yh, int tile, int s, int t, int dsdx,
                                     int dtdy) {
    gSPTextureRectangle(gfx++, xl << 1, yl << 1, xh << 1, yh << 1, tile, s, t, dsdx >> 1, dtdy >> 1);
    return gfx;
}

extern Gfx* gfx_gSPScisTextureRectangle1(Gfx* gfx, int xl, int yl, int xh, int yh, int tile, int s, int t, int dsdx,
                                         int dtdy) {
    gSPScisTextureRectangle(gfx++, (s16)(xl << 1), (s16)(yl << 1), xh << 1, yh << 1, tile, s, t, dsdx >> 1, dtdy >> 1);
    return gfx;
}
