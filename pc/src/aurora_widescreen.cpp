#include <dolphin/gx.h>
#include <dolphin/mtx.h>

#include "pc_platform.h"

#include <cstring>

extern "C" {

float pc_widescreen_get_aspect_factor(void)
{
    if (g_pc_window_w <= 0 || g_pc_window_h <= 0) {
        return 1.0f;
    }

    const float gcAspect = static_cast<float>(PC_GC_WIDTH) / static_cast<float>(PC_GC_HEIGHT);
    const float renderAspect = static_cast<float>(g_pc_window_w) / static_cast<float>(g_pc_window_h);
    if (renderAspect <= gcAspect + 0.01f) {
        return 1.0f;
    }
    return gcAspect / renderAspect;
}

void pc_widescreen_set_projection(const void* mtx, u32 type)
{
    Mtx44 adjusted;
    std::memcpy(adjusted, mtx, sizeof(adjusted));

    const float aspectFactor = pc_widescreen_get_aspect_factor();
    const bool correctProjection =
        g_pc_widescreen_stretch == 0 ||
        (g_pc_widescreen_stretch == 2 && type == GX_ORTHOGRAPHIC);
    if (correctProjection && aspectFactor < 1.0f) {
        adjusted[0][0] *= aspectFactor;
    }

    GXSetProjection(adjusted, static_cast<GXProjectionType>(type));
}

void pc_widescreen_set_viewport(float left, float top, float width, float height,
                                float nearz, float farz)
{
    const float aspectFactor = pc_widescreen_get_aspect_factor();
    if (g_pc_widescreen_stretch == 2 && aspectFactor < 1.0f) {
        const bool isFullViewport =
            left < 1.0f && top < 1.0f &&
            width > static_cast<float>(PC_GC_WIDTH - 1) &&
            height > static_cast<float>(PC_GC_HEIGHT - 1);
        if (!isFullViewport) {
            const float contentLeft =
                (1.0f - aspectFactor) * 0.5f * static_cast<float>(PC_GC_WIDTH);
            left = contentLeft + left * aspectFactor;
            width *= aspectFactor;
        }
    }

    GXSetViewport(left, top, width, height, nearz, farz);
}

} // extern "C"
