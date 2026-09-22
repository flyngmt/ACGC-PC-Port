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
static s32 g_mouse_x = 0, g_mouse_y = 0;
static s32 g_mouse_dx = 0, g_mouse_dy = 0;
static s32 g_mouse_locked = 0;
static s32 g_prev_mouse_x = 0, g_prev_mouse_y = 0;
static s32 g_mouse_moved = 0;
static u32 g_mouse_buttons_current = 0;
static u32 g_mouse_buttons_previous = 0;
static int g_mouse_active_this_frame = 0;

static s32 g_mouse_wheel_delta = 0;

void pc_mouse_initialize(SDL_Window* window) {
    pc_mouse_shutdown();
    g_mouse_window = window;
}

void pc_mouse_shutdown(void) {
    pc_mouse_lock(0);
    g_mouse_window = NULL;
    g_mouse_x = g_mouse_y = 0;
    g_mouse_dx = g_mouse_dy = 0;
    g_prev_mouse_x = g_prev_mouse_y = 0;
    g_mouse_locked = g_mouse_moved = 0;
    g_mouse_buttons_current = g_mouse_buttons_previous = 0;
    g_mouse_active_this_frame = 0;
    g_mouse_wheel_delta = 0;
}

void pc_mouse_handle_event(const SDL_Event* event) {
    if (g_mouse_window == NULL || event == NULL) {
        return;
    }
    if (event->type == SDL_EVENT_MOUSE_WHEEL && event->wheel.windowID == SDL_GetWindowID(g_mouse_window)) {
        s32 delta = event->wheel.integer_y;
        if (event->wheel.direction == SDL_MOUSEWHEEL_FLIPPED) {
            delta = -delta;
        }
        g_mouse_wheel_delta += delta;
    }
}

u32 pc_mouse_button_held(void) {
    return g_mouse_buttons_current;
}

u32 pc_mouse_button_pressed(void) {
    return (g_mouse_buttons_current & ~g_mouse_buttons_previous);
}

u32 pc_mouse_button_released(void) {
    return (~g_mouse_buttons_current & g_mouse_buttons_previous);
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
    s32 wheel = g_mouse_wheel_delta;
    if (g_mouse_wheel_delta) g_mouse_wheel_delta = 0;
    return wheel;
}

void pc_mouse_get_position(s32 *x, s32 *y) {
    if (x) *x = g_mouse_x;
    if (y) *y = g_mouse_y;
}

void pc_mouse_get_delta(s32 *dx, s32 *dy) {
    if (dx) *dx = g_mouse_dx;
    if (dy) *dy = g_mouse_dy;
}

int pc_mouse_moved(void) {
    return g_mouse_moved;
}

int pc_mouse_active(void) {
    return g_mouse_active_this_frame;
}

/* Scale mouse position to the native's game window.
 * Makes it easier to interact with menus. */
void pc_mouse_get_native_position(s32 *x, s32 *y) {
    s32 mouse_x, mouse_y;
    f32 scaled_x, scaled_y;
    
    pc_mouse_get_position(&mouse_x, &mouse_y);
    
    if (g_pc_window_w > 0 && g_pc_window_h > 0) {
#ifdef PC_ENHANCEMENTS
        const f32 aspect_factor = pc_widescreen_get_aspect_factor();
        if (aspect_factor < 1.0f) {
            const f32 aspect_offset = (1.0f - aspect_factor) * 0.5f * PC_GC_WIDTH;
            scaled_x = ((f32)mouse_x * PC_GC_WIDTH) / g_pc_window_w;
            scaled_x = (scaled_x - aspect_offset) / aspect_factor;

            scaled_y = ((f32)mouse_y * PC_GC_HEIGHT) / g_pc_window_h;
        } else
#endif
        {
            scaled_x = ((f32)mouse_x * PC_GC_WIDTH) / g_pc_window_w;
            scaled_y = ((f32)mouse_y * PC_GC_HEIGHT) / g_pc_window_h;
        }
    } else {
        scaled_x = (f32)mouse_x;
        scaled_y = (f32)mouse_y;
    }
    
    if (x) *x = (s32)scaled_x;
    if (y) *y = (s32)scaled_y;
}

void pc_mouse_update(void) {
    if (g_mouse_window == NULL) {
        return;
    }
    g_mouse_buttons_previous = g_mouse_buttons_current;

    float sdl_x, sdl_y;
    SDL_MouseButtonFlags sdl_buttons = SDL_GetMouseState(&sdl_x, &sdl_y);
    s32 mx = (s32)sdl_x;
    s32 my = (s32)sdl_y;
    g_mouse_buttons_current = 0;

    /* Convert each SDL button to our bitflag system */
    if (sdl_buttons & SDL_BUTTON_LMASK)  g_mouse_buttons_current |= PC_MOUSE_BUTTON_LEFT;
    if (sdl_buttons & SDL_BUTTON_MMASK)  g_mouse_buttons_current |= PC_MOUSE_BUTTON_MIDDLE;
    if (sdl_buttons & SDL_BUTTON_RMASK)  g_mouse_buttons_current |= PC_MOUSE_BUTTON_RIGHT;
    if (sdl_buttons & SDL_BUTTON_X1MASK) g_mouse_buttons_current |= PC_MOUSE_BUTTON_X1;
    if (sdl_buttons & SDL_BUTTON_X2MASK) g_mouse_buttons_current |= PC_MOUSE_BUTTON_X2;

    int wheel_active = 0;
    if (g_mouse_wheel_delta > 0) {
        g_mouse_buttons_current |= PC_MOUSE_WHEEL_UP;
        wheel_active = 1;
    } else if (g_mouse_wheel_delta < 0) {
        g_mouse_buttons_current |= PC_MOUSE_WHEEL_DOWN;
        wheel_active = 1;
    }

    g_mouse_moved = (mx != g_prev_mouse_x || my != g_prev_mouse_y);

    g_mouse_active_this_frame = (g_mouse_moved || 
                                 (g_mouse_buttons_current & ~(PC_MOUSE_WHEEL_UP | PC_MOUSE_WHEEL_DOWN)) ||
                                 wheel_active);
    
    float mdx = 0, mdy = 0;
    SDL_GetRelativeMouseState(&mdx, &mdy);
    
    if (g_mouse_locked) {
        g_mouse_dx = (s32)mdx;
        g_mouse_dy = (s32)mdy;
    } else {
        g_mouse_dx = mx - g_mouse_x;
        g_mouse_dy = my - g_mouse_y;
    }

    g_prev_mouse_x = g_mouse_x;
    g_prev_mouse_y = g_mouse_y;
    g_mouse_x = mx;
    g_mouse_y = my;
}

#endif /* MOUSE_INPUT */
