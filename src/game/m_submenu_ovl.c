#include "m_submenu_ovl.h"

#include "m_font.h"
#include "m_play.h"
#include "m_trademark.h"
#include "m_rcp.h"
#include "libultra/libultra.h"
#include "sys_matrix.h"
#include "libforest/emu64/emu64_wrapper.h"
#include "m_inventory_ovl.h"
#include "m_hboard_ovl.h"
#include "m_timeIn_ovl.h"
#include "m_ledit_ovl.h"
#include "m_map_ovl.h"
#include "m_notice_ovl.h"
#include "m_repay_ovl.h"
#include "m_mscore_ovl.h"
#include "m_birthday_ovl.h"
#include "m_editor_ovl.h"
#include "m_mailbox_ovl.h"
#include "m_board_ovl.h"
#include "m_address_ovl.h"
#include "m_haniwa_ovl.h"
#include "m_editEndChk_ovl.h"
#include "m_warning_ovl.h"
#include "m_cpmail_ovl.h"
#include "m_cpwarning_ovl.h"
#include "m_cpedit_ovl.h"
#include "m_catalog_ovl.h"
#include "m_music_ovl.h"
#include "m_bank_ovl.h"
#include "m_needlework_ovl.h"
#include "m_cporiginal_ovl.h"
#include "m_design_ovl.h"
#include "m_gba_ovl.h"
#include "m_diary_ovl.h"
#include "m_calendar_ovl.h"
#include "m_passwordMake_ovl.h"
#include "m_passwordChk_ovl.h"
#include "m_tag_ovl.h"
#include "m_hand_ovl.h"
#include "m_haniwaPortrait_ovl.h"

static Submenu_Overlay_c ovl_base;

static void mSM_setup_view(Submenu* submenu, GRAPH* graph, int init_flag) {
    Mtx* mtx;

    if (init_flag) {
        mtx = GRAPH_ALLOC_TYPE(graph, Mtx, 1);
        mFont_CulcOrthoMatrix(mtx);
        submenu->overlay->projection_matrix = mtx;
    } else {
        mtx = submenu->overlay->projection_matrix;
    }

    OPEN_POLY_OPA_DISP(graph);

    if (init_flag == FALSE) {
        View* view;

        if (submenu->mode != mSM_MODE_OTHER) {
            view = &((GAME_PLAY*)gamePT)->view;
        } else {
            view = &((GAME_TRADEMARK*)gamePT)->view; // I'm not sure this is the correct game subclass
        }

        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetScissor(POLY_OPA_DISP++, G_SC_NON_INTERLACE, view->screen.l, view->screen.top, view->screen.r,
                      view->screen.bottom);
#ifdef TARGET_PC
        /* Copy viewport into GRAPH_ALLOC buffer to avoid seg2k0 collision.
           GAME_PLAY is heap-allocated and its address can land in the N64
           segment range 0x03-0x0F, causing emu64 to misidentify the pointer. */
        {
            Vp* vp_copy = (Vp*)GRAPH_ALLOC_TYPE(graph, Vp, 1);
            *vp_copy = view->viewport;
            gSPViewport(POLY_OPA_DISP++, vp_copy);
        }
#else
        gSPViewport(POLY_OPA_DISP++, &view->viewport);
#endif
        gDPSetScissor(POLY_OPA_DISP++, G_SC_NON_INTERLACE, 0, 0, 640, 480);
    }

    gSPMatrix(POLY_OPA_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    CLOSE_POLY_OPA_DISP(graph);
}

static void mSM_change_view(GRAPH* graph, f32 eye_dist, f32 y_lookAt, f32 vp_x, f32 vp_y, s16 angle, int width,
                            int height) {
    static Vp viewport_data = { 0, 0, 511, 0, 0, 0, 511, 0 };

    static Lights0 light_data = {
        { 105, 90, 90, 0, 105, 90, 90, 0 },                      // Ambient
        { { 255, 255, 245, 0, 255, 255, 245, 0, 0, 60, 60, 0 } } // Light
    };

    Vp* viewport = GRAPH_ALLOC_TYPE(graph, Vp, 1);
    Mtx* mtx = GRAPH_ALLOC_TYPE(graph, Mtx, 1);
    Mtx* view_mtx = GRAPH_ALLOC_TYPE(graph, Mtx, 1);
    u16 persp_norm;
    f32 y_eye;
    f32 z_eye;

    if (viewport == NULL) {
        viewport = &viewport_data;
    } else {
        viewport->vp.vscale[0] = width << 1;
        viewport->vp.vtrans[0] = (width << 1) + (s16)(int)vp_x;

        viewport->vp.vscale[1] = height << 1;
        viewport->vp.vtrans[1] = (height << 1) + (s16)(int)vp_y;

        viewport->vp.vtrans[2] = 511;
        viewport->vp.vscale[2] = 511;

        viewport->vp.vtrans[3] = 0;
        viewport->vp.vscale[3] = 0;
    }

    OPEN_DISP(graph);

    gSPViewport(NOW_POLY_OPA_DISP++, viewport);

    CLOSE_DISP(graph);

    if (width != 256) {
        guPerspective(mtx, &persp_norm, 35.0f, (f32)width / (f32)height, 1.0f, 2000.0f, 1.0f);
    } else {
        guPerspective(mtx, &persp_norm, 20.0f, (f32)width / (f32)height, 100.0f, 800.0f, 1.0f);
    }

    OPEN_DISP(graph);

    gSPPerspNormalize(NOW_POLY_OPA_DISP++, persp_norm);
    gSPMatrix(NOW_POLY_OPA_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

    CLOSE_DISP(graph);

    if (angle == DEG2SHORT_ANGLE(90.0f)) {
        angle = 0x4100;
    } else if (angle == DEG2SHORT_ANGLE(-90.0f)) {
        angle = -0x3F00;
    }

    y_eye = y_lookAt + eye_dist * sin_s(angle);
    z_eye = eye_dist * cos_s(angle);

    if (angle < DEG2SHORT_ANGLE(-90.0f) || angle >= DEG2SHORT_ANGLE(90.0f)) {
        guLookAt(view_mtx, 0.0f, y_eye, z_eye, 0.0f, y_lookAt, 0.0f, 0.0f, -1.0f, 0.0f);
    } else {
        guLookAt(view_mtx, 0.0f, y_eye, z_eye, 0.0f, y_lookAt, 0.0f, 0.0f, 1.0f, 0.0f);
    }

    OPEN_DISP(graph);

    gSPMatrix(NOW_POLY_OPA_DISP++, view_mtx, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
    gSPSetLights0(NOW_POLY_OPA_DISP++, light_data);
    SET_POLY_OPA_DISP(gfx_set_fog_nosync(NOW_POLY_OPA_DISP++, 255, 255, 255, 255, 1000, 1000));

    CLOSE_DISP(graph);
}

static void mSM_set_char_matrix(GRAPH* graph) {
    OPEN_POLY_OPA_DISP(graph);

    gSPMatrix(POLY_OPA_DISP++, &Mtx_clear, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    CLOSE_POLY_OPA_DISP(graph);
}

static void mSM_cbuf_copy(GRAPH* graph, PreRender* prerender, int x, int y, int mode) {
    int temp;
    int temp0;
    int src_w;
    int src_h;
    int dst_w;
    int dst_h;
    int uls;
    int ult;
    int lrs;
    int lrt;
    int tmem_line;
    int y_min;
    int x_min;
    int x_max;
    int y_max;
    int tex_wd;
    void* src_buffer;
    void* dst_buffer;

    if (x >= (640 - 1) || x <= -prerender->width_bak || y <= -prerender->height_bak || y >= (480 - 1)) {
        return;
    }

    if (x < 0) {
        x_max = prerender->width_bak + x;
        x_min = -x;
        x = 0;
    } else {
        x_min = 0;

        if (x + prerender->width_bak >= 640) {
            x_max = 640 - x;
        } else {
            x_max = prerender->width_bak;
        }
    }

    if (y < 0) {
        y_max = prerender->height_bak + y;
        y_min = -y;
        y = 0;
    } else {
        y_min = 0;

        if (y + prerender->height_bak >= 480) {
            y_max = (480 - 1) - y;
        } else {
            y_max = prerender->height_bak;
        }
    }

    if (mode == 0) {
        src_w = 640;
        src_h = 480;
        dst_w = prerender->width_bak;
        dst_h = prerender->height_bak;
        uls = x;
        ult = y;
        lrt = y_min;
        lrs = x_min;
        src_buffer = prerender->framebuffer_bak;
    } else {
        src_w = prerender->width_bak;
        src_h = prerender->height_bak;
        dst_w = 640;
        dst_h = 480;
        uls = x_min;
        ult = y_min;
        lrt = y;
        lrs = x;
        dst_buffer = prerender->framebuffer_bak;
    }

    tmem_line = (4 << 10) / ((((x_max + 4) - 1) & ~(4 - 1)) * 2);
    temp0 = uls + (x_max - 1);
    tex_wd = (lrs + x_max - 1) << 2;
    lrs <<= 2;

    OPEN_DISP(graph);
    if (mode) {
        Gfx* gfx = NOW_POLY_OPA_DISP;

        prerender->width = 640;
        prerender->height = 480;
        PreRender_CopyRGBC(prerender, &gfx, x - x_min, y - y_min);

        SET_POLY_OPA_DISP(gfx);
    } else {
        gDPPipeSync(NEXT_POLY_OPA_DISP);
        gSPClearGeometryMode(NEXT_POLY_OPA_DISP, 0xFFFFFF);
        gDPSetOtherMode(NEXT_POLY_OPA_DISP,
                        G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                            G_TD_CLAMP | G_TP_NONE | G_CYC_COPY | G_PM_NPRIMITIVE,
                        G_AC_NONE | G_ZS_PRIM | G_RM_NOOP | G_RM_NOOP2);
        gDPSetColorImage(NEXT_POLY_OPA_DISP, G_IM_FMT_RGBA, G_IM_SIZ_16b, dst_w, src_buffer);
        gDPSetScissor(NEXT_POLY_OPA_DISP, G_SC_NON_INTERLACE, 0, 0, dst_w, dst_h);

        while (y_max > 0) {
            if (tmem_line > y_max) {
                tmem_line = y_max;
            }

            temp = ult + tmem_line - 1;
            gDPLoadTextureTile(NEXT_POLY_OPA_DISP, dst_buffer, G_IM_FMT_RGBA, G_IM_SIZ_16b, src_w, src_h, uls, ult,
                               temp0, temp, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                               G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

            gSPTextureRectangle(NEXT_POLY_OPA_DISP, lrs, lrt << 2, tex_wd, (lrt + tmem_line - 1) << 2, G_TX_RENDERTILE,
                                uls << 5, ult << 5, (4 << 10), (1 << 10));

            ult += tmem_line;
            lrt += tmem_line;
            y_max -= tmem_line;
        }
    }

    CLOSE_DISP(graph);
}

static void mSM_set_drawMode(GRAPH* graph, PreRender* prerender, f32 eye_dist, f32 eye_height, s16 angle) {
    static Vp viewport_data = { 0, 0, 511, 0, 0, 0, 511, 0 };
    static Lights1 light_data = {
        /* Ambient */
        105, 90, 90, /* ambient color */
        0,           /* pad */
        105, 90, 90, /* ambient color copy */
        0,           /* pad */

        /* Light */
        255, 255, 245, /* color */
        0,             /* pad */
        255, 255, 245, /* color copy */
        0,             /* pad */
        0, 60, 60,     /* direction */
        0              /* pad */
    };

    int width = prerender->width_bak;
    int height = prerender->height_bak;

    OPEN_DISP(graph);

    gDPPipeSync(NEXT_POLY_OPA_DISP);
    gSPClearGeometryMode(NEXT_POLY_OPA_DISP, 0xFFFFFF);
    gSPTexture(NEXT_POLY_OPA_DISP, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF);
    gDPSetCombineMode(NEXT_POLY_OPA_DISP, G_CC_SHADE, G_CC_SHADE);
    gDPSetOtherMode(NEXT_POLY_OPA_DISP,
                    G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                        G_TD_CLAMP | G_TP_PERSP | G_CYC_FILL | G_PM_NPRIMITIVE,
                    G_AC_NONE | G_ZS_PIXEL | G_RM_NOOP | G_RM_NOOP2);
    gSPLoadGeometryMode(NEXT_POLY_OPA_DISP, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH);
    gDPSetScissor(NEXT_POLY_OPA_DISP, G_SC_NON_INTERLACE, 0, 0, width, height);
    gSPClipRatio(NEXT_POLY_OPA_DISP, FRUSTRATIO_1);
    gDPSetColorImage(NEXT_POLY_OPA_DISP, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, prerender->zbuffer_bak);
    gDPSetFillColor(NEXT_POLY_OPA_DISP, ((0xFFFC) << 16) | (0xFFFC));
    gDPFillRectangle(NEXT_POLY_OPA_DISP, 0, 0, width - 1, height - 1);
    gDPPipeSync(NEXT_POLY_OPA_DISP);
    gDPSetColorImage(NEXT_POLY_OPA_DISP, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, prerender->framebuffer_bak);
    gDPPipeSync(NEXT_POLY_OPA_DISP);
    gDPSetDepthImage(NEXT_POLY_OPA_DISP, prerender->zbuffer_bak);

    {
        Vp* vp = GRAPH_ALLOC_TYPE(graph, Vp, 1);
        Mtx* projMtx = GRAPH_ALLOC_TYPE(graph, Mtx, 1);
        Mtx* viewMtx = GRAPH_ALLOC_TYPE(graph, Mtx, 1);
        u16 perspNorm;

        if (vp == NULL) {
            vp = &viewport_data;
        } else {
            vp->vp.vscale[0] = vp->vp.vtrans[0] = width * 2;
            vp->vp.vscale[1] = vp->vp.vtrans[1] = height * 2;
            vp->vp.vscale[2] = vp->vp.vtrans[2] = 511;
            vp->vp.vscale[3] = vp->vp.vtrans[3] = 0;
        }

        gSPViewport(NEXT_POLY_OPA_DISP, vp);

        if (width != 256) {
            guPerspective(projMtx, &perspNorm, 35.0f, (f32)width / (f32)height, 1.0f, 2000.0f, 1.0f);
        } else {
            guPerspective(projMtx, &perspNorm, 20.0f, (f32)width / (f32)height, 100.0f, 800.0f, 1.0f);
        }

        gSPPerspNormalize(NEXT_POLY_OPA_DISP, perspNorm);
        gSPMatrix(NEXT_POLY_OPA_DISP, projMtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);

        {
            f32 yEye;
            f32 zEye;

            if (angle == DEG2SHORT_ANGLE(90.0f)) {
                angle = 0x4100;
            } else if (angle == DEG2SHORT_ANGLE(-90.0f)) {
                angle = -0x3F00;
            }

            yEye = eye_height + eye_dist * sin_s(angle);
            zEye = eye_dist * cos_s(angle);

            if (angle < DEG2SHORT_ANGLE(-90.0f) || angle >= DEG2SHORT_ANGLE(90.0f)) {
                guLookAt(viewMtx, 0.0f, yEye, zEye, 0.0f, eye_height, 0.0f, 0.0f, -1.0f, 0.0f);
            } else {
                guLookAt(viewMtx, 0.0f, yEye, zEye, 0.0f, eye_height, 0.0f, 0.0f, 1.0f, 0.0f);
            }
        }

        gSPMatrix(NEXT_POLY_OPA_DISP, viewMtx, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
        gSPSetLights1(NEXT_POLY_OPA_DISP, light_data);
    }

    SET_POLY_OPA_DISP(gfx_set_fog_nosync(NEXT_POLY_OPA_DISP, 255, 255, 255, 255, 1000, 1000));

    CLOSE_DISP(graph);
}

static int mSM_get_groupNo(mActor_name_t item) {
    return ITEM_NAME_GET_INDEX(item);
}

typedef struct inventory_icon_info_s {
    u16* pal;
    u8* tex;
} mSM_inventory_icon_info_c;

extern u8 inv_win_mark_tex[];

static void mSM_set_dl_item(GRAPH* graph, f32 x, f32 y, f32 scale, mSM_inventory_icon_info_c* icon_info, u16* palette,
                            u8 l, rgba_t* color, int draw_shadow, int draw_mark) {
    f32 rect_xh;
    f32 rect_yh;
    int t;
    int scale_factor;

    OPEN_POLY_OPA_DISP(graph);

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetAlphaCompare(POLY_OPA_DISP++, G_AC_THRESHOLD);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, l, color->r, color->g, color->b, color->a);

    /* Check if we're drawing the shadow or the actual icon */
    if (draw_shadow) {
        gDPSetBlendColor(POLY_OPA_DISP++, 255, 255, 255, 40);
    } else {
        if (color->a == 255) {
            gDPSetBlendColor(POLY_OPA_DISP++, 255, 255, 255, 254);
            gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL0, PRIMITIVE, PRIM_LOD_FRAC, PRIMITIVE, 0, 0, 0, TEXEL0, TEXEL0,
                              PRIMITIVE, PRIM_LOD_FRAC, PRIMITIVE, 0, 0, 0, TEXEL0);
        } else {
            gDPSetBlendColor(POLY_OPA_DISP++, 255, 255, 255, 40);
            gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL0, PRIMITIVE, PRIM_LOD_FRAC, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0,
                              TEXEL0, PRIMITIVE, PRIM_LOD_FRAC, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
        }
    }

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetTextureLUT(POLY_OPA_DISP++, G_TT_RGBA16);
    gDPSetTexturePersp(POLY_OPA_DISP++, G_TP_NONE);
    gDPLoadTLUT_Dolphin(POLY_OPA_DISP++, 15, 16, 1, palette);
    gDPSetTextureImage_Dolphin(POLY_OPA_DISP++, G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, icon_info->tex);
    gDPSetTile_Dolphin(POLY_OPA_DISP++, G_DOLPHIN_TLUT_DEFAULT_MODE, G_TX_RENDERTILE, 15, GX_MIRROR, GX_MIRROR,
                       GX_CLAMP, GX_CLAMP);

    t = (int)(x * 0.975f);
    x = (160.0f + (f32)t) - scale * 12.0f;
    y = (120.0f - y) - scale * 12.0f;
    scale_factor = (int)((1.0f / scale) * 1365.333333333f);

    /* Draw 2D rectangle with icon texture */
    if (x < 320.0f) {
        f32 mod = scale * 24.0f;

        rect_xh = x + mod;
        rect_yh = y + mod;

        POLY_OPA_DISP = gfx_gSPScisTextureRectangle1(POLY_OPA_DISP, x * 4.0f, y * 4.0f, rect_xh * 4.0f, rect_yh * 4.0f,
                                                     G_TX_RENDERTILE, 0, 0, scale_factor, scale_factor);
    }

    if (draw_mark) {
        f32 frame_per = (((f32)(gamePT->frame_counter % 40)) * (1.0f / 40.0f)) * 2.0f;

        if (frame_per > 1.0f) {
            frame_per = 2.0f - frame_per;
        }

        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetTextureLUT(POLY_OPA_DISP++, G_TT_NONE);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, (int)(frame_per * 90.0f + 95.0f), 0, 255);
        gDPSetEnvColor(POLY_OPA_DISP++, (int)(frame_per * 60.0f), (int)(frame_per * 45.0f + 210.0f),
                       (int)(frame_per * 60.0f), 255);
        gDPSetAlphaCompare(POLY_OPA_DISP++, G_AC_NONE);
        gDPSetBlendColor(POLY_OPA_DISP++, 255, 255, 255, 8);
        gDPSetTextureLUT(POLY_OPA_DISP++, G_TT_NONE); // duplicate?
        gDPSetTextureImage_Dolphin(POLY_OPA_DISP++, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, inv_win_mark_tex);
        gDPSetTile_Dolphin(POLY_OPA_DISP++, G_DOLPHIN_TLUT_DEFAULT_MODE, G_TX_RENDERTILE, 0, GX_MIRROR, GX_MIRROR,
                           GX_CLAMP, GX_CLAMP);
        gDPSetBlendColor(POLY_OPA_DISP++, 255, 255, 255, 254); // bug? doesn't this undo the previous blend color set?
        gDPSetCombineMode(POLY_OPA_DISP++, G_CC_BLENDPEDECALA, G_CC_BLENDPEDECALA);

        /* Draw 2D rectangle with mark texture */
        if (x < 320.0f) {
            f32 mod = scale * 24.0f;

            rect_xh = x + mod;
            rect_yh = y + mod;

            POLY_OPA_DISP =
                gfx_gSPScisTextureRectangle1(POLY_OPA_DISP, x * 4.0f, y * 4.0f, rect_xh * 4.0f, rect_yh * 4.0f,
                                             G_TX_RENDERTILE, 0, 0, scale_factor, scale_factor);
        }
    }

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetTextureLUT(POLY_OPA_DISP++, G_TT_RGBA16);
    gDPSetAlphaCompare(POLY_OPA_DISP++, G_AC_NONE);
    gDPSetBlendColor(POLY_OPA_DISP++, 255, 255, 255, 8);
    gDPSetTexturePersp(POLY_OPA_DISP++, G_TP_PERSP);

    CLOSE_POLY_OPA_DISP(graph);
}

extern u16 inv_mwin_leaf_pal[];
extern u8 inv_mwin_leaf_tex[];

extern u16 inv_mwin_haniwa_pal[];
extern u8 inv_mwin_haniwa_tex[];

extern u16 inv_mwin_kaseki2_pal[];
extern u8 inv_mwin_kaseki2_tex[];

extern u16 inv_mwin_unknown_pal[];
extern u8 inv_mwin_unknown_tex[];

extern u16 inv_mwin_pbox2_pal[];
extern u8 inv_mwin_pbox_tex[];

extern u16 inv_mwin_pbox1_tex_rgb_ci4_pal[];
extern u8 inv_mwin_pbox1_tex_rgb_ci4[];

extern u16 inv_mwin_pbox2_tex_rgb_ci4_pal[];
extern u8 inv_mwin_pbox2_tex_rgb_ci4[];

extern u16 inv_mwin_pbox3_tex_rgb_ci4_pal[];
extern u8 inv_mwin_pbox3_tex_rgb_ci4[];

extern u16 inv_mwin_pbox4_tex_rgb_ci4_pal[];
extern u8 inv_mwin_pbox4_tex_rgb_ci4[];

extern u16 inv_mwin_pbox5_tex_rgb_ci4_pal[];
extern u8 inv_mwin_pbox5_tex_rgb_ci4[];

extern u16 inv_mwin_binsen1_pal[];
extern u8 inv_mwin_binsen1_tex[];
extern u8 inv_mwin_binsen2_tex[];
extern u8 inv_mwin_binsen3_tex[];
extern u8 inv_mwin_binsen4_tex[];

extern u16 inv_mwin_okane1_pal[];
extern u8 inv_mwin_okane1_tex[];
extern u8 inv_mwin_okane2_tex[];
extern u8 inv_mwin_okane3_tex[];
extern u8 inv_mwin_okane4_tex[];

extern u16 inv_mwin_mushi_pal[];
extern u8 inv_mwin_mushi_tex[];
extern u16 inv_mwin_ono_pal[];
extern u8 inv_mwin_ono_tex[];
extern u16 inv_mwin_scoop_pal[];
extern u8 inv_mwin_scoop_tex[];
extern u16 inv_mwin_turi_tex_pal[];
extern u8 inv_mwin_turi_tex[];
extern u16 inv_mwin_unbrella_pal[];
extern u8 inv_mwin_unbrella_tex[];
extern u16 inv_mwin_mushi_pal[];
extern u8 inv_mwin_mushi_tex[];
extern u16 inv_mwin_gmushi_pal[];
extern u8 inv_mwin_gmushi_tex[];
extern u16 inv_mwin_gono_pal[];
extern u8 inv_mwin_gono_tex[];
extern u16 inv_mwin_gscoop_pal[];
extern u8 inv_mwin_gscoop_tex[];
extern u16 inv_mwin_gturi_pal[];
extern u8 inv_mwin_gturi_tex[];
extern u16 inv_mwin_ono_pal[];
extern u8 inv_mwin_ono_tex[];
extern u8 inv_mwin_ono2_tex[];
extern u8 inv_mwin_ono3_tex[];
extern u16 inv_mwin_fuusen_pal[];
extern u8 inv_mwin_fuusen_tex[];
extern u16 inv_mwin_kazaguruma_pal[];
extern u8 inv_mwin_kazaguruma_tex[];
extern u16 inv_mwin_utiwa_pal[];
extern u8 inv_mwin_utiwa_tex[];

extern u16 inv_mwin_01funa_pal[];
extern u8 inv_mwin_01funa_tex[];
extern u16 inv_mwin_02masu_pal[];
extern u8 inv_mwin_02masu_tex[];
extern u16 inv_mwin_03koi_pal[];
extern u8 inv_mwin_03koi_tex[];
extern u16 inv_mwin_04nishiki_pal[];
extern u8 inv_mwin_04nishiki_tex[];
extern u16 inv_mwin_07namazu_pal[];
extern u8 inv_mwin_07namazu_tex[];
extern u16 inv_mwin_13bass_pal[];
extern u8 inv_mwin_13bass_tex[];
extern u16 inv_mwin_14bassm_pal[];
extern u8 inv_mwin_14bassm_tex[];
extern u16 inv_mwin_15bassl_pal[];
extern u8 inv_mwin_15bassl_tex[];
extern u16 inv_mwin_12gill_pal[];
extern u8 inv_mwin_12gill_tex[];
extern u16 inv_mwin_08oonamazu_pal[];
extern u8 inv_mwin_08oonamazu_tex[];
extern u16 inv_mwin_16raigyo_pal[];
extern u8 inv_mwin_16raigyo_tex[];
extern u16 inv_mwin_05nigoi_pal[];
extern u8 inv_mwin_05nigoi_tex[];
extern u16 inv_mwin_06ugui_pal[];
extern u8 inv_mwin_06ugui_tex[];
extern u16 inv_mwin_09oikawa_pal[];
extern u8 inv_mwin_09oikawa_tex[];
extern u16 inv_mwin_10tanago_pal[];
extern u8 inv_mwin_10tanago_tex[];
extern u16 inv_mwin_11dojyou_pal[];
extern u8 inv_mwin_11dojyou_tex[];
extern u16 inv_mwin_19wakasagi_pal[];
extern u8 inv_mwin_19wakasagi_tex[];
extern u16 inv_mwin_20ayu_pal[];
extern u8 inv_mwin_20ayu_tex[];
extern u16 inv_mwin_21yamame_pal[];
extern u8 inv_mwin_21yamame_tex[];
extern u16 inv_mwin_23iwana_pal[];
extern u8 inv_mwin_23iwana_tex[];
extern u16 inv_mwin_22niji_pal[];
extern u8 inv_mwin_22niji_tex[];
extern u16 inv_mwin_24itou_pal[];
extern u8 inv_mwin_24itou_tex[];
extern u16 inv_mwin_25sake_pal[];
extern u8 inv_mwin_25sake_tex[];
extern u16 inv_mwin_26kingyo_pal[];
extern u8 inv_mwin_26kingyo_tex[];
extern u16 inv_mwin_30pirania_pal[];
extern u8 inv_mwin_30pirania_tex[];
extern u16 inv_mwin_31aroana_pal[];
extern u8 inv_mwin_31aroana_tex[];
extern u16 inv_mwin_17unagi_pal[];
extern u8 inv_mwin_17unagi_tex[];
extern u16 inv_mwin_18donko_pal[];
extern u8 inv_mwin_18donko_tex[];
extern u16 inv_mwin_29angel_pal[];
extern u8 inv_mwin_29angel_tex[];
extern u16 inv_mwin_28gupi_pal[];
extern u8 inv_mwin_28gupi_tex[];
extern u16 inv_mwin_27demekin_pal[];
extern u8 inv_mwin_27demekin_tex[];
extern u16 inv_mwin_32kaseki_pal[];
extern u8 inv_mwin_32kaseki_tex[];
extern u16 inv_mwin_33zarigani_pal[];
extern u8 inv_mwin_33zarigani_tex[];
extern u16 inv_mwin_34kaeru_pal[];
extern u8 inv_mwin_34kaeru_tex[];
extern u16 inv_mwin_35medaka_pal[];
extern u8 inv_mwin_35medaka_tex[];
extern u16 inv_mwin_36kurage_pal[];
extern u8 inv_mwin_36kurage_tex[];
extern u16 inv_mwin_37suzuki_pal[];
extern u8 inv_mwin_37suzuki_tex[];
extern u16 inv_mwin_38tai_pal[];
extern u8 inv_mwin_38tai_tex[];
extern u16 inv_mwin_39ishidai_pal[];
extern u8 inv_mwin_39ishidai_tex[];
extern u16 inv_mwin_40piraruku_pal[];
extern u8 inv_mwin_40piraruku_tex[];

extern u16 inv_mwin_fuku3_pal[];
extern u8 inv_mwin_fuku3_tex[];

extern u16 inv_mwin_mtegami_pal[];
extern u8 inv_mwin_mtegami_tex[];

extern u16 inv_mwin_video_pal[];
extern u8 inv_mwin_video_tex[];

extern u16 inv_mwin_tetyou_pal[];
extern u8 inv_mwin_tetyou_tex[];

extern u16 inv_mwin_pokepi_pal[];
extern u8 inv_mwin_pokepi_tex[];

extern u16 inv_mwin_manga_pal[];
extern u8 inv_mwin_manga_tex[];

extern u16 inv_mwin_ehon_pal[];
extern u8 inv_mwin_ehon_tex[];

extern u16 inv_mwin_GB_pal[];
extern u8 inv_mwin_GB_tex[];

extern u16 inv_mwin_camera2_pal[];
extern u8 inv_mwin_camera_tex[];

extern u16 inv_mwin_tokei_pal[];
extern u8 inv_mwin_tokei_tex[];

extern u16 inv_mwin_hankati_pal[];
extern u8 inv_mwin_hankati_tex[];

extern u16 inv_mwin_glasses_pal[];
extern u8 inv_mwin_glasses_tex[];

extern u16 inv_mwin_aki_pal[];
extern u8 inv_mwin_akikan_tex[];

extern u16 inv_mwin_kutu_pal[];
extern u8 inv_mwin_kutu_tex[];

extern u8 inv_mwin_taiya_tex[];

extern u16 inv_mwin_kaseki_pal[];
extern u8 inv_mwin_kaseki_tex[];

extern u16 inv_mwin_ana_pal[];
extern u8 inv_mwin_ana_tex[];

extern u16 inv_mwin_hiougi_pal[];
extern u8 inv_mwin_hiougi_tex[];

extern u16 inv_mwin_hirako_pal[];
extern u8 inv_mwin_hirako_tex[];

extern u16 inv_mwin_hone_pal[];
extern u8 inv_mwin_hone_tex[];

extern u16 inv_mwin_hoshida_pal[];
extern u8 inv_mwin_hoshida_tex[];

extern u16 inv_mwin_sanddollar_pal[];
extern u8 inv_mwin_sanddollar_tex[];

extern u16 inv_mwin_syako_pal[];
extern u8 inv_mwin_syako_tex[];

extern u16 inv_mwin_hora_pal[];
extern u8 inv_mwin_hora_tex[];

extern u16 inv_mwin_sango_pal[];
extern u8 inv_mwin_sango_tex[];

extern u16 inv_mwin_kanban_pal[];
extern u8 inv_mwin_kanban_tex[];

extern u16 inv_mwin_taisou_pal[];
extern u8 inv_mwin_taisou_tex[];

extern u16 inv_mwin_fork_pal[];
extern u8 inv_mwin_fork_tex[];

extern u16 inv_mwin_jyuutan_pal[];
extern u8 inv_mwin_jyuutan_tex[];

extern u16 inv_mwin_kabe2_pal[];
extern u8 inv_mwin_kabe_tex[];

extern u16 inv_mwin_apple_pal[];
extern u8 inv_mwin_apple_tex[];

extern u16 inv_mwin_nuts_pal[];
extern u8 inv_mwin_nuts_tex[];

extern u16 inv_mwin_pear_pal[];
extern u8 inv_mwin_pear_tex[];

extern u16 inv_mwin_peach_pal[];
extern u8 inv_mwin_peach_tex[];

extern u16 inv_mwin_orange_pal[];
extern u8 inv_mwin_orange_tex[];

extern u16 inv_mwin_matutake2_pal[];
extern u8 inv_mwin_matutake_tex[];

extern u16 inv_mwin_ame_pal[];
extern u8 inv_mwin_ame_tex[];

extern u16 inv_mwin_yashi_pal[];
extern u8 inv_mwin_yashi_tex[];

extern u16 inv_mwin_naegi_pal[];
extern u8 inv_mwin_naegi_tex[];

extern u16 inv_mwin_cnaegi_pal[];
extern u8 inv_mwin_cnaegi_tex[];

extern u16 inv_mwin_seed_pal[];
extern u8 inv_mwin_seed_tex[];

extern u16 inv_mwin_onpu_pal[];
extern u8 inv_mwin_onpu_tex[];

extern u16 inv_mwin_nittki_pal[];
extern u8 inv_mwin_nittki_tex[];

extern u16 inv_mwin_1fukubiki_pal[];
extern u16 inv_mwin_2fukubiki_pal[];
extern u16 inv_mwin_3fukubiki_pal[];
extern u16 inv_mwin_4fukubiki_pal[];
extern u16 inv_mwin_5fukubiki_pal[];
extern u16 inv_mwin_6fukubiki_pal[];
extern u16 inv_mwin_7fukubiki_pal[];
extern u16 inv_mwin_8fukubiki_pal[];
extern u16 inv_mwin_9fukubiki_pal[];
extern u16 inv_mwin_10fukubiki_pal[];
extern u16 inv_mwin_11fukubiki_pal[];
extern u16 inv_mwin_12fukubiki_pal[];

extern u8 inv_mwin_1biki1_tex[];
extern u8 inv_mwin_1biki2_tex[];
extern u8 inv_mwin_1biki3_tex[];
extern u8 inv_mwin_1biki4_tex[];
extern u8 inv_mwin_1biki5_tex[];

extern u16 inv_mwin_01monshiro_pal[];
extern u8 inv_mwin_01monshiro_tex[];
extern u16 inv_mwin_02monki_pal[];
extern u8 inv_mwin_02monki_tex[];
extern u16 inv_mwin_03kiageha_pal[];
extern u8 inv_mwin_03kiageha_tex[];
extern u16 inv_mwin_04ohmurasaki_pal[];
extern u8 inv_mwin_04ohmurasaki_tex[];
extern u16 inv_mwin_06minmin_pal[];
extern u8 inv_mwin_06minmin_tex[];
extern u16 inv_mwin_07tukutuku_pal[];
extern u8 inv_mwin_07tukutuku_tex[];
extern u16 inv_mwin_08higurashi_pal[];
extern u8 inv_mwin_08higurashi_tex[];
extern u16 inv_mwin_05abura_pal[];
extern u8 inv_mwin_05abura_tex[];
extern u16 inv_mwin_23hati_pal[];
extern u8 inv_mwin_23hati_tex[];
extern u16 inv_mwin_10shiokara_pal[];
extern u8 inv_mwin_10shiokara_tex[];
extern u16 inv_mwin_09akiakane_pal[];
extern u8 inv_mwin_09akiakane_tex[];
extern u16 inv_mwin_11ginyanma_pal[];
extern u8 inv_mwin_11ginyanma_tex[];
extern u16 inv_mwin_12oniyanma_pal[];
extern u8 inv_mwin_12oniyanma_tex[];
extern u16 inv_mwin_20syouryou_pal[];
extern u8 inv_mwin_20syouryou_tex[];
extern u16 inv_mwin_21tonosama_pal[];
extern u8 inv_mwin_21tonosama_tex[];
extern u16 inv_mwin_13koorogi_pal[];
extern u8 inv_mwin_13koorogi_tex[];
extern u16 inv_mwin_14kirigirisu_pal[];
extern u8 inv_mwin_14kirigirisu_tex[];
extern u16 inv_mwin_16suzumushi_pal[];
extern u8 inv_mwin_16suzumushi_tex[];
extern u16 inv_mwin_15matumushi_pal[];
extern u8 inv_mwin_15matumushi_tex[];
extern u16 inv_mwin_25kanabun_pal[];
extern u8 inv_mwin_25kanabun_tex[];
extern u16 inv_mwin_28kabuto_pal[];
extern u8 inv_mwin_28kabuto_tex[];
extern u16 inv_mwin_29hirata_pal[];
extern u8 inv_mwin_29hirata_tex[];
extern u16 inv_mwin_27tamamushi_pal[];
extern u8 inv_mwin_27tamamushi_tex[];
extern u16 inv_mwin_26gomadara_pal[];
extern u8 inv_mwin_26gomadara_tex[];
extern u16 inv_mwin_17tentou_pal[];
extern u8 inv_mwin_17tentou_tex[];
extern u16 inv_mwin_18nanahoshi_pal[];
extern u8 inv_mwin_18nanahoshi_tex[];
extern u16 inv_mwin_19kamakiri_pal[];
extern u8 inv_mwin_19kamakiri_tex[];
extern u16 inv_mwin_24genji_pal[];
extern u8 inv_mwin_24genji_tex[];
extern u16 inv_mwin_22danna_pal[];
extern u8 inv_mwin_22danna_tex[];
extern u16 inv_mwin_30nokogiri_pal[];
extern u8 inv_mwin_30nokogiri_tex[];
extern u16 inv_mwin_31miyama_pal[];
extern u8 inv_mwin_31miyama_tex[];
extern u16 inv_mwin_32okuwa_pal[];
extern u8 inv_mwin_32okuwa_tex[];
extern u16 inv_mwin_33maimai_pal[];
extern u8 inv_mwin_33maimai_tex[];
extern u16 inv_mwin_34kera_pal[];
extern u8 inv_mwin_34kera_tex[];
extern u16 inv_mwin_35amenbo_pal[];
extern u8 inv_mwin_35amenbo_tex[];
extern u16 inv_mwin_36mino_pal[];
extern u8 inv_mwin_36mino_tex[];
extern u16 inv_mwin_37dango_pal[];
extern u8 inv_mwin_37dango_tex[];
extern u16 inv_mwin_38kumo_pal[];
extern u8 inv_mwin_38kumo_tex[];
extern u16 inv_mwin_39ari_pal[];
extern u8 inv_mwin_39ari_tex[];
extern u16 inv_mwin_40ka_pal[];
extern u8 inv_mwin_40ka_tex[];
extern u16 inv_mwin_hitodama_pal[];
extern u8 inv_mwin_hitodama1_tex[];
extern u8 inv_mwin_hitodama2_tex[];
extern u8 inv_mwin_hitodama3_tex[];
extern u8 inv_mwin_hitodama4_tex[];
extern u8 inv_mwin_hitodama5_tex[];

extern u16 inv_mwin_fukubukuro_pal[];
extern u8 inv_mwin_fukubukuro_tex[];

extern u16 inv_mwin_fukubukuro2_pal[];
extern u8 inv_mwin_fukubukuro_tex_rgb_ci4[];

extern u16 inv_mwin_fukubukuro2_tex_rgb_ci4_pal[];
extern u8 inv_mwin_fukubukuro2_tex_rgb_ci4[];

extern u16 inv_mwin_cabu1_pal[];
extern u8 inv_mwin_cabu1_tex[];
extern u8 inv_mwin_cabu2_tex[];
extern u8 inv_mwin_cabu3_tex[];

extern u16 inv_mwin_2cabu1_pal[];
extern u8 inv_mwin_2cabu1_tex[];

static void mSM_draw_item(GRAPH* graph, f32 pos_x, f32 pos_y, f32 scale, mActor_name_t item, int present_flag,
                          int color_flag, int anim_frame, int shadow_flag, int mark_flag) {
    static mSM_inventory_icon_info_c furniture_tex_data = { inv_mwin_leaf_pal, inv_mwin_leaf_tex };
    static mSM_inventory_icon_info_c haniwa_tex_data = { inv_mwin_haniwa_pal, inv_mwin_haniwa_tex };
    static mSM_inventory_icon_info_c fossil_tex_data = { inv_mwin_kaseki2_pal, inv_mwin_kaseki2_tex };
    static mSM_inventory_icon_info_c unknown_tex_data = { inv_mwin_unknown_pal, inv_mwin_unknown_tex };

    // clang-format off
    static mSM_inventory_icon_info_c present_tex_data[] = {
        { inv_mwin_pbox2_pal, inv_mwin_pbox_tex },
        { inv_mwin_pbox2_pal, inv_mwin_pbox_tex },
        { inv_mwin_pbox1_tex_rgb_ci4_pal, inv_mwin_pbox1_tex_rgb_ci4 },
        { inv_mwin_pbox1_tex_rgb_ci4_pal, inv_mwin_pbox1_tex_rgb_ci4 },
        { inv_mwin_pbox2_tex_rgb_ci4_pal, inv_mwin_pbox2_tex_rgb_ci4 },
        { inv_mwin_pbox2_tex_rgb_ci4_pal, inv_mwin_pbox2_tex_rgb_ci4 },
        { inv_mwin_pbox3_tex_rgb_ci4_pal, inv_mwin_pbox3_tex_rgb_ci4 },
        { inv_mwin_pbox3_tex_rgb_ci4_pal, inv_mwin_pbox3_tex_rgb_ci4 },
        { inv_mwin_pbox4_tex_rgb_ci4_pal, inv_mwin_pbox4_tex_rgb_ci4 },
        { inv_mwin_pbox4_tex_rgb_ci4_pal, inv_mwin_pbox4_tex_rgb_ci4 },
        { inv_mwin_pbox5_tex_rgb_ci4_pal, inv_mwin_pbox5_tex_rgb_ci4 },
        { inv_mwin_pbox5_tex_rgb_ci4_pal, inv_mwin_pbox5_tex_rgb_ci4 },
    };
    // clang-format on

    // clang-format off
    static mSM_inventory_icon_info_c binsen_tex_table[] = {
        { inv_mwin_binsen1_pal, inv_mwin_binsen1_tex },
        { inv_mwin_binsen1_pal, inv_mwin_binsen2_tex },
        { inv_mwin_binsen1_pal, inv_mwin_binsen3_tex },
        { inv_mwin_binsen1_pal, inv_mwin_binsen4_tex },
    };
    // clang-format on

    // clang-format off
    static mSM_inventory_icon_info_c money_tex_table[] = {
        { inv_mwin_okane1_pal, inv_mwin_okane1_tex },
        { inv_mwin_okane1_pal, inv_mwin_okane2_tex },
        { inv_mwin_okane1_pal, inv_mwin_okane3_tex },
        { inv_mwin_okane1_pal, inv_mwin_okane4_tex },
    };
    // clang-format on

    // clang-format off
    static mSM_inventory_icon_info_c tool_tex_table[] = {
        { inv_mwin_mushi_pal, inv_mwin_mushi_tex },
        { inv_mwin_ono_pal, inv_mwin_ono_tex },
        { inv_mwin_scoop_pal, inv_mwin_scoop_tex },
        { inv_mwin_turi_tex_pal, inv_mwin_turi_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_unbrella_pal, inv_mwin_unbrella_tex },
        { inv_mwin_mushi_pal, inv_mwin_mushi_tex },
        { inv_mwin_mushi_pal, inv_mwin_mushi_tex },
        { inv_mwin_mushi_pal, inv_mwin_mushi_tex },
        { inv_mwin_mushi_pal, inv_mwin_mushi_tex },
        { inv_mwin_mushi_pal, inv_mwin_mushi_tex },
        { inv_mwin_mushi_pal, inv_mwin_mushi_tex },
        { inv_mwin_mushi_pal, inv_mwin_mushi_tex },
        { inv_mwin_mushi_pal, inv_mwin_mushi_tex },
        { inv_mwin_mushi_pal, inv_mwin_mushi_tex },
        { inv_mwin_mushi_pal, inv_mwin_mushi_tex },
        { inv_mwin_mushi_pal, inv_mwin_mushi_tex },
        { inv_mwin_mushi_pal, inv_mwin_mushi_tex },
        { inv_mwin_mushi_pal, inv_mwin_mushi_tex },
        { inv_mwin_gmushi_pal, inv_mwin_gmushi_tex },
        { inv_mwin_gono_pal, inv_mwin_gono_tex },
        { inv_mwin_gscoop_pal, inv_mwin_gscoop_tex },
        { inv_mwin_gturi_pal, inv_mwin_gturi_tex },
        { inv_mwin_ono_pal, inv_mwin_ono_tex },
        { inv_mwin_ono_pal, inv_mwin_ono2_tex },
        { inv_mwin_ono_pal, inv_mwin_ono2_tex },
        { inv_mwin_ono_pal, inv_mwin_ono2_tex },
        { inv_mwin_ono_pal, inv_mwin_ono3_tex },
        { inv_mwin_ono_pal, inv_mwin_ono3_tex },
        { inv_mwin_ono_pal, inv_mwin_ono3_tex },
        { inv_mwin_fuusen_pal, inv_mwin_fuusen_tex },
        { inv_mwin_fuusen_pal, inv_mwin_fuusen_tex },
        { inv_mwin_fuusen_pal, inv_mwin_fuusen_tex },
        { inv_mwin_fuusen_pal, inv_mwin_fuusen_tex },
        { inv_mwin_fuusen_pal, inv_mwin_fuusen_tex },
        { inv_mwin_fuusen_pal, inv_mwin_fuusen_tex },
        { inv_mwin_fuusen_pal, inv_mwin_fuusen_tex },
        { inv_mwin_fuusen_pal, inv_mwin_fuusen_tex },
        { inv_mwin_kazaguruma_pal, inv_mwin_kazaguruma_tex },
        { inv_mwin_kazaguruma_pal, inv_mwin_kazaguruma_tex },
        { inv_mwin_kazaguruma_pal, inv_mwin_kazaguruma_tex },
        { inv_mwin_kazaguruma_pal, inv_mwin_kazaguruma_tex },
        { inv_mwin_kazaguruma_pal, inv_mwin_kazaguruma_tex },
        { inv_mwin_kazaguruma_pal, inv_mwin_kazaguruma_tex },
        { inv_mwin_kazaguruma_pal, inv_mwin_kazaguruma_tex },
        { inv_mwin_kazaguruma_pal, inv_mwin_kazaguruma_tex },
        { inv_mwin_utiwa_pal, inv_mwin_utiwa_tex },
        { inv_mwin_utiwa_pal, inv_mwin_utiwa_tex },
        { inv_mwin_utiwa_pal, inv_mwin_utiwa_tex },
        { inv_mwin_utiwa_pal, inv_mwin_utiwa_tex },
        { inv_mwin_utiwa_pal, inv_mwin_utiwa_tex },
        { inv_mwin_utiwa_pal, inv_mwin_utiwa_tex },
        { inv_mwin_utiwa_pal, inv_mwin_utiwa_tex },
        { inv_mwin_utiwa_pal, inv_mwin_utiwa_tex },
    };
    // clang-format on

    // clang-format off
    static mSM_inventory_icon_info_c fish_tex_table[] = {
        { inv_mwin_01funa_pal, inv_mwin_01funa_tex },
        { inv_mwin_02masu_pal, inv_mwin_02masu_tex },
        { inv_mwin_03koi_pal, inv_mwin_03koi_tex },
        { inv_mwin_04nishiki_pal, inv_mwin_04nishiki_tex },
        { inv_mwin_07namazu_pal, inv_mwin_07namazu_tex },
        { inv_mwin_13bass_pal, inv_mwin_13bass_tex },
        { inv_mwin_14bassm_pal, inv_mwin_14bassm_tex },
        { inv_mwin_15bassl_pal, inv_mwin_15bassl_tex },
        { inv_mwin_12gill_pal, inv_mwin_12gill_tex },
        { inv_mwin_08oonamazu_pal, inv_mwin_08oonamazu_tex },
        { inv_mwin_16raigyo_pal, inv_mwin_16raigyo_tex },
        { inv_mwin_05nigoi_pal, inv_mwin_05nigoi_tex },
        { inv_mwin_06ugui_pal, inv_mwin_06ugui_tex },
        { inv_mwin_09oikawa_pal, inv_mwin_09oikawa_tex },
        { inv_mwin_10tanago_pal, inv_mwin_10tanago_tex },
        { inv_mwin_11dojyou_pal, inv_mwin_11dojyou_tex },
        { inv_mwin_19wakasagi_pal, inv_mwin_19wakasagi_tex },
        { inv_mwin_20ayu_pal, inv_mwin_20ayu_tex },
        { inv_mwin_21yamame_pal, inv_mwin_21yamame_tex },
        { inv_mwin_23iwana_pal, inv_mwin_23iwana_tex },
        { inv_mwin_22niji_pal, inv_mwin_22niji_tex },
        { inv_mwin_24itou_pal, inv_mwin_24itou_tex },
        { inv_mwin_25sake_pal, inv_mwin_25sake_tex },
        { inv_mwin_26kingyo_pal, inv_mwin_26kingyo_tex },
        { inv_mwin_30pirania_pal, inv_mwin_30pirania_tex },
        { inv_mwin_31aroana_pal, inv_mwin_31aroana_tex },
        { inv_mwin_17unagi_pal, inv_mwin_17unagi_tex },
        { inv_mwin_18donko_pal, inv_mwin_18donko_tex },
        { inv_mwin_29angel_pal, inv_mwin_29angel_tex },
        { inv_mwin_28gupi_pal, inv_mwin_28gupi_tex },
        { inv_mwin_27demekin_pal, inv_mwin_27demekin_tex },
        { inv_mwin_32kaseki_pal, inv_mwin_32kaseki_tex },
        { inv_mwin_33zarigani_pal, inv_mwin_33zarigani_tex },
        { inv_mwin_34kaeru_pal, inv_mwin_34kaeru_tex },
        { inv_mwin_35medaka_pal, inv_mwin_35medaka_tex },
        { inv_mwin_36kurage_pal, inv_mwin_36kurage_tex },
        { inv_mwin_37suzuki_pal, inv_mwin_37suzuki_tex },
        { inv_mwin_38tai_pal, inv_mwin_38tai_tex },
        { inv_mwin_39ishidai_pal, inv_mwin_39ishidai_tex },
        { inv_mwin_40piraruku_pal, inv_mwin_40piraruku_tex },
    };
    // clang-format on

    // clang-format off
    static mSM_inventory_icon_info_c cloth_tex_table[1] = {
        { inv_mwin_fuku3_pal, inv_mwin_fuku3_tex },
    };
    // clang-format on

    // clang-format off
    static mSM_inventory_icon_info_c etc_tex_table[] = {
        { inv_mwin_mtegami_pal, inv_mwin_mtegami_tex },
        { inv_mwin_fuku3_pal, inv_mwin_fuku3_tex },
        { inv_mwin_okane1_pal, inv_mwin_okane1_tex },
        { inv_mwin_video_pal, inv_mwin_video_tex },
        { inv_mwin_tetyou_pal, inv_mwin_tetyou_tex },
        { inv_mwin_pokepi_pal, inv_mwin_pokepi_tex },
        { inv_mwin_manga_pal, inv_mwin_manga_tex },
        { inv_mwin_ehon_pal, inv_mwin_ehon_tex },
        { inv_mwin_GB_pal, inv_mwin_GB_tex },
        { inv_mwin_camera2_pal, inv_mwin_camera_tex },
        { inv_mwin_tokei_pal, inv_mwin_tokei_tex },
        { inv_mwin_hankati_pal, inv_mwin_hankati_tex },
        { inv_mwin_glasses_pal, inv_mwin_glasses_tex },
        { inv_mwin_okane1_pal, inv_mwin_okane1_tex },
        { inv_mwin_aki_pal, inv_mwin_akikan_tex },
        { inv_mwin_kutu_pal, inv_mwin_kutu_tex },
        { inv_mwin_kutu_pal, inv_mwin_taiya_tex },
        { inv_mwin_kaseki_pal, inv_mwin_kaseki_tex },
        { inv_mwin_ana_pal, inv_mwin_ana_tex },
        { inv_mwin_ana_pal, inv_mwin_ana_tex },
        { inv_mwin_hiougi_pal, inv_mwin_hiougi_tex },
        { inv_mwin_hirako_pal, inv_mwin_hirako_tex },
        { inv_mwin_hone_pal, inv_mwin_hone_tex },
        { inv_mwin_hoshida_pal, inv_mwin_hoshida_tex },
        { inv_mwin_sanddollar_pal, inv_mwin_sanddollar_tex },
        { inv_mwin_syako_pal, inv_mwin_syako_tex },
        { inv_mwin_hora_pal, inv_mwin_hora_tex },
        { inv_mwin_sango_pal, inv_mwin_sango_tex },
        { inv_mwin_pbox2_pal, inv_mwin_pbox_tex },
        { inv_mwin_pbox2_pal, inv_mwin_pbox_tex },
        { inv_mwin_kanban_pal, inv_mwin_kanban_tex },
        { inv_mwin_pbox2_pal, inv_mwin_pbox_tex },
        { inv_mwin_pbox2_pal, inv_mwin_pbox_tex },
        { inv_mwin_pbox2_pal, inv_mwin_pbox_tex },
        { inv_mwin_pbox2_pal, inv_mwin_pbox_tex },
        { inv_mwin_taisou_pal, inv_mwin_taisou_tex },
        { inv_mwin_taisou_pal, inv_mwin_taisou_tex },
        { inv_mwin_taisou_pal, inv_mwin_taisou_tex },
        { inv_mwin_taisou_pal, inv_mwin_taisou_tex },
        { inv_mwin_taisou_pal, inv_mwin_taisou_tex },
        { inv_mwin_taisou_pal, inv_mwin_taisou_tex },
        { inv_mwin_taisou_pal, inv_mwin_taisou_tex },
        { inv_mwin_taisou_pal, inv_mwin_taisou_tex },
        { inv_mwin_taisou_pal, inv_mwin_taisou_tex },
        { inv_mwin_taisou_pal, inv_mwin_taisou_tex },
        { inv_mwin_taisou_pal, inv_mwin_taisou_tex },
        { inv_mwin_taisou_pal, inv_mwin_taisou_tex },
        { inv_mwin_taisou_pal, inv_mwin_taisou_tex },
        { inv_mwin_fork_pal, inv_mwin_fork_tex },
    };
    // clang-format on

    // clang-format off
    static mSM_inventory_icon_info_c carpet_tex_table[1] = {
        { inv_mwin_jyuutan_pal, inv_mwin_jyuutan_tex },
    };
    // clang-format on

    // clang-format off
    static mSM_inventory_icon_info_c wall_tex_table[1] = {
        { inv_mwin_kabe2_pal, inv_mwin_kabe_tex },
    };
    // clang-format on

    // clang-format off
    static mSM_inventory_icon_info_c food_tex_table[] = {
        { inv_mwin_apple_pal, inv_mwin_apple_tex },
        { inv_mwin_nuts_pal, inv_mwin_nuts_tex },
        { inv_mwin_pear_pal, inv_mwin_pear_tex },
        { inv_mwin_peach_pal, inv_mwin_peach_tex },
        { inv_mwin_orange_pal, inv_mwin_orange_tex },
        { inv_mwin_matutake2_pal, inv_mwin_matutake_tex },
        { inv_mwin_ame_pal, inv_mwin_ame_tex },
        { inv_mwin_yashi_pal, inv_mwin_yashi_tex },
    };
    // clang-format on

    // clang-format off
    static mSM_inventory_icon_info_c plant_tex_table[] = {
        { inv_mwin_naegi_pal, inv_mwin_naegi_tex },
        { inv_mwin_cnaegi_pal, inv_mwin_cnaegi_tex },
        { inv_mwin_seed_pal, inv_mwin_seed_tex },
        { inv_mwin_seed_pal, inv_mwin_seed_tex },
        { inv_mwin_seed_pal, inv_mwin_seed_tex },
        { inv_mwin_seed_pal, inv_mwin_seed_tex },
        { inv_mwin_seed_pal, inv_mwin_seed_tex },
        { inv_mwin_seed_pal, inv_mwin_seed_tex },
        { inv_mwin_seed_pal, inv_mwin_seed_tex },
        { inv_mwin_seed_pal, inv_mwin_seed_tex },
        { inv_mwin_seed_pal, inv_mwin_seed_tex },
    };
    // clang-format on

    // clang-format off
    static mSM_inventory_icon_info_c minidisk_tex_table[1] = {
        { inv_mwin_onpu_pal, inv_mwin_onpu_tex },
    };
    // clang-format on

    // clang-format off
    static mSM_inventory_icon_info_c etc2_tex_table[] = {
        { inv_mwin_nittki_pal, inv_mwin_nittki_tex },
        { inv_mwin_nittki_pal, inv_mwin_nittki_tex },
        { inv_mwin_nittki_pal, inv_mwin_nittki_tex },
        { inv_mwin_nittki_pal, inv_mwin_nittki_tex },
        { inv_mwin_nittki_pal, inv_mwin_nittki_tex },
        { inv_mwin_nittki_pal, inv_mwin_nittki_tex },
        { inv_mwin_nittki_pal, inv_mwin_nittki_tex },
        { inv_mwin_nittki_pal, inv_mwin_nittki_tex },
        { inv_mwin_nittki_pal, inv_mwin_nittki_tex },
        { inv_mwin_nittki_pal, inv_mwin_nittki_tex },
        { inv_mwin_nittki_pal, inv_mwin_nittki_tex },
        { inv_mwin_nittki_pal, inv_mwin_nittki_tex },
        { inv_mwin_nittki_pal, inv_mwin_nittki_tex },
        { inv_mwin_nittki_pal, inv_mwin_nittki_tex },
        { inv_mwin_nittki_pal, inv_mwin_nittki_tex },
        { inv_mwin_nittki_pal, inv_mwin_nittki_tex },
    };
    // clang-format on

    // clang-format off
    static mSM_inventory_icon_info_c ticket_tex_table[] = {
        { inv_mwin_1fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_1fukubiki_pal, inv_mwin_1biki2_tex },
        { inv_mwin_1fukubiki_pal, inv_mwin_1biki3_tex },
        { inv_mwin_1fukubiki_pal, inv_mwin_1biki4_tex },
        { inv_mwin_1fukubiki_pal, inv_mwin_1biki5_tex },
        { inv_mwin_1fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_1fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_1fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_2fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_2fukubiki_pal, inv_mwin_1biki2_tex },
        { inv_mwin_2fukubiki_pal, inv_mwin_1biki3_tex },
        { inv_mwin_2fukubiki_pal, inv_mwin_1biki4_tex },
        { inv_mwin_2fukubiki_pal, inv_mwin_1biki5_tex },
        { inv_mwin_2fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_2fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_2fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_3fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_3fukubiki_pal, inv_mwin_1biki2_tex },
        { inv_mwin_3fukubiki_pal, inv_mwin_1biki3_tex },
        { inv_mwin_3fukubiki_pal, inv_mwin_1biki4_tex },
        { inv_mwin_3fukubiki_pal, inv_mwin_1biki5_tex },
        { inv_mwin_3fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_3fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_3fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_4fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_4fukubiki_pal, inv_mwin_1biki2_tex },
        { inv_mwin_4fukubiki_pal, inv_mwin_1biki3_tex },
        { inv_mwin_4fukubiki_pal, inv_mwin_1biki4_tex },
        { inv_mwin_4fukubiki_pal, inv_mwin_1biki5_tex },
        { inv_mwin_4fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_4fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_4fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_5fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_5fukubiki_pal, inv_mwin_1biki2_tex },
        { inv_mwin_5fukubiki_pal, inv_mwin_1biki3_tex },
        { inv_mwin_5fukubiki_pal, inv_mwin_1biki4_tex },
        { inv_mwin_5fukubiki_pal, inv_mwin_1biki5_tex },
        { inv_mwin_5fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_5fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_5fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_6fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_6fukubiki_pal, inv_mwin_1biki2_tex },
        { inv_mwin_6fukubiki_pal, inv_mwin_1biki3_tex },
        { inv_mwin_6fukubiki_pal, inv_mwin_1biki4_tex },
        { inv_mwin_6fukubiki_pal, inv_mwin_1biki5_tex },
        { inv_mwin_6fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_6fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_6fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_7fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_7fukubiki_pal, inv_mwin_1biki2_tex },
        { inv_mwin_7fukubiki_pal, inv_mwin_1biki3_tex },
        { inv_mwin_7fukubiki_pal, inv_mwin_1biki4_tex },
        { inv_mwin_7fukubiki_pal, inv_mwin_1biki5_tex },
        { inv_mwin_7fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_7fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_7fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_8fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_8fukubiki_pal, inv_mwin_1biki2_tex },
        { inv_mwin_8fukubiki_pal, inv_mwin_1biki3_tex },
        { inv_mwin_8fukubiki_pal, inv_mwin_1biki4_tex },
        { inv_mwin_8fukubiki_pal, inv_mwin_1biki5_tex },
        { inv_mwin_8fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_8fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_8fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_9fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_9fukubiki_pal, inv_mwin_1biki2_tex },
        { inv_mwin_9fukubiki_pal, inv_mwin_1biki3_tex },
        { inv_mwin_9fukubiki_pal, inv_mwin_1biki4_tex },
        { inv_mwin_9fukubiki_pal, inv_mwin_1biki5_tex },
        { inv_mwin_9fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_9fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_9fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_10fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_10fukubiki_pal, inv_mwin_1biki2_tex },
        { inv_mwin_10fukubiki_pal, inv_mwin_1biki3_tex },
        { inv_mwin_10fukubiki_pal, inv_mwin_1biki4_tex },
        { inv_mwin_10fukubiki_pal, inv_mwin_1biki5_tex },
        { inv_mwin_10fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_10fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_10fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_11fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_11fukubiki_pal, inv_mwin_1biki2_tex },
        { inv_mwin_11fukubiki_pal, inv_mwin_1biki3_tex },
        { inv_mwin_11fukubiki_pal, inv_mwin_1biki4_tex },
        { inv_mwin_11fukubiki_pal, inv_mwin_1biki5_tex },
        { inv_mwin_11fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_11fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_11fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_12fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_12fukubiki_pal, inv_mwin_1biki2_tex },
        { inv_mwin_12fukubiki_pal, inv_mwin_1biki3_tex },
        { inv_mwin_12fukubiki_pal, inv_mwin_1biki4_tex },
        { inv_mwin_12fukubiki_pal, inv_mwin_1biki5_tex },
        { inv_mwin_12fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_12fukubiki_pal, inv_mwin_1biki1_tex },
        { inv_mwin_12fukubiki_pal, inv_mwin_1biki1_tex },
    };
    // clang-format on

    // clang-format off
    static mSM_inventory_icon_info_c insect_tex_table[] = {
        { inv_mwin_01monshiro_pal, inv_mwin_01monshiro_tex },
        { inv_mwin_02monki_pal, inv_mwin_02monki_tex },
        { inv_mwin_03kiageha_pal, inv_mwin_03kiageha_tex },
        { inv_mwin_04ohmurasaki_pal, inv_mwin_04ohmurasaki_tex },
        { inv_mwin_06minmin_pal, inv_mwin_06minmin_tex },
        { inv_mwin_07tukutuku_pal, inv_mwin_07tukutuku_tex },
        { inv_mwin_08higurashi_pal, inv_mwin_08higurashi_tex },
        { inv_mwin_05abura_pal, inv_mwin_05abura_tex },
        { inv_mwin_23hati_pal, inv_mwin_23hati_tex },
        { inv_mwin_10shiokara_pal, inv_mwin_10shiokara_tex },
        { inv_mwin_09akiakane_pal, inv_mwin_09akiakane_tex },
        { inv_mwin_11ginyanma_pal, inv_mwin_11ginyanma_tex },
        { inv_mwin_12oniyanma_pal, inv_mwin_12oniyanma_tex },
        { inv_mwin_20syouryou_pal, inv_mwin_20syouryou_tex },
        { inv_mwin_21tonosama_pal, inv_mwin_21tonosama_tex },
        { inv_mwin_13koorogi_pal, inv_mwin_13koorogi_tex },
        { inv_mwin_14kirigirisu_pal, inv_mwin_14kirigirisu_tex },
        { inv_mwin_16suzumushi_pal, inv_mwin_16suzumushi_tex },
        { inv_mwin_15matumushi_pal, inv_mwin_15matumushi_tex },
        { inv_mwin_25kanabun_pal, inv_mwin_25kanabun_tex },
        { inv_mwin_28kabuto_pal, inv_mwin_28kabuto_tex },
        { inv_mwin_29hirata_pal, inv_mwin_29hirata_tex },
        { inv_mwin_27tamamushi_pal, inv_mwin_27tamamushi_tex },
        { inv_mwin_26gomadara_pal, inv_mwin_26gomadara_tex },
        { inv_mwin_17tentou_pal, inv_mwin_17tentou_tex },
        { inv_mwin_18nanahoshi_pal, inv_mwin_18nanahoshi_tex },
        { inv_mwin_19kamakiri_pal, inv_mwin_19kamakiri_tex },
        { inv_mwin_24genji_pal, inv_mwin_24genji_tex },
        { inv_mwin_22danna_pal, inv_mwin_22danna_tex },
        { inv_mwin_30nokogiri_pal, inv_mwin_30nokogiri_tex },
        { inv_mwin_31miyama_pal, inv_mwin_31miyama_tex },
        { inv_mwin_32okuwa_pal, inv_mwin_32okuwa_tex },
        { inv_mwin_33maimai_pal, inv_mwin_33maimai_tex },
        { inv_mwin_34kera_pal, inv_mwin_34kera_tex },
        { inv_mwin_35amenbo_pal, inv_mwin_35amenbo_tex },
        { inv_mwin_36mino_pal, inv_mwin_36mino_tex },
        { inv_mwin_37dango_pal, inv_mwin_37dango_tex },
        { inv_mwin_38kumo_pal, inv_mwin_38kumo_tex },
        { inv_mwin_39ari_pal, inv_mwin_39ari_tex },
        { inv_mwin_40ka_pal, inv_mwin_40ka_tex },
        { inv_mwin_hitodama_pal, inv_mwin_hitodama1_tex },
        { inv_mwin_hitodama_pal, inv_mwin_hitodama2_tex },
        { inv_mwin_hitodama_pal, inv_mwin_hitodama3_tex },
        { inv_mwin_hitodama_pal, inv_mwin_hitodama4_tex },
        { inv_mwin_hitodama_pal, inv_mwin_hitodama5_tex },
    };
    // clang-format on

    // clang-format off
    static mSM_inventory_icon_info_c hukuro_tex_table[] = {
        { inv_mwin_fukubukuro_pal, inv_mwin_fukubukuro_tex },
        { inv_mwin_fukubukuro_pal, inv_mwin_fukubukuro_tex },
        { inv_mwin_fukubukuro2_pal, inv_mwin_fukubukuro_tex_rgb_ci4 },
        { inv_mwin_fukubukuro2_pal, inv_mwin_fukubukuro_tex_rgb_ci4 },
        { inv_mwin_fukubukuro2_tex_rgb_ci4_pal, inv_mwin_fukubukuro2_tex_rgb_ci4 },
        { inv_mwin_fukubukuro2_tex_rgb_ci4_pal, inv_mwin_fukubukuro2_tex_rgb_ci4 },
    };
    // clang-format on

    // clang-format off
    static mSM_inventory_icon_info_c kabu_tex_table[] = {
        { inv_mwin_cabu1_pal, inv_mwin_cabu1_tex },
        { inv_mwin_cabu1_pal, inv_mwin_cabu2_tex },
        { inv_mwin_cabu1_pal, inv_mwin_cabu3_tex },
        { inv_mwin_2cabu1_pal, inv_mwin_2cabu1_tex },
    };
    // clang-format on

    // clang-format off
    static mSM_inventory_icon_info_c* item_tex_data_table[] = {
        binsen_tex_table,
        money_tex_table,
        tool_tex_table,
        fish_tex_table,
        cloth_tex_table,
        etc_tex_table,
        carpet_tex_table,
        wall_tex_table,
        food_tex_table,
        plant_tex_table,
        minidisk_tex_table,
        etc2_tex_table,
        ticket_tex_table,
        insect_tex_table,
        hukuro_tex_table,
        kabu_tex_table,
    };
    // clang-format on

    mSM_inventory_icon_info_c* icon;
    u16* palette;
    rgba_t color;
    int category = -1;
    int alpha_flag = FALSE;
    u8 l;

    if (scale < 0.05f) {
        return;
    }

    if (present_flag) {
        if (anim_frame > 11) {
            /* Start fading out */
            icon = &present_tex_data[11];
            if (anim_frame > 22) {
                alpha_flag = TRUE;
            }
        } else {
            icon = &present_tex_data[anim_frame];
        }
    } else {
        if (item >= HANIWA_START && item <= HANIWA_END) {
            icon = &haniwa_tex_data;
        } else if (item >= FTR_DINO_START && item <= FTR_DINO_END) {
            icon = &fossil_tex_data;
        } else if (mNT_check_unknown(item) == TRUE) {
            icon = &unknown_tex_data;
        } else if (ITEM_IS_FTR(item)) {
            icon = &furniture_tex_data;
        } else {
            int groupNo = mSM_get_groupNo(item);

            category = ITEM_NAME_GET_CAT(item);
            switch (category) {
                case ITEM1_CAT_HUKUBUKURO:
                    icon = &item_tex_data_table[category][anim_frame];
                    break;
                case ITEM1_CAT_PAPER:
                    icon = &item_tex_data_table[category][1 + PAPER2STACK(item - ITM_PAPER_START)] - 1;
                    break;
                case ITEM1_CAT_CLOTH:
                case ITEM1_CAT_CARPET:
                case ITEM1_CAT_WALL:
                case ITEM1_CAT_MINIDISK:
                case ITEM1_CAT_DUMMY:
                    icon = &item_tex_data_table[category][0];
                    break;
                default:
                    icon = &item_tex_data_table[category][groupNo];
                    break;
            }
        }
    }

    if (icon != NULL) {
        if ((category == ITEM1_CAT_FISH || category == ITEM1_CAT_INSECT) && anim_frame != 0) {
            /* Fish & insects have two back-to-back palettes for inventory & collection windows */
            palette = 16 + icon->pal;
        } else {
            palette = icon->pal;
        }

        if (color_flag) {
            if (alpha_flag) {
                color.a = (int)(((48 - anim_frame) * 255) / 26);
            } else {
                color.a = 255;
            }

            color.r = 255;
            color.g = 255;
            color.b = 255;
            l = 255;
        } else {
            color.r = 100;
            color.g = 115;
            color.b = 160;
            color.a = 255;
            l = 100;
        }
    }

    if (icon != NULL) {
        mSM_set_dl_item(graph, pos_x, pos_y, scale, icon, palette, l, &color, shadow_flag, mark_flag);
    }
}

enum {
    mSM_MAIL_NORMAL,
    mSM_MAIL_PRESENT,
    mSM_MAIL_SEND,
    mSM_MAIL_SEND_PRESENT,
    mSM_MAIL_NORMAL2,
    mSM_MAIL_PRESENT2,

    mSM_MAIL_NUM
};

extern u16 inv_mwin_mtegami_pal[];
extern u8 inv_mwin_mtegami_tex[];
extern u8 inv_mwin_pmtegami_tex[];

extern u16 inv_mwin_otegami_pal[];
extern u8 inv_mwin_otegami_tex[];
extern u8 inv_mwin_potegami_tex[];

extern u16 inv_mwin_mtegami2_pal[];
extern u8 inv_mwin_mtegami2_tex[];
extern u8 inv_mwin_pmtegami2_tex[];

extern Gfx inv_item_model[];
extern Gfx inv_mark_model[];

static void mSM_draw_mail(GRAPH* graph, f32 pos_x, f32 pos_y, f32 scale, Mail_c* mail, int color_flag, int shadow_flag,
                          int mark_flag) {
    static mSM_inventory_icon_info_c letter_tex_data_table[] = {
        /* Letters */
        { inv_mwin_mtegami_pal, inv_mwin_mtegami_tex },
        { inv_mwin_mtegami_pal, inv_mwin_pmtegami_tex },

        /* Send letters */
        { inv_mwin_otegami_pal, inv_mwin_otegami_tex },
        { inv_mwin_otegami_pal, inv_mwin_potegami_tex },

        /* Opened? letters */
        { inv_mwin_mtegami2_pal, inv_mwin_mtegami2_tex },
        { inv_mwin_mtegami2_pal, inv_mwin_pmtegami2_tex },
    };

    mSM_inventory_icon_info_c* icon;
    int type;

    if (mMl_check_send_mail(mail)) {
        type = mSM_MAIL_SEND;
    } else if (mail->content.font == mMl_FONT_RECV_PLAYER_PRESENT_READ || mail->content.font == mMl_FONT_RECV_READ) {
        type = mSM_MAIL_NORMAL2;
    } else {
        type = mSM_MAIL_NORMAL;
    }

    if (mail->present != EMPTY_NO) {
        type++;
    }

    icon = &letter_tex_data_table[type];
    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(pos_x, pos_y, 140.0f, MTX_MULT);
    Matrix_scale(scale, scale, 1.0f, MTX_MULT);

    OPEN_POLY_OPA_DISP(graph);

    gDPPipeSync(POLY_OPA_DISP++);
    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(POLY_OPA_DISP++, G_MWO_SEGMENT_9, icon->pal);
    gSPSegment(POLY_OPA_DISP++, G_MWO_SEGMENT_A, icon->tex);
    gDPSetAlphaCompare(POLY_OPA_DISP++, G_AC_THRESHOLD);
    gDPSetBlendColor(POLY_OPA_DISP++, 255, 255, 255, 40);

    if (color_flag) {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 255, 255, 255, 255);
    } else {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 130, 255, 110, 105, 255);
    }

    if (shadow_flag == FALSE) {
        gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL0, PRIMITIVE, PRIM_LOD_FRAC, PRIMITIVE, 0, 0, 0, TEXEL0, TEXEL0,
                          PRIMITIVE, PRIM_LOD_FRAC, PRIMITIVE, 0, 0, 0, TEXEL0);
    }

    gSPDisplayList(POLY_OPA_DISP++, inv_item_model);

    if (mark_flag) {
        f32 frame_per = (((f32)(gamePT->frame_counter % 40)) * (1.0f / 40.0f)) * 2.0f;

        if (frame_per > 1.0f) {
            frame_per = 2.0f - frame_per;
        }

        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, (int)(frame_per * 90.0f + 95.0f), 0, 255);
        gDPSetEnvColor(POLY_OPA_DISP++, (int)(frame_per * 60.0f), (int)(frame_per * 45.0f + 210.0f),
                       (int)(frame_per * 60.0f), 255);
        gSPDisplayList(POLY_OPA_DISP++, inv_mark_model);
    }

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetTextureLUT(POLY_OPA_DISP++, G_TT_RGBA16);
    gDPSetAlphaCompare(POLY_OPA_DISP++, G_AC_NONE);
    gDPSetBlendColor(POLY_OPA_DISP++, 255, 255, 255, 8);

    CLOSE_POLY_OPA_DISP(graph);
}

extern void mSM_draw_original(Submenu* submenu, GRAPH* graph, f32 pos_x, f32 pos_y, f32 scale, mActor_name_t item,
                              int shadow_flag) {
    if (ITEM_IS_RSVNWORG(item)) {
        mNW_draw_original(submenu, graph, pos_x, pos_y, scale, item - RSV_NW_ORIGINAL0, shadow_flag);
    }

    if (ITEM_IS_RSVCPORG(item)) {
        mCO_draw_cporiginal(submenu, graph, pos_x, pos_y, scale, item - RSV_NW_ORIGINAL0, shadow_flag);
    }

    if (ITEM_IS_RSVGBAORG(item)) {
        mGB_draw_gba(submenu, graph, pos_x, pos_y, scale, item - RSV_GBAORIGINAL0, shadow_flag);
    }
}

static mSM_Ovl_dlftbl_c mSM_program_dlftbl[] = {
    {
        0,
        0,
        NULL,
        NULL,
        &mIV_inventory_ovl_construct,
        &mIV_inventory_ovl_destruct,
        &mIV_inventory_ovl_set_proc,
        FALSE,
    },
    {
        0,
        0,
        NULL,
        NULL,
        &mIV_inventory_ovl_construct,
        &mIV_inventory_ovl_destruct,
        &mIV_inventory_ovl_set_proc,
        FALSE,
    },
    {
        0,
        0,
        NULL,
        NULL,
        &mHB_hboard_ovl_construct,
        &mHB_hboard_ovl_destruct,
        &mHB_hboard_ovl_set_proc,
        FALSE,
    },
    {
        0,
        0,
        NULL,
        NULL,
        &mTI_timeIn_ovl_construct,
        &mTI_timeIn_ovl_destruct,
        &mTI_timeIn_ovl_set_proc,
        FALSE,
    },
    {
        0,
        0,
        NULL,
        NULL,
        &mLE_ledit_ovl_construct,
        &mLE_ledit_ovl_destruct,
        &mLE_ledit_ovl_set_proc,
        FALSE,
    },
    {
        0,
        0,
        NULL,
        NULL,
        &mMP_map_ovl_construct,
        &mMP_map_ovl_destruct,
        &mMP_map_ovl_set_proc,
        FALSE,
    },
    {
        0,
        0,
        NULL,
        NULL,
        &mNT_notice_ovl_construct,
        &mNT_notice_ovl_destruct,
        &mNT_notice_ovl_set_proc,
        FALSE,
    },
    {
        0,
        0,
        NULL,
        NULL,
        &mRP_repay_ovl_construct,
        &mRP_repay_ovl_destruct,
        &mRP_repay_ovl_set_proc,
        FALSE,
    },
    {
        0,
        0,
        NULL,
        NULL,
        &mMS_mscore_ovl_construct,
        &mMS_mscore_ovl_destruct,
        &mMS_mscore_ovl_set_proc,
        FALSE,
    },
    {
        0,
        0,
        NULL,
        NULL,
        &mBR_birthday_ovl_construct,
        &mBR_birthday_ovl_destruct,
        &mBR_birthday_ovl_set_proc,
        FALSE,
    },
    {
        0,
        0,
        NULL,
        NULL,
        &mED_editor_ovl_construct,
        &mED_editor_ovl_destruct,
        &mED_editor_ovl_set_proc,
        FALSE,
    },
    {
        0,
        0,
        NULL,
        NULL,
        &mMB_mailbox_ovl_construct,
        &mMB_mailbox_ovl_destruct,
        &mMB_mailbox_ovl_set_proc,
        FALSE,
    },
    {
        0,
        0,
        NULL,
        NULL,
        &mBD_board_ovl_construct,
        &mBD_board_ovl_destruct,
        &mBD_board_ovl_set_proc,
        FALSE,
    },
    {
        0,
        0,
        NULL,
        NULL,
        &mAD_address_ovl_construct,
        &mAD_address_ovl_destruct,
        &mAD_address_ovl_set_proc,
        FALSE,
    },
    {
        0,
        0,
        NULL,
        NULL,
        &mHW_haniwa_ovl_construct,
        &mHW_haniwa_ovl_destruct,
        &mHW_haniwa_ovl_set_proc,
        FALSE,
    },
    {
        0,
        0,
        NULL,
        NULL,
        &mEE_editEndChk_ovl_construct,
        &mEE_editEndChk_ovl_destruct,
        &mEE_editEndChk_ovl_set_proc,
        FALSE,
    },
    {
        0,
        0,
        NULL,
        NULL,
        &mWR_warning_ovl_construct,
        &mWR_warning_ovl_destruct,
        &mWR_warning_ovl_set_proc,
        FALSE,
    },
    {
        0,
        0,
        NULL,
        NULL,
        &mCM_cpmail_ovl_construct,
        &mCM_cpmail_ovl_destruct,
        &mCM_cpmail_ovl_set_proc,
        FALSE,
    },
    {
        0,
        0,
        NULL,
        NULL,
        &mCW_cpwarning_ovl_construct,
        &mCW_cpwarning_ovl_destruct,
        &mCW_cpwarning_ovl_set_proc,
        FALSE,
    },
    {
        0,
        0,
        NULL,
        NULL,
        &mCE_cpedit_ovl_construct,
        &mCE_cpedit_ovl_destruct,
        &mCE_cpedit_ovl_set_proc,
        FALSE,
    },
    {
        0,
        0,
        NULL,
        NULL,
        &mCL_catalog_ovl_construct,
        &mCL_catalog_ovl_destruct,
        &mCL_catalog_ovl_set_proc,
        FALSE,
    },
    {
        0,
        0,
        NULL,
        NULL,
        &mMU_music_ovl_construct,
        &mMU_music_ovl_destruct,
        &mMU_music_ovl_set_proc,
        FALSE,
    },
    {
        0,
        0,
        NULL,
        NULL,
        &mBN_bank_ovl_construct,
        &mBN_bank_ovl_destruct,
        &mBN_bank_ovl_set_proc,
        FALSE,
    },
    {
        0,
        0,
        NULL,
        NULL,
        &mNW_needlework_ovl_construct,
        &mNW_needlework_ovl_destruct,
        &mNW_needlework_ovl_set_proc,
        FALSE,
    },
    {
        0,
        0,
        NULL,
        NULL,
        &mCO_cporiginal_ovl_construct,
        &mCO_cporiginal_ovl_destruct,
        &mCO_cporiginal_ovl_set_proc,
        FALSE,
    },
    {
        0,
        0,
        NULL,
        NULL,
        &mDE_design_ovl_construct,
        &mDE_design_ovl_destruct,
        &mDE_design_ovl_set_proc,
        FALSE,
    },
    {
        0,
        0,
        NULL,
        NULL,
        &mGB_gba_ovl_construct,
        &mGB_gba_ovl_destruct,
        &mGB_gba_ovl_set_proc,
        FALSE,
    },
    {
        0,
        0,
        NULL,
        NULL,
        &mDI_diary_ovl_construct,
        &mDI_diary_ovl_destruct,
        &mDI_diary_ovl_set_proc,
        FALSE,
    },
    {
        0,
        0,
        NULL,
        NULL,
        &mCD_calendar_ovl_construct,
        &mCD_calendar_ovl_destruct,
        &mCD_calendar_ovl_set_proc,
        FALSE,
    },
    {
        0,
        0,
        NULL,
        NULL,
        &mPM_passwordMake_ovl_construct,
        &mPM_passwordMake_ovl_destruct,
        &mPM_passwordMake_ovl_set_proc,
        FALSE,
    },
    {
        0,
        0,
        NULL,
        NULL,
        &mPC_passwordChk_ovl_construct,
        &mPC_passwordChk_ovl_destruct,
        &mPC_passwordChk_ovl_set_proc,
        FALSE,
    },
};

// clang-format off
static mSM_Ovl_dlftbl_c tag_program_dlftbl = {
    0,
    0,
    NULL,
    NULL,
    &mTG_tag_ovl_construct,
    &mTG_tag_ovl_destruct,
    &mTG_tag_ovl_destruct,
    FALSE,
};
// clang-format on

// clang-format off
static mSM_Ovl_dlftbl_c hand_program_dlftbl = {
    0,
    0,
    NULL,
    NULL,
    &mHD_hand_ovl_construct,
    &mHD_hand_ovl_destruct,
    &mHD_hand_ovl_destruct,
    FALSE,
};
// clang-format on

// clang-format off
static mSM_Ovl_dlftbl_c haniwa_program_dlftbl = {
    0,
    0,
    NULL,
    NULL,
    &mHP_haniwaPortrait_ovl_construct,
    &mHP_haniwaPortrait_ovl_destruct,
    &mHP_haniwaPortrait_ovl_destruct,
    FALSE,
};
// clang-format on

static void mSM_ovl_prog_seg(Submenu* submenu, mSM_Ovl_dlftbl_c* dlftbl) {
    mSM_Segment_c* segment = &submenu->overlay->segment;

    if (dlftbl->in_ram_flag == TRUE) {
        dlftbl->ct_proc(submenu);
    } else {
        mSM_OVL_CT_PROC ct_proc;

        dlftbl->seg_start = NULL;
        dlftbl->seg_end = NULL;
        submenu->next_overlay_address = (char*)ALIGN_NEXT((uintptr_t)dlftbl->seg_end - (uintptr_t)dlftbl->seg_start, 64);
        ct_proc = dlftbl->ct_proc;
        (*ct_proc)(submenu);
        dlftbl->ct_proc = ct_proc;
        dlftbl->in_ram_flag = TRUE;
        segment->dlftbl_loaded_tbl[segment->dlftbl_loaded_num] = dlftbl;
        segment->dlftbl_loaded_num++;
    }
}

static void mSM_set_other_seg(Submenu* submenu) {
    static u8 flg_table[] = {
        mSM_OVL_FLAG_NONE,
        mSM_OVL_FLAG_USE_ITEM | mSM_OVL_FLAG_USE_TAG | mSM_OVL_FLAG_USE_HAND,
        mSM_OVL_FLAG_USE_HANIWA_PORTRAIT,
        mSM_OVL_FLAG_NONE,
        mSM_OVL_FLAG_NONE,
        mSM_OVL_FLAG_NONE,
        mSM_OVL_FLAG_NONE,
        mSM_OVL_FLAG_NONE,
        mSM_OVL_FLAG_NONE,
        mSM_OVL_FLAG_NONE,
        mSM_OVL_FLAG_NONE,
        mSM_OVL_FLAG_USE_ITEM | mSM_OVL_FLAG_USE_TAG | mSM_OVL_FLAG_USE_HAND,
        mSM_OVL_FLAG_NONE,
        mSM_OVL_FLAG_NONE,
        mSM_OVL_FLAG_USE_ITEM | mSM_OVL_FLAG_USE_TAG | mSM_OVL_FLAG_USE_HAND | mSM_OVL_FLAG_USE_HANIWA_PORTRAIT,
        mSM_OVL_FLAG_NONE,
        mSM_OVL_FLAG_NONE,
        mSM_OVL_FLAG_USE_ITEM | mSM_OVL_FLAG_USE_TAG | mSM_OVL_FLAG_USE_HAND,
        mSM_OVL_FLAG_NONE,
        mSM_OVL_FLAG_USE_TAG | mSM_OVL_FLAG_USE_HAND,
        mSM_OVL_FLAG_USE_TAG | mSM_OVL_FLAG_USE_HAND,
        mSM_OVL_FLAG_USE_ITEM | mSM_OVL_FLAG_USE_TAG | mSM_OVL_FLAG_USE_HAND,
        mSM_OVL_FLAG_NONE,
        mSM_OVL_FLAG_USE_TAG | mSM_OVL_FLAG_USE_HAND,
        mSM_OVL_FLAG_NONE,
        mSM_OVL_FLAG_NONE,
        mSM_OVL_FLAG_NONE,
        mSM_OVL_FLAG_NONE,
        mSM_OVL_FLAG_NONE,
        mSM_OVL_FLAG_NONE,
        mSM_OVL_FLAG_NONE,
    };

    int flg = flg_table[submenu->current_menu_type];

    if ((flg & mSM_OVL_FLAG_USE_TAG) != 0) {
        mSM_ovl_prog_seg(submenu, &tag_program_dlftbl);
    }

    if ((flg & mSM_OVL_FLAG_USE_HAND) != 0) {
        mSM_ovl_prog_seg(submenu, &hand_program_dlftbl);
    }

    if ((flg & mSM_OVL_FLAG_USE_HANIWA_PORTRAIT) != 0) {
        mSM_ovl_prog_seg(submenu, &haniwa_program_dlftbl);
    }
}

static void mSM_set_before_menu_proc(Submenu* submenu) {
    int type = submenu->menu_type;
    mSM_Ovl_dlftbl_c* dlftbl = &mSM_program_dlftbl[type];
    mSM_MenuInfo_c* menu_info;

    dlftbl->set_proc(submenu);
    submenu->current_menu_type = type;
    menu_info = &submenu->overlay->menu_info[type];
    menu_info->next_menu_type = mSM_OVL_NONE;
}

static void mSM_set_new_seg(Submenu* submenu) {
    int type = submenu->menu_type;

    mSM_ovl_prog_seg(submenu, &mSM_program_dlftbl[type]);
    submenu->current_menu_type = type;
}

typedef struct submenu_ovl_start_data_s {
    f32 pos_x;
    f32 pos_y;
    f32 speed_x;
    f32 speed_y;
} mSM_ovl_start_data_c;

static void mSM_set_new_start_data(Submenu* submenu) {
    // clang-format off
    static mSM_ovl_start_data_c data_table[] = {
        { 0.0, 0.0, 0.0, 0.0, },
        { 300.0, 0.0, 75.0, 0.0, },
        { 0.0, 300.0, 0.0, 75.0, },
        { 0.0, 300.0, 0.0, 75.0, },
        { 0.0, 300.0, 0.0, 75.0, },
        { 0.0, 300.0, 0.0, 75.0, },
        { 0.0, 300.0, 0.0, 75.0, },
        { 0.0, 300.0, 0.0, 75.0, },
        { 0.0, 300.0, 0.0, 75.0, },
        { 0.0, 300.0, 0.0, 75.0, },
        { 0.0, -300.0, 0.0, 75.0, },
        { -300.0, 0.0, 75.0, 0.0, },
        { 0.0, 300.0, 0.0, 75.0, },
        { 0.0, 0.0, 0.0, 0.0, },
        { -300.0, 0.0, 75.0, 0.0, },
        { 0.0, -300.0, 0.0, 75.0, },
        { 0.0, 0.0, 0.0, 0.0, },
        { 300.0, 0.0, 75.0, 0.0, },
        { 0.0, 0.0, 0.0, 0.0, },
        { 0.0, 300.0, 0.0, 75.0, },
        { 300.0, 0.0, 75.0, 0.0, },
        { -300.0, 0.0, 75.0, 0.0, },
        { 0.0, 300.0, 0.0, 75.0, },
        { 300.0, 0.0, 75.0, 0.0, },
        { 300.0, 0.0, 75.0, 0.0, },
        { 0.0, 300.0, 0.0, 75.0, },
        { -300.0, 0.0, 75.0, 0.0, },
        { -300.0, 0.0, 75.0, 0.0, },
        { 0.0, 300.0, 0.0, 75.0, },
        { 0.0, 300.0, 0.0, 75.0, },
        { 0.0, 300.0, 0.0, 75.0, },
    };
    // clang-format on
    int type = submenu->menu_type;
    mSM_MenuInfo_c* menu = &submenu->overlay->menu_info[type];
    mSM_ovl_start_data_c* data = &data_table[type];

    menu->menu_type = type;
    menu->position[0] = data->pos_x;
    menu->position[1] = data->pos_y;
    menu->speed[0] = data->speed_x;
    menu->speed[1] = data->speed_y;
    menu->data0 = submenu->param0;
    menu->data1 = submenu->param1;
    menu->data2 = submenu->param2;
    menu->data3 = submenu->param3;
    menu->move_flag = FALSE;

    if (type == mSM_OVL_INVENTORY && submenu->param0 == mSM_IV_OPEN_CPMAIL) {
        menu->position[0] = -300.0f;
    }

    if (type == mSM_OVL_NEEDLEWORK && submenu->param0 == 2) {
        menu->position[0] = -300.0f;
    }
}

static void mSM_move_chg_base(mSM_MenuInfo_c* menu_info, int mv_dir) {
    menu_info->proc_status = mSM_OVL_PROC_MOVE;
    menu_info->move_drt = mv_dir;

    if ((mv_dir & 1) != 0) {
        menu_info->next_proc_status = mSM_OVL_PROC_PLAY;
    } else {
        menu_info->next_proc_status = mSM_OVL_PROC_END;
    }
}

static void mSM_make_trigger_data(Submenu* submenu) {
    static u32 add_trigger[] = { BUTTON_CRIGHT, BUTTON_CUP, BUTTON_CLEFT, BUTTON_CDOWN };
    int trigger = (getButton() & 0xF) | getTrigger();
    mSM_Control_c* control = &submenu->overlay->menu_control;

    if (gamePT->mcon.move_pR > 0.5f) {
        u16 angle = gamePT->mcon.move_angle + DEG2SHORT_ANGLE2(45.0f);

        trigger |= add_trigger[angle / DEG2SHORT_ANGLE2(90.0f)];
    }

    if (trigger == control->last_trigger) {
        if (control->repeat_timer > 0) {
            control->repeat_timer--;
            trigger = 0;
        } else {
            control->repeat_timer = 3;
        }
    } else {
        control->last_trigger = trigger;
        control->repeat_timer = 25;
    }

    control->trigger = trigger;
}

static void mSM_save_before_func(Submenu* submenu) {
    Submenu_Overlay_c* ovl = submenu->overlay;
    mSM_MenuInfo_c* menu_info = &ovl->menu_info[submenu->menu_type];
    mSM_MenuInfo_c* prev_info = &ovl->menu_info[submenu->current_menu_type];

    menu_info->pre_menu_type = submenu->current_menu_type;
    menu_info->pre_move_func = ovl->menu_control.menu_move_func;
    menu_info->pre_draw_func = ovl->menu_control.menu_draw_func;
    prev_info->next_menu_type = submenu->menu_type;
}

static void mSM_set_proc(Submenu* submenu) {
    mSM_save_before_func(submenu);
    mSM_set_new_start_data(submenu);
    mSM_set_new_seg(submenu);
    mSM_set_other_seg(submenu);
}

static void mSM_tex_move(Submenu* submenu) {
    mSM_Control_c* control = &submenu->overlay->menu_control;

    control->texture_pos[0] += 0.3535f;
    control->texture_pos[1] += 0.3535f;

    while (control->texture_pos[0] >= 1024.0f) {
        control->texture_pos[0] -= 1024.0f;
    }

    while (control->texture_pos[1] >= 1024.0f) {
        control->texture_pos[1] -= 1024.0f;
    }
}

static void mSM_return_func(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    if (menu_info->next_menu_type != mSM_OVL_NONE) {
        mSM_MenuInfo_c* next_menu_info = &submenu->overlay->menu_info[menu_info->next_menu_type];
        mSM_MenuInfo_c* prev_menu_info = &submenu->overlay->menu_info[menu_info->pre_menu_type];

        next_menu_info->pre_menu_type = menu_info->pre_menu_type;
        next_menu_info->pre_move_func = menu_info->pre_move_func;
        next_menu_info->pre_draw_func = menu_info->pre_draw_func;
        prev_menu_info->next_menu_type = menu_info->next_menu_type;
    } else {
        mSM_Segment_c* segment = &submenu->overlay->segment;

        submenu->menu_type = menu_info->pre_menu_type;
        if (submenu->menu_type == mSM_OVL_NONE) {

            while (segment->dlftbl_loaded_num != 0) {
                segment->dlftbl_loaded_num--;
                segment->dlftbl_loaded_tbl[segment->dlftbl_loaded_num]->dt_proc(submenu);
            }

            submenu->process_status = mSM_PROCESS_END;
            submenu->move_proc = (SUBMENU_PROC)&none_proc1;
            submenu->current_menu_type = menu_info->pre_menu_type;
            submenu->overlay->menu_control.menu_move_func = (SUBMENU_PROC)&none_proc1;
            submenu->overlay->menu_control.menu_draw_func = (SUBMENU_GAME_PROC)&none_proc1;
            emu64_refresh();
        } else {
            mSM_set_before_menu_proc(submenu);
        }
    }

    menu_info->open_flag = FALSE;
    menu_info->pre_menu_type = mSM_OVL_NONE;
    menu_info->next_menu_type = mSM_OVL_NONE;
    menu_info->proc_status = mSM_OVL_PROC_MOVE;
    menu_info->next_proc_status = mSM_OVL_PROC_MOVE;
}

static int mSM_move_menu(f32* pos, f32* speed, s16* flag, f32 speed_mult, f32 p0, f32 p1, f32 p2) {
    if (*flag == FALSE) {
        if ((p2 * (*pos - p0)) >= 0.0f) {
            *speed *= speed_mult;
            if (*speed < 1.0f) {
                *speed = 1.0f;
            } else if (*speed > 75.0f) {
                *speed = 75.0f;
            }
        }

        *flag = TRUE;
    } else {
        *flag = FALSE;
    }

    *pos += *speed * p2 * 0.5f;
    if ((p2 * (*pos - p1)) > 0.0f) {
        *flag = FALSE;
        *pos = p1;
        return TRUE;
    }

    return FALSE;
}

typedef struct submenu_move_data_s {
    f32 speed_mult;
    f32 start_pos;
    f32 target_pos;
    f32 check_mult;
} mSM_move_data_c;

static void mSM_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    static mSM_move_data_c move_data[] = {
        { 2.0f, 0.0f, 300.0f, 1.0f },
        { 0.5f, 120.0f, 0.0f, -1.0f },
    };
    int move_dir = menu_info->move_drt;
    int idx = move_dir >> 2;
    mSM_move_data_c* data_p = &move_data[move_dir & 1];
    f32 dir;
    int res;

    if ((move_dir & 2)) {
        dir = -1.0f;
    } else {
        dir = 1.0f;
    }

    res = mSM_move_menu(&menu_info->position[idx], &menu_info->speed[idx], &menu_info->move_flag, data_p->speed_mult,
                        data_p->start_pos * dir, data_p->target_pos * dir, data_p->check_mult * dir);
    if (res == TRUE) {
        menu_info->proc_status = menu_info->next_proc_status;
    }

    /* Round down to nearest int */
    menu_info->position[idx] = (f32)(int)menu_info->position[idx];
}

static void mSM_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mSM_return_func(submenu, menu_info);
}

static void mSM_menu_ovl_move(Submenu* submenu) {
    mSM_Control_c* control = &submenu->overlay->menu_control;

    mSM_make_trigger_data(submenu);
    if (submenu->menu_type != submenu->current_menu_type) {
        mSM_set_proc(submenu);
    }

    mSM_tex_move(submenu);
    control->menu_move_func(submenu);
}

static void mSM_menu_ovl_draw(Submenu* submenu, GAME* game) {
    mSM_setup_view(submenu, game->graph, TRUE);
    submenu->overlay->menu_control.menu_draw_func(submenu, game);
}

extern void mSM_menu_ovl_init(Submenu* submenu) {
    mSM_Control_c* control = &ovl_base.menu_control;
    int i;

    submenu->overlay = &ovl_base;
    bzero(&ovl_base, sizeof(Submenu_Overlay_c));

    for (i = 0; i < mSM_OVL_NUM; i++) {
        mSM_program_dlftbl[i].in_ram_flag = FALSE;
    }

    tag_program_dlftbl.in_ram_flag = FALSE;
    hand_program_dlftbl.in_ram_flag = FALSE;
    haniwa_program_dlftbl.in_ram_flag = FALSE;

    emu64_refresh();
    submenu->current_menu_type = mSM_OVL_NONE;
    control->menu_move_func = (SUBMENU_PROC)&none_proc1;
    control->menu_draw_func = (SUBMENU_GAME_PROC)&none_proc1;
    control->hand_move_func = (mSM_HAND_MOVE_FUNC)&none_proc1;
    control->hand_draw_func = (mSM_HAND_DRAW_FUNC)&none_proc1;
    control->tag_move_func = (mSM_TAG_MOVE_FUNC)&none_proc1;
    control->tag_draw_func = (mSM_TAG_DRAW_FUNC)&none_proc1;
    control->texture_movement_angle = DEG2SHORT_ANGLE2(45.0f);

    submenu->overlay->return_func_proc = &mSM_return_func;
    submenu->overlay->move_Move_proc = &mSM_move_Move;
    submenu->overlay->move_End_proc = &mSM_move_End;
    submenu->overlay->move_chg_base_proc = &mSM_move_chg_base;
    submenu->overlay->set_char_matrix_proc = &mSM_set_char_matrix;
    submenu->overlay->cbuf_copy_proc = &mSM_cbuf_copy;
    submenu->overlay->set_drawMode_proc = &mSM_set_drawMode;
    submenu->overlay->draw_item_proc = &mSM_draw_item;
    submenu->overlay->draw_mail_proc = &mSM_draw_mail;
    submenu->overlay->setup_view_proc = &mSM_setup_view;
    submenu->overlay->change_view_proc = &mSM_change_view;
    submenu->overlay->unused_func_968 = NULL;

    mSM_set_proc(submenu);
    submenu->move_proc = &mSM_menu_ovl_move;
    submenu->draw_proc = &mSM_menu_ovl_draw;
    mSM_menu_ovl_move(submenu);
}
