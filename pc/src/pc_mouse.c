/* pc_mouse.c - Mouse input mode for menus and misc interfaces.
 * When an interface is active, mouse can be used to interact with it.
 * There's helpers to see when a mouse is moved, wheel movement and clicks. */

#include "pc_mouse.h"

#ifdef MOUSE_INPUT
#include "pc_platform.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_video.h>

static SDL_Window* g_mouse_window = NULL;
static f32 g_mouse_x = 0, g_mouse_y = 0;
static f32 g_mouse_ui_x = -1, g_mouse_ui_y = -1;
static int g_mouse_inside_viewport = 0;
static u32 g_mouse_suppressed_buttons = 0;
static s32 g_mouse_dx = 0, g_mouse_dy = 0;
static s32 g_mouse_locked = 0;
static s32 g_mouse_moved = 0;
static u32 g_mouse_buttons_current = 0;
static u32 g_mouse_buttons_pressed = 0;
static u32 g_mouse_buttons_released = 0;
static int g_mouse_active_this_frame = 0;

static s32 g_mouse_wheel_delta = 0;
static s32 g_pending_mouse_wheel_delta = 0;
static u32 g_pending_mouse_pressed = 0;
static u32 g_pending_mouse_released = 0;

static u32 pc_mouse_buttons_from_sdl(SDL_MouseButtonFlags buttons) {
    u32 result = 0;
    if (buttons & SDL_BUTTON_LMASK)  result |= PC_MOUSE_BUTTON_LEFT;
    if (buttons & SDL_BUTTON_MMASK)  result |= PC_MOUSE_BUTTON_MIDDLE;
    if (buttons & SDL_BUTTON_RMASK)  result |= PC_MOUSE_BUTTON_RIGHT;
    if (buttons & SDL_BUTTON_X1MASK) result |= PC_MOUSE_BUTTON_X1;
    if (buttons & SDL_BUTTON_X2MASK) result |= PC_MOUSE_BUTTON_X2;
    return result;
}

static int pc_mouse_map_ui_position(f32 x, f32 y, f32* ui_x, f32* ui_y) {
    int window_width, window_height, pixel_width, pixel_height;
    if (ui_x) *ui_x = -1.0f;
    if (ui_y) *ui_y = -1.0f;
    if (g_mouse_window == NULL ||
        !SDL_GetWindowSize(g_mouse_window, &window_width, &window_height) ||
        !SDL_GetWindowSizeInPixels(g_mouse_window, &pixel_width, &pixel_height) ||
        window_width <= 0 || window_height <= 0 || pixel_width <= 0 || pixel_height <= 0 ||
        g_pc_window_w <= 0 || g_pc_window_h <= 0) {
        return 0;
    }

    int viewport_width = pixel_width;
    int viewport_height = (int)fmin(pixel_height, fmax(1.0,
        round((double)viewport_width * g_pc_window_h / g_pc_window_w)));
    if (viewport_height == pixel_height) {
        viewport_width = (int)fmin(pixel_width, fmax(1.0,
            round((double)viewport_height * g_pc_window_w / g_pc_window_h)));
    }
    const int left = (pixel_width - viewport_width) / 2;
    const int top = (pixel_height - viewport_height) / 2;
    const f32 pixel_x = x * pixel_width / window_width;
    const f32 pixel_y = y * pixel_height / window_height;
    const f32 native_x = (pixel_x - left) * PC_GC_WIDTH / viewport_width;
    const f32 native_y = (pixel_y - top) * PC_GC_HEIGHT / viewport_height;
    f32 aspect_factor = 1.0f;
#ifdef PC_ENHANCEMENTS
    aspect_factor = pc_widescreen_get_aspect_factor();
#endif
    const f32 aspect_offset = (1.0f - aspect_factor) * 0.5f * PC_GC_WIDTH;
    const f32 mapped_x = (native_x - aspect_offset) / (2.0f * aspect_factor);
    const f32 mapped_y = native_y * 0.5f;
    if (ui_x) *ui_x = mapped_x;
    if (ui_y) *ui_y = mapped_y;
    return pixel_x >= left && pixel_x < left + viewport_width &&
           pixel_y >= top && pixel_y < top + viewport_height;
}

void pc_mouse_initialize(SDL_Window* window) {
    pc_mouse_shutdown();
    g_mouse_window = window;
    if (g_mouse_window != NULL) {
        g_mouse_buttons_current = pc_mouse_buttons_from_sdl(SDL_GetMouseState(&g_mouse_x, &g_mouse_y));
        g_mouse_inside_viewport = pc_mouse_map_ui_position(g_mouse_x, g_mouse_y, &g_mouse_ui_x, &g_mouse_ui_y);
        if (!g_mouse_inside_viewport) {
            g_mouse_suppressed_buttons = g_mouse_buttons_current;
        }
        SDL_GetRelativeMouseState(NULL, NULL);
    }
}

void pc_mouse_shutdown(void) {
    pc_mouse_lock(0);
    g_mouse_window = NULL;
    g_mouse_x = g_mouse_y = 0;
    g_mouse_ui_x = g_mouse_ui_y = -1.0f;
    g_mouse_inside_viewport = 0;
    g_mouse_suppressed_buttons = 0;
    g_mouse_dx = g_mouse_dy = 0;
    g_mouse_locked = g_mouse_moved = 0;
    g_mouse_buttons_current = g_mouse_buttons_pressed = g_mouse_buttons_released = 0;
    g_mouse_active_this_frame = 0;
    g_mouse_wheel_delta = 0;
    g_pending_mouse_wheel_delta = 0;
    g_pending_mouse_pressed = g_pending_mouse_released = 0;
}

void pc_mouse_handle_event(const SDL_Event* event) {
    if (g_mouse_window == NULL || event == NULL) {
        return;
    }
    if (event->type == SDL_EVENT_MOUSE_WHEEL && event->wheel.windowID == SDL_GetWindowID(g_mouse_window)) {
        if (!pc_mouse_map_ui_position(event->wheel.mouse_x, event->wheel.mouse_y, NULL, NULL)) {
            return;
        }
        s32 delta = event->wheel.integer_y;
        if (event->wheel.direction == SDL_MOUSEWHEEL_FLIPPED) {
            delta = -delta;
        }
        g_pending_mouse_wheel_delta += delta;
    } else if ((event->type == SDL_EVENT_MOUSE_BUTTON_DOWN || event->type == SDL_EVENT_MOUSE_BUTTON_UP) &&
               event->button.windowID == SDL_GetWindowID(g_mouse_window) &&
               event->button.button >= SDL_BUTTON_LEFT && event->button.button <= SDL_BUTTON_X2) {
        const u32 button = pc_mouse_buttons_from_sdl(SDL_BUTTON_MASK(event->button.button));
        if (event->type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            if (pc_mouse_map_ui_position(event->button.x, event->button.y, NULL, NULL)) {
                g_mouse_suppressed_buttons &= ~button;
                g_pending_mouse_pressed |= button;
            } else {
                g_mouse_suppressed_buttons |= button;
            }
        } else {
            g_pending_mouse_released |= button;
            g_mouse_suppressed_buttons &= ~button;
        }
    }
}

u32 pc_mouse_button_held(void) {
    return g_mouse_inside_viewport ? g_mouse_buttons_current & ~g_mouse_suppressed_buttons : 0;
}

u32 pc_mouse_button_pressed(void) {
    return g_mouse_inside_viewport ? g_mouse_buttons_pressed & ~g_mouse_suppressed_buttons : 0;
}

u32 pc_mouse_button_released(void) {
    return g_mouse_buttons_released;
}

void pc_mouse_lock(s32 lock) {
    if (g_mouse_window != NULL && SDL_SetWindowRelativeMouseMode(g_mouse_window, lock != 0)) {
        g_mouse_locked = SDL_GetWindowRelativeMouseMode(g_mouse_window);
    }
}

int pc_mouse_is_locked(void) {
    return g_mouse_locked;
}

s32 pc_mouse_scroll_wheel(void) {
    return g_mouse_inside_viewport ? g_mouse_wheel_delta : 0;
}

void pc_mouse_get_position(s32 *x, s32 *y) {
    if (x) *x = (s32)g_mouse_x;
    if (y) *y = (s32)g_mouse_y;
}

void pc_mouse_get_delta(s32 *dx, s32 *dy) {
    if (dx) *dx = g_mouse_dx;
    if (dy) *dy = g_mouse_dy;
}

int pc_mouse_moved(void) {
    return g_mouse_inside_viewport && g_mouse_moved;
}

int pc_mouse_active(void) {
    return g_mouse_inside_viewport && g_mouse_active_this_frame;
}

int pc_mouse_get_ui_position(f32* x, f32* y) {
    if (x) *x = g_mouse_ui_x;
    if (y) *y = g_mouse_ui_y;
    return g_mouse_inside_viewport;
}

void pc_mouse_get_native_position(s32 *x, s32 *y) {
    if (x) *x = (s32)floorf(g_mouse_ui_x * 2.0f);
    if (y) *y = (s32)floorf(g_mouse_ui_y * 2.0f);
}

void pc_mouse_update(void) {
    if (g_mouse_window == NULL) {
        return;
    }
    const u32 previous_buttons = g_mouse_buttons_current;
    const u32 wheel_buttons = PC_MOUSE_WHEEL_UP | PC_MOUSE_WHEEL_DOWN;

    float mx, my;
    g_mouse_buttons_current = pc_mouse_buttons_from_sdl(SDL_GetMouseState(&mx, &my));
    g_mouse_inside_viewport = pc_mouse_map_ui_position(mx, my, &g_mouse_ui_x, &g_mouse_ui_y);
    g_mouse_suppressed_buttons &= g_mouse_buttons_current;
    if (!g_mouse_inside_viewport) {
        g_mouse_suppressed_buttons |= g_mouse_buttons_current;
    }

    g_mouse_wheel_delta = g_pending_mouse_wheel_delta;
    g_pending_mouse_wheel_delta = 0;
    if (g_mouse_wheel_delta > 0) {
        g_mouse_buttons_current |= PC_MOUSE_WHEEL_UP;
    } else if (g_mouse_wheel_delta < 0) {
        g_mouse_buttons_current |= PC_MOUSE_WHEEL_DOWN;
    }

    g_mouse_buttons_pressed = g_pending_mouse_pressed | (g_mouse_buttons_current & ~previous_buttons) |
                              (g_mouse_buttons_current & wheel_buttons);
    g_mouse_buttons_released = g_pending_mouse_released | (previous_buttons & ~g_mouse_buttons_current);
    g_pending_mouse_pressed = g_pending_mouse_released = 0;
    
    float mdx = 0, mdy = 0;
    SDL_GetRelativeMouseState(&mdx, &mdy);
    
    if (g_mouse_locked) {
        g_mouse_dx = (s32)mdx;
        g_mouse_dy = (s32)mdy;
        g_mouse_moved = (mdx != 0.0f || mdy != 0.0f);
    } else {
        g_mouse_dx = (s32)(mx - g_mouse_x);
        g_mouse_dy = (s32)(my - g_mouse_y);
        g_mouse_moved = (mx != g_mouse_x || my != g_mouse_y);
    }

    g_mouse_x = mx;
    g_mouse_y = my;

    g_mouse_active_this_frame = g_mouse_moved ||
        ((g_mouse_buttons_current | g_mouse_buttons_pressed | g_mouse_buttons_released) &
         ~(wheel_buttons | g_mouse_suppressed_buttons)) ||
        g_mouse_wheel_delta != 0;
}

#endif /* MOUSE_INPUT */
