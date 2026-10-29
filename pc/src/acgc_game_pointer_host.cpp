#include "acgc/game_pointer.hpp"
#include "aurora_mouse_cursor.h"
#include "pc_platform.h"
#include <aurora/aurora.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_timer.h>

namespace acgc::input {
GamePointer& game_pointer() {
    static GamePointer pointer;
    return pointer;
}

void update_pointer_viewport() {
    const auto size = aurora_get_window_size();
    game_pointer().set_viewport({
        static_cast<int>(size.width),
        static_cast<int>(size.height),
        static_cast<int>(size.native_fb_width),
        static_cast<int>(size.native_fb_height),
        g_pc_window_w,
        g_pc_window_h,
        pc_widescreen_get_aspect_factor(),
    });
}

void pointer_window_event(const SDL_Event& event) {
    if (auto* window = SDL_GetWindowFromEvent(&event); window && window != aurora_get_window()) {
        return;
    }
    switch (event.type) {
        case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
        case SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED:
            aurora_mouse_cursor_invalidate();
            update_pointer_viewport();
            break;
        case SDL_EVENT_WINDOW_MOUSE_LEAVE:
        case SDL_EVENT_WINDOW_MINIMIZED:
        case SDL_EVENT_WINDOW_HIDDEN:
        case SDL_EVENT_WILL_ENTER_BACKGROUND:
            game_pointer().cancel();
            break;
        default:
            break;
    }
}
} // namespace acgc::input

extern "C" const GamePointerFrame* acgc_pointer_frame() {
    return &acgc::input::game_pointer().frame();
}

extern "C" void acgc_pointer_begin_tick(uint32_t tick) {
    acgc::input::game_pointer().begin_tick(tick, SDL_GetTicksNS());
}
