#include "acgc/game_editor.hpp"
#include "pc_platform.h"
#include <aurora/aurora.h>
#include <algorithm>
#include <cmath>

namespace acgc::input {

GameEditor& game_editor() {
    static GameEditor editor;
    return editor;
}

} // namespace acgc::input

extern "C" void acgc_editor_set_available(int available, int multiline) {
    acgc::input::game_editor().set_available(available != 0, multiline != 0);
}

extern "C" GameEditorState acgc_editor_state() {
    return acgc::input::game_editor().state();
}

extern "C" size_t acgc_editor_drain(GameEditorEvent* output, size_t capacity) {
    if (!output) {
        return 0;
    }
    return acgc::input::game_editor().drain({ output, capacity });
}

extern "C" void acgc_editor_set_caret(float x, float y, float height) {
    const auto size = aurora_get_window_size();
    const float aspect = pc_widescreen_get_aspect_factor();
    if (!size.native_fb_width || !size.native_fb_height || !size.width || !size.height || g_pc_window_w <= 0 ||
        g_pc_window_h <= 0 || aspect <= 0.f) {
        acgc::input::game_editor().set_area(std::nullopt);
        return;
    }
    // Inverse of GamePointer's menu projection, including letterboxing and DPI.
    const float scale =
        std::min(float(size.native_fb_width) / g_pc_window_w, float(size.native_fb_height) / g_pc_window_h);
    const float width = g_pc_window_w * scale, viewportHeight = g_pc_window_h * scale;
    const float left = (size.native_fb_width - width) * .5f, top = (size.native_fb_height - viewportHeight) * .5f;
    const float sx = float(size.width) / size.native_fb_width, sy = float(size.height) / size.native_fb_height;
    const float nativeX = (2.f * aspect * x + (1.f - aspect) * 320.f) / 640.f;
    const float nativeY = y / 240.f;
    acgc::input::game_editor().set_area(aurora::input::TextInputArea{
        .rect = {
            .x = static_cast<int>(std::lround((left + nativeX * width) * sx)),
            .y = static_cast<int>(std::lround((top + nativeY * viewportHeight) * sy)),
            .w = 1,
            .h = std::max(1, static_cast<int>(std::lround(height / 240.f * viewportHeight * sy))),
        } });
}
