#include "aurora_mouse_cursor.h"

#ifdef MOUSE_INPUT
#include "m_hand_ovl_h.h"
#include "game_pointer.h"
#include "pc_platform.h"

#include <aurora/gfx.h>
#include <dolphin/gx.h>
#include <dolphin/gx/GXAurora.h>
#include <dolphin/mtx.h>

#include <algorithm>
#include <vector>

namespace {
constexpr int kDrawSize = 64;
struct CursorFrame {
    std::vector<u8> data;
    GXTexObj texture{};
    bool ready = false;
    bool complete = false;
};
CursorFrame s_frames[AURORA_MOUSE_CURSOR_FRAME_COUNT];
int s_renderWidth = 0;
int s_renderHeight = 0;
u16 s_textureSize = AURORA_MOUSE_CURSOR_VIEW_SIZE;
f32 s_offsetX = 0.0f;
f32 s_offsetY = 0.0f;
}

extern "C" {

int aurora_mouse_cursor_needs_capture(int frame) {
    if (s_renderWidth != g_pc_window_w || s_renderHeight != g_pc_window_h) {
        aurora_mouse_cursor_invalidate();
        s_renderWidth = g_pc_window_w;
        s_renderHeight = g_pc_window_h;
        const int pixels = (kDrawSize * s_renderHeight + 479) / 480;
        // Align to RGBA8 tiles and stay within the display-list scissor range.
        s_textureSize = std::clamp((pixels + 3) & ~3, AURORA_MOUSE_CURSOR_VIEW_SIZE, 1020);
    }
    return !s_frames[frame].complete;
}

int aurora_mouse_cursor_texture_size(void) {
    return s_textureSize;
}

void aurora_mouse_cursor_invalidate(void) {
    for (auto& frame : s_frames) {
        frame.ready = false;
        frame.complete = false;
    }
}

void aurora_mouse_cursor_capture_begin(void) {
    GXCreateFrameBuffer(s_textureSize, s_textureSize);
    GXSetPixelFmt(GX_PF_RGBA6_Z24, GX_ZC_LINEAR);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);
    GXSetDstAlpha(GX_FALSE, 0);
}

void aurora_mouse_cursor_capture_end(int frame) {
    auto& cached = s_frames[frame];
    const std::size_t dataSize = s_textureSize * s_textureSize * 4;
    if (cached.data.size() != dataSize) {
        GXDestroyCopyTex(cached.data.data());
        cached.data.resize(dataSize);
    }
    GXSetTexCopySrc(0, 0, s_textureSize, s_textureSize);
    GXSetTexCopyDst(s_textureSize, s_textureSize, GX_TF_RGBA8, GX_FALSE);
    GXSetCopyFilter(GX_FALSE, nullptr, GX_FALSE, nullptr);
    GXCopyTex(cached.data.data(), GX_FALSE);
    GXPixModeSync();
    GXRestoreFrameBuffer();
    GXSetAlphaUpdate(GX_FALSE);

    GXDestroyTexObj(&cached.texture);
    GXInitTexObj(&cached.texture, cached.data.data(), s_textureSize, s_textureSize,
                 GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&cached.texture, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    mHD_mouse_pointer_get_offset(&s_offsetX, &s_offsetY);
    AuroraGXSync();
    cached.ready = true;
    cached.complete = aurora_get_stats()->queuedPipelines == 0;
}

void aurora_mouse_cursor_draw(int frame) {
    const GamePointerFrame* pointer = acgc_pointer_frame();
    if (!s_frames[frame].ready || !pointer->visible || !pointer->inside) {
        return;
    }

    const f32 aspect = pc_widescreen_get_aspect_factor();
    const f32 left = (1.0f - aspect) * 320.0f + (pointer->x + s_offsetX - 16.0f) * 2.0f * aspect;
    const f32 top = (pointer->y + s_offsetY - 16.0f) * 2.0f;
    const f32 right = left + kDrawSize * aspect;
    const f32 bottom = top + kDrawSize;

    Mtx44 projection = {
        {2.0f / 640.0f, 0.0f, 0.0f, -1.0f},
        {0.0f, -2.0f / 480.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, -1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f},
    };
    Mtx model = {{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}};
    GXSetViewport(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    GXSetScissor(0, 0, 640, 480);
    GXSetProjection(projection, GX_ORTHOGRAPHIC);
    GXLoadPosMtxImm(model, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXSetNumIndStages(0);
    GXSetNumTevStages(1);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
    GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, {0, 0, 0, 0});
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetZCompLoc(GX_FALSE);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetDstAlpha(GX_FALSE, 0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXLoadTexObj(&s_frames[frame].texture, GX_TEXMAP0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition2f32(left, top); GXTexCoord2f32(0.0f, 0.0f);
    GXPosition2f32(right, top); GXTexCoord2f32(1.0f, 0.0f);
    GXPosition2f32(right, bottom); GXTexCoord2f32(1.0f, 1.0f);
    GXPosition2f32(left, bottom); GXTexCoord2f32(0.0f, 1.0f);
    GXEnd();
}

} // extern "C"
#endif
